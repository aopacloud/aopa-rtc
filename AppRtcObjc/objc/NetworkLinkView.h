#import <UIKit/UIKit.h>
#import "NADAppDelegate.h"
NS_ASSUME_NONNULL_BEGIN

@interface NetworkLinkView : UIView
- (void)loadview:(BBRtcEngineKit*)rtcEngine;
- (void)show;
@end

NS_ASSUME_NONNULL_END
