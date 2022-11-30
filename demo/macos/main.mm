#include <iostream>
#import <Cocoa/Cocoa.h>
#import <QuartzCore/CAMetalLayer.h>
#include <simd/simd.h>
#include "appkit/Application.hpp"
#include "appkit/Menu.hpp"
#include "appkit/Screen.hpp"
#include "foundation/AutoreleasePool.hpp"
#include "metal/Metal.hpp"
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

@interface WindowDelegate: NSObject<NSWindowDelegate>
{
}

@end

@implementation WindowDelegate

-(void)windowDidResize:(__unused NSNotification*)notification
{
    std::cout << "Window did resize\n";
}

@end

@interface View : NSView

@end

@implementation View

- (id)initWithFrame:(NSRect)frameRect
{
    if (self = [super initWithFrame:frameRect])
    {
        [self setAutoresizingMask:NSViewWidthSizable | NSViewHeightSizable];
        [self setWantsLayer:YES];

        ca::MetalLayer metalLayer;

        const CGFloat bgColor[] = {0.0, 0.0, 0.0, 0.0};
        CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
        CGColorRef backgroundColor = CGColorCreate(colorSpace, bgColor);

        metalLayer.setEdgeAntialiasingMask(ca::EdgeAntialiasingMask::None);
        metalLayer.setMasksToBounds(true);
        //metalLayer.setBackgroundColor(backgroundColor);
        metalLayer.setPresentsWithTransaction(false);
        metalLayer.setAnchorPoint(cg::Point(0.5, 0.5));
        metalLayer.setFrame(cg::Rect{cg::Point{frameRect.origin.x, frameRect.origin.y}, cg::Size{frameRect.size.width, frameRect.size.height}});
        metalLayer.setMagnificationFilter(ca::filterNearest);
        metalLayer.setMinificationFilter(ca::filterNearest);
        metalLayer.setFramebufferOnly(false);
        metalLayer.setPixelFormat(mtl::PixelFormat::BGRA8Unorm);

        [self setLayer:metalLayer];

        CGColorRelease(backgroundColor);
        CGColorSpaceRelease(colorSpace);
    }

    return self;
}

- (BOOL)isOpaque
{
    return YES;
}

- (BOOL)mouseDownCanMoveWindow
{
    return YES;
}

- (BOOL)acceptsFirstResponder
{
    return YES;
}

- (BOOL)acceptsFirstMouse:(__unused NSEvent*)event
{
    return YES;
}

- (void)keyDown:(NSEvent*)event
{
    //std::cout << "Key down " << event.keyCode << '\n';
}

- (void)keyUp:(NSEvent*)event
{
    //std::cout << "Key up " << event.keyCode << '\n';
}

- (void)mouseDown:(NSEvent*)event
{
//    const NSPoint location = [self convertPoint:event.locationInWindow fromView: nil];
//    std::cout << "Mouse down " << location.x << ' ' << location.y << '\n';
}

- (void)mouseUp:(NSEvent*)event
{
//    const NSPoint location = [self convertPoint:event.locationInWindow fromView: nil];
//    std::cout << "Mouse up " << location.x << ' ' << location.y << '\n';
}

- (void)mouseMoved:(NSEvent*)event
{
//    const NSPoint location = [self convertPoint:event.locationInWindow fromView: nil];
//    std::cout << "Mouse move " << location.x << ' ' << location.y << '\n';
}

- (void)mouseDragged:(NSEvent*)event
{
//    const NSPoint location = [self convertPoint:event.locationInWindow fromView: nil];
//    std::cout << "Mouse drag " << location.x << ' ' << location.y << '\n';
}

@end

static void createMainMenu(NSApplication* sharedApplication)
{
    ns::Menu mainMenu;

    // Apple menu
    auto mainMenuItem = mainMenu.addItem("", nullptr, "");

    ns::Menu applicationMenu;
    mainMenuItem.setSubmenu(applicationMenu);

    NSString* bundleName = NSBundle.mainBundle.infoDictionary[@"CFBundleDisplayName"];
    if (!bundleName)
        bundleName = NSBundle.mainBundle.infoDictionary[@"CFBundleName"];

    [applicationMenu addItemWithTitle:[NSString stringWithFormat:@"%@ %@", NSLocalizedString(@"About", nil), bundleName]
                               action:@selector(orderFrontStandardAboutPanel:)
                        keyEquivalent:@""];

    applicationMenu.addItem(ns::MenuItem::separatorItem());

    auto servicesItem = applicationMenu.addItem("Services", nil, "");

    ns::Menu servicesMenu;
    servicesItem.setSubmenu(servicesMenu);
    sharedApplication.servicesMenu = servicesMenu;

    applicationMenu.addItem(ns::MenuItem::separatorItem());

    [applicationMenu addItemWithTitle:[NSString stringWithFormat:@"%@ %@", NSLocalizedString(@"Hide", nil), bundleName]
                               action:@selector(hide:)
                        keyEquivalent:@"h"];

    NSMenuItem* hideOthersItem = [applicationMenu addItemWithTitle:NSLocalizedString(@"Hide Others", nil)
                                                            action:@selector(hideOtherApplications:)
                                                     keyEquivalent:@"h"];
    hideOthersItem.keyEquivalentModifierMask = NSEventModifierFlagOption | NSEventModifierFlagCommand;

    applicationMenu.addItem("Show All", @selector(unhideAllApplications:), "");
    applicationMenu.addItem(ns::MenuItem::separatorItem());

    [applicationMenu addItemWithTitle:[NSString stringWithFormat:@"%@ %@", NSLocalizedString(@"Quit", nil), bundleName]
                               action:@selector(terminate:)
                        keyEquivalent:@"q"];

    // View menu
    auto viewItem = mainMenu.addItem("View", nullptr, "");

    ns::Menu viewMenu{"View"};
    viewItem.setSubmenu(viewMenu);

    // Window menu
    auto windowsItem = mainMenu.addItem("Window", nullptr, "");

    ns::Menu windowsMenu{"Window"};
    windowsMenu.addItem("Minimize", @selector(performMiniaturize:), "m");
    windowsMenu.addItem("Zoom", @selector(performZoom:), "");

    windowsItem.setSubmenu(windowsMenu);
    sharedApplication.windowsMenu = windowsMenu;

    // Help menu
    auto helpItem = mainMenu.addItem("Help", nullptr, "");

    ns::Menu helpMenu{"Help"};
    helpItem.setSubmenu(helpMenu);
    sharedApplication.helpMenu = helpMenu;

    sharedApplication.mainMenu = mainMenu;
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

class AppDelegate: public ns::ApplicationDelegate
{
public:
    virtual void applicationDidFinishLaunching([[maybe_unused]] id notification) override
    {
        NSLog(@"applicationDidFinishLaunching");
    }
};

class App
{
public:
    App()
    {
        application.activateIgnoringOtherApps(true);
        application.setDelegate(appDelegate);
        createMainMenu(application);

        const NSWindowStyleMask windowStyleMask = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable;

        const auto screenFrame = screen.frame();

        const CGSize windowSize = CGSizeMake(std::round(screenFrame.size.width * 0.6),
                                             std::round(screenFrame.size.height * 0.6));

        const NSRect frame = NSMakeRect(std::round(screenFrame.size.width / 2.0F - windowSize.width / 2.0F),
                                        std::round(screenFrame.size.height / 2.0F - windowSize.height / 2.0F),
                                        windowSize.width, windowSize.height);

        NSWindow* window  = [[NSWindow alloc] initWithContentRect:frame
                                                        styleMask:windowStyleMask
                                                          backing:NSBackingStoreBuffered
                                                            defer:NO
                                                           screen:screen];

        [window setReleasedWhenClosed:NO];
        [window setTabbingMode:NSWindowTabbingModeDisallowed];

        [window setAcceptsMouseMovedEvents:YES];

        WindowDelegate* windowDelegate = [[WindowDelegate alloc] init];
        [window setDelegate:windowDelegate];

        [window setCollectionBehavior:NSWindowCollectionBehaviorFullScreenPrimary];
        [window setTitle:@"demo"];

        NSView* view = [[[View alloc] init] autorelease];

        [window setContentView:view];
        [window makeKeyAndOrderFront:nil];

        ca::MetalLayer metalLayer{[view.layer retain]};
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
    //    renderPipelineDescriptor.setDepthAttachmentPixelFormat(mtl::PixelFormat::Depth24Unorm_Stencil8);
    //    renderPipelineDescriptor.setStencilAttachmentPixelFormat(mtl::PixelFormat::Depth24Unorm_Stencil8);

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
        void *bufferPointer = uniformBuffer.contents();
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

        //commandBuffer.presentDrawable(drawable);

        commandBuffer.commit();
        commandBuffer.waitUntilCompleted();

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
//        [window release];
//        [windowDelegate release];
    }

    void render()
    {

    }
private:
    AppDelegate appDelegate;
    ns::Application application = ns::Application::sharedApplication();
    ns::Screen screen = ns::Screen::mainScreen();
    mtl::Device device = mtl::Device::createSystemDefaultDevice();
};

static CVReturn renderCallback(CVDisplayLinkRef,
                               const CVTimeStamp*,
                               const CVTimeStamp*,
                               CVOptionFlags,
                               CVOptionFlags*,
                               void* userInfo)
{
    return kCVReturnSuccess;
}

int main(int argc, const char* argv[])
{
    ns::AutoreleasePool autoreleasePool;

    try
    {
        App app;
        app.run();
    }
    catch(const std::exception& exception)
    {
        std::cerr << exception.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
