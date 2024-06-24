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


/**
 * Defines the maximum lengths for various identifiers within the media engine.
 */

/**
 * The maximum length of the device ID in bytes.
 */
enum MAX_DEVICE_ID_LENGTH_TYPE {
  MAX_DEVICE_ID_LENGTH = 512,  /**< The device ID should not exceed 512 bytes. */
};

/**
 * The maximum length of the user account string in bytes.
 */
enum MAX_USER_ACCOUNT_LENGTH_TYPE {
  MAX_USER_ACCOUNT_LENGTH = 256,  /**< The user account should not exceed 255 bytes. */
};

/**
 * The maximum length of the channel ID in bytes.
 */
enum MAX_CHANNEL_ID_LENGTH_TYPE {
  MAX_CHANNEL_ID_LENGTH = 65,  /**< The channel ID should not exceed 64 bytes. */
};

/**
 * Formats available for the quality report.
 */
enum QUALITY_REPORT_FORMAT_TYPE {
  QUALITY_REPORT_JSON = 0,  /**< Quality report in JSON format. */
  QUALITY_REPORT_HTML = 1,  /**< Quality report in HTML format. */
};

/**
 * Event codes for media engine events.
 */
enum MEDIA_ENGINE_EVENT_CODE_TYPE {
  MEDIA_ENGINE_AUDIO_EVENT_MIXING_ALL_LOOPS_COMPLETED = 723,  /**< For internal use only. */
};

/**
 * States of the local user's audio mixing file.
 */
enum AUDIO_MIXING_STATE_TYPE {
  AUDIO_MIXING_STATE_PLAYING = 710,  /**< The audio mixing file is currently playing. */
  AUDIO_MIXING_STATE_PAUSED = 711,  /**< The audio mixing file is paused. */
  AUDIO_MIXING_STATE_STOPPED = 713,  /**< The audio mixing file has stopped. */
  AUDIO_MIXING_STATE_FAILED = 714,  /**< An error occurred during playback of the audio mixing file. */
};

/**
 * Error codes associated with the local user's audio mixing file.
 */
enum AUDIO_MIXING_ERROR_TYPE {
  AUDIO_MIXING_ERROR_CAN_NOT_OPEN = 701,  /**< The SDK cannot open the audio mixing file. */
  AUDIO_MIXING_ERROR_TOO_FREQUENT_CALL = 702,  /**< The SDK is opening the audio mixing file too frequently. */
  AUDIO_MIXING_ERROR_INTERRUPTED_EOF = 703,  /**< The audio mixing file playback is interrupted. */
  AUDIO_MIXING_ERROR_NETWORK_UNSTABLE = 705,  /**< The network is unstable during audio mixing. */
  AUDIO_MIXING_ERROR_OK = 0,  /**< No error; the SDK successfully opens the audio mixing file. */
};

/**
 * Reasons for changes in the audio mixing state.
 */
enum AUDIO_MIXING_REASON_TYPE {
  AUDIO_MIXING_REASON_CAN_NOT_OPEN = 701,  /**< The SDK cannot open the audio mixing file. */
  AUDIO_MIXING_REASON_TOO_FREQUENT_CALL = 702,  /**< The audio mixing file is opened too frequently. */
  AUDIO_MIXING_REASON_INTERRUPTED_EOF = 703,  /**< The playback is interrupted. */
  AUDIO_MIXING_REASON_STARTED_BY_USER = 720,  /**< The audio mixing is started by the user. */
  AUDIO_MIXING_REASON_ONE_LOOP_COMPLETED = 721,  /**< The audio mixing file has played once. */
  AUDIO_MIXING_REASON_START_NEW_LOOP = 722,  /**< The audio mixing starts a new loop. */
  AUDIO_MIXING_REASON_ALL_LOOPS_COMPLETED = 723,  /**< All loops of the audio mixing have been played. */
  AUDIO_MIXING_REASON_STOPPED_BY_USER = 724,  /**< The user has stopped the audio mixing. */
  AUDIO_MIXING_REASON_PAUSED_BY_USER = 725,  /**< The user has paused the audio mixing. */
  AUDIO_MIXING_REASON_RESUMED_BY_USER = 726,  /**< The user has resumed the audio mixing. */
};

/**
 * States of media devices.
 */
enum MEDIA_DEVICE_STATE_TYPE {
  MEDIA_DEVICE_STATE_ACTIVE = 1,    /**< The device is active and ready for use. */
  MEDIA_DEVICE_STATE_DISABLED = 2,   /**< The device is disabled and not available. */
  MEDIA_DEVICE_STATE_NOT_PRESENT = 4,/**< The device is not present on the system. */
  MEDIA_DEVICE_STATE_UNPLUGGED = 8, /**< The device is unplugged and not connected. */
};

/**
 * Types of media devices.
 */
enum MEDIA_DEVICE_TYPE {
  UNKNOWN_AUDIO_DEVICE = -1,     /**< The device type is unknown. */
  AUDIO_PLAYOUT_DEVICE = 0,       /**< The device is an audio playback device. */
  AUDIO_RECORDING_DEVICE = 1,     /**< The device is an audio recording device. */
  VIDEO_RENDER_DEVICE = 2,        /**< The device is a video renderer. */
  VIDEO_CAPTURE_DEVICE = 3,       /**< The device is a video capturer. */
  AUDIO_APPLICATION_PLAYOUT_DEVICE = 4, /**< The device is an application-specific audio playback device. */
};

/**
 * States of the local video stream.
 */
enum LOCAL_VIDEO_STREAM_STATE {
  LOCAL_VIDEO_STREAM_STATE_STOPPED = 0,   /**< The local video is in the initial stopped state. */
  LOCAL_VIDEO_STREAM_STATE_CAPTURING = 1, /**< The capturer has started successfully. */
  LOCAL_VIDEO_STREAM_STATE_ENCODING = 2,  /**< The first video frame has been successfully encoded. */
  LOCAL_VIDEO_STREAM_STATE_FAILED = 3,   /**< The local video has failed to start. */
};

/**
 * Local video state error codes indicating the status of the local video stream.
 */
enum LOCAL_VIDEO_STREAM_ERROR {
    LOCAL_VIDEO_STREAM_ERROR_OK = 0, /**< The local video is functioning normally. */
    LOCAL_VIDEO_STREAM_ERROR_FAILURE = 1, /**< The local video has failed for an unspecified reason. */
    LOCAL_VIDEO_STREAM_ERROR_DEVICE_NO_PERMISSION = 2, /**< Lack of permission to use the local video capturing device. */
    LOCAL_VIDEO_STREAM_ERROR_DEVICE_BUSY = 3, /**< The local video capturing device is currently in use. */
    LOCAL_VIDEO_STREAM_ERROR_CAPTURE_FAILURE = 4, /**< The local video capture has failed. */
    LOCAL_VIDEO_STREAM_ERROR_ENCODE_FAILURE = 5, /**< The local video encoding has failed. */
};

/**
 * Local audio state types representing the different states of the local audio stream.
 */
enum LOCAL_AUDIO_STREAM_STATE {
    LOCAL_AUDIO_STREAM_STATE_STOPPED = 0, /**< The local audio is in the initial stopped state. */
    LOCAL_AUDIO_STREAM_STATE_RECORDING = 1, /**< The recording device has started successfully. */
    LOCAL_AUDIO_STREAM_STATE_ENCODING = 2, /**< The first audio frame has been encoded successfully. */
    LOCAL_AUDIO_STREAM_STATE_FAILED = 3, /**< The local audio has failed to start. */
};

/**
 * Local audio state error codes indicating issues with the local audio stream.
 */
enum LOCAL_AUDIO_STREAM_ERROR {
    LOCAL_AUDIO_STREAM_ERROR_OK = 0, /**< The local audio is functioning normally. */
    LOCAL_AUDIO_STREAM_ERROR_FAILURE = 1, /**< The local audio has failed for an unspecified reason. */
    LOCAL_AUDIO_STREAM_ERROR_DEVICE_NO_PERMISSION = 2, /**< Lack of permission to use the local audio device. */
    LOCAL_AUDIO_STREAM_ERROR_DEVICE_BUSY = 3, /**< The microphone is currently in use. */
    LOCAL_AUDIO_STREAM_ERROR_RECORD_FAILURE = 4, /**< The local audio recording has failed. */
    LOCAL_AUDIO_STREAM_ERROR_ENCODE_FAILURE = 5, /**< The local audio encoding has failed. */
};

/**
 * Audio recording qualities defining the quality of the audio recording.
 */
enum AUDIO_RECORDING_QUALITY_TYPE {
    AUDIO_RECORDING_QUALITY_LOW = 0, /**< Low quality with a sample rate of 32 kHz, resulting in approximately 1.2 MB file size after 10 minutes of recording. */
    AUDIO_RECORDING_QUALITY_MEDIUM = 1, /**< Medium quality with a sample rate of 32 kHz, resulting in approximately 2 MB file size after 10 minutes of recording. */
    AUDIO_RECORDING_QUALITY_HIGH = 2, /**< High quality with a sample rate of 32 kHz, resulting in approximately 3.75 MB file size after 10 minutes of recording. */
};

/**
 * Network quality types representing the quality of the network connection during a call.
 */
enum QUALITY_TYPE {
    QUALITY_UNKNOWN = 0, /**< The network quality is unknown. */
    QUALITY_EXCELLENT = 1, /**< The network quality is excellent. */
    QUALITY_GOOD = 2, /**< The network quality is good, but the bitrate may be slightly lower than excellent. */
    QUALITY_POOR = 3, /**< The network quality is poor, and users may experience slightly impaired communication. */
    QUALITY_BAD = 4, /**< The network quality is bad, and users cannot communicate smoothly. */
    QUALITY_VBAD = 5, /**< The network quality is very bad, making communication almost impossible. */
    QUALITY_DOWN = 6, /**< The network is down, and users cannot communicate at all. */
    QUALITY_UNSUPPORTED = 7, /**< The network quality cannot be detected (Not in use). */
    QUALITY_DETECTING = 8, /**< The network quality is currently being detected. */
};

/**
 * Video display modes for rendering video on the screen.
 */
enum RENDER_MODE_TYPE {
    RENDER_MODE_HIDDEN = 1, /**< Uniformly scale the video until it fills the visible area, potentially cropping one dimension. */
    RENDER_MODE_FIT = 2, /**< Uniformly scale the video until one dimension fits the boundary, filling unfilled areas with black bars. */
    RENDER_MODE_ADAPTIVE = 3, /**< Deprecated: This mode is no longer in use. */
    RENDER_MODE_FILL = 4, /**< Scale the video to fill the display window, possibly stretching or zooming the content. */
};

/**
 * Video mirror modes for enabling or disabling the mirror effect of the video.
 */
enum VIDEO_MIRROR_MODE_TYPE {
    VIDEO_MIRROR_MODE_AUTO = 0, /**< The mirror mode is determined automatically by the SDK. */
    VIDEO_MIRROR_MODE_ENABLED = 1, /**< The mirror mode is enabled. */
    VIDEO_MIRROR_MODE_DISABLED = 2, /**< The mirror mode is disabled. */
};

/** **DEPRECATED**: Enumerates different video profiles with specified resolutions, frame rates, and bitrates. */
enum VIDEO_PROFILE_TYPE
{
    ///< 160x120 at 15 fps with 65 Kbps.
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

/**
 * Enumerates the channel profiles for the Agora RtcEngine.
 */
typedef enum {
    /** (Default) The Communication profile. Use this for one-on-one calls or group calls where all users can talk freely. */
    CHANNEL_PROFILE_COMMUNICATION = 0,
    
    /** The Live-Broadcast profile. Users in a live-broadcast channel have roles as either broadcaster or audience. A broadcaster can both send and receive streams; an audience can only receive streams. */
    CHANNEL_PROFILE_LIVE_BROADCASTING = 1,
    
    /** The Gaming profile. This profile uses a codec with a lower bitrate and consumes less power, suitable for gaming scenarios where all players can talk freely. */
    CHANNEL_PROFILE_GAME = 2,
} CHANNEL_PROFILE_TYPE;

/**
 * Enumerates the client roles in a live broadcast.
 */
typedef enum {
    /** Host role in a live broadcast. */
    CLIENT_ROLE_BROADCASTER = 1,
    
    /** Audience role in a live broadcast. */
    CLIENT_ROLE_AUDIENCE = 2,
} CLIENT_ROLE_TYPE;

/**
 * Enumerates the client roles in a KTV chorus scenario.
 */
typedef enum {
    /** Invalid role in a KTV chorus. */
    CLIENT_ROLE_CHORUS_INVALID = 0,
    
    /** Lead Singer role in a KTV chorus. */
    CLIENT_ROLE_CHORUS_MAIN = 1,
    
    /** Deputy role in a KTV chorus. */
    CLIENT_ROLE_CHORUS_DEPUTY = 2,
} CLIENT_ROLE_CHORUS_TYPE;

/**
 * Enumerates the reasons for a user being offline.
 */
typedef enum {
    /** The user quits the call. */
    USER_OFFLINE_QUIT = 0,
    
    /** The user drops offline due to network issues or no data packet received within a certain period of time. */
    USER_OFFLINE_DROPPED = 1,
    
    /** (Live broadcast only) The client role switches from the host to the audience. */
    USER_OFFLINE_BECOME_AUDIENCE = 2,
} USER_OFFLINE_REASON_TYPE;

/**
 * Enumerates the states of the RTMP streaming.
 */
typedef enum {
    /** The RTMP streaming is idle or has not started, or has ended. Also triggered after removing an RTMP address from the CDN. */
    RTMP_STREAM_PUBLISH_STATE_IDLE = 0,
    
    /** The SDK is connecting to Agora's streaming server and the RTMP server. */
    RTMP_STREAM_PUBLISH_STATE_CONNECTING = 1,
    
    /** The RTMP streaming is publishing successfully. */
    RTMP_STREAM_PUBLISH_STATE_RUNNING = 2,
    
    /** The RTMP streaming is recovering after an interruption or exception. */
    RTMP_STREAM_PUBLISH_STATE_RECOVERING = 3,
    
    /** The RTMP streaming has failed. See the error code for detailed information. */
    RTMP_STREAM_PUBLISH_STATE_FAILURE = 4,
} RTMP_STREAM_PUBLISH_STATE;

/**
 * Enumerates the error codes of the RTMP streaming.
 */
typedef enum {
    /** The RTMP streaming is published successfully. */
    RTMP_STREAM_PUBLISH_ERROR_OK = 0,
    
    /** An invalid argument is used, such as not configuring LiveTranscoding parameters before adding a publish stream URL. */
    RTMP_STREAM_PUBLISH_ERROR_INVALID_ARGUMENT = 1,
    
    /** The RTMP streaming is encrypted and cannot be published. */
    RTMP_STREAM_PUBLISH_ERROR_ENCRYPTED_STREAM_NOT_ALLOWED = 2,
    
    /** A timeout occurred for the RTMP streaming. */
    RTMP_STREAM_PUBLISH_ERROR_CONNECTION_TIMEOUT = 3,
    
    /** An internal server error occurred in Agora's streaming server. */
    RTMP_STREAM_PUBLISH_ERROR_INTERNAL_SERVER_ERROR = 4,
    
    /** An error occurred in the RTMP server. */
    RTMP_STREAM_PUBLISH_ERROR_RTMP_SERVER_ERROR = 5,
    
    /** The RTMP streaming is published too frequently. */
    RTMP_STREAM_PUBLISH_ERROR_TOO_OFTEN = 6,
    
    /** The host has published more than 10 URLs. */
    RTMP_STREAM_PUBLISH_ERROR_REACH_LIMIT = 7,
    
    /** The host is not authorized to manipulate other hosts' URLs. */
    RTMP_STREAM_PUBLISH_ERROR_NOT_AUTHORIZED = 8,
    
    /** Agora's server fails to find the RTMP streaming. */
    RTMP_STREAM_PUBLISH_ERROR_STREAM_NOT_FOUND = 9,
    
    /** The format of the RTMP streaming URL is not supported. */
    RTMP_STREAM_PUBLISH_ERROR_FORMAT_NOT_SUPPORTED = 10,
} RTMP_STREAM_PUBLISH_ERROR;


/**
 * Enumerates the states of importing an external video stream in a live broadcast.
 */
typedef enum {
    /** 0: The external video stream has been successfully imported. */
    INJECT_STREAM_STATUS_START_SUCCESS = 0,
    /** 1: The external video stream already exists. */
    INJECT_STREAM_STATUS_START_ALREADY_EXISTS = 1,
    /** 2: The external video stream to be imported is unauthorized. */
    INJECT_STREAM_STATUS_START_UNAUTHORIZED = 2,
    /** 3: Timeout occurred while importing the external video stream. */
    INJECT_STREAM_STATUS_START_TIMEDOUT = 3,
    /** 4: Failed to import the external video stream. */
    INJECT_STREAM_STATUS_START_FAILED = 4,
    /** 5: The external video stream has been successfully stopped. */
    INJECT_STREAM_STATUS_STOP_SUCCESS = 5,
    /** 6: No external video stream was found. */
    INJECT_STREAM_STATUS_STOP_NOT_FOUND = 6,
    /** 7: The external video stream to be stopped is unauthorized. */
    INJECT_STREAM_STATUS_STOP_UNAUTHORIZED = 7,
    /** 8: Timeout occurred while stopping the external video stream. */
    INJECT_STREAM_STATUS_STOP_TIMEDOUT = 8,
    /** 9: Failed to stop the external video stream. */
    INJECT_STREAM_STATUS_STOP_FAILED = 9,
    /** 10: The external video stream is corrupted. */
    INJECT_STREAM_STATUS_BROKEN = 10,
} INJECT_STREAM_STATUS;

/**
 * Enumerates the types of remote video streams.
 */
typedef enum {
    /** 0: High-quality video stream. */
    REMOTE_VIDEO_STREAM_HIGH = 0,
    /** 1: Low-quality video stream. */
    REMOTE_VIDEO_STREAM_LOW = 1,
    /** 2: Automatically select the video stream based on network conditions. */
    REMOTE_VIDEO_STREAM_AUTO = 2,
} REMOTE_VIDEO_STREAM_TYPE;

/**
 * Enumerates the use modes of the `onRecordAudioFrame` callback.
 */
typedef enum {
    /** 0: Read-only mode. Users read the `AudioFrame` data without modification. */
    RAW_AUDIO_FRAME_OP_MODE_READ_ONLY = 0,
    /** 1: Write-only mode. Users replace the `AudioFrame` data with their own data for encoding. */
    RAW_AUDIO_FRAME_OP_MODE_WRITE_ONLY = 1,
    /** 2: Read and write mode. Users read, modify, and then use the `AudioFrame` data. */
    RAW_AUDIO_FRAME_OP_MODE_READ_WRITE = 2,
} RAW_AUDIO_FRAME_OP_MODE_TYPE;

/**
 * Enumerates the audio sample rates.
 */
typedef enum {
    /** 32000: 32 kHz sample rate. */
    AUDIO_SAMPLE_RATE_32000 = 32000,
    /** 44100: 44.1 kHz sample rate. */
    AUDIO_SAMPLE_RATE_44100 = 44100,
    /** 48000: 48 kHz sample rate. */
    AUDIO_SAMPLE_RATE_48000 = 48000,
} AUDIO_SAMPLE_RATE_TYPE;

/**
 * Enumerates the video codec profile types.
 */
typedef enum {
    /** 66: Baseline video codec profile, typically used for mobile video calls. */
    VIDEO_CODEC_PROFILE_BASELINE = 66,
    /** 77: Main video codec profile, used in mainstream electronics like MP4 players and iPads. */
    VIDEO_CODEC_PROFILE_MAIN = 77,
    /** 100: High video codec profile, used for high-resolution broadcasts or television. */
    VIDEO_CODEC_PROFILE_HIGH = 100,
} VIDEO_CODEC_PROFILE_TYPE;

/**
 * Enumerates the video codec types.
 */
typedef enum {
    /** Standard VP8 codec. */
    VIDEO_CODEC_VP8 = 1,
    /** Standard H264 codec. */
    VIDEO_CODEC_H264 = 2,
    /** Enhanced VP8 codec. */
    VIDEO_CODEC_EVP = 3,
    /** Enhanced H264 codec. */
    VIDEO_CODEC_E264 = 4,
} VIDEO_CODEC_TYPE;

/**
 * Enumerates the audio equalization band frequencies.
 */
typedef enum {
    /** 31 Hz equalization band. */
    AUDIO_EQUALIZATION_BAND_31 = 0,
    /** 62 Hz equalization band. */
    AUDIO_EQUALIZATION_BAND_62 = 1,
    /** 125 Hz equalization band. */
    AUDIO_EQUALIZATION_BAND_125 = 2,
    /** 250 Hz equalization band. */
    AUDIO_EQUALIZATION_BAND_250 = 3,
    /** 500 Hz equalization band. */
    AUDIO_EQUALIZATION_BAND_500 = 4,
    /** 1 kHz equalization band. */
    AUDIO_EQUALIZATION_BAND_1K = 5,
    /** 2 kHz equalization band. */
    AUDIO_EQUALIZATION_BAND_2K = 6,
    /** 4 kHz equalization band. */
    AUDIO_EQUALIZATION_BAND_4K = 7,
    /** 8 kHz equalization band. */
    AUDIO_EQUALIZATION_BAND_8K = 8,
    /** 16 kHz equalization band. */
    AUDIO_EQUALIZATION_BAND_16K = 9,
} AUDIO_EQUALIZATION_BAND_FREQUENCY;


/**
 * Enumerates the preset voice beautifier effects available in the SDK.
 */
typedef enum {
    /** 
     * Turns off voice beautifier effects, resulting in the use of the original voice.
     */
    VOICE_BEAUTIFIER_OFF = 0x00000000,

    /**
     * Enhances the voice to sound more magnetic.
     *
     * @note Agora recommends using this effect for a male-sounding voice. Using it on other voice types may result in distortion.
     */
    CHAT_BEAUTIFIER_MAGNETIC = 0x01010100,

    /**
     * Makes the voice sound fresher.
     *
     * @note Agora recommends using this effect for a female-sounding voice. Using it on other voice types may result in distortion.
     */
    CHAT_BEAUTIFIER_FRESH = 0x01010200,

    /**
     * Adds vitality to the voice.
     *
     * @note Agora recommends using this effect for a female-sounding voice. Using it on other voice types may result in distortion.
     */
    CHAT_BEAUTIFIER_VITALITY = 0x01010300,

    /**
     * @since v3.3.0
     *
     * Applies a singing beautifier effect, suitable for karaoke or singing scenarios.
     * - For a male-sounding voice, use `setVoiceBeautifierPreset` with `SINGING_BEAUTIFIER` to add a reverberation effect that mimics singing in a small room.
     * - For both male and female voices, use `setVoiceBeautifierParameters` with `SINGING_BEAUTIFIER` and specific parameters to adjust the reverberation effect.
     */
    SINGING_BEAUTIFIER = 0x01020100,

    /** Makes the voice sound more vigorous. */
    TIMBRE_TRANSFORMATION_VIGOROUS = 0x01030100,

    /** Deepens the voice. */
    TIMBRE_TRANSFORMATION_DEEP = 0x01030200,

    /** Makes the voice sound mellower. */
    TIMBRE_TRANSFORMATION_MELLOW = 0x01030300,

    /** Creates a falsetto voice effect. */
    TIMBRE_TRANSFORMATION_FALSETTO = 0x01030400,

    /** Enhances the fullness of the voice. */
    TIMBRE_TRANSFORMATION_FULL = 0x01030500,

    /** Makes the voice clearer. */
    TIMBRE_TRANSFORMATION_CLEAR = 0x01030600,

    /** Adds a resounding quality to the voice. */
    TIMBRE_TRANSFORMATION_RESOUNDING = 0x01030700,

    /** Gives the voice a ringing tone. */
    TIMBRE_TRANSFORMATION_RINGING = 0x01030800
} VOICE_BEAUTIFIER_PRESET;


/**
 * Enumerates the preset audio effects available in the SDK.
 */
typedef enum {
    /**
     * Turns off audio effects, resulting in the use of the original voice.
     */
    AUDIO_EFFECT_OFF = 0x00000000,

    /**
     * Applies a KTV venue-style audio effect.
     *
     * @note For optimal effect quality, Agora recommends configuring the audio profile with `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before applying this effect.
     */
    ROOM_ACOUSTICS_KTV = 0x02010100,

    /**
     * Simulates the acoustics of a concert hall.
     *
     * @note For optimal effect quality, Agora recommends configuring the audio profile with `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before applying this effect.
     */
    ROOM_ACOUSTICS_VOCAL_CONCERT = 0x02010200,

    /**
     * Imitates the sound of a recording studio.
     *
     * @note For optimal effect quality, Agora recommends configuring the audio profile with `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before applying this effect.
     */
    ROOM_ACOUSTICS_STUDIO = 0x02010300,

    /**
     * Applies an audio effect reminiscent of a vintage phonograph.
     *
     * @note For optimal effect quality, Agora recommends configuring the audio profile with `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before applying this effect.
     */
    ROOM_ACOUSTICS_PHONOGRAPH = 0x02010400,

    /**
     * Creates a virtual stereo effect from monophonic audio.
     *
     * @note Configure the audio profile with `AUDIO_PROFILE_MUSIC_STANDARD_STEREO(3)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before applying this effect for it to take effect properly.
     */
    ROOM_ACOUSTICS_VIRTUAL_STEREO = 0x02010500,

    /**
     * Adds a spatial audio effect.
     *
     * @note For optimal effect quality, Agora recommends configuring the audio profile with `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before applying this effect.
     */
    ROOM_ACOUSTICS_SPACIAL = 0x02010600,

    /**
     * Creates an ethereal audio effect.
     *
     * @note For optimal effect quality, Agora recommends configuring the audio profile with `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before applying this effect.
     */
    ROOM_ACOUSTICS_ETHEREAL = 0x02010700,

    /**
     * Applies a 3D voice effect, giving the impression that the voice is moving around the listener.
     * The default cycle for this effect is 10 seconds, but it can be adjusted with `setAudioEffectParameters` after applying this effect.
     *
     * @note Configure the audio profile with `AUDIO_PROFILE_MUSIC_STANDARD_STEREO(3)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before applying this effect for it to take effect properly. For the best experience, use stereo audio playback devices.
     */
    ROOM_ACOUSTICS_3D_VOICE = 0x02010800,

    /**
     * Modifies the voice to sound like an uncle.
     *
     * @note Agora recommends using this effect for a male-sounding voice to achieve the intended effect. For optimal quality, configure the audio profile as noted.
     */
    VOICE_CHANGER_EFFECT_UNCLE = 0x02020100,

    /**
     * Modifies the voice to sound like an old man.
     *
     * @note Agora recommends using this effect for a male-sounding voice to achieve the intended effect. For optimal quality, configure the audio profile as noted.
     */
    VOICE_CHANGER_EFFECT_OLDMAN = 0x02020200,

    /**
     * Modifies the voice to sound like a boy.
     *
     * @note Agora recommends using this effect for a male-sounding voice to achieve the intended effect. For optimal quality, configure the audio profile as noted.
     */
    VOICE_CHANGER_EFFECT_BOY = 0x02020300,

    /**
     * Modifies the voice to sound like a young woman.
     *
     * @note Agora recommends using this effect for a female-sounding voice to achieve the intended effect. For optimal quality, configure the audio profile as noted.
     */
    VOICE_CHANGER_EFFECT_SISTER = 0x02020400,

    /**
     * Modifies the voice to sound like a girl.
     *
     * @note Agora recommends using this effect for a female-sounding voice to achieve the intended effect. For optimal quality, configure the audio profile as noted.
     */
    VOICE_CHANGER_EFFECT_GIRL = 0x02020500,

    /**
     * Modifies the voice to sound like Pig King, a character with a bear-like growl from Journey to the West.
     *
     * @note For optimal quality, configure the audio profile as noted.
     */
    VOICE_CHANGER_EFFECT_PIGKING = 0x02020600,

    /**
     * Modifies the voice to sound like Hulk.
     *
     * @note For optimal quality, configure the audio profile as noted.
     */
    VOICE_CHANGER_EFFECT_HULK = 0x02020700,

    /**
     * Applies an R&B music style audio effect.
     *
     * @note Configure the audio profile with `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before applying this effect for it to take effect properly.
     */
    STYLE_TRANSFORMATION_RNB = 0x02030100,

    /**
     * Applies a popular music style audio effect.
     *
     * @note Configure the audio profile with `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before applying this effect for it to take effect properly.
     */
    STYLE_TRANSFORMATION_POPULAR = 0x02030200,

    /**
     * Applies a pitch correction effect that adjusts the user's pitch based on the natural C major scale.
     * Use `setAudioEffectParameters` after this method to modify the root key and tonic pitch.
     *
     * @note For optimal quality, configure the audio profile as noted.
     */
    PITCH_CORRECTION = 0x02040100,
} AUDIO_EFFECT_PRESET;


/**
 * Defines types for audio reverberation effects, allowing customization of the audio environment.
 */
typedef enum {
    /**
     * 0: The dry signal level in decibels (dB). Adjusts the volume of the direct sound without reverb.
     * The value ranges from -20 dB to 10 dB.
     */
    AUDIO_REVERB_DRY_LEVEL, // dB value ranging from -20 to 10, adjusts the dry signal level

    /**
     * 1: The wet signal level in decibels (dB). Adjusts the volume of the sound with reverb.
     * The value ranges from -20 dB to 10 dB.
     */
    AUDIO_REVERB_WET_LEVEL, // dB value ranging from -20 to 10, adjusts the early reflection signal level (wet signal)

    /**
     * 2: The simulated room size for the reverberation effect.
     * The value ranges from 0 to 100, with higher values indicating a larger perceived room size.
     */
    AUDIO_REVERB_ROOM_SIZE, // Value ranging from 0 to 100, simulates the size of the room for reverb effect

    /**
     * 3: The initial delay in milliseconds for the wet signal, which is the time it takes for the first
     * reflections to reach the listener's ears after the dry signal.
     * The value ranges from 0 ms to 200 ms.
     */
    AUDIO_REVERB_WET_DELAY, // ms value ranging from 0 to 200, sets the initial delay of the wet signal

    /**
     * 4: The overall strength of the reverberation effect.
     * The value ranges from 0 to 100, with higher values resulting in a more pronounced reverb effect.
     */
    AUDIO_REVERB_STRENGTH, // Value ranging from 0 to 100, adjusts the strength of the reverberation effect
} AUDIO_REVERB_TYPE;

/**
 * Provides local voice changer options for modifying the voice during audio processing.
 */
typedef enum {
    /**
     * 0: Disables voice changing, resulting in the use of the original voice.
     */
    VOICE_CHANGER_OFF, // Turns off the voice changer, using the original voice

    /**
     * 1: Modifies the voice to sound like an old man.
     */
    VOICE_CHANGER_OLDMAN,

    /**
     * 2: Modifies the voice to sound like a little boy.
     */
    VOICE_CHANGER_BABYBOY,

    /**
     * 3: Modifies the voice to sound like a little girl.
     */
    VOICE_CHANGER_BABYGIRL,

    /**
     * 4: Applies a voice effect that sounds like a growling bear.
     */
    VOICE_CHANGER_ZHUBAJIE,

    /**
     * 5: Applies ethereal vocal effects, giving the voice a dreamy or otherworldly quality.
     */
    VOICE_CHANGER_ETHEREAL,

    /**
     * 6: Modifies the voice to sound like the character Hulk, typically deep and resonant.
     */
    VOICE_CHANGER_HULK,
} VOICE_CHANGER_PRESET;



/**
 * @deprecated This enumeration is deprecated from v3.2.0.
 *
 * Enumerates local voice reverberation presets, which apply different reverb effects to the voice.
 */
typedef enum {
    /**
     * Turns off local voice reverberation, using the original voice without any reverb effects.
     */
    AUDIO_REVERB_OFF,
    
    /**
     * Applies an enhanced reverberation style typical of a KTV venue.
     */
    AUDIO_REVERB_FX_KTV,

    /**
     * Applies an enhanced reverberation style typical of a concert hall.
     */
    AUDIO_REVERB_FX_VOCAL_CONCERT,

    /**
     * Applies a reverberation style typical of an uncle's voice.
     */
    AUDIO_REVERB_FX_UNCLE,

    /**
     * Applies a reverberation style typical of a little sister's voice.
     */
    AUDIO_REVERB_FX_SISTER,

    /**
     * Applies an enhanced reverberation style typical of a recording studio.
     */
    AUDIO_REVERB_FX_STUDIO,

    /**
     * Applies an enhanced reverberation style typical of popular music.
     */
    AUDIO_REVERB_FX_POPULAR,

    /**
     * Applies an enhanced reverberation style typical of R&B music.
     */
    AUDIO_REVERB_FX_RNB,

    /**
     * Applies a reverberation style typical of a vintage phonograph.
     */
    AUDIO_REVERB_FX_PHONOGRAPH,

    // ... Additional presets have been omitted for brevity.

} AUDIO_REVERB_PRESET;

/**
 * Enumerates voice conversion presets for modifying the voice characteristics.
 */
typedef enum {
    VOICE_CONVERSION_OFF, // Turns off voice conversion effects

    /**
     * Applies a neutral voice changer effect.
     */
    VOICE_CHANGER_NEUTRAL,

    /**
     * Modifies the voice to have a sweet tone.
     */
    VOICE_CHANGER_SWEET,

    /**
     * Modifies the voice to sound more solid and robust.
     */
    VOICE_CHANGER_SOLID,

    /**
     * Enhances the bass frequencies of the voice.
     */
    VOICE_CHANGER_BASS,
} VOICE_CONVERSION_PRESET;


/** Audio codec profile types, with LC-AAC as the default profile. */
enum AUDIO_CODEC_PROFILE_TYPE
{
    /** 0: LC-AAC, a low-complexity audio codec suitable for lower computational requirements. */
    AUDIO_CODEC_PROFILE_LC_AAC = 0,
    /** 1: HE-AAC, a high-efficiency audio codec that offers better compression and quality. */
    AUDIO_CODEC_PROFILE_HE_AAC = 1,
};

/** States of the remote audio stream, indicating the current operational status. */
enum REMOTE_AUDIO_STATE
{
    /** 0: The remote audio is inactive, possibly due to local or remote muting, or the remote user being offline. */
    REMOTE_AUDIO_STATE_STOPPED = 0,  // Audio is muted or the remote stream is disabled
    /** 1: The initial stage where the first packet of the remote audio has been received. */
    REMOTE_AUDIO_STATE_STARTING = 1,  // Receiving the first audio frame packet
    /** 2: The remote audio is playing after decoding, resumed after a network issue or unmute action. */
    REMOTE_AUDIO_STATE_DECODING = 2,  // Decoding the first remote audio frame, or recovering from a frozen state
    /** 3: The remote audio is temporarily halted, likely due to network congestion affecting playback. */
    REMOTE_AUDIO_STATE_FROZEN = 3,    // Network issues have caused the audio to freeze
    /** 4: The remote audio has failed to start, which may be due to internal errors or failures. */
    REMOTE_AUDIO_STATE_FAILED = 4,    // Failure in starting the remote audio playback
};

/** Reasons for changes in the state of the remote audio stream, providing insight into the cause of state transitions. */
enum REMOTE_AUDIO_STATE_REASON
{
    /** 0: An unspecified internal error or issue has occurred. */
    REMOTE_AUDIO_REASON_INTERNAL = 0,
    /** 1: The network is congested, impacting the flow of audio data. */
    REMOTE_AUDIO_REASON_NETWORK_CONGESTION = 1,
    /** 2: The network condition has improved, allowing audio data to flow smoothly again. */
    REMOTE_AUDIO_REASON_NETWORK_RECOVERY = 2,
    /** 3: The local user has chosen to stop receiving the remote audio or has disabled the audio functionality. */
    REMOTE_AUDIO_REASON_LOCAL_MUTED = 3,
    /** 4: The local user has re-enabled the audio functionality or resumed receiving the remote audio. */
    REMOTE_AUDIO_REASON_LOCAL_UNMUTED = 4,
    /** 5: The remote user has stopped sending the audio stream or has disabled their audio capabilities. */
    REMOTE_AUDIO_REASON_REMOTE_MUTED = 5,
    /** 6: The remote user has re-enabled their audio stream or resumed sending audio data. */
    REMOTE_AUDIO_REASON_REMOTE_UNMUTED = 6,
    /** 7: The remote user has disconnected from the channel, ceasing to send any audio. */
    REMOTE_AUDIO_REASON_REMOTE_OFFLINE = 7,
};

/** States of the stream publishing process, detailing the progression from initiation to completion. */
enum STREAM_PUBLISH_STATE
{
    /** 0: The initial state after joining the channel, indicating no publishing activity yet. */
    PUB_STATE_IDLE = 0,
    /** 1: Indicates a failure to publish the local stream due to various reasons, such as muting, disabling, or user role restrictions. */
    PUB_STATE_NO_PUBLISHED = 1,
    /** 2: The stream is in the process of being published to the channel. */
    PUB_STATE_PUBLISHING = 2,
    /** 3: The local stream has been successfully published and is now available to the channel's audience. */
    PUB_STATE_PUBLISHED = 3,
};

/** States of the stream subscription process, detailing the progression from joining to successful subscription. */
enum STREAM_SUBSCRIBE_STATE {
    /** 0: The initial state after joining the channel, indicating no subscription attempt has been made. */
    SUB_STATE_IDLE = 0,
    /** 1: Subscription to the remote stream has failed. This could be due to the remote user muting or disabling their stream, or the local user choosing not to receive it. */
    SUB_STATE_NO_SUBSCRIBED = 1,
    /** 2: The subscription process is ongoing. */
    SUB_STATE_SUBSCRIBING = 2,
    /** 3: Successfully subscribed to and receiving the remote stream. */
    SUB_STATE_SUBSCRIBED = 3,
};

/** States of the remote video stream, reflecting its operational status and any issues encountered. */
enum REMOTE_VIDEO_STATE {
    /** 0: The remote video is inactive, possibly due to local or remote muting, or the remote user being offline. */
    REMOTE_VIDEO_STATE_STOPPED = 0,
    /** 1: The process of subscribing to the remote video has started, with the first packet received. */
    REMOTE_VIDEO_STATE_STARTING = 1,
    /** 2: The remote video is being decoded and displayed without issues, following a recovery from a previous state. */
    REMOTE_VIDEO_STATE_DECODING = 2,
    /** 3: The remote video display is paused, likely due to network congestion or a fallback to audio-only. */
    REMOTE_VIDEO_STATE_FROZEN = 3,
    /** 4: The remote video has failed to start, which may be due to internal errors or issues. */
    REMOTE_VIDEO_STATE_FAILED = 4,
};

/** Reasons for changes in the state of the remote video stream, providing context for the state transitions. */
enum REMOTE_VIDEO_STATE_REASON {
    /** 0: An internal error or issue has caused a change in the video state. */
    REMOTE_VIDEO_STATE_REASON_INTERNAL = 0,
    /** 1: Network congestion is affecting the video stream, potentially causing it to freeze or stop. */
    REMOTE_VIDEO_STATE_REASON_NETWORK_CONGESTION = 1,
    /** 2: Network conditions have improved, allowing the video stream to resume or start. */
    REMOTE_VIDEO_STATE_REASON_NETWORK_RECOVERY = 2,
    /** 3: The local user has chosen to stop receiving the remote video stream or has disabled the video module. */
    REMOTE_VIDEO_STATE_REASON_LOCAL_MUTED = 3,
    /** 4: The local user has resumed receiving the remote video stream or enabled the video module. */
    REMOTE_VIDEO_STATE_REASON_LOCAL_UNMUTED = 4,
    /** 5: The remote user has stopped sending the video stream or has disabled the video module. */
    REMOTE_VIDEO_STATE_REASON_REMOTE_MUTED = 5,
    /** 6: The remote user has resumed sending the video stream or enabled the video module. */
    REMOTE_VIDEO_STATE_REASON_REMOTE_UNMUTED = 6,
    /** 7: The remote user has left the channel, ceasing to send any video. */
    REMOTE_VIDEO_STATE_REASON_REMOTE_OFFLINE = 7,
    /** 8: The remote media stream has fallen back to audio-only due to poor network conditions. */
    REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK = 8,
    /** 9: The remote media stream has recovered from an audio-only fallback to a video stream as network conditions have improved. */
    REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK_RECOVERY = 9,
};

/** Enum representing different video frame rates. */
enum FRAME_RATE {
    /** 1 fps as the frame rate. */
    FRAME_RATE_FPS_1 = 1,
    /** 7 fps as the frame rate. */
    FRAME_RATE_FPS_7 = 7,
    /** 10 fps as the frame rate. */
    FRAME_RATE_FPS_10 = 10,
    /** 15 fps as the frame rate. */
    FRAME_RATE_FPS_15 = 15,
    /** 24 fps, a common cinematic frame rate. */
    FRAME_RATE_FPS_24 = 24,
    /** 30 fps, a standard frame rate for many video applications. */
    FRAME_RATE_FPS_30 = 30,
    /** 60 fps, providing smooth motion, available on Windows and macOS. */
    FRAME_RATE_FPS_60 = 60,
};

/** Enum defining the orientation modes for video output. */
enum ORIENTATION_MODE {
    /** 0: Adaptive mode where the encoder adjusts to the input device's orientation. */
    ORIENTATION_MODE_ADAPTIVE = 0,
    /** 1: Fixed landscape mode, always sends video in landscape orientation, used in CDN live streaming. */
    ORIENTATION_MODE_FIXED_LANDSCAPE = 1,
    /** 2: Fixed portrait mode, always sends video in portrait orientation, used in CDN live streaming. */
    ORIENTATION_MODE_FIXED_PORTRAIT = 2,
};

/** Enum indicating the preference for video quality degradation under bandwidth constraints. */
enum DEGRADATION_PREFERENCE {
    /** 0: Maintain video quality by degrading frame rate if necessary. */
    MAINTAIN_QUALITY = 0,
    /** 1: Maintain frame rate by degrading video quality if necessary. */
    MAINTAIN_FRAMERATE = 1,
    /** 2: Balance between frame rate and video quality (for future use). */
    MAINTAIN_BALANCED = 2,
    /** 3: Disable degradation preferences. */
    MAINTAIN_DISABLED = 3,
};

/** Enum for stream fallback options when network conditions are poor. */
enum STREAM_FALLBACK_OPTIONS {
    /** 0: No fallback; stream quality is not guaranteed. */
    STREAM_FALLBACK_OPTION_DISABLED = 0,
    /** 1: Remote video falls back to a low-resolution, low-bitrate stream under poor downlink conditions. */
    STREAM_FALLBACK_OPTION_VIDEO_STREAM_LOW = 1,
    /** 2: Local published video falls back to audio-only under poor uplink conditions; remote video falls back to audio if downlink conditions worsen. */
    STREAM_FALLBACK_OPTION_AUDIO_ONLY = 2,
};

/** Enum for camera capturer configuration preferences. */
enum CAPTURER_OUTPUT_PREFERENCE {
    /** 0: Auto mode, balances CPU consumption with preview quality based on system performance and network conditions. */
    CAPTURER_OUTPUT_PREFERENCE_AUTO = 0,
    /** 1: Performance priority, chooses camera capture closest to encoder settings to optimize system performance. */
    CAPTURER_OUTPUT_PREFERENCE_PERFORMANCE = 1,
    /** 2: Preview quality priority, selects higher camera output parameters for better local preview at the cost of extra CPU and RAM. */
    CAPTURER_OUTPUT_PREFERENCE_PREVIEW = 2,
    /** 3: Manual mode, allows customizing the width and height of the captured video image. */
    CAPTURER_OUTPUT_PREFERENCE_MANUAL = 3,
};

/** Enum defining the priority levels for remote users in a call. */
enum PRIORITY_TYPE {
    /** 50: High priority for the user. */
    PRIORITY_HIGH = 50,
    /** 100: Normal priority, the default setting. */
    PRIORITY_NORMAL = 100,
};

/** Enum for connection states of the SDK to Aopa's edge server. */
enum CONNECTION_STATE_TYPE {
    /** 1: Disconnected, either initially or after leaving a channel. */
    CONNECTION_STATE_DISCONNECTED = 1,
    /** 2: In process of connecting to the edge server after joining a channel. */
    CONNECTION_STATE_CONNECTING = 2,
    /** 3: Connected and joined a channel, ready to publish or subscribe to media streams. */
    CONNECTION_STATE_CONNECTED = 3,
    /** 4: Reconnecting to the channel after being disconnected due to network issues. */
    CONNECTION_STATE_RECONNECTING = 4,
    /** 5: Failed to connect or join the channel, requires manual intervention to rejoin. */
    CONNECTION_STATE_FAILED = 5,
};

/** Enum for reasons behind changes in the connection state. */
enum CONNECTION_CHANGED_REASON_TYPE {
    /** 0: The SDK is in the process of connecting to the edge server. */
    CONNECTION_CHANGED_CONNECTING = 0,
    /** 1: The SDK has successfully joined the channel. */
    CONNECTION_CHANGED_JOIN_SUCCESS = 1,
    /** 2: The connection to the edge server has been interrupted. */
    CONNECTION_CHANGED_INTERRUPTED = 2,
    /** 3: The connection is banned by the edge server. */
    CONNECTION_CHANGED_BANNED_BY_SERVER = 3,
    /** 4: Failed to join the channel within 20 minutes, and the SDK stops attempting to reconnect. */
    CONNECTION_CHANGED_JOIN_FAILED = 4,
    /** 5: The channel has been left successfully. */
    CONNECTION_CHANGED_LEAVE_CHANNEL = 5,
    /** 6: The connection failed due to an invalid App ID. */
    CONNECTION_CHANGED_INVALID_APP_ID = 6,
    /** 7: The connection failed due to an invalid channel name. */
    CONNECTION_CHANGED_INVALID_CHANNEL_NAME = 7,
    /** 8: The connection failed due to an invalid or mismatched token. */
    CONNECTION_CHANGED_INVALID_TOKEN = 8,
    /** 9: The connection failed because the token has expired. */
    CONNECTION_CHANGED_TOKEN_EXPIRED = 9,
    /** 10: The server has rejected the connection. */
    CONNECTION_CHANGED_REJECTED_BY_SERVER = 10,
    /** 11: The SDK is reconnecting due to a proxy server setting change. */
    CONNECTION_CHANGED_SETTING_PROXY_SERVER = 11,
    /** 12: The SDK is reconnecting as a result of token renewal. */
    CONNECTION_CHANGED_RENEW_TOKEN = 12,
    /** 13: The client's IP address has changed, possibly due to network operator changes. */
    CONNECTION_CHANGED_CLIENT_IP_ADDRESS_CHANGED = 13,
    /** 14: The keep-alive timeout for the connection to the edge server has been reached. */
    CONNECTION_CHANGED_KEEP_ALIVE_TIMEOUT = 14,
};

/** Enum for types of network connections. */
enum NETWORK_TYPE {
    /** -1: The network type is undetermined. */
    NETWORK_TYPE_UNKNOWN = -1,
    /** 0: The network is disconnected. */
    NETWORK_TYPE_DISCONNECTED = 0,
    /** 1: The network is a Local Area Network (LAN). */
    NETWORK_TYPE_LAN = 1,
    /** 2: The network is Wi-Fi, including mobile hotspots. */
    NETWORK_TYPE_WIFI = 2,
    /** 3: The network is mobile 2G. */
    NETWORK_TYPE_MOBILE_2G = 3,
    /** 4: The network is mobile 3G. */
    NETWORK_TYPE_MOBILE_3G = 4,
    /** 5: The network is mobile 4G. */
    NETWORK_TYPE_MOBILE_4G = 5,
    /** 6: The network is mobile 5G. */
    NETWORK_TYPE_MOBILE_5G = 6,
};

/** Enum for routing audio output to different devices. */
enum AUDIO_ROUTE_TYPE {
    /** -1: The default audio route. */
    AUDIO_ROUTE_DEFAULT = -1,
    /** 0: Headset, including those with a microphone. */
    AUDIO_ROUTE_HEADSET = 0,
    /** 1: Earpiece of the device. */
    AUDIO_ROUTE_EARPIECE = 1,
    /** 2: Headset without a microphone. */
    AUDIO_ROUTE_HEADSET_NO_MIC = 2,
    /** 3: Speakerphone of the device. */
    AUDIO_ROUTE_SPEAKERPHONE = 3,
    /** 4: Loudspeaker of the device. */
    AUDIO_ROUTE_LOUDSPEAKER = 4,
    /** 5: Bluetooth headset or audio device. */
    AUDIO_ROUTE_BLUETOOTH = 5,
    /** 6: USB audio device. */
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

/** AudioVolumeInfo struct encapsulates the audio volume properties of speakers in a session. */
struct AudioVolumeInfo {
   /** 
    User ID of the speaker; for the local user, this is set to 0.
    */
   uid_t uid;

   /** 
    Represents the volume of the speaker, with a scale from 0 (silent) to 255 (loudest).
   */
   unsigned int volume;

   /**
    Indicates the voice activity status of the local user:
    - 0: The local user is not speaking.
    - 1: The local user is speaking.

    @note
    This parameter reports the voice activity status only for the local user. For remote users, it is always reported as 0. 
    To enable voice activity detection for the local user, ensure that `report_vad` is set to true in the 
    \ref bb::rtc::IRtcEngine::enableAudioVolumeIndication(int, int, bool) "enableAudioVolumeIndication" method.
   */
   unsigned int vad;

   /** 
    A string identifier for the channel that the speaker is currently in.
   */
   const char *channelId;
};

/** 
  * Channel statistics provide insights into the performance and status of the communication channel.
  * These statistics can include metrics such as packet loss, round-trip time, and available bandwidth.
  */

/** RtcStats struct provides a comprehensive set of statistics for monitoring the performance of an RTC (Real-Time Communications) session. */
struct RtcStats {
   /** 
    The total duration of the call in seconds, given as a cumulative value.
   */
   unsigned int duration;

   /** 
    The total number of bytes sent over the network, as a cumulative value.
   */
   unsigned int txBytes;

   /** 
    The total number of bytes received over the network, as a cumulative value.
   */
   unsigned int rxBytes;

   /** 
    Total bytes of audio sent, before any network optimizations, as a cumulative value.
   */
   unsigned int txAudioBytes;

   /** 
    Total bytes of video sent, before any network optimizations, as a cumulative value.
   */
   unsigned int txVideoBytes;

   /** 
    Total bytes of audio received before any network optimizations, as a cumulative value.
   */
   unsigned int rxAudioBytes;

   /** 
    Total bytes of video received, as a cumulative value.
   */
   unsigned int rxVideoBytes;

   /** 
    The transmission bitrate in Kbps, measured at a specific instant.
   */
   unsigned short txKBitRate;

   /** 
    The receive bitrate in Kbps, measured at a specific instant.
   */
   unsigned short rxKBitRate;

   /** 
    The audio receive bitrate in Kbps, measured at a specific instant.
   */
   unsigned short rxAudioKBitRate;

   /** 
    The audio transmission bitrate in Kbps, measured at a specific instant.
   */
   unsigned short txAudioKBitRate;

   /** 
    The video receive bitrate in Kbps, measured at a specific instant.
   */
   unsigned short rxVideoKBitRate;

   /** 
    The video transmission bitrate in Kbps, measured at a specific instant.
   */
   unsigned short txVideoKBitRate;

   /** 
    The round-trip latency from the client to the server in milliseconds.
   */
   unsigned short lastmileDelay;

   /** 
    The packet loss rate from the client to the server, before anti-packet-loss methods, as a percentage.
   */
   unsigned short txPacketLossRate;

   /** 
    The packet loss rate from the server to the client, before anti-packet-loss methods, as a percentage.
   */
   unsigned short rxPacketLossRate;

   /** 
    The current number of users in the channel, which varies based on the profile and role of the local user.
   */
   unsigned int userCount;

   /** 
    The CPU usage of the application as a percentage of total CPU time.
   */
   double cpuAppUsage;

   /** 
    The total CPU usage system-wide as a percentage.
   */
   double cpuTotalUsage;

   /** 
    The round-trip time (RTT) from the client to the local router in milliseconds.
   */
   int gatewayRtt;

   /** 
    The memory usage ratio of the application, expressed as a percentage of the total available memory.
    @note This is an indicative value and may not always be available due to system limitations.
   */
   double memoryAppUsageRatio;

   /** 
    The total system memory usage ratio, expressed as a percentage.
    @note This is an indicative value and may not always be available due to system limitations.
   */
   double memoryTotalUsageRatio;

   /** 
    The memory consumption of the application in kilobytes.
    @note This is an indicative value and may not always be available due to system limitations.
   */
   int memoryAppUsageInKbytes;

   /** 
    Constructor to initialize default values for all statistics.
   */
   RtcStats()
      : duration(0), txBytes(0), rxBytes(0), txAudioBytes(0), txVideoBytes(0), rxAudioBytes(0), rxVideoBytes(0),
        txKBitRate(0), rxKBitRate(0), rxAudioKBitRate(0), txAudioKBitRate(0), rxVideoKBitRate(0), txVideoKBitRate(0),
        lastmileDelay(0), txPacketLossRate(0), rxPacketLossRate(0), userCount(0),
        cpuAppUsage(0), cpuTotalUsage(0), gatewayRtt(0),
        memoryAppUsageRatio(0), memoryTotalUsageRatio(0), memoryAppUsageInKbytes(0) {}
};

/** Enum representing the quality adaptation of the local video since the last reported state, based on network conditions. */
enum QUALITY_ADAPT_INDICATION {
    /** 0: No change in local video quality. */
    ADAPT_NONE = 0,
    /** 1: Local video quality improves due to increased network bandwidth. */
    ADAPT_UP_BANDWIDTH = 1,
    /** 2: Local video quality degrades due to decreased network bandwidth. */
    ADAPT_DOWN_BANDWIDTH = 2,
};

/** Enum for error codes related to channel media relay operations. */
enum CHANNEL_MEDIA_RELAY_ERROR {
    /** 0: No error; the operation is successful. */
    RELAY_OK = 0,
    /** 1: An error in the server's response to the relay operation. */
    RELAY_ERROR_SERVER_ERROR_RESPONSE = 1,
    /** 2: No response received from the server; consider leaving the channel. */
    RELAY_ERROR_SERVER_NO_RESPONSE = 2,
    /** 3: Service access failure due to server resource limitations. */
    RELAY_ERROR_NO_RESOURCE_AVAILABLE = 3,
    /** 4: Failure to send a relay request to the source channel. */
    RELAY_ERROR_FAILED_JOIN_SRC = 4,
    /** 5: Failure to accept a relay request for the destination channel. */
    RELAY_ERROR_FAILED_JOIN_DEST = 5,
    /** 6: Server failure to receive media stream from the source channel. */
    RELAY_ERROR_FAILED_PACKET_RECEIVED_FROM_SRC = 6,
    /** 7: Server failure to send media stream to the destination channel. */
    RELAY_ERROR_FAILED_PACKET_SENT_TO_DEST = 7,
    /** 8: Disconnection from the server due to poor network; consider leaving the channel. */
    RELAY_ERROR_SERVER_CONNECTION_LOST = 8,
    /** 9: An internal server error occurred during the relay process. */
    RELAY_ERROR_INTERNAL_ERROR = 9,
    /** 10: Expiration of the source channel's token. */
    RELAY_ERROR_SRC_TOKEN_EXPIRED = 10,
    /** 11: Expiration of the destination channel's token. */
    RELAY_ERROR_DEST_TOKEN_EXPIRED = 11,
};

/** Enum for event codes indicating the status of channel media relay operations. */
enum CHANNEL_MEDIA_RELAY_EVENT {
    /** 0: User disconnected from the server due to network issues. */
    RELAY_EVENT_NETWORK_DISCONNECTED = 0,
    /** 1: Network reconnected after a previous disconnection. */
    RELAY_EVENT_NETWORK_CONNECTED = 1,
    /** 2: User successfully joined the source channel for relay. */
    RELAY_EVENT_PACKET_JOINED_SRC_CHANNEL = 2,
    /** 3: User successfully joined the destination channel for relay. */
    RELAY_EVENT_PACKET_JOINED_DEST_CHANNEL = 3,
    /** 4: Media stream relay to the destination channel has started. */
    RELAY_EVENT_PACKET_SENT_TO_DEST_CHANNEL = 4,
    /** 5: Server received the video stream from the source channel. */
    RELAY_EVENT_PACKET_RECEIVED_VIDEO_FROM_SRC = 5,
    /** 6: Server received the audio stream from the source channel. */
    RELAY_EVENT_PACKET_RECEIVED_AUDIO_FROM_SRC = 6,
    /** 7: Update to the destination channel information. */
    RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL = 7,
    /** 8: Failed to update the destination channel due to internal reasons. */
    RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL_REFUSED = 8,
    /** 9: No change to the destination channel; update failed. */
    RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL_NOT_CHANGE = 9,
    /** 10: The destination channel name is NULL, affecting the update process. */
    RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL_IS_NULL = 10,
    /** 11: Video profile information has been sent to the server. */
    RELAY_EVENT_VIDEO_PROFILE_UPDATE = 11,
};

/** Enum representing the states of channel media relay. */
enum CHANNEL_MEDIA_RELAY_STATE {
    /** 0: The media relay process is not started or has ended. */
    RELAY_STATE_IDLE = 0,
    /** 1: The SDK is attempting to establish a media stream relay to the destination channel. */
    RELAY_STATE_CONNECTING = 1,
    /** 2: The media stream is being successfully relayed to the destination channel. */
    RELAY_STATE_RUNNING = 2,
    /** 3: The media relay process has encountered a failure. For details, see the error code. */
    RELAY_STATE_FAILURE = 3,
};

/** Struct containing statistics related to the local video stream. */
struct LocalVideoStats {
    /** The bitrate (Kbps) of the video sent during the reporting interval, excluding retransmitted video after packet loss. */
    int sentBitrate;
    /** The frame rate (fps) of the video sent during the reporting interval, excluding retransmitted video after packet loss. */
    int sentFrameRate;
    /** The output frame rate (fps) of the local video encoder. */
    int encoderOutputFrameRate;
    /** The output frame rate (fps) of the local video renderer. */
    int rendererOutputFrameRate;
    /** The target bitrate (Kbps) currently used by the encoder, estimated by the SDK based on network conditions. */
    int targetBitrate;
    /** The target frame rate (fps) set for the current video encoder. */
    int targetFrameRate;
    /**
     * The quality adaptation of the local video in terms of target frame rate and target bitrate during this reporting interval.
     * See #QUALITY_ADAPT_INDICATION for possible values.
     */
    QUALITY_ADAPT_INDICATION qualityAdaptIndication;
    /** The encoding bitrate (Kbps), not including the bitrate of re-transmitted video after packet loss. */
    int encodedBitrate;
    /** The width (pixels) of the video frames being encoded. */
    int encodedFrameWidth;
    /** The height (pixels) of the video frames being encoded. */
    int encodedFrameHeight;
    /** The total number of encoded video frames sent during the reporting interval. */
    int encodedFrameCount;
    /**
     * The codec type used for the local video encoding:
     * - VIDEO_CODEC_VP8 = 1: VP8 codec.
     * - VIDEO_CODEC_H264 = 2: H.264 codec (default).
     */
    VIDEO_CODEC_TYPE codecType;
};

/** Struct providing statistics about the remote video stream received by the local user. */
struct RemoteVideoStats {
    /** User ID of the remote user who is sending the video streams. */
    uid_t uid;
    /** [DEPRECATED] Time delay of the video stream, measured in milliseconds. */
    int delay;
    /** Width of the video stream in pixels. */
    int width;
    /** Height of the video stream in pixels. */
    int height;
    /** Bitrate of the received video stream since the last reported count, in Kbps. */
    int receivedBitrate;
    /** Decoder output frame rate of the remote video, in fps. */
    int decoderOutputFrameRate;
    /** Render output frame rate of the remote video, in fps. */
    int rendererOutputFrameRate;
    /** Packet loss rate of the remote video stream after anti-packet-loss methods are applied, in percent. */
    int packetLossRate;
    /** Type of the received remote video stream. */
    REMOTE_VIDEO_STREAM_TYPE rxStreamType;
    /** Total freeze time of the remote video stream in milliseconds after the remote user joins the channel. */
    int totalFrozenTime;
    /** Total video freeze time as a percentage of the total time the video is available. */
    int frozenRate;
    /** Remote video buffer delay in milliseconds. */
    int remoteJbInMs;
    /** Timestamp of when the first frame of the remote video was received. */
    int64_t remoteFirstFrameReceiveTs;
};

/** Struct containing audio statistics for the local user. */
struct LocalAudioStats {
    /** Number of audio channels. */
    int numChannels;
    /** Sample rate of the sent audio, in Hz. */
    int sentSampleRate;
    /** Average bitrate of the sent audio, in Kbps. */
    int sentBitrate;
};

/** Struct containing audio statistics for a remote user. */
struct RemoteAudioStats {
    /** User ID of the remote user who is sending the audio streams. */
    uid_t uid;
    /** Received audio quality, as indicated by the #QUALITY_TYPE enum. */
    int quality;
    /** Network transport delay from the sender to the receiver, in milliseconds. */
    int networkTransportDelay;
    /** Delay introduced by the jitter buffer, in milliseconds. */
    int jitterBufferDelay;
    /** Audio frame loss rate during the reported interval. */
    int audioLossRate;
    /** Number of audio channels in the received stream. */
    int numChannels;
    /** Sample rate of the received audio stream, in Hz. */
    int receivedSampleRate;
    /** Average bitrate of the received audio stream, in Kbps. */
    int receivedBitrate;
    /** Total freeze time of the remote audio stream in milliseconds after the remote user joins the channel. */
    int totalFrozenTime;
    /** Total audio freeze time as a percentage of the total time the audio is available. */
    int frozenRate;
};

/** Struct defining the dimensions of a video frame. */
struct VideoDimensions {
    /** Horizontal pixels count of the video frame. */
    int width;
    /** Vertical pixels count of the video frame. */
    int height;

    /** Default constructor initializes dimensions to 640x480. */
    VideoDimensions() : width(640), height(480) {}
    /** Parameterized constructor for custom dimensions. */
    VideoDimensions(int w, int h) : width(w), height(h) {}
};

/** Constant for the standard bitrate configuration in video encoding. */
const int STANDARD_BITRATE = 0;

/** Constant for the default minimum bitrate setting. */
const int DEFAULT_MIN_BITRATE = -1;

/** Struct for configuring video encoder settings. */
struct VideoEncoderConfiguration {
    /** Dimensions of the video frame. */
    VideoDimensions dimensions;
    /** Frame rate of the encoded video. */
    FRAME_RATE frameRate;
    /** Minimum frame rate setting for the encoder. */
    int minFrameRate;
    /** Target encoding bitrate for the video, with options for standard or custom bitrates. */
    int bitrate;
    /** Minimum encoding bitrate to ensure quality under various network conditions. */
    int minBitrate;
    /** Video orientation mode for encoding. */
    ORIENTATION_MODE orientationMode;
    /** Degradation preference when bandwidth is limited. */
    DEGRADATION_PREFERENCE degradationPreference;
    /** Mirror mode for the local video stream as seen by remote users. */
    VIDEO_MIRROR_MODE_TYPE mirrorMode;

    /** Parameterized constructor for a customized video encoder configuration. */
    VideoEncoderConfiguration(
        const VideoDimensions& d, FRAME_RATE f, int b,
        ORIENTATION_MODE m, VIDEO_MIRROR_MODE_TYPE mr = VIDEO_MIRROR_MODE_AUTO)
        : dimensions(d), frameRate(f), minFrameRate(DEFAULT_MIN_BITRATE),
          bitrate(b), minBitrate(DEFAULT_MIN_BITRATE), orientationMode(m),
          degradationPreference(MAINTAIN_QUALITY), mirrorMode(mr) {}
    
    /** Parameterized constructor allowing direct specification of dimensions and other settings. */
    VideoEncoderConfiguration(
        int width, int height, FRAME_RATE f, int b,
        ORIENTATION_MODE m, VIDEO_MIRROR_MODE_TYPE mr = VIDEO_MIRROR_MODE_AUTO)
        : dimensions(width, height), frameRate(f), minFrameRate(DEFAULT_MIN_BITRATE),
          bitrate(b), minBitrate(DEFAULT_MIN_BITRATE), orientationMode(m),
          degradationPreference(MAINTAIN_QUALITY), mirrorMode(mr) {}
    
    /** Default constructor with preset configuration values. */
    VideoEncoderConfiguration()
        : dimensions(640, 480), frameRate(FRAME_RATE_FPS_15),
          minFrameRate(-1), bitrate(STANDARD_BITRATE),
          minBitrate(DEFAULT_MIN_BITRATE), orientationMode(ORIENTATION_MODE_ADAPTIVE),
          degradationPreference(MAINTAIN_FRAMERATE), mirrorMode(VIDEO_MIRROR_MODE_DISABLED) {}
};

/** Struct defining the video properties for a user in a CDN live streaming scenario. A maximum of 17 transcoding users are supported in a channel. */
typedef struct TranscodingUser {
    /** Unique identifier for the user who is streaming their video to the CDN. */
    uid_t uid;

    /** Horizontal pixel position of the video frame relative to the top-left corner of the viewport. */
    int x;

    /** Vertical pixel position of the video frame relative to the top-left corner of the viewport. */
    int y;

    /** Width of the video frame in pixels; defaults to 360 if not set. */
    int width;

    /** Height of the video frame in pixels; defaults to 640 if not set. */
    int height;

    /**
     * Layering order of the video frame, with 0 as the lowest (background) and 100 as the highest (foreground).
     * @note Values outside this range may result in an error.
     */
    int zOrder;

    /** Opacity level of the video frame, ranging from 0 (completely transparent) to 1.0 (fully opaque), with 1.0 as the default. */
    double alpha;

    /**
     * Audio channel mapping for the user's audio stream:
     * - 0: Default, supports up to dual channels based on broadcaster's audio stream.
     * - 1 through 5: Specify a particular audio channel (FL, FC, FR, BL, BR), forcing the audio stream to mono if multiple channels are present.
     * @note Non-zero settings may require a specialized player for proper audio output.
     */
    int audioChannel;

    /** Default constructor for TranscodingUser, initializing all properties. */
    TranscodingUser()
        : uid(0), x(0), y(0), width(360), height(640), zOrder(0), alpha(1.0), audioChannel(0) {}
} TranscodingUser;

/** Struct defining the properties of an image used in a live broadcast, such as a watermark or background. */
typedef struct RtcImage {
    /** Default constructor for RtcImage, initializing properties with default values. */
    RtcImage() : url(NULL), x(0), y(0), width(0), height(0) {}

    /** URL of the image to be displayed, must be accessible via HTTP or HTTPS, with a maximum length of 1024 bytes. */
    const char* url;

    /** Horizontal position of the image from the upper left corner of the broadcast video. */
    int x;

    /** Vertical position of the image from the upper left corner of the broadcast video. */
    int y;

    /** Width of the image as displayed on the broadcast video. */
    int width;

    /** Height of the image as displayed on the broadcast video. */
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

/** Struct defining the configuration for media relay in a channel. */
struct ChannelMediaRelayConfiguration {
    /** Pointer to the source channel's media information, including:
     * - `channelName`: Name of the source channel; use `NULL` for the current channel's name.
     * - `uid`: Broadcaster's ID in the source channel; must be set to 0 for a random UID.
     * - `token`: Authentication token for the source channel; use `NULL` for App ID or a generated token if App Certificate is enabled.
     */
    ChannelMediaInfo *srcInfo;

    /** Pointer to the destination channel's media information, including:
     * - `channelName`: Name of the destination channel.
     * - `uid`: Unique broadcaster's ID in the destination channel; use 0 for a random UID.
     * - `token`: Authentication token for the destination channel; use a generated token if required.
     */
    ChannelMediaInfo *destInfos;

    /** Number of destination channels configured for relay, with a default of 0 and an upper limit of 4. */
    int destCount;

    /** Default constructor for ChannelMediaRelayConfiguration, initializing all pointers to `nullptr` and `destCount` to 0. */
    ChannelMediaRelayConfiguration()
            : srcInfo(nullptr), destInfos(nullptr), destCount(0) {}
};


/** Enum for providing content hints to the screen sharing feature for optimal encoding performance. */
enum VideoContentHint {
    /** No content hint provided; the system applies default settings. */
    CONTENT_HINT_NONE,

    /** Hint for motion-intensive content, such as video clips or games, where smoothness is prioritized. */
    CONTENT_HINT_MOTION,

    /** Hint for motionless content, such as images or text, where sharpness is prioritized. */
    CONTENT_HINT_DETAILS,
};

/** Struct for configuring video display settings in the VideoCanvas class. */
struct VideoCanvas {
    /** The video display window or view. */
    view_t view;

    /** The rendering mode of the video view, which dictates how the video is fitted within the view. */
    int renderMode;

    /** The unique channel name for the Agora RTC session, with a maximum length of 64 bytes. */
    char channelId[MAX_CHANNEL_ID_LENGTH];

    /** The user ID for the video display settings. */
    uid_t uid;

    /** Private data reserved for internal video engine usage. */
    void *priv;

    /** The mirror mode of the video view, which affects how video is mirrored on the display. */
    VIDEO_MIRROR_MODE_TYPE mirrorMode;

    /** Default constructor for VideoCanvas, initializing members with default values. */
    VideoCanvas()
        : view(NULL), renderMode(RENDER_MODE_HIDDEN), uid(0), priv(NULL), mirrorMode(VIDEO_MIRROR_MODE_AUTO) {
        channelId[0] = '\0';
    }

    /** Parameterized constructor for VideoCanvas with specific view, render mode, and user ID. */
    VideoCanvas(view_t v, int m, uid_t u)
        : view(v), renderMode(m), uid(u), priv(NULL), mirrorMode(VIDEO_MIRROR_MODE_AUTO) {
        channelId[0] = '\0';
    }

    /** Parameterized constructor for VideoCanvas with additional channel ID specification. */
    VideoCanvas(view_t v, int m, const char *ch, uid_t u)
        : view(v), renderMode(m), uid(u), priv(NULL), mirrorMode(VIDEO_MIRROR_MODE_AUTO) {
        strncpy(channelId, ch, MAX_CHANNEL_ID_LENGTH);
        channelId[MAX_CHANNEL_ID_LENGTH - 1] = '\0';
    }

    /** Parameterized constructor for VideoCanvas with specific mirror mode. */
    VideoCanvas(view_t v, int rm, uid_t u, VIDEO_MIRROR_MODE_TYPE mm)
        : view(v), renderMode(rm), uid(u), priv(NULL), mirrorMode(mm) {
        channelId[0] = '\0';
    }

    /** Parameterized constructor for VideoCanvas with all settings specified. */
    VideoCanvas(view_t v, int rm, const char *ch, uid_t u, VIDEO_MIRROR_MODE_TYPE mm)
        : view(v), renderMode(rm), uid(u), priv(NULL), mirrorMode(mm) {
        strncpy(channelId, ch, MAX_CHANNEL_ID_LENGTH);
        channelId[MAX_CHANNEL_ID_LENGTH - 1] = '\0';
    }
};

/** Struct for configuring image enhancement options such as contrast, brightness, and smoothness. */
struct BeautyOptions {
    /** Enum for defining contrast levels used with lightening effects. */
    enum LIGHTENING_CONTRAST_LEVEL {
        LIGHTENING_CONTRAST_LOW,  ///< Low contrast level for subtle image enhancement.
        LIGHTENING_CONTRAST_NORMAL,  ///< Normal contrast level, the default setting.
        LIGHTENING_CONTRAST_HIGH,  ///< High contrast level for significant image enhancement.
    };

    /** The contrast level used in conjunction with the lightening effect. */
    LIGHTENING_CONTRAST_LEVEL lighteningContrastLevel;

    /** The brightness level, ranging from 0.0 (original) to 1.0 (maximum enhancement). */
    float lighteningLevel;

    /** The sharpness level, from 0 (original) to 1, used to remove blemishes. */
    float smoothnessLevel;

    /** The redness level, from 0 (original) to 1, used to adjust the saturation of red tones. */
    float rednessLevel;

    /** Parameterized constructor for BeautyOptions with specific enhancement levels. */
    BeautyOptions(LIGHTENING_CONTRAST_LEVEL contrastLevel, float lightening, float smoothness, float redness)
        : lighteningLevel(lightening), smoothnessLevel(smoothness), rednessLevel(redness), lighteningContrastLevel(contrastLevel) {}

    /** Default constructor for BeautyOptions, initializing with default enhancement levels. */
    BeautyOptions()
        : lighteningLevel(0), smoothnessLevel(0), rednessLevel(0), lighteningContrastLevel(LIGHTENING_CONTRAST_NORMAL) {}
};

/** Struct for storing user information, including a unique user ID and user account string. */
struct UserInfo {
    uid_t uid;  ///< Unique user identifier.
    char userAccount[MAX_USER_ACCOUNT_LENGTH];  ///< User account string, maximum length defined by MAX_USER_ACCOUNT_LENGTH.

    /** Default constructor for UserInfo, initializing the user ID to 0 and the account string to an empty string. */
    UserInfo() : uid(0) {
        userAccount[0] = '\0';
    }
};

/** Struct for configuring low-light enhancement options to improve video quality in poor lighting conditions. */
struct LowLightEnhanceOptions {
    /** Enum for selecting the low-light enhancement mode. */
    enum LOW_LIGHT_ENHANCE_MODE {
        LOW_LIGHT_ENHANCE_AUTO,  ///< Automatic mode for ambient light conditions.
        LOW_LIGHT_ENHANCE_MANUAL,  ///< Manual mode for user-controlled enhancement.
    };

    /** Enum for setting the low-light enhancement level. */
    enum LOW_LIGHT_ENHANCE_LEVEL {
        LOW_LIGHT_ENHANCE_LEVEL_HIGH_QUALITY,  ///< High-quality enhancement with moderate performance.
        LOW_LIGHT_ENHANCE_LEVEL_FAST,  ///< Fast enhancement prioritizing processing speed.
    };

    /** The selected low-light enhancement mode. */
    LOW_LIGHT_ENHANCE_MODE mode;

    /** The chosen low-light enhancement level. */
    LOW_LIGHT_ENHANCE_LEVEL level;

    /** Parameterized constructor for LowLightEnhanceOptions with specific mode and level. */
    LowLightEnhanceOptions(LOW_LIGHT_ENHANCE_MODE lowlightMode, LOW_LIGHT_ENHANCE_LEVEL lowlightLevel) : mode(lowlightMode), level(lowlightLevel) {}

    /** Default constructor for LowLightEnhanceOptions, initializing with default enhancement settings. */
    LowLightEnhanceOptions() : mode(LOW_LIGHT_ENHANCE_AUTO), level(LOW_LIGHT_ENHANCE_LEVEL_HIGH_QUALITY) {}
};

/** Struct for configuring video noise reduction options to improve video quality by reducing noise in the video stream.
 *  @since v3.6.2
 */
struct VideoDenoiserOptions {
    /** Enum for selecting the video noise reduction mode. */
    enum VIDEO_DENOISER_MODE {
        VIDEO_DENOISER_AUTO,  ///< 0: Automatic mode for ambient light conditions.
        VIDEO_DENOISER_MANUAL  ///< Manual mode for user-controlled noise reduction.
    };

    /** Enum for setting the video noise reduction level. */
    enum VIDEO_DENOISER_LEVEL {
        VIDEO_DENOISER_LEVEL_HIGH_QUALITY,  ///< 0: High-quality balance for noise reduction.
        VIDEO_DENOISER_LEVEL_FAST,  ///< Fast mode for reduced performance consumption.
        VIDEO_DENOISER_LEVEL_STRENGTH  ///< Strength mode for enhanced noise reduction quality.
    };

    /** The selected video noise reduction mode. */
    VIDEO_DENOISER_MODE mode;

    /** The chosen video noise reduction level. */
    VIDEO_DENOISER_LEVEL level;

    /** Parameterized constructor for VideoDenoiserOptions with specific mode and level. */
    VideoDenoiserOptions(VIDEO_DENOISER_MODE denoiserMode, VIDEO_DENOISER_LEVEL denoiserLevel) : mode(denoiserMode), level(denoiserLevel) {}

    /** Default constructor for VideoDenoiserOptions, initializing with default noise reduction settings. */
    VideoDenoiserOptions() : mode(VIDEO_DENOISER_AUTO), level(VIDEO_DENOISER_LEVEL_HIGH_QUALITY) {}
};

/** Struct for configuring color enhancement options to improve video appearance by adjusting color vibrancy and skin tone protection.
 *  @since v3.6.2
 */
struct ColorEnhanceOptions {
    /** The intensity of color enhancement, ranging from 0.0 (no enhancement) to 1.0 (maximum enhancement). */
    float strengthLevel;

    /** The level of skin tone protection, ranging from 0.0 (no protection) to 1.0 (maximum protection), to prevent distortion of skin tones during color enhancement. */
    float skinProtectLevel;

    /** Parameterized constructor for ColorEnhanceOptions with specific strength and skin protection levels. */
    ColorEnhanceOptions(float strength, float skinProtect) : strengthLevel(strength), skinProtectLevel(skinProtect) {}

    /** Default constructor for ColorEnhanceOptions, initializing with no color enhancement and maximum skin tone protection. */
    ColorEnhanceOptions() : strengthLevel(0), skinProtectLevel(1) {}
};

/** Struct for defining a custom background image for video streams.
 *  @since v3.4.5
 */
struct VirtualBackgroundSource {
    /** Enum for the type of custom background image. */
    enum BACKGROUND_SOURCE_TYPE {
        BACKGROUND_COLOR,  ///< Solid color background.
        BACKGROUND_IMG,  ///< Image file as the background.
        BACKGROUND_BLUR,  ///< Blurred background effect.
    };

    /** Enum for the degree of blurring applied to the background image.
     *  @since v3.5.1
     */
    enum BACKGROUND_BLUR_DEGREE {
        BLUR_DEGREE_LOW,  ///< Low blur degree, allowing the background to be seen clearly.
        BLUR_DEGREE_MEDIUM,  ///< Medium blur degree, making it difficult to recognize background details.
        BLUR_DEGREE_HIGH,  ///< High blur degree, barely revealing any features in the background.
    };

    /** The type of the custom background image. */
    BACKGROUND_SOURCE_TYPE background_source_type;

    /** The color of the background when using a solid color, in hexadecimal RGB format without the # sign. */
    unsigned int color;

    /** The local file path to the image for the background when using an image file. */
    const char* source;

    /** The degree of blurring for the background when using the blur effect.
     *  @since v3.5.1
     */
    BACKGROUND_BLUR_DEGREE blur_degree;

    /** Default constructor for VirtualBackgroundSource, initializing with a white solid color and no blur. */
    VirtualBackgroundSource() : color(0xffffff), source(NULL), background_source_type(BACKGROUND_COLOR), blur_degree(BLUR_DEGREE_HIGH) {}
};

#if defined(_WIN32)
/** Enum defining the types of video capture sources. */
enum VIDEO_CAPTURE_TYPE {
    VIDEO_CAPTURE_UNKNOWN,  ///< Unknown video capture type.
    VIDEO_CAPTURE_CAMERA,  ///< Video captured by a camera, the default type.
    VIDEO_CAPTURE_SCREEN,  ///< Video for screen sharing.
};

/** The IVideoFrameConsumer class is used by the SDK to receive video frames captured from a custom video source. */
class IVideoFrameConsumer {
public:
    /** Pure virtual method to receive a raw video frame.
     *
     * @param buffer The buffer containing the video frame data.
     * @param frameType The pixel format of the video frame. See VIDEO_PIXEL_FORMAT for possible values.
     * @param width The width of the video frame in pixels.
     * @param height The height of the video frame in pixels.
     * @param rotation The clockwise rotation angle applied to the video frame (0, 90, 180, or 270 degrees).
     * @param timestamp The Unix timestamp in milliseconds indicating when the video frame was captured.
     */
    virtual void consumeRawVideoFrame(const unsigned char* buffer, bbrtc::media::ExternalVideoFrame::VIDEO_PIXEL_FORMAT frameType, int width, int height, int rotation, long timestamp) = 0;
};

/** The IVideoSource class allows customization of the video source for the SDK. */
class IVideoSource {
public:
    /** Pure virtual method for initializing the custom video source.
     *
     * @param consumer An IVideoFrameConsumer object provided by the SDK to send video frames.
     * @return true if the custom video source is successfully initialized; otherwise, false.
     */
    virtual bool onInitialize(IVideoFrameConsumer* consumer) = 0;

    /** Pure virtual method for disposing of the custom video source when it's no longer needed. */
    virtual void onDispose() = 0;

    /** Pure virtual method for starting the capture of the custom video source. */
    virtual bool onStart() = 0;

    /** Pure virtual method for stopping the capture of the custom video source. */
    virtual void onStop() = 0;

    /** Pure virtual method to get the type of video frame buffer provided by the custom video source. */
    virtual bbrtc::media::ExternalVideoFrame::VIDEO_PIXEL_FORMAT getBufferType() = 0;

    /** Pure virtual method to get the capture type of the custom video source. */
    virtual VIDEO_CAPTURE_TYPE getVideoCaptureType() = 0;

    /** Pure virtual method to get the content hint for the custom video source, which helps the SDK to apply the appropriate processing algorithms. */
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
