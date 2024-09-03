#import <UIKit/UIKit.h>

@interface FUViewController : UIViewController
@property(nonatomic, strong) NSString* channelId;
@property(nonatomic) int audioType;
@property(nonatomic) int userRole;
@property(nonatomic) int userId;
@property(nonatomic, strong) NSString* appId;
@property(nonatomic, strong) NSString* token;
@property(nonatomic) int serverType;
@property(nonatomic, strong) NSString* customAddr;
@property(nonatomic, assign) BOOL quicEnabled;
@property(nonatomic, assign) BOOL videoEnabled;
@property(nonatomic, assign) BOOL speakerEnabled;
@property(nonatomic, assign) BOOL videoSourceEnabled;
@property(nonatomic, assign) BOOL simulcastStreamEnabled;
@property(nonatomic, assign) BOOL detachStreamEnabled;
@property(nonatomic) int videoProfile;
@end

