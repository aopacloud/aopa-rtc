//
//  UserViewCell.h
//  AopaRtcObjc
//
//  Created by bhb on 2020/4/27.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN
@protocol UserViewDelegate <NSObject>
@optional
-(void) onMuteClick:(int)uid mute:(BOOL)mute;
-(void) onVolumeChange:(int)uid volume:(int)volume;
-(void) onVideoStreamChange:(int)uid type:(int)type;
@end

@interface UserViewCell : UICollectionViewCell
- (instancetype)initWithFrame:(CGRect)frame;
- (id)initWithUser:(CGRect)frame delegate:(id<UserViewDelegate> _Nullable)delegate uid:(uint32_t)uid;
- (void)setMuteEnable:(BOOL)mute;
- (void)setRealTimeVolume:(int)volume;
- (void)setRemoteMute:(BOOL)mute;
- (void)setStreamType:(int)type;
- (void)setUserId:(uint32_t)userId;
- (uint32_t)getUserId;
- (UIView*)getVideoView;
- (void)setIndex:(int)idx;
- (int)getIndex;
@property (nonatomic, assign) id<UserViewDelegate>  _Nullable delegate;

@end

NS_ASSUME_NONNULL_END
