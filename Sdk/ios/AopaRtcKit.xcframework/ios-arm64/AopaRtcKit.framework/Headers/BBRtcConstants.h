//
//  BBRtcConstants.h
//  sources
//
//  Created by bhb on 2020/4/22.
//  Copyright © 2020 banban. All rights reserved.
//

#import <Foundation/Foundation.h>
#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#elif TARGET_OS_MAC
#import <AppKit/AppKit.h>
#endif

/** The standard bitrate set in [setVideoEncoderConfiguration]([BBRtcEngineKit setVideoEncoderConfiguration:]).

(Recommended) The standard bitrate mode. In this mode, the bitrate under the live broadcast and communication profiles differs:

    - Communication profile: The video bitrate is the same as the base bitrate.
    - Live broadcast profile: The video bitrate is twice the base bitrate.
 */
extern NSInteger const BBRtcVideoBitrateStandard;

/** The compatible bitrate set in [setVideoEncoderConfiguration]([BBRtcEngineKit setVideoEncoderConfiguration:]).

The compatible bitrate mode. In this mode, the bitrate stays the same regardless of the channel profile. In a live broadcast channel, if you choose this mode, the video frame rate may be lower than the set value.
 */
extern NSInteger const BBRtcVideoBitrateCompatible;

/** Use the default minimum bitrate.
 */
extern NSInteger const BBRtcVideoBitrateDefaultMin;

/** 120 &times; 120
 */
extern CGSize const BBRtcVideoDimension120x120;
/** 160 &times; 120
 */
extern CGSize const BBRtcVideoDimension160x120;
/** 180 &times; 180
 */
extern CGSize const BBRtcVideoDimension180x180;
/** 240 &times; 180
 */
extern CGSize const BBRtcVideoDimension240x180;
/** 320 &times; 180
 */
extern CGSize const BBRtcVideoDimension320x180;
/** 240 &times; 240
 */
extern CGSize const BBRtcVideoDimension240x240;
/** 320 &times; 240
 */
extern CGSize const BBRtcVideoDimension320x240;
/** 424 &times; 240
 */
extern CGSize const BBRtcVideoDimension424x240;
/** 360 &times; 360
 */
extern CGSize const BBRtcVideoDimension360x360;
/** 480 &times; 360
 */
extern CGSize const BBRtcVideoDimension480x360;
/** 640 &times; 360
 */
extern CGSize const BBRtcVideoDimension640x360;
/** 480 &times; 480
 */
extern CGSize const BBRtcVideoDimension480x480;
/** 640 &times; 480
 */
extern CGSize const BBRtcVideoDimension640x480;
/** 840 &times; 480
 */
extern CGSize const BBRtcVideoDimension840x480;
/** 960 &times; 720 (Hardware dependent)
 */
extern CGSize const BBRtcVideoDimension960x720;
/** 1280 &times; 720 (Hardware dependent)
 */
extern CGSize const BBRtcVideoDimension1280x720;
#if TARGET_OS_MAC && !TARGET_OS_IPHONE
/** 1920 &times; 1080 (Hardware dependent, macOS only)
 */
extern CGSize const BBRtcVideoDimension1920x1080;
/** 25400 &times; 1440 (Hardware dependent, macOS only)
 */
extern CGSize const BBRtcVideoDimension2540x1440;
/** 3840 &times; 2160 (Hardware dependent, macOS only)
 */
extern CGSize const BBRtcVideoDimension3840x2160;
#endif
