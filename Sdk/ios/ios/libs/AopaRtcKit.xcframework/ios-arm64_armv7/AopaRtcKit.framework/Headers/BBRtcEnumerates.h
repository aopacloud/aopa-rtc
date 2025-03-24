//
//  BBRtcEnumerates.h
//  sources
//
//  Created by bhb on 2020/4/22.
//  Copyright © 2020 banban. All rights reserved.
//


#import <Foundation/Foundation.h>

/** Warning code.

Warning codes occur when the SDK encounters an error that may be recovered automatically. These are only notifications, and can generally be ignored. For example, when the SDK loses connection to the server, the SDK reports the BBRtcWarningCodeOpenChannelTimeout(106) warning and tries to reconnect automatically.
*/
typedef NS_ENUM(NSInteger, BBRtcWarningCode) {
    /** 8: The specified view is invalid. Specify a view when using the video call function. */
    BBRtcWarningCodeInvalidView = 8,
    /** 16: Failed to initialize the video function, possibly caused by a lack of resources. The users cannot see the video while the voice communication is not affected. */
    BBRtcWarningCodeInitVideo = 16,
     /** 20: The request is pending, usually due to some module not being ready, and the SDK postpones processing the request. */
    BBRtcWarningCodePending = 20,
    /** 103: No channel resources are available. Maybe because the server cannot allocate any channel resource. */
    BBRtcWarningCodeNoAvailableChannel = 103,
    /** 104: A timeout occurs when looking up the channel. When joining a channel, the SDK looks up the specified channel. The warning usually occurs when the network condition is too poor for the SDK to connect to the server. */
    BBRtcWarningCodeLookupChannelTimeout = 104,
    /** 105: The server rejects the request to look up the channel. The server cannot process this request or the request is illegal.
     <br></br><b>DEPRECATED</b> as of v2.4.1. Use BBRtcConnectionChangedRejectedByServer(10) in the `reason` parameter of [connectionChangedToState]([BBRtcEngineDelegate rtcEngine:connectionChangedToState:reason:]).
     */
    BBRtcWarningCodeLookupChannelRejected = 105,
    /** 106: The server rejects the request to look up the channel. The server cannot process this request or the request is illegal. */
    BBRtcWarningCodeOpenChannelTimeout = 106,
    /** 107: The server rejects the request to open the channel. The server cannot process this request or the request is illegal. */
    BBRtcWarningCodeOpenChannelRejected = 107,
    /** 111: A timeout occurs when switching to the live video. */
    BBRtcWarningCodeSwitchLiveVideoTimeout = 111,
    /** 118: A timeout occurs when setting the client role in the live broadcast profile. */
    BBRtcWarningCodeSetClientRoleTimeout = 118,
    /** 119: The client role is unauthorized. */
    BBRtcWarningCodeSetClientRoleNotAuthorized = 119,
    /** 121: The ticket to open the channel is invalid. */
    BBRtcWarningCodeOpenChannelInvalidTicket = 121,
    /** 122: Try connecting to another server. */
    BBRtcWarningCodeOpenChannelTryNextVos = 122,
    /** 701: An error occurs in opening the audio mixing file. */
    BBRtcWarningCodeAudioMixingOpenError = 701,
    /** 1014: Audio Device Module: a warning occurs in the playback device. */
    BBRtcWarningCodeAdmRuntimePlayoutWarning = 1014,
    /** 1016: Audio Device Module: a warning occurs in the recording device. */
    BBRtcWarningCodeAdmRuntimeRecordingWarning = 1016,
    /** 1019: Audio Device Module: no valid audio data is collected. */
    BBRtcWarningCodeAdmRecordAudioSilence = 1019,
    /** 1020: Audio Device Module: a playback device fails. */
    BBRtcWarningCodeAdmPlaybackMalfunction = 1020,
    /** 1021: Audio Device Module: a recording device fails. */
    BBRtcWarningCodeAdmRecordMalfunction = 1021,
    /** 1025: Call is interrupted by system events such as phone call or siri etc. */
    BBRtcWarningCodeAdmInterruption = 1025,
    /** 1031: Audio Device Module: the recorded audio is too low. */
    BBRtcWarningCodeAdmRecordAudioLowlevel = 1031,
    /** 1032: Audio Device Module: the playback audio is too low. */
    BBRtcWarningCodeAdmPlayoutAudioLowlevel = 1032,
    /** 1051: Audio Device Module: howling is detected. */
    BBRtcWarningCodeApmHowling = 1051,
    /** 1052: Audio Device Module: the device is in the glitch state. */
    BBRtcWarningCodeAdmGlitchState = 1052,
    /** 1053: Audio Device Module: the underlying audio settings have changed. */
    BBRtcWarningCodeAdmImproperSettings = 1053,
};

/** Error code.

Error codes occur when the SDK encounters an error that cannot be recovered automatically without any app intervention. For example, the SDK reports the BBRtcErrorCodeStartCall = 1002 error if it fails to start a call, and reminds the user to call the [leaveChannel]([BBRtcEngineKit leaveChannel:]) method.
*/
typedef NS_ENUM(NSInteger, BBRtcErrorCode) {
    /** 0: No error occurs. */
    BBRtcErrorCodeNoError = 0,
    /** 1: A general error occurs (no specified reason). */
    BBRtcErrorCodeFailed = 1,
    /** 2: An invalid parameter is used. For example, the specific channel name includes illegal characters. */
    BBRtcErrorCodeInvalidArgument = 2,
    /** 3: The SDK module is not ready.
     <p>Possible solutions：
     <ul><li>Check the audio device.</li>
     <li>Check the completeness of the app.</li>
     <li>Re-initialize the SDK.</li></ul></p>
    */
    BBRtcErrorCodeNotReady = 3,
    /** 4: The current state of the SDK does not support this function. */
    BBRtcErrorCodeNotSupported = 4,
    /** 5: The request is rejected. This is for internal SDK use only, and is not returned to the app through any method or callback. */
    BBRtcErrorCodeRefused = 5,
    /** 6: The buffer size is not big enough to store the returned data. */
    BBRtcErrorCodeBufferTooSmall = 6,
    /** 7: The SDK is not initialized before calling this method. */
    BBRtcErrorCodeNotInitialized = 7,
    /** 9: No permission exists. Check if the user has granted access to the audio or video device. */
    BBRtcErrorCodeNoPermission = 9,
    /** 10: An API method timeout occurs. Some API methods require the SDK to return the execution result, and this error occurs if the request takes too long (over 10 seconds) for the SDK to process. */
    BBRtcErrorCodeTimedOut = 10,
    /** 11: The request is canceled. This is for internal SDK use only, and is not returned to the app through any method or callback. */
    BBRtcErrorCodeCanceled = 11,
    /** 12: The method is called too often. This is for internal SDK use only, and is not returned to the app through any method or callback. */
    BBRtcErrorCodeTooOften = 12,
    /** 13: The SDK fails to bind to the network socket. This is for internal SDK use only, and is not returned to the app through any method or callback. */
    BBRtcErrorCodeBindSocket = 13,
    /** 14: The network is unavailable. This is for internal SDK use only, and is not returned to the app through any method or callback. */
    BBRtcErrorCodeNetDown = 14,
    /** 15: No network buffers are available. This is for internal SDK use only, and is not returned to the app through any method or callback. */
    BBRtcErrorCodeNoBufs = 15,
    /** 17: The request to join the channel is rejected.
     <p>Possible reasons are:
     <ul><li>The user is already in the channel, and still calls the API method to join the channel, for example, [joinChannelByToken]([BBRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]).</li>
     <li>The user tries joining the channel during the echo test. Please join the channel after the echo test ends.</li></ul></p>
    */
    BBRtcErrorCodeJoinChannelRejected = 17,
    /** 18: The request to leave the channel is rejected.
     <p>Possible reasons are:
     <ul><li>The user left the channel and still calls the API method to leave the channel, for example, [leaveChannel]([BBRtcEngineKit leaveChannel:]).</li>
     <li>The user has not joined the channel and calls the API method to leave the channel.</li></ul></p>
    */
    BBRtcErrorCodeLeaveChannelRejected = 18,
    /** 19: The resources are occupied and cannot be used. */
    BBRtcErrorCodeAlreadyInUse = 19,
    /** 20: The SDK gave up the request due to too many requests.  */
    BBRtcErrorCodeAbort = 20,
    /** 21: In Windows, specific firewall settings cause the SDK to fail to initialize and crash. */
    BBRtcErrorCodeInitNetEngine = 21,
    /** 22: The app uses too much of the system resources and the SDK fails to allocate the resources. */
    BBRtcErrorCodeResourceLimited = 22,
    /** 101: The specified App ID is invalid. Please try to rejoin the channel with a valid App ID.*/
    BBRtcErrorCodeInvalidAppId = 101,
    /** 102: The specified channel name is invalid. Please try to rejoin the channel with a valid channel name. */
    BBRtcErrorCodeInvalidChannelId = 102,
    /** 109: The token expired.
     <br></br><b>DEPRECATED</b> as of v2.4.1. Use BBRtcConnectionChangedTokenExpired(9) in the `reason` parameter of [connectionChangedToState]([BBRtcEngineDelegate rtcEngine:connectionChangedToState:reason:]).
     <p>Possible reasons are:
     <ul><li>Authorized Timestamp expired: The timestamp is represented by the number of seconds elapsed since 1/1/1970. The user can use the token to access the BBRtc service within five minutes after the token is generated. If the user does not access the BBRtc service after five minutes, this token is no longer valid.</li>
     <li>Call Expiration Timestamp expired: The timestamp is the exact time when a user can no longer use the BBRtc service (for example, when a user is forced to leave an ongoing call). When a value is set for the Call Expiration Timestamp, it does not mean that the token will expire, but that the user will be banned from the channel.</li></ul></p>
     */
    BBRtcErrorCodeTokenExpired = 109,
    /** 110: The token is invalid.
<br></br><b>DEPRECATED</b> as of v2.4.1. Use BBRtcConnectionChangedInvalidToken(8) in the `reason` parameter of [connectionChangedToState]([BBRtcEngineDelegate rtcEngine:connectionChangedToState:reason:]).
     <p>Possible reasons are:
     <ul><li>The App Certificate for the project is enabled in Console, but the user is using the App ID. Once the App Certificate is enabled, the user must use a token.</li>
     <li>The uid is mandatory, and users must set the same uid as the one set in the [joinChannelByToken]([BBRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]) method.</li></ul></p>
     */
    BBRtcErrorCodeInvalidToken = 110,
    /** 111: The Internet connection is interrupted. This applies to the BBRtc Web SDK only. */
    BBRtcErrorCodeConnectionInterrupted = 111,
    /** 112: The Internet connection is lost. This applies to the BBRtc Web SDK only. */
    BBRtcErrorCodeConnectionLost = 112,
    /** 113: The user is not in the channel when calling the [sendStreamMessage]([BBRtcEngineKit sendStreamMessage:data:]) or [getUserInfoByUserAccount]([BBRtcEngineKit getUserInfoByUserAccount:withError:]) method. */
    BBRtcErrorCodeNotInChannel = 113,
    /** 114: The size of the sent data is over 1024 bytes when the user calls the [sendStreamMessage]([BBRtcEngineKit sendStreamMessage:data:]) method. */
    BBRtcErrorCodeSizeTooLarge = 114,
    /** 115: The bitrate of the sent data exceeds the limit of 6 Kbps when the user calls the [sendStreamMessage]([BBRtcEngineKit sendStreamMessage:data:]) method. */
    BBRtcErrorCodeBitrateLimit = 115,
    /** 116: Too many data streams (over five streams) are created when the user calls the [createDataStream]([BBRtcEngineKit createDataStream:reliable:ordered:]) method. */
    BBRtcErrorCodeTooManyDataStreams = 116,
    /** 120: Decryption fails. The user may have used a different encryption password to join the channel. Check your settings or try rejoining the channel. */
    BBRtcErrorCodeDecryptionFailed = 120,
    /** 124: Incorrect watermark file parameter. */
    BBRtcErrorCodeWatermarkParam = 124,
    /** 125: Incorrect watermark file path. */
    BBRtcErrorCodeWatermarkPath = 125,
    /** 126: Incorrect watermark file format. */
    BBRtcErrorCodeWatermarkPng = 126,
    /** 127: Incorrect watermark file information. */
    BBRtcErrorCodeWatermarkInfo = 127,
    /** 128: Incorrect watermark file data format. */
    BBRtcErrorCodeWatermarkAGRB = 128,
    /** 129: An error occurs in reading the watermark file. */
    BBRtcErrorCodeWatermarkRead = 129,
    /** 130: The encrypted stream is not allowed to publish. */
    BBRtcErrorCodeEncryptedStreamNotAllowedPublish = 130,
    /** 134: The user account is invalid. */
    BBRtcErrorCodeInvalidUserAccount = 134,

    /** 151: CDN related errors. Remove the original URL address and add a new one by calling the [removePublishStreamUrl]([BBRtcEngineKit removePublishStreamUrl:]) and [addPublishStreamUrl]([BBRtcEngineKit addPublishStreamUrl:transcodingEnabled:]) methods. */
    BBRtcErrorCodePublishStreamCDNError = 151,
    /** 152: The host publishes more than 10 URLs. Delete the unnecessary URLs before adding new ones. */
    BBRtcErrorCodePublishStreamNumReachLimit = 152,
    /** 153: The host manipulates other hosts' URLs. Check your app logic. */
    BBRtcErrorCodePublishStreamNotAuthorized = 153,
    /** 154: An error occurs in BBRtc's streaming server. Call the [addPublishStreamUrl]([BBRtcEngineKit addPublishStreamUrl:transcodingEnabled:]) method to publish the stream again. */
    BBRtcErrorCodePublishStreamInternalServerError = 154,
    /** 155: The server fails to find the stream. */
    BBRtcErrorCodePublishStreamNotFound = 155,
    /** 156: The format of the RTMP stream URL is not supported. Check whether the URL format is correct. */
    BBRtcErrorCodePublishStreamFormatNotSuppported = 156,

    /** 1001: Fails to load the media engine. */
    BBRtcErrorCodeLoadMediaEngine = 1001,
    /** 1002: Fails to start the call after enabling the media engine. */
    BBRtcErrorCodeStartCall = 1002,
    /** 1003: Fails to start the camera.
     <br></br><b>DEPRECATED</b> as of v2.4.1. Use BBRtcLocalVideoStreamErrorCaptureFailure(4) in the `error` parameter of [connectionChangedToState]([BBRtcEngineDelegate rtcEngine:connectionChangedToState:reason:]).
     */
    BBRtcErrorCodeStartCamera = 1003,
    /** 1004: Fails to start the video rendering module. */
    BBRtcErrorCodeStartVideoRender = 1004,
    /** 1005: A general error occurs in the Audio Device Module (the reason is not classified specifically). Check if the audio device is used by another app, or try rejoining the channel. */
    BBRtcErrorCodeAdmGeneralError = 1005,
    /** 1006: Audio Device Module: An error occurs in using the Java resources. */
    BBRtcErrorCodeAdmJavaResource = 1006,
    /** 1007: Audio Device Module: An error occurs in setting the sampling frequency. */
    BBRtcErrorCodeAdmSampleRate = 1007,
    /** 1008: Audio Device Module: An error occurs in initializing the playback device. */
    BBRtcErrorCodeAdmInitPlayout = 1008,
    /** 1009: Audio Device Module: An error occurs in starting the playback device. */
    BBRtcErrorCodeAdmStartPlayout = 1009,
    /** 1010: Audio Device Module: An error occurs in stopping the playback device. */
    BBRtcErrorCodeAdmStopPlayout = 1010,
    /** 1011: Audio Device Module: An error occurs in initializing the recording device. */
    BBRtcErrorCodeAdmInitRecording = 1011,
    /** 1012: Audio Device Module: An error occurs in starting the recording device. */
    BBRtcErrorCodeAdmStartRecording = 1012,
    /** 1013: Audio Device Module: An error occurs in stopping the recording device. */
    BBRtcErrorCodeAdmStopRecording = 1013,
    /** 1015: Audio Device Module: A playback error occurs. Check your playback device, or try rejoining the channel. */
    BBRtcErrorCodeAdmRuntimePlayoutError = 1015,
    /** 1017: Audio Device Module: A recording error occurs. */
    BBRtcErrorCodeAdmRuntimeRecordingError = 1017,
    /** 1018: Audio Device Module: Fails to record. */
    BBRtcErrorCodeAdmRecordAudioFailed = 1018,
    /** 1020: Audio Device Module: Abnormal audio playback frequency. */
    BBRtcErrorCodeAdmPlayAbnormalFrequency = 1020,
    /** 1021: Audio Device Module: Abnormal audio recording frequency. */
    BBRtcErrorCodeAdmRecordAbnormalFrequency = 1021,
    /** 1022: Audio Device Module: An error occurs in initializing the loopback device. */
    BBRtcErrorCodeAdmInitLoopback  = 1022,
    /** 1023: Audio Device Module: An error occurs in starting the loopback device. */
    BBRtcErrorCodeAdmStartLoopback = 1023,
    /** 1027: Audio Device Module: An error occurs in no recording Permission. */
    BBRtcErrorCodeAdmNoPermission = 1027,
    /** 1359: No recording device exists. */
    BBRtcErrorCodeAdmNoRecordingDevice = 1359,
    /** 1360: No playback device exists. */
    BBRtcErrorCodeAdmNoPlayoutDevice = 1360,
    /** 1501: Video Device Module: The camera is unauthorized. */
    BBRtcErrorCodeVdmCameraNotAuthorized = 1501,
    /** 1600: Video Device Module: An unknown error occurs. */
    BBRtcErrorCodeVcmUnknownError = 1600,
    /** 1601: Video Device Module: An error occurs in initializing the video encoder. */
    BBRtcErrorCodeVcmEncoderInitError = 1601,
    /** 1602: Video Device Module: An error occurs in video encoding. */
    BBRtcErrorCodeVcmEncoderEncodeError = 1602,
    /** 1603: Video Device Module: An error occurs in setting the video encoder.
    <p><b>DEPRECATED</b></p>
    */
    BBRtcErrorCodeVcmEncoderSetError = 1603,
    BBRtcSetChorusRoleError = 1604,
};

/** The state of the audio mixing file. */
typedef NS_ENUM(NSInteger, BBRtcAudioMixingStateCode){
    /** The audio mixing file is playing. */
    BBRtcAudioMixingStatePlaying = 710,
    /** The audio mixing file pauses playing. */
    BBRtcAudioMixingStatePaused = 711,
    /** The audio mixing file stops playing. */
    BBRtcAudioMixingStateStopped = 713,
    /** An exception occurs when playing the audio mixing file. */
    BBRtcAudioMixingStateFailed = 714,
};

/**  The error code of the audio mixing file. */
typedef NS_ENUM(NSInteger, BBRtcAudioMixingErrorCode){
    /** The SDK cannot open the audio mixing file. */
   BBRtcAudioMixingErrorCanNotOpen = 701,
   /** The SDK opens the audio mixing file too frequently. */
   BBRtcAudioMixingErrorTooFrequentCall = 702,
   /** The opening of the audio mixing file is interrupted. */
   BBRtcAudioMixingErrorInterruptedEOF = 703,
  /** The opening of the audio mixing file is interrupted. */
   BBRtcAudioMixingErrorNetworkBad = 705,
   /** No error. */
   BBRtcAudioMixingErrorOK = 0,
};

/**  The reason of audio mixing state change. */
typedef NS_ENUM(NSInteger, BBRtcAudioMixingReasonCode) {
  /** 701: The SDK cannot open the audio mixing file. */
  BBRtcAudioMixingReasonCanNotOpen = 701,
  /** 702: The SDK opens the audio mixing file too frequently. */
  BBRtcAudioMixingReasonTooFrequentCall = 702,
  /** 703: The opening of the audio mixing file is interrupted. */
  BBRtcAudioMixingReasonInterruptedEOF = 703,
  /** 720: The audio mixing is started by user. */
  BBRtcAudioMixingReasonStartedByUser = 720,
  /** 721: The audio mixing file is played once. */
  BBRtcAudioMixingReasonOneLoopCompleted = 721,
  /** 722: The audio mixing file is playing in a new loop. */
  BBRtcAudioMixingReasonStartNewLoop = 722,
  /** 723: The audio mixing file is all played out. */
  BBRtcAudioMixingReasonAllLoopsCompleted = 723,
  /** 724: Playing of audio file is stopped by user. */
  BBRtcAudioMixingReasonStoppedByUser = 724,
  /** 725: Playing of audio file is paused by user. */
  BBRtcAudioMixingReasonPausedByUser = 725,
  /** 726: Playing of audio file is resumed by user. */
  BBRtcAudioMixingReasonResumedByUser = 726,
};
/** Video profile.

**DEPRECATED**

Please use BBRtcVideoEncoderConfiguration.

iPhones do not support resolutions above 720p.
*/
typedef NS_ENUM(NSInteger, BBRtcVideoProfile) {
    /** Invalid profile. */
    BBRtcVideoProfileInvalid = -1,
    /** Resolution 160 &times; 120, frame rate 15 fps, bitrate 65 Kbps. */
    BBRtcVideoProfileLandscape120P = 0,
    /** (iOS only) Resolution 120 &times; 120, frame rate 15 fps, bitrate 50 Kbps. */
    BBRtcVideoProfileLandscape120P_3 = 2,
    /** (iOS only) Resolution 320 &times; 180, frame rate 15 fps, bitrate 140 Kbps. */
    BBRtcVideoProfileLandscape180P = 10,
    /** (iOS only) Resolution 180 &times; 180, frame rate 15 fps, bitrate 100 Kbps. */
    BBRtcVideoProfileLandscape180P_3 = 12,
    /** Resolution 240 &times; 180, frame rate 15 fps, bitrate 120 Kbps. */
    BBRtcVideoProfileLandscape180P_4 = 13,
    /** Resolution 320 &times; 240, frame rate 15 fps, bitrate 200 Kbps. */
    BBRtcVideoProfileLandscape240P = 20,
    /** (iOS only) Resolution 240 &times; 240, frame rate 15 fps, bitrate 140 Kbps. */
    BBRtcVideoProfileLandscape240P_3 = 22,
    /** Resolution 424 &times; 240, frame rate 15 fps, bitrate 220 Kbps. */
    BBRtcVideoProfileLandscape240P_4 = 23,
    /** Resolution 640 &times; 360, frame rate 15 fps, bitrate 400 Kbps. */
    BBRtcVideoProfileLandscape360P = 30,
    /** (iOS only) Resolution 360 &times; 360, frame rate 15 fps, bitrate 260 Kbps. */
    BBRtcVideoProfileLandscape360P_3 = 32,
    /** Resolution 640 &times; 360, frame rate 30 fps, bitrate 600 Kbps. */
    BBRtcVideoProfileLandscape360P_4 = 33,
    /** Resolution 360 &times; 360, frame rate 30 fps, bitrate 400 Kbps. */
    BBRtcVideoProfileLandscape360P_6 = 35,
    /** Resolution 480 &times; 360, frame rate 15 fps, bitrate 320 Kbps. */
    BBRtcVideoProfileLandscape360P_7 = 36,
    /** Resolution 480 &times; 360, frame rate 30 fps, bitrate 490 Kbps. */
    BBRtcVideoProfileLandscape360P_8 = 37,
    /** Resolution 640 &times; 360, frame rate 15 fps, bitrate 800 Kbps.
    <br>
     <b>Note:</b> This profile applies to the live broadcast channel profile only.
     */
    BBRtcVideoProfileLandscape360P_9 = 38,
    /** Resolution 640 &times; 360, frame rate 24 fps, bitrate 800 Kbps.
    <br>
     <b>Note:</b> This profile applies to the live broadcast channel profile only.
     */
    BBRtcVideoProfileLandscape360P_10 = 39,
    /** Resolution 640 &times; 360, frame rate 24 fps, bitrate 1000 Kbps.
    <br>
     <b>Note:</b> This profile applies to the live broadcast channel profile only.
     */
    BBRtcVideoProfileLandscape360P_11 = 100,
    /** Resolution 640 &times; 480, frame rate 15 fps, bitrate 500 Kbps. */
    BBRtcVideoProfileLandscape480P = 40,
    /** (iOS only) Resolution 480 &times; 480, frame rate 15 fps, bitrate 400 Kbps. */
    BBRtcVideoProfileLandscape480P_3 = 42,
    /** Resolution 640 &times; 480, frame rate 30 fps, bitrate 750 Kbps. */
    BBRtcVideoProfileLandscape480P_4 = 43,
    /** Resolution 480 &times; 480, frame rate 30 fps, bitrate 600 Kbps. */
    BBRtcVideoProfileLandscape480P_6 = 45,
    /** Resolution 848 &times; 480, frame rate 15 fps, bitrate 610 Kbps. */
    BBRtcVideoProfileLandscape480P_8 = 47,
    /** Resolution 848 &times; 480, frame rate 30 fps, bitrate 930 Kbps. */
    BBRtcVideoProfileLandscape480P_9 = 48,
    /** Resolution 640 &times; 480, frame rate 10 fps, bitrate 400 Kbps. */
    BBRtcVideoProfileLandscape480P_10 = 49,
    /** Resolution 1280 &times; 720, frame rate 15 fps, bitrate 1130 Kbps. */
    BBRtcVideoProfileLandscape720P = 50,
    /** Resolution 1280 &times; 720, frame rate 30 fps, bitrate 1710 Kbps. */
    BBRtcVideoProfileLandscape720P_3 = 52,
    /** Resolution 960 &times; 720, frame rate 15 fps, bitrate 910 Kbps. */
    BBRtcVideoProfileLandscape720P_5 = 54,
    /** Resolution 960 &times; 720, frame rate 30 fps, bitrate 1380 Kbps. */
    BBRtcVideoProfileLandscape720P_6 = 55,
    /** (macOS only) Resolution 1920 &times; 1080, frame rate 15 fps, bitrate 2080 Kbps. */
    BBRtcVideoProfileLandscape1080P = 60,
    /** (macOS only) Resolution 1920 &times; 1080, frame rate 30 fps, bitrate 3150 Kbps. */
    BBRtcVideoProfileLandscape1080P_3 = 62,
    /** (macOS only) Resolution 1920 &times; 1080, frame rate 60 fps, bitrate 4780 Kbps. */
    BBRtcVideoProfileLandscape1080P_5 = 64,
    /** (macOS only) Resolution 2560 &times; 1440, frame rate 30 fps, bitrate 4850 Kbps. */
    BBRtcVideoProfileLandscape1440P = 66,
    /** (macOS only) Resolution 2560 &times; 1440, frame rate 60 fps, bitrate 6500 Kbps. */
    BBRtcVideoProfileLandscape1440P_2 = 67,
    /** (macOS only) Resolution 3840 &times; 2160, frame rate 30 fps, bitrate 6500 Kbps. */
    BBRtcVideoProfileLandscape4K = 70,
    /** (macOS only) Resolution 3840 &times; 2160, frame rate 60 fps, bitrate 6500 Kbps. */
    BBRtcVideoProfileLandscape4K_3 = 72,

    /** Resolution 120 &times; 160, frame rate 15 fps, bitrate 65 Kbps. */
    BBRtcVideoProfilePortrait120P = 1000,
    /** (iOS only) Resolution 120 &times; 120, frame rate 15 fps, bitrate 50 Kbps. */
    BBRtcVideoProfilePortrait120P_3 = 1002,
    /** (iOS only) Resolution 180 &times; 320, frame rate 15 fps, bitrate 140 Kbps. */
    BBRtcVideoProfilePortrait180P = 1010,
    /** (iOS only) Resolution 180 &times; 180, frame rate 15 fps, bitrate 100 Kbps. */
    BBRtcVideoProfilePortrait180P_3 = 1012,
    /** Resolution 180 &times; 240, frame rate 15 fps, bitrate 120 Kbps. */
    BBRtcVideoProfilePortrait180P_4 = 1013,
    /** Resolution 240 &times; 320, frame rate 15 fps, bitrate 200 Kbps. */
    BBRtcVideoProfilePortrait240P = 1020,
    /** (iOS only) Resolution 240 &times; 240, frame rate 15 fps, bitrate 140 Kbps. */
    BBRtcVideoProfilePortrait240P_3 = 1022,
    /** Resolution 240 &times; 424, frame rate 15 fps, bitrate 220 Kbps. */
    BBRtcVideoProfilePortrait240P_4 = 1023,
    /** Resolution 360 &times; 640, frame rate 15 fps, bitrate 400 Kbps. */
    BBRtcVideoProfilePortrait360P = 1030,
    /** (iOS only) Resolution 360 &times; 360, frame rate 15 fps, bitrate 260 Kbps. */
    BBRtcVideoProfilePortrait360P_3 = 1032,
    /** Resolution 360 &times; 640, frame rate 30 fps, bitrate 600 Kbps. */
    BBRtcVideoProfilePortrait360P_4 = 1033,
    /** Resolution 360 &times; 360, frame rate 30 fps, bitrate 400 Kbps. */
    BBRtcVideoProfilePortrait360P_6 = 1035,
    /** Resolution 360 &times; 480, frame rate 15 fps, bitrate 320 Kbps. */
    BBRtcVideoProfilePortrait360P_7 = 1036,
    /** Resolution 360 &times; 480, frame rate 30 fps, bitrate 490 Kbps. */
    BBRtcVideoProfilePortrait360P_8 = 1037,
    /** Resolution 360 &times; 640, frame rate 15 fps, bitrate 600 Kbps. */
    BBRtcVideoProfilePortrait360P_9 = 1038,
    /** Resolution 360 &times; 640, frame rate 24 fps, bitrate 800 Kbps. */
    BBRtcVideoProfilePortrait360P_10 = 1039,
    /** Resolution 360 &times; 640, frame rate 24 fps, bitrate 800 Kbps. */
    BBRtcVideoProfilePortrait360P_11 = 1100,
    /** Resolution 480 &times; 640, frame rate 15 fps, bitrate 500 Kbps. */
    BBRtcVideoProfilePortrait480P = 1040,
    /** (iOS only) Resolution 480 &times; 480, frame rate 15 fps, bitrate 400 Kbps. */
    BBRtcVideoProfilePortrait480P_3 = 1042,
    /** Resolution 480 &times; 640, frame rate 30 fps, bitrate 750 Kbps. */
    BBRtcVideoProfilePortrait480P_4 = 1043,
    /** Resolution 480 &times; 480, frame rate 30 fps, bitrate 600 Kbps. */
    BBRtcVideoProfilePortrait480P_6 = 1045,
    /** Resolution 480 &times; 848, frame rate 15 fps, bitrate 610 Kbps. */
    BBRtcVideoProfilePortrait480P_8 = 1047,
    /** Resolution 480 &times; 848, frame rate 30 fps, bitrate 930 Kbps. */
    BBRtcVideoProfilePortrait480P_9 = 1048,
    /** Resolution 480 &times; 640, frame rate 10 fps, bitrate 400 Kbps. */
    BBRtcVideoProfilePortrait480P_10 = 1049,
    /** Resolution 720 &times; 1280, frame rate 15 fps, bitrate 1130 Kbps. */
    BBRtcVideoProfilePortrait720P = 1050,
    /** Resolution 720 &times; 1280, frame rate 30 fps, bitrate 1710 Kbps. */
    BBRtcVideoProfilePortrait720P_3 = 1052,
    /** Resolution 720 &times; 960, frame rate 15 fps, bitrate 910 Kbps. */
    BBRtcVideoProfilePortrait720P_5 = 1054,
    /** Resolution 720 &times; 960, frame rate 30 fps, bitrate 1380 Kbps. */
    BBRtcVideoProfilePortrait720P_6 = 1055,
    /** (macOS only) Resolution 1080 &times; 1920, frame rate 15 fps, bitrate 2080 Kbps. */
    BBRtcVideoProfilePortrait1080P = 1060,
    /** (macOS only) Resolution 1080 &times; 1920, frame rate 30 fps, bitrate 3150 Kbps. */
    BBRtcVideoProfilePortrait1080P_3 = 1062,
    /** (macOS only) Resolution 1080 &times; 1920, frame rate 60 fps, bitrate 4780 Kbps. */
    BBRtcVideoProfilePortrait1080P_5 = 1064,
    /** (macOS only) Resolution 1440 &times; 2560, frame rate 30 fps, bitrate 4850 Kbps. */
    BBRtcVideoProfilePortrait1440P = 1066,
    /** (macOS only) Resolution 1440 &times; 2560, frame rate 60 fps, bitrate 6500 Kbps. */
    BBRtcVideoProfilePortrait1440P_2 = 1067,
    /** (macOS only) Resolution 2160 &times; 3840, frame rate 30 fps, bitrate 6500 Kbps. */
    BBRtcVideoProfilePortrait4K = 1070,
    /** (macOS only) Resolution 2160 &times; 3840, frame rate 60 fps, bitrate 6500 Kbps. */
    BBRtcVideoProfilePortrait4K_3 = 1072,
    /** (Default) Resolution 640 &times; 360, frame rate 15 fps, bitrate 400 Kbps. */
    BBRtcVideoProfileDEFAULT = BBRtcVideoProfileLandscape360P,
};

/** The camera capturer configuration. */
typedef NS_ENUM(NSInteger, BBRtcCameraCaptureOutputPreference) {
    /** (default) Self-adapts the camera output parameters to the system performance and network conditions to balance CPU consumption and video preview quality. */
    BBRtcCameraCaptureOutputPreferenceAuto = 0,
    /** Prioritizes the system performance. The SDK chooses the dimension and frame rate of the local camera capture closest to those set by [setVideoEncoderConfiguration]([BBRtcEngineKit setVideoEncoderConfiguration:]). */
    BBRtcCameraCaptureOutputPreferencePerformance = 1,
    /** Prioritizes the local preview quality. The SDK chooses higher camera output parameters to improve the local video preview quality. This option requires extra CPU and RAM usage for video pre-processing. */
    BBRtcCameraCaptureOutputPreferencePreview = 2,
    /** Internal use only */
    BBRtcCameraCaptureOutputPreferenceUnkown = 3
};

#if TARGET_OS_IOS
/** The camera direction. */
typedef NS_ENUM(NSInteger, BBRtcCameraDirection) {
        /** The rear camera. */
        BBRtcCameraDirectionRear = 0,
        /** The front camera. */
        BBRtcCameraDirectionFront = 1,
    };
#endif

/** Video frame rate */
typedef NS_ENUM(NSInteger, BBRtcVideoFrameRate) {
    /** 1 fps. */
    BBRtcVideoFrameRateFps1 = 1,
    /** 7 fps. */
    BBRtcVideoFrameRateFps7 = 7,
    /** 10 fps. */
    BBRtcVideoFrameRateFps10 = 10,
    /** 15 fps. */
    BBRtcVideoFrameRateFps15 = 15,
    /** 24 fps. */
    BBRtcVideoFrameRateFps24 = 24,
    /** 30 fps. */
    BBRtcVideoFrameRateFps30 = 30,
    /** 60 fps (macOS only). */
    BBRtcVideoFrameRateFps60 = 60,
};

/** Video output orientation mode.

  **Note:** When a custom video source is used, if you set BBRtcVideoOutputOrientationMode as BBRtcVideoOutputOrientationModeFixedLandscape(1) or BBRtcVideoOutputOrientationModeFixedPortrait(2), when the rotated video image has a different orientation than the specified output orientation, the video encoder first crops it and then encodes it.
 */
typedef NS_ENUM(NSInteger, BBRtcVideoOutputOrientationMode) {
    /** Adaptive mode (Default).
     <p>The video encoder adapts to the orientation mode of the video input device. When you use a custom video source, the output video from the encoder inherits the orientation of the original video.
     <ul><li>If the width of the captured video from the SDK is greater than the height, the encoder sends the video in landscape mode. The encoder also sends the rotational information of the video, and the receiver uses the rotational information to rotate the received video.</li>
     <li>If the original video is in portrait mode, the output video from the encoder is also in portrait mode. The encoder also sends the rotational information of the video to the receiver.</li></ul></p>
     */
    BBRtcVideoOutputOrientationModeAdaptative = 0,
    /** Landscape mode.
     <p>The video encoder always sends the video in landscape mode. The video encoder rotates the original video before sending it and the rotational information is 0. This mode applies to scenarios involving CDN live streaming.</p>
     */
    BBRtcVideoOutputOrientationModeFixedLandscape = 1,
     /** Portrait mode.
      <p>The video encoder always sends the video in portrait mode. The video encoder rotates the original video before sending it and the rotational information is 0. This mode applies to scenarios involving CDN live streaming.</p>
      */
    BBRtcVideoOutputOrientationModeFixedPortrait = 2,
};

/** Channel profile. */
typedef NS_ENUM(NSInteger, BBRtcChannelProfile) {
    /** 0: (Default) The Communication profile. 
     <p>Use this profile in one-on-one calls or group calls, where all users can talk freely.</p>
     */
    BBRtcChannelProfileCommunication = 0,
    /** 1: The Live-Broadcast profile. 
     <p>Users in a live-broadcast channel have a role as either broadcaster or audience. A broadcaster can both send and receive streams; an audience can only receive streams.</p>
     */
    BBRtcChannelProfileLiveBroadcasting = 1,
    /** 2: The Gaming profile. 
     <p>This profile uses a codec with a lower bitrate and consumes less power. Applies to the gaming scenario, where all game players can talk freely.</p>
     */
    BBRtcChannelProfileGame = 2,
    /** 3: The Audio Player profile. */
    BBRtcChannelProfileAudioPlayer = 3,
};

/** Client role in a live broadcast. */
typedef NS_ENUM(NSInteger, BBRtcClientRole) {
    /** Host. */
    BBRtcClientRoleBroadcaster = 1,
    /** Audience. */
    BBRtcClientRoleAudience = 2,
};

/** Client role in a KTV chorus. */
typedef NS_ENUM(NSInteger, BBRtcChorusRole) {
    BBRtcChorusRoleInvalid = 0,
    BBRtcChorusRoleMain = 1,
    BBRtcChorusRoleDeputy = 2
};

/** Media type. */
typedef NS_ENUM(NSInteger, BBRtcMediaType) {
    /** No audio and video. */
    BBRtcMediaTypeNone = 0,
    /** Audio only. */
    BBRtcMediaTypeAudioOnly = 1,
    /** Video only. */
    BBRtcMediaTypeVideoOnly = 2,
    /** Audio and video. */
    BBRtcMediaTypeAudioAndVideo = 3,
};

/** Encryption mode */
typedef NS_ENUM(NSInteger, BBRtcEncryptionMode) {
    /** When encryptionMode is set as NULL, the encryption mode is set as "aes-128-xts" by default. */
    BBRtcEncryptionModeNone = 0,
    /** (Default) 128-bit AES encryption, XTS mode. */
    BBRtcEncryptionModeAES128XTS = 1,
    /** 256-bit AES encryption, XTS mode. */
    BBRtcEncryptionModeAES256XTS = 2,
    /** 128-bit AES encryption, ECB mode. */
    BBRtcEncryptionModeAES128ECB = 3,
};

/** Reason for the user being offline. */
typedef NS_ENUM(NSUInteger, BBRtcUserOfflineReason) {
    /** The user left the current channel. */
    BBRtcUserOfflineReasonQuit = 0,
    /** The SDK timed out and the user dropped offline because no data packet is received within a certain period of time. If a user quits the call and the message is not passed to the SDK (due to an unreliable channel), the SDK assumes the user dropped offline. */
    BBRtcUserOfflineReasonDropped = 1,
    /** (Live broadcast only.) The client role switched from the host to the audience. */
    BBRtcUserOfflineReasonBecomeAudience = 2,
};

/** The RTMP streaming state. */
typedef NS_ENUM(NSUInteger, BBRtcRtmpStreamingState) {
  /** The RTMP streaming has not started or has ended. This state is also triggered after you remove an RTMP address from the CDN by calling removePublishStreamUrl.*/
  BBRtcRtmpStreamingStateIdle = 0,
  /** The SDK is connecting to BBRtc's streaming server and the RTMP server. This state is triggered after you call the [addPublishStreamUrl]([BBRtcEngineKit addPublishStreamUrl:transcodingEnabled:]) method. */
  BBRtcRtmpStreamingStateConnecting = 1,
  /** The RTMP streaming is being published. The SDK successfully publishes the RTMP streaming and returns this state. */
  BBRtcRtmpStreamingStateRunning = 2,
  /** The RTMP streaming is recovering. When exceptions occur to the CDN, or the streaming is interrupted, the SDK attempts to resume RTMP streaming and returns this state.
<li> If the SDK successfully resumes the streaming, BBRtcRtmpStreamingStateRunning(2) returns.
<li> If the streaming does not resume within 60 seconds or server errors occur, BBRtcRtmpStreamingStateFailure(4) returns. You can also reconnect to the server by calling the [removePublishStreamUrl]([BBRtcEngineKit removePublishStreamUrl:]) and [addPublishStreamUrl]([BBRtcEngineKit addPublishStreamUrl:transcodingEnabled:]) methods. */
  BBRtcRtmpStreamingStateRecovering = 3,
  /** The RTMP streaming fails. See the errorCode parameter for the detailed error information. You can also call the [addPublishStreamUrl]([BBRtcEngineKit addPublishStreamUrl:transcodingEnabled:]) method to publish the RTMP streaming again. */
  BBRtcRtmpStreamingStateFailure = 4,
};


enum RTMP_STREAM_PUBLISH_ERROR
{
  RTMP_STREAM_PUBLISH_ERROR_OK = 0,
  RTMP_STREAM_PUBLISH_ERROR_INVALID_ARGUMENT = 1,
  RTMP_STREAM_PUBLISH_ERROR_ENCRYPTED_STREAM_NOT_ALLOWED = 2,
  RTMP_STREAM_PUBLISH_ERROR_CONNECTION_TIMEOUT = 3,
  RTMP_STREAM_PUBLISH_ERROR_INTERNAL_SERVER_ERROR = 4,
  RTMP_STREAM_PUBLISH_ERROR_RTMP_SERVER_ERROR = 5,
  RTMP_STREAM_PUBLISH_ERROR_TOO_OFTEN = 6,
  RTMP_STREAM_PUBLISH_ERROR_REACH_LIMIT = 7,
  RTMP_STREAM_PUBLISH_ERROR_NOT_AUTHORIZED = 8,
  RTMP_STREAM_PUBLISH_ERROR_STREAM_NOT_FOUND = 9,
  RTMP_STREAM_PUBLISH_ERROR_FORMAT_NOT_SUPPORTED = 10,
};

/** The detailed error information for streaming. */
typedef NS_ENUM(NSUInteger, BBRtcRtmpStreamingErrorCode) {
  /** The RTMP streaming publishes successfully. */
  BBRtcRtmpStreamingErrorCodeOK = 0,
  /** Invalid argument used. If, for example, you do not call the [setLiveTranscoding]([BBRtcEngineKit setLiveTranscoding:]) method to configure the LiveTranscoding parameters before calling the [addPublishStreamUrl]([BBRtcEngineKit addPublishStreamUrl:transcodingEnabled:]) method, the SDK returns this error. Check whether you set the parameters in the setLiveTranscoding method properly. */
  BBRtcRtmpStreamingErrorCodeInvalidParameters = 1,
  /** The RTMP streaming is encrypted and cannot be published. */
  BBRtcRtmpStreamingErrorCodeEncryptedStreamNotAllowed = 2,
  /** Timeout for the RTMP streaming. Call the [addPublishStreamUrl]([BBRtcEngineKit addPublishStreamUrl:transcodingEnabled:]) method to publish the streaming again. */
  BBRtcRtmpStreamingErrorCodeConnectionTimeout = 3,
  /** An error occurs in BBRtc's streaming server. Call the [addPublishStreamUrl]([BBRtcEngineKit addPublishStreamUrl:transcodingEnabled:]) method to publish the streaming again. */
  BBRtcRtmpStreamingErrorCodeInternalServerError = 4,
  /** An error occurs in the RTMP server. */
  BBRtcRtmpStreamingErrorCodeRtmpServerError = 5,
  /** The RTMP streaming publishes too frequently. */
  BBRtcRtmpStreamingErrorCodeTooOften = 6,
  /** The host publishes more than 10 URLs. Delete the unnecessary URLs before adding new ones. */
  BBRtcRtmpStreamingErrorCodeReachLimit = 7,
  /** The host manipulates other hosts' URLs. Check your app logic. */
  BBRtcRtmpStreamingErrorCodeNotAuthorized = 8,
  /** BBRtc's server fails to find the RTMP streaming. */
  BBRtcRtmpStreamingErrorCodeStreamNotFound = 9,
  /** The format of the RTMP streaming URL is not supported. Check whether the URL format is correct. */
  BBRtcRtmpStreamingErrorCodeFormatNotSupported = 10,
};

/** State of importing an external video stream in a live broadcast. */
typedef NS_ENUM(NSUInteger, BBRtcInjectStreamStatus) {
    /** The external video stream imported successfully. */
    BBRtcInjectStreamStatusStartSuccess = 0,
    /** The external video stream already exists. */
    BBRtcInjectStreamStatusStartAlreadyExists = 1,
    /** The external video stream import is unauthorized. */
    BBRtcInjectStreamStatusStartUnauthorized = 2,
    /** Import external video stream timeout. */
    BBRtcInjectStreamStatusStartTimedout = 3,
    /** The external video stream failed to import. */
    BBRtcInjectStreamStatusStartFailed = 4,
    /** The external video stream imports successfully. */
    BBRtcInjectStreamStatusStopSuccess = 5,
    /** No external video stream is found. */
    BBRtcInjectStreamStatusStopNotFound = 6,
    /** The external video stream is stopped from being unauthorized. */
    BBRtcInjectStreamStatusStopUnauthorized = 7,
    /** Importing the external video stream timeout. */
    BBRtcInjectStreamStatusStopTimedout = 8,
    /** Importing the external video stream failed. */
    BBRtcInjectStreamStatusStopFailed = 9,
    /** The external video stream import is interrupted. */
    BBRtcInjectStreamStatusBroken = 10,
};

/** Output log filter level. */
typedef NS_ENUM(NSUInteger, BBRtcLogFilter) {
    /** Do not output any log information. */
    BBRtcLogFilterOff = 0,
    /** Output all log information. Set your log filter as debug if you want to get the most complete log file. */
    BBRtcLogFilterDebug = 0x080f,
    /** Output CRITICAL, ERROR, WARNING, and INFO level log information. We recommend setting your log filter as this level. */
    BBRtcLogFilterInfo = 0x000f,
    /** Outputs CRITICAL, ERROR, and WARNING level log information. */
    BBRtcLogFilterWarning = 0x000e,
    /** Outputs CRITICAL and ERROR level log information. */
    BBRtcLogFilterError = 0x000c,
    /** Outputs CRITICAL level log information. */
    BBRtcLogFilterCritical = 0x0008,
};

/** Audio recording quality. */
typedef NS_ENUM(NSInteger, BBRtcAudioRecordingQuality) {
   /** Low quality: The sample rate is 32 KHz, and the file size is around 1.2 MB after 10 minutes of recording. */
    BBRtcAudioRecordingQualityLow = 0,
    /** Medium quality: The sample rate is 32 KHz, and the file size is around 2 MB after 10 minutes of recording. */
    BBRtcAudioRecordingQualityMedium = 1,
    /** High quality: The sample rate is 32 KHz, and the file size is around 3.75 MB after 10 minutes of recording. */
    BBRtcAudioRecordingQualityHigh = 2
};

/** Lifecycle of the CDN live video stream.

**DEPRECATED**
*/
typedef NS_ENUM(NSInteger, BBRtcRtmpStreamLifeCycle) {
    /** Bound to the channel lifecycle. If all hosts leave the channel, the CDN live streaming stops after 30 seconds. */
    BBRtcRtmpStreamLifeCycleBindToChannel = 1,
    /** Bound to the owner of the RTMP stream. If the owner leaves the channel, the CDN live streaming stops immediately. */
    BBRtcRtmpStreamLifeCycleBindToOwnner = 2,
};

/** Network quality. */
typedef NS_ENUM(NSUInteger, BBRtcNetworkQuality) {
    /** The network quality is unknown. */
    BBRtcNetworkQualityUnknown = 0,
    /**  The network quality is excellent. */
    BBRtcNetworkQualityExcellent = 1,
    /** The network quality is quite good, but the bitrate may be slightly lower than excellent. */
    BBRtcNetworkQualityGood = 2,
    /** Users can feel the communication slightly impaired. */
    BBRtcNetworkQualityPoor = 3,
    /** Users can communicate only not very smoothly. */
    BBRtcNetworkQualityBad = 4,
     /** The network quality is so bad that users can hardly communicate. */
    BBRtcNetworkQualityVBad = 5,
     /** The network is disconnected and users cannot communicate at all. */
    BBRtcNetworkQualityDown = 6,
     /** Users cannot detect the network quality. (Not in use.) */
    BBRtcNetworkQualityUnsupported = 7,
     /** Detecting the network quality. */
    BBRtcNetworkQualityDetecting = 8,
};

/** Video stream type. */
typedef NS_ENUM(NSInteger, BBRtcVideoStreamType) {
    /** High-bitrate, high-resolution video stream. */
    BBRtcVideoStreamTypeHigh = 0,
    /** Low-bitrate, low-resolution video stream. */
    BBRtcVideoStreamTypeLow = 1,

    BBRtcVideoStreamTypeAuto = 2,
};

/** The priority of the remote user. */
typedef NS_ENUM(NSInteger, BBRtcUserPriority) {
  /** The user's priority is high. */
  BBRtcUserPriorityHigh = 50,
  /** (Default) The user's priority is normal. */
  BBRtcUserPriorityNormal = 100,
};

/**  Quality change of the local video in terms of target frame rate and target bit rate since last count. */
typedef NS_ENUM(NSInteger, BBRtcVideoQualityAdaptIndication) {
  /** The quality of the local video stays the same. */
  BBRtcVideoQualityAdaptNone = 0,
  /** The quality improves because the network bandwidth increases. */
  BBRtcVideoQualityAdaptUpbandwidth = 1,
  /** The quality worsens because the network bandwidth decreases. */
  BBRtcVideoQualityAdaptDownbandwidth = 2,
};

/** The publishing state */
typedef NS_ENUM(NSUInteger, BBRtcStreamPublishState) {
  /** 0: The initial publishing state after joining the channel.
   */
  BBRtcStreamPublishIdle = 0,
  /** 1: Fails to publish the local stream. Possible reasons:
   <li>The local user calls [muteLocalAudioStream(YES)]([BBRtcEngineKit muteLocalAudioStream:]) or [muteLocalVideoStream(YES)]([BBRtcEngineKit muteLocalVideoStream:]) to stop sending local streams.</li>
   <li>The local user calls [disableAudio]([BBRtcEngineKit disableAudio]) or [disableVideo]([BBRtcEngineKit disableVideo]) to disable the entire audio or video module.</li>
   <li>The local user calls [enableLocalAudio(NO)]([BBRtcEngineKit  enableLocalAudio:]) or [enableLocalVideo(NO)]([BBRtcEngineKit  enableLocalVideo:]) to disable the local audio sampling or video capturing.</li>
   <li>The role of the local user is <tt>BBRtcClientRoleAudience</tt>.</li>
   */
  BBRtcStreamPublishNoPublished = 1,
  /** 2: Publishing.
   */
  BBRtcStreamPublishPublishing = 2,
  /** 3: Publishes successfully.
   */
  BBRtcStreamPublishPublished = 3,
};

/** The subscribing state. */
typedef NS_ENUM(NSUInteger, BBRtcStreamSubscribeState) {
  /** 0: The initial subscribing state after joining the channel.
   */
  BBRtcStreamSubscribeIdle = 0,

  BBRtcStreamSubscribeNoSubscribed = 1,
  /** 2: Subscribing.
   */
  BBRtcStreamSubscribeSubscribing = 2,
  /** 3: Subscribes to and receives the remote stream successfully.
   */
  BBRtcStreamSubscribeSubscribed = 3,
};


/** Video display mode. */
typedef NS_ENUM(NSUInteger, BBRtcVideoRenderMode) {
    /** Hidden(1): Uniformly scale the video until it fills the visible boundaries (cropped). One dimension of the video may have clipped contents. */
    BBRtcVideoRenderModeHidden = 1,

    /** Fit(2): Uniformly scale the video until one of its dimension fits the boundary (zoomed to fit). Areas that are not filled due to the disparity in the aspect ratio are filled with black. */
    BBRtcVideoRenderModeFit = 2,

    /** Adaptive(3)：This mode is deprecated. */
    BBRtcVideoRenderModeAdaptive __deprecated_enum_msg("BBRtcVideoRenderModeAdaptive is deprecated.") = 3,
};

/** Self-defined video codec profile. */
typedef NS_ENUM(NSInteger, BBRtcVideoCodecProfileType) {
    /** 66: Baseline video codec profile. Generally used in video calls on mobile phones. */
    BBRtcVideoCodecProfileTypeBaseLine = 66,
    /** 77: Main video codec profile. Generally used in mainstream electronics, such as MP4 players, portable video players, PSP, and iPads. */
    BBRtcVideoCodecProfileTypeMain = 77,
    /** 100: (Default) High video codec profile. Generally used in high-resolution broadcasts or television. */
    BBRtcVideoCodecProfileTypeHigh = 100
};

/** Video codec types. */
typedef NS_ENUM(NSInteger, BBRtcVideoCodecType) {
    /** 1: Standard VP8. */
    BBRtcVideoCodecTypeVP8 = 1,
    /** 2: Standard H264. */
    BBRtcVideoCodecTypeH264 = 2,
    /** 3: Enhanced VP8. */
    BBRtcVideoCodecTypeEVP = 3,
    /** 4: Enhanced H264. */
    BBRtcVideoCodecTypeE264 = 4,
};

/** Video mirror mode. */
typedef NS_ENUM(NSUInteger, BBRtcVideoMirrorMode) {
    /** 0: (Default) The SDK determines the mirror mode.
     */
    BBRtcVideoMirrorModeAuto = 0,
    /** 1: Enables mirror mode. */
    BBRtcVideoMirrorModeEnabled = 1,
    /** 2: Disables mirror mode. */
    BBRtcVideoMirrorModeDisabled = 2,
};

/** The content hint for screen sharing. */
typedef NS_ENUM(NSUInteger, BBRtcVideoContentHint) {
    /** 0: (Default) No content hint. */
    BBRtcVideoContentHintNone = 0,
    /** 1: Motion-intensive content. Choose this option if you prefer smoothness or when you are sharing a video clip, movie, or video game. */
    BBRtcVideoContentHintMotion = 1,
    /** 2: Motionless content. Choose this option if you prefer sharpness or when you are sharing a picture, PowerPoint slide, or text. */
    BBRtcVideoContentHintDetails = 2,
};

/** The state of the remote video. */
typedef NS_ENUM(NSUInteger, BBRtcVideoRemoteState) {
    /** 0: The remote video is in the default state, probably due to BBRtcVideoRemoteStateReasonLocalMuted(3), BBRtcVideoRemoteStateReasonRemoteMuted(5), or BBRtcVideoRemoteStateReasonRemoteOffline(7).
     */
    BBRtcVideoRemoteStateStopped = 0,
    /** 1: The first remote video packet is received.
     */
    BBRtcVideoRemoteStateStarting = 1,
    /** 2: The remote video stream is decoded and plays normally, probably due to BBRtcVideoRemoteStateReasonNetworkRecovery(2), BBRtcVideoRemoteStateReasonLocalUnmuted(4), BBRtcVideoRemoteStateReasonRemoteUnmuted(6), or BBRtcVideoRemoteStateReasonAudioFallbackRecovery(9).
     */
    BBRtcVideoRemoteStateDecoding = 2,
    /** 3: The remote video is frozen, probably due to BBRtcVideoRemoteStateReasonNetworkCongestion(1) or BBRtcVideoRemoteStateReasonAudioFallback(8).
     */
    BBRtcVideoRemoteStateFrozen = 3,
    /** 4: The remote video fails to start, probably due to BBRtcVideoRemoteStateReasonInternal(0).
     */
    BBRtcVideoRemoteStateFailed = 4,
};

/** The reason of the remote video state change. */
typedef NS_ENUM(NSUInteger, BBRtcVideoRemoteStateReason) {
    /** 0: Internal reasons. */
    BBRtcVideoRemoteStateReasonInternal = 0,
    /** 1: Network congestion. */
    BBRtcVideoRemoteStateReasonNetworkCongestion = 1,
    /** 2: Network recovery. */
    BBRtcVideoRemoteStateReasonNetworkRecovery = 2,
    /** 3: The local user stops receiving the remote video stream or disables the video module. */
    BBRtcVideoRemoteStateReasonLocalMuted = 3,
    /** 4: The local user resumes receiving the remote video stream or enables the video module. */
    BBRtcVideoRemoteStateReasonLocalUnmuted = 4,
    /** 5: The remote user stops sending the video stream or disables the video module. */
    BBRtcVideoRemoteStateReasonRemoteMuted = 5,
    /** 6: The remote user resumes sending the video stream or enables the video module. */
    BBRtcVideoRemoteStateReasonRemoteUnmuted = 6,
    /** 7: The remote user leaves the channel. */
    BBRtcVideoRemoteStateReasonRemoteOffline = 7,
    /** 8: The remote media stream falls back to the audio-only stream due to poor network conditions. */
    BBRtcVideoRemoteStateReasonAudioFallback = 8,
    /** 9: The remote media stream switches back to the video stream after the network conditions improve. */
    BBRtcVideoRemoteStateReasonAudioFallbackRecovery = 9,
};

/** Stream fallback option. */
typedef NS_ENUM(NSInteger, BBRtcStreamFallbackOptions) {
    /** No fallback behavior for the local/remote video stream when the uplink/downlink network condition is unreliable. The quality of the stream is not guaranteed. */
    BBRtcStreamFallbackOptionDisabled = 0,
    /** Under unreliable downlink network conditions, the remote video stream falls back to the low-stream (low resolution and low bitrate) video. You can only set this option in the [setRemoteSubscribeFallbackOption]([BBRtcEngineKit setRemoteSubscribeFallbackOption:]) method. Nothing happens when you set this in the [setLocalPublishFallbackOption]([BBRtcEngineKit setLocalPublishFallbackOption:]) method. */
    BBRtcStreamFallbackOptionVideoStreamLow = 1,
    /** Under unreliable uplink network conditions, the published video stream falls back to audio only. Under unreliable downlink network conditions, the remote video stream first falls back to the low-stream (low resolution and low bitrate) video; and then to an audio-only stream if the network condition deteriorates. */
    BBRtcStreamFallbackOptionAudioOnly = 2,
};

/** Audio sample rate. */
typedef NS_ENUM(NSInteger, BBRtcAudioSampleRateType) {
    /** 32 kHz. */
    BBRtcAudioSampleRateType32000 = 32000,
    /** 44.1 kHz. */
    BBRtcAudioSampleRateType44100 = 44100,
    /** 48 kHz. */
    BBRtcAudioSampleRateType48000 = 48000,
};

/** Audio profile. */
typedef NS_ENUM(NSInteger, BBRtcAudioProfile) {
    /** Default audio profile. In the communication profile, the default value is BBRtcAudioProfileSpeechStandard; in the live-broadcast profile, the default value is BBRtcAudioProfileMusicStandard. */
    BBRtcAudioProfileDefault = 0,
    /** A sample rate of 32 KHz, audio encoding, mono, and a bitrate of up to 18 Kbps. */
    BBRtcAudioProfileSpeechStandard = 1,
    /** A sample rate of 48 KHz, music encoding, mono, and a bitrate of up to 48 Kbps. */
    BBRtcAudioProfileMusicStandard = 2,
    /** A sample rate of 48 KHz, music encoding, stereo, and a bitrate of up to 56 Kbps. */
    BBRtcAudioProfileMusicStandardStereo = 3,
    /** A sample rate of 48 KHz, music encoding, mono, and a bitrate of up to 128 Kbps. */
    BBRtcAudioProfileMusicHighQuality = 4,
    /** A sample rate of 48 KHz, music encoding, stereo, and a bitrate of up to 192 Kbps. */
    BBRtcAudioProfileMusicHighQualityStereo = 5,
};

/** Audio scenario. */
typedef NS_ENUM(NSInteger, BBRtcAudioScenario) {
    /** Default. */
    BBRtcAudioScenarioDefault = 0,
    /** Entertainment scenario, supporting voice during gameplay. */
    BBRtcAudioScenarioChatRoomEntertainment = 1,
    /** Education scenario, prioritizing fluency and stability. */
    BBRtcAudioScenarioEducation = 2,
    /** Live gaming scenario, enabling the gaming audio effects in the speaker mode in a live broadcast scenario. Choose this scenario for high-fidelity music playback.*/
    BBRtcAudioScenarioGameStreaming = 3,
    /** Showroom scenario, optimizing the audio quality with external professional equipment. */
    BBRtcAudioScenarioShowRoom = 4,
    /** Gaming scenario. */
    BBRtcAudioScenarioChatRoomGaming = 5,
    /** Chorus */
    BBRtcAudioScenarioChorus = 7,
};

/** Audio output routing. */
typedef NS_ENUM(NSInteger, BBRtcAudioOutputRouting) {
    /** Default. */
    BBRtcAudioOutputRoutingDefault = -1,
    /** Headset.*/
    BBRtcAudioOutputRoutingHeadset = 0,
    /** Earpiece. */
    BBRtcAudioOutputRoutingEarpiece = 1,
    /** Headset with no microphone. */
    BBRtcAudioOutputRoutingHeadsetNoMic = 2,
    /** Speakerphone. */
    BBRtcAudioOutputRoutingSpeakerphone = 3,
    /** Loudspeaker. */
    BBRtcAudioOutputRoutingLoudspeaker = 4,
    /** Bluetooth headset. */
    BBRtcAudioOutputRoutingHeadsetBluetooth = 5,
    /** USB */
    BBRtcAudioOutputRoutingUSB = 6
};

/** Use mode of the onRecordAudioFrame callback. */
typedef NS_ENUM(NSInteger, BBRtcAudioRawFrameOperationMode) {
    /** Read-only mode: Users only read the AudioFrame data without modifying anything. For example, when users acquire data with the BBRtc SDK then push the RTMP streams. */
    BBRtcAudioRawFrameOperationModeReadOnly = 0,
    /** Write-only mode: Users replace the AudioFrame data with their own data and pass them to the SDK for encoding. For example, when users acquire data. */
    BBRtcAudioRawFrameOperationModeWriteOnly = 1,
    /** Read and write mode: Users read the data from AudioFrame, modify it, and then play it. For example, when users have their own sound-effect processing module and perform some voice pre-processing such as a voice change. */
    BBRtcAudioRawFrameOperationModeReadWrite = 2,
};

/** Audio equalization band frequency. */
typedef NS_ENUM(NSInteger, BBRtcAudioEqualizationbandFrequency) {
    /** 31 Hz. */
    BBRtcAudioEqualizationband31 = 0,
    /** 62 Hz. */
    BBRtcAudioEqualizationband62 = 1,
    /** 125 Hz. */
    BBRtcAudioEqualizationband125 = 2,
    /** 250 Hz. */
    BBRtcAudioEqualizationband250 = 3,
    /** 500 Hz */
    BBRtcAudioEqualizationband500 = 4,
    /** 1 kHz. */
    BBRtcAudioEqualizationband1K = 5,
    /** 2 kHz. */
    BBRtcAudioEqualizationband2K = 6,
    /** 4 kHz. */
    BBRtcAudioEqualizationband4K = 7,
    /** 8 kHz. */
    BBRtcAudioEqualizationband8K = 8,
    /** 16 kHz. */
    BBRtcAudioEqualizationband16K = 9,
};

/** Audio reverberation type. */
typedef NS_ENUM(NSInteger, BBRtcAudioReverbType) {
    /** The level of the dry signal (dB). The value ranges between -20 and 10. */
    BBRtcAudioReverbDryLevel = 0,
    /** The level of the early reflection signal (wet signal) in dB. The value ranges between -20 and 10. */
    BBRtcAudioReverbWetLevel = 1,
    /** The room size of the reverberation. A larger room size means a stronger reverberation. The value ranges between 0 and 100. */
    BBRtcAudioReverbRoomSize = 2,
    /** The length of the initial delay of the wet signal (ms). The value ranges between 0 and 200. */
    BBRtcAudioReverbWetDelay = 3,
     /** The reverberation strength. The value ranges between 0 and 100. */
    BBRtcAudioReverbStrength = 4,
};

/** The preset audio voice configuration used to change the voice effect. */
typedef NS_ENUM(NSInteger, BBRtcAudioVoiceChanger) {
    /** The original voice (no local voice change). */
    BBRtcAudioVoiceChangerOff = 0,
    /** An old man's voice. */
    BBRtcAudioVoiceChangerOldMan = 1,
    /** A little boy's voice. */
    BBRtcAudioVoiceChangerBabyBoy = 2,
    /** A little girl's voice. */
    BBRtcAudioVoiceChangerBabyGirl = 3,
    /** TBD */
    BBRtcAudioVoiceChangerZhuBaJie = 4,
    /** Ethereal vocal effects. */
    BBRtcAudioVoiceChangerEthereal = 5,
    /** Hulk's voice. */
    BBRtcAudioVoiceChangerHulk = 6
};


/** **DEPRECATED** from v3.2.0. The preset local voice reverberation option. */
typedef NS_ENUM(NSInteger, BBRtcAudioReverbPreset) {
    /** Turn off local voice reverberation, that is, to use the original voice. */
    BBRtcAudioReverbPresetOff __deprecated_enum_msg("BBRtcAudioReverbPresetOff is deprecated.") = 0x00000000,
    /** The reverberation style typical of a KTV venue (enhanced).  */
    BBRtcAudioReverbPresetFxKTV __deprecated_enum_msg("BBRtcAudioReverbPresetFxKTV is deprecated.") = 0x00100001,
    /** The reverberation style typical of a concert hall (enhanced). */
    BBRtcAudioReverbPresetFxVocalConcert __deprecated_enum_msg("BBRtcAudioReverbPresetFxVocalConcert is deprecated.") = 0x00100002,
    /** The reverberation style typical of an uncle's voice. */
    BBRtcAudioReverbPresetFxUncle __deprecated_enum_msg("BBRtcAudioReverbPresetFxUncle is deprecated.") = 0x00100003,
    /** The reverberation style typical of a sister's voice. */
    BBRtcAudioReverbPresetFxSister __deprecated_enum_msg("BBRtcAudioReverbPresetFxSister is deprecated.") = 0x00100004,
    /** The reverberation style typical of a recording studio (enhanced).  */
    BBRtcAudioReverbPresetFxStudio __deprecated_enum_msg("BBRtcAudioReverbPresetFxStudio is deprecated.") = 0x00100005,
    /** The reverberation style typical of popular music (enhanced). */
    BBRtcAudioReverbPresetFxPopular __deprecated_enum_msg("BBRtcAudioReverbPresetFxPopular is deprecated.") = 0x00100006,
    /** The reverberation style typical of R&B music (enhanced). */
    BBRtcAudioReverbPresetFxRNB __deprecated_enum_msg("BBRtcAudioReverbPresetFxRNB is deprecated.") = 0x00100007,
    /** The reverberation style typical of the vintage phonograph. */
    BBRtcAudioReverbPresetFxPhonograph __deprecated_enum_msg("BBRtcAudioReverbPresetFxPhonograph is deprecated.") = 0x00100008,
    /** The reverberation style typical of popular music. */
    BBRtcAudioReverbPresetPopular __deprecated_enum_msg("BBRtcAudioReverbPresetPopular is deprecated.") = 0x00000001,
    /** The reverberation style typical of R&B music. */
    BBRtcAudioReverbPresetRnB __deprecated_enum_msg("BBRtcAudioReverbPresetRnB is deprecated.") = 0x00000002,
    /** The reverberation style typical of rock music. */
    BBRtcAudioReverbPresetRock __deprecated_enum_msg("BBRtcAudioReverbPresetRock is deprecated.") = 0x00000003,
    /** The reverberation style typical of hip-hop music. */
    BBRtcAudioReverbPresetHipHop __deprecated_enum_msg("BBRtcAudioReverbPresetHipHop is deprecated.") = 0x00000004,
    /** The reverberation style typical of a concert hall. */
    BBRtcAudioReverbPresetVocalConcert __deprecated_enum_msg("BBRtcAudioReverbPresetVocalConcert is deprecated.") = 0x00000005,
    /** The reverberation style typical of a KTV venue. */
    BBRtcAudioReverbPresetKTV __deprecated_enum_msg("BBRtcAudioReverbPresetKTV is deprecated.") = 0x00000006,
    /** The reverberation style typical of a recording studio. */
    BBRtcAudioReverbPresetStudio __deprecated_enum_msg("BBRtcAudioReverbPresetStudio is deprecated.") = 0x00000007,
    /** The reverberation of the virtual stereo. The virtual stereo is an effect that renders the monophonic audio as the stereo audio, so that all users in the channel can hear the stereo voice effect. To achieve better virtual stereo reverberation, BBRtc recommends setting the `profile` parameter in `setAudioProfile` as `BBRtcAudioProfileMusicHighQualityStereo(5)`. */
    BBRtcAudioReverbPresetVirtualStereo __deprecated_enum_msg("BBRtcAudioReverbPresetVirtualStereo is deprecated.") = 0x00200001,
    /** The reverberation of the Electronic Voice */
    BBRtcAudioReverbPresetElectronicVoice __deprecated_enum_msg("BBRtcAudioReverbPresetElectronicVoice is deprecated.") = 0x00300001,
    /** 3D Voice */
    BBRtcAudioReverbPresetThreeDimVoice __deprecated_enum_msg("BBRtcAudioReverbPresetThreeDimVoice is deprecated.") = 0x00400001
};


/** Audio session restriction. */
typedef NS_OPTIONS(NSUInteger, BBRtcAudioSessionOperationRestriction) {
    /** No restriction, the SDK has full control of the audio session operations. */
    BBRtcAudioSessionOperationRestrictionNone              = 0,
    /** The SDK does not change the audio session category. */
    BBRtcAudioSessionOperationRestrictionSetCategory       = 1,
    /** The SDK does not change any setting of the audio session (category, mode, categoryOptions). */
    BBRtcAudioSessionOperationRestrictionConfigureSession  = 1 << 1,
    /** The SDK keeps the audio session active when leaving a channel. */
    BBRtcAudioSessionOperationRestrictionDeactivateSession = 1 << 2,
    /** The SDK does not configure the audio session anymore. */
    BBRtcAudioSessionOperationRestrictionAll               = 1 << 7
};

/** Audio codec profile. */
typedef NS_ENUM(NSInteger, BBRtcAudioCodecProfileType) {
    /** (Default) LC-AAC, the low-complexity audio codec profile. */
  BBRtcAudioCodecProfileLCAAC = 0,
  /** HE-AAC, the high-efficiency audio codec profile. */
  BBRtcAudioCodecProfileHEAAC = 1
};

/** The state of the remote audio. */
typedef NS_ENUM(NSUInteger, BBRtcAudioRemoteState) {
    /** 0: The remote audio is in the default state, probably due to BBRtcAudioRemoteReasonLocalMuted(3), BBRtcAudioRemoteReasonRemoteMuted(5), or BBRtcAudioRemoteReasonRemoteOffline(7). */
    BBRtcAudioRemoteStateStopped = 0,
    /** 1: The first remote audio packet is received. */
    BBRtcAudioRemoteStateStarting = 1,
    /** 2: The remote audio stream is decoded and plays normally, probably due to BBRtcAudioRemoteReasonNetworkRecovery(2), BBRtcAudioRemoteReasonLocalUnmuted(4), or BBRtcAudioRemoteReasonRemoteUnmuted(6). */
    BBRtcAudioRemoteStateDecoding = 2,
    /** 3: The remote audio is frozen, probably due to BBRtcAudioRemoteReasonNetworkCongestion(1). */
    BBRtcAudioRemoteStateFrozen = 3,
    /** 4: The remote audio fails to start, probably due to BBRtcAudioRemoteReasonInternal(0). */
    BBRtcAudioRemoteStateFailed = 4,
};

/** The reason of the remote audio state change. */
typedef NS_ENUM(NSUInteger, BBRtcAudioRemoteStateReason) {
    /** 0: Internal reasons. */
    BBRtcAudioRemoteReasonInternal = 0,
    /** 1: Network congestion. */
    BBRtcAudioRemoteReasonNetworkCongestion = 1,
    /** 2: Network recovery. */
    BBRtcAudioRemoteReasonNetworkRecovery = 2,
    /** 3: The local user stops receiving the remote audio stream or disables the audio module. */
    BBRtcAudioRemoteReasonLocalMuted = 3,
    /** 4: The local user resumes receiving the remote audio stream or enables the audio module. */
    BBRtcAudioRemoteReasonLocalUnmuted = 4,
    /** 5: The remote user stops sending the audio stream or disables the audio module. */
    BBRtcAudioRemoteReasonRemoteMuted = 5,
    /** 6: The remote user resumes sending the audio stream or enables the audio module. */
    BBRtcAudioRemoteReasonRemoteUnmuted = 6,
    /** 7: The remote user leaves the channel. */
    BBRtcAudioRemoteReasonRemoteOffline = 7,
};

/** The state of the local audio. */
typedef NS_ENUM(NSUInteger, BBRtcAudioLocalState) {
    /** 0: The local audio is in the initial state. */
    BBRtcAudioLocalStateStopped = 0,
    /** 1: The recording device starts successfully.  */
    BBRtcAudioLocalStateRecording = 1,
    /** 2: The first audio frame encodes successfully. */
    BBRtcAudioLocalStateEncoding = 2,
    /** 3: The local audio fails to start. */
    BBRtcAudioLocalStateFailed = 3,
};

/** The error information of the local audio. */
typedef NS_ENUM(NSUInteger, BBRtcAudioLocalError) {
    /** 0: The local audio is normal. */
    BBRtcAudioLocalErrorOk = 0,
    /** 1: No specified reason for the local audio failure. */
    BBRtcAudioLocalErrorFailure = 1,
    /** 2: No permission to use the local audio device. */
    BBRtcAudioLocalErrorDeviceNoPermission = 2,
    /** 3: The microphone is in use. */
    BBRtcAudioLocalErrorDeviceBusy = 3,
    /** 4: The local audio recording fails. Check whether the recording device is working properly. */
    BBRtcAudioLocalErrorRecordFailure = 4,
    /** 5: The local audio encoding fails. */
    BBRtcAudioLocalErrorEncodeFailure = 5,
};

/** Media device type. */
typedef NS_ENUM(NSInteger, BBRtcMediaDeviceType) {
    /** Unknown device. */
    BBRtcMediaDeviceTypeAudioUnknown = -1,
    /** Audio playback device. */
    BBRtcMediaDeviceTypeAudioPlayout = 0,
    /** Audio recording device. */
    BBRtcMediaDeviceTypeAudioRecording = 1,
    /** Video render device. */
    BBRtcMediaDeviceTypeVideoRender = 2,
    /** Video capture device. */
    BBRtcMediaDeviceTypeVideoCapture = 3,
};

/** Connection states. */
typedef NS_ENUM(NSInteger, BBRtcConnectionStateType) {
    /** <p>1: The SDK is disconnected from BBRtc's edge server.</p>
This is the initial state before [joinChannelByToken]([BBRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]).<br>
The SDK also enters this state when the app calls [leaveChannel]([BBRtcEngineKit leaveChannel:]).
    */
    BBRtcConnectionStateDisconnected = 1,
    /** <p>2: The SDK is connecting to BBRtc's edge server.</p>
When the app calls [joinChannelByToken]([BBRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]), the SDK starts to establish a connection to the specified channel, triggers the [connectionChangedToState]([BBRtcEngineDelegate rtcEngine:connectionChangedToState:reason:]) callback, and switches to the `BBRtcConnectionStateConnecting` state.<br>
<br>
When the SDK successfully joins the channel, the SDK triggers the [connectionChangedToState]([BBRtcEngineDelegate rtcEngine:connectionChangedToState:reason:]) callback and switches to the `BBRtcConnectionStateConnected` state.<br>
<br>
After the SDK joins the channel and when it finishes initializing the media engine, the SDK triggers the [didJoinChannel]([BBRtcEngineDelegate rtcEngine:didJoinChannel:withUid:elapsed:]) callback.
*/
    BBRtcConnectionStateConnecting = 2,
    /** <p>3: The SDK is connected to BBRtc's edge server and joins a channel. You can now publish or subscribe to a media stream in the channel.</p>
If the connection to the channel is lost because, for example, the network is down or switched, the SDK automatically tries to reconnect and triggers:
<li> The [rtcEngineConnectionDidInterrupted]([BBRtcEngineDelegate rtcEngineConnectionDidInterrupted:])(deprecated) callback
<li> The [connectionChangedToState]([BBRtcEngineDelegate rtcEngine:connectionChangedToState:reason:]) callback, and switches to the `BBRtcConnectionStateReconnecting` state.
    */
    BBRtcConnectionStateConnected = 3,
    /** <p>4: The SDK keeps rejoining the channel after being disconnected from a joined channel because of network issues.</p>
<li>If the SDK cannot rejoin the channel within 10 seconds after being disconnected from BBRtc's edge server, the SDK triggers the [rtcEngineConnectionDidLost]([BBRtcEngineDelegate rtcEngineConnectionDidLost:]) callback, stays in the `BBRtcConnectionStateReconnecting` state, and keeps rejoining the channel.
<li>If the SDK fails to rejoin the channel 20 minutes after being disconnected from BBRtc's edge server, the SDK triggers the [connectionChangedToState]([BBRtcEngineDelegate rtcEngine:connectionChangedToState:reason:]) callback, switches to the `BBRtcConnectionStateFailed` state, and stops rejoining the channel.
    */
    BBRtcConnectionStateReconnecting = 4,
    /** <p>5: The SDK fails to connect to BBRtc's edge server or join the channel.</p>
You must call [leaveChannel]([BBRtcEngineKit leaveChannel:]) to leave this state, and call [joinChannelByToken]([BBRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]) again to rejoin the channel.<br>
<br>
If the SDK is banned from joining the channel by BBRtc's edge server (through the RESTful API), the SDK triggers the [rtcEngineConnectionDidBanned]([BBRtcEngineDelegate rtcEngineConnectionDidBanned:])(deprecated) and [connectionChangedToState]([BBRtcEngineDelegate rtcEngine:connectionChangedToState:reason:]) callbacks.
    */
    BBRtcConnectionStateFailed = 5,

    /** 6：Reconnect successfully
     */
    BBRtcConnectionStateReConnected = 6,
    /** 7:The media subscriber service is connected and starts playing.
    * Used for direct pull stream
    */
    BBRtcConnectionStateSubscriberConnected = 7,
};

/** Reasons for the connection state change. */
typedef NS_ENUM(NSUInteger, BBRtcConnectionChangedReason) {
    /** 0: The SDK is connecting to BBRtc's edge server. */
    BBRtcConnectionChangedConnecting = 0,
    /** 1: The SDK has joined the channel successfully. */
    BBRtcConnectionChangedJoinSuccess = 1,
    /** 2: The connection between the SDK and BBRtc's edge server is interrupted.  */
    BBRtcConnectionChangedInterrupted = 2,
    /** 3: The connection between the SDK and BBRtc's edge server is banned by BBRtc's edge server. */
    BBRtcConnectionChangedBannedByServer = 3,
    /** 4: The SDK fails to join the channel for more than 20 minutes and stops reconnecting to the channel. */
    BBRtcConnectionChangedJoinFailed = 4,
    /** 5: The SDK has left the channel. */
    BBRtcConnectionChangedLeaveChannel = 5,
    /** 6: The specified App ID is invalid. Try to rejoin the channel with a valid App ID. */
    BBRtcConnectionChangedInvalidAppId = 6,
    /** 7: The specified channel name is invalid. Try to rejoin the channel with a valid channel name. */
    BBRtcConnectionChangedInvalidChannelName = 7,
    /** 8: The generated token is invalid probably due to the following reasons:
<li>The App Certificate for the project is enabled in Console, but you do not use Token when joining the channel. If you enable the App Certificate, you must use a token to join the channel.
<li>The uid that you specify in the [joinChannelByToken]([BBRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]) method is different from the uid that you pass for generating the token. */
    BBRtcConnectionChangedInvalidToken = 8,
    /** 9: The token has expired. Generate a new token from your server. */
    BBRtcConnectionChangedTokenExpired = 9,
    /** 10: The user is banned by the server. */
    BBRtcConnectionChangedRejectedByServer = 10,
    /** 11: The SDK tries to reconnect after setting a proxy server. */
    BBRtcConnectionChangedSettingProxyServer = 11,
    /** 12: The token renews. */
    BBRtcConnectionChangedRenewToken = 12,
    /** 13: The client IP address has changed, probably due to a change of the network type, IP address, or network port. */
    BBRtcConnectionChangedClientIpAddressChanged = 13,
    /** 14: Timeout for the keep-alive of the connection between the SDK and BBRtc's edge server. The connection state changes to BBRtcConnectionStateReconnecting(4). */
    BBRtcConnectionChangedKeepAliveTimeout = 14,
};

/** The state code in BBRtcChannelMediaRelayState.
 */
typedef NS_ENUM(NSInteger, BBRtcChannelMediaRelayState) {
    /** 0: The SDK is initializing.
     */
    BBRtcChannelMediaRelayStateIdle = 0,
    /** 1: The SDK tries to relay the media stream to the destination channel.
     */
    BBRtcChannelMediaRelayStateConnecting = 1,
    /** 2: The SDK successfully relays the media stream to the destination channel.
     */
    BBRtcChannelMediaRelayStateRunning = 2,
    /** 3: A failure occurs. See the details in `error`.
     */
    BBRtcChannelMediaRelayStateFailure = 3,
};

/** The event code in BBRtcChannelMediaRelayEvent.
 */
typedef NS_ENUM(NSInteger, BBRtcChannelMediaRelayEvent) {
    /** 0: The user disconnects from the server due to poor network connections.
     */
    BBRtcChannelMediaRelayEventDisconnect = 0,
    /** 1: The network reconnects.
     */
    BBRtcChannelMediaRelayEventConnected = 1,
    /** 2: The user joins the source channel.
     */
    BBRtcChannelMediaRelayEventJoinedSourceChannel = 2,
    /** 3: The user joins the destination channel.
     */
    BBRtcChannelMediaRelayEventJoinedDestinationChannel = 3,
    /** 4: The SDK starts relaying the media stream to the destination channel.
     */
    BBRtcChannelMediaRelayEventSentToDestinationChannel = 4,
    /** 5: The server receives the video stream from the source channel.
     */
    BBRtcChannelMediaRelayEventReceivedVideoPacketFromSource = 5,
    /** 6: The server receives the audio stream from the source channel.
     */
    BBRtcChannelMediaRelayEventReceivedAudioPacketFromSource = 6,
    /** 7: The destination channel is updated.
     */
    BBRtcChannelMediaRelayEventUpdateDestinationChannel = 7,
    /** 8: The destination channel update fails due to internal reasons.
     */
    BBRtcChannelMediaRelayEventUpdateDestinationChannelRefused = 8,
    /** 9: The destination channel does not change, which means that the destination channel fails to be updated.
     */
    BBRtcChannelMediaRelayEventUpdateDestinationChannelNotChange = 9,
    /** 10: The destination channel name is NULL.
     */
    BBRtcChannelMediaRelayEventUpdateDestinationChannelIsNil = 10,
    /** 11: The video profile is sent to the server.
     */
    BBRtcChannelMediaRelayEventVideoProfileUpdate = 11,
};

/** The error code in BBRtcChannelMediaRelayError.
 */
typedef NS_ENUM(NSInteger, BBRtcChannelMediaRelayError) {
    /** 0: The state is normal.
     */
    BBRtcChannelMediaRelayErrorNone = 0,
    /** 1: An error occurs in the server response.
     */
    BBRtcChannelMediaRelayErrorServerErrorResponse = 1,
    /** 2: No server response. You can call the [leaveChannel]([BBRtcEngineKit leaveChannel:]) method to leave the channel.
     */
    BBRtcChannelMediaRelayErrorServerNoResponse = 2,
    /** 3: The SDK fails to access the service, probably due to limited resources of the server.
     */
    BBRtcChannelMediaRelayErrorNoResourceAvailable = 3,
    /** 4: Fails to send the relay request.
     */
    BBRtcChannelMediaRelayErrorFailedJoinSourceChannel = 4,
    /** 5: Fails to accept the relay request.
     */
    BBRtcChannelMediaRelayErrorFailedJoinDestinationChannel = 5,
    /** 6: The server fails to receive the media stream.
     */
    BBRtcChannelMediaRelayErrorFailedPacketReceivedFromSource = 6,
    /** 7: The server fails to send the media stream.
     */
    BBRtcChannelMediaRelayErrorFailedPacketSentToDestination = 7,
    /** 8: The SDK disconnects from the server due to poor network connections. You can call the [leaveChannel]([BBRtcEngineKit leaveChannel:]) method to leave the channel.
     */
    BBRtcChannelMediaRelayErrorServerConnectionLost = 8,
    /** 9: An internal error occurs in the server.
     */
    BBRtcChannelMediaRelayErrorInternalError = 9,
    /** 10: The token of the source channel has expired.    
     */
    BBRtcChannelMediaRelayErrorSourceTokenExpired = 10,
    /** 11: The token of the destination channel has expired.
     */
    BBRtcChannelMediaRelayErrorDestinationTokenExpired = 11,
};

/** Network type. */
typedef NS_ENUM(NSInteger, BBRtcNetworkType) {
  /** -1: The network type is unknown. */
  BBRtcNetworkTypeUnknown = -1,
  /** 0: The SDK disconnects from the network. */
  BBRtcNetworkTypeDisconnected = 0,
  /** 1: The network type is LAN. */
  BBRtcNetworkTypeLAN = 1,
  /** 2: The network type is Wi-Fi (including hotspots). */
  BBRtcNetworkTypeWIFI = 2,
  /** 3: The network type is mobile 2G. */
  BBRtcNetworkTypeMobile2G = 3,
  /** 4: The network type is mobile 3G. */
  BBRtcNetworkTypeMobile3G = 4,
  /** 5: The network type is mobile 4G. */
  BBRtcNetworkTypeMobile4G = 5,
};

/** The video encoding degradation preference under limited bandwidth. */
typedef NS_ENUM(NSInteger, BBRtcDegradationPreference) {
    /** (Default) Degrades the frame rate to guarantee the video quality. */
    BBRtcDegradationMaintainQuality = 0,
    /** Degrades the video quality to guarantee the frame rate. */
    BBRtcDegradationMaintainFramerate = 1,
    /** Reserved for future use. */
    BBRtcDegradationBalanced = 2,
    
    BBRtcDegradationDisable = 3,
};
/** The lightening contrast level. */
typedef NS_ENUM(NSUInteger, BBRtcLighteningContrastLevel) {
    /** Low contrast level. */
    BBRtcLighteningContrastLow = 0,
    /** (Default) Normal contrast level. */
    BBRtcLighteningContrastNormal = 1,
    /** High contrast level. */
    BBRtcLighteningContrastHigh = 2,
};

/** The state of the probe test result. */
typedef NS_ENUM(NSUInteger, BBRtcLastmileProbeResultState) {
  /** 1: the last-mile network probe test is complete. */
  BBRtcLastmileProbeResultComplete = 1,
  /** 2: the last-mile network probe test is incomplete and the bandwidth estimation is not available, probably due to limited test resources. */
  BBRtcLastmileProbeResultIncompleteNoBwe = 2,
  /** 3: the last-mile network probe test is not carried out, probably due to poor network conditions. */
  BBRtcLastmileProbeResultUnavailable = 3,
};

/** The state of the local video stream. */
typedef NS_ENUM(NSInteger, BBRtcLocalVideoStreamState) {
  /** 0: the local video is in the initial state. */
  BBRtcLocalVideoStreamStateStopped = 0,
  /** 1: the local video capturer starts successfully. */
  BBRtcLocalVideoStreamStateCapturing = 1,
  /** 2: the first local video frame encodes successfully. */
  BBRtcLocalVideoStreamStateEncoding = 2,
  /** 3: the local video fails to start. */
  BBRtcLocalVideoStreamStateFailed = 3,
};

/** The detailed error information of the local video. */
typedef NS_ENUM(NSInteger, BBRtcLocalVideoStreamError) {
  /** 0: the local video is normal. */
  BBRtcLocalVideoStreamErrorOK = 0,
  /** 1: no specified reason for the local video failure. */
  BBRtcLocalVideoStreamErrorFailure = 1,
  /** 2: no permission to use the local video device. */
  BBRtcLocalVideoStreamErrorDeviceNoPermission = 2,
  /** 3: the local video capturer is in use. */
  BBRtcLocalVideoStreamErrorDeviceBusy = 3,
  /** 4: the local video capture fails. Check whether the capturer is working properly. */
  BBRtcLocalVideoStreamErrorCaptureFailure = 4,
  /** 5: the local video encoding fails. */
  BBRtcLocalVideoStreamErrorEncodeFailure = 5,
};


/** The options for SDK preset audio effects. */
typedef NS_ENUM(NSInteger, BBRtcAudioEffectPreset) {
    /** Turn off audio effects and use the original voice. */
    BBRtcAudioEffectOff = 0x00000000,
    /** An audio effect typical of a KTV venue.
     <p>**Note**</p>
     <p>To achieve better audio effect quality, BBRtc recommends calling [setAudioProfile]([BBRtcRtcEngineKit setAudioProfile:scenario:])
     and setting the `profile` parameter to `BBRtcAudioProfileMusicHighQuality(4)` or `BBRtcAudioProfileMusicHighQualityStereo(5)`
     before setting this enumerator.</p>
     */
    BBRtcRoomAcousticsKTV = 0x02010100,
    /** An audio effect typical of a concert hall.
     <p>**Note**</p>
     <p>To achieve better audio effect quality, BBRtc recommends calling [setAudioProfile]([BBRtcRtcEngineKit setAudioProfile:scenario:])
     and setting the `profile` parameter to `BBRtcAudioProfileMusicHighQuality(4)` or `BBRtcAudioProfileMusicHighQualityStereo(5)`
     before setting this enumerator.</p>
     */
    BBRtcRoomAcousticsVocalConcert = 0x02010200,
    /** An audio effect typical of a recording studio.
     <p>**Note**</p>
     <p>To achieve better audio effect quality, BBRtc recommends calling [setAudioProfile]([BBRtcRtcEngineKit setAudioProfile:scenario:])
     and setting the `profile` parameter to `BBRtcAudioProfileMusicHighQuality(4)` or `BBRtcAudioProfileMusicHighQualityStereo(5)`
     before setting this enumerator.</p>
     */
    BBRtcRoomAcousticsStudio = 0x02010300,
    /** An audio effect typical of a vintage phonograph.
     <p>**Note**</p>
     <p>To achieve better audio effect quality, BBRtc recommends calling [setAudioProfile]([BBRtcRtcEngineKit setAudioProfile:scenario:])
     and setting the `profile` parameter to `BBRtcAudioProfileMusicHighQuality(4)` or `BBRtcAudioProfileMusicHighQualityStereo(5)`
     before setting this enumerator.</p>
     */
    BBRtcRoomAcousticsPhonograph = 0x02010400,
    /** A virtual stereo effect that renders monophonic audio as stereo audio.
     <p>**Note**</p>
     <p>Call [setAudioProfile]([BBRtcRtcEngineKit setAudioProfile:scenario:]) and set the `profile` parameter to
     `BBRtcAudioProfileMusicStandardStereo(3)` or `BBRtcAudioProfileMusicHighQualityStereo(5)` before setting this enumerator;
     otherwise, the enumerator setting does not take effect.</p>
     */
    BBRtcRoomAcousticsVirtualStereo = 0x02010500,
    /** A more spatial audio effect.
     <p>**Note**</p>
     <p>To achieve better audio effect quality, BBRtc recommends calling [setAudioProfile]([BBRtcRtcEngineKit setAudioProfile:scenario:])
     and setting the `profile` parameter to `BBRtcAudioProfileMusicHighQuality(4)` or `BBRtcAudioProfileMusicHighQualityStereo(5)`
     before setting this enumerator.</p>
     */
    BBRtcRoomAcousticsSpacial = 0x02010600,
    /** A more ethereal audio effect.
     <p>**Note**</p>
     <p>To achieve better audio effect quality, BBRtc recommends calling [setAudioProfile]([BBRtcRtcEngineKit setAudioProfile:scenario:])
     and setting the `profile` parameter to `BBRtcAudioProfileMusicHighQuality(4)` or `BBRtcAudioProfileMusicHighQualityStereo(5)`
     before setting this enumerator.</p>
     */
    BBRtcRoomAcousticsEthereal = 0x02010700,
    /** A 3D voice effect that makes the voice appear to be moving around the user. The default cycle period of the 3D voice effect is
     10 seconds. To change the cycle period, call [setAudioEffectParameters]([BBRtcRtcEngineKit setAudioEffectParameters:param1:param2:])
     after this method.
     <p>**Note**</p>
     <li>Call [setAudioProfile]([BBRtcRtcEngineKit setAudioProfile:scenario:]) and set the `profile` parameter to
     `BBRtcAudioProfileMusicStandardStereo(3)` or `BBRtcAudioProfileMusicHighQualityStereo(5)` before setting this enumerator;
     otherwise, the enumerator setting does not take effect.</li>
     <li>If the 3D voice effect is enabled, users need to use stereo audio playback devices to hear the anticipated voice effect.</li>
     */
    BBRtcRoomAcoustics3DVoice = 0x02010800,
    /** The voice of a middle-aged man.
     <p>**Note**</p>
     <li>BBRtc recommends using this enumerator to process a male-sounding voice; otherwise, you may not hear the anticipated voice
     effect.</li>
     <li>To achieve better audio effect quality, BBRtc recommends calling [setAudioProfile]([BBRtcRtcEngineKit setAudioProfile:scenario:])
     and setting the `profile` parameter to `BBRtcAudioProfileMusicHighQuality(4)` or `BBRtcAudioProfileMusicHighQualityStereo(5)`
     before setting this enumerator.</li>
     */
    BBRtcVoiceChangerEffectUncle = 0x02020100,
    /** The voice of an old man.
     <p>**Note**</p>
     <li>BBRtc recommends using this enumerator to process a male-sounding voice; otherwise, you may not hear the anticipated voice
     effect.</li>
     <li>To achieve better audio effect quality, BBRtc recommends calling [setAudioProfile]([BBRtcRtcEngineKit setAudioProfile:scenario:])
     and setting the `profile` parameter to `BBRtcAudioProfileMusicHighQuality(4)` or `BBRtcAudioProfileMusicHighQualityStereo(5)`
     before setting this enumerator.</li>
     */
    BBRtcVoiceChangerEffectOldMan = 0x02020200,
    /** The voice of a boy.
     <p>**Note**</p>
     <li>BBRtc recommends using this enumerator to process a male-sounding voice; otherwise, you may not hear the anticipated voice
     effect.</li>
     <li>To achieve better audio effect quality, BBRtc recommends calling [setAudioProfile]([BBRtcRtcEngineKit setAudioProfile:scenario:])
     and setting the `profile` parameter to `BBRtcAudioProfileMusicHighQuality(4)` or `BBRtcAudioProfileMusicHighQualityStereo(5)`
     before setting this enumerator.</li>
     */
    BBRtcVoiceChangerEffectBoy = 0x02020300,
    /** The voice of a young woman.
     <p>**Note**</p>
     <li>BBRtc recommends using this enumerator to process a female-sounding voice; otherwise, you may not hear the anticipated voice
     effect.</li>
     <li>To achieve better audio effect quality, BBRtc recommends calling [setAudioProfile]([BBRtcRtcEngineKit setAudioProfile:scenario:])
     and setting the `profile` parameter to `BBRtcAudioProfileMusicHighQuality(4)` or `BBRtcAudioProfileMusicHighQualityStereo(5)`
     before setting this enumerator.</li>
     */
    BBRtcVoiceChangerEffectSister = 0x02020400,
    /** The voice of a girl.
     <p>**Note**</p>
     <li>BBRtc recommends using this enumerator to process a female-sounding voice; otherwise, you may not hear the anticipated voice
     effect.</li>
     <li>To achieve better audio effect quality, BBRtc recommends calling [setAudioProfile]([BBRtcRtcEngineKit setAudioProfile:scenario:])
     and setting the `profile` parameter to `BBRtcAudioProfileMusicHighQuality(4)` or `BBRtcAudioProfileMusicHighQualityStereo(5)`
     before setting this enumerator.</li>
     */
    BBRtcVoiceChangerEffectGirl = 0x02020500,
    /** The voice of Pig King, a character in Journey to the West who has a voice like a growling bear.
     <p>**Note**</p>
     <p>To achieve better audio effect quality, BBRtc recommends calling [setAudioProfile]([BBRtcRtcEngineKit setAudioProfile:scenario:])
     and setting the `profile` parameter to `BBRtcAudioProfileMusicHighQuality(4)` or `BBRtcAudioProfileMusicHighQualityStereo(5)`
     before setting this enumerator.</p>
     */
    BBRtcVoiceChangerEffectPigKing = 0x02020600,
    /** The voice of Hulk.
     <p>**Note**</p>
     <p>To achieve better audio effect quality, BBRtc recommends calling [setAudioProfile]([BBRtcRtcEngineKit setAudioProfile:scenario:])
     and setting the `profile` parameter to `BBRtcAudioProfileMusicHighQuality(4)` or `BBRtcAudioProfileMusicHighQualityStereo(5)`
     before setting this enumerator.</p>
     */
    BBRtcVoiceChangerEffectHulk = 0x02020700,
    /** An audio effect typical of R&B music.
     <p>**Note**</p>
     <p>Call [setAudioProfile]([BBRtcRtcEngineKit setAudioProfile:scenario:]) and set the `profile` parameter to
     `BBRtcAudioProfileMusicHighQuality(4)` or `BBRtcAudioProfileMusicHighQualityStereo(5)` before setting this enumerator;
     otherwise, the enumerator setting does not take effect.</p>
     */
    BBRtcStyleTransformationRnB = 0x02030100,
    /** An audio effect typical of popular music.
     <p>**Note**</p>
     <p>Call [setAudioProfile]([BBRtcRtcEngineKit setAudioProfile:scenario:]) and set the `profile` parameter to
     `BBRtcAudioProfileMusicHighQuality(4)` or `BBRtcAudioProfileMusicHighQualityStereo(5)` before setting this enumerator;
     otherwise, the enumerator setting does not take effect.</p>
     */
    BBRtcStyleTransformationPopular = 0x02030200,
    /** A pitch correction effect that corrects the user's pitch based on the pitch of the natural C major scale. To change the basic
     mode and tonic pitch, call [setAudioEffectParameters]([BBRtcRtcEngineKit setAudioEffectParameters:param1:param2:]) after this method.
     <p>**Note**</p>
     <p>To achieve better audio effect quality, BBRtc recommends calling [setAudioProfile]([BBRtcRtcEngineKit setAudioProfile:scenario:])
     and setting the `profile` parameter to `BBRtcAudioProfileMusicHighQuality(4)` or `BBRtcAudioProfileMusicHighQualityStereo(5)`
     before setting this enumerator.</p>
     */
    BBRtcPitchCorrection = 0x02040100
};


/** The options for SDK preset voice beautifier effects. */
typedef NS_ENUM(NSInteger, BBRtcVoiceBeautifierPreset) {
    /** Turn off voice beautifier effects and use the original voice. */
    BBRtcVoiceBeautifierOff = 0x00000000,
    /** A more magnetic voice.<p>**Note**</p><p>BBRtc recommends using this enumerator to process a male-sounding voice; otherwise, you
     may experience vocal distortion.</p>
     */
    BBRtcChatBeautifierMagnetic = 0x01010100,
    /** A fresher voice.<p>**Note**</p><p>BBRtc recommends using this enumerator to process a female-sounding voice; otherwise, you
     may experience vocal distortion.</p>
     */
    BBRtcChatBeautifierFresh = 0x01010200,
    /** A more vital voice.<p>**Note**</p><p>BBRtc recommends using this enumerator to process a female-sounding voice; otherwise, you
     may experience vocal distortion.</p>
     */
    BBRtcChatBeautifierVitality = 0x01010300,
    /** Singing beautifier effect.
     <li>If you call [setVoiceBeautifierPreset(BBRtcSingingBeautifier)]([BBRtcRtcEngineKit setVoiceBeautifierPreset:]), 
     you can beautify a male-sounding voice and add a reverberation effect that 
     sounds like singing in a small room. BBRtc recommends not using 
     <tt>setVoiceBeautifierPreset(BBRtcSingingBeautifier)</tt> to process a 
     female-sounding voice; otherwise, you may experience vocal distortion.</li>
     <li>If you call [setVoiceBeautifierParameters(BBRtcSingingBeautifier, param1, param2)]([BBRtcRtcEngineKit setVoiceBeautifierParameters:param1:param2:]), 
     you can beautify a male- or female-sounding voice and add a reverberation 
     effect.</li>

     @since v3.3.0
     */
    BBRtcSingingBeautifier = 0x01020100,
    /** A more vigorous voice. */
    BBRtcTimbreTransformationVigorous = 0x01030100,
    /** A deeper voice. */
    BBRtcTimbreTransformationDeep = 0x01030200,
    /** A mellower voice. */
    BBRtcTimbreTransformationMellow = 0x01030300,
    /** A falsetto voice. */
    BBRtcTimbreTransformationFalsetto = 0x01030400,
    /** A fuller voice. */
    BBRtcTimbreTransformationFull = 0x01030500,
    /** A clearer voice. */
    BBRtcTimbreTransformationClear = 0x01030600,
    /** A more resounding voice. */
    BBRtcTimbreTransformationResounding = 0x01030700,
    /** A more ringing voice. */
    BBRtcTimbreTransformationRinging = 0x01030800
};

typedef NS_ENUM(NSInteger, BBRtcVoiceConversionPreset) {
    BBRtcVoiceConversionOff = 0x00000000,
    BBRtcVoiceChangerNeutral = 0x03010100,
    BBRtcVoiceChangerSweet = 0x03010200,
    BBRtcVoiceChangerSolid = 0x03010300,
    BBRtcVoiceChangerBass = 0x03010400
};

/** The color video format. (iOS only)

 @since v3.4.5
 */
typedef NS_ENUM(NSUInteger, BBRtcVideoFrameType) {
  /** 0: (Default) YUV 420
   */
  BBRtcVideoFrameTypeYUV420 = 0,  // YUV 420 format
  /** 1: YUV422
   */
  BBRtcVideoFrameTypeYUV422 = 1,  // YUV 422 format
  /** 2: RGBA
   */
  BBRtcVideoFrameTypeRGBA = 2,  // RGBA format
};

/** The bit mask of the observation positions. (iOS only)

 @since v3.4.5
 */
typedef NS_ENUM(NSUInteger, BBRtcVideoFramePosition) {
  /** (Default) The position to observe the video data captured by the local
   camera, which corresponds to the
   [onCaptureVideoFrame]([BBRtcVideoDataFrameProtocol onCaptureVideoFrame:])
   callback.
   */
  BBRtcVideoFramePositionPostCapture = 1 << 0,
  /** (Default) The position to observe the incoming remote video data,
   which corresponds to the
   [onRenderVideoFrame]([BBRtcVideoDataFrameProtocol onRenderVideoFrame:forUid:]) or
   [onRenderVideoFrameEx]([BBRtcVideoDataFrameProtocol onRenderVideoFrameEx:forUid:inChannel:])
   callback.
   */
  BBRtcVideoFramePositionPreRenderer = 1 << 1,
  /** The position to observe the local pre-encoded video data, which
   corresponds to the
   [onPreEncodeVideoFrame]([BBRtcVideoDataFrameProtocol onPreEncodeVideoFrame:])
   callback.
   */
  BBRtcVideoFramePositionPreEncoder = 1 << 2,
};

/** The bit mask that controls the audio observation positions. (iOS only)

 @since v3.4.5
 */
typedef NS_ENUM(NSUInteger, BBRtcAudioFramePosition) {
  /** The position for observing the playback audio of all remote users after
   mixing, which enables the SDK to trigger the
   [onPlaybackAudioFrame]([BBRtcAudioDataFrameProtocol onPlaybackAudioFrame:])
   callback.
   */
  BBRtcAudioFramePositionPlayback = 1 << 0,
  /** The position for observing the recorded audio of the local user, which
   enables the SDK to trigger the
   [onRecordAudioFrame]([BBRtcAudioDataFrameProtocol onRecordAudioFrame:])
   callback.
   */
  BBRtcAudioFramePositionRecord = 1 << 1,
  /** The position for observing the mixed audio of the local user and all
   remote users, which enables the SDK to trigger the
   [onMixedAudioFrame]([BBRtcAudioDataFrameProtocol onMixedAudioFrame:])
   callback.
   */
  BBRtcAudioFramePositionMixed = 1 << 2,
  /** The position for observing the audio of a single remote user before
   mixing, which enables the SDK to trigger the
   [onPlaybackAudioFrameBeforeMixing]([BBRtcAudioDataFrameProtocol onPlaybackAudioFrameBeforeMixing:uid:])
   callback.
   S-54718: add mutiplechannel and beforeMixingEx for audioDataFrameProtocol)
   */
  BBRtcAudioFramePositionBeforeMixing = 1 << 3,

};

/** The video noise reduction mode.

 */
typedef NS_ENUM(NSUInteger, BBRtcVideoDenoiserMode) {
  /** 0: (Default) Automatic mode. The SDK automatically enables or disables the video noise reduction feature according to the ambient light. */
  BBRtcVideoDenoiserModeAuto = 0,
  /** 1: Manual mode. Users need to enable or disable the video noise reduction feature manually.  */
  BBRtcVideoDenoiserModeManual = 1,
};

/** The video noise reduction level.

 */
typedef NS_ENUM(NSUInteger, BBRtcVideoDenoiserLevel) {
  /** 0: (Default) Promotes video quality during video noise reduction. `HighQuality` balances performance consumption and video noise reduction quality. The performance consumption is moderate, the video noise reduction speed is moderate, and the overall video quality is optimal. */
  BBRtcVideoDenoiserLevelHighQuality = 0,
  /** 1: Promotes reducing performance consumption during video noise reduction. `Fast` prioritizes reducing performance consumption over video noise reduction quality. The performance consumption is lower, and the video noise reduction speed is faster. To avoid a noticeable shadowing effect (shadows trailing behind moving objects) in the processed video, BBRtc recommends that you use `Fast` when the camera is fixed. */
  BBRtcVideoDenoiserLevelFast = 1,
  /** 2: Enhanced video noise reduction. `Strength` prioritizes video noise reduction quality over reducing performance consumption. The performance consumption is higher, the video noise reduction speed is slower, and the video noise reduction quality is better. If `HighQuality` is not enough for your video noise reduction needs, you can use `Strength`. */
  BBRtcVideoDenoiserLevelStrength = 2,

};

/** The low-light enhancement mode.

 */
typedef NS_ENUM(NSUInteger, BBRtcLowlightEnhanceMode) {
  /** 0: (Default) Automatic mode. The SDK automatically enables or disables the low-light enhancement feature according to the ambient light to compensate for the lighting level or prevent overexposure, as necessary. */
  BBRtcLowlightEnhanceModeAuto = 0,
  /** 1: Manual mode. Users need to enable or disable the low-light enhancement feature manually. */
  BBRtcLowlightEnhanceModeManual = 1,
};

/** The low-light enhancement level.

 */
typedef NS_ENUM(NSUInteger, BBRtcLowlightEnhanceLevel) {
  /** 0: (Default) Promotes video quality during low-light enhancement. It processes the brightness, details, and noise of the video image. The performance consumption is moderate, the processing speed is moderate, and the overall video quality is optimal. */
  BBRtcLowlightEnhanceLevelQuality = 0,
  /** 1: Promotes performance during low-light enhancement. It processes the brightness and details of the video image. The processing speed is faster. */
  BBRtcLowlightEnhanceLevelFast = 1,
};

/** The type of the custom background image.

 */
typedef NS_ENUM(NSUInteger, BBRtcVirtualBackgroundSourceType) {
  /** 1: (Default) The background image is a solid color.*/
  BBRtcVirtualBackgroundColor = 1,
  /** 2: The background image is a file in PNG or JPG format.*/
  BBRtcVirtualBackgroundImg = 2,
  /** 3: The background image is blurred.
   */
  BBRtcVirtualBackgroundBlur = 3,
};

typedef NS_ENUM(NSUInteger, BBRtcBlurDegree) {
  /** 1: The degree of blurring applied to the custom background image is low.
   The user can almost see the background clearly.
   */
  BBRtcBlurLow = 1,
  /** 2: The degree of blurring applied to the custom background image is
   medium. It is difficult for the user to recognize details in the background.
   */
  BBRtcBlurMedium = 2,
  /** 3: (Default) The degree of blurring applied to the custom background
   image is high. The user can barely see any distinguishing features in the
   background.
   */
  BBRtcBlurHigh = 3,
};


