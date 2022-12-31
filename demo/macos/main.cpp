#include <fstream>
#include <iostream>
#include <type_traits>
#include <simd/simd.h>
#include "appkit/Application.hpp"
#include "appkit/Menu.hpp"
#include "appkit/Screen.hpp"
#include "appkit/Window.hpp"
#include "coregraphics/Color.hpp"
#include "coregraphics/ColorSpace.hpp"
#include "corevideo/DisplayLink.hpp"
#include "foundation/AutoreleasePool.hpp"
#include "foundation/Bundle.hpp"
#include "foundation/Value.hpp"
#include "metal/Metal.hpp"
#include "objc/Class.hpp"
#include "quartzcore/MetalLayer.hpp"

namespace
{
    template<typename T>
    std::enable_if_t<std::is_unsigned_v<T>, T> readUint(std::istream& stream)
    {
        std::uint8_t data[sizeof(T)];
        stream.read(reinterpret_cast<char*>(data), sizeof(T));

        T result = T(0);

        for (std::size_t i = 0; i < sizeof(T); ++i)
            result |= static_cast<T>(static_cast<std::uint8_t>(data[i]) << ((sizeof(T) - i - 1) * 8));

        return result;
    }

    mtl::Texture loadTexture(const ns::String& filename, mtl::Device& device)
    {
        std::ifstream textureFile{filename.cString(), std::ios::binary};
        const auto mipmapCount = readUint<std::uint8_t>(textureFile);
        auto width = readUint<std::uint32_t>(textureFile);
        auto height = readUint<std::uint32_t>(textureFile);

        mtl::TextureDescriptor textureDescriptor;
        textureDescriptor.setWidth(static_cast<ns::UInteger>(width));
        textureDescriptor.setHeight(static_cast<ns::UInteger>(height));
        textureDescriptor.setPixelFormat(mtl::PixelFormat::RGBA8Unorm);
        textureDescriptor.setTextureType(mtl::TextureType::Type2D);
        textureDescriptor.setMipmapLevelCount(mipmapCount);

        auto texture = device.newTexture(textureDescriptor);

        std::unique_ptr<char[]> pixelBytes{new char[width * height * 4]};

        for (std::uint32_t i = 0; i < mipmapCount; ++i)
        {
            if (i != 0)
            {
                width = readUint<std::uint32_t>(textureFile);
                height = readUint<std::uint32_t>(textureFile);
            }

            textureFile.read(pixelBytes.get(), width * height * 4);

            texture.replaceRegion(mtl::Region{0, 0, 0, width, height, 1},
                                  i,
                                  pixelBytes.get(),
                                  width * 4);
        }

        return texture;
    }

    CVReturn renderCallback(CVDisplayLinkRef,
                            const CVTimeStamp*,
                            const CVTimeStamp*,
                            CVOptionFlags,
                            CVOptionFlags*,
                            void* displayLinkContext);

    matrix_float4x4 projectionMatrix() noexcept
    {
        matrix_float4x4 m = {
            .columns[0] = { 1, 0, 0, 0 },
            .columns[1] = { 0, 1.5, 0, 0 },
            .columns[2] = { 0, 0, 1, 0 },
            .columns[3] = { 0, 0, 0, 1 }
        };
        return m;
    }

    matrix_float4x4 rotationMatrix2d(const float radians) noexcept
    {
        const float c = std::cosf(radians);
        const float s = std::sinf(radians);

        matrix_float4x4 m = {
            .columns[0] = {  c, s, 0, 0 },
            .columns[1] = { -s, c, 0, 0 },
            .columns[2] = {  0, 0, 1, 0 },
            .columns[3] = {  0, 0, 0, 1 }
        };
        return m;
    }

    static const char* shadersSource =
    "#include <metal_stdlib>\n" \
    "#include <simd/simd.h>\n" \

    "using namespace metal;\n" \

    "typedef struct\n" \
    "{\n" \
    "    float4x4 projectionMatrix;\n" \
    "    float4x4 modelMatrix;\n" \
    "} Uniforms;\n" \

    "typedef struct\n" \
    "{\n" \
    "    float4 position [[attribute(0)]];\n" \
    "    half4 color [[attribute(1)]];\n" \
    "    float2 texCoord [[attribute(2)]];\n" \
    "} VertexIn;\n" \

    "typedef struct {\n" \
    "    float4 position [[position]];\n" \
    "    half4  color;\n" \
    "    float2 texCoord;\n" \
    "} VertexOut;\n" \

    "vertex VertexOut vertex_function(const VertexIn input [[stage_in]],\n" \
    "                                 constant Uniforms &uniforms [[buffer(1)]])\n" \
    "{\n" \
    "    VertexOut out;\n" \
    "    out.position = uniforms.projectionMatrix * uniforms.modelMatrix * input.position;\n" \
    "    out.color = half4(input.color);\n" \
    "    out.texCoord = input.texCoord;\n" \
    "    return out;\n" \
    "}\n" \

    "fragment half4 fragment_function(VertexOut in [[stage_in]],\n" \
    "                                 texture2d<float> diffuseTexture [[texture(0)]],\n" \
    "                                 sampler diffuseSampler [[sampler(0)]],\n" \
    "                                 texture2d<float> normalTexture [[texture(1)]],\n" \
    "                                 sampler normalSampler [[sampler(1)]])\n" \
    "{\n" \
    "    return in.color * half4(diffuseTexture.sample(diffuseSampler, in.texCoord)) * half4(normalTexture.sample(normalSampler, in.texCoord));\n" \
    "}";
}

class Application final
{
public:
    Application()
    {
        void* thisPointer = this;

        appDelegateClass.addMethod(sel_registerName("applicationWillTerminate:"),
                                   applicationWillTerminate,
                                   "v@:@");
        appDelegateClass.addMethod(sel_registerName("applicationShouldTerminateAfterLastWindowClosed:"),
                                   applicationShouldTerminateAfterLastWindowClosed,
                                   "b@:@");
        appDelegateClass.reg();
        appDelegate = appDelegateClass.createInstance();
        std::memcpy(appDelegate.getIndexedIvars(), thisPointer, sizeof(thisPointer));

        application.activateIgnoringOtherApps(true);
        application.setDelegate(appDelegate);
        createMainMenu();

        const auto windowStyleMask = ns::WindowStyleMask::Titled | ns::WindowStyleMask::Closable | ns::WindowStyleMask::Miniaturizable | ns::WindowStyleMask::Resizable;

        const auto screenFrame = screen.frame();
        const ns::Size windowSize{
            std::round(screenFrame.size.width * 0.6),
            std::round(screenFrame.size.height * 0.6)
        };

        const ns::Rect frame{
            std::round(screenFrame.size.width / 2.0F - windowSize.width / 2.0F),
            std::round(screenFrame.size.height / 2.0F - windowSize.height / 2.0F),
            windowSize.width, windowSize.height
        };

        ns::Window window{frame, windowStyleMask, ns::BackingStoreType::Buffered, false, screen};
        std::memcpy(window.getIndexedIvars(), thisPointer, sizeof(thisPointer));
        window.setTitle("demo");
        window.setCollectionBehavior(ns::WindowCollectionBehavior::FullScreenPrimary);

        window.setTabbingMode(ns::WindowTabbingMode::Disallowed);
        window.setAcceptsMouseMovedEvents(true);

        windowDelegateClass.addMethod(sel_registerName("windowDidResize:"), windowDidResize, "v@:@");
        windowDelegateClass.reg();
        windowDelegate = windowDelegateClass.createInstance();
        std::memcpy(windowDelegate.getIndexedIvars(), thisPointer, sizeof(thisPointer));
        window.setDelegate(windowDelegate);

        viewClass.addMethod(sel_registerName("isOpaque"), isOpaque, "B@:");
        viewClass.addMethod(sel_registerName("acceptsFirstResponder"), acceptsFirstResponder, "B@:");
        viewClass.addMethod(sel_registerName("acceptsFirstMouse:"), acceptsFirstMouse, "B@:@");
        viewClass.addMethod(sel_registerName("keyDown:"), keyDown, "v@:@");
        viewClass.addMethod(sel_registerName("keyUp:"), keyUp, "v@:@");
        viewClass.addMethod(sel_registerName("mouseDown:"), mouseDown, "v@:@");
        viewClass.addMethod(sel_registerName("mouseUp:"), mouseUp, "v@:@");
        viewClass.addMethod(sel_registerName("rightMouseDown:"), rightMouseDown, "v@:@");
        viewClass.addMethod(sel_registerName("rightMouseUp:"), rightMouseUp, "v@:@");
        viewClass.addMethod(sel_registerName("otherMouseDown:"), otherMouseDown, "v@:@");
        viewClass.addMethod(sel_registerName("otherMouseUp:"), otherMouseUp, "v@:@");
        viewClass.addMethod(sel_registerName("mouseMoved:"), mouseMoved, "v@:@");
        viewClass.addMethod(sel_registerName("mouseDragged:"), mouseDragged, "v@:@");
        viewClass.addMethod(sel_registerName("rightMouseDragged:"), rightMouseDragged, "v@:@");
        viewClass.addMethod(sel_registerName("otherMouseDragged:"), otherMouseDragged, "v@:@");

        viewClass.reg();

        auto view = viewClass.createInstance();
        std::memcpy(view.getIndexedIvars(), thisPointer, sizeof(thisPointer));
        view.setAutoresizingMask(ns::AutoresizingMaskOptions::WidthSizable | ns::AutoresizingMaskOptions::HeightSizable);
        view.setWantsLayer(true);

        cg::ColorSpace colorSpace = cg::ColorSpace::deviceRGB();
        const cg::Float bgColor[] = {0.0, 0.0, 0.0, 0.0};
        cg::Color backgroundColor{colorSpace, bgColor};

        metalLayer.setEdgeAntialiasingMask(ca::EdgeAntialiasingMask::None);
        metalLayer.setMasksToBounds(true);
        metalLayer.setBackgroundColor(backgroundColor);
        metalLayer.setPresentsWithTransaction(false);
        metalLayer.setAnchorPoint(cg::Point{0.5, 0.5});
        metalLayer.setFrame(cg::Rect{cg::Point{0.0, 0.0}, cg::Size{frame.size.width, frame.size.height}});
        metalLayer.setMagnificationFilter(ca::FilterNearest);
        metalLayer.setMinificationFilter(ca::FilterNearest);
        metalLayer.setFramebufferOnly(false);
        metalLayer.setPixelFormat(mtl::PixelFormat::BGRA8Unorm);
        view.setLayer(metalLayer);

        window.setContentView(view);

        window.makeKeyAndOrderFront(nullptr);

        metalLayer.setDevice(device); // assign device
        const cg::Size drawableSize{windowSize.width, windowSize.height};
        metalLayer.setDrawableSize(drawableSize);

        mtl::CompileOptions options;
        options.setLanguageVersion(mtl::LanguageVersion::Version1_1);
        options.setFastMathEnabled(true);

        auto library = device.newLibrary(shadersSource, options);
        library.setLabel("Library");

        const auto vertexFunction = library.newFunction("vertex_function");
        const auto fragmentFunction = library.newFunction("fragment_function");

        mtl::VertexDescriptor vertexDescriptor;

        mtl::VertexBufferLayoutDescriptorArray vertexLayouts = vertexDescriptor.layouts();

        mtl::VertexBufferLayoutDescriptor vertexLayout0 = vertexLayouts[0];
        vertexLayout0.setStride(40);
        vertexLayout0.setStepRate(1);
        vertexLayout0.setStepFunction(mtl::VertexStepFunction::PerVertex);

        mtl::VertexAttributeDescriptorArray vertexAttributes = vertexDescriptor.attributes();

        // position
        mtl::VertexAttributeDescriptor vertexAttribute0 = vertexAttributes[0];
        vertexAttribute0.setFormat(mtl::VertexFormat::Float4);
        vertexAttribute0.setOffset(0);
        vertexAttribute0.setBufferIndex(0);

        // color
        mtl::VertexAttributeDescriptor vertexAttribute1 = vertexAttributes[1];
        vertexAttribute1.setFormat(mtl::VertexFormat::Float4);
        vertexAttribute1.setOffset(16);
        vertexAttribute1.setBufferIndex(0);

        // texCoord
        mtl::VertexAttributeDescriptor vertexAttribute2 = vertexAttributes[2];
        vertexAttribute2.setFormat(mtl::VertexFormat::Float2);
        vertexAttribute2.setOffset(32);
        vertexAttribute2.setBufferIndex(0);

        mtl::RenderPipelineDescriptor renderPipelineDescriptor;
        renderPipelineDescriptor.setLabel("renderPipeline");
        renderPipelineDescriptor.setVertexFunction(vertexFunction);
        renderPipelineDescriptor.setFragmentFunction(fragmentFunction);
        renderPipelineDescriptor.setVertexDescriptor(vertexDescriptor);
        //renderPipelineDescriptor.setDepthAttachmentPixelFormat(mtl::PixelFormat::Depth24Unorm_Stencil8);
        //renderPipelineDescriptor.setStencilAttachmentPixelFormat(mtl::PixelFormat::Depth24Unorm_Stencil8);

        const auto colorAttachments = renderPipelineDescriptor.colorAttachments();
        colorAttachments[0].setPixelFormat(mtl::PixelFormat::BGRA8Unorm);

        pipelineState = device.newRenderPipelineState(renderPipelineDescriptor);

        static const std::uint16_t indexData[] = {0, 1, 2, 3, 0, 2};
        indexBuffer = device.newBuffer(indexData, sizeof(indexData), mtl::ResourceOptions::CPUCacheModeDefaultCache);

        static const float quadVertexData[] = {
             0.5F, -0.5F, 0.0F, 1.0F,    1.0F, 1.0F, 1.0F, 1.0F,    1.0f, 0.0F,
            -0.5F, -0.5F, 0.0F, 1.0F,    0.0F, 1.0F, 1.0F, 1.0F,    0.0f, 0.0F,
            -0.5F,  0.5F, 0.0F, 1.0F,    1.0F, 1.0F, 1.0F, 1.0F,    0.0f, 1.0F,
             0.5F,  0.5F, 0.0F, 1.0F,    1.0F, 1.0F, 1.0F, 1.0F,    1.0f, 1.0F,
        };
        vertexBuffer = device.newBuffer(quadVertexData, sizeof(quadVertexData), mtl::ResourceOptions::CPUCacheModeDefaultCache);

        uniformBuffer = device.newBuffer(sizeof(Uniforms), mtl::ResourceOptions::CPUCacheModeDefaultCache);

        const auto bundle = ns::Bundle::mainBundle();
        const auto diffuseTexturePath = bundle.pathForResource("wall_color", "tex");
        const auto normalTexturePath = bundle.pathForResource("wall_n", "tex");

        diffuseTexture = loadTexture(diffuseTexturePath, device);
        normalTexture = loadTexture(normalTexturePath, device);

        mtl::SamplerDescriptor diffuseSamplerDescriptor;
        diffuseSamplerDescriptor.setMinFilter(mtl::SamplerMinMagFilter::Linear);
        diffuseSamplerDescriptor.setMagFilter(mtl::SamplerMinMagFilter::Linear);
        diffuseSamplerDescriptor.setMipFilter(mtl::SamplerMipFilter::Linear);
        diffuseSamplerDescriptor.setSAddressMode(mtl::SamplerAddressMode::ClampToEdge);
        diffuseSamplerDescriptor.setTAddressMode(mtl::SamplerAddressMode::ClampToEdge);
        diffuseSamplerDescriptor.setRAddressMode(mtl::SamplerAddressMode::ClampToEdge);
        diffuseSampler = device.newSamplerState(diffuseSamplerDescriptor);

        mtl::SamplerDescriptor normalSamplerDescriptor;
        normalSamplerDescriptor.setMinFilter(mtl::SamplerMinMagFilter::Linear);
        normalSamplerDescriptor.setMagFilter(mtl::SamplerMinMagFilter::Linear);
        normalSamplerDescriptor.setMipFilter(mtl::SamplerMipFilter::NotMipmapped);
        normalSamplerDescriptor.setSAddressMode(mtl::SamplerAddressMode::ClampToEdge);
        normalSamplerDescriptor.setTAddressMode(mtl::SamplerAddressMode::ClampToEdge);
        normalSamplerDescriptor.setRAddressMode(mtl::SamplerAddressMode::ClampToEdge);
        normalSampler = device.newSamplerState(normalSamplerDescriptor);

        displayLink.setOutputCallback(renderCallback, this);
        displayLink.start();
    }

    void run()
    {
        application.run();
    }

    void windowDidResize()
    {
        std::cout << "Window did resize" << '\n';
    }

    void keyDown(unsigned short keyCode)
    {
        std::cout << "Key down " << keyCode << '\n';
    }

    void keyUp(unsigned short keyCode)
    {
        std::cout << "Key up " << keyCode << '\n';
    }

    void mouseDown(const ns::Point& location)
    {
        std::cout << "Mouse down " << location.x << ' ' << location.y << '\n';
    }

    void mouseUp(const ns::Point& location)
    {
        std::cout << "Mouse up " << location.x << ' ' << location.y << '\n';
    }

    void rightMouseDown(const ns::Point& location)
    {
        std::cout << "Right mouse down " << location.x << ' ' << location.y << '\n';
    }

    void rightMouseUp(const ns::Point& location)
    {
        std::cout << "Right mouse up " << location.x << ' ' << location.y << '\n';
    }

    void otherMouseDown(const ns::Point& location)
    {
        std::cout << "Other mouse down " << location.x << ' ' << location.y << '\n';
    }

    void otherMouseUp(const ns::Point& location)
    {
        std::cout << "Other mouse up " << location.x << ' ' << location.y << '\n';
    }

    void mouseMoved(const ns::Point& location)
    {
        std::cout << "Mouse move " << location.x << ' ' << location.y << '\n';
    }

    void mouseDragged(const ns::Point& location)
    {
        std::cout << "Mouse drag " << location.x << ' ' << location.y << '\n';
    }

    void rightMouseDragged(const ns::Point& location)
    {
        std::cout << "Right mouse drag " << location.x << ' ' << location.y << '\n';
    }

    void otherMouseDragged(const ns::Point& location)
    {
        std::cout << "Other mouse drag " << location.x << ' ' << location.y << '\n';
    }

    void render()
    {
        ns::AutoreleasePool pool;

        auto commandQueue = device.newCommandQueue();
        auto commandBuffer = commandQueue.commandBuffer();

        auto drawable = metalLayer.nextDrawable();

        angle += 0.01F;

        Uniforms uniforms;
        uniforms.projectionMatrix = projectionMatrix();
        uniforms.modelMatrix = rotationMatrix2d(angle);
        auto bufferPointer = uniformBuffer.contents();
        memcpy(bufferPointer, &uniforms, sizeof(Uniforms));

        mtl::RenderPassDescriptor renderPassDescriptor;
        renderPassDescriptor.colorAttachments()[0].setTexture(drawable.texture());
        renderPassDescriptor.colorAttachments()[0].setLoadAction(mtl::LoadAction::Clear);
        renderPassDescriptor.colorAttachments()[0].setClearColor(mtl::ClearColor{1.0, 1.0, 1.0, 1.0});
        renderPassDescriptor.colorAttachments()[0].setStoreAction(mtl::StoreAction::Store);

        auto renderCommand = commandBuffer.renderCommandEncoder(renderPassDescriptor);
        renderCommand.setFragmentTexture(diffuseTexture, 0);
        renderCommand.setFragmentSamplerState(diffuseSampler, 0);
        renderCommand.setFragmentTexture(normalTexture, 1);
        renderCommand.setFragmentSamplerState(normalSampler, 1);
        renderCommand.setRenderPipelineState(pipelineState);
        renderCommand.setVertexBuffer(vertexBuffer, 0, 0);
        renderCommand.setVertexBuffer(uniformBuffer, 0, 1);
        renderCommand.drawIndexedPrimitives(mtl::PrimitiveType::Triangle, 6, mtl::IndexType::UInt16, indexBuffer, 0);
        renderCommand.endEncoding();

        commandBuffer.commit();
        commandBuffer.waitUntilCompleted();

        //commandBuffer.presentDrawable(drawable);
        drawable.present();
    }
private:
    void createMainMenu()
    {
        ns::Menu mainMenu;

        // Apple menu
        auto mainMenuItem = mainMenu.addItem("", nullptr, "");

        ns::Menu applicationMenu;
        mainMenuItem.setSubmenu(applicationMenu);

        const auto mainBundle = ns::Bundle::mainBundle();
        const auto infoDictionary = mainBundle.infoDictionary();

        auto bundleName = infoDictionary.objectForKey<ns::String>("CFBundleDisplayName");
        if (!bundleName)
            bundleName = infoDictionary.objectForKey<ns::String>("CFBundleName");

        applicationMenu.addItem(ns::String{"About "} + bundleName, sel_registerName("orderFrontStandardAboutPanel:"), "");
        applicationMenu.addItem(ns::MenuItem::separatorItem());

        auto servicesItem = applicationMenu.addItem("Services", nullptr, "");

        ns::Menu servicesMenu;
        servicesItem.setSubmenu(servicesMenu);
        application.setServicesMenu(servicesMenu);

        applicationMenu.addItem(ns::MenuItem::separatorItem());
        applicationMenu.addItem(ns::String{"Hide "} + bundleName, sel_registerName("hide:"), "h");

        auto hideOthersItem = applicationMenu.addItem("Hide Others", sel_registerName("hideOtherApplications:"), "h");
        hideOthersItem.setKeyEquivalentModifierMask(ns::EventModifierFlags::Option | ns::EventModifierFlags::Command);

        applicationMenu.addItem("Show All", sel_registerName("unhideAllApplications:"), "");
        applicationMenu.addItem(ns::MenuItem::separatorItem());
        applicationMenu.addItem(ns::String{"Quit "} + bundleName, sel_registerName("terminate:"), "q");

        // View menu
        auto viewItem = mainMenu.addItem("View", nullptr, "");

        ns::Menu viewMenu{"View"};
        viewItem.setSubmenu(viewMenu);

        // Window menu
        auto windowsItem = mainMenu.addItem("Window", nullptr, "");

        ns::Menu windowsMenu{"Window"};
        windowsMenu.addItem("Minimize", sel_registerName("performMiniaturize:"), "m");
        windowsMenu.addItem("Zoom", sel_registerName("performZoom:"), "");

        windowsItem.setSubmenu(windowsMenu);
        application.setWindowsMenu(windowsMenu);

        // Help menu
        auto helpItem = mainMenu.addItem("Help", nullptr, "");

        ns::Menu helpMenu{"Help"};
        helpItem.setSubmenu(helpMenu);
        application.setHelpMenu(helpMenu);

        application.setMainMenu(mainMenu);
    }

    // AppDelegate
    static void applicationWillTerminate(id, SEL, id)
    {
        std::cout << "Application will terminate\n";
    }

    static BOOL applicationShouldTerminateAfterLastWindowClosed(id, SEL, id) noexcept
    {
        return YES;
    }

    // WindowDelegate
    static void windowDidResize(id self, SEL, id)
    {
        ns::Object windowDelegate{self};
        Application* application;
        std::memcpy(&application, windowDelegate.getIndexedIvars(), sizeof(Application*));

        application->windowDidResize();
    }

    // View
    static BOOL isOpaque(id, SEL)
    {
        return YES;
    }

    static BOOL acceptsFirstResponder(id, SEL)
    {
        return YES;
    }

    static BOOL acceptsFirstMouse(id, SEL, [[maybe_unused]] id event)
    {
        return YES;
    }

    static void keyDown(id self, SEL, id e)
    {
        ns::View view{self};
        ns::Event event{e};
        Application* application;
        std::memcpy(&application, view.getIndexedIvars(), sizeof(Application*));
        application->keyDown(event.keyCode());
    }

    static void keyUp(id self, SEL, id e)
    {
        ns::View view{self};
        ns::Event event{e};
        Application* application;
        std::memcpy(&application, view.getIndexedIvars(), sizeof(Application*));
        application->keyUp(event.keyCode());
    }

    static void mouseDown(id self, SEL, id e)
    {
        ns::View view{self};
        ns::Event event{e};
        Application* application;
        std::memcpy(&application, view.getIndexedIvars(), sizeof(Application*));
        const auto location = view.convertToView(event.locationInWindow(), nullptr);
        application->mouseDown(location);
    }

    static void mouseUp(id self, SEL, id e)
    {
        ns::View view{self};
        ns::Event event{e};
        Application* application;
        std::memcpy(&application, view.getIndexedIvars(), sizeof(Application*));
        const auto location = view.convertToView(event.locationInWindow(), nullptr);
        application->mouseUp(location);
    }

    static void rightMouseDown(id self, SEL, id e)
    {
        ns::View view{self};
        ns::Event event{e};
        Application* application;
        std::memcpy(&application, view.getIndexedIvars(), sizeof(Application*));
        const auto location = view.convertToView(event.locationInWindow(), nullptr);
        application->rightMouseDown(location);
    }

    static void rightMouseUp(id self, SEL, id e)
    {
        ns::View view{self};
        ns::Event event{e};
        Application* application;
        std::memcpy(&application, view.getIndexedIvars(), sizeof(Application*));
        const auto location = view.convertToView(event.locationInWindow(), nullptr);
        application->rightMouseUp(location);
    }

    static void otherMouseDown(id self, SEL, id e)
    {
        ns::View view{self};
        ns::Event event{e};
        Application* application;
        std::memcpy(&application, view.getIndexedIvars(), sizeof(Application*));
        const auto location = view.convertToView(event.locationInWindow(), nullptr);
        application->otherMouseDown(location);
    }

    static void otherMouseUp(id self, SEL, id e)
    {
        ns::View view{self};
        ns::Event event{e};
        Application* application;
        std::memcpy(&application, view.getIndexedIvars(), sizeof(Application*));
        const auto location = view.convertToView(event.locationInWindow(), nullptr);
        application->otherMouseUp(location);
    }

    static void mouseMoved(id self, SEL, id e)
    {
        ns::View view{self};
        ns::Event event{e};
        Application* application;
        std::memcpy(&application, view.getIndexedIvars(), sizeof(Application*));
        const auto location = view.convertToView(event.locationInWindow(), nullptr);
        application->mouseMoved(location);
    }

    static void mouseDragged(id self, SEL, id e)
    {
        ns::View view{self};
        ns::Event event{e};
        Application* application;
        std::memcpy(&application, view.getIndexedIvars(), sizeof(Application*));
        const auto location = view.convertToView(event.locationInWindow(), nullptr);
        application->mouseDragged(location);
    }

    static void rightMouseDragged(id self, SEL, id e)
    {
        ns::View view{self};
        ns::Event event{e};
        Application* application;
        std::memcpy(&application, view.getIndexedIvars(), sizeof(Application*));
        const auto location = view.convertToView(event.locationInWindow(), nullptr);
        application->rightMouseDragged(location);
    }

    static void otherMouseDragged(id self, SEL, id e)
    {
        ns::View view{self};
        ns::Event event{e};
        Application* application;
        std::memcpy(&application, view.getIndexedIvars(), sizeof(Application*));
        const auto location = view.convertToView(event.locationInWindow(), nullptr);
        application->otherMouseDragged(location);
    }

    struct Uniforms final
    {
        matrix_float4x4 projectionMatrix;
        matrix_float4x4 modelMatrix;
    };

    objc::Class<ns::Object> appDelegateClass{"AppDelegate", sizeof(Application*)};
    ns::Object appDelegate;
    objc::Class<ns::Object> windowDelegateClass{"WindowDelegate", sizeof(Application*)};
    ns::Object windowDelegate;
    objc::Class<ns::View> viewClass{"View", sizeof(Application*)};

    ca::MetalLayer metalLayer;

    ns::Application application = ns::Application::sharedApplication();
    ns::Screen screen = ns::Screen::mainScreen();
    mtl::Device device = mtl::Device::createSystemDefaultDevice();
    cv::DisplayLink displayLink{screen.deviceDescription().objectForKey<ns::Number>("NSScreenNumber").unsignedIntValue()};

    float angle = 0.0F;

    mtl::RenderPipelineState pipelineState = nullptr;

    mtl::Buffer indexBuffer = nullptr;
    mtl::Buffer vertexBuffer = nullptr;
    mtl::Buffer uniformBuffer = nullptr;

    mtl::Texture diffuseTexture = nullptr;
    mtl::Texture normalTexture = nullptr;

    mtl::SamplerState diffuseSampler = nullptr;
    mtl::SamplerState normalSampler = nullptr;
};

namespace
{
    CVReturn renderCallback(CVDisplayLinkRef,
                            const CVTimeStamp*,
                            const CVTimeStamp*,
                            CVOptionFlags,
                            CVOptionFlags*,
                            void* userInfo)
    {
        auto application = static_cast<Application*>(userInfo);
        application->render();
        return kCVReturnSuccess;
    }
}

int main(int argc, const char* argv[])
{
    ns::AutoreleasePool autoreleasePool;

    try
    {
        Application application;
        application.run();
    }
    catch(const std::exception& exception)
    {
        std::cerr << exception.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
