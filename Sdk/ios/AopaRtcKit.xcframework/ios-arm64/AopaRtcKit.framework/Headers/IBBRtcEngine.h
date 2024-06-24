//
//  IBBRtcEngine.h
//  products
//
//  Created by bhb on 2020/4/16.
//  Copyright © 2020 banban. All rights reserved.
//

#ifndef IBBRtcEngine_h
#define IBBRtcEngine_h
#include "BBRtcBase.h"
#include "IBBMediaEngine.h"
namespace bbrtc {
const long RTCVERSION = 235103;
typedef unsigned int uid_t;
typedef void* view_t;
/** Maximum length of the device ID.
*/
enum MAX_DEVICE_ID_LENGTH_TYPE
{
  /** The maximum length of the device ID is 512 bytes.
  */
    MAX_DEVICE_ID_LENGTH = 512
};
/** Maximum length of user account.
 */
enum MAX_USER_ACCOUNT_LENGTH_TYPE
{
  /** The maximum length of user account is 255 bytes.
   */
  MAX_USER_ACCOUNT_LENGTH = 256
};
/** Maximum length of channel ID.
 */
enum MAX_CHANNEL_ID_LENGTH_TYPE
{
    /** The maximum length of channel id is 64 bytes.
     */
    MAX_CHANNEL_ID_LENGTH = 65
};
/** Formats of the quality report.
*/
enum QUALITY_REPORT_FORMAT_TYPE
{
  /** 0: The quality report in JSON format,
  */
    QUALITY_REPORT_JSON = 0,
    /** 1: The quality report in HTML format.
    */
    QUALITY_REPORT_HTML = 1,
};

enum MEDIA_ENGINE_EVENT_CODE_TYPE
{
    /** 723: For internal use only.
     */
    MEDIA_ENGINE_AUDIO_EVENT_MIXING_ALL_LOOPS_COMPLETED = 723,
};

/** The states of the local user's audio mixing file.
*/
enum AUDIO_MIXING_STATE_TYPE{
    /** 710: The audio mixing file is playing.
    */
    AUDIO_MIXING_STATE_PLAYING = 710,
    /** 711: The audio mixing file pauses playing.
    */
    AUDIO_MIXING_STATE_PAUSED = 711,
    /** 713: The audio mixing file stops playing.
    */
    AUDIO_MIXING_STATE_STOPPED = 713,
    /** 714: An exception occurs when playing the audio mixing file. See #AUDIO_MIXING_ERROR_TYPE.
    */
    AUDIO_MIXING_STATE_FAILED = 714,
};

/** The error codes of the local user's audio mixing file.
*/
enum AUDIO_MIXING_ERROR_TYPE{
    /** 701: The SDK cannot open the audio mixing file.
    */
    AUDIO_MIXING_ERROR_CAN_NOT_OPEN = 701,
    /** 702: The SDK opens the audio mixing file too frequently.
    */
    AUDIO_MIXING_ERROR_TOO_FREQUENT_CALL = 702,
    /** 703: The audio mixing file playback is interrupted.
     */
    AUDIO_MIXING_ERROR_INTERRUPTED_EOF = 703,
    /** 710: Network unstable
    */
    AUDIO_MIXING_ERROR_NETWORK_UNSTABLE = 705,
    /** 0: The SDK can open the audio mixing file.
    */
    AUDIO_MIXING_ERROR_OK = 0,
};


/** The reason of audio mixing state change.
 */
enum AUDIO_MIXING_REASON_TYPE {
  /** 701: The SDK cannot open the audio mixing file.
   */
  AUDIO_MIXING_REASON_CAN_NOT_OPEN = 701,
  /** 702: The SDK opens the audio mixing file too frequently.
   */
  AUDIO_MIXING_REASON_TOO_FREQUENT_CALL = 702,
  /** 703: The audio mixing file playback is interrupted.
   */
  AUDIO_MIXING_REASON_INTERRUPTED_EOF = 703,
  /** 720: The audio mixing is started by user.
   */
  AUDIO_MIXING_REASON_STARTED_BY_USER = 720,
  /** 721: The audio mixing file is played once.
   */
  AUDIO_MIXING_REASON_ONE_LOOP_COMPLETED = 721,
  /** 722: The audio mixing file is playing in a new loop.
   */
  AUDIO_MIXING_REASON_START_NEW_LOOP = 722,
  /** 723: The audio mixing file is all played out.
   */
  AUDIO_MIXING_REASON_ALL_LOOPS_COMPLETED = 723,
  /** 724: Playing of audio file is stopped by user.
   */
  AUDIO_MIXING_REASON_STOPPED_BY_USER = 724,
  /** 725: Playing of audio file is paused by user.
   */
  AUDIO_MIXING_REASON_PAUSED_BY_USER = 725,
  /** 726: Playing of audio file is resumed by user.
   */
  AUDIO_MIXING_REASON_RESUMED_BY_USER = 726,
};


/** Media device states.
 */
enum MEDIA_DEVICE_STATE_TYPE
{
  /** 1: The device is active.
  */
    MEDIA_DEVICE_STATE_ACTIVE = 1,
    /** 2: The device is disabled.
    */
    MEDIA_DEVICE_STATE_DISABLED = 2,
    /** 4: The device is not present.
    */
    MEDIA_DEVICE_STATE_NOT_PRESENT = 4,
    /** 8: The device is unplugged.
    */
    MEDIA_DEVICE_STATE_UNPLUGGED = 8
};

/** Media device types.
 */
enum MEDIA_DEVICE_TYPE
{
  /** -1: Unknown device type.
  */
    UNKNOWN_AUDIO_DEVICE = -1,
    /** 0: Audio playback device.
    */
    AUDIO_PLAYOUT_DEVICE = 0,
    /** 1: Audio recording device.
    */
    AUDIO_RECORDING_DEVICE = 1,
    /** 2: Video renderer.
    */
    VIDEO_RENDER_DEVICE = 2,
    /** 3: Video capturer.
    */
    VIDEO_CAPTURE_DEVICE = 3,
    /** 4: Application audio playback device.
    */
    AUDIO_APPLICATION_PLAYOUT_DEVICE = 4,
};

/** Local video state types
 */
enum LOCAL_VIDEO_STREAM_STATE
{
    /** Initial state */
    LOCAL_VIDEO_STREAM_STATE_STOPPED = 0,
    /** The capturer starts successfully. */
    LOCAL_VIDEO_STREAM_STATE_CAPTURING = 1,
    /** The first video frame is successfully encoded. */
    LOCAL_VIDEO_STREAM_STATE_ENCODING = 2,
    /** The local video fails to start. */
    LOCAL_VIDEO_STREAM_STATE_FAILED = 3
};

/** Local video state error codes
 */
enum LOCAL_VIDEO_STREAM_ERROR {
    /** The local video is normal. */
    LOCAL_VIDEO_STREAM_ERROR_OK = 0,
    /** No specified reason for the local video failure. */
    LOCAL_VIDEO_STREAM_ERROR_FAILURE = 1,
    /** No permission to use the local video capturing device. */
    LOCAL_VIDEO_STREAM_ERROR_DEVICE_NO_PERMISSION = 2,
    /** The local video capturing device is in use. */
    LOCAL_VIDEO_STREAM_ERROR_DEVICE_BUSY = 3,
    /** The local video capture fails. Check whether the capturing device is working properly. */
    LOCAL_VIDEO_STREAM_ERROR_CAPTURE_FAILURE = 4,
    /** The local video encoding fails. */
    LOCAL_VIDEO_STREAM_ERROR_ENCODE_FAILURE = 5
};

/** Local audio state types.
 */
enum LOCAL_AUDIO_STREAM_STATE
{
    /** 0: The local audio is in the initial state.
     */
    LOCAL_AUDIO_STREAM_STATE_STOPPED = 0,
    /** 1: The recording device starts successfully.
     */
    LOCAL_AUDIO_STREAM_STATE_RECORDING = 1,
    /** 2: The first audio frame encodes successfully.
     */
    LOCAL_AUDIO_STREAM_STATE_ENCODING = 2,
    /** 3: The local audio fails to start.
     */
    LOCAL_AUDIO_STREAM_STATE_FAILED = 3
};

/** Local audio state error codes.
 */
enum LOCAL_AUDIO_STREAM_ERROR
{
    /** 0: The local audio is normal.
     */
    LOCAL_AUDIO_STREAM_ERROR_OK = 0,
    /** 1: No specified reason for the local audio failure.
     */
    LOCAL_AUDIO_STREAM_ERROR_FAILURE = 1,
    /** 2: No permission to use the local audio device.
     */
    LOCAL_AUDIO_STREAM_ERROR_DEVICE_NO_PERMISSION = 2,
    /** 3: The microphone is in use.
     */
    LOCAL_AUDIO_STREAM_ERROR_DEVICE_BUSY = 3,
    /** 4: The local audio recording fails. Check whether the recording device
     * is working properly.
     */
    LOCAL_AUDIO_STREAM_ERROR_RECORD_FAILURE = 4,
    /** 5: The local audio encoding fails.
     */
    LOCAL_AUDIO_STREAM_ERROR_ENCODE_FAILURE = 5
};

/** Audio recording qualities.
*/
enum AUDIO_RECORDING_QUALITY_TYPE
{
    /** 0: Low quality. The sample rate is 32 kHz, and the file size is around
     * 1.2 MB after 10 minutes of recording.
    */
    AUDIO_RECORDING_QUALITY_LOW = 0,
    /** 1: Medium quality. The sample rate is 32 kHz, and the file size is
     * around 2 MB after 10 minutes of recording.
    */
    AUDIO_RECORDING_QUALITY_MEDIUM = 1,
    /** 2: High quality. The sample rate is 32 kHz, and the file size is
     * around 3.75 MB after 10 minutes of recording.
    */
    AUDIO_RECORDING_QUALITY_HIGH = 2,
};

/** Network quality types. */
enum QUALITY_TYPE
{
    /** 0: The network quality is unknown. */
    QUALITY_UNKNOWN = 0,
    /**  1: The network quality is excellent. */
    QUALITY_EXCELLENT = 1,
    /** 2: The network quality is quite good, but the bitrate may be slightly lower than excellent. */
    QUALITY_GOOD = 2,
    /** 3: Users can feel the communication slightly impaired. */
    QUALITY_POOR = 3,
    /** 4: Users cannot communicate smoothly. */
    QUALITY_BAD = 4,
    /** 5: The network is so bad that users can barely communicate. */
    QUALITY_VBAD = 5,
    /** 6: The network is down and users cannot communicate at all. */
    QUALITY_DOWN = 6,
    /** 7: Users cannot detect the network quality. (Not in use.) */
    QUALITY_UNSUPPORTED = 7,
    /** 8: Detecting the network quality. */
    QUALITY_DETECTING = 8,
};

/** Video display modes. */
enum RENDER_MODE_TYPE
{
    /**
     1: Uniformly scale the video until it fills the visible boundaries (cropped). One dimension of the video may have clipped contents.
     */
    RENDER_MODE_HIDDEN = 1,
    /**
     2: Uniformly scale the video until one of its dimension fits the boundary (zoomed to fit). Areas that are not filled due to disparity in the aspect ratio are filled with black.
     */
    RENDER_MODE_FIT = 2,
    /** **DEPRECATED** 3: This mode is deprecated.
     */
    RENDER_MODE_ADAPTIVE = 3,
    /**
     4: The fill mode. In this mode, the SDK stretches or zooms the video to fill the display window.
     */
    RENDER_MODE_FILL = 4,
};

/** Video mirror modes. */
enum VIDEO_MIRROR_MODE_TYPE
{
    /** 0: (Default) The SDK enables the mirror mode.
     */
    VIDEO_MIRROR_MODE_AUTO = 0,//determined by SDK
    /** 1: Enable mirror mode. */
    VIDEO_MIRROR_MODE_ENABLED = 1,//enabled mirror
    /** 2: Disable mirror mode. */
    VIDEO_MIRROR_MODE_DISABLED = 2,//disable mirror
};

/** **DEPRECATED** Video profiles. */
enum VIDEO_PROFILE_TYPE
{
    /** 0: 160 &times; 120, frame rate 15 fps, bitrate 65 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_120P = 0,
    /** 2: 120 &times; 120, frame rate 15 fps, bitrate 50 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_120P_3 = 2,
    /** 10: 320&times;180, frame rate 15 fps, bitrate 140 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_180P = 10,
    /** 12: 180 &times; 180, frame rate 15 fps, bitrate 100 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_180P_3 = 12,
    /** 13: 240 &times; 180, frame rate 15 fps, bitrate 120 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_180P_4 = 13,
    /** 20: 320 &times; 240, frame rate 15 fps, bitrate 200 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_240P = 20,
    /** 22: 240 &times; 240, frame rate 15 fps, bitrate 140 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_240P_3 = 22,
    /** 23: 424 &times; 240, frame rate 15 fps, bitrate 220 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_240P_4 = 23,
    /** 30: 640 &times; 360, frame rate 15 fps, bitrate 400 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_360P = 30,
    /** 32: 360 &times; 360, frame rate 15 fps, bitrate 260 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_360P_3 = 32,
    /** 33: 640 &times; 360, frame rate 30 fps, bitrate 600 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_360P_4 = 33,
    /** 35: 360 &times; 360, frame rate 30 fps, bitrate 400 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_360P_6 = 35,
    /** 36: 480 &times; 360, frame rate 15 fps, bitrate 320 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_360P_7 = 36,
    /** 37: 480 &times; 360, frame rate 30 fps, bitrate 490 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_360P_8 = 37,
    /** 38: 640 &times; 360, frame rate 15 fps, bitrate 800 Kbps.
     @note Live broadcast profile only.
     */
    VIDEO_PROFILE_LANDSCAPE_360P_9 = 38,
    /** 39: 640 &times; 360, frame rate 24 fps, bitrate 800 Kbps.
     @note Live broadcast profile only.
     */
    VIDEO_PROFILE_LANDSCAPE_360P_10 = 39,
    /** 100: 640 &times; 360, frame rate 24 fps, bitrate 1000 Kbps.
     @note Live broadcast profile only.
     */
    VIDEO_PROFILE_LANDSCAPE_360P_11 = 100,
    /** 40: 640 &times; 480, frame rate 15 fps, bitrate 500 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_480P = 40,
    /** 42: 480 &times; 480, frame rate 15 fps, bitrate 400 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_480P_3 = 42,
    /** 43: 640 &times; 480, frame rate 30 fps, bitrate 750 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_480P_4 = 43,
    /** 45: 480 &times; 480, frame rate 30 fps, bitrate 600 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_480P_6 = 45,
    /** 47: 848 &times; 480, frame rate 15 fps, bitrate 610 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_480P_8 = 47,
    /** 48: 848 &times; 480, frame rate 30 fps, bitrate 930 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_480P_9 = 48,
    /** 49: 640 &times; 480, frame rate 10 fps, bitrate 400 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_480P_10 = 49,
    /** 50: 1280 &times; 720, frame rate 15 fps, bitrate 1130 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_720P = 50,
    /** 52: 1280 &times; 720, frame rate 30 fps, bitrate 1710 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_720P_3 = 52,
    /** 54: 960 &times; 720, frame rate 15 fps, bitrate 910 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_720P_5 = 54,
    /** 55: 960 &times; 720, frame rate 30 fps, bitrate 1380 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_720P_6 = 55,
    /** 60: 1920 &times; 1080, frame rate 15 fps, bitrate 2080 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_1080P = 60,
    /** 62: 1920 &times; 1080, frame rate 30 fps, bitrate 3150 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_1080P_3 = 62,
    /** 64: 1920 &times; 1080, frame rate 60 fps, bitrate 4780 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_1080P_5 = 64,
    /** 66: 2560 &times; 1440, frame rate 30 fps, bitrate 4850 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_1440P = 66,
    /** 67: 2560 &times; 1440, frame rate 60 fps, bitrate 6500 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_1440P_2 = 67,
    /** 70: 3840 &times; 2160, frame rate 30 fps, bitrate 6500 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_4K = 70,
    /** 72: 3840 &times; 2160, frame rate 60 fps, bitrate 6500 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_4K_3 = 72,
    /** 1000: 120 &times; 160, frame rate 15 fps, bitrate 65 Kbps. */
    VIDEO_PROFILE_PORTRAIT_120P = 1000,
    /** 1002: 120 &times; 120, frame rate 15 fps, bitrate 50 Kbps. */
    VIDEO_PROFILE_PORTRAIT_120P_3 = 1002,
    /** 1010: 180 &times; 320, frame rate 15 fps, bitrate 140 Kbps. */
    VIDEO_PROFILE_PORTRAIT_180P = 1010,
    /** 1012: 180 &times; 180, frame rate 15 fps, bitrate 100 Kbps. */
    VIDEO_PROFILE_PORTRAIT_180P_3 = 1012,
    /** 1013: 180 &times; 240, frame rate 15 fps, bitrate 120 Kbps. */
    VIDEO_PROFILE_PORTRAIT_180P_4 = 1013,
    /** 1020: 240 &times; 320, frame rate 15 fps, bitrate 200 Kbps. */
    VIDEO_PROFILE_PORTRAIT_240P = 1020,
    /** 1022: 240 &times; 240, frame rate 15 fps, bitrate 140 Kbps. */
    VIDEO_PROFILE_PORTRAIT_240P_3 = 1022,
    /** 1023: 240 &times; 424, frame rate 15 fps, bitrate 220 Kbps. */
    VIDEO_PROFILE_PORTRAIT_240P_4 = 1023,
    /** 1030: 360 &times; 640, frame rate 15 fps, bitrate 400 Kbps. */
    VIDEO_PROFILE_PORTRAIT_360P = 1030,
    /** 1032: 360 &times; 360, frame rate 15 fps, bitrate 260 Kbps. */
    VIDEO_PROFILE_PORTRAIT_360P_3 = 1032,
    /** 1033: 360 &times; 640, frame rate 30 fps, bitrate 600 Kbps. */
    VIDEO_PROFILE_PORTRAIT_360P_4 = 1033,
    /** 1035: 360 &times; 360, frame rate 30 fps, bitrate 400 Kbps. */
    VIDEO_PROFILE_PORTRAIT_360P_6 = 1035,
    /** 1036: 360 &times; 480, frame rate 15 fps, bitrate 320 Kbps. */
    VIDEO_PROFILE_PORTRAIT_360P_7 = 1036,
    /** 1037: 360 &times; 480, frame rate 30 fps, bitrate 490 Kbps. */
    VIDEO_PROFILE_PORTRAIT_360P_8 = 1037,
    /** 1038: 360 &times; 640, frame rate 15 fps, bitrate 800 Kbps.
     @note Live broadcast profile only.
     */
    VIDEO_PROFILE_PORTRAIT_360P_9 = 1038,
    /** 1039: 360 &times; 640, frame rate 24 fps, bitrate 800 Kbps.
     @note Live broadcast profile only.
     */
    VIDEO_PROFILE_PORTRAIT_360P_10 = 1039,
    /** 1100: 360 &times; 640, frame rate 24 fps, bitrate 1000 Kbps.
     @note Live broadcast profile only.
     */
    VIDEO_PROFILE_PORTRAIT_360P_11 = 1100,
    /** 1040: 480 &times; 640, frame rate 15 fps, bitrate 500 Kbps. */
    VIDEO_PROFILE_PORTRAIT_480P = 1040,
    /** 1042: 480 &times; 480, frame rate 15 fps, bitrate 400 Kbps. */
    VIDEO_PROFILE_PORTRAIT_480P_3 = 1042,
    /** 1043: 480 &times; 640, frame rate 30 fps, bitrate 750 Kbps. */
    VIDEO_PROFILE_PORTRAIT_480P_4 = 1043,
    /** 1045: 480 &times; 480, frame rate 30 fps, bitrate 600 Kbps. */
    VIDEO_PROFILE_PORTRAIT_480P_6 = 1045,
    /** 1047: 480 &times; 848, frame rate 15 fps, bitrate 610 Kbps. */
    VIDEO_PROFILE_PORTRAIT_480P_8 = 1047,
    /** 1048: 480 &times; 848, frame rate 30 fps, bitrate 930 Kbps. */
    VIDEO_PROFILE_PORTRAIT_480P_9 = 1048,
    /** 1049: 480 &times; 640, frame rate 10 fps, bitrate 400 Kbps. */
    VIDEO_PROFILE_PORTRAIT_480P_10 = 1049,
    /** 1050: 720 &times; 1280, frame rate 15 fps, bitrate 1130 Kbps. */
    VIDEO_PROFILE_PORTRAIT_720P = 1050,
    /** 1052: 720 &times; 1280, frame rate 30 fps, bitrate 1710 Kbps. */
    VIDEO_PROFILE_PORTRAIT_720P_3 = 1052,
    /** 1054: 720 &times; 960, frame rate 15 fps, bitrate 910 Kbps. */
    VIDEO_PROFILE_PORTRAIT_720P_5 = 1054,
    /** 1055: 720 &times; 960, frame rate 30 fps, bitrate 1380 Kbps. */
    VIDEO_PROFILE_PORTRAIT_720P_6 = 1055,
    /** 1060: 1080 &times; 1920, frame rate 15 fps, bitrate 2080 Kbps. */
    VIDEO_PROFILE_PORTRAIT_1080P = 1060,
    /** 1062: 1080 &times; 1920, frame rate 30 fps, bitrate 3150 Kbps. */
    VIDEO_PROFILE_PORTRAIT_1080P_3 = 1062,
    /** 1064: 1080 &times; 1920, frame rate 60 fps, bitrate 4780 Kbps. */
    VIDEO_PROFILE_PORTRAIT_1080P_5 = 1064,
    /** 1066: 1440 &times; 2560, frame rate 30 fps, bitrate 4850 Kbps. */
    VIDEO_PROFILE_PORTRAIT_1440P = 1066,
    /** 1067: 1440 &times; 2560, frame rate 60 fps, bitrate 6500 Kbps. */
    VIDEO_PROFILE_PORTRAIT_1440P_2 = 1067,
    /** 1070: 2160 &times; 3840, frame rate 30 fps, bitrate 6500 Kbps. */
    VIDEO_PROFILE_PORTRAIT_4K = 1070,
    /** 1072: 2160 &times; 3840, frame rate 60 fps, bitrate 6500 Kbps. */
    VIDEO_PROFILE_PORTRAIT_4K_3 = 1072,
    /** Default 640 &times; 360, frame rate 15 fps, bitrate 400 Kbps. */
    VIDEO_PROFILE_DEFAULT = VIDEO_PROFILE_LANDSCAPE_360P,
};

/** Audio profiles.

Sets the sample rate, bitrate, encoding mode, and the number of channels:*/
enum AUDIO_PROFILE_TYPE // sample rate, bit rate, mono/stereo, speech/music codec
{
  /**
   0: Default audio profile.

   - In the Communication profile, the default value is #AUDIO_PROFILE_SPEECH_STANDARD;
   - In the Live-broadcast profile, the default value is #AUDIO_PROFILE_MUSIC_STANDARD.
   */
    AUDIO_PROFILE_DEFAULT = 0, // use default settings
    /**
     1: A sample rate of 32 KHz, audio encoding, mono, and a bitrate of up to 18 Kbps.
     */
    AUDIO_PROFILE_SPEECH_STANDARD = 1, // 32Khz, 18Kbps, mono, speech
    /**
     2: A sample rate of 48 KHz, music encoding, mono, and a bitrate of up to 48 Kbps.
     */
    AUDIO_PROFILE_MUSIC_STANDARD = 2, // 48Khz, 48Kbps, mono, music
    /**
     3: A sample rate of 48 KHz, music encoding, stereo, and a bitrate of up to 56 Kbps.
     */
    AUDIO_PROFILE_MUSIC_STANDARD_STEREO = 3, // 48Khz, 56Kbps, stereo, music
    /**
     4: A sample rate of 48 KHz, music encoding, mono, and a bitrate of up to 128 Kbps.
     */
    AUDIO_PROFILE_MUSIC_HIGH_QUALITY = 4, // 48Khz, 128Kbps, mono, music
    /**
     5: A sample rate of 48 KHz, music encoding, stereo, and a bitrate of up to 192 Kbps.
     */
    AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO = 5, // 48Khz, 192Kbps, stereo, music
    /**
     6: A sample rate of 16 KHz, audio encoding, mono, and Acoustic Echo Cancellation (AES) enabled.
     */
    AUDIO_PROFILE_IOT                       = 6,
    AUDIO_PROFILE_NUM = 7,
};

/** Audio application scenarios.
*/
enum AUDIO_SCENARIO_TYPE // set a suitable scenario for your app type
{
    /** 0: Default. */
    AUDIO_SCENARIO_DEFAULT = 0,
    /** 1: Entertainment scenario, supporting voice during gameplay. */
    AUDIO_SCENARIO_CHATROOM_ENTERTAINMENT = 1,
    /** 2: Education scenario, prioritizing smoothness and stability. */
    AUDIO_SCENARIO_EDUCATION = 2,
    /** 3: Live gaming scenario, enabling the gaming audio effects in the speaker mode in a live broadcast scenario. Choose this scenario for high-fidelity music playback. */
    AUDIO_SCENARIO_GAME_STREAMING = 3,
    /** 4: Showroom scenario, optimizing the audio quality with external professional equipment. */
    AUDIO_SCENARIO_SHOWROOM = 4,
    /** 5: Gaming scenario. */
    AUDIO_SCENARIO_CHATROOM_GAMING = 5,
    /** 6: Applicable to the IoT scenario. */
    AUDIO_SCENARIO_IOT = 6,
    /** 7: Real-time chorus scenario, where users have good network conditions and require ultra-low latency. */
    AUDIO_SCENARIO_CHORUS = 7,
};

 /** The channel profile of the Aopa RtcEngine.
 */
enum CHANNEL_PROFILE_TYPE
{
   /** (Default) The Communication profile. Use this profile in one-on-one calls or group calls, where all users can talk freely.
    */
    CHANNEL_PROFILE_COMMUNICATION = 0,
   /** The Live-Broadcast profile. Users in a live-broadcast channel have a role as either broadcaster or audience.
    A broadcaster can both send and receive streams; an audience can only receive streams.
    */
    CHANNEL_PROFILE_LIVE_BROADCASTING = 1,
   /** 2: The Gaming profile. This profile uses a codec with a lower bitrate and consumes less power. Applies to the gaming scenario, where all game players can talk freely.
    */
    CHANNEL_PROFILE_GAME = 2,
};

/** Client roles in a live broadcast. */
enum CLIENT_ROLE_TYPE
{
    /** 1: Host */
    CLIENT_ROLE_BROADCASTER = 1,
    /** 2: Audience */
    CLIENT_ROLE_AUDIENCE = 2,
};

/** Client roles in a KTV chorus. */
enum CLIENT_ROLE_CHORUS_TYPE
{
    /** 0: Host */
    CLIENT_ROLE_CHORUS_INVALID = 0,
    /** 1: Lead Singer */
    CLIENT_ROLE_CHORUS_MAIN = 1,
    /** 2: Deputy */
    CLIENT_ROLE_CHORUS_DEPUTY = 2
};

/** Reasons for a user being offline. */
enum USER_OFFLINE_REASON_TYPE
{
    /** 0: The user quits the call. */
    USER_OFFLINE_QUIT = 0,
    /** 1: The SDK times out and the user drops offline because no data packet is received within a certain period of time. If the user quits the call and the message is not passed to the SDK (due to an unreliable channel), the SDK assumes the user dropped offline. */
    USER_OFFLINE_DROPPED = 1,
      /** 2: (Live broadcast only.) The client role switched from the host to the audience. */
    USER_OFFLINE_BECOME_AUDIENCE = 2,
};
/**
 States of the RTMP streaming.
 */
enum RTMP_STREAM_PUBLISH_STATE
{
  /** The RTMP streaming has not started or has ended. This state is also triggered after you remove an RTMP address from the CDN by calling removePublishStreamUrl.
   */
  RTMP_STREAM_PUBLISH_STATE_IDLE = 0,
  /** The SDK is connecting to Aopa's streaming server and the RTMP server. This state is triggered after you call the \ref IRtcEngine::addPublishStreamUrl "addPublishStreamUrl" method.
   */
  RTMP_STREAM_PUBLISH_STATE_CONNECTING = 1,
  /** The RTMP streaming publishes. The SDK successfully publishes the RTMP streaming and returns this state.
   */
  RTMP_STREAM_PUBLISH_STATE_RUNNING = 2,
  /** The RTMP streaming is recovering. When exceptions occur to the CDN, or the streaming is interrupted, the SDK tries to resume RTMP streaming and returns this state.

   - If the SDK successfully resumes the streaming, #RTMP_STREAM_PUBLISH_STATE_RUNNING (2) returns.
   - If the streaming does not resume within 60 seconds or server errors occur, #RTMP_STREAM_PUBLISH_STATE_FAILURE (4) returns. You can also reconnect to the server by calling the \ref IRtcEngine::removePublishStreamUrl "removePublishStreamUrl" and \ref IRtcEngine::addPublishStreamUrl "addPublishStreamUrl" methods.
   */
  RTMP_STREAM_PUBLISH_STATE_RECOVERING = 3,
  /** The RTMP streaming fails. See the errCode parameter for the detailed error information. You can also call the \ref IRtcEngine::addPublishStreamUrl "addPublishStreamUrl" method to publish the RTMP streaming again.
   */
  RTMP_STREAM_PUBLISH_STATE_FAILURE = 4,
};

/**
 Error codes of the RTMP streaming.
 */
enum RTMP_STREAM_PUBLISH_ERROR
{
  /** The RTMP streaming publishes successfully. */
  RTMP_STREAM_PUBLISH_ERROR_OK = 0,
  /** Invalid argument used. If, for example, you do not call the \ref IRtcEngine::setLiveTranscoding "setLiveTranscoding" method to configure the LiveTranscoding parameters before calling the addPublishStreamUrl method, the SDK returns this error. Check whether you set the parameters in the *setLiveTranscoding* method properly. */
  RTMP_STREAM_PUBLISH_ERROR_INVALID_ARGUMENT = 1,
  /** The RTMP streaming is encrypted and cannot be published. */
  RTMP_STREAM_PUBLISH_ERROR_ENCRYPTED_STREAM_NOT_ALLOWED = 2,
  /** Timeout for the RTMP streaming. Call the \ref IRtcEngine::addPublishStreamUrl "addPublishStreamUrl" method to publish the streaming again. */
  RTMP_STREAM_PUBLISH_ERROR_CONNECTION_TIMEOUT = 3,
  /** An error occurs in Aopa's streaming server. Call the addPublishStreamUrl method to publish the streaming again. */
  RTMP_STREAM_PUBLISH_ERROR_INTERNAL_SERVER_ERROR = 4,
  /** An error occurs in the RTMP server. */
  RTMP_STREAM_PUBLISH_ERROR_RTMP_SERVER_ERROR = 5,
  /** The RTMP streaming publishes too frequently. */
  RTMP_STREAM_PUBLISH_ERROR_TOO_OFTEN = 6,
  /** The host publishes more than 10 URLs. Delete the unnecessary URLs before adding new ones. */
  RTMP_STREAM_PUBLISH_ERROR_REACH_LIMIT = 7,
  /** The host manipulates other hosts' URLs. Check your app logic. */
  RTMP_STREAM_PUBLISH_ERROR_NOT_AUTHORIZED = 8,
  /** Aopa's server fails to find the RTMP streaming. */
  RTMP_STREAM_PUBLISH_ERROR_STREAM_NOT_FOUND = 9,
  /** The format of the RTMP streaming URL is not supported. Check whether the URL format is correct. */
  RTMP_STREAM_PUBLISH_ERROR_FORMAT_NOT_SUPPORTED = 10,
};

/** States of importing an external video stream in a live broadcast. */
enum INJECT_STREAM_STATUS
{
    /** 0: The external video stream imported successfully. */
    INJECT_STREAM_STATUS_START_SUCCESS = 0,
    /** 1: The external video stream already exists. */
    INJECT_STREAM_STATUS_START_ALREADY_EXISTS = 1,
    /** 2: The external video stream to be imported is unauthorized. */
    INJECT_STREAM_STATUS_START_UNAUTHORIZED = 2,
    /** 3: Import external video stream timeout. */
    INJECT_STREAM_STATUS_START_TIMEDOUT = 3,
    /** 4: Import external video stream failed. */
    INJECT_STREAM_STATUS_START_FAILED = 4,
    /** 5: The external video stream stopped importing successfully. */
    INJECT_STREAM_STATUS_STOP_SUCCESS = 5,
    /** 6: No external video stream is found. */
    INJECT_STREAM_STATUS_STOP_NOT_FOUND = 6,
    /** 7: The external video stream to be stopped importing is unauthorized. */
    INJECT_STREAM_STATUS_STOP_UNAUTHORIZED = 7,
    /** 8: Stop importing external video stream timeout. */
    INJECT_STREAM_STATUS_STOP_TIMEDOUT = 8,
    /** 9: Stop importing external video stream failed. */
    INJECT_STREAM_STATUS_STOP_FAILED = 9,
    /** 10: The external video stream is corrupted. */
    INJECT_STREAM_STATUS_BROKEN = 10,
};
/** Remote video stream types. */
enum REMOTE_VIDEO_STREAM_TYPE
{
      /** 0: High-stream video. */
    REMOTE_VIDEO_STREAM_HIGH = 0,
      /** 1: Low-stream video. */
    REMOTE_VIDEO_STREAM_LOW = 1,

    REMOTE_VIDEO_STREAM_AUTO = 2,
};

/** Use modes of the \ref media::IAudioFrameObserver::onRecordAudioFrame "onRecordAudioFrame" callback. */
enum RAW_AUDIO_FRAME_OP_MODE_TYPE
{
    /** 0: Read-only mode: Users only read the \ref bb::media::IAudioFrameObserver::AudioFrame "AudioFrame" data without modifying anything. For example, when users acquire the data with the Aopa SDK, then push the RTMP streams. */
    RAW_AUDIO_FRAME_OP_MODE_READ_ONLY = 0,
    /** 1: Write-only mode: Users replace the \ref bb::media::IAudioFrameObserver::AudioFrame "AudioFrame" data with their own data and pass the data to the SDK for encoding. For example, when users acquire the data. */
    RAW_AUDIO_FRAME_OP_MODE_WRITE_ONLY = 1,
    /** 2: Read and write mode: Users read the data from \ref bb::media::IAudioFrameObserver::AudioFrame "AudioFrame", modify it, and then play it. For example, when users have their own sound-effect processing module and perform some voice pre-processing, such as a voice change. */
    RAW_AUDIO_FRAME_OP_MODE_READ_WRITE = 2,
};

/** Audio-sample rates. */
enum AUDIO_SAMPLE_RATE_TYPE
{
    /** 32000: 32 kHz */
    AUDIO_SAMPLE_RATE_32000 = 32000,
    /** 44100: 44.1 kHz */
    AUDIO_SAMPLE_RATE_44100 = 44100,
      /** 48000: 48 kHz */
    AUDIO_SAMPLE_RATE_48000 = 48000,
};

/** Video codec profile types. */
enum VIDEO_CODEC_PROFILE_TYPE
{  /** 66: Baseline video codec profile. Generally used in video calls on mobile phones. */
    VIDEO_CODEC_PROFILE_BASELINE = 66,
    /** 77: Main video codec profile. Generally used in mainstream electronics such as MP4 players, portable video players, PSP, and iPads. */
    VIDEO_CODEC_PROFILE_MAIN = 77,
      /** 100: (Default) High video codec profile. Generally used in high-resolution broadcasts or television. */
    VIDEO_CODEC_PROFILE_HIGH = 100,
};

/** Video codec types */
enum VIDEO_CODEC_TYPE {
    /** Standard VP8 */
    VIDEO_CODEC_VP8 = 1,
    /** Standard H264 */
    VIDEO_CODEC_H264 = 2,
    /** Enhanced VP8 */
    VIDEO_CODEC_EVP = 3,
    /** Enhanced H264 */
    VIDEO_CODEC_E264 = 4,
};

/** Audio equalization band frequencies. */
enum AUDIO_EQUALIZATION_BAND_FREQUENCY
{
    /** 0: 31 Hz */
    AUDIO_EQUALIZATION_BAND_31 = 0,
      /** 1: 62 Hz */
    AUDIO_EQUALIZATION_BAND_62 = 1,
    /** 2: 125 Hz */
    AUDIO_EQUALIZATION_BAND_125 = 2,
      /** 3: 250 Hz */
    AUDIO_EQUALIZATION_BAND_250 = 3,
      /** 4: 500 Hz */
    AUDIO_EQUALIZATION_BAND_500 = 4,
        /** 5: 1 kHz */
    AUDIO_EQUALIZATION_BAND_1K = 5,
        /** 6: 2 kHz */
    AUDIO_EQUALIZATION_BAND_2K = 6,
        /** 7: 4 kHz */
    AUDIO_EQUALIZATION_BAND_4K = 7,
        /** 8: 8 kHz */
    AUDIO_EQUALIZATION_BAND_8K = 8,
      /** 9: 16 kHz */
    AUDIO_EQUALIZATION_BAND_16K = 9,
};
/** The options for SDK preset voice beautifier effects.
 */
enum VOICE_BEAUTIFIER_PRESET
{
    /** Turn off voice beautifier effects and use the original voice.
     */
    VOICE_BEAUTIFIER_OFF = 0x00000000,
    /** A more magnetic voice.
     *
     * @note Aopa recommends using this enumerator to process a male-sounding voice; otherwise, you may experience vocal distortion.
     */
    CHAT_BEAUTIFIER_MAGNETIC = 0x01010100,
    /** A fresher voice.
     *
     * @note Aopa recommends using this enumerator to process a female-sounding voice; otherwise, you may experience vocal distortion.
     */
    CHAT_BEAUTIFIER_FRESH = 0x01010200,
    /** A more vital voice.
     *
     * @note Aopa recommends using this enumerator to process a female-sounding voice; otherwise, you may experience vocal distortion.
     */
    CHAT_BEAUTIFIER_VITALITY = 0x01010300,
    /**
     * @since v3.3.0
     *
     * Singing beautifier effect.
     * - If you call \ref IRtcEngine::setVoiceBeautifierPreset "setVoiceBeautifierPreset" (SINGING_BEAUTIFIER), you can beautify a male-sounding voice and add a reverberation
     * effect that sounds like singing in a small room. Aopa recommends not using \ref IRtcEngine::setVoiceBeautifierPreset "setVoiceBeautifierPreset" (SINGING_BEAUTIFIER)
     * to process a female-sounding voice; otherwise, you may experience vocal distortion.
     * - If you call \ref IRtcEngine::setVoiceBeautifierParameters "setVoiceBeautifierParameters"(SINGING_BEAUTIFIER, param1, param2), you can beautify a male- or
     * female-sounding voice and add a reverberation effect.
     */
    SINGING_BEAUTIFIER = 0x01020100,
    /** A more vigorous voice.
     */
    TIMBRE_TRANSFORMATION_VIGOROUS = 0x01030100,
    /** A deeper voice.
     */
    TIMBRE_TRANSFORMATION_DEEP = 0x01030200,
    /** A mellower voice.
     */
    TIMBRE_TRANSFORMATION_MELLOW = 0x01030300,
    /** A falsetto voice.
     */
    TIMBRE_TRANSFORMATION_FALSETTO = 0x01030400,
    /** A fuller voice.
     */
    TIMBRE_TRANSFORMATION_FULL = 0x01030500,
    /** A clearer voice.
     */
    TIMBRE_TRANSFORMATION_CLEAR = 0x01030600,
    /** A more resounding voice.
     */
    TIMBRE_TRANSFORMATION_RESOUNDING = 0x01030700,
    /** A more ringing voice.
     */
    TIMBRE_TRANSFORMATION_RINGING = 0x01030800
};
/** The options for SDK preset audio effects.
 */
enum AUDIO_EFFECT_PRESET
{
    /** Turn off audio effects and use the original voice.
     */
    AUDIO_EFFECT_OFF = 0x00000000,
    /** An audio effect typical of a KTV venue.
     *
     * @note To achieve better audio effect quality, Aopa recommends calling \ref IRtcEngine::setAudioProfile "setAudioProfile"
     * and setting the `profile` parameter to `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)`
     * before setting this enumerator.
     */
    ROOM_ACOUSTICS_KTV = 0x02010100,
    /** An audio effect typical of a concert hall.
     *
     * @note To achieve better audio effect quality, Aopa recommends calling \ref IRtcEngine::setAudioProfile "setAudioProfile"
     * and setting the `profile` parameter to `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)`
     * before setting this enumerator.
     */
    ROOM_ACOUSTICS_VOCAL_CONCERT = 0x02010200,
    /** An audio effect typical of a recording studio.
     *
     * @note To achieve better audio effect quality, Aopa recommends calling \ref IRtcEngine::setAudioProfile "setAudioProfile"
     * and setting the `profile` parameter to `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)`
     * before setting this enumerator.
     */
    ROOM_ACOUSTICS_STUDIO = 0x02010300,
    /** An audio effect typical of a vintage phonograph.
     *
     * @note To achieve better audio effect quality, Aopa recommends calling \ref IRtcEngine::setAudioProfile "setAudioProfile"
     * and setting the `profile` parameter to `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)`
     * before setting this enumerator.
     */
    ROOM_ACOUSTICS_PHONOGRAPH = 0x02010400,
    /** A virtual stereo effect that renders monophonic audio as stereo audio.
     *
     * @note Call \ref IRtcEngine::setAudioProfile "setAudioProfile" and set the `profile` parameter to
     * `AUDIO_PROFILE_MUSIC_STANDARD_STEREO(3)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before setting this
     * enumerator; otherwise, the enumerator setting does not take effect.
     */
    ROOM_ACOUSTICS_VIRTUAL_STEREO = 0x02010500,
    /** A more spatial audio effect.
     *
     * @note To achieve better audio effect quality, Aopa recommends calling \ref IRtcEngine::setAudioProfile "setAudioProfile"
     * and setting the `profile` parameter to `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)`
     * before setting this enumerator.
     */
    ROOM_ACOUSTICS_SPACIAL = 0x02010600,
    /** A more ethereal audio effect.
     *
     * @note To achieve better audio effect quality, Aopa recommends calling \ref IRtcEngine::setAudioProfile "setAudioProfile"
     * and setting the `profile` parameter to `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)`
     * before setting this enumerator.
     */
    ROOM_ACOUSTICS_ETHEREAL = 0x02010700,
    /** A 3D voice effect that makes the voice appear to be moving around the user. The default cycle period of the 3D
     * voice effect is 10 seconds. To change the cycle period, call \ref IRtcEngine::setAudioEffectParameters "setAudioEffectParameters"
     * after this method.
     *
     * @note
     * - Call \ref IRtcEngine::setAudioProfile "setAudioProfile" and set the `profile` parameter to `AUDIO_PROFILE_MUSIC_STANDARD_STEREO(3)`
     * or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before setting this enumerator; otherwise, the enumerator setting does not take effect.
     * - If the 3D voice effect is enabled, users need to use stereo audio playback devices to hear the anticipated voice effect.
     */
    ROOM_ACOUSTICS_3D_VOICE = 0x02010800,
    /** The voice of an uncle.
     *
     * @note
     * - Aopa recommends using this enumerator to process a male-sounding voice; otherwise, you may not hear the anticipated voice effect.
     * - To achieve better audio effect quality, Aopa recommends calling \ref IRtcEngine::setAudioProfile "setAudioProfile" and
     * setting the `profile` parameter to `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before
     * setting this enumerator.
     */
    VOICE_CHANGER_EFFECT_UNCLE = 0x02020100,
    /** The voice of an old man.
     *
     * @note
     * - Aopa recommends using this enumerator to process a male-sounding voice; otherwise, you may not hear the anticipated voice effect.
     * - To achieve better audio effect quality, Aopa recommends calling \ref IRtcEngine::setAudioProfile "setAudioProfile" and setting
     * the `profile` parameter to `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before setting
     * this enumerator.
     */
    VOICE_CHANGER_EFFECT_OLDMAN = 0x02020200,
    /** The voice of a boy.
     *
     * @note
     * - Aopa recommends using this enumerator to process a male-sounding voice; otherwise, you may not hear the anticipated voice effect.
     * - To achieve better audio effect quality, Aopa recommends calling \ref IRtcEngine::setAudioProfile "setAudioProfile" and setting
     * the `profile` parameter to `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before
     * setting this enumerator.
     */
    VOICE_CHANGER_EFFECT_BOY = 0x02020300,
    /** The voice of a young woman.
     *
     * @note
     * - Aopa recommends using this enumerator to process a female-sounding voice; otherwise, you may not hear the anticipated voice effect.
     * - To achieve better audio effect quality, Aopa recommends calling \ref IRtcEngine::setAudioProfile "setAudioProfile" and setting
     * the `profile` parameter to `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before
     * setting this enumerator.
     */
    VOICE_CHANGER_EFFECT_SISTER = 0x02020400,
    /** The voice of a girl.
     *
     * @note
     * - Aopa recommends using this enumerator to process a female-sounding voice; otherwise, you may not hear the anticipated voice effect.
     * - To achieve better audio effect quality, Aopa recommends calling \ref IRtcEngine::setAudioProfile "setAudioProfile" and setting
     * the `profile` parameter to `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before
     * setting this enumerator.
     */
    VOICE_CHANGER_EFFECT_GIRL = 0x02020500,
    /** The voice of Pig King, a character in Journey to the West who has a voice like a growling bear.
     *
     * @note To achieve better audio effect quality, Aopa recommends calling \ref IRtcEngine::setAudioProfile "setAudioProfile" and
     * setting the `profile` parameter to `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before
     * setting this enumerator.
     */
    VOICE_CHANGER_EFFECT_PIGKING = 0x02020600,
    /** The voice of Hulk.
     *
     * @note To achieve better audio effect quality, Aopa recommends calling \ref IRtcEngine::setAudioProfile "setAudioProfile" and
     * setting the `profile` parameter to `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before
     * setting this enumerator.
     */
    VOICE_CHANGER_EFFECT_HULK = 0x02020700,
    /** An audio effect typical of R&B music.
     *
     * @note Call \ref IRtcEngine::setAudioProfile "setAudioProfile" and
     * set the `profile` parameter to `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before
     * setting this enumerator; otherwise, the enumerator setting does not take effect.
     */
    STYLE_TRANSFORMATION_RNB = 0x02030100,
    /** An audio effect typical of popular music.
     *
     * @note Call \ref IRtcEngine::setAudioProfile "setAudioProfile" and
     * set the `profile` parameter to `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before
     * setting this enumerator; otherwise, the enumerator setting does not take effect.
     */
    STYLE_TRANSFORMATION_POPULAR = 0x02030200,
    /** A pitch correction effect that corrects the user's pitch based on the pitch of the natural C major scale.
     * To change the basic mode and tonic pitch, call \ref IRtcEngine::setAudioEffectParameters "setAudioEffectParameters" after this method.
     *
     * @note To achieve better audio effect quality, Aopa recommends calling \ref IRtcEngine::setAudioProfile "setAudioProfile" and
     * setting the `profile` parameter to `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before
     * setting this enumerator.
     */
    PITCH_CORRECTION = 0x02040100
};

/** Audio reverberation types. */
enum AUDIO_REVERB_TYPE
{
    /** 0: The level of the dry signal (db). The value is between -20 and 10. */
    AUDIO_REVERB_DRY_LEVEL = 0, // (dB, [-20,10]), the level of the dry signal
    /** 1: The level of the early reflection signal (wet signal) (dB). The value is between -20 and 10. */
    AUDIO_REVERB_WET_LEVEL = 1, // (dB, [-20,10]), the level of the early reflection signal (wet signal)
    /** 2: The room size of the reflection. The value is between 0 and 100. */
    AUDIO_REVERB_ROOM_SIZE = 2, // ([0,100]), the room size of the reflection
    /** 3: The length of the initial delay of the wet signal (ms). The value is between 0 and 200. */
    AUDIO_REVERB_WET_DELAY = 3, // (ms, [0,200]), the length of the initial delay of the wet signal in ms
    /** 4: The reverberation strength. The value is between 0 and 100. */
    AUDIO_REVERB_STRENGTH = 4, // ([0,100]), the strength of the reverberation
};

/** Local voice changer options. */
enum VOICE_CHANGER_PRESET {
    /** 0: The original voice (no local voice change).
    */
    VOICE_CHANGER_OFF = 0, //Turn off the voice changer
    /** 1: An old man's voice.
    */
    VOICE_CHANGER_OLDMAN = 1,
    /** 2: A little boy's voice.
    */
    VOICE_CHANGER_BABYBOY = 2,
    /** 3: A little girl's voice.
    */
    VOICE_CHANGER_BABYGIRL = 3,
    /** 4: The voice of a growling bear.
    */
    VOICE_CHANGER_ZHUBAJIE = 4,
    /** 5: Ethereal vocal effects.
    */
    VOICE_CHANGER_ETHEREAL = 5,
    /** 6: Hulk's voice.
    */
    VOICE_CHANGER_HULK = 6
};


/** @deprecated Deprecated from v3.2.0.
 *
 *  Local voice reverberation presets.
 */
enum AUDIO_REVERB_PRESET {
    /**
     * Turn off local voice reverberation, that is, to use the original voice.
     */
    AUDIO_REVERB_OFF = 0x00000000, // Turn off audio reverb
    /**
     * The reverberation style typical of a KTV venue (enhanced).
     */
    AUDIO_REVERB_FX_KTV = 0x00100001,
    /**
     * The reverberation style typical of a concert hall (enhanced).
     */
    AUDIO_REVERB_FX_VOCAL_CONCERT = 0x00100002,
    /**
     * The reverberation style typical of an uncle's voice.
     */
    AUDIO_REVERB_FX_UNCLE = 0x00100003,
    /**
     * The reverberation style typical of a little sister's voice.
     */
    AUDIO_REVERB_FX_SISTER = 0x00100004,
    /**
     * The reverberation style typical of a recording studio (enhanced).
     */
    AUDIO_REVERB_FX_STUDIO = 0x00100005,
    /**
     * The reverberation style typical of popular music (enhanced).
     */
    AUDIO_REVERB_FX_POPULAR = 0x00100006,
    /**
     * The reverberation style typical of R&B music (enhanced).
     */
    AUDIO_REVERB_FX_RNB = 0x00100007,
    /**
     * The reverberation style typical of the vintage phonograph.
     */
    AUDIO_REVERB_FX_PHONOGRAPH = 0x00100008,
    /**
     * The reverberation style typical of popular music.
     */
    AUDIO_REVERB_POPULAR = 0x00000001,
    /**
     * The reverberation style typical of R&B music.
     */
    AUDIO_REVERB_RNB = 0x00000002,
    /**
     * The reverberation style typical of rock music.
     */
    AUDIO_REVERB_ROCK = 0x00000003,
    /**
     * The reverberation style typical of hip-hop music.
     */
     AUDIO_REVERB_HIPHOP = 0x00000004,
    /**
     * The reverberation style typical of a concert hall.
     */
    AUDIO_REVERB_VOCAL_CONCERT = 0x00000005,
    /**
     * The reverberation style typical of a KTV venue.
     */
    AUDIO_REVERB_KTV = 0x00000006,
    /**
     * The reverberation style typical of a recording studio.
     */
    AUDIO_REVERB_STUDIO = 0x00000007,
    /**
     * The reverberation of the virtual stereo. The virtual stereo is an effect that renders the monophonic
     * audio as the stereo audio, so that all users in the channel can hear the stereo voice effect.
     * To achieve better virtual stereo reverberation, Aopa recommends setting `profile` in `setAudioProfile`
     * as `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)`.
     */
    AUDIO_VIRTUAL_STEREO = 0x00200001,
    /** 1: Electronic Voice.*/
    AUDIO_ELECTRONIC_VOICE = 0x00300001,
    /** 1: 3D Voice.*/
    AUDIO_THREEDIM_VOICE = 0x00400001
};
enum VOICE_CONVERSION_PRESET
{
    VOICE_CONVERSION_OFF = 0x00000000,
    VOICE_CHANGER_NEUTRAL = 0x03010100,
    VOICE_CHANGER_SWEET = 0x03010200,
    VOICE_CHANGER_SOLID = 0x03010300,
    VOICE_CHANGER_BASS = 0x03010400
};
/** Audio codec profile types. The default value is LC_ACC. */
enum AUDIO_CODEC_PROFILE_TYPE
{
    /** 0: LC-AAC, which is the low-complexity audio codec type. */
  AUDIO_CODEC_PROFILE_LC_AAC = 0,
    /** 1: HE-AAC, which is the high-efficiency audio codec type. */
  AUDIO_CODEC_PROFILE_HE_AAC = 1,
};

/** Remote audio states.
 */
enum REMOTE_AUDIO_STATE
{
      /** 0: The remote audio is in the default state, probably due to
       * #REMOTE_AUDIO_REASON_LOCAL_MUTED (3),
       * #REMOTE_AUDIO_REASON_REMOTE_MUTED (5), or
       * #REMOTE_AUDIO_REASON_REMOTE_OFFLINE (7).
       */
      REMOTE_AUDIO_STATE_STOPPED = 0,  // Default state, audio is started or remote user disabled/muted audio stream
      /** 1: The first remote audio packet is received.
       */
      REMOTE_AUDIO_STATE_STARTING = 1,  // The first audio frame packet has been received
      /** 2: The remote audio stream is decoded and plays normally, probably
       * due to #REMOTE_AUDIO_REASON_NETWORK_RECOVERY (2),
       * #REMOTE_AUDIO_REASON_LOCAL_UNMUTED (4), or
       * #REMOTE_AUDIO_REASON_REMOTE_UNMUTED (6).
       */
      REMOTE_AUDIO_STATE_DECODING = 2,  // The first remote audio frame has been decoded or fronzen state ends
      /** 3: The remote audio is frozen, probably due to
       * #REMOTE_AUDIO_REASON_NETWORK_CONGESTION (1).
       */
      REMOTE_AUDIO_STATE_FROZEN = 3,    // Remote audio is frozen, probably due to network issue
      /** 4: The remote audio fails to start, probably due to
       * #REMOTE_AUDIO_REASON_INTERNAL (0).
       */
      REMOTE_AUDIO_STATE_FAILED = 4,    // Remote audio play failed
};

/** Remote audio state reasons.
 */
enum REMOTE_AUDIO_STATE_REASON
{
      /** 0: Internal reasons.
       */
      REMOTE_AUDIO_REASON_INTERNAL = 0,
      /** 1: Network congestion.
       */
      REMOTE_AUDIO_REASON_NETWORK_CONGESTION = 1,
      /** 2: Network recovery.
       */
      REMOTE_AUDIO_REASON_NETWORK_RECOVERY = 2,
      /** 3: The local user stops receiving the remote audio stream or
       * disables the audio module.
       */
      REMOTE_AUDIO_REASON_LOCAL_MUTED = 3,
      /** 4: The local user resumes receiving the remote audio stream or
       * enables the audio module.
       */
      REMOTE_AUDIO_REASON_LOCAL_UNMUTED = 4,
      /** 5: The remote user stops sending the audio stream or disables the
       * audio module.
       */
      REMOTE_AUDIO_REASON_REMOTE_MUTED = 5,
      /** 6: The remote user resumes sending the audio stream or enables the
       * audio module.
       */
      REMOTE_AUDIO_REASON_REMOTE_UNMUTED = 6,
      /** 7: The remote user leaves the channel.
       */
      REMOTE_AUDIO_REASON_REMOTE_OFFLINE = 7,
};

/** The publishing state.
 */
enum STREAM_PUBLISH_STATE {
  /** 0: The initial publishing state after joining the channel.
   */
  PUB_STATE_IDLE = 0,
  /** 1: Fails to publish the local stream. Possible reasons:
   * - The local user calls \ref IRtcEngine::muteLocalAudioStream "muteLocalAudioStream(true)" or \ref IRtcEngine::muteLocalVideoStream "muteLocalVideoStream(true)" to stop sending local streams.
   * - The local user calls \ref IRtcEngine::disableAudio "disableAudio" or \ref IRtcEngine::disableVideo "disableVideo" to disable the entire audio or video module.
   * - The local user calls \ref IRtcEngine::enableLocalAudio "enableLocalAudio(false)" or \ref IRtcEngine::enableLocalVideo "enableLocalVideo(false)" to disable the local audio sampling or video capturing.
   * - The role of the local user is `AUDIENCE`.
   */
  PUB_STATE_NO_PUBLISHED = 1,
  /** 2: Publishing.
   */
  PUB_STATE_PUBLISHING = 2,
  /** 3: Publishes successfully.
   */
  PUB_STATE_PUBLISHED = 3
};

/** The subscribing state.
 */
enum STREAM_SUBSCRIBE_STATE {
  /** 0: The initial subscribing state after joining the channel.
   */
  SUB_STATE_IDLE = 0,
  /** 1: Fails to subscribe to the remote stream. Possible reasons:
   * - The remote user:
   *  - Calls \ref IRtcEngine::muteLocalAudioStream "muteLocalAudioStream(true)" or \ref IRtcEngine::muteLocalVideoStream "muteLocalVideoStream(true)" to stop sending local streams.
   *  - Calls \ref IRtcEngine::disableAudio "disableAudio" or \ref IRtcEngine::disableVideo "disableVideo" to disable the entire audio or video modules.
   *  - Calls \ref IRtcEngine::enableLocalAudio "enableLocalAudio(false)" or \ref IRtcEngine::enableLocalVideo "enableLocalVideo(false)" to disable the local audio sampling or video capturing.
   *  - The role of the remote user is `AUDIENCE`.
   * - The local user calls the following methods to stop receiving remote streams:
   *  - Calls \ref IRtcEngine::muteRemoteAudioStream "muteRemoteAudioStream(true)", \ref IRtcEngine::muteAllRemoteAudioStreams "muteAllRemoteAudioStreams(true)", or \ref IRtcEngine::setDefaultMuteAllRemoteAudioStreams "setDefaultMuteAllRemoteAudioStreams(true)" to stop receiving remote audio streams.
   *  - Calls \ref IRtcEngine::muteRemoteVideoStream "muteRemoteVideoStream(true)", \ref IRtcEngine::muteAllRemoteVideoStreams "muteAllRemoteVideoStreams(true)", or \ref IRtcEngine::setDefaultMuteAllRemoteVideoStreams "setDefaultMuteAllRemoteVideoStreams(true)" to stop receiving remote video streams.
   */
  SUB_STATE_NO_SUBSCRIBED = 1,
  /** 2: Subscribing.
   */
  SUB_STATE_SUBSCRIBING = 2,
  /** 3: Subscribes to and receives the remote stream successfully.
   */
  SUB_STATE_SUBSCRIBED = 3
};


/** The state of the remote video. */
enum REMOTE_VIDEO_STATE {
    /** 0: The remote video is in the default state, probably due to #REMOTE_VIDEO_STATE_REASON_LOCAL_MUTED (3), #REMOTE_VIDEO_STATE_REASON_REMOTE_MUTED (5), or #REMOTE_VIDEO_STATE_REASON_REMOTE_OFFLINE (7).
     */
    REMOTE_VIDEO_STATE_STOPPED = 0,

    /** 1: The first remote video packet is received.
     */
    REMOTE_VIDEO_STATE_STARTING = 1,

    /** 2: The remote video stream is decoded and plays normally, probably due to #REMOTE_VIDEO_STATE_REASON_NETWORK_RECOVERY (2), #REMOTE_VIDEO_STATE_REASON_LOCAL_UNMUTED (4), #REMOTE_VIDEO_STATE_REASON_REMOTE_UNMUTED (6), or #REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK_RECOVERY (9).
     */
    REMOTE_VIDEO_STATE_DECODING = 2,

    /** 3: The remote video is frozen, probably due to #REMOTE_VIDEO_STATE_REASON_NETWORK_CONGESTION (1) or #REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK (8).
     */
    REMOTE_VIDEO_STATE_FROZEN = 3,

    /** 4: The remote video fails to start, probably due to #REMOTE_VIDEO_STATE_REASON_INTERNAL (0).
     */
    REMOTE_VIDEO_STATE_FAILED = 4
};

/** The reason of the remote video state change. */
enum REMOTE_VIDEO_STATE_REASON {
    /** 0: Internal reasons.
     */
    REMOTE_VIDEO_STATE_REASON_INTERNAL = 0,

    /** 1: Network congestion.
     */
    REMOTE_VIDEO_STATE_REASON_NETWORK_CONGESTION = 1,

    /** 2: Network recovery.
     */
    REMOTE_VIDEO_STATE_REASON_NETWORK_RECOVERY = 2,

    /** 3: The local user stops receiving the remote video stream or disables the video module.
     */
    REMOTE_VIDEO_STATE_REASON_LOCAL_MUTED = 3,

    /** 4: The local user resumes receiving the remote video stream or enables the video module.
     */
    REMOTE_VIDEO_STATE_REASON_LOCAL_UNMUTED = 4,

    /** 5: The remote user stops sending the video stream or disables the video module.
     */
    REMOTE_VIDEO_STATE_REASON_REMOTE_MUTED = 5,

    /** 6: The remote user resumes sending the video stream or enables the video module.
     */
    REMOTE_VIDEO_STATE_REASON_REMOTE_UNMUTED = 6,

    /** 7: The remote user leaves the channel.
     */
    REMOTE_VIDEO_STATE_REASON_REMOTE_OFFLINE = 7,

    /** 8: The remote media stream falls back to the audio-only stream due to poor network conditions.
     */
    REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK = 8,

    /** 9: The remote media stream switches back to the video stream after the network conditions improve.
     */
    REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK_RECOVERY = 9

};

/** Video frame rates. */
enum FRAME_RATE
{
      /** 1: 1 fps */
    FRAME_RATE_FPS_1 = 1,
        /** 7: 7 fps */
    FRAME_RATE_FPS_7 = 7,
      /** 10: 10 fps */
    FRAME_RATE_FPS_10 = 10,
    /** 15: 15 fps */
    FRAME_RATE_FPS_15 = 15,
        /** 24: 24 fps */
    FRAME_RATE_FPS_24 = 24,
    /** 30: 30 fps */
    FRAME_RATE_FPS_30 = 30,
    /** 60: 60 fps (Windows and macOS only) */
    FRAME_RATE_FPS_60 = 60,
};

/** Video output orientation modes.
 */
enum ORIENTATION_MODE {
  /** 0: (Default) Adaptive mode.

   The video encoder adapts to the orientation mode of the video input device.

   - If the width of the captured video from the SDK is greater than the height, the encoder sends the video in landscape mode. The encoder also sends the rotational information of the video, and the receiver uses the rotational information to rotate the received video.
   - When you use a custom video source, the output video from the encoder inherits the orientation of the original video. If the original video is in portrait mode, the output video from the encoder is also in portrait mode. The encoder also sends the rotational information of the video to the receiver.
   */
    ORIENTATION_MODE_ADAPTIVE = 0,
    /** 1: Landscape mode.

     The video encoder always sends the video in landscape mode. The video encoder rotates the original video before sending it and the rotational infomation is 0. This mode applies to scenarios involving CDN live streaming.
     */
    ORIENTATION_MODE_FIXED_LANDSCAPE = 1,
    /** 2: Portrait mode.

     The video encoder always sends the video in portrait mode. The video encoder rotates the original video before sending it and the rotational infomation is 0. This mode applies to scenarios involving CDN live streaming.
     */
    ORIENTATION_MODE_FIXED_PORTRAIT = 2,
};

/** Video degradation preferences when the bandwidth is a constraint. */
enum DEGRADATION_PREFERENCE {
    /** 0: (Default) Degrade the frame rate in order to maintain the video quality. */
    MAINTAIN_QUALITY = 0,
    /** 1: Degrade the video quality in order to maintain the frame rate. */
    MAINTAIN_FRAMERATE = 1,
    /** 2: (For future use) Maintain a balance between the frame rate and video quality. */
    MAINTAIN_BALANCED = 2,
    
    MAINTAIN_DISABLED = 3,
};

/** Stream fallback options. */
enum STREAM_FALLBACK_OPTIONS
{
    /** 0: No fallback behavior for the local/remote video stream when the uplink/downlink network conditions are poor. The quality of the stream is not guaranteed. */
    STREAM_FALLBACK_OPTION_DISABLED = 0,
    /** 1: Under poor downlink network conditions, the remote video stream, to which you subscribe, falls back to the low-stream (low resolution and low bitrate) video. You can set this option only in the \ref IRtcEngine::setRemoteSubscribeFallbackOption "setRemoteSubscribeFallbackOption" method. Nothing happens when you set this in the \ref IRtcEngine::setLocalPublishFallbackOption "setLocalPublishFallbackOption" method. */
    STREAM_FALLBACK_OPTION_VIDEO_STREAM_LOW = 1,
    /** 2: Under poor uplink network conditions, the locally published video stream falls back to audio only.

    Under poor downlink network conditions, the remote video stream, to which you subscribe, first falls back to the low-stream (low resolution and low bitrate) video; and then to an audio-only stream if the network conditions worsen.*/
    STREAM_FALLBACK_OPTION_AUDIO_ONLY = 2,
};

 /** Camera capturer configuration.
 */
 enum CAPTURER_OUTPUT_PREFERENCE
 {
    /** 0: (Default) self-adapts the camera output parameters to the system performance and network conditions to balance CPU consumption and video preview quality.
     */
    CAPTURER_OUTPUT_PREFERENCE_AUTO = 0,
    /** 1: Prioritizes the system performance. The SDK chooses the dimension and frame rate of the local camera capture closest to those set by \ref IRtcEngine::setVideoEncoderConfiguration "setVideoEncoderConfiguration".
     */
    CAPTURER_OUTPUT_PREFERENCE_PERFORMANCE = 1,
    /** 2: Prioritizes the local preview quality. The SDK chooses higher camera output parameters to improve the local video preview quality. This option requires extra CPU and RAM usage for video pre-processing.
     */
    CAPTURER_OUTPUT_PREFERENCE_PREVIEW = 2,
    /** 3: Allows you to customize the width and height of the video image captured by the local camera.
     */
    CAPTURER_OUTPUT_PREFERENCE_MANUAL = 3,
 };

/** The priority of the remote user.
 */
enum PRIORITY_TYPE
{
  /** 50: The user's priority is high.
   */
  PRIORITY_HIGH = 50,
  /** 100: (Default) The user's priority is normal.
  */
  PRIORITY_NORMAL = 100,
};

/** Connection states. */
enum CONNECTION_STATE_TYPE
{
  /** 1: The SDK is disconnected from Aopa's edge server.

   - This is the initial state before calling the \ref bb::rtc::IRtcEngine::joinChannel "joinChannel" method.
   - The SDK also enters this state when the application calls the \ref bb::rtc::IRtcEngine::leaveChannel "leaveChannel" method.
   */
  CONNECTION_STATE_DISCONNECTED = 1,
  /** 2: The SDK is connecting to Aopa's edge server.

   - When the application calls the \ref bb::rtc::IRtcEngine::joinChannel "joinChannel" method, the SDK starts to establish a connection to the specified channel, triggers the \ref bb::rtc::IRtcEngineEventHandler::onConnectionStateChanged "onConnectionStateChanged" callback, and switches to the #CONNECTION_STATE_CONNECTING state.
   - When the SDK successfully joins the channel, it triggers the \ref bb::rtc::IRtcEngineEventHandler::onConnectionStateChanged "onConnectionStateChanged" callback and switches to the #CONNECTION_STATE_CONNECTED state.
   - After the SDK joins the channel and when it finishes initializing the media engine, the SDK triggers the \ref bb::rtc::IRtcEngineEventHandler::onJoinChannelSuccess "onJoinChannelSuccess" callback.
   */
  CONNECTION_STATE_CONNECTING = 2,
  /** 3: The SDK is connected to Aopa's edge server and has joined a channel. You can now publish or subscribe to a media stream in the channel.

   If the connection to the channel is lost because, for example, if the network is down or switched, the SDK automatically tries to reconnect and triggers:
   - The \ref bb::rtc::IRtcEngineEventHandler::onConnectionInterrupted "onConnectionInterrupted" callback (deprecated).
   - The \ref bb::rtc::IRtcEngineEventHandler::onConnectionStateChanged "onConnectionStateChanged" callback and switches to the #CONNECTION_STATE_RECONNECTING state.
   */
  CONNECTION_STATE_CONNECTED = 3,
  /** 4: The SDK keeps rejoining the channel after being disconnected from a joined channel because of network issues.

   - If the SDK cannot rejoin the channel within 10 seconds after being disconnected from Aopa's edge server, the SDK triggers the \ref bb::rtc::IRtcEngineEventHandler::onConnectionLost "onConnectionLost" callback, stays in the #CONNECTION_STATE_RECONNECTING state, and keeps rejoining the channel.
   - If the SDK fails to rejoin the channel 20 minutes after being disconnected from Aopa's edge server, the SDK triggers the \ref bb::rtc::IRtcEngineEventHandler::onConnectionStateChanged "onConnectionStateChanged" callback, switches to the #CONNECTION_STATE_FAILED state, and stops rejoining the channel.
   */
  CONNECTION_STATE_RECONNECTING = 4,
  /** 5: The SDK fails to connect to Aopa's edge server or join the channel.

   You must call the \ref bb::rtc::IRtcEngine::leaveChannel "leaveChannel" method to leave this state, and call the \ref bb::rtc::IRtcEngine::joinChannel "joinChannel" method again to rejoin the channel.

   If the SDK is banned from joining the channel by Aopa's edge server (through the RESTful API), the SDK triggers the \ref bb::rtc::IRtcEngineEventHandler::onConnectionBanned "onConnectionBanned" (deprecated) and \ref bb::rtc::IRtcEngineEventHandler::onConnectionStateChanged "onConnectionStateChanged" callbacks.
   */
  CONNECTION_STATE_FAILED = 5,
};

/** Reasons for a connection state change. */
enum CONNECTION_CHANGED_REASON_TYPE
{
  /** 0: The SDK is connecting to Aopa's edge server. */
  CONNECTION_CHANGED_CONNECTING = 0,
  /** 1: The SDK has joined the channel successfully. */
  CONNECTION_CHANGED_JOIN_SUCCESS = 1,
  /** 2: The connection between the SDK and Aopa's edge server is interrupted. */
  CONNECTION_CHANGED_INTERRUPTED = 2,
  /** 3: The connection between the SDK and Aopa's edge server is banned by Aopa's edge server. */
  CONNECTION_CHANGED_BANNED_BY_SERVER = 3,
  /** 4: The SDK fails to join the channel for more than 20 minutes and stops reconnecting to the channel. */
  CONNECTION_CHANGED_JOIN_FAILED = 4,
  /** 5: The SDK has left the channel. */
  CONNECTION_CHANGED_LEAVE_CHANNEL = 5,
  /** 6: The connection failed since Appid is not valid. */
  CONNECTION_CHANGED_INVALID_APP_ID = 6,
  /** 7: The connection failed since channel name is not valid. */
  CONNECTION_CHANGED_INVALID_CHANNEL_NAME = 7,
  /** 8: The connection failed since token is not valid, possibly because:

   - The App Certificate for the project is enabled in Console, but you do not use Token when joining the channel. If you enable the App Certificate, you must use a token to join the channel.
   - The uid that you specify in the \ref bb::rtc::IRtcEngine::joinChannel "joinChannel" method is different from the uid that you pass for generating the token.
   */
  CONNECTION_CHANGED_INVALID_TOKEN = 8,
  /** 9: The connection failed since token is expired. */
  CONNECTION_CHANGED_TOKEN_EXPIRED = 9,
  /** 10: The connection is rejected by server. */
  CONNECTION_CHANGED_REJECTED_BY_SERVER = 10,
  /** 11: The connection changed to reconnecting since SDK has set a proxy server. */
  CONNECTION_CHANGED_SETTING_PROXY_SERVER = 11,
  /** 12: When SDK is in connection failed, the renew token operation will make it connecting. */
  CONNECTION_CHANGED_RENEW_TOKEN = 12,
  /** 13: The IP Address of SDK client has changed. i.e., Network type or IP/Port changed by network operator might change client IP address. */
  CONNECTION_CHANGED_CLIENT_IP_ADDRESS_CHANGED = 13,
  /** 14: Timeout for the keep-alive of the connection between the SDK and Aopa's edge server. The connection state changes to CONNECTION_STATE_RECONNECTING(4). */
  CONNECTION_CHANGED_KEEP_ALIVE_TIMEOUT = 14,
};

/** Network type. */
enum NETWORK_TYPE
{
  /** -1: The network type is unknown. */
  NETWORK_TYPE_UNKNOWN = -1,
  /** 0: The SDK disconnects from the network. */
  NETWORK_TYPE_DISCONNECTED = 0,
  /** 1: The network type is LAN. */
  NETWORK_TYPE_LAN = 1,
  /** 2: The network type is Wi-Fi(including hotspots). */
  NETWORK_TYPE_WIFI = 2,
  /** 3: The network type is mobile 2G. */
  NETWORK_TYPE_MOBILE_2G = 3,
  /** 4: The network type is mobile 3G. */
  NETWORK_TYPE_MOBILE_3G = 4,
  /** 5: The network type is mobile 4G. */
  NETWORK_TYPE_MOBILE_4G = 5,
  /** 6: The network type is mobile 5G. */
  NETWORK_TYPE_MOBILE_5G = 6,
};

/** Audio output routing. */
enum AUDIO_ROUTE_TYPE {
    /** Default.
     */
    AUDIO_ROUTE_DEFAULT = -1,
    /** Headset.
     */
    AUDIO_ROUTE_HEADSET = 0,
    /** Earpiece.
     */
    AUDIO_ROUTE_EARPIECE = 1,
    /** Headset with no microphone.
     */
    AUDIO_ROUTE_HEADSET_NO_MIC = 2,
    /** Speakerphone.
     */
    AUDIO_ROUTE_SPEAKERPHONE = 3,
    /** Loudspeaker.
     */
    AUDIO_ROUTE_LOUDSPEAKER = 4,
    /** Bluetooth headset.
     */
    AUDIO_ROUTE_BLUETOOTH = 5,
    /** USB
     */
    AUDIO_ROUTE_USB = 6,
};

#if (defined(__APPLE__) && TARGET_OS_IOS)
/** Audio session restriction. */
enum AUDIO_SESSION_OPERATION_RESTRICTION {
    /** No restriction, the SDK has full control of the audio session operations. */
    AUDIO_SESSION_OPERATION_RESTRICTION_NONE = 0,
    /** The SDK does not change the audio session category. */
    AUDIO_SESSION_OPERATION_RESTRICTION_SET_CATEGORY = 1,
    /** The SDK does not change any setting of the audio session (category, mode, categoryOptions). */
    AUDIO_SESSION_OPERATION_RESTRICTION_CONFIGURE_SESSION = 1 << 1,
    /** The SDK keeps the audio session active when leaving a channel. */
    AUDIO_SESSION_OPERATION_RESTRICTION_DEACTIVATE_SESSION = 1 << 2,
    /** The SDK does not configure the audio session anymore. */
    AUDIO_SESSION_OPERATION_RESTRICTION_ALL = 1 << 7,
};
#endif

#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
enum CAMERA_DIRECTION {
    /** The rear camera. */
    CAMERA_REAR = 0,
    /** The front camera. */
    CAMERA_FRONT = 1,
};
#endif

/** Properties of the audio volume information.

 An array containing the user ID and volume information for each speaker.
 */
struct AudioVolumeInfo
{
   /**
    User ID of the speaker. The uid of the local user is 0.
    */
    uid_t uid;
   /** The volume of the speaker. The volume ranges between 0 (lowest volume) and 255 (highest volume).
    */
    unsigned int volume;
    /** Voice activity status of the local user.
     * - 0: The local user is not speaking.
     * - 1: The local user is speaking.
     *
     * @note
     * - The `vad` parameter cannot report the voice activity status of the remote users. In the remote users' callback, `vad` = 0.
     * - Ensure that you set `report_vad`(true) in the \ref bb::rtc::IRtcEngine::enableAudioVolumeIndication(int, int, bool) "enableAudioVolumeIndication" method to enable the voice activity detection of the local user.
     */
    unsigned int vad;
    /** The channel ID, which indicates which channel the speaker is in.
     */
    const char * channelId;
};

/** Statistics of the channel.
 */
struct RtcStats
{
  /**
   Call duration (s), represented by an aggregate value.
   */
    unsigned int duration;
    /**
     Total number of bytes transmitted, represented by an aggregate value.
     */
    unsigned int txBytes;
    /**
     Total number of bytes received, represented by an aggregate value.
     */
    unsigned int rxBytes;
     /** Total number of audio bytes sent (bytes), represented
     * by an aggregate value.
     */
    unsigned int txAudioBytes;
    /** Total number of video bytes sent (bytes), represented
     * by an aggregate value.
     */
    unsigned int txVideoBytes;
    /** Total number of audio bytes received (bytes) before
     * network countermeasures, represented by an aggregate value.
     */
    unsigned int rxAudioBytes;
    /** Total number of video bytes received (bytes),
     * represented by an aggregate value.
     */
    unsigned int rxVideoBytes;

    /**
     Transmission bitrate (Kbps), represented by an instantaneous value.
     */
    unsigned short txKBitRate;
    /**
     Receive bitrate (Kbps), represented by an instantaneous value.
     */
    unsigned short rxKBitRate;
    /**
     Audio receive bitrate (Kbps), represented by an instantaneous value.
     */
    unsigned short rxAudioKBitRate;
    /**
     Audio transmission bitrate (Kbps), represented by an instantaneous value.
     */
    unsigned short txAudioKBitRate;
    /**
     Video receive bitrate (Kbps), represented by an instantaneous value.
     */
    unsigned short rxVideoKBitRate;
    /**
     Video transmission bitrate (Kbps), represented by an instantaneous value.
     */
    unsigned short txVideoKBitRate;
    /** Client-server latency (ms)
     */
    unsigned short lastmileDelay;
    /** The packet loss rate (%) from the local client to Aopa's edge server,
     * before using the anti-packet-loss method.
     */
    unsigned short txPacketLossRate;
    /** The packet loss rate (%) from Aopa's edge server to the local client,
     * before using the anti-packet-loss method.
     */
    unsigned short rxPacketLossRate;
    /** Number of users in the channel.

     - Communication profile: The number of users in the channel.
     - Live broadcast profile:

         -  If the local user is an audience: The number of users in the channel = The number of hosts in the channel + 1.
         -  If the user is a host: The number of users in the channel = The number of hosts in the channel.
     */
    unsigned int userCount;
    /**
     Application CPU usage (%).
     */
    double cpuAppUsage;
    /**
     System CPU usage (%).
     */
    double cpuTotalUsage;
    /** The round-trip time delay from the client to the local router.
     */
    int gatewayRtt;
    /**
     The memory usage ratio of the app (%).
     @note This value is for reference only. Due to system limitations, you may not get the value of this member.
     */
    double memoryAppUsageRatio;
    /**
     The memory usage ratio of the system (%).
     @note This value is for reference only. Due to system limitations, you may not get the value of this member.
     */
    double memoryTotalUsageRatio;
    /**
     The memory usage of the app (KB).
     @note This value is for reference only. Due to system limitations, you may not get the value of this member.
     */
    int memoryAppUsageInKbytes;
  RtcStats()
      : duration(0)
      , txBytes(0)
      , rxBytes(0)
      , txAudioBytes(0)
      , txVideoBytes(0)
      , rxAudioBytes(0)
      , rxVideoBytes(0)
      , txKBitRate(0)
      , rxKBitRate(0)
      , rxAudioKBitRate(0)
      , txAudioKBitRate(0)
      , rxVideoKBitRate(0)
      , txVideoKBitRate(0)
      , lastmileDelay(0)
      , txPacketLossRate(0)
      , rxPacketLossRate(0)
      , userCount(0)
      , cpuAppUsage(0)
      , cpuTotalUsage(0)
      , gatewayRtt(0)
      , memoryAppUsageRatio(0)
      , memoryTotalUsageRatio(0)
      , memoryAppUsageInKbytes(0) {}
};

/** Quality change of the local video in terms of target frame rate and target bit rate since last count.
  */
enum QUALITY_ADAPT_INDICATION {
  /** The quality of the local video stays the same. */
  ADAPT_NONE = 0,
  /** The quality improves because the network bandwidth increases. */
  ADAPT_UP_BANDWIDTH = 1,
  /** The quality worsens because the network bandwidth decreases. */
  ADAPT_DOWN_BANDWIDTH = 2,
};

/** The error code in CHANNEL_MEDIA_RELAY_ERROR. */
enum CHANNEL_MEDIA_RELAY_ERROR {
    /** 0: The state is normal.
     */
    RELAY_OK = 0,
    /** 1: An error occurs in the server response.
     */
    RELAY_ERROR_SERVER_ERROR_RESPONSE = 1,
    /** 2: No server response. You can call the
     * \ref bb::rtc::IRtcEngine::leaveChannel "leaveChannel" method to
     * leave the channel.
     */
    RELAY_ERROR_SERVER_NO_RESPONSE = 2,
    /** 3: The SDK fails to access the service, probably due to limited
     * resources of the server.
     */
    RELAY_ERROR_NO_RESOURCE_AVAILABLE = 3,
    /** 4: Fails to send the relay request.
     */
    RELAY_ERROR_FAILED_JOIN_SRC = 4,
    /** 5: Fails to accept the relay request.
     */
    RELAY_ERROR_FAILED_JOIN_DEST = 5,
    /** 6: The server fails to receive the media stream.
     */
    RELAY_ERROR_FAILED_PACKET_RECEIVED_FROM_SRC = 6,
    /** 7: The server fails to send the media stream.
     */
    RELAY_ERROR_FAILED_PACKET_SENT_TO_DEST = 7,
    /** 8: The SDK disconnects from the server due to poor network
     * connections. You can call the \ref bb::rtc::IRtcEngine::leaveChannel
     * "leaveChannel" method to leave the channel.
     */
    RELAY_ERROR_SERVER_CONNECTION_LOST = 8,
    /** 9: An internal error occurs in the server.
     */
    RELAY_ERROR_INTERNAL_ERROR = 9,
    /** 10: The token of the source channel has expired.
     */
    RELAY_ERROR_SRC_TOKEN_EXPIRED = 10,
    /** 11: The token of the destination channel has expired.
     */
    RELAY_ERROR_DEST_TOKEN_EXPIRED = 11,
};

/** The event code in CHANNEL_MEDIA_RELAY_EVENT. */
enum CHANNEL_MEDIA_RELAY_EVENT {
    /** 0: The user disconnects from the server due to poor network
     * connections.
     */
    RELAY_EVENT_NETWORK_DISCONNECTED = 0,
    /** 1: The network reconnects.
     */
    RELAY_EVENT_NETWORK_CONNECTED = 1,
    /** 2: The user joins the source channel.
     */
    RELAY_EVENT_PACKET_JOINED_SRC_CHANNEL = 2,
    /** 3: The user joins the destination channel.
     */
    RELAY_EVENT_PACKET_JOINED_DEST_CHANNEL = 3,
    /** 4: The SDK starts relaying the media stream to the destination channel.
     */
    RELAY_EVENT_PACKET_SENT_TO_DEST_CHANNEL = 4,
    /** 5: The server receives the video stream from the source channel.
     */
    RELAY_EVENT_PACKET_RECEIVED_VIDEO_FROM_SRC = 5,
    /** 6: The server receives the audio stream from the source channel.
     */
    RELAY_EVENT_PACKET_RECEIVED_AUDIO_FROM_SRC = 6,
    /** 7: The destination channel is updated.
     */
    RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL = 7,
    /** 8: The destination channel update fails due to internal reasons.
     */
    RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL_REFUSED = 8,
    /** 9: The destination channel does not change, which means that the
     * destination channel fails to be updated.
     */
    RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL_NOT_CHANGE = 9,
    /** 10: The destination channel name is NULL.
     */
    RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL_IS_NULL = 10,
    /** 11: The video profile is sent to the server.
     */
    RELAY_EVENT_VIDEO_PROFILE_UPDATE = 11,
};

/** The state code in CHANNEL_MEDIA_RELAY_STATE. */
enum CHANNEL_MEDIA_RELAY_STATE {
    /** 0: The SDK is initializing.
     */
    RELAY_STATE_IDLE = 0,
    /** 1: The SDK tries to relay the media stream to the destination channel.
     */
    RELAY_STATE_CONNECTING = 1,
    /** 2: The SDK successfully relays the media stream to the destination
     * channel.
     */
    RELAY_STATE_RUNNING = 2,
    /** 3: A failure occurs. See the details in code.
     */
    RELAY_STATE_FAILURE = 3,
};

/** Statistics of the local video stream.
 */
struct LocalVideoStats
{
  /** Bitrate (Kbps) sent in the reported interval, which does not include
   * the bitrate of the retransmission video after packet loss.
   */
  int sentBitrate;
  /** Frame rate (fps) sent in the reported interval, which does not include
   * the frame rate of the retransmission video after packet loss.
   */
  int sentFrameRate;
  /** The encoder output frame rate (fps) of the local video.
   */
  int encoderOutputFrameRate;
  /** The render output frame rate (fps) of the local video.
   */
  int rendererOutputFrameRate;
  /** The target bitrate (Kbps) of the current encoder. This value is estimated by the SDK based on the current network conditions.
    */
  int targetBitrate;
  /** The target frame rate (fps) of the current encoder.
    */
  int targetFrameRate;
  /** Quality change of the local video in terms of target frame rate and
   * target bit rate in this reported interval. See #QUALITY_ADAPT_INDICATION.
   */
  QUALITY_ADAPT_INDICATION qualityAdaptIndication;
  /** The encoding bitrate (Kbps), which does not include the bitrate of the
   * re-transmission video after packet loss.
   */
  int encodedBitrate;
  /** The width of the encoding frame (px).
   */
  int encodedFrameWidth;
  /** The height of the encoding frame (px).
   */
  int encodedFrameHeight;
  /** The value of the sent frames, represented by an aggregate value.
   */
  int encodedFrameCount;
  /** The codec type of the local video:
   * - VIDEO_CODEC_VP8 = 1: VP8.
   * - VIDEO_CODEC_H264 = 2: (Default) H.264.
   */
  VIDEO_CODEC_TYPE codecType;
};

/** Statistics of the remote video stream.
 */
struct RemoteVideoStats
{
  /**
 User ID of the remote user sending the video streams.
 */
    uid_t uid;
    /** **DEPRECATED** Time delay (ms).
 */
    int delay;
/**
 Width (pixels) of the video stream.
 */
    int width;
  /**
 Height (pixels) of the video stream.
 */
    int height;
  /**
 Bitrate (Kbps) received since the last count.
 */
    int receivedBitrate;
  /** The decoder output frame rate (fps) of the remote video.
   */
    int decoderOutputFrameRate;
  /** The render output frame rate (fps) of the remote video.
   */
  int rendererOutputFrameRate;
  /** Packet loss rate (%) of the remote video stream after using the anti-packet-loss method.
   */
  int packetLossRate;
  REMOTE_VIDEO_STREAM_TYPE rxStreamType;
  /**
   The total freeze time (ms) of the remote video stream after the remote user joins the channel.
   In a video session where the frame rate is set to no less than 5 fps, video freeze occurs when
   the time interval between two adjacent renderable video frames is more than 500 ms.
   */
    int totalFrozenTime;
  /**
   The total video freeze time as a percentage (%) of the total time when the video is available.
   */
    int frozenRate;
    /**
     * remote video bufferdelay in ms
    */
    int remoteJbInMs;
    /**
     * remote video first frame receive ts
    */
    int64_t remoteFirstFrameReceiveTs;
};

/** Audio statistics of the local user */
struct LocalAudioStats
{
    /** The number of channels.
     */
    int numChannels;
    /** The sample rate (Hz).
     */
    int sentSampleRate;
    /** The average sending bitrate (Kbps).
     */
    int sentBitrate;
};

/** Audio statistics of a remote user */
struct RemoteAudioStats
{
    /** User ID of the remote user sending the audio streams.
     *
     */
    uid_t uid;
    /** Audio quality received by the user: #QUALITY_TYPE.
     */
    int quality;
    /** Network delay (ms) from the sender to the receiver.
     */
    int networkTransportDelay;
    /** Network delay (ms) from the receiver to the jitter buffer.
     */
    int jitterBufferDelay;
    /** The audio frame loss rate in the reported interval.
     */
    int audioLossRate;
    /** The number of channels.
     */
    int numChannels;
    /** The sample rate (Hz) of the received audio stream in the reported
     * interval.
     */
    int receivedSampleRate;
    /** The average bitrate (Kbps) of the received audio stream in the
     * reported interval. */
    int receivedBitrate;
    /** The total freeze time (ms) of the remote audio stream after the remote user joins the channel. In a session, audio freeze occurs when the audio frame loss rate reaches 4%.
     * bbrtc uses 2 seconds as an audio piece unit to calculate the audio freeze time. The total audio freeze time = The audio freeze number &times; 2 seconds
     */
    int totalFrozenTime;
    /** The total audio freeze time as a percentage (%) of the total time when the audio is available. */
    int frozenRate;
};

/**
 * Video dimensions.
 */
struct VideoDimensions {
    /** Width (pixels) of the video. */
    int width;
      /** Height (pixels) of the video. */
    int height;
    VideoDimensions()
        : width(640), height(480)
    {}
    VideoDimensions(int w, int h)
        : width(w), height(h)
    {}
};

/** (Recommended) The standard bitrate set in the \ref IRtcEngine::setVideoEncoderConfiguration "setVideoEncoderConfiguration" method.

 In this mode, the bitrates differ between the live broadcast and communication profiles:

 - Communication profile: The video bitrate is the same as the base bitrate.
 - Live broadcast profile: The video bitrate is twice the base bitrate.

 */
const int STANDARD_BITRATE = 0;

/** Use the default minimum bitrate.
 */
const int DEFAULT_MIN_BITRATE = -1;

/** Video encoder configurations.
 */
struct VideoEncoderConfiguration {
  /** The video frame dimensions (px) used to specify the video quality and measured by the total number of pixels along a frame's width and height: VideoDimensions. The default value is 640 x 360.
  */
    VideoDimensions dimensions;
    /** The frame rate of the video: #FRAME_RATE. The default value is 15.

     Note that we do not recommend setting this to a value greater than 30.
    */
    FRAME_RATE frameRate;
    /** The minimum frame rate of the video. The default value is -1.
     */
    int minFrameRate;
    /** The video encoding bitrate (Kbps).

     Choose one of the following options:

     - #STANDARD_BITRATE: (Recommended) The standard bitrate.
        - The Communication profile: the encoding bitrate equals the base bitrate.
        - The Live-broadcast profile: the encoding bitrate is twice the base bitrate.
     - #COMPATIBLE_BITRATE: The compatible bitrate: the bitrate stays the same regardless of the profile.

     The Communication profile prioritizes smoothness, while the Live-broadcast profile prioritizes video quality (requiring a higher bitrate). We recommend setting the bitrate mode as #STANDARD_BITRATE to address this difference.

     The following table lists the recommended video encoder configurations, where the base bitrate applies to the Communication profile. Set your bitrate based on this table. If you set a bitrate beyond the proper range, the SDK automatically sets it to within the range.

     | Resolution             | Frame Rate (fps) | Base Bitrate (Kbps, for Communication) | Live Bitrate (Kbps, for Live Broadcast)|
     |------------------------|------------------|----------------------------------------|----------------------------------------|
     | 160 &times; 120        | 15               | 65                                     | 130                                    |
     | 120 &times; 120        | 15               | 50                                     | 100                                    |
     | 320 &times; 180        | 15               | 140                                    | 280                                    |
     | 180 &times; 180        | 15               | 100                                    | 200                                    |
     | 240 &times; 180        | 15               | 120                                    | 240                                    |
     | 320 &times; 240        | 15               | 200                                    | 400                                    |
     | 240 &times; 240        | 15               | 140                                    | 280                                    |
     | 424 &times; 240        | 15               | 220                                    | 440                                    |
     | 640 &times; 360        | 15               | 400                                    | 800                                    |
     | 360 &times; 360        | 15               | 260                                    | 520                                    |
     | 640 &times; 360        | 30               | 600                                    | 1200                                   |
     | 360 &times; 360        | 30               | 400                                    | 800                                    |
     | 480 &times; 360        | 15               | 320                                    | 640                                    |
     | 480 &times; 360        | 30               | 490                                    | 980                                    |
     | 640 &times; 480        | 15               | 500                                    | 1000                                   |
     | 480 &times; 480        | 15               | 400                                    | 800                                    |
     | 640 &times; 480        | 30               | 750                                    | 1500                                   |
     | 480 &times; 480        | 30               | 600                                    | 1200                                   |
     | 848 &times; 480        | 15               | 610                                    | 1220                                   |
     | 848 &times; 480        | 30               | 930                                    | 1860                                   |
     | 640 &times; 480        | 10               | 400                                    | 800                                    |
     | 1280 &times; 720       | 15               | 1130                                   | 2260                                   |
     | 1280 &times; 720       | 30               | 1710                                   | 3420                                   |
     | 960 &times; 720        | 15               | 910                                    | 1820                                   |
     | 960 &times; 720        | 30               | 1380                                   | 2760                                   |
     | 1920 &times; 1080      | 15               | 2080                                   | 4160                                   |
     | 1920 &times; 1080      | 30               | 3150                                   | 6300                                   |
     | 1920 &times; 1080      | 60               | 4780                                   | 6500                                   |
     | 2560 &times; 1440      | 30               | 4850                                   | 6500                                   |
     | 2560 &times; 1440      | 60               | 6500                                   | 6500                                   |
     | 3840 &times; 2160      | 30               | 6500                                   | 6500                                   |
     | 3840 &times; 2160      | 60               | 6500                                   | 6500                                   |

     */
    int bitrate;
    /** The minimum encoding bitrate (Kbps).

     The SDK automatically adjusts the encoding bitrate to adapt to the network conditions. Using a value greater than the default value forces the video encoder to output high-quality images but may cause more packet loss and hence sacrifice the smoothness of the video transmission. That said, unless you have special requirements for image quality, Aopa does not recommend changing this value.

     @note This parameter applies only to the Live-broadcast profile.
     */
    int minBitrate;
    /** The video orientation mode of the video: #ORIENTATION_MODE.
    */
    ORIENTATION_MODE orientationMode;
    /** The video encoding degradation preference under limited bandwidth: #DEGRADATION_PREFERENCE.
     */
    DEGRADATION_PREFERENCE degradationPreference;
    /** Sets the mirror mode of the published local video stream. It only affects the video that the remote user sees. See #VIDEO_MIRROR_MODE_TYPE

    @note: The SDK disables the mirror mode by default.
    */
    VIDEO_MIRROR_MODE_TYPE mirrorMode;

    VideoEncoderConfiguration(
        const VideoDimensions& d, FRAME_RATE f,
        int b, ORIENTATION_MODE m, VIDEO_MIRROR_MODE_TYPE mr = VIDEO_MIRROR_MODE_AUTO)
        : dimensions(d), frameRate(f), minFrameRate(-1), bitrate(b),
          minBitrate(DEFAULT_MIN_BITRATE), orientationMode(m),
          degradationPreference(MAINTAIN_QUALITY), mirrorMode(mr)
    {}
    VideoEncoderConfiguration(
        int width, int height, FRAME_RATE f,
        int b, ORIENTATION_MODE m, VIDEO_MIRROR_MODE_TYPE mr = VIDEO_MIRROR_MODE_AUTO)
        : dimensions(width, height), frameRate(f),
          minFrameRate(-1), bitrate(b),
          minBitrate(DEFAULT_MIN_BITRATE), orientationMode(m),
          degradationPreference(MAINTAIN_QUALITY), mirrorMode(mr)
    {}
    VideoEncoderConfiguration()
        : dimensions(640, 480)
        , frameRate(FRAME_RATE_FPS_15)
        , minFrameRate(-1)
        , bitrate(STANDARD_BITRATE)
        , minBitrate(DEFAULT_MIN_BITRATE)
        , orientationMode(ORIENTATION_MODE_ADAPTIVE)
        , degradationPreference(MAINTAIN_FRAMERATE)
        , mirrorMode(VIDEO_MIRROR_MODE_DISABLED)
    {}
};

/** The video properties of the user displaying the video in the CDN live. Aopa supports a maximum of 17 transcoding users in a CDN streaming channel.
*/
typedef struct TranscodingUser {
  /** User ID of the user displaying the video in the CDN live.
  */
    uid_t uid;

/** Horizontal position (pixel) of the video frame relative to the top left corner.
*/
    int x;
    /** Vertical position (pixel) of the video frame relative to the top left corner.
    */
    int y;
    /** Width (pixel) of the video frame. The default value is 360.
    */
    int width;
    /** Height (pixel) of the video frame. The default value is 640.
    */
    int height;

    /** Layer position of the video frame. The value ranges between 0 and 100.

     - 0: (Default) Lowest
     - 100: Highest

     @note
     - If zOrder is beyond this range, the SDK reports #ERR_INVALID_ARGUMENT.
     - As of v2.3, the SDK supports zOrder = 0.
     */
    int zOrder;
    /**  Transparency of the video frame in CDN live. The value ranges between 0 and 1.0:

     - 0: Completely transparent
     - 1.0: (Default) Opaque
     */
    double alpha;
    /** The audio channel of the sound. The default value is 0:

     - 0: (Default) Supports dual channels at most, depending on the upstream of the broadcaster.
     - 1: The audio stream of the broadcaster uses the FL audio channel. If the upstream of the broadcaster uses multiple audio channels, these channels are mixed into mono first.
     - 2: The audio stream of the broadcaster uses the FC audio channel. If the upstream of the broadcaster uses multiple audio channels, these channels are mixed into mono first.
     - 3: The audio stream of the broadcaster uses the FR audio channel. If the upstream of the broadcaster uses multiple audio channels, these channels are mixed into mono first.
     - 4: The audio stream of the broadcaster uses the BL audio channel. If the upstream of the broadcaster uses multiple audio channels, these channels are mixed into mono first.
     - 5: The audio stream of the broadcaster uses the BR audio channel. If the upstream of the broadcaster uses multiple audio channels, these channels are mixed into mono first.

     @note If your setting is not 0, you may need a specialized player.
     */
    int audioChannel;
    TranscodingUser()
        : uid(0)
        , x(0)
        , y(0)
        , width(0)
        , height(0)
        , zOrder(0)
        , alpha(1.0)
        , audioChannel(0)
    {}

} TranscodingUser;

/** Image properties.

 The properties of the watermark and background images.
 */
typedef struct RtcImage {
    RtcImage() :
       url(NULL),
       x(0),
       y(0),
       width(0),
       height(0)
    {}
    /** HTTP/HTTPS URL address of the image on the broadcasting video. The maximum length of this parameter is 1024 bytes. */
    const char* url;
    /** Horizontal position of the image from the upper left of the broadcasting video. */
    int x;
    /** Vertical position of the image from the upper left of the broadcasting video. */
    int y;
    /** Width of the image on the broadcasting video. */
    int width;
    /** Height of the image on the broadcasting video. */
    int height;
} RtcImage;

/** A struct for managing CDN live audio/video transcoding settings.
*/
typedef struct LiveTranscoding {
  /** Width of the video. The default value is 360.
   * - If you push video streams to the CDN, set the value of width &times; height to at least 64 &times; 64 (px), or the SDK will adjust it to 64 &times; 64 (px).
   * - If you push audio streams to the CDN, set the value of width &times; height to 0 &times; 0 (px).
   */
    int width;
    /** Height of the video. The default value is 640.
     * - If you push video streams to the CDN, set the value of width &times; height to at least 64 &times; 64 (px), or the SDK will adjust it to 64 &times; 64 (px).
     * - If you push audio streams to the CDN, set the value of width &times; height to 0 &times; 0 (px).
    */
    int height;
    /** Bitrate of the CDN live output video stream. The default value is 400 Kbps.

    Set this parameter according to the Video Bitrate Table. If you set a bitrate beyond the proper range, the SDK automatically adapts it to a value within the range.
    */
    int videoBitrate;
    /** Frame rate of the output video stream set for the CDN live broadcast. The default value is 15 fps, and the value range is (0,30].

    @note Aopa adjusts all values over 30 to 30.
    */
    int videoFramerate;

    /** **DEPRECATED** Latency mode:

     - true: Low latency with unassured quality.
     - false: (Default) High latency with assured quality.
     */
    bool lowLatency;

    /** Video GOP in frames. The default value is 30 fps.
    */
    int videoGop;
    /** Self-defined video codec profile: #VIDEO_CODEC_PROFILE_TYPE.

    @note If you set this parameter to other values, Aopa adjusts it to the default value of 100.
    */
    VIDEO_CODEC_PROFILE_TYPE videoCodecProfile;
    /** The background color in RGB hex value. Value only, do not include a #. For example, 0xFFB6C1 (light pink). The default value is 0x000000 (black).
     */
    unsigned int backgroundColor;
    /** The number of users in the live broadcast.
     */
    unsigned int userCount;
    /** TranscodingUser
    */
    TranscodingUser *transcodingUsers;
    /** Reserved property. Extra user-defined information to send SEI for the H.264/H.265 video stream to the CDN live client. Maximum length: 4096 Bytes.

     For more information on SEI frame, see [SEI-related questions](https://docs.bb.io/en/faq/sei).
     */
    const char *transcodingExtraInfo;

    /** **DEPRECATED** The metadata sent to the CDN live client defined by the RTMP or FLV metadata.
     */
    const char *metadata;
    /** The watermark image added to the CDN live publishing stream.

    Ensure that the format of the image is PNG. Once a watermark image is added, the audience of the CDN live publishing stream can see the watermark image. See RtcImage.
    */
    RtcImage* watermark;
    /** The background image added to the CDN live publishing stream.

     Once a background image is added, the audience of the CDN live publishing stream can see the background image. See RtcImage.
    */
    RtcImage* backgroundImage;
    /** Self-defined audio-sample rate: #AUDIO_SAMPLE_RATE_TYPE.
    */
    AUDIO_SAMPLE_RATE_TYPE audioSampleRate;
    /** Bitrate of the CDN live audio output stream. The default value is 48 Kbps, and the highest value is 128.
     */
    int audioBitrate;
    /** Aopa's self-defined audio-channel types. We recommend choosing option 1 or 2. A special player is required if you choose option 3, 4, or 5:

     - 1: (Default) Mono
     - 2: Two-channel stereo
     - 3: Three-channel stereo
     - 4: Four-channel stereo
     - 5: Five-channel stereo
     */
    int audioChannels;
    /** Self-defined audio codec profile: #AUDIO_CODEC_PROFILE_TYPE.
     */

    AUDIO_CODEC_PROFILE_TYPE audioCodecProfile;


    LiveTranscoding()
        : width(360)
        , height(640)
        , videoBitrate(400)
        , videoFramerate(15)
        , lowLatency(false)
        , videoGop(30)
        , videoCodecProfile(VIDEO_CODEC_PROFILE_HIGH)
        , backgroundColor(0x000000)
        , userCount(0)
        , transcodingUsers(NULL)
        , transcodingExtraInfo(NULL)
        , metadata(NULL)
        , watermark(NULL)
        , backgroundImage(NULL)
        , audioSampleRate(AUDIO_SAMPLE_RATE_48000)
        , audioBitrate(48)
        , audioChannels(1)
        , audioCodecProfile(AUDIO_CODEC_PROFILE_LC_AAC)
    {}
} LiveTranscoding;

 /** Camera capturer configuration.
  */
 struct CameraCapturerConfiguration{
    /** Camera capturer preference settings. See: #CAPTURER_OUTPUT_PREFERENCE. */
    CAPTURER_OUTPUT_PREFERENCE preference;
    /** The width (px) of the video image captured by the local camera.
     * To customize the width of the video image, set `preference` as #CAPTURER_OUTPUT_PREFERENCE_MANUAL (3) first,
     * and then use `captureWidth`.
     */
    int captureWidth;
    /** The height (px) of the video image captured by the local camera.
     * To customize the height of the video image, set `preference` as #CAPTURER_OUTPUT_PREFERENCE_MANUAL (3) first,
     * and then use `captureHeight`.
     */
    int captureHeight;
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
    /** Camera direction settings (for Android/iOS only). See: #CAMERA_DIRECTION. */
    CAMERA_DIRECTION cameraDirection;
#endif

    CameraCapturerConfiguration() : preference(CAPTURER_OUTPUT_PREFERENCE_AUTO), captureWidth(640), captureHeight(480) {}

    CameraCapturerConfiguration(int width, int height) : preference(CAPTURER_OUTPUT_PREFERENCE_MANUAL), captureWidth(width), captureHeight(height) {}
 };

/** Configuration of the imported live broadcast voice or video stream.
 */
struct InjectStreamConfig {
    /** Width of the added stream in the live broadcast. The default value is 0 (same width as the original stream).
     */
    int width;
    /** Height of the added stream in the live broadcast. The default value is 0 (same height as the original stream).
     */
    int height;
    /** Video GOP of the added stream in the live broadcast in frames. The default value is 30 fps.
     */
    int videoGop;
    /** Video frame rate of the added stream in the live broadcast. The default value is 15 fps.
     */
    int videoFramerate;
    /** Video bitrate of the added stream in the live broadcast. The default value is 400 Kbps.

     @note The setting of the video bitrate is closely linked to the resolution. If the video bitrate you set is beyond a reasonable range, the SDK sets it within a reasonable range.
     */
    int videoBitrate;
    /** Audio-sample rate of the added stream in the live broadcast: #AUDIO_SAMPLE_RATE_TYPE. The default value is 48000 Hz.

     @note We recommend setting the default value.
     */
    AUDIO_SAMPLE_RATE_TYPE audioSampleRate;
    /** Audio bitrate of the added stream in the live broadcast. The default value is 48.

     @note We recommend setting the default value.
     */
    int audioBitrate;
    /** Audio channels in the live broadcast.

     - 1: (Default) Mono
     - 2: Two-channel stereo

     @note We recommend setting the default value.
     */
    int audioChannels;

    // width / height default set to 0 means pull the stream with its original resolution
    InjectStreamConfig()
        : width(0)
        , height(0)
        , videoGop(30)
        , videoFramerate(15)
        , videoBitrate(400)
        , audioSampleRate(AUDIO_SAMPLE_RATE_48000)
        , audioBitrate(48)
        , audioChannels(1)
    {}
};
/** The definition of ChannelMediaInfo.
 */
struct ChannelMediaInfo {
    /** The channel name.
     */
    const char* channelName;
    /** The token that enables the user to join the channel.
     */
    const char* token;
    /** The user ID.
     */
    uid_t uid;
};

/** The definition of ChannelMediaRelayConfiguration.
 */
struct ChannelMediaRelayConfiguration {
    /** Pointer to the information of the source channel: ChannelMediaInfo. It contains the following members:
     * - `channelName`: The name of the source channel. The default value is `NULL`, which means the SDK applies the name of the current channel.
     * - `uid`: ID of the broadcaster whose media stream you want to relay. The default value is 0, which means the SDK generates a random UID. You must set it as 0.
     * - `token`: The token for joining the source channel. It is generated with the `channelName` and `uid` you set in `srcInfo`.
     *   - If you have not enabled the App Certificate, set this parameter as the default value `NULL`, which means the SDK applies the App ID.
     *   - If you have enabled the App Certificate, you must use the `token` generated with the `channelName` and `uid`, and the `uid` must be set as 0.
     */
    ChannelMediaInfo *srcInfo;
    /** Pointer to the information of the destination channel: ChannelMediaInfo. It contains the following members:
     * - `channelName`: The name of the destination channel.
     * - `uid`: ID of the broadcaster in the destination channel. The value ranges from 0 to (2<sup>32</sup>-1). To avoid UID conflicts, this `uid` must be different from any other UIDs in the destination channel. The default value is 0, which means the SDK generates a random UID.
     * - `token`: The token for joining the destination channel. It is generated with the `channelName` and `uid` you set in `destInfos`.
     *   - If you have not enabled the App Certificate, set this parameter as the default value `NULL`, which means the SDK applies the App ID.
     *   - If you have enabled the App Certificate, you must use the `token` generated with the `channelName` and `uid`.
     */
    ChannelMediaInfo *destInfos;
    /** The number of destination channels. The default value is 0, and the
     * value range is [0,4). Ensure that the value of this parameter
     * corresponds to the number of ChannelMediaInfo structs you define in
     * `destInfos`.
     */
    int destCount;

    ChannelMediaRelayConfiguration()
            : srcInfo(nullptr)
            , destInfos(nullptr)
            , destCount(0)
    {}
};

/** Content hints for screen sharing.
*/
enum VideoContentHint
{
    /** (Default) No content hint.
     */
    CONTENT_HINT_NONE,
    /** Motion-intensive content. Choose this option if you prefer smoothness or when you are sharing a video clip, movie, or video game.
     */
    CONTENT_HINT_MOTION,
    /** Motionless content. Choose this option if you prefer sharpness or when you are sharing a picture, PowerPoint slide, or text.
     */
    CONTENT_HINT_DETAILS
};

/** Video display settings of the VideoCanvas class.
*/
struct VideoCanvas
{
    /** Video display window (view).
     */
    view_t view;
    /** The rendering mode of the video view. See RENDER_MODE_TYPE
     */
    int renderMode;
    /** The unique channel name for the AopaRTC session in the string format. The string length must be less than 64 bytes. Supported character scopes are:
     - All lowercase English letters: a to z.
     - All uppercase English letters: A to Z.
     - All numeric characters: 0 to 9.
     - The space character.
     - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".

     @note
     - The default value is the empty string "". Use the default value if the user joins the channel using the \ref IRtcEngine::joinChannel "joinChannel" method in the IRtcEngine class. The `VideoCanvas` struct defines the video canvas of the user in the channel.
     - If the user joins the channel using the \ref IRtcEngine::joinChannel "joinChannel" method in the IChannel class, set this parameter as the `channelId` of the `IChannel` object. The `VideoCanvas` struct defines the video canvas of the user in the channel with the specified channel ID.
     */
    char channelId[MAX_CHANNEL_ID_LENGTH];
    /** The user ID. */
    uid_t uid;
    void *priv; // private data (underlying video engine denotes it)
    /** The mirror mode of the video view. See VIDEO_MIRROR_MODE_TYPE
     @note
     - For the mirror mode of the local video view: If you use a front camera, the SDK enables the mirror mode by default; if you use a rear camera, the SDK disables the mirror mode by default.
     - For the mirror mode of the remote video view: The SDK disables the mirror mode by default.
    */
    VIDEO_MIRROR_MODE_TYPE mirrorMode;

    VideoCanvas()
        : view(NULL)
        , renderMode(RENDER_MODE_HIDDEN)
        , uid(0)
        , priv(NULL)
        , mirrorMode(VIDEO_MIRROR_MODE_AUTO)
    {
        channelId[0] = '\0';
    }
    VideoCanvas(view_t v, int m, uid_t u)
        : view(v)
        , renderMode(m)
        , uid(u)
        , priv(NULL)
        , mirrorMode(VIDEO_MIRROR_MODE_AUTO)
    {
        channelId[0] = '\0';
    }
    VideoCanvas(view_t v, int m, const char *ch, uid_t u)
        : view(v)
        , renderMode(m)
        , uid(u)
        , priv(NULL)
        , mirrorMode(VIDEO_MIRROR_MODE_AUTO)
    {
        strncpy(channelId, ch, MAX_CHANNEL_ID_LENGTH);
        channelId[MAX_CHANNEL_ID_LENGTH - 1] = '\0';
    }
    VideoCanvas(view_t v, int rm, uid_t u, VIDEO_MIRROR_MODE_TYPE mm)
        : view(v)
        , renderMode(rm)
        , uid(u)
        , priv(NULL)
        , mirrorMode(mm)
    {
        channelId[0] = '\0';
    }
    VideoCanvas(view_t v, int rm, const char *ch, uid_t u, VIDEO_MIRROR_MODE_TYPE mm)
        : view(v)
        , renderMode(rm)
        , uid(u)
        , priv(NULL)
        , mirrorMode(mm)
    {
        strncpy(channelId, ch, MAX_CHANNEL_ID_LENGTH);
        channelId[MAX_CHANNEL_ID_LENGTH - 1] = '\0';
    }
};

/** Image enhancement options.
*/
struct BeautyOptions {
    /** The contrast level, used with the @p lightening parameter.
    */
    enum LIGHTENING_CONTRAST_LEVEL
    {
        /** Low contrast level. */
        LIGHTENING_CONTRAST_LOW = 0,
        /** (Default) Normal contrast level. */
        LIGHTENING_CONTRAST_NORMAL,
        /** High contrast level. */
        LIGHTENING_CONTRAST_HIGH
    };

/** The contrast level, used with the @p lightening parameter.
*/
LIGHTENING_CONTRAST_LEVEL lighteningContrastLevel;

/** The brightness level. The value ranges from 0.0 (original) to 1.0. */
float lighteningLevel;

/** The sharpness level. The value ranges between 0 (original) and 1. This parameter is usually used to remove blemishes.
 */
float smoothnessLevel;

/** The redness level. The value ranges between 0 (original) and 1. This parameter adjusts the red saturation level.
*/
float rednessLevel;

BeautyOptions(LIGHTENING_CONTRAST_LEVEL contrastLevel, float lightening, float smoothness, float redness)
    : lighteningLevel(lightening),
    smoothnessLevel(smoothness),
    rednessLevel(redness),
    lighteningContrastLevel(contrastLevel) {}

BeautyOptions()
    : lighteningLevel(0),
    smoothnessLevel(0),
    rednessLevel(0),
    lighteningContrastLevel(LIGHTENING_CONTRAST_NORMAL) {}
};

struct UserInfo {
  uid_t uid;
  char userAccount[MAX_USER_ACCOUNT_LENGTH];
  UserInfo()
      : uid(0) {
    userAccount[0] = '\0';
  }
};

struct LowLightEnhanceOptions {
  /**
   * The low-light enhancement mode.
   */
  enum LOW_LIGHT_ENHANCE_MODE {
    /** 0: (Default) Automatic mode. The SDK automatically enables or disables the low-light enhancement feature according to the ambient light to compensate for the lighting level or prevent overexposure, as necessary. */
    LOW_LIGHT_ENHANCE_AUTO = 0,
    /** Manual mode. Users need to enable or disable the low-light enhancement feature manually. */
    LOW_LIGHT_ENHANCE_MANUAL
  };
  /**
   * The low-light enhancement level.
   */
  enum LOW_LIGHT_ENHANCE_LEVEL {
    /**
     * 0: (Default) Promotes video quality during low-light enhancement. It processes the brightness, details, and noise of the video image. The performance consumption is moderate, the processing speed is moderate, and the overall video quality is optimal.
     */
    LOW_LIGHT_ENHANCE_LEVEL_HIGH_QUALITY = 0,
    /**
     * Promotes performance during low-light enhancement. It processes the brightness and details of the video image. The processing speed is faster.
     */
    LOW_LIGHT_ENHANCE_LEVEL_FAST
  };

  /** The low-light enhancement mode. See #LOW_LIGHT_ENHANCE_MODE.
   */
  LOW_LIGHT_ENHANCE_MODE mode;

  /** The low-light enhancement level. See #LOW_LIGHT_ENHANCE_LEVEL.
   */
  LOW_LIGHT_ENHANCE_LEVEL level;

  LowLightEnhanceOptions(LOW_LIGHT_ENHANCE_MODE lowlightMode, LOW_LIGHT_ENHANCE_LEVEL lowlightLevel) : mode(lowlightMode), level(lowlightLevel) {}

  LowLightEnhanceOptions() : mode(LOW_LIGHT_ENHANCE_AUTO), level(LOW_LIGHT_ENHANCE_LEVEL_HIGH_QUALITY) {}
};
/**
 * The video noise reduction options.
 *
 * @since v3.6.2
 */
struct VideoDenoiserOptions {
  /** The video noise reduction mode.
   */
  enum VIDEO_DENOISER_MODE {
    /** 0: (Default) Automatic mode. The SDK automatically enables or disables the video noise reduction feature according to the ambient light. */
    VIDEO_DENOISER_AUTO = 0,
    /** Manual mode. Users need to enable or disable the video noise reduction feature manually. */
    VIDEO_DENOISER_MANUAL
  };
  /**
   * The video noise reduction level.
   */
  enum VIDEO_DENOISER_LEVEL {
    /**
     * 0: (Default) Promotes video quality during video noise reduction. `HIGH_QUALITY` balances performance consumption and video noise reduction quality.
     * The performance consumption is moderate, the video noise reduction speed is moderate, and the overall video quality is optimal.
     */
    VIDEO_DENOISER_LEVEL_HIGH_QUALITY = 0,
    /**
     * Promotes reducing performance consumption during video noise reduction. `FAST` prioritizes reducing performance consumption over video noise reduction quality.
     * The performance consumption is lower, and the video noise reduction speed is faster. To avoid a noticeable shadowing effect (shadows trailing behind moving objects) in the processed video, Aopa recommends that you use `FAST` when the camera is fixed.
     */
    VIDEO_DENOISER_LEVEL_FAST,
    /**
     * Enhanced video noise reduction. `STRENGTH` prioritizes video noise reduction quality over reducing performance consumption.
     * The performance consumption is higher, the video noise reduction speed is slower, and the video noise reduction quality is better.
     * If `HIGH_QUALITY` is not enough for your video noise reduction needs, you can use `STRENGTH`.
     */
    VIDEO_DENOISER_LEVEL_STRENGTH
  };
  /** The video noise reduction mode. See #VIDEO_DENOISER_MODE.
   */
  VIDEO_DENOISER_MODE mode;

  /** The video noise reduction level. See #VIDEO_DENOISER_LEVEL.
   */
  VIDEO_DENOISER_LEVEL level;

  VideoDenoiserOptions(VIDEO_DENOISER_MODE denoiserMode, VIDEO_DENOISER_LEVEL denoiserLevel) : mode(denoiserMode), level(denoiserLevel) {}

  VideoDenoiserOptions() : mode(VIDEO_DENOISER_AUTO), level(VIDEO_DENOISER_LEVEL_HIGH_QUALITY) {}
};

/** The color enhancement options.
 *
 * @since v3.6.2
 */
struct ColorEnhanceOptions {
  /** The level of color enhancement. The value range is [0.0,1.0]. `0.0` is the default value, which means no color enhancement is applied to the video. The higher the value, the higher the level of color enhancement.
   */
  float strengthLevel;

  /** The level of skin tone protection. The value range is [0.0,1.0]. `0.0` means no skin tone protection. The higher the value, the higher the level of skin tone protection.
   * The default value is `1.0`. When the level of color enhancement is higher, the portrait skin tone can be significantly distorted, so you need to set the level of skin tone protection; when the level of skin tone protection is higher, the color enhancement effect can be slightly reduced.
   * Therefore, to get the best color enhancement effect, Aopa recommends that you adjust `strengthLevel` and `skinProtectLevel` to get the most appropriate values.
   */
  float skinProtectLevel;

  ColorEnhanceOptions(float stength, float skinProtect) : strengthLevel(stength), skinProtectLevel(skinProtect) {}

  ColorEnhanceOptions() : strengthLevel(0), skinProtectLevel(1) {}
};

/** The custom background image.
 *
 * @since v3.4.5
 */
struct VirtualBackgroundSource {
  /** The type of the custom background image.
   *
   * @since v3.4.5
   */
  enum BACKGROUND_SOURCE_TYPE {
    /**
     * 1: (Default) The background image is a solid color.
     */
    BACKGROUND_COLOR = 1,
    /**
     * The background image is a file in PNG or JPG format.
     */
    BACKGROUND_IMG,
    /**
     * The background image is blurred.
     *
     * @since v3.5.1
     */
    BACKGROUND_BLUR,
  };

  /**
   * The degree of blurring applied to the custom background image.
   *
   * @since v3.5.1
   */
  enum BACKGROUND_BLUR_DEGREE {
    /**
     * 1: The degree of blurring applied to the custom background image is low.
     * The user can almost see the background clearly.
     */
    BLUR_DEGREE_LOW = 1,
    /**
     * The degree of blurring applied to the custom background image is medium.
     * It is difficult for the user to recognize details in the background.
     */
    BLUR_DEGREE_MEDIUM,
    /**
     * (Default) The degree of blurring applied to the custom background image is high.
     * The user can barely see any distinguishing features in the background.
     */
    BLUR_DEGREE_HIGH,
  };

  /** The type of the custom background image. See #BACKGROUND_SOURCE_TYPE.
   */
  BACKGROUND_SOURCE_TYPE background_source_type;

  /**
   * The color of the custom background image. The format is a hexadecimal integer defined by RGB, without the # sign,
   * such as 0xFFB6C1 for light pink. The default value is 0xFFFFFF, which signifies white. The value range
   * is [0x000000,0xFFFFFF]. If the value is invalid, the SDK replaces the original background image with a white
   * background image.
   *
   * @note This parameter takes effect only when the type of the custom background image is `BACKGROUND_COLOR`.
   */
  unsigned int color;

  /**
   * The local absolute path of the custom background image. PNG and JPG formats are supported. If the path is invalid,
   * the SDK replaces the original background image with a white background image.
   *
   * @note This parameter takes effect only when the type of the custom background image is `BACKGROUND_IMG`.
   */
  const char* source;

  /**
   * The degree of blurring applied to the custom background image. See #BACKGROUND_BLUR_DEGREE.
   *
   * @note This parameter takes effect only when the type of the custom background image is `BACKGROUND_BLUR`.
   *
   * @since v3.5.1
   */
  BACKGROUND_BLUR_DEGREE blur_degree;

  VirtualBackgroundSource() : color(0xffffff), source(NULL), background_source_type(BACKGROUND_COLOR), blur_degree(BLUR_DEGREE_HIGH) {}
};

#if defined(_WIN32)
/** The capture type of the custom video source.
 */
enum VIDEO_CAPTURE_TYPE {
    /** Unknown type.
     */
    VIDEO_CAPTURE_UNKNOWN,
    /** (Default) Video captured by the camera.
     */
    VIDEO_CAPTURE_CAMERA,
    /** Video for screen sharing.
     */
    VIDEO_CAPTURE_SCREEN,
};

/** The IVideoFrameConsumer class. The SDK uses it to receive the video frame that you capture.
 */
class IVideoFrameConsumer {
public:
    /** Receives the raw video frame.
     *
     * @note Ensure that the video frame type that you specify in this method is the same as that in the \ref bbrtc::IVideoSource::getBufferType "getBufferType" callback.
     *
     * @param buffer The video buffer.
     * @param frameType The video frame type. See \ref bbrtc::media::ExternalVideoFrame::VIDEO_PIXEL_FORMAT "VIDEO_PIXEL_FORMAT".
     * @param width The width (px) of the video frame.
     * @param height The height (px) of the video frame.
     * @param rotation The angle (degree) at which the video frame rotates clockwise. If you set the rotation angle, the
     * SDK rotates the video frame after receiving it. You can set the rotation angle as `0`, `90`, `180`, and `270`.
     * @param timestamp The Unix timestamp (ms) of the video frame. You must set a timestamp for each video frame.
     */
    virtual void consumeRawVideoFrame(const unsigned char* buffer, bbrtc::media::ExternalVideoFrame::VIDEO_PIXEL_FORMAT frameType, int width, int height, int rotation, long timestamp) = 0;
};

/** The IVideoSource class. You can use it to customize the video source.
 */
class IVideoSource {
public:
    /** Notification for initializing the custom video source.
     *
     * The SDK triggers this callback to remind you to initialize the custom video source. After receiving this callback,
     * you can do some preparation, such as enabling the camera, and then use the return value to tell the SDK whether the
     * custom video source is prepared.
     *
     * @param consumer An IVideoFrameConsumer object that the SDK passes to you. You need to reserve this object and use it
     * to send the video frame to the SDK once the custom video source is started. See IVideoFrameConsumer.
     *
     * @return
     * - true: The custom video source is initialized.
     * - false: The custom video source is not ready or fails to initialize. The SDK stops and reports the error.
     */
    virtual bool onInitialize(IVideoFrameConsumer* consumer) = 0;

    /** Notification for disabling the custom video source.
     *
     * The SDK triggers this callback to remind you to disable the custom video source device. This callback tells you
     * that the SDK is about to release the IVideoFrameConsumer object. Ensure that you no longer use IVideoFrameConsumer
     * after receiving this callback.
     */
    virtual void onDispose() = 0;

    /** Notification for starting the custom video source.
     *
     * The SDK triggers this callback to remind you to start the custom video source for capturing video. The SDK uses
     * IVideoFrameConsumer to receive the video frame that you capture after the video source is started. You must use
     * the return value to tell the SDK whether the custom video source is started.
     *
     * @return
     * - true: The custom video source is started.
     * - false: The custom video source fails to start. The SDK stops and reports the error.
     */
    virtual bool onStart() = 0;

    /** Notification for stopping capturing video.
     *
     * The SDK triggers this callback to remind you to stop capturing video. This callback tells you that the SDK is about
     * to stop using IVideoFrameConsumer to receive the video frame that you capture.
     */
    virtual void onStop() = 0;

    /** Gets the video frame type.
     *
     * Before you initialize the custom video source, the SDK triggers this callback to query the video frame type. You
     * must specify the video frame type in the return value and then pass it to the SDK.
     *
     * @note Ensure that the video frame type that you specify in this callback is the same as that in the \ref bbrtc::IVideoFrameConsumer::consumeRawVideoFrame "consumeRawVideoFrame" method.
     *
     * @return \ref bbrtc::media::ExternalVideoFrame::VIDEO_PIXEL_FORMAT "VIDEO_PIXEL_FORMAT"
     */
    virtual bbrtc::media::ExternalVideoFrame::VIDEO_PIXEL_FORMAT getBufferType() = 0;
    /** Gets the capture type of the custom video source.
     *
     * Before you initialize the custom video source, the SDK triggers this callback to query the capture type of the video source.
     * You must specify the capture type in the return value and then pass it to the SDK. The SDK enables the corresponding video
     * processing algorithm according to the capture type after receiving the video frame.
     *
     * @return #VIDEO_CAPTURE_TYPE
     */
    virtual VIDEO_CAPTURE_TYPE getVideoCaptureType() = 0;
    /** Gets the content hint of the custom video source.
     *
     * If you specify the custom video source as a screen-sharing video, the SDK triggers this callback to query the
     * content hint of the video source before you initialize the video source. You must specify the content hint in the
     * return value and then pass it to the SDK. The SDK enables the corresponding video processing algorithm according
     * to the content hint after receiving the video frame.
     *
     * @return \ref Aopa::rtc::VideoContentHint "VideoContentHint"
     */
    virtual VideoContentHint getVideoContentHint() = 0;
};
#endif

/** The SDK uses the IRtcEngineEventHandler interface class to send callbacks to the application. The application inherits the methods of this interface class to retrieve these callbacks.

 All methods in this interface class have default (empty) implementations. Therefore, the application can only inherit some required events. In the callbacks, avoid time-consuming tasks or calling blocking APIs, such as the SendMessage method. Otherwise, the SDK may not work properly.
 */
class IRtcEngineEventHandler
{
public:
    virtual ~IRtcEngineEventHandler() {}
    
    /**
     * Reports a warning during SDK operation.
     *
     * Applications can typically ignore SDK warnings, as the SDK attempts to self-correct or recover from issues. For instance, a #WARN_LOOKUP_CHANNEL_TIMEOUT might be followed by an automatic reconnection attempt.
     *
     * @param warn The warning code indicating the type of issue encountered.
     * @param msg A pointer to a string describing the warning in detail.
     */
    virtual void onWarning(int warn, const char* msg) {
        (void)warn;
        (void)msg;
    }

    /**
     * Reports an error during SDK operation.
     *
     * Errors require application intervention or user notification, as the SDK cannot recover automatically. For example, an #ERR_START_CALL error necessitates informing the user and potentially invoking \ref IRtcEngine::leaveChannel "leaveChannel".
     *
     * @param err The error code identifying the specific issue.
     * @param msg A pointer to a string providing further context about the error.
     */
    virtual void onError(int err, const char* msg) {
        (void)err;
        (void)msg;
    }

    /**
     * Notifies when a user successfully joins a channel.
     *
     * This callback signifies that a user has entered a channel after \ref IRtcEngine::joinChannel "joinChannel" was called. The channel name corresponds to the one provided in the join request, and if no user ID was specified, the server assigns one.
     *
     * @param channel Pointer to the name of the channel joined.
     * @param uid The unique user ID assigned to the joining user.
     * @param elapsed Time in milliseconds from the join request until this callback.
     */
    virtual void onJoinChannelSuccess(const char* channel, uid_t uid, int elapsed) {
        (void)channel;
        (void)uid;
        (void)elapsed;
    }

    /**
     * Triggers upon a user successfully rejoining a channel after a network disruption.
     *
     * Following a network interruption, the SDK automatically attempts to reconnect and invokes this callback upon success.
     *
     * @param channel Pointer to the name of the channel rejoined.
     * @param uid The unique user ID of the rejoining user.
     * @param elapsed Time in milliseconds from the start of reconnection efforts until this callback.
     */
    virtual void onRejoinChannelSuccess(const char* channel, uid_t uid, int elapsed) {
        (void)channel;
        (void)uid;
        (void)elapsed;
    }

    /**
     * Indicates when a user leaves a channel.
     *
     * This callback delivers channel statistics upon a user exiting via \ref IRtcEngine::leaveChannel "leaveChannel".
     *
     * @param stats A reference to the \ref RtcStats structure containing call duration and other metrics.
     */
    virtual void onLeaveChannel(const RtcStats& stats) {
        (void)stats;
    }

    /**
     * Informs of a change in user role within a live broadcast (e.g., from broadcaster to audience).
     *
     * Triggered when the local user's role changes via \ref IRtcEngine::setClientRole "setClientRole", after joining a channel.
     *
     * @param oldRole The previous role of the user.
     * @param newRole The updated role of the user.
     */
    virtual void onClientRoleChanged(CLIENT_ROLE_TYPE oldRole, CLIENT_ROLE_TYPE newRole) {
    }

    /**
     * Reports a change in the chorus role within a KTV session.
     *
     * Activated by \ref IRtcEngine::setChorusRole "setChorusRole". Only applicable to users in the #CLIENT_ROLE_BROADCASTER role.
     *
     * @param oldRole Previous chorus role of the user.
     * @param newRole New chorus role of the user.
     */
    virtual void onChorusRoleChanged(CLIENT_ROLE_CHORUS_TYPE oldRole, CLIENT_ROLE_CHORUS_TYPE newRole) {
    }

    /**
     * Alerts when another user (in Communication) or host (in Live Broadcast) enters the channel.
     *
     * - Communication scenario: Notifies of any new user joining.
     * - Live Broadcast scenario: Specifically indicates a new host joining, with a recommendation to limit hosts to 17.
     *
     * Triggers in scenarios such as a user joining, role switching to host post-join, rejoining after a disconnect, or when a host adds an online media stream.
     *
     * @param uid The unique user ID of the joining/host user.
     * @param elapsed Time in milliseconds from the local user's join request until this callback.
     */
    virtual void onUserJoined(uid_t uid, int elapsed) {
        (void)uid;
        (void)elapsed;
    }

    /**
     * Signals when a remote user/host exits the channel or goes offline.
     *
     * Reasons for a user being offline include voluntary channel departure or network disconnection. False positives may arise due to unreliable networks, hence a signaling system is advisable for accurate offline detection.
     *
     * @param uid The unique user ID of the offline user/host.
     * @param reason The #USER_OFFLINE_REASON_TYPE explaining the offline status.
     */
    virtual void onUserOffline(uid_t uid, USER_OFFLINE_REASON_TYPE reason) {
        (void)uid;
        (void)reason;
    }

    /**
     * Periodically updates (every 2 seconds) the last-mile network quality before a user joins a channel.
     *
     * Reflects the uplink and downlink conditions between the local device and Aopa's edge server, following a call to \ref IRtcEngine::enableLastmileTest "enableLastmileTest".
     *
     * @param quality The network quality level as defined by #QUALITY_TYPE.
     */
    virtual void onLastmileQuality(int quality) {
        (void)quality;
    }

    // ===================================================================================
    // Event Handler Interface for Aopa Real-Time Communication (RTC) Engine
    // ===================================================================================

    /** 
     * @brief [DEPRECATED] Notifies when the connection between the SDK and server is interrupted.
     *
     * @deprecated Since v2.3.2, use \ref bb::rtc::IRtcEngineEventHandler::onConnectionStateChanged 
     *             with reason "CONNECTION_STATE_RECONNECTING" and cause "CONNECTION_CHANGED_INTERRUPTED".
     *
     * Triggered when the SDK disconnects from the server for over 4 seconds post-connection.
     * The SDK attempts to automatically reconnect after this event. Implement notifications 
     * or UI updates via this callback.
     *
     * Note: Differs from onConnectionLost in trigger conditions and timing.
     */
    virtual void onConnectionInterrupted() {}

    /** 
     * @brief Notifies when the SDK fails to reconnect to Aopa's edge server after a 10-second interruption.
     *
     * Triggered when reconnection efforts fail 10 seconds after initial disconnection, regardless 
     * of whether the client was in a channel or not.
     *
     * Note: This differs from onConnectionInterrupted in the duration before triggering and scenarios.
     */
    virtual void onConnectionLost() {}

    /** 
     * @brief [DEPRECATED] Notifies when the connection is banned by the Aopa server.
     *
     * @deprecated Replaced by \ref bb::rtc::IRtcEngineEventHandler::onConnectionStateChanged 
     *             with state "CONNECTION_STATE_FAILED" and reason "CONNECTION_CHANGED_BANNED_BY_SERVER".
     */
    virtual void onConnectionBanned() {}

    /** 
     * @brief Executes when an SDK method call finishes, providing error code and method details.
     *
     * @param err Error code indicating success (0) or failure.
     * @param apiPointer Pointer to the name of the executed SDK API method.
     * @param resultPointer Pointer to the result string of the executed method, if applicable.
     */
    virtual void onApiCallExecuted(int err, const char* apiPointer, const char* resultPointer) {
        (void)err;
        (void)apiPointer;
        (void)resultPointer;
    }

    /** 
     * @brief Triggers when the token used for authentication is about to expire or has expired.
     *
     * Requires the application to fetch and set a new token via renewToken to maintain session continuity.
     */
    virtual void onRequestToken() {}

    /** 
     * @brief Warns 30 seconds prior to token expiration to allow for proactive token renewal.
     *
     * @param tokenPointer Pointer to the token expiring soon.
     */
    virtual void onTokenPrivilegeWillExpire(const char* tokenPointer) {
        (void)tokenPointer;
    }

    /**
     * @brief [DEPRECATED] Reports the audio quality statistics for each remote user/host.
     *
     * @deprecated As of v2.3.2, use \ref bb::rtc::IRtcEngineEventHandler::onRemoteAudioStats "onRemoteAudioStats" instead.
     *
     * This callback is triggered every two seconds to provide audio quality metrics for each remote user/host transmitting audio in the channel. If multiple users are sending audio, the callback is fired accordingly for each one.
     *
     * @param uid Unique identifier of the remote user whose audio quality is being reported.
     * @param quality Audio quality metric based on #QUALITY_TYPE.
     * @param delay Network latency (in ms) from sender to receiver, inclusive of processing, transmission, and jitter buffer delays.
     * @param lost Packet loss rate (%) of audio packets during transmission from sender to receiver.
     */
    virtual void onAudioQuality(uid_t uid, int quality, unsigned short delay, unsigned short lost) {
        (void)uid;
        (void)quality;
        (void)delay;
        (void)lost;
    }

    /**
     * @brief Provides periodic statistics of the ongoing call.
     *
     * Triggered every two seconds following a successful channel join, delivering metrics on the RTC engine performance.
     *
     * @param stats Comprehensive statistics object for the RTC session: RtcStats.
     */
    virtual void onRtcStats(const RtcStats& stats) {
        (void)stats;
    }

    /**
     * @brief Periodically reports the last-mile network quality for each user in the channel.
     *
     * The 'last mile' pertains to the link between the local device and Aopa's edge server. This callback is issued every two seconds to update on the network conditions experienced by each participant. If multiple users are present, expect multiple invocations.
     *
     * @param uid Unique identifier of the user. If @p uid equals 0, it refers to the local user.
     * @param txQuality Uplink transmission quality assessment considering bitrate, packet loss, RTT, and jitter. Reflects suitability of current uplink for chosen video encoding settings. See #QUALITY_TYPE.
     * @param rxQuality Downlink network quality score based on packet loss, RTT, and jitter. Refer to #QUALITY_TYPE.
     */
    virtual void onNetworkQuality(uid_t uid, int txQuality, int rxQuality) {
        (void)uid;
        (void)txQuality;
        (void)rxQuality;
    }

    /**
     * @brief Updates the statistics of the local video stream every two seconds.
     *
     * This callback is for each local user/host and is called every two seconds. In multi-user scenarios, expect multiple invocations.
     *
     * @note If dual streaming is enabled via \ref bb::rtc::IRtcEngine::enableDualStream "enableDualStream", this callback reports on the high-quality video stream.
     *
     * @param stats Detailed metrics for the local video stream: LocalVideoStats.
     */
    virtual void onLocalVideoStats(const LocalVideoStats& stats) {
        (void)stats;
    }

    /**
     * @brief Reports statistics of the remote video stream every two seconds per user/host.
     *
     * For each remote participant in the channel, this callback is triggered every two seconds to deliver video stream stats. In multi-user channels, anticipate multiple callbacks.
     *
     * @param stats Object encapsulating remote video stream statistics: RemoteVideoStats.
     */
    virtual void onRemoteVideoStats(const RemoteVideoStats& stats) {
        (void)stats;
    }

    /**
     * @brief Delivers the local audio stream statistics every two seconds.
     *
     * This callback provides a periodic update on the local audio stream's performance.
     *
     * @param stats Metrics for the local audio stream: LocalAudioStats.
     */
    virtual void onLocalAudioStats(const LocalAudioStats& stats) {
        (void)stats;
    }

    /**
     * @brief Supplies statistics of the remote audio streams every two seconds.
     *
     * This callback supersedes \ref bb::rtc::IRtcEngineEventHandler::onAudioQuality "onAudioQuality". It is invoked every two seconds per remote user/host, with multiple calls in multi-participant channels.
     *
     * @param stats Array pointer to remote audio stream statistics objects: RemoteAudioStats.
     */
    virtual void onRemoteAudioStats(const RemoteAudioStats& stats) {
        (void)stats;
    }

    /**
     * @brief Indicates a change in the local audio state, such as recording or encoding issues.
     *
     * Helps diagnose issues by signaling state transitions in the local audio stream.
     *
     * @param state Current state of the local audio stream, see #LOCAL_AUDIO_STREAM_STATE.
     * @param error Specific error information if the state is #LOCAL_AUDIO_STREAM_STATE_FAILED (3).
     */
    virtual void onLocalAudioStateChanged(LOCAL_AUDIO_STREAM_STATE state, LOCAL_AUDIO_STREAM_ERROR error) {
        (void)state;
        (void)error;
    }

    /**
     * @brief Notifies when the remote audio state changes.
     *
     * Reflects changes in the remote user's audio stream state.
     *
     * @param uid Unique identifier of the remote user experiencing the audio state change.
     * @param state New state of the remote audio stream, see #REMOTE_AUDIO_STATE.
     * @param reason Reason behind the remote audio state change, see #REMOTE_AUDIO_STATE_REASON.
     * @param elapsed Time (in ms) since joining the channel until this callback is triggered.
     */
    virtual void onRemoteAudioStateChanged(uid_t uid, REMOTE_AUDIO_STATE state, REMOTE_AUDIO_STATE_REASON reason, int elapsed) {
        (void)uid;
        (void)state;
        (void)reason;
        (void)elapsed;
    }

    /**
     * @brief Notifies of changes in the audio publishing state.
     *
     * @since v3.1.0
     *
     * Signals state transitions in the publishing of the local audio stream.
     *
     * @param channel Name of the channel related to the publishing state change.
     * @param oldState Previous publishing state, refer to #STREAM_PUBLISH_STATE.
     * @param newState Current publishing state, refer to #STREAM_PUBLISH_STATE.
     * @param elapseSinceLastState Time (in ms) from the last state to the current one.
     */
    virtual void onAudioPublishStateChanged(const char* channel, STREAM_PUBLISH_STATE oldState, STREAM_PUBLISH_STATE newState, int elapseSinceLastState) {
        (void)channel;
        (void)oldState;
        (void)newState;
        (void)elapseSinceLastState;
    }

       /**
     * Reports the change in the local video publishing state.
     *
     * @param channel The identifier for the channel where the event occurs.
     * @param oldState The previous publishing state; refer to #STREAM_PUBLISH_STATE for details.
     * @param newState The current publishing state; refer to #STREAM_PUBLISH_STATE for details.
     * @param elapseSinceLastState The time in milliseconds from the last state to the current one.
     */
    virtual void onVideoPublishStateChanged(const char* channel, STREAM_PUBLISH_STATE oldState, STREAM_PUBLISH_STATE newState, int elapseSinceLastState) {
        // Currently, the implementation is a placeholder and ignores the parameters.
        (void)channel;
        (void)oldState;
        (void)newState;
        (void)elapseSinceLastState;
    }

    /**
     * Notifies about changes in the subscription state of a remote audio stream.
     *
     * @param channel The channel name where the event is happening.
     * @param uid The unique identifier of the remote user.
     * @param oldState The previous subscription state; refer to #STREAM_SUBSCRIBE_STATE for more information.
     * @param newState The current subscription state; refer to #STREAM_SUBSCRIBE_STATE for more information.
     * @param elapseSinceLastState Time in milliseconds since the last state change.
     */
    virtual void onAudioSubscribeStateChanged(const char* channel, uid_t uid, STREAM_SUBSCRIBE_STATE oldState, STREAM_SUBSCRIBE_STATE newState, int elapseSinceLastState) {
        // Placeholder implementation; actual logic should utilize the parameters.
        (void)channel;
        (void)uid;
        (void)oldState;
        (void)newState;
        (void)elapseSinceLastState;
    }

    /**
     * Notifies about changes in the subscription state of a remote video stream.
     *
     * @param channel The name of the channel.
     * @param uid Identifier of the remote user.
     * @param oldState Prior subscription state; refer to #STREAM_SUBSCRIBE_STATE for enumeration values.
     * @param newState Current subscription state; refer to #STREAM_SUBSCRIBE_STATE for enumeration values.
     * @param elapseSinceLastState Duration in milliseconds from the last state to the current one.
     */
    virtual void onVideoSubscribeStateChanged(const char* channel, uid_t uid, STREAM_SUBSCRIBE_STATE oldState, STREAM_SUBSCRIBE_STATE newState, int elapseSinceLastState) {
        // Function body intentionally left empty; parameters are not used.
        (void)channel;
        (void)uid;
        (void)oldState;
        (void)newState;
        (void)elapseSinceLastState;
    }

    /**
     * Provides information on active speakers, their volume levels, and the local user's speaking status.
     *
     * @param speakers Array of AudioVolumeInfo structures detailing speaker information.
     *                 For the local user, `uid`=0, `volume`=totalVolume (sum of voice and audio mixing volume), and `vad`=voice activity detection status.
     *                 For remote speakers, includes their `uid`, combined `volume`, and `vad`=0.
     *                 An empty array implies no remote speaker activity.
     * @param speakerNumber Total number of active speakers reported, ranging from 0 to 3.
     *                      Always 1 for the local user, regardless of speaking status.
     *                      For remote speakers, up to 3 loudest speakers are reported when more than 3 are present.
     * @param totalVolume The combined volume after audio mixing, ranging from 0 (silent) to 255 (loudest).
     *                    Represents local user's total volume in their callback, and total volume of all remote speakers otherwise.
     */
    virtual void onAudioVolumeIndication(const AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume) {
        // Placeholder; actual implementation should handle the provided parameters.
        (void)speakers;
        (void)speakerNumber;
        (void)totalVolume;
    }

    /**
     * Indicates whether the local user is actively speaking.
     *
     * @param localInfo Structure containing the local user's audio volume information.
     */
    virtual void onLocalAudioVolumeIndication(AudioVolumeInfo localInfo) {
        // Function body is a placeholder and currently disregards the input parameter.
        (void)localInfo;
    }

    /**
     * Identifies the loudest speaker in the channel.
     *
     * @param uid Unique identifier of the loudest speaker. A value of 0 signifies the local user.
     */
    virtual void onActiveSpeaker(uid_t uid) {
        // Placeholder; actual logic should consider the provided user ID.
        (void)uid;
    }

    /**
     * Triggers when the first local video frame is displayed.
     *
     * @param width Width of the video frame in pixels.
     * @param height Height of the video frame in pixels.
     * @param elapsed Time in milliseconds from invoking joinChannel or startPreview until this callback.
     */
    virtual void onFirstLocalVideoFrame(int width, int height, int elapsed) {
        // Placeholder; actual implementation would use width, height, and elapsed.
        (void)width;
        (void)height;
        (void)elapsed;
    }

    /**
     * Invoked when the first remote video frame is rendered.
     *
     * @param uid The remote user's ID who is sending the video stream.
     * @param width Width of the video frame in pixels.
     * @param height Height of the video stream in pixels.
     * @param elapsed Time in milliseconds from the local user joining the channel until this callback.
     */
    virtual void onFirstRemoteVideoFrame(uid_t uid, int width, int height, int elapsed) {
        // Function body is a placeholder and does not process the parameters.
        (void)uid;
        (void)width;
        (void)height;
        (void)elapsed;
    }

    /**
     * Signals when a remote user mutes or unmutes their audio stream.
     *
     * @param uid The remote user's ID.
     * @param muted True if the audio stream is muted; false if unmuted.
     */
    virtual void onUserMuteAudio(uid_t uid, bool muted) {}

    /**
     * Reports changes in video dimensions or orientation for a specific user.
     * 
     * @param uid The user's ID (remote or local with 0 as local).
     * @param width The new video width in pixels.
     * @param height The new video height in pixels.
     * @param rotation The new video rotation in degrees [0, 360).
     */
    virtual void onVideoSizeChanged(uid_t uid, int width, int height, int rotation) {
        (void)uid;
        (void)width;
        (void)height;
        (void)rotation;
    }

    /**
     * Called when an audio effect playback finishes.
     * @param soundId The unique identifier for the audio effect that has finished playing.
     */
    virtual void onAudioEffectFinished(int soundId){}

    /**
     * Notifies the application of a change in the camera's exposure area.
     * @param x The x-coordinate of the top-left corner of the exposure area.
     * @param y The y-coordinate of the top-left corner of the exposure area.
     * @param width The width of the exposure area.
     * @param height The height of the exposure area.
     */
    virtual void onCameraExposureAreaChanged(int x,
                                             int y,
                                             int width,
                                             int height) {}

    /**
     * Called to notify the application of changes in the state of audio mixing.
     * @param state The current state of the audio mixing. See AUDIO_MIXING_STATE_TYPE for possible values.
     * @param errorCode The reason for the state change, if any. See AUDIO_MIXING_REASON_TYPE for possible values.
     */
    virtual void onAudioMixingStateChanged(AUDIO_MIXING_STATE_TYPE state, AUDIO_MIXING_REASON_TYPE errorCode) = 0;

    /**
     * Called when the first remote audio stream is decoded.
     * @param uid The user ID of the remote user whose audio stream has been decoded.
     * @param elapsed The time in milliseconds it took for the first remote audio to be decoded.
     */
    virtual void onFirstRemoteAudioDecoded(uid_t uid, int elapsed) {}

    /**
     * Called when the local video state changes.
     * @param localVideoState The new state of the local video stream. See LOCAL_VIDEO_STREAM_STATE for possible values.
     * @param error The error code indicating the cause of the state change, if any. See LOCAL_VIDEO_STREAM_ERROR for possible values.
     */
    virtual void onLocalVideoStateChanged(
        LOCAL_VIDEO_STREAM_STATE localVideoState,
        LOCAL_VIDEO_STREAM_ERROR error){}

    /**
     * Called when the camera's focus area is changed.
     * This event is triggered whenever there is a change in the camera's focus area, which can affect image clarity.
     * @param x The new focus area's x-coordinate.
     * @param y The new focus area's y-coordinate.
     * @param width The new focus area's width.
     * @param height The new focus area's height.
     */
    virtual void onCameraFocusAreaChanged(int x, int y, int width, int height) {
        (void)x;
        (void)y;
        (void)width;
        (void)height;
    }


    /**
     * Called when the state of the remote video changes.
     * @param uid The user ID of the remote user whose video state has changed.
     * @param state The new state of the remote video. See REMOTE_VIDEO_STATE for possible values.
     * @param reason The reason for the change in the remote video state. See REMOTE_VIDEO_STATE_REASON for more information.
     * @param elapsed The time in milliseconds since the local user joined the channel until this callback is triggered.
     */
    virtual void onRemoteVideoStateChanged(uid_t uid, REMOTE_VIDEO_STATE state, REMOTE_VIDEO_STATE_REASON reason, int elapsed) {
        (void)uid;
        (void)state;
        (void)reason;
        (void)elapsed;
    }

    /**
     * Called when the local user receives a data stream message from a remote user within five seconds.
     * @param uid The User ID of the remote user who sent the message.
     * @param streamId The ID of the data stream.
     * @param data A pointer to the data received.
     * @param length The length of the data in bytes.
     */
    virtual void onStreamMessage(uid_t uid, int streamId, const char* data, size_t length) {
        (void)uid;
        (void)streamId;
        (void)data;
        (void)length;
    }

    /**
     * Called when the local user fails to receive a data stream message from a remote user within five seconds.
     * @param uid The User ID of the remote user who attempted to send the message.
     * @param streamId The ID of the data stream.
     * @param code The error code. See ERROR_CODE_TYPE for possible values.
     * @param missed The number of messages that were not received.
     * @param cached The number of messages cached while the data stream was interrupted.
     */
    virtual void onStreamMessageError(uid_t uid, int streamId, int code, int missed, int cached) {
        (void)uid;
        (void)streamId;
        (void)code;
        (void)missed;
        (void)cached;
    }

    // ... Additional methods with updated comments ...

    /**
     * Called when the media engine successfully loads.
     */
    virtual void onMediaEngineLoadSuccess() {
    }

    /**
     * Called when the media engine call starts successfully.
     */
    virtual void onMediaEngineStartCallSuccess() {
    }

    /**
     * Called when the state of the media stream relay changes.
     * @param state The new state of the media stream relay. See CHANNEL_MEDIA_RELAY_STATE for possible values.
     * @param code The error code associated with the state change. See CHANNEL_MEDIA_RELAY_ERROR for possible values.
     */
    virtual void onChannelMediaRelayStateChanged(CHANNEL_MEDIA_RELAY_STATE state, CHANNEL_MEDIA_RELAY_ERROR code) {
    }

    /**
     * Reports events that occur during the media stream relay.
     * @param code The event code that indicates the type of event that occurred. See CHANNEL_MEDIA_RELAY_EVENT for possible values.
     */
    virtual void onChannelMediaRelayEvent(CHANNEL_MEDIA_RELAY_EVENT code) {
    }


    /**
     * Called when the engine sends the first local audio frame.
     * @param elapsed The time in milliseconds elapsed from the local user calling joinChannel until this callback is triggered.
     */
    virtual void onFirstLocalAudioFrame(int elapsed) {
        (void)elapsed;
    }

    /**
     * Called when the engine receives the first audio frame from a specific remote user.
     * @param uid The user ID of the remote user.
     * @param elapsed The time in milliseconds elapsed from the remote user calling joinChannel until this callback is triggered.
     */
    virtual void onFirstRemoteAudioFrame(uid_t uid, int elapsed) {
        (void)uid;
        (void)elapsed;
    }

    /**
     * Called when the state of the RTMP streaming changes.
     * This callback is triggered by the SDK to report the result of the local user calling addPublishStreamUrl or removePublishStreamUrl.
     * @param url The RTMP URL address.
     * @param state The current RTMP streaming state. See RTMP_STREAM_PUBLISH_STATE for possible values.
     * @param errCode The detailed error information for the streaming. See RTMP_STREAM_PUBLISH_ERROR for possible values.
     */
    virtual void onRtmpStreamingStateChanged(const char *url, RTMP_STREAM_PUBLISH_STATE state, RTMP_STREAM_PUBLISH_ERROR errCode) {
        (void)url;
        (void)state;
        (void)errCode;
    }

    /**
     * Reports the result of calling the addPublishStreamUrl method for CDN live streaming.
     * @param url The RTMP URL address to which the stream is being published.
     * @param error The error code. See ERROR_CODE_TYPE for possible values. An error code of #ERR_OK (0) indicates success.
     */
    virtual void onStreamPublished(const char *url, int error) {
        (void)url;
        (void)error;
    }

    /**
     * Reports the result of calling the removePublishStreamUrl method for CDN live streaming.
     * @param url The RTMP URL address from which the stream has been removed.
     */
    virtual void onStreamUnpublished(const char *url) {
        (void)url;
    }

    /**
     * Called when the publisher's transcoding settings are updated.
     * The SDK triggers this callback to report update information to the local host after changes to the LiveTranscoding class.
     * @note The SDK does not trigger this callback if setLiveTranscoding is called for the first time.
     */
    virtual void onTranscodingUpdated() {
    }

    /**
     * Called when a voice or video stream URL is added to a live broadcast.
     * @param url The URL address of the externally injected stream.
     * @param uid The user ID associated with the stream.
     * @param status The status of the injected stream. See INJECT_STREAM_STATUS for possible values.
     */
    virtual void onStreamInjectedStatus(const char* url, uid_t uid, int status) {
        (void)url;
        (void)uid;
        (void)status;
    }

    /**
     * Called when the local audio route changes.
     * The SDK triggers this callback when the audio route is switched to an earpiece, speakerphone, headset, or Bluetooth device.
     * @note This callback is for Android and iOS only.
     * @param routing The new audio output routing. See AUDIO_ROUTE_TYPE for possible values.
     */
    virtual void onAudioRouteChanged(AUDIO_ROUTE_TYPE routing) {
        (void)routing;
    }



    /**
     * Called when the locally published media stream falls back to audio-only due to poor network conditions or switches back to video when the network improves.
     * @param isFallbackOrRecover true if the stream has fallen back to audio-only; false if it has switched back to video.
     */
    virtual void onLocalPublishFallbackToAudioOnly(bool isFallbackOrRecover) {
        (void)isFallbackOrRecover;
    }

    /**
     * Called when the remote media stream falls back to audio-only due to poor network conditions or switches back to video when the network improves.
     * @param uid The user ID of the remote user whose media stream has changed.
     * @param isFallbackOrRecover true if the remote stream has fallen back to audio-only; false if it has switched back to video.
     */
    virtual void onRemoteSubscribeFallbackToAudioOnly(uid_t uid, bool isFallbackOrRecover) {
        (void)uid;
        (void)isFallbackOrRecover;
    }

    /**
     * Deprecated: Replaced by the onRemoteVideoStats callback.
     * Called to report the transport-layer statistics of each remote video stream, such as packet loss rate and network delay.
     * @param uid The user ID of the remote user sending the video packet.
     * @param delay The network delay from when the video packet was sent to when it was received.
     * @param lost The packet loss rate of the received video packet.
     * @param rxKBitRate The received bitrate of the received video packet.
     */
    virtual void onRemoteVideoTransportStats(uid_t uid, unsigned short delay, unsigned short lost, unsigned short rxKBitRate) {
        (void)uid;
        (void)delay;
        (void)lost;
        (void)rxKBitRate;
    }

    /**
     * Deprecated: Use onLocalAudioStateChanged with LOCAL_AUDIO_STREAM_STATE_STOPPED or LOCAL_AUDIO_STREAM_STATE_RECORDING.
     * Called when the local audio capturing is enabled or disabled.
     * @param enabled true if the microphone is enabled; false if it is disabled.
     */
    virtual void onMicrophoneEnabled(bool enabled) {
        (void)enabled;
    }

    /**
     * Called when the connection state between the SDK and the server changes.
     * @param state The new connection state. See CONNECTION_STATE_TYPE for possible values.
     * @param reason The reason for the connection state change. See CONNECTION_CHANGED_REASON_TYPE for possible values.
     */
    virtual void onConnectionStateChanged(CONNECTION_STATE_TYPE state, CONNECTION_CHANGED_REASON_TYPE reason) {
        (void)state;
        (void)reason;
    }

    /**
     * Called when the local network type changes, indicating if the network connection is interrupted due to a network type change or poor conditions.
     * @param type The new local network type. See NETWORK_TYPE for possible values.
     */
    virtual void onNetworkTypeChanged(NETWORK_TYPE type) {
        (void)type;
    }

    /**
     * Called when the SDK chorus starts.
     */
    virtual void onChorusStart() {
    }

    /**
     * Called when the SDK chorus stops.
     */
    virtual void onChorusStop() {
    }

// ... Additional methods with updated comments ...
};

/** Audio device collection methods.

The IAudioDeviceCollection interface class retrieves device-related information.
*/
class IAudioDeviceCollection
{
protected:
    virtual ~IAudioDeviceCollection(){}
public:

    /** Retrieves the total number of audio playback or audio recording devices.

     @note You must first call the \ref IAudioDeviceManager::enumeratePlaybackDevices "enumeratePlaybackDevices" or \ref IAudioDeviceManager::enumerateRecordingDevices "enumerateRecordingDevices" method before calling this method to return the number of  audio playback or audio recording devices.

     @return Number of audio playback or audio recording devices.
     */
    virtual int getCount() = 0;

    /** Retrieves a specified piece of information about an indexed audio device.

     @param index The specified index that must be less than the return value of \ref IAudioDeviceCollection::getCount "getCount".
     @param deviceName Pointer to the audio device name.
     @param deviceId Pointer to the audio device ID.
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getDevice(int index, char deviceName[MAX_DEVICE_ID_LENGTH], char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;

    /** Specifies a device with the device ID.

     @param deviceId Pointer to the device ID of the device.
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setDevice(const char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;

    /** Sets the volume of the application.

    @param volume Application volume. The value ranges between 0 (lowest volume) and 255 (highest volume).
    @return
    - 0: Success.
    - < 0: Failure.
    */
    virtual int setApplicationVolume(int volume) = 0;

    /** Retrieves the volume of the application.

     @param volume Pointer to the application volume. The volume value ranges between 0 (lowest volume) and 255 (highest volume).

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getApplicationVolume(int* volume) = 0;

    /** Mutes the application.

     @param mute Sets whether to mute/unmute the application:
     - true: Mute the application.
     - false: Unmute the application.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setApplicationMute(bool mute) = 0;
    /** Gets the mute state of the application.

     @param mute Pointer to whether the application is muted/unmuted.
     - true: The application is muted.
     - false: The application is not muted.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int isApplicationMute(bool* mute) = 0;

    /** Releases all IAudioDeviceCollection resources.
    */
    virtual void release() = 0;

      /**
   * Gets the default audio device of the system (for macOS and Windows only).
   *
   * @since v3.6.0
   *
   * @param deviceName The name of the system default audio device.
   * @param deviceId The device ID of the the system default audio device.
   *
   * @return
   * - 0: Success.
   * - < 0: Failure.
   */
  virtual int getDefaultDevice(char deviceName[MAX_DEVICE_ID_LENGTH], char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;
};
/** Audio device management methods.

 The IAudioDeviceManager interface class allows for audio device interface testing. Instantiate an AAudioDeviceManager class to retrieve the IAudioDeviceManager interface.
*/
class IAudioDeviceManager
{
protected:
    virtual ~IAudioDeviceManager(){}
public:

    /** Enumerates the audio playback devices.

     This method returns an IAudioDeviceCollection object that includes all audio playback devices in the system. With the IAudioDeviceCollection object, the application can enumerate the audio playback devices.

     @note The application must call the \ref IAudioDeviceCollection::release "release" method to release the returned object after using it.

     @return
     - Success: Returns an IAudioDeviceCollection object that includes all audio playback devices in the system. For wireless Bluetooth headset devices with master and slave headsets, the master headset is the playback device.
     - Returns NULL: Failure.
     */
    virtual IAudioDeviceCollection* enumeratePlaybackDevices() = 0;

    /** Enumerates the audio recording devices.

     This method returns an IAudioDeviceCollection object that includes all audio recording devices in the system. With the IAudioDeviceCollection object, the application can enumerate the audio recording devices.

     @note The application needs to call the \ref IAudioDeviceCollection::release "release" method to release the returned object after using it.

     @return
     - Returns an IAudioDeviceCollection object that includes all audio recording devices in the system: Success.
     - Returns NULL: Failure.
     */
    virtual IAudioDeviceCollection* enumerateRecordingDevices() = 0;

    /** Sets the audio playback device using the device ID.

     @note Plugging or unplugging the audio device does not change the device ID.

     @param deviceId Device ID of the audio playback device, retrieved by calling the \ref IAudioDeviceManager::enumeratePlaybackDevices "enumeratePlaybackDevices" method.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setPlaybackDevice(const char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;

    /** Sets the audio recording device using the device ID.

     @param deviceId Device ID of the audio recording device, retrieved by calling the \ref IAudioDeviceManager::enumerateRecordingDevices "enumerateRecordingDevices" method.

     @note Plugging or unplugging the audio device does not change the device ID.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setRecordingDevice(const char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;

    
  /**
   * Sets the audio playback device used by the SDK to follow the system default audio playback device (for macOS and Windows only).
   *
   * @since v3.6.0
   *
   * @param enable Whether to follow the system default audio playback device:
   * - true: Follow. The SDK immediately switches the audio playback device when the system default audio playback device changes.
   * - false: Do not follow. The SDK switches the audio playback device to the system default audio playback device only when the currently used audio playback device is disconnected.
   *
   * @return
   * - 0: Success.
   * - < 0: Failure.
   */
  virtual int followSystemPlaybackDevice(bool enable) = 0;

  /**
   * Sets the audio recording device used by the SDK to follow the system default audio recording device (for macOS and Windows only).
   *
   * @since v3.6.0
   *
   * @param enable Whether to follow the system default audio recording device:
   * - true: Follow. The SDK immediately switches the audio recording device when the system default audio recording device changes.
   * - false: Do not follow. The SDK switches the audio recording device to the system default audio recording device only when the currently used audio recording device is disconnected.
   *
   * @return
   * - 0: Success.
   * - < 0: Failure.
   */
  virtual int followSystemRecordingDevice(bool enable) = 0;

    /** Starts the audio playback device test.

     This method tests if the playback device works properly. In the test, the SDK plays an audio file specified by the user. If the user can hear the audio, the playback device works properly.

     @param testAudioFilePath Pointer to the path of the audio file for the audio playback device test in UTF-8:
     - Supported file formats: wav, mp3, m4a, and aac.
     - Supported file sample rates: 8000, 16000, 32000, 44100, and 48000 Hz.

     @return
     - 0: Success, and you can hear the sound of the specified audio file.
     - < 0: Failure.
     */
    virtual int startPlaybackDeviceTest(const char* testAudioFilePath) = 0;

    /** Stops the audio playback device test.

     This method stops testing the audio playback device. You must call this method to stop the test after calling the \ref IAudioDeviceManager::startPlaybackDeviceTest "startPlaybackDeviceTest" method.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int stopPlaybackDeviceTest() = 0;

    /** Sets the volume of the audio playback device.

     @param volume Sets the volume of the audio playback device. The value ranges between 0 (lowest volume) and 255 (highest volume).
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setPlaybackDeviceVolume(int volume) = 0;

    /** Retrieves the volume of the audio playback device.

     @param volume Pointer to the audio playback device volume. The volume value ranges between 0 (lowest volume) and 255 (highest volume).
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getPlaybackDeviceVolume(int *volume) = 0;

    /** Sets the volume of the microphone.

     @param volume Sets the volume of the microphone. The value ranges between 0 (lowest volume) and 255 (highest volume).
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setRecordingDeviceVolume(int volume) = 0;

    /** Retrieves the volume of the microphone.

     @param volume Pointer to the microphone volume. The volume value ranges between 0 (lowest volume) and 255 (highest volume).
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getRecordingDeviceVolume(int *volume) = 0;

    /** Mutes the audio playback device.

     @param mute Sets whether to mute/unmute the audio playback device:
     - true: Mutes.
     - false: Unmutes.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setPlaybackDeviceMute(bool mute) = 0;
    /** Retrieves the mute status of the audio playback device.

     @param mute Pointer to whether the audio playback device is muted/unmuted.
     - true: Muted.
     - false: Unmuted.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getPlaybackDeviceMute(bool *mute) = 0;
    /** Mutes/Unmutes the microphone.

     @param mute Sets whether to mute/unmute the microphone:
     - true: Mutes.
     - false: Unmutes.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setRecordingDeviceMute(bool mute) = 0;

    /** Retrieves the microphone's mute status.

     @param mute Pointer to whether the microphone is muted/unmuted.
     - true: Muted.
     - false: Unmuted.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getRecordingDeviceMute(bool *mute) = 0;

    /** Starts the microphone test.

     This method tests whether the microphone works properly. Once the test starts, the SDK uses the \ref IRtcEngineEventHandler::onAudioVolumeIndication "onAudioVolumeIndication" callback to notify the application with the volume information.

     @param indicationInterval Interval period (ms) of the \ref IRtcEngineEventHandler::onAudioVolumeIndication "onAudioVolumeIndication" callback cycle.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int startRecordingDeviceTest(int indicationInterval) = 0;

    /** Stops the microphone test.

     This method stops the microphone test. You must call this method to stop the test after calling the \ref IAudioDeviceManager::startRecordingDeviceTest "startRecordingDeviceTest" method.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int stopRecordingDeviceTest() = 0;

    /** Retrieves the audio playback device associated with the device ID.

     @param deviceId Pointer to the ID of the audio playback device.
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getPlaybackDevice(char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;

    /** Retrieves the audio playback device information associated with the device ID and device name.

     @param deviceId Pointer to the device ID of the audio playback device.
     @param deviceName Pointer to the device name of the audio playback device.
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getPlaybackDeviceInfo(char deviceId[MAX_DEVICE_ID_LENGTH], char deviceName[MAX_DEVICE_ID_LENGTH]) = 0;

    /** Retrieves the audio recording device associated with the device ID.

     @param deviceId Pointer to the device ID of the audio recording device.
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getRecordingDevice(char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;

    /** Retrieves the audio recording device information associated with the device ID and device name.

     @param deviceId Pointer to the device ID of the recording audio device.
     @param deviceName Pointer to the device name of the recording audio device.
     @return
     - 0: Success.
     - < 0: Failure.
     */
   virtual int getRecordingDeviceInfo(char deviceId[MAX_DEVICE_ID_LENGTH], char deviceName[MAX_DEVICE_ID_LENGTH]) = 0;

   /** Starts the audio device loopback test.

   This method tests whether the local audio devices are working properly. After calling this method, the microphone captures the local audio and plays it through the speaker. The \ref IRtcEngineEventHandler::onAudioVolumeIndication "onAudioVolumeIndication" callback returns the local audio volume information at the set interval.

   @note This method tests the local audio devices and does not report the network conditions.

   @param indicationInterval The time interval (ms) at which the \ref IRtcEngineEventHandler::onAudioVolumeIndication "onAudioVolumeIndication" callback returns.

   @return
   - 0: Success.
   - < 0: Failure.
   */
   virtual int startAudioDeviceLoopbackTest(int indicationInterval) = 0;

   /** Stops the audio device loopback test.

   @note Ensure that you call this method to stop the loopback test after calling the \ref IAudioDeviceManager::startAudioDeviceLoopbackTest "startAudioDeviceLoopbackTest" method.

   @return
   - 0: Success.
   - < 0: Failure.
   */
   virtual int stopAudioDeviceLoopbackTest() = 0;

   /** Releases all IAudioDeviceManager resources.
   */
    virtual void release() = 0;

};

/** Definition of RtcEngineContext.
*/
struct RtcEngineContext
{
    /** The IRtcEngineEventHandler object.
     */
    IRtcEngineEventHandler* eventHandler;
    /** App ID issued to you by Aopa. Apply for a new App ID from Aopa if
     * it is missing from your kit.
     */
    const char* appId;
    // For android, it the context(Activity or Application
    // for windows,Video hot plug device
    /** The video window handle. Once set, this parameter enables you to plug
     * or unplug the video devices while they are powered.
     */
    void* context;
    RtcEngineContext()
    :eventHandler(NULL)
    ,appId(NULL)
    ,context(NULL)
    {}
};

/** The channel media options.
 */
struct ChannelMediaOptions {
  /** Determines whether to automatically subscribe to all remote audio streams when the user joins a channel:
   - true: (Default) Subscribe.
   - false: Do not subscribe.

   This member serves a similar function to the `muteAllRemoteAudioStreams` method. After joining the channel,
   you can call the `muteAllRemoteAudioStreams` method to set whether to subscribe to audio streams in the channel.
   */
  bool autoSubscribeAudio;
  /** Determines whether to subscribe to video streams when the user joins the channel:
   - true: (Default) Subscribe.
   - false: Do not subscribe.

   This member serves a similar function to the `muteAllRemoteVideoStreams` method. After joining the channel,
   you can call the `muteAllRemoteVideoStreams` method to set whether to subscribe to video streams in the channel.
   */
  bool autoSubscribeVideo;
  /** Determines whether to publish the local audio stream when the user joins a channel:
   * - true: (Default) Publish.
   * - false: Do not publish.
   *
   * This member serves a similar function to the `muteLocalAudioStream` method. After the user joins
   * the channel, you can call the `muteLocalAudioStream` method to set whether to publish the
   * local audio stream in the channel.
   */
  bool publishLocalAudio;
  /** Determines whether to publish the local video stream when the user joins a channel:
   * - true: (Default) Publish.
   * - false: Do not publish.
   *
   * This member serves a similar function to the `muteLocalVideoStream` method. After the user joins
   * the channel, you can call the `muteLocalVideoStream` method to set whether to publish the
   * local video stream in the channel.
   */
  bool publishLocalVideo;
  ChannelMediaOptions() : autoSubscribeAudio(true), autoSubscribeVideo(true), publishLocalAudio(true), publishLocalVideo(true) {}
};

/** IRtcEngine is the base interface class of the Aopa SDK that provides the main Aopa SDK methods invoked by your application.

Enable the Aopa SDK's communication functionality through the creation of an IRtcEngine object, then call the methods of this object.
 */
class  IRtcEngine {
public:
    virtual ~IRtcEngine() {}
public:

    /** 
     * Initializes the Aopa Real-Time Communication (RTC) service.
     *
     * **Prerequisite:** This method must be called after \ref bb::rtc::IRtcEngine::createAopaRtcEngine "createAopaRtcEngine",
     * and before invoking any other APIs to ensure proper setup of the RTC engine.
     *
     * @param context A reference to the RTC engine context which holds initialization parameters. Refer to RtcEngineContext for details.
     *
     * @return
     * - 0: Initialization successful.
     * - < 0: Initialization failed.
     *   - `ERR_INVALID_APP_ID (101)`: The provided App ID is invalid. Verify the format.
     */
    virtual int initialize(const RtcEngineContext& context) = 0;

    /**
     * Releases all resources associated with the IRtcEngine instance.
     *
     * @param sync Determines the mode of operation:
     * - true: Synchronous release. The function blocks until resource release is complete. Avoid using in SDK callback scopes to prevent deadlock; the SDK may auto-convert to async to bypass deadlock, introducing test delays.
     * - false: Asynchronous release. Returns immediately without waiting for resource cleanup to finish.
     *
     * @note Post-call, avoid immediate removal of the SDK's dynamic library to prevent crashes from the cleanup thread not terminating properly.
     */
    virtual void release(bool sync) = 0;

    /**
     * Configures the channel profile for the Aopa RtcEngine.
     *
     * The RtcEngine optimizes performance based on the specified channel profile,
     * e.g., emphasizing low latency for voice calls or high video quality for broadcasts.
     *
     * @note
     * - Ensure all participants in a channel use the same profile for optimal real-time communication.
     * - This method must be invoked before \ref IRtcEngine::joinChannel "joinChannel".
     *   Once in a channel, the profile cannot be altered.
     *
     * @param profile The desired channel profile. Refer to #CHANNEL_PROFILE_TYPE for options.
     *
     * @return
     * - 0: The profile was set successfully.
     * - < 0: An error occurred.
     */
    virtual int setChannelProfile(CHANNEL_PROFILE_TYPE profile) = 0;

    /**
     * Assigns or alters the user role in a live broadcast channel.
     *
     * This function allows role switching post-channel join, applicable for live streaming scenarios.
     *
     * In a live broadcast, a successful role change via \ref bb::rtc::IRtcEngine::setClientRole "setClientRole"
     * will notify clients via these callbacks:
     * - Local client: \ref bb::rtc::IRtcEngineEventHandler::onClientRoleChanged "onClientRoleChanged".
     * - Remote clients: \ref bb::rtc::IRtcEngineEventHandler::onUserJoined "onUserJoined" or
     *   \ref bb::rtc::IRtcEngineEventHandler::onUserOffline "onUserOffline" (when becoming an audience).
     *
     * @note Restricted to the Live Broadcast profile.
     *
     * @param role The new role for the user. See #CLIENT_ROLE_TYPE for definitions.
     *
     * @return
     * - 0: Role updated successfully.
     * - < 0: Update failed.
     */
    virtual int setClientRole(CLIENT_ROLE_TYPE role) = 0;

    /**
     * Designates the KTV chorus role for the user.
     *
     * @note
     * - Invoke this method after successfully joining a channel.
     * - Designed for KTV-style applications where synchronized singing is a feature.
     *
     * @param role The KTV chorus role to assign. Refer to #CLIENT_ROLE_CHORUS_TYPE.
     *
     * @return
     * - 0: Role set successfully.
     * - < 0: An error occurred.
     */
    virtual int setChorusRole(CLIENT_ROLE_CHORUS_TYPE role) = 0;

    /**
     * Retrieves the current playing position of the chorus in milliseconds.
     *
     * @note
     * - Should be called after joining a channel with active chorus functionality.
     *
     * @return
     * - >= 0: The current chorus play position in milliseconds.
     * - < 0: An error occurred or the position could not be retrieved.
     */
    virtual int getChorusPosition() = 0;

        
    /**
     * Joins a channel with the specified user ID for audio/video communication.
     *
     * Users in the same channel can communicate with each other. To join a channel,
     * you must first call the \ref IRtcEngine::leaveChannel "leaveChannel" method to exit any
     * current channel.
     *
     * A successful join will trigger the \ref IRtcEngineEventHandler::onJoinChannelSuccess "onJoinChannelSuccess"
     * callback on the local client and the \ref IRtcEngineEventHandler::onUserJoined "onUserJoined" callback
     * on remote clients, depending on the user role.
     *
     * @note Ensure each user has a unique user ID. The system assigns a user ID if \p uid is set to 0.
     * @warning Use the same App ID for token generation as used in the \ref IRtcEngine::initialize "initialize" method.
     *
     * @param token Pointer to the token string generated by the application server.
     * @param channelId Pointer to the unique channel name string, with a maximum length of 63 bytes.
     * @param info Optional additional channel information.
     * @param uid User ID; must be unique and within the range of 1 to 2^32-1.
     * @return
     * - 0: Success
     * - < 0: Failure (See error codes for details)
     */
    virtual int joinChannel(const char* token, const char* channelId, const char* info, uid_t uid) = 0;

    /**
     * Joins a channel with additional media options, specifying whether to publish
     * or automatically subscribe to audio/video streams.
     *
     * @since v3.3.0
     *
     * @param token The token generated by your server.
     * @param channelId The unique channel name string.
     * @param info Reserved for future use.
     * @param uid The unique user ID.
     * @param options The channel media options, including publish and subscribe settings.
     * @return
     * - 0(ERR_OK): Success
     * - < 0: Failure (See error codes for details)
     */
    virtual int joinChannel(const char* token, const char* channelId, const char* info, uid_t uid, const ChannelMediaOptions& options) = 0;

    /**
     * Switches to a different channel in a live-broadcast scenario.
     *
     * @note This method is for audience members in a live-broadcast channel.
     *
     * @param token The new token for the channel switch.
     * @param channelId The unique name of the new channel.
     * @return
     * - 0: Success
     * - < 0: Failure (See error codes for details)
     */
    virtual int switchChannel(const char* token, const char* channelId) = 0;

    /**
     * Leaves the current channel and ends the communication session.
     *
     * This method is asynchronous; the \ref IRtcEngineEventHandler::onLeaveChannel "onLeaveChannel"
     * callback indicates that the user has successfully left the channel.
     *
     * @return
     * - 0: Success
     * - < 0: Failure (See error codes for details)
     */
    virtual int leaveChannel() = 0;

    // Assuming leaveChannel2 is an overloaded function or a follow-up method,
    // the comment should reflect any differences from leaveChannel if applicable.
    virtual int leaveChannel2() = 0;

    
    /**
     * Renews the token when the current token is about to expire.
     *
     * The token is essential for authentication and will expire after a set time.
     * The SDK will trigger the \ref IRtcEngineEventHandler::onTokenPrivilegeWillExpire
     * "onTokenPrivilegeWillExpire" callback or report CONNECTION_CHANGED_TOKEN_EXPIRED(9)
     * via the \ref IRtcEngineEventHandler::onConnectionStateChanged "onConnectionStateChanged"
     * when the token is nearing expiration.
     *
     * @param token The new token string acquired from the server.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates failure. See error codes for details.
     */
    virtual int renewToken(const char* token) = 0;

    /**
     * Retrieves the device manager object for handling device-related operations.
     *
     * @param iid The interface ID of the device manager.
     * @param inter Pointer to the address where the device manager object will be stored.
     * @return
     * - 0: Indicates the operation was successful and the device manager object is retrieved.
     * - Negative value: Indicates failure. See error codes for details.
     */
    virtual int queryInterface(INTERFACE_ID_TYPE iid, void** inter) = 0;

    /**
     * Enables the video module for audio/video communication.
     *
     * This method can be called before or during a call. If called before joining a channel,
     * the channel will start in video mode. If called during an audio call, it will switch
     * to video mode. To disable the video module, use the \ref IRtcEngine::disableVideo "disableVideo" method.
     *
     * A successful call of this method will trigger the \ref IRtcEngineEventHandler::onUserEnableVideo "onUserEnableVideo" (true)
     * callback on the remote client.
     *
     * @note
     * - This method can be called after \ref IRtcEngine::leaveChannel "leaveChannel".
     * - For more granular control over video settings, refer to other video control methods.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates failure. See error codes for details.
     */
    virtual int enableVideo() = 0;

    /**
     * Disables the video module, switching to audio-only mode.
     *
     * This method can be called before or during a call to start in audio mode or to switch
     * from video mode to audio mode. To enable the video module, use the \ref IRtcEngine::enableVideo "enableVideo" method.
     *
     * A successful call of this method will trigger the \ref IRtcEngineEventHandler::onUserEnableVideo "onUserEnableVideo" (false)
     * callback on the remote client.
     *
     * @note
     * - This method can be called after \ref IRtcEngine::leaveChannel "leaveChannel".
     * - For more granular control over video settings, refer to other video control methods.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates failure. See error codes for details.
     */
    virtual int disableVideo() = 0;

    /**
     * Sets the video profile. As of v2.3, this method is deprecated; use \ref IRtcEngine::setVideoEncoderConfiguration "setVideoEncoderConfiguration" instead.
     *
     * @deprecated
     * @param profile The video profile to set. See #VIDEO_PROFILE_TYPE.
     * @param swapWidthAndHeight Whether to swap the width and height of the video stream.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates failure. See error codes for details.
     */
    virtual int setVideoProfile(VIDEO_PROFILE_TYPE profile, bool swapWidthAndHeight) = 0;

    /**
     * Sets the video encoder configuration with a set of parameters including resolution, frame rate, bitrate, and orientation.
     *
     * @param config The local video encoder configuration. See VideoEncoderConfiguration.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates failure. See error codes for details.
     */
    virtual int setVideoEncoderConfiguration(const VideoEncoderConfiguration& config) = 0;

    /**
     * Configures the camera capture settings to optimize performance or preview quality.
     *
     * @param config The camera capturer configuration. See CameraCapturerConfiguration.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates failure. See error codes for details.
     */
    virtual int setCameraCapturerConfiguration(const CameraCapturerConfiguration& config) = 0;

    /**
     * Sets up the local video view for preview before joining a channel.
     *
     * @param canvas The local video view settings. See VideoCanvas.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates failure. See error codes for details.
     */
    virtual int setupLocalVideo(const VideoCanvas& canvas) = 0;

    /**
     * Sets up the video view for a remote user.
     *
     * @param canvas The remote video view settings. See VideoCanvas.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates failure. See error codes for details.
     */
    virtual int setupRemoteVideo(const VideoCanvas& canvas) = 0;

    /**
     * Starts the local video preview.
     *
     * Call this method after setting up the local video and enabling video.
     *
     * @note The preview will continue even after leaving the channel until \ref IRtcEngine::stopPreview "stopPreview" is called.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates failure. See error codes for details.
     */
    virtual int startPreview() = 0;

    /**
     * Sets the priority of a remote user's stream to ensure optimal quality when fallback is enabled.
     * @note Only one user can be assigned high priority at a time.
     * @param uid The unique identifier of the remote user.
     * @param userPriority The priority level to assign. See PRIORITY_TYPE for possible values.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates an error occurred.
     */
    virtual int setRemoteUserPriority(uid_t uid, PRIORITY_TYPE userPriority) = 0;

    /**
     * Stops the local video preview and disables the video module.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates an error occurred.
     */
    virtual int stopPreview() = 0;

    /**
     * Enables the audio module, which is enabled by default.
     * @note This method can be called at any time to affect the internal engine state.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates an error occurred.
     */
    virtual int enableAudio() = 0;

    /**
     * Enables or disables the local audio function, controlling the local audio capturing.
     * @param enabled true to enable, false to disable the local audio function.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates an error occurred.
     */
    virtual int enableLocalAudio(bool enabled) = 0;

    /**
     * Disables the audio module, stopping all audio-related processes.
     * @note This method can be called at any time to affect the internal engine state.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates an error occurred.
     */
    virtual int disableAudio() = 0;

    /**
     * Sets the audio profile and scenario for optimized audio settings.
     * @param profile The audio profile to set, which defines the sample rate, bitrate, encoding mode, and the number of channels. See AUDIO_PROFILE_TYPE.
     * @param scenario The audio scenario to set, which affects the volume tracks used by the device, such as in-call volume or media volume. See AUDIO_SCENARIO_TYPE. For more information on volume tracks, see the system volume FAQ.
     * @note The method must be called before joining a channel. The bitrate may vary based on network conditions.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates an error occurred.
     */
    virtual int setAudioProfile(AUDIO_PROFILE_TYPE profile, AUDIO_SCENARIO_TYPE scenario) = 0;

    // ... Additional methods with updated comments ...

    /**
     * Mutes or unmutes the local audio stream.
     * @param mute true to mute, false to unmute the local audio stream.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates an error occurred.
     */
    virtual int muteLocalAudioStream(bool mute) = 0;

    /**
     * Mutes or unmutes all remote audio streams.
     * @param mute true to mute, false to unmute all remote audio streams.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates an error occurred.
     */
    virtual int muteAllRemoteAudioStreams(bool mute) = 0;

    /**
     * Sets the default mute state for all remote audio streams.
     * @param mute true to mute by default, false to unmute by default.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates an error occurred.
     */
    virtual int setDefaultMuteAllRemoteAudioStreams(bool mute) = 0;

    /**
     * Adjusts the playback volume for a specified remote user.
     * @param uid The unique identifier of the remote user.
     * @param volume The playback volume, ranging from 0 (mute) to 100 (maximum volume).
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates an error occurred.
     */
    virtual int adjustUserPlaybackSignalVolume(unsigned int uid, int volume) = 0;

    /**
     * Mutes or unmutes the audio stream of a specified remote user.
     * @param userId The ID of the remote user whose audio stream is to be muted or unmuted.
     * @param mute true to stop receiving the audio stream from the specified remote user, false to resume receiving.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates an error occurred.
     */
    virtual int muteRemoteAudioStream(uid_t userId, bool mute) = 0;

    /**
     * Mutes or unmutes the local video stream.
     * A successful call to this method triggers the onUserMuteVideo callback on remote clients.
     * @param mute true to stop sending the local video stream, false to resume sending.
     * @note
     * - Setting mute to true does not disable the camera and does not affect the retrieval of local video streams.
     * - If setChannelProfile is called after this method, the SDK resets the local video stream's mute state according to the channel profile and user role. It is recommended to call this method after setChannelProfile.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates an error occurred.
     */
    virtual int muteLocalVideoStream(bool mute) = 0;

    /**
     * Enables or disables the local video capture.
     * @param enabled true to enable local video capture, false to disable it.
     * @note
     * - Disabling local video capture does not affect the reception of remote video streams.
     * - After calling enableVideo, local video capture is enabled by default. Use enableLocalVideo(false) to disable it.
     * - The onUserEnableLocalVideo callback is triggered on remote clients after the local video capture is successfully enabled or disabled.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates an error occurred.
     */
    virtual int enableLocalVideo(bool enabled) = 0;

    /**
     * Mutes or unmutes all remote video streams.
     * @param mute true to stop receiving all remote video streams, false to resume receiving.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates an error occurred.
     */
    virtual int muteAllRemoteVideoStreams(bool mute) = 0;

    /**
     * Sets the default mute state for all remote video streams.
     * @param mute true to set the default state to mute for all remote video streams, false to unmute.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates an error occurred.
     */
    virtual int setDefaultMuteAllRemoteVideoStreams(bool mute) = 0;

    /**
     * Mutes or unmutes the video stream of a specified remote user.
     * @param userId The ID of the remote user whose video stream is to be muted or unmuted.
     * @param mute true to stop receiving the video stream from the specified remote user, false to resume receiving.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates an error occurred.
     */
    virtual int muteRemoteVideoStream(uid_t userId, bool mute) = 0;

    // ... Additional methods with updated comments ...

    /**
     * Sets the video stream type for a remote user when dual streams are being sent.
     * @param userId The ID of the remote user sending the video streams.
     * @param streamType The type of video stream to receive. See REMOTE_VIDEO_STREAM_TYPE for possible values.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates an error occurred.
     */
    virtual int setRemoteVideoStreamType(uid_t userId, REMOTE_VIDEO_STREAM_TYPE streamType) = 0;

    /**
     * Sets the default video stream type for all remote users when dual streams are being sent.
     * @param streamType The default type of video stream to receive. See REMOTE_VIDEO_STREAM_TYPE for possible values.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates an error occurred.
     */
    virtual int setRemoteDefaultVideoStreamType(REMOTE_VIDEO_STREAM_TYPE streamType) = 0;

    /**
     * Enables the onAudioVolumeIndication callback to report which users are speaking and the volume of their speech at set intervals.
     * @param interval The interval between volume indications, in milliseconds. Set to 0 to disable.
     * @param smooth The smoothing factor for the volume indicator, ranging from 0 to 10. A higher value makes the indicator more sensitive.
     * @param report_vad Whether to enable voice activity detection for the local user and report its status in the onAudioVolumeIndication callback.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates an error occurred.
     */
    virtual int enableAudioVolumeIndication(int interval, int smooth, bool report_vad) = 0;


    /**
     * Initiates audio recording on the client.
     * Once initiated, the audio of all users in the channel can be recorded to a file.
     * @param filePath The absolute path to the output audio file, in UTF-8 encoding.
     * @param sampleRate The sample rate of the recording in kHz. Supported values: 16, 32 (default), 44.1, 48.
     * @param quality The quality setting for the audio recording. See AUDIO_RECORDING_QUALITY_TYPE for options.
     * @note
     * - Ensure the specified directory is accessible and has write permissions.
     * - This method should be called after joining a channel, and the recording will cease upon leaving the channel.
     * - For optimal quality, use #AUDIO_RECORDING_QUALITY_MEDIUM or #AUDIO_RECORDING_QUALITY_HIGH at a sampleRate of 44.1 kHz or 48 kHz.
     * @return
     * - 0: Indicates success.
     * - Negative values: Indicate failure.
     */
    virtual int startAudioRecording(const char* filePath, int sampleRate, AUDIO_RECORDING_QUALITY_TYPE quality) = 0;

    /**
     * Stops an audio recording session on the client.
     * @note This method should be called before leaving the channel; otherwise, the recording will stop automatically.
     * @return
     * - 0: Indicates success.
     * - Negative values: Indicate failure.
     */
    virtual int stopAudioRecording() = 0;

    /**
     * Starts audio mixing by playing a music file that is mixed with the microphone audio stream.
     * @param filePath The absolute path to the local or online audio file for mixing.
     * @param loopback Determines if only the local user can hear the mixed audio.
     * @param replace Determines if the audio file replaces the microphone stream or is mixed with it.
     * @param cycle The number of times the audio file will loop; use -1 for infinite looping.
     * @note
     * - Call this method while in a channel.
     * - Unsupported file formats or inaccessible URLs may result in an error.
     * - The onAudioMixingStateChanged callback indicates the start and finish of playback.
     * @return
     * - 0: Indicates success.
     * - Negative values: Indicate failure.
     */
    virtual int startAudioMixing(const char* filePath, bool loopback, bool replace, int cycle) = 0;
                        
    /**
     * Starts audio mixing by playing a music file that is mixed with the microphone audio stream.
     * @param filePath The absolute path to the local or online audio file for mixing.
     * @param loopback Determines if only the local user can hear the mixed audio.
     * @param replace Determines if the audio file replaces the microphone stream or is mixed with it.
     * @param cycle The number of times the audio file will loop; use -1 for infinite looping.
     * @param startPos The starting position of the audio playback in milliseconds.
     * @note
     * - Call this method while in a channel.
     * - Unsupported file formats or inaccessible URLs may result in an error.
     * - The onAudioMixingStateChanged callback indicates the start and finish of playback.
     * @return
     * - 0: Indicates success.
     * - Negative values: Indicate failure.
     */
    virtual int startAudioMixing(const char* filePath, bool loopback, bool replace, int cycle, int startPos) = 0;

    /**
     * Stops the currently playing audio mix.
     * @return
     * - 0: Indicates success.
     * - Negative values: Indicate failure.
     */
    virtual int stopAudioMixing() = 0;

    /**
     * Pauses the currently playing audio mix.
     * @return
     * - 0: Indicates success.
     * - Negative values: Indicate failure.
     */
    virtual int pauseAudioMixing() = 0;

    /**
     * Resumes playback of the audio mix after it has been paused.
     * @return
     * - 0: Indicates success.
     * - Negative values: Indicate failure.
     */
    virtual int resumeAudioMixing() = 0;

    /**
     * Sets high-quality audio parameters (deprecated).
     * @param fullband Enables or disables full-band codec at 48-kHz sample rate.
     * @param stereo Enables or disables stereo codec.
     * @param fullBitrate Enables or disables high-bitrate mode, recommended for voice-only modes.
     * @note
     * - Aopa recommends not using this method.
     * - Set these parameters before joining a channel and avoid changing them afterward.
     * @return
     * - 0: Indicates success.
     * - Negative values: Indicate failure.
     */
    virtual int setHighQualityAudioParameters(bool fullband, bool stereo, bool fullBitrate) = 0;

    // ... Additional methods with updated comments ...

    /**
     * Adjusts the volume of the audio mixing for local playback.
     * @param volume The volume level to set, ranging from 0 to 100.
     * @return
     * - 0: Indicates success.
     * - Negative values: Indicate failure.
     */
    virtual int adjustAudioMixingPlayoutVolume(int volume) = 0;

    /**
     * Retrieves the current volume level of the audio mixing for local playback.
     * @return
     * - >= 0: The current volume level if successful.
     * - Negative values: Indicate failure.
     */
    virtual int getAudioMixingPlayoutVolume() = 0;

    /**
     * Adjusts the volume of the audio mixing for publishing to remote users.
     * @param volume The volume level to set, ranging from 0 to 100.
     * @return
     * - 0: Indicates success.
     * - Negative values: Indicate failure.
     */
    virtual int adjustAudioMixingPublishVolume(int volume) = 0;


    /**
     * Retrieves the audio mixing volume for publishing, which is used to help troubleshoot audio volume related issues.
     * @note This method should be called while in a channel.
     * @return
     * - >= 0: Indicates the audio mixing volume for publishing if the method call succeeds. The value range is [0, 100].
     * - < 0: Indicates failure.
     */
    virtual int getAudioMixingPublishVolume() = 0;

    /**
     * Retrieves the duration of the music file in milliseconds.
     * @note This method should be called while in a channel.
     * @return
     * - >= 0: Indicates the audio mixing duration if the method call succeeds.
     * - < 0: Indicates failure.
     */
    virtual int getAudioMixingDuration() = 0;

    /**
     * Retrieves the current playback position of the music file in milliseconds.
     * @note This method should be called while in a channel.
     * @return
     * - >= 0: Indicates the current playback position of the audio mixing if the method call succeeds.
     * - < 0: Indicates failure.
     */
    virtual int getAudioMixingCurrentPosition() = 0;

    /**
     * Sets the playback position of the music file to a specified starting position in milliseconds.
     * @param pos The desired playback starting position of the music file in milliseconds.
     * @return
     * - 0: Indicates success.
     * - < 0: Indicates failure.
     */
    virtual int setAudioMixingPosition(int pos /* in ms */) = 0;

    /**
     * Sets the pitch of the local music file when mixed with a local human voice.
     * @since v3.0.1
     * @note This method should be called after starting audio mixing and receiving the onAudioMixingStateChanged callback with AUDIO_MIXING_STATE_PLAYING state.
     * @param pitch The pitch value, ranging from -12 to 12. A value of 0 indicates the original pitch.
     * @return
     * - 0: Indicates success.
     * - < 0: Indicates failure.
     */
    virtual int setAudioMixingPitch(int pitch) = 0;

    /**
     * Retrieves the volume of the audio effects, which ranges between 0.0 and 100.0.
     * @return
     * - >= 0: The volume of the audio effects if the method call succeeds.
     * - < 0: Indicates failure.
     */
    virtual int getEffectsVolume() = 0;

    /**
     * Sets the volume of the audio effects.
     * @param volume The volume level to set, ranging from 0 to 100.
     * @return
     * - 0: Indicates success.
     * - < 0: Indicates failure.
     */
    virtual int setEffectsVolume(int volume) = 0;

    /**
     * Sets the volume of a specified audio effect.
     * @param soundId The unique ID of the audio effect.
     * @param volume The volume level to set for the specified audio effect, ranging from 0 to 100.
     * @return
     * - 0: Indicates success.
     * - < 0: Indicates failure.
     */
    virtual int setVolumeOfEffect(int soundId, int volume) = 0;

    /**
     * Plays a specified local or online audio effect file with customizable loop count, pitch, pan, and gain.
     * @deprecated Deprecated from v3.4.0. Use the newer playEffect method instead.
     * @param soundId The unique ID of the audio effect.
     * @param filePath The absolute path or URL of the audio file to play.
     * @param loopCount The number of times the audio effect should loop. Use -1 for an indefinite loop.
     * @param pitch The pitch of the audio effect, ranging from 0.5 to 2.0.
     * @param pan The spatial position of the audio effect, ranging from -1.0 to 1.0.
     * @param gain The volume of the audio effect, ranging from 0 to 100.
     * @param publish Whether the audio effect should be published to the remote stream.
     * @return
     * - 0: Indicates success.
     * - < 0: Indicates failure.
     */
    virtual int playEffect(int soundId, const char* filePath, int loopCount, double pitch, double pan, int gain, bool publish) = 0;


    /**
     * Plays a specified local or online audio effect file.
     * @since v3.4.0
     * @param soundId Unique identifier for the audio effect. Used to reference the preloaded effect.
     * @param filePath Absolute path or URL to the audio file, supporting formats like MP3, AAC, etc.
     * @param loopCount Number of times the audio effect should loop. Use -1 for an indefinite loop.
     * @param pitch Pitch adjustment for the audio effect, ranging from 0.5 to 2.0.
     * @param pan Spatial positioning of the audio effect, ranging from -1.0 (left) to 1.0 (right).
     * @param gain Volume adjustment for the audio effect, ranging from 0.0 to 100.0.
     * @param publish Determines if the audio effect should be published to remote users.
     * @param startPos Starting position of the audio playback in milliseconds.
     * @return
     * - 0: Success.
     * - < 0: Failure.
     */
    virtual int playEffect(int soundId, const char* filePath, int loopCount, double pitch, double pan, int gain, bool publish, int startPos) = 0;

    /**
     * Stops playing a specified audio effect by its unique ID.
     * @param soundId Unique identifier for the audio effect to stop.
     * @return
     * - 0: Success.
     * - < 0: Failure.
     */
    virtual int stopEffect(int soundId) = 0;

    /**
     * Stops all audio effects currently playing.
     * @return
     * - 0: Success.
     * - < 0: Failure.
     */
    virtual int stopAllEffects() = 0;

    /**
     * Preloads a specified audio effect file into memory to enhance performance during a call.
     * @note Does not support online audio files and recommends limiting file size for smooth communication.
     * @param soundId Unique identifier for the audio effect.
     * @param filePath Absolute path to the audio file, supporting formats like mp3, aac, etc.
     * @return
     * - 0: Success.
     * - < 0: Failure.
     */
    virtual int preloadEffect(int soundId, const char* filePath) = 0;

    /**
     * Unloads a preloaded audio effect from memory.
     * @param soundId Unique identifier for the audio effect to unload.
     * @return
     * - 0: Success.
     * - < 0: Failure.
     */
    virtual int unloadEffect(int soundId) = 0;

    /**
     * Pauses a specified audio effect.
     * @param soundId Unique identifier for the audio effect to pause.
     * @return
     * - 0: Success.
     * - < 0: Failure.
     */
    virtual int pauseEffect(int soundId) = 0;

    /**
     * Pauses all currently playing audio effects.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates an error occurred.
     */
    virtual int pauseAllEffects() = 0;

    /**
     * Resumes playing a specified audio effect.
     * @param soundId The unique identifier for the audio effect to resume.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates an error occurred.
     */
    virtual int resumeEffect(int soundId) = 0;

    /**
     * Resumes playing all audio effects that have been paused.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates an error occurred.
     */
    virtual int resumeAllEffects() = 0;

    /**
     * Retrieves the total duration of the specified audio effect file.
     * @param filePath The absolute path or URL to the audio file.
     * @return
     * - >= 0: The duration of the audio effect file in milliseconds if the method call succeeds.
     * - < 0: Indicates an error occurred, such as the file not being found.
     */
    virtual int getEffectDuration(const char* filePath) = 0;

    /**
     * Sets the playback position for a specified audio effect file.
     * @param soundId The unique identifier for the audio effect.
     * @param pos The new playback position in milliseconds.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates an error occurred, such as the audio effect not being found.
     */
    virtual int setEffectPosition(int soundId, int pos) = 0;

    /**
     * Gets the current playback position of the specified audio effect file.
     * @param soundId The unique identifier for the audio effect.
     * @return
     * - >= 0: The current playback position in milliseconds if the method call succeeds.
     * - < 0: Indicates an error occurred, such as the audio effect not being found.
     */
    virtual int getEffectCurrentPosition(int soundId) = 0;

    /**
     * Adjusts the pitch of the local speaker's voice.
     * @param pitch The pitch value to set, ranging from 0.5 to 2.0. A value of 1.0 means no change.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates an error occurred.
     */
    virtual int setLocalVoicePitch(double pitch) = 0;

    /**
     * Sets the equalization effect for the local voice across specified frequency bands.
     * @param bandFrequency The band frequency to adjust. See AUDIO_EQUALIZATION_BAND_FREQUENCY for options.
     * @param bandGain The gain to apply to the specified band in decibels, ranging from -15 to 15.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates an error occurred.
     */
    virtual int setLocalVoiceEqualization(AUDIO_EQUALIZATION_BAND_FREQUENCY bandFrequency, int bandGain) = 0;

    /**
     * Sets the reverberation effect for the local voice.
     * @param reverbKey The reverberation key defining the type of reverberation. See AUDIO_REVERB_TYPE for options.
     * @param value The value to set for the reverberation key.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates an error occurred.
     */
    virtual int setLocalVoiceReverb(AUDIO_REVERB_TYPE reverbKey, int value) = 0;

    /**
     * Sets the voice changer option for the local voice.
     * @param voiceChanger The voice changer preset to apply. See VOICE_CHANGER_PRESET for options.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates an error occurred.
     */
    virtual int setLocalVoiceChanger(VOICE_CHANGER_PRESET voiceChanger) = 0;

    

    /**
     * Sets the preset local voice reverberation effect.
     * @note Avoid using this method in conjunction with setLocalVoiceReverb or setLocalVoiceChanger, 
     * as the latter called method will override the settings of the former.
     * @param reverbPreset The preset audio reverberation configuration to apply. See AUDIO_REVERB_PRESET for options.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates an error occurred.
     */
    virtual int setLocalVoiceReverbPreset(AUDIO_REVERB_PRESET reverbPreset) = 0;

    /**
     * Specifies the file path for the SDK's output log, which records all runtime operations.
     * If the specified log file doesn't exist, the SDK will create one.
     * @note
     * - The default log file is typically located in a directory such as "C:\Users\<user_name>\AppData\Local\Aopa\<process_name>".
     * - It is recommended to call this method right after the initialize method to ensure complete log output.
     * @param filePath The UTF-8 encoded string file path of the log file.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates an error occurred.
     */
    virtual int setLogFile(const char* filePath) = 0;

    /**
     * Sets the log output level for the SDK, determining the types of logs to record.
     * @param filter The log filter level to set. See LOG_FILTER_TYPE for options.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates an error occurred.
     */
    virtual int setLogFilter(unsigned int filter) = 0;

    /**
     * Sets the maximum size of the SDK's log files in kilobytes.
     * @param fileSizeInKBytes The maximum size of the log files in KB.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates an error occurred.
     */
    virtual int setLogFileSize(unsigned int fileSizeInKBytes) = 0;

    /**
     * @deprecated This method is deprecated. Use setLocalRenderMode(RENDER_MODE_TYPE, VIDEO_MIRROR_MODE_TYPE) instead.
     * Sets the local video display mode.
     * @param renderMode The local video display mode to set. See RENDER_MODE_TYPE for options.
     * @return
     * - 0: Success.
     * - < 0: Failure.
     */
    virtual int setLocalRenderMode(RENDER_MODE_TYPE renderMode) = 0;

    /**
     * Updates the display mode for the local video view, including rendering and mirror modes.
     * @param renderMode The rendering mode of the local video view. See RENDER_MODE_TYPE for options.
     * @param mirrorMode The mirror mode of the local video view. See VIDEO_MIRROR_MODE_TYPE for options.
     * @note This method only affects the local user's view and not the published video stream.
     * @return
     * - 0: Success.
     * - < 0: Failure.
     */
    virtual int setLocalRenderMode(RENDER_MODE_TYPE renderMode, VIDEO_MIRROR_MODE_TYPE mirrorMode) = 0;

    /**
     * @deprecated This method is deprecated. Use setRemoteRenderMode(uid_t, RENDER_MODE_TYPE, VIDEO_MIRROR_MODE_TYPE) instead.
     * Sets the video display mode for a specified remote user.
     * @param userId The ID of the remote user.
     * @param renderMode The video display mode to set. See RENDER_MODE_TYPE for options.
     * @return
     * - 0: Success.
     * - < 0: Failure.
     */
    virtual int setRemoteRenderMode(uid_t userId, RENDER_MODE_TYPE renderMode) = 0;

    /**
     * Updates the display mode for a remote user's video view, including rendering and mirror modes.
     * @param userId The ID of the remote user.
     * @param renderMode The rendering mode of the remote video view. See RENDER_MODE_TYPE for options.
     * @param mirrorMode The mirror mode of the remote video view. See VIDEO_MIRROR_MODE_TYPE for options.
     * @note This method only affects the local user's view of the remote video.
     * @return
     * - 0: Success.
     * - < 0: Failure.
     */
    virtual int setRemoteRenderMode(uid_t userId, RENDER_MODE_TYPE renderMode, VIDEO_MIRROR_MODE_TYPE mirrorMode) = 0;

    /**
     * Enables or disables dual-stream mode for the live broadcast scenario.
     * @param enabled true to enable dual-stream mode, false to disable and use single-stream mode.
     */
    virtual int enableDualStreamMode(bool enabled) = 0;

    /**
     * Sets the audio recording format for the onRecordAudioFrame callback.
     * @param sampleRate The sample rate in Hz for the recorded audio.
     * @param channel The number of audio channels (1 for mono, 2 for stereo).
     * @param mode The operation mode for the audio frame callback. See RAW_AUDIO_FRAME_OP_MODE_TYPE for options.
     * @param samplesPerCall The number of samples per callback call, often set to 1024 for streaming.
     * @note Ensure the sample interval is no less than 0.01 seconds.
     * @return
     * - 0: Success.
     * - 0: Failure.
     */
    virtual int setRecordingAudioFrameParameters(int sampleRate, int channel, RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall) = 0;

    /**
     * Sets the audio playback format for the onPlaybackAudioFrame callback.
     * @param sampleRate The sample rate in Hz for the played audio.
     * @param channel The number of audio channels (1 for mono, 2 for stereo).
     * @param mode The operation mode for the audio frame callback. See RAW_AUDIO_FRAME_OP_MODE_TYPE for options.
     * @param samplesPerCall The number of samples per callback call, often set to 1024 for streaming.
     * @note Ensure the sample interval is no less than 0.01 seconds.
     * @return
     * - 0: Success.
     * - < 0: Failure.
     */
    virtual int setPlaybackAudioFrameParameters(int sampleRate, int channel, RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall) = 0;

    /**
     * Sets the audio format for the onMixedAudioFrame callback, which handles mixed audio frames.
     * @param sampleRate The sample rate in Hz for the mixed audio. Common values are 8000, 16000, 32000, 44100, or 48000.
     * @param samplesPerCall The number of audio samples returned per callback. Commonly set to 1024 for streaming applications.
     * @note The onMixedAudioFrame callback is triggered based on the sample interval, which should be at least 0.01 seconds.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates an error occurred.
     */
    virtual int setMixedAudioFrameParameters(int sampleRate, int samplesPerCall) = 0;

    /**
     * Adjusts the volume of the audio recording signal.
     * @param volume The recording volume. Valid range: [0, 400].
     * - 0: Mute.
     * - 100: Original volume.
     * - 400: Maximum volume with signal clipping protection.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates an error occurred.
     */
    virtual int adjustRecordingSignalVolume(int volume) = 0;

    /**
     * Adjusts the volume of the audio mixing.
     * @param volume The audio mixing volume. The valid range is typically between 0 and 100.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates an error occurred.
     */
    virtual int adjustAudioMixingVolume(int volume) = 0;

    /**
     * Adjusts the playback volume for all remote users.
     * @param volume The playback volume for all remote users. Valid range: [0, 400].
     * - 0: Mute.
     * - 100: Original volume.
     * - 400: Maximum volume with signal clipping protection.
     * @note To mute local audio playback, set the volume to 0 using both adjustPlaybackSignalVolume and adjustAudioMixingVolume.
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates an error occurred.
     */
    virtual int adjustPlaybackSignalVolume(int volume) = 0;

    /**
     * Adjusts the loopback recording volume.
     * @param volume The loopback recording volume. Valid range: [0, 100].
     * @return
     * - 0: Indicates the operation was successful.
     * - Negative value: Indicates an error occurred.
     */
    virtual int adjustLoopbackRecordingSignalVolume(int volume) = 0;

    /**
     * @deprecated As of v3.0.0, the Native SDK automatically enables interoperability with the Web SDK, making this method obsolete.
     * Enables interoperability with the Aopa Web SDK.
     * @note
     * - Only applicable to the Live-broadcast profile. In Communication profile, Web SDK interoperability is enabled by default.
     * - Ensure this method is called if the channel includes Web SDK users to prevent video black screen issues for Web users.
     * @param enabled true to enable, false to disable interoperability with the Aopa Web SDK.
     * @return
     * - 0: Success.
     * - < 0: Failure.
     */
    virtual int enableWebSdkInteroperability(bool enabled) = 0;


    #if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
    // ... Additional methods with updated comments ...

    /**
     * Switches between the front and rear cameras on Android and iOS devices.
     * @return
     * - 0: Success.
     * - < 0: Failure.
     */
    virtual int switchCamera() = 0;

    /**
     * Sets the default audio route for playback before joining a channel.
     * @param defaultToSpeaker true to default to speakerphone, false to earpiece.
     * @return
     * - 0: Success.
     * - < 0: Failure.
     */
    virtual int setDefaultAudioRouteToSpeakerphone(bool defaultToSpeaker) = 0;

    /**
     * Enables or disables the speakerphone as the audio route for playback.
     * @param speakerOn true to use speakerphone, false to use earpiece.
     * @return
     * - 0: Success.
     * - < 0: Failure.
     */
    virtual int setEnableSpeakerphone(bool speakerOn) = 0;

    /**
     * Enables in-ear monitoring on Android and iOS devices.
     * @param enabled true to enable, false to disable in-ear monitoring.
     * @return
     * - 0: Success.
     * - < 0: Failure.
     */
    virtual int enableInEarMonitoring(bool enabled) = 0;

    /**
     * Sets the volume of the in-ear monitor for Android and iOS devices.
     * @param volume The volume level for the in-ear monitor, ranging from 0 to 100.
     * @return
     * - 0: Success.
     * - < 0: Failure.
     */
    virtual int setInEarMonitoringVolume(int volume) = 0;

    /**
     * Checks whether the speakerphone is currently enabled.
     * @return true if the speakerphone is enabled, false otherwise.
     */
    virtual bool isSpeakerphoneEnabled() = 0;
#endif


    #if (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE) || defined(_WIN32)
        /**
         * Enables or disables loopback recording, capturing the output of the sound card.
         * When loopback recording is enabled, the audio output from the sound card is mixed into the
         * audio stream that is sent to other users in the call.
         * @param enabled true to enable loopback recording, false to disable it.
         * @param deviceName Optional. The name of the sound card device to use for loopback recording.
         *        If set to NULL (default), the system's default sound card is used.
         * @note
         * - This functionality is only supported on macOS and Windows operating systems.
         * - macOS does not support loopback recording for the default sound card. For macOS, use a
         *   virtual sound card like Soundflower, and provide its name as the deviceName parameter.
         *   Aopa's testing recommends using Soundflower for the best experience on macOS.
         * @return
         * - 0: Indicates the operation was successful.
         * - Negative value: Indicates an error occurred, such as an invalid device name or unsupported operation.
         */
        virtual int enableLoopbackRecording(bool enabled, const char* deviceName = nullptr) = 0;
    #endif

    #if defined(_WIN32)
        /**
         * Sets a custom video source for the SDK, allowing the use of a non-default video input.
         * By default, the SDK captures video from the built-in camera. This method enables the use of
         * a custom video source, such as an external camera or a virtual camera, by implementing the IVideoSource interface.
         *
         * @param source A pointer to the custom video source object. If set to NULL, the SDK reverts to using the default video source.
         *        See IVideoSource for more details on how to implement a custom video source.
         * @note
         * - The custom video source must be implemented with the IVideoSource interface.
         * - This method can be called either before or after joining a channel to apply the custom video source.
         * - The SDK takes ownership of the video source object and manages its lifecycle.
         *
         * @return
         * - true: Indicates the custom video source was successfully added to the SDK.
         * - false: Indicates a failure to add the custom video source to the SDK, possibly due to an invalid implementation or the object being already in use.
         */
        virtual bool setVideoSource(IVideoSource* source) = 0;
    #endif
    /**
     * Retrieves the version number of the SDK.
     * @param build If not NULL, the method also returns the build number of the SDK.
     * @return A string representing the version of the current SDK, such as "2.3.1".
     */
    virtual const char* getVersion(int* build) = 0;

    /**
     * Enables built-in encryption for the SDK with a specified password before joining a channel.
     * All users in the same channel must use the same encryption password, which is cleared upon leaving the channel.
     * If no password is set, encryption is disabled.
     * @note
     * - Not recommended for CDN live streaming.
     * - Ensure encrypted data size does not exceed original size + 16 bytes (AES encryption padding).
     * @param secret The encryption password to be used.
     * @return
     * - 0: Indicates success.
     * - Negative value: Indicates failure.
     */
    virtual int setEncryptionSecret(const char* secret) = 0;

    /**
     * Sets the encryption mode for the built-in encryption feature of the SDK.
     * @note
     * - Call setEncryptionSecret first to enable encryption.
     * - All users in the channel must use the same mode and password.
     * @param encryptionMode The encryption mode to set (e.g., "aes-128-xts", "aes-128-ecb", "aes-256-xts").
     * @return
     * - 0: Indicates success.
     * - Negative value: Indicates failure.
     */
    virtual int setEncryptionMode(const char* encryptionMode) = 0;

    /**
     * Creates a data stream for sending and receiving data.
     * @note
     * - Up to five data streams can be created per user.
     * - Set both reliable and ordered parameters consistently (both true or both false).
     * @param streamId The ID assigned to the created data stream.
     * @param reliable true if the data stream must be received by the recipient within 5 seconds; otherwise, false.
     * @param ordered true if the data stream must be received in the sent order; otherwise, false.
     * @return
     * - 0: Indicates success.
     * - Negative value: Indicates failure.
     */
    virtual int createDataStream(int* streamId, bool reliable, bool ordered) = 0;

    /**
     * Sends data through a specified data stream to all users in the channel.
     * @note
     * - Limited to 30 packets per second per channel, with each packet up to 1 kB in size.
     * - Each client can send up to 6 kB of data per second.
     * - Each user can have up to five data streams simultaneously.
     * - Use createDataStream to obtain a stream ID before sending data.
     * @param streamId The ID of the data stream for sending messages.
     * @param data Pointer to the data to be sent.
     * @param length The length of the data to be sent.
     * @return
     * - 0: Indicates success.
     * - Negative value: Indicates failure.
     */
    virtual int sendStreamMessage(int streamId, const char* data, size_t length) = 0;

    /**
     * Publishes the local stream to a specified CDN live RTMP address.
     * @note
     * - Call this method after joining the channel.
     * - Ensure the RTMP Converter service is enabled.
     * - Only one RTMP URL can be added per method call.
     * - This method is only applicable for Live Broadcast profiles.
     * @param url The RTMP URL to which the stream is published.
     * @param transcodingEnabled true to enable transcoding of the published stream; false to disable it.
     * @return
     * - 0: Indicates success.
     * - Negative value: Indicates failure, such as invalid arguments or uninitialized RTC engine.
     */
    virtual int addPublishStreamUrl(const char *url, bool transcodingEnabled) = 0;

        /**
     * Removes a specified RTMP streaming address from the ongoing CDN live broadcast.
     *
     * This function revokes an RTMP URL that was previously added through `addPublishStreamUrl`. The outcome of this operation is notified via the `onStreamUnpublished` callback. Additionally, invoking this method triggers the `onRtmpStreamingStateChanged` callback locally, providing updates on the status of the RTMP stream removal from the CDN.
     *
     * @note
     * - Only a single RTMP URL is processed per method call.
     * - The RTMP URL must be alphanumeric and should avoid special characters, excluding common punctuation.
     * - This feature is exclusive to the Live Broadcast profile.

    * @param url The RTMP streaming URL to be revoked, with a maximum allowable length of 1024 bytes.

    * @return
    * - 0: The operation was successful.
    * - < 0: An error occurred, refer to specific error codes for details.
    */
    virtual int removePublishStreamUrl(const char *url) = 0;

    /**
     * Configures video layout and audio settings for CDN live streaming in Live Broadcast mode.
     *
     * Upon updating the transcoding configuration via `setLiveTranscoding`, the SDK initiates the `onTranscodingUpdated` callback to notify about the setting change.
     *
     * @note
     * - This function is applicable solely within the Live Broadcast scenario.
     * - Prior to utilizing this function, ensure the RTMP Converter service is activated. Refer to the [Prerequisites](https://docs.bb.io/en/Interactive%20Broadcast/cdn_streaming_windows?platform=Windows#prerequisites) for setup instructions.
     * - The initial invocation of `setLiveTranscoding` to establish transcoding settings will not elicit the `onTranscodingUpdated` callback.

    * @param transcoding An instance of `LiveTranscoding` struct containing detailed configurations for audio and video transcoding tailored for CDN live streaming.

    * @return
    * - 0: The operation completed successfully.
    * - < 0: An error was encountered, consult specific return values for more information.
    */
    virtual int setLiveTranscoding(const LiveTranscoding &transcoding) = 0;

    /**
     * Configures the fallback strategy for the local publishing stream in case of network issues.
     *
     * This method sets the action to be taken when the local stream publication encounters network congestion or failure. The behavior is defined by the `STREAM_FALLBACK_OPTIONS` enum provided as the `option` parameter.
     *
     * @param option An enumeration value from `STREAM_FALLBACK_OPTIONS` specifying the fallback strategy for handling local stream publish disruptions.
     *
     * @return
     * - 0: The fallback option was set successfully.
     * - < 0: An error occurred during the setting process.
     */
    virtual int setLocalPublishFallbackOption(STREAM_FALLBACK_OPTIONS option) = 0;

    /**
     * Specifies the fallback behavior for remote subscription in the event of network degradation.
     *
     * Determines how the system should react when the subscribed remote stream quality deteriorates due to network conditions. The reaction strategy is determined by the `STREAM_FALLBACK_OPTIONS` value passed as `option`.
     *
     * @param option A `STREAM_FALLBACK_OPTIONS` enum member indicating the fallback action to take when the remote stream subscription encounters network problems.
     *
     * @return
     * - 0: The remote subscribe fallback option was configured successfully.
     * - < 0: An error was encountered while setting the fallback option.
     */
    virtual int setRemoteSubscribeFallbackOption(STREAM_FALLBACK_OPTIONS option) = 0;


    #if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
    virtual int switchCamera2(CAMERA_DIRECTION direction) = 0;
    #endif

        /**
     * Adjusts image enhancement settings and toggles the feature on or off.
     *
     * @note
     * - Invoke this function after enabling video functionality with `enableVideo`.
     * - Currently unsupported on macOS platforms.

    * @param enabled A boolean flag to control image enhancement activation:
    *   - `true`: Enables image enhancement features.
    *   - `false`: Disables image enhancement features.
    * @param options An instance of `BeautyOptions` struct to customize the image enhancement parameters.
    *
    * @return
    * - 0: The operation was successful.
    * - < 0: An error occurred, refer to error codes for specifics.
    */
    virtual int setBeautyEffectOptions(bool enabled, BeautyOptions options) = 0;

    /**
     * Incorporates an external voice or video stream into an ongoing live broadcast.
     *
     * Utilize this method to introduce online media streams into a live channel, enhancing audience engagement. The `onStreamPublished` callback signals the injection status. Upon success, the server fetches the stream and integrates it into the live session.
     *
     * Triggers the following callbacks:
     * - Locally:
     - `onStreamInjectedStatus`, reflecting the stream injection status.
    - `onUserJoined` (with `uid: 666`), upon successful injection of the stream into the channel.
    * - Remotely:
    - `onUserJoined` (also with `uid: 666`), for other users when the stream is effectively integrated.

    * @note
    * - Ensure the RTMP Converter service is active prior to use. Refer to [Prerequisites](https://docs.bb.io/en/Interactive%20Broadcast/cdn_streaming_windows?platform=Windows#prerequisites).
    * - Applicable for Native SDK versions 2.4.1 onwards.

    * @param url A pointer to the stream's URL (RTMP, HLS, or FLV format). 
    - FLV supports AAC audio codec.
    - FLV supports H264 (AVC) video codec.
    * @param config A reference to an `InjectStreamConfig` object detailing the stream's configuration.

    * @return
    * - 0: The stream URL was successfully added.
    * - < 0: An error occurred, including but not limited to:
    - `ERR_INVALID_ARGUMENT` (2): Invalid URL. Retry with a valid URL.
    - `ERR_NOT_READY` (3): The user is not in a channel.
    - `ERR_NOT_SUPPORTED` (4): Incorrect channel profile. Set to live broadcast using `setChannelProfile` beforehand.
    - `ERR_NOT_INITIALIZED` (7): The SDK is uninitialized. Initialize `IRtcEngine` first.
    */
    virtual int addInjectStreamUrl(const char* url, const InjectStreamConfig& config) = 0;

        /**
     * Initiates real-time media stream relay across multiple channels.
     *
     * Upon a successful invocation, the SDK triggers:
     * - \ref bb::rtc::IRtcEngineEventHandler::onChannelMediaRelayStateChanged "onChannelMediaRelayStateChanged": Reports the relay's state changes.
     * - \ref bb::rtc::IRtcEngineEventHandler::onChannelMediaRelayEvent "onChannelMediaRelayEvent": Notifies about relay-related events.
     * 
     * **Callback Scenarios:**
     * - If \ref bb::rtc::IRtcEngineEventHandler::onChannelMediaRelayStateChanged "onChannelMediaRelayStateChanged" returns #RELAY_STATE_RUNNING (2) and #RELAY_OK (0),
     and \ref bb::rtc::IRtcEngineEventHandler::onChannelMediaRelayEvent "onChannelMediaRelayEvent" returns #RELAY_EVENT_PACKET_SENT_TO_DEST_CHANNEL (4), 
    the media relay has started, and the broadcaster is transmitting to the target channel.
    * - If \ref bb::rtc::IRtcEngineEventHandler::onChannelMediaRelayStateChanged "onChannelMediaRelayStateChanged" returns #RELAY_STATE_FAILURE (3), 
    an error has occurred during the relay process.

    * @note
    * - Ensure to call this after successfully joining a channel via \ref joinChannel().
    * - Applicable only when acting as a broadcaster in a live-broadcast channel.
    * - For subsequent relay configurations, invoke \ref stopChannelMediaRelay() before calling this method again.
    * - Consult with sales-us@bb.io prior to implementation.
    * - Usernames as strings are not supported in this API.

    * @param configuration The structure defining the relay configuration: ChannelMediaRelayConfiguration.

    * @return
    * - 0: Operation successful.
    * - < 0: An error occurred.
    */
    virtual int startChannelMediaRelay(const ChannelMediaRelayConfiguration &configuration) = 0;

    /**
     * Modifies the destination channels for an ongoing media stream relay.
     *
     * Use this method post-\ref startChannelMediaRelay() to modify relay destinations:
     * add new channels or abandon the current one.
     * 
     * Upon successful execution, the SDK triggers the
     * \ref bb::rtc::IRtcEngineEventHandler::onChannelMediaRelayEvent "onChannelMediaRelayEvent" callback
     * with the event code #RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL (7).

    * @note
    * Execute this after \ref startChannelMediaRelay() to alter the target channels.

    * @param configuration The updated media stream relay configuration: ChannelMediaRelayConfiguration.

    * @return
    * - 0: Operation successful.
    * - < 0: An error occurred.
    */
    virtual int updateChannelMediaRelay(const ChannelMediaRelayConfiguration &configuration) = 0;

        /**
     * Terminates the ongoing media stream relay process.
     *
     * Upon stopping, the broadcaster is disconnected from all destination channels.
     *
     * Post-execution, the \ref bb::rtc::IRtcEngineEventHandler::onChannelMediaRelayStateChanged
     *  "onChannelMediaRelayStateChanged" callback signifies the relay status change.
     * A return of #RELAY_STATE_IDLE (0) and #RELAY_OK (0) confirms a successful relay halt.

    * @note
    * In case of failure, the SDK issues the
    * \ref bb::rtc::IRtcEngineEventHandler::onChannelMediaRelayStateChanged
    *  "onChannelMediaRelayStateChanged" callback with either
    * #RELAY_ERROR_SERVER_NO_RESPONSE (2) or #RELAY_ERROR_SERVER_CONNECTION_LOST (8).
    * Exiting the channel via \ref leaveChannel() also discontinues the relay.

    * @return
    * - 0: Operation completed successfully.
    * - < 0: An error was encountered.
    */
    virtual int stopChannelMediaRelay() = 0;

    /**
     * Eliminates a previously injected voice or video stream URL from the live broadcast.
     *
     * This function revokes the integration of a stream URL (previously attached using
     * \ref IRtcEngine::addInjectStreamUrl) from the ongoing live session.
     *
     * @note A successful execution prompts the \ref IRtcEngineEventHandler::onUserOffline
     *  "onUserOffline" callback, indicating the disconnection of a stream with a UID of 666.

    * @param url Pointer directing to the stream URL string scheduled for removal.

    * @return
    * - 0: The operation was successful.
    * - < 0: An error transpired.
    */
    virtual int removeInjectStreamUrl(const char* url) = 0;

        /**
     * Registers a callback handler for real-time communication events.
     *
     * @param eventHandler Pointer to the event handler object.
     *
     * @return
     * - `true`: Registration successful.
     * - `false`: Registration failed.
     */
    virtual bool registerEventHandler(IRtcEngineEventHandler *eventHandler) = 0;

    /**
     * Unregisters a previously registered callback handler.
     *
     * @param eventHandler Pointer to the event handler object to unregister.
     *
     * @return
     * - `true`: Unregistration successful.
     * - `false`: Unregistration failed.
     */
    virtual bool unregisterEventHandler(IRtcEngineEventHandler *eventHandler) = 0;

    /**
     * Retrieves the current connectivity status of the SDK.
     *
     * @return The current #CONNECTION_STATE_TYPE.
     */
    virtual CONNECTION_STATE_TYPE getConnectionState() = 0;

    /**
     * Configures SDK behaviors and enables experimental features through JSON parameters.
     *
     * Note: These JSON options are currently non-public. Aopa is actively working towards exposing common options through standardized APIs.
     *
     * @param parameters A JSON-formatted string containing the desired configuration parameters.
     *
     * @return
     * - 0: Configuration successful.
     * - < 0: Configuration failed.
     */
    virtual int setParameters(const char* parameters) = 0;

    // Added by bhb on 2020/06/09
    /**
     * Specifies the output directory for SDK dump files.
     *
     * @param dir Path to the designated directory.
     *
     * @return
     * - 0: Success.
     * - < 0: Failure.
     */
    virtual int setDumpOutputDirectory(const char* dir) = 0;

    /**
     * Enables or disables SDK dump file generation.
     *
     * @param enabled `true` to enable, `false` to disable.
     *
     * @return
     * - 0: Operation successful.
     * - < 0: Operation failed.
     */
    virtual int enableDump(bool enabled) = 0;

    // Added by bhb on 2021/03/26
    /**
     * Applies a predefined audio effect preset.
     *
     * @param preset The selected #AUDIO_EFFECT_PRESET.
     *
     * @return
     * - 0: Preset applied successfully.
     * - < 0: Application failed.
     */
    virtual int setAudioEffectPreset(AUDIO_EFFECT_PRESET preset) = 0;

    /**
     * Selects a voice beautifier preset.
     *
     * @param preset The chosen #VOICE_BEAUTIFIER_PRESET.
     *
     * @return
     * - 0: Preset set successfully.
     * - < 0: Setting failed.
     */
    virtual int setVoiceBeautifierPreset(VOICE_BEAUTIFIER_PRESET preset) = 0;

    /**
     * Adjusts low-light enhancement settings.
     *
     * @param enabled `true` to enable, `false` to disable.
     * @param options Detailed enhancement options.
     *
     * @return
     * - 0: Settings applied successfully.
     * - < 0: Application failed.
     */
    virtual int setLowlightEnhanceOptions(bool enabled, LowLightEnhanceOptions options) = 0;

    /**
     * Retrieves the duration of the captured voice in milliseconds.
     *
     * @return The duration of the voice in milliseconds, or an error code if failed.
     */
    virtual int getVoiceDuration() = 0;
};


class IRtcEngineParameter
{
public:
    virtual ~IRtcEngineParameter(){}
    /**
    * Releases all IRtcEngineParameter resources.
    */
    virtual void release() = 0;

    /** Sets the bool value of a specified key in the JSON format.

     @param key Pointer to the name of the key.
     @param value Sets the value.
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setBool(const char* key, bool value) = 0;

    /** Sets the int value of a specified key in the JSON format.

     @param key Pointer to the name of the key.
     @param value Sets the value.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setInt(const char* key, int value) = 0;

    /** Sets the unsigned int value of a specified key in the JSON format.

     @param key Pointer to the name of the key.
     @param value Sets the value.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setUInt(const char* key, unsigned int value) = 0;

    /** Sets the double value of a specified key in the JSON format.

     @param key Pointer to the name of the key.
     @param value Sets the value.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setNumber(const char* key, double value) = 0;

    /** Sets the string value of a specified key in the JSON format.

     @param key Pointer to the name of the key.
     @param value Pointer to the set value.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setString(const char* key, const char* value) = 0;

    /** Sets the object value of a specified key in the JSON format.

     @param key Pointer to the name of the key.
     @param value Pointer to the set value.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setObject(const char* key, const char* value) = 0;

    /** Retrieves the bool value of a specified key in the JSON format.

     @param key Pointer to the name of the key.
     @param value Pointer to the retrieved value.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getBool(const char* key, bool& value) = 0;

    /** Retrieves the int value of the JSON format.

     @param key Pointer to the name of the key.
     @param value Pointer to the retrieved value.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getInt(const char* key, int& value) = 0;

    /** Retrieves the unsigned int value of a specified key in the JSON format.

     @param key Pointer to the name of the key.
     @param value Pointer to the retrieved value.
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getUInt(const char* key, unsigned int& value) = 0;

    /** Retrieves the double value of a specified key in the JSON format.

     @param key Pointer to the name of the key.
     @param value Pointer to the retrieved value.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getNumber(const char* key, double& value) = 0;

    /** Retrieves the string value of a specified key in the JSON format.

     @param key Pointer to the name of the key.
     @param value Pointer to the retrieved value.

     @return
     - 0: Success.
     - < 0: Failure.
    */
    virtual int getString(const char* key, bbrtc::util::AString& value) = 0;

    /** Retrieves a child object value of a specified key in the JSON format.

     @param key Pointer to the name of the key.
     @param value Pointer to the retrieved value.
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getObject(const char* key, bbrtc::util::AString& value) = 0;

    /** Retrieves the array value of a specified key in the JSON format.

     @param key Pointer to the name of the key.
     @param value Pointer to the retrieved value.
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getArray(const char* key, bbrtc::util::AString& value) = 0;

    /** Provides the technical preview functionalities or special customizations by configuring the SDK with JSON options.

     @param parameters Pointer to the set parameters in a JSON string.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setParameters(const char* parameters) = 0;

    /** Sets the profile to control the RTC engine.

     @param profile Pointer to the set profile.
     @param merge Sets whether to merge the profile data with the original value:
     - true: Merge the profile data with the original value.
     - false: Do not merge the profile data with the original value.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setProfile(const char* profile, bool merge) = 0;

    virtual int convertPath(const char* filePath, bbrtc::util::AString& value) = 0;
};

class AAudioDeviceManager : public bbrtc::util::AutoPtr<IAudioDeviceManager>
{
public:
    AAudioDeviceManager(IRtcEngine* engine)
    {
        queryInterface(engine, BBRTC_IID_AUDIO_DEVICE_MANAGER);
    }
};

class AParameter : public bbrtc::util::AutoPtr<IRtcEngineParameter>
{
public:
    AParameter(IRtcEngine& engine) { initialize(&engine); }
    AParameter(IRtcEngine* engine) { initialize(engine); }
    AParameter(IRtcEngineParameter* p) :bbrtc::util::AutoPtr<IRtcEngineParameter>(p) {}
private:
    bool initialize(IRtcEngine* engine)
    {
        IRtcEngineParameter* p = NULL;
        if (engine && !engine->queryInterface(BBRTC_IID_RTC_ENGINE_PARAMETER, (void**)&p))
            reset(p);
        return p != NULL;
    }
};

} // namespace bbrtc



////////////////////////////////////////////////////////
/** \addtogroup createBBRtcEngine
 @{
 */
////////////////////////////////////////////////////////

/** Creates the IRtcEngine object and returns the pointer.
 *
 * @return Pointer to the IRtcEngine object.
 */
BB_API bbrtc::IRtcEngine* BB_CALL createRtcEngine();

BB_API void BB_CALL releaseRtcEngine(bbrtc::IRtcEngine*);

BB_API void BB_CALL setRtcServerAddress(const char*);

#endif /* IBBRtcEngine_h */
