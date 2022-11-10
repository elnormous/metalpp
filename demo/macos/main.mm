#import <Cocoa/Cocoa.h>
#import <QuartzCore/CAMetalLayer.h>
#include "AppDelegate.h"
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

void createMainMenu(NSApplication* sharedApplication)
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

int main(int argc, const char* argv[]) {
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];

    NSApplication* sharedApplication = [NSApplication sharedApplication];
    [sharedApplication activateIgnoringOtherApps:YES];
    [sharedApplication setDelegate:[[[AppDelegate alloc] init] autorelease]];
    createMainMenu(sharedApplication);

    const NSWindowStyleMask windowStyleMask = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable;

    NSScreen* screen = [NSScreen mainScreen];

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

    metal::Device device;
    NSLog(@"Device name: %s\n", device.getName().cString());

    metal::Library library = device.newDefaultLibrary();
    NSLog(@"Library: %p\n", (id)library);

    foundation::String str{"test"};
    NSLog(@"String: %s (%lu), %c\n", str.cString(), str.length(), str[1]);

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
    [pool release];
}
