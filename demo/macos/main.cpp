#include <iostream>
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
#include "metal/Metal.hpp"
#include "objc/Class.hpp"
#include "quartzcore/MetalLayer.hpp"

struct Uniforms
{
    matrix_float4x4 rotation_matrix;
};

static matrix_float4x4 rotationMatrix2d(const float radians)
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
"    float4x4 rotation_matrix;\n" \
"} Uniforms;\n" \

"typedef struct\n" \
"{\n" \
"    float4 position;\n" \
"    float4 color;\n" \
"} VertexIn;\n" \

"typedef struct {\n" \
"    float4 position [[position]];\n" \
"    half4  color;\n" \
"} VertexOut;\n" \

"vertex VertexOut vertex_function(const device VertexIn *vertices [[buffer(0)]],\n" \
"                                 constant Uniforms &uniforms [[buffer(1)]],\n" \
"                                 uint vid [[vertex_id]])\n" \
"{\n" \
"    VertexOut out;\n" \
"    out.position = uniforms.rotation_matrix * vertices[vid].position;\n" \
"    out.color = half4(vertices[vid].color);\n" \
"    return out;\n" \
"}\n" \

"fragment half4 fragment_function(VertexOut in [[stage_in]])\n" \
"{\n" \
"    return in.color;\n" \
"}";

class Application final
{
public:
    Application()
    {
        appDelegateClass.addMethod(sel_registerName("applicationWillTerminate:"),
                                   applicationWillTerminate,
                                   "v@:@");
        appDelegateClass.addMethod(sel_registerName("applicationShouldTerminateAfterLastWindowClosed:"),
                                   applicationShouldTerminateAfterLastWindowClosed,
                                   "b@:@");
        appDelegateClass.reg();
        appDelegate = appDelegateClass.createInstance();

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
        window.setTitle("demo");
        window.setCollectionBehavior(ns::WindowCollectionBehavior::FullScreenPrimary);

        window.setTabbingMode(ns::WindowTabbingMode::Disallowed);
        window.setAcceptsMouseMovedEvents(true);

        windowDelegateClass.addMethod(sel_registerName("windowDidResize:"), windowDidResize, "v@:@");
        windowDelegateClass.reg();
        windowDelegate = windowDelegateClass.createInstance();
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
        view.setAutoresizingMask(ns::AutoresizingMaskOptions::WidthSizable | ns::AutoresizingMaskOptions::HeightSizable);
        view.setWantsLayer(true);

        cg::ColorSpace colorSpace = cg::ColorSpace::deviceRGB();
        const cg::Float bgColor[] = {0.0, 0.0, 0.0, 0.0};
        cg::Color backgroundColor{colorSpace, bgColor};

        ca::MetalLayer metalLayer;
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
        vertexLayout0.setStride(32);
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

        mtl::RenderPipelineDescriptor renderPipelineDescriptor;
        renderPipelineDescriptor.setLabel("renderPipeline");
        renderPipelineDescriptor.setVertexFunction(vertexFunction);
        renderPipelineDescriptor.setFragmentFunction(fragmentFunction);
        renderPipelineDescriptor.setVertexDescriptor(vertexDescriptor);
        //renderPipelineDescriptor.setDepthAttachmentPixelFormat(mtl::PixelFormat::Depth24Unorm_Stencil8);
        //renderPipelineDescriptor.setStencilAttachmentPixelFormat(mtl::PixelFormat::Depth24Unorm_Stencil8);

        const auto colorAttachments = renderPipelineDescriptor.colorAttachments();
        colorAttachments[0].setPixelFormat(mtl::PixelFormat::BGRA8Unorm);

        auto pipelineState = device.newRenderPipelineState(renderPipelineDescriptor);

        static std::uint16_t indexData[] = { 0, 1, 2, 3, 0, 2 };
        const auto indexBuffer = device.newBuffer(indexData, sizeof(indexData), mtl::ResourceOptions::CPUCacheModeDefaultCache);

        static float quadVertexData[] = {
             0.5, -0.5, 0.0, 1.0,     1.0, 0.0, 0.0, 1.0,
            -0.5, -0.5, 0.0, 1.0,     0.0, 1.0, 0.0, 1.0,
            -0.5,  0.5, 0.0, 1.0,     0.0, 0.0, 1.0, 1.0,
             0.5,  0.5, 0.0, 1.0,     1.0, 1.0, 0.0, 1.0,
        };

        const auto vertexBuffer = device.newBuffer(quadVertexData, sizeof(quadVertexData), mtl::ResourceOptions::CPUCacheModeDefaultCache);

        auto uniformBuffer = device.newBuffer(sizeof(Uniforms), mtl::ResourceOptions::CPUCacheModeDefaultCache);
        Uniforms uniforms;
        uniforms.rotation_matrix = rotationMatrix2d(static_cast<float>(M_PI_4));
        auto bufferPointer = uniformBuffer.contents();
        memcpy(bufferPointer, &uniforms, sizeof(Uniforms));

        auto drawable = metalLayer.nextDrawable();

        mtl::RenderPassDescriptor renderPassDescriptor;
        renderPassDescriptor.colorAttachments()[0].setTexture(drawable.texture());
        renderPassDescriptor.colorAttachments()[0].setLoadAction(mtl::LoadAction::Clear);
        renderPassDescriptor.colorAttachments()[0].setClearColor(mtl::ClearColor{1.0, 1.0, 1.0, 1.0});
        renderPassDescriptor.colorAttachments()[0].setStoreAction(mtl::StoreAction::Store);

        auto commandQueue = device.newCommandQueue();
        auto commandBuffer = commandQueue.commandBuffer();

        auto renderCommand = commandBuffer.renderCommandEncoder(renderPassDescriptor);
        renderCommand.setRenderPipelineState(pipelineState);
        renderCommand.setVertexBuffer(vertexBuffer, 0, 0);
        renderCommand.setVertexBuffer(uniformBuffer, 0, 1);
        renderCommand.drawIndexedPrimitives(mtl::PrimitiveType::Triangle, 6, mtl::IndexType::UInt16, indexBuffer, 0);
        renderCommand.endEncoding();

        commandBuffer.commit();
        commandBuffer.waitUntilCompleted();

        //commandBuffer.presentDrawable(drawable);
        drawable.present();

//        CGDirectDisplayID displayId = [[[screen deviceDescription] objectForKey:@"NSScreenNumber"] unsignedIntValue];
//        CVDisplayLinkRef displayLink = NULL;
//        const CVReturn createResult = CVDisplayLinkCreateWithCGDisplay(displayId, &displayLink);
//        if (createResult != kCVReturnSuccess) return 1;
//
//        CVReturn setOutputCallbackResult = CVDisplayLinkSetOutputCallback(displayLink, renderCallback, NULL);
//        if (setOutputCallbackResult != kCVReturnSuccess)
//            return 1;
//
//        CVReturn startResult = CVDisplayLinkStart(displayLink);
//        if (startResult != kCVReturnSuccess)
//            return 1;
    }

    void run()
    {
        application.run();

//        CVDisplayLinkRelease(displayLink);
    }

    void render()
    {

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
    static void windowDidResize(id, SEL, id notification)
    {
        std::cout << "Window did resize " << notification << '\n';
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
        ns::View view{objc::sendMessage<id>(self, ns::Object::METALPP_SEL(retain))};
        ns::Event event{objc::sendMessage<id>(e, ns::Object::METALPP_SEL(retain))};
        std::cout << "Key down " << event.keyCode() << '\n';
    }

    static void keyUp(id self, SEL, id e)
    {
        ns::View view{objc::sendMessage<id>(self, ns::Object::METALPP_SEL(retain))};
        ns::Event event{objc::sendMessage<id>(e, ns::Object::METALPP_SEL(retain))};
        std::cout << "Key up " << event.keyCode() << '\n';
    }

    static void mouseDown(id self, SEL, id e)
    {
        ns::View view{objc::sendMessage<id>(self, ns::Object::METALPP_SEL(retain))};
        ns::Event event{objc::sendMessage<id>(e, ns::Object::METALPP_SEL(retain))};
        const auto location = view.convertToView(event.locationInWindow(), nullptr);
        std::cout << "Mouse down " << location.x << ' ' << location.y << '\n';
    }

    static void mouseUp(id self, SEL, id e)
    {
        ns::View view{objc::sendMessage<id>(self, ns::Object::METALPP_SEL(retain))};
        ns::Event event{objc::sendMessage<id>(e, ns::Object::METALPP_SEL(retain))};
        const auto location = view.convertToView(event.locationInWindow(), nullptr);
        std::cout << "Mouse up " << location.x << ' ' << location.y << '\n';
    }

    static void rightMouseDown(id self, SEL, id e)
    {
        ns::View view{objc::sendMessage<id>(self, ns::Object::METALPP_SEL(retain))};
        ns::Event event{objc::sendMessage<id>(e, ns::Object::METALPP_SEL(retain))};
        const auto location = view.convertToView(event.locationInWindow(), nullptr);
        std::cout << "Right mouse down " << location.x << ' ' << location.y << '\n';
    }

    static void rightMouseUp(id self, SEL, id e)
    {
        ns::View view{objc::sendMessage<id>(self, ns::Object::METALPP_SEL(retain))};
        ns::Event event{objc::sendMessage<id>(e, ns::Object::METALPP_SEL(retain))};
        const auto location = view.convertToView(event.locationInWindow(), nullptr);
        std::cout << "Right mouse up " << location.x << ' ' << location.y << '\n';
    }

    static void otherMouseDown(id self, SEL, id e)
    {
        ns::View view{objc::sendMessage<id>(self, ns::Object::METALPP_SEL(retain))};
        ns::Event event{objc::sendMessage<id>(e, ns::Object::METALPP_SEL(retain))};
        const auto location = view.convertToView(event.locationInWindow(), nullptr);
        std::cout << "Other mouse down " << location.x << ' ' << location.y << '\n';
    }

    static void otherMouseUp(id self, SEL, id e)
    {
        ns::View view{objc::sendMessage<id>(self, ns::Object::METALPP_SEL(retain))};
        ns::Event event{objc::sendMessage<id>(e, ns::Object::METALPP_SEL(retain))};
        const auto location = view.convertToView(event.locationInWindow(), nullptr);
        std::cout << "Other mouse up " << location.x << ' ' << location.y << '\n';
    }

    static void mouseMoved(id self, SEL, id e)
    {
        ns::View view{objc::sendMessage<id>(self, ns::Object::METALPP_SEL(retain))};
        ns::Event event{objc::sendMessage<id>(e, ns::Object::METALPP_SEL(retain))};
        const auto location = view.convertToView(event.locationInWindow(), nullptr);
        std::cout << "Mouse move " << location.x << ' ' << location.y << '\n';
    }

    static void mouseDragged(id self, SEL, id e)
    {
        ns::View view{objc::sendMessage<id>(self, ns::Object::METALPP_SEL(retain))};
        ns::Event event{objc::sendMessage<id>(e, ns::Object::METALPP_SEL(retain))};
        const auto location = view.convertToView(event.locationInWindow(), nullptr);
        std::cout << "Mouse drag " << location.x << ' ' << location.y << '\n';
    }

    static void rightMouseDragged(id self, SEL, id e)
    {
        ns::View view{objc::sendMessage<id>(self, ns::Object::METALPP_SEL(retain))};
        ns::Event event{objc::sendMessage<id>(e, ns::Object::METALPP_SEL(retain))};
        const auto location = view.convertToView(event.locationInWindow(), nullptr);
        std::cout << "Right mouse drag " << location.x << ' ' << location.y << '\n';
    }

    static void otherMouseDragged(id self, SEL, id e)
    {
        ns::View view{objc::sendMessage<id>(self, ns::Object::METALPP_SEL(retain))};
        ns::Event event{objc::sendMessage<id>(e, ns::Object::METALPP_SEL(retain))};
        const auto location = view.convertToView(event.locationInWindow(), nullptr);
        std::cout << "Other mouse drag " << location.x << ' ' << location.y << '\n';
    }

    objc::Class<ns::Object> appDelegateClass{"AppDelegate"};
    ns::Object appDelegate;
    objc::Class<ns::Object> windowDelegateClass{"WindowDelegate"};
    ns::Object windowDelegate;
    objc::Class<ns::View> viewClass{"View"};

    ns::Application application = ns::Application::sharedApplication();
    ns::Screen screen = ns::Screen::mainScreen();
    mtl::Device device = mtl::Device::createSystemDefaultDevice();
    //cv::DisplayLink displayLink;
};

//static CVReturn renderCallback(CVDisplayLinkRef,
//                               const CVTimeStamp*,
//                               const CVTimeStamp*,
//                               CVOptionFlags,
//                               CVOptionFlags*,
//                               void* userInfo)
//{
//    return kCVReturnSuccess;
//}

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
