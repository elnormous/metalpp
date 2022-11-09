#import "AppDelegate.h"

@interface AppDelegate ()


@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification*)notification {
    [[NSAppleEventManager sharedAppleEventManager]
        setEventHandler:self
            andSelector:@selector(handleURLEvent:withReplyEvent:)
          forEventClass:kInternetEventClass
             andEventID:kAEGetURL];

    NSDictionary* defaults = [NSDictionary dictionaryWithObjectsAndKeys:
                              [NSNumber numberWithBool:NO], @"AppleMomentumScrollSupported",
                              [NSNumber numberWithBool:NO], @"ApplePressAndHoldEnabled",
                              [NSNumber numberWithBool:YES], @"ApplePersistenceIgnoreState",
                              nil];
    [[NSUserDefaults standardUserDefaults] registerDefaults:defaults];
}

- (void)applicationWillTerminate:(NSNotification*)notification {

}

- (BOOL)applicationSupportsSecureRestorableState:(NSApplication*)app {
    return YES;
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)app {
    return YES;
}

- (void)handleURLEvent:(NSAppleEventDescriptor*)event withReplyEvent:(NSAppleEventDescriptor*)replyEvent
{
    NSString* path = [[event paramDescriptorForKeyword:keyDirectObject] stringValue];
    NSLog(@"URL event %@", path);
}

@end
