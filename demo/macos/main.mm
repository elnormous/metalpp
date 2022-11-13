#import <Cocoa/Cocoa.h>
#import <QuartzCore/CAMetalLayer.h>
#include "AppDelegate.h"
#include "foundation/AutoreleasePool.hpp"
#include "metal/Metal.hpp"

@interface WindowDelegate: NSObject<NSWindowDelegate>
{
}

@end

@implementation WindowDelegate

-(void)windowDidResize:(__unused NSNotification*)notification
{
    NSLog(@"Window did resize");
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

        CAMetalLayer* metalLayer = [[[CAMetalLayer alloc] init] autorelease];

        const CGFloat bgColor[] = {0.0, 0.0, 0.0, 0.0};
        CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
        CGColorRef backgroundColor = CGColorCreate(colorSpace, bgColor);

        metalLayer.edgeAntialiasingMask = 0;
        metalLayer.masksToBounds = YES;
        metalLayer.backgroundColor = backgroundColor;
        metalLayer.presentsWithTransaction = NO;
        metalLayer.anchorPoint = CGPointMake(0.5, 0.5);
        metalLayer.frame = frameRect;
        metalLayer.magnificationFilter = kCAFilterNearest;
        metalLayer.minificationFilter = kCAFilterNearest;
        metalLayer.framebufferOnly = NO;
        metalLayer.pixelFormat = MTLPixelFormatBGRA8Unorm;

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
    //NSLog(@"Key down %d", event.keyCode);
}

- (void)keyUp:(NSEvent*)event
{
    //NSLog(@"Key up %d", event.keyCode);
}

- (void)mouseDown:(NSEvent*)event
{
    //const NSPoint location = [self convertPoint:event.locationInWindow fromView: nil];
    //NSLog(@"Mouse down %f, %f", location.x, location.y);
}

- (void)mouseUp:(NSEvent*)event
{
    //const NSPoint location = [self convertPoint:event.locationInWindow fromView: nil];
    //NSLog(@"Mouse up %f, %f", location.x, location.y);
}

- (void)mouseMoved:(NSEvent*)event
{
    //const NSPoint location = [self convertPoint:event.locationInWindow fromView: nil];
    //NSLog(@"Mouse moved %f, %f", location.x, location.y);
}

- (void)mouseDragged:(NSEvent*)event
{
    //const NSPoint location = [self convertPoint:event.locationInWindow fromView: nil];
    //NSLog(@"Mouse dragged %f, %f", location.x, location.y);
}

@end

static void createMainMenu(NSApplication* sharedApplication)
{
    NSMenu* mainMenu = [[[NSMenu alloc] init] autorelease];
    // Apple menu
    NSMenuItem* mainMenuItem = [mainMenu addItemWithTitle:@""
                                                   action:nil
                                            keyEquivalent:@""];

    NSMenu* applicationMenu = [[[NSMenu alloc] init] autorelease];
    mainMenuItem.submenu = applicationMenu;

    NSString* bundleName = NSBundle.mainBundle.infoDictionary[@"CFBundleDisplayName"];
    if (!bundleName)
        bundleName = NSBundle.mainBundle.infoDictionary[@"CFBundleName"];

    [applicationMenu addItemWithTitle:[NSString stringWithFormat:@"%@ %@", NSLocalizedString(@"About", nil), bundleName]
                               action:@selector(orderFrontStandardAboutPanel:)
                        keyEquivalent:@""];

    [applicationMenu addItem:[NSMenuItem separatorItem]];

    NSMenuItem* servicesItem = [applicationMenu addItemWithTitle:NSLocalizedString(@"Services", nil)
                                                          action:nil
                                                   keyEquivalent:@""];

    NSMenu* servicesMenu = [[[NSMenu alloc] init] autorelease];
    servicesItem.submenu = servicesMenu;
    sharedApplication.servicesMenu = servicesMenu;

    [applicationMenu addItem:[NSMenuItem separatorItem]];

    [applicationMenu addItemWithTitle:[NSString stringWithFormat:@"%@ %@", NSLocalizedString(@"Hide", nil), bundleName]
                               action:@selector(hide:)
                        keyEquivalent:@"h"];

    NSMenuItem* hideOthersItem = [applicationMenu addItemWithTitle:NSLocalizedString(@"Hide Others", nil)
                                                            action:@selector(hideOtherApplications:)
                                                     keyEquivalent:@"h"];
    hideOthersItem.keyEquivalentModifierMask = NSEventModifierFlagOption | NSEventModifierFlagCommand;

    [applicationMenu addItemWithTitle:NSLocalizedString(@"Show All", nil)
                               action:@selector(unhideAllApplications:)
                        keyEquivalent:@""];

    [applicationMenu addItem:[NSMenuItem separatorItem]];

    [applicationMenu addItemWithTitle:[NSString stringWithFormat:@"%@ %@", NSLocalizedString(@"Quit", nil), bundleName]
                               action:@selector(terminate:)
                        keyEquivalent:@"q"];

    // View menu
    NSMenuItem* viewItem = [mainMenu addItemWithTitle:NSLocalizedString(@"View", nil)
                                               action:nil
                                        keyEquivalent:@""];

    NSMenu* viewMenu = [[[NSMenu alloc] initWithTitle:NSLocalizedString(@"View", nil)] autorelease];
    viewItem.submenu = viewMenu;

    // Window menu
    NSMenuItem* windowsItem = [mainMenu addItemWithTitle:NSLocalizedString(@"Window", nil)
                                                  action:nil
                                           keyEquivalent:@""];

    NSMenu* windowsMenu = [[[NSMenu alloc] initWithTitle:NSLocalizedString(@"Window", nil)] autorelease];
    [windowsMenu addItemWithTitle:NSLocalizedString(@"Minimize", nil) action:@selector(performMiniaturize:) keyEquivalent:@"m"];
    [windowsMenu addItemWithTitle:NSLocalizedString(@"Zoom", nil) action:@selector(performZoom:) keyEquivalent:@""];

    windowsItem.submenu = windowsMenu;
    sharedApplication.windowsMenu = windowsMenu;

    // Help menu
    NSMenuItem* helpItem = [mainMenu addItemWithTitle:NSLocalizedString(@"Help", nil)
                                               action:nil
                                        keyEquivalent:@""];

    NSMenu* helpMenu = [[[NSMenu alloc] initWithTitle:NSLocalizedString(@"Help", nil)] autorelease];
    helpItem.submenu = helpMenu;
    sharedApplication.helpMenu = helpMenu;

    sharedApplication.mainMenu = mainMenu;
}

static CVReturn renderCallback(CVDisplayLinkRef,
                               const CVTimeStamp*,
                               const CVTimeStamp*,
                               CVOptionFlags,
                               CVOptionFlags*,
                               void* userInfo)
{
    return kCVReturnSuccess;
}

static const char* fragmentShader =
"#include <metal_stdlib>\n" \
"#include <simd/simd.h>\n" \

"using namespace metal;\n" \

"typedef struct\n" \
"{\n" \
"    float4 color;\n" \
"} uniforms_t;\n" \

"typedef struct\n" \
"{\n" \
"    float4 position [[position]];\n" \
"    half4 color;\n" \
"} VS2PS;\n" \

"fragment half4 mainPS(VS2PS input [[stage_in]],\n" \
"                      constant uniforms_t& uniforms [[buffer(1)]])\n" \
"{\n" \
"    return input.color * half4(uniforms.color);\n" \
"}";

static const char* vertexShader =
"#include <simd/simd.h>\n"

"using namespace metal;\n"

"typedef struct\n"
"{\n"
"    float4x4 modelViewProj;\n"
"} uniforms_t;\n"

"typedef struct\n"
"{\n"
"    float3 position [[attribute(0)]];\n"
"    half4 color [[attribute(1)]];\n"
"} VSInput;\n"

"typedef struct\n"
"{\n"
"    float4 position [[position]];\n"
"    half4 color;\n"
"} VS2PS;\n"

"vertex VS2PS mainVS(VSInput input [[stage_in]],\n"
"                    constant uniforms_t& uniforms [[buffer(1)]])\n"
"{\n"
"    VS2PS output;\n"
"    output.position = uniforms.modelViewProj * float4(input.position, ONE);\n"
"    output.color = input.color;\n"
"    return output;\n"
"}";

int main(int argc, const char* argv[]) {
    ns::AutoreleasePool autoreleasePool;

    NSApplication* sharedApplication = [NSApplication sharedApplication];
    [sharedApplication activateIgnoringOtherApps:YES];
    [sharedApplication setDelegate:[[[AppDelegate alloc] init] autorelease]];
    createMainMenu(sharedApplication);

    const NSWindowStyleMask windowStyleMask = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable;

    NSScreen* screen = [NSScreen mainScreen];
    NSLog(@"Screen: %lu\n", screen.retainCount);

    const CGSize windowSize = CGSizeMake(round(screen.frame.size.width * 0.6),
                                         round(screen.frame.size.height * 0.6));

    const NSRect frame = NSMakeRect(round(screen.frame.size.width / 2.0F - windowSize.width / 2.0F),
                                    round(screen.frame.size.height / 2.0F - windowSize.height / 2.0F),
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

    CAMetalLayer* metalLayer = (CAMetalLayer*)view.layer;

    mtl::Device device;
    {
        ns::String name = device.name();
        NSLog(@"Device name: %s, %lu\n", name.cString(), name.retainCount());
    }

    mtl::Library library = device.newDefaultLibrary();
    NSLog(@"Default library: %p, %lu\n", (id)library, library.retainCount());

    NSString* nsstr = [[NSString alloc] initWithCString:"test" encoding:NSASCIIStringEncoding];
    NSLog(@"NSString: %s (%lu), %c, %lu\n", [nsstr cStringUsingEncoding:NSASCIIStringEncoding], nsstr.length, (char)[nsstr characterAtIndex:1], (unsigned long)nsstr.retainCount);

    ns::String str{"test"};
    NSLog(@"String: %s (%lu), %c, %lu\n", str.cString(), str.length(), str[1], str.retainCount());

    str = ns::String{"test1"};
    NSLog(@"String: %s (%lu), %c, %lu\n", str.cString(), str.length(), str[1], str.retainCount());

    mtl::RenderPipelineDescriptor renderPipelineDescriptor;
    renderPipelineDescriptor.setLabel("renderPipeline");
    NSLog(@"Render pipeline descriptor: %p, %lu\n", (id)renderPipelineDescriptor, renderPipelineDescriptor.retainCount());

    ns::Object obj1;
    NSLog(@"Object 1: %lu\n", obj1.retainCount());
    ns::Object obj2;
    NSLog(@"Object 2: %lu\n", obj2.retainCount());

    ns::Array<ns::Object> array{obj1, obj2};
    NSLog(@"Array: %p (%lu), %lu\n", (id)array, array.count(), array.retainCount());
    NSLog(@"Object 1: %lu\n", obj1.retainCount());
    NSLog(@"Object 2: %lu\n", obj2.retainCount());

//    ns::String invalidString = array.objectAtIndexedSubscript(10);
//    NSLog(@"Invalid string: %p\n", (id)invalidString);

    try
    {
        mtl::CompileOptions options;
        NSLog(@"Compile options: %p, %lu\n", (id)options, options.retainCount());
        options.setLanguageVersion(mtl::LanguageVersion::Version1_1);
        options.setFastMathEnabled(true);

        const ns::Dictionary<ns::String, ns::Object> preprocessorMacros{ns::String{"1.0"}, ns::String{"ONE"}};
        NSLog(@"Preprocessor Macros: %p (%lu), %lu\n", (id)preprocessorMacros, preprocessorMacros.count(), preprocessorMacros.retainCount());
        NSLog(@"ONE: %p\n", static_cast<id>(preprocessorMacros["ONE"]));
        const ns::Array<ns::String> keys = preprocessorMacros.allKeys();
        NSLog(@"Key 0: %s\n", keys[0].cString());
        const ns::Array<ns::Object> values = preprocessorMacros.allValues();
        NSLog(@"Value 0: %p\n", static_cast<id>(values[0]));
        const ns::Array<ns::String> keysForObject = preprocessorMacros.allKeysForObject(values[0]);
        NSLog(@"Key 0 for object: %s\n", keysForObject[0].cString());
        options.setPreprocessorMacros(preprocessorMacros);

        mtl::Library vertexLibrary = device.newLibraryWithSource(ns::String{vertexShader}, options);
        NSLog(@"Vertex library: %p, %lu\n", (id)vertexLibrary, vertexLibrary.retainCount());
        vertexLibrary.setLabel("Vertex library");
        NSLog(@"%s\n", vertexLibrary.label().cString());

        mtl::Function vertexFunction = vertexLibrary.newFunctionWithName(ns::String{"mainVS"});
        renderPipelineDescriptor.setVertexFunction(vertexFunction);

        mtl::Library fragmentLibrary = device.newLibraryWithSource(ns::String{fragmentShader});
        NSLog(@"Fragment library: %p, %lu\n", (id)fragmentLibrary, fragmentLibrary.retainCount());
        fragmentLibrary.setLabel("Fragment library");
        NSLog(@"%s\n", fragmentLibrary.label().cString());

        mtl::Function fragmentFunction = fragmentLibrary.newFunctionWithName(ns::String{"mainPS"});
        renderPipelineDescriptor.setFragmentFunction(fragmentFunction);

        mtl::VertexDescriptor vertexDescriptor;

        mtl::VertexBufferLayoutDescriptorArray vertexLayouts = vertexDescriptor.layouts();
        NSLog(@"Vertex layouts: %p, %lu\n", (id)vertexLayouts, vertexLayouts.retainCount());

        mtl::VertexBufferLayoutDescriptor vertexLayout0 = vertexLayouts[0];
        NSLog(@"Vertex layout 0: %p, %lu\n", (id)vertexLayout0, vertexLayout0.retainCount());
        vertexLayout0.setStride(44);
        vertexLayout0.setStepRate(1);
        vertexLayout0.setStepFunction(mtl::VertexStepFunction::PerVertex);

        mtl::VertexAttributeDescriptorArray vertexAttributes = vertexDescriptor.attributes();
        NSLog(@"Vertex attributes: %p, %lu\n", (id)vertexAttributes, vertexAttributes.retainCount());

        // position
        mtl::VertexAttributeDescriptor vertexAttribute0 = vertexAttributes[0];
        NSLog(@"Vertex attribute 0: %p, %lu\n", (id)vertexAttribute0, vertexAttribute0.retainCount());
        vertexAttribute0.setFormat(mtl::VertexFormat::Float3);
        vertexAttribute0.setOffset(0);
        vertexAttribute0.setBufferIndex(0);

        // color
        mtl::VertexAttributeDescriptor vertexAttribute1 = vertexAttributes[1];
        NSLog(@"Vertex attribute 1: %p, %lu\n", (id)vertexAttribute1, vertexAttribute1.retainCount());
        vertexAttribute1.setFormat(mtl::VertexFormat::UChar4Normalized);
        vertexAttribute1.setOffset(12);
        vertexAttribute1.setBufferIndex(0);

        // texture coordinates 0
        mtl::VertexAttributeDescriptor vertexAttribute2 = vertexAttributes[2];
        NSLog(@"Vertex attribute 2: %p, %lu\n", (id)vertexAttribute2, vertexAttribute2.retainCount());
        vertexAttribute2.setFormat(mtl::VertexFormat::Float2);
        vertexAttribute2.setOffset(16);
        vertexAttribute2.setBufferIndex(0);

        // texture coordinates 1
        mtl::VertexAttributeDescriptor vertexAttribute3 = vertexAttributes[3];
        NSLog(@"Vertex attribute 3: %p, %lu\n", (id)vertexAttribute3, vertexAttribute3.retainCount());
        vertexAttribute3.setFormat(mtl::VertexFormat::Float2);
        vertexAttribute3.setOffset(24);
        vertexAttribute3.setBufferIndex(0);

        // normal
        mtl::VertexAttributeDescriptor vertexAttribute4 = vertexAttributes[4];
        NSLog(@"Vertex attribute 4: %p, %lu\n", (id)vertexAttribute4, vertexAttribute4.retainCount());
        vertexAttribute4.setFormat(mtl::VertexFormat::Float3);
        vertexAttribute4.setOffset(32);
        vertexAttribute4.setBufferIndex(0);

        renderPipelineDescriptor.setVertexDescriptor(vertexDescriptor);

        renderPipelineDescriptor.setDepthAttachmentPixelFormat(mtl::PixelFormat::Depth24Unorm_Stencil8);
        renderPipelineDescriptor.setStencilAttachmentPixelFormat(mtl::PixelFormat::Depth24Unorm_Stencil8);

        mtl::RenderPipelineState renderPipelineState = device.newRenderPipelineStateWithDescriptor(renderPipelineDescriptor);
        NSLog(@"Render pipeline state: %p, %lu\n", (id)renderPipelineState, renderPipelineState.retainCount());
    }
    catch (const ns::Error& error)
    {
        NSLog(@"Error: %ld, %s, %s, %lu", error.code(), error.domain().cString(), error.localizedDescription().cString(), error.retainCount());
    }

    metalLayer.device = device; // assign device
    const CGSize drawableSize = windowSize;
    metalLayer.drawableSize = drawableSize;

    CGDirectDisplayID displayId = [[[screen deviceDescription] objectForKey:@"NSScreenNumber"] unsignedIntValue];
    CVDisplayLinkRef displayLink = NULL;
    const CVReturn createResult = CVDisplayLinkCreateWithCGDisplay(displayId, &displayLink);
    if (createResult != kCVReturnSuccess) return 1;

    CVReturn setOutputCallbackResult = CVDisplayLinkSetOutputCallback(displayLink, renderCallback, NULL);
    if (setOutputCallbackResult != kCVReturnSuccess)
        return 1;

    CVReturn startResult = CVDisplayLinkStart(displayLink);
    if (startResult != kCVReturnSuccess)
        return 1;

    [sharedApplication run];

    CVDisplayLinkRelease(displayLink);
    [window release];
    [windowDelegate release];
}
