//
//  BBRtcBase.h
//  products
//
//  Created by bhb on 2020/4/16.
//  Copyright © 2020 banban. All rights reserved.
//

#ifndef BBRtcBase_h
#define BBRtcBase_h

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#define BB_CALL  //__cdecl
#if defined(BANBAN_EXPORT)
#define BB_API  __declspec(dllexport)
#else
#define BB_API   __declspec(dllimport)
#endif
#elif defined(__APPLE__)
#include <TargetConditionals.h>
#define BB_API __attribute__((visibility("default"))) //extern "C"
#define BB_CALL
#elif defined(__ANDROID__) || defined(__linux__)
#define BB_API  __attribute__((visibility("default")))
#define BB_CALL
#else
#define BB_API extern "C"
#define BB_CALL
#endif

namespace bbrtc {
namespace util {

template <class T>
class AutoPtr {
  typedef T value_type;
  typedef T* pointer_type;

 public:
  AutoPtr(pointer_type p = 0) : ptr_(p) {}
  ~AutoPtr() {
    if (ptr_)
      ptr_->release();
  }
  operator bool() const { return ptr_ != (pointer_type)0; }
  value_type& operator*() const { return *get(); }

  pointer_type operator->() const { return get(); }

  pointer_type get() const { return ptr_; }

  pointer_type release() {
    pointer_type tmp = ptr_;
    ptr_ = 0;
    return tmp;
  }

  void reset(pointer_type ptr = 0) {
    if (ptr != ptr_ && ptr_)
      ptr_->release();
    ptr_ = ptr;
  }
  template <class C1, class C2>
  bool queryInterface(C1* c, C2 iid) {
    pointer_type p = NULL;
    if (c && !c->queryInterface(iid, (void**)&p)) {
      reset(p);
    }
    return p != NULL;
  }

 private:
  AutoPtr(const AutoPtr&);
  AutoPtr& operator=(const AutoPtr&);

 private:
  pointer_type ptr_;
};

class IString {
 protected:
  virtual ~IString() {}

 public:
  virtual bool empty() const = 0;
  virtual const char* c_str() const = 0;
  virtual const char* data() const = 0;
  virtual size_t length() const = 0;
  virtual void release() = 0;
};
typedef AutoPtr<IString> AString;

class BString : public IString {
 public:
  BString() : ptr_(nullptr), len_(0) {}

  BString(char* str, size_t len = 0) {
    if (!str)
      return;
    if (!len)
      len = strlen(str);
    ptr_ = new char[len + 1];
    if (!ptr_)
      return;
    memcpy(ptr_, str, len);
    ptr_[len] = '\0';
    len_ = len;
  }

  ~BString() { release(); }

  BString& operator=(const BString& src) {
    if (src.empty())
      return *this;
    const size_t len = src.length();
    const char* str = src.data();
    ptr_ = new char[len + 1];
    if (!ptr_)
      return *this;
    memcpy(ptr_, str, len);
    ptr_[len] = '\0';
    len_ = len;
    return *this;
  }

  bool empty() const override { return ptr_ == nullptr; }
  const char* c_str() const override { return ptr_; }
  const char* data() const override { return ptr_; }
  size_t length() const override { return len_; }
  void release() override {
    if (ptr_) {
      delete[] ptr_;
      ptr_ = nullptr;
    }
    len_ = 0;
  }

 private:
  char* ptr_;
  size_t len_;
};
typedef AutoPtr<BString> ABString;

}  // namespace util

enum INTERFACE_ID_TYPE {
  BBRTC_IID_AUDIO_DEVICE_MANAGER = 1,
  BBRTC_IID_VIDEO_DEVICE_MANAGER = 2,
  BBRTC_IID_RTC_ENGINE_PARAMETER = 3,
  BBRTC_IID_MEDIA_ENGINE = 4,
  BBRTC_IID_SIGNALING_ENGINE = 8,
};

/**
 * Defines a comprehensive set of warning codes that the SDK uses to communicate various issues and states.
 * These warnings help developers understand the current status and take appropriate actions if necessary.
 */
enum WARN_CODE_TYPE {
  /** 8: The provided view is invalid. Ensure a valid view is specified for video functionalities. */
  WARN_INVALID_VIEW = 8,

  /** 16: Initialization of the video module failed, possibly due to insufficient resources. Voice communication remains operational. */
  WARN_INIT_VIDEO = 16,

  /** 20: The request is pending due to a module not being ready, causing the SDK to postpone processing. */
  WARN_PENDING = 20,

  /** 103: No channel resources are available, likely due to the server's inability to allocate resources at the moment. */
  WARN_NO_AVAILABLE_CHANNEL = 103,

  /** 104: A timeout has occurred while attempting to look up the channel, typically indicating poor network conditions. */
  WARN_LOOKUP_CHANNEL_TIMEOUT = 104,

  /** 105: **Deprecated** The server has rejected the channel lookup request and cannot process it or finds it invalid. Use `CONNECTION_CHANGED_REJECTED_BY_SERVER(10)` in the `onConnectionStateChanged` callback instead. Deprecated since v2.4.1. */
  WARN_LOOKUP_CHANNEL_REJECTED = 105,

  /** 106: A timeout has occurred while attempting to open the channel, typically due to poor network conditions. */
  WARN_OPEN_CHANNEL_TIMEOUT = 106,

  /** 107: The server has rejected the request to open the channel, either due to an invalid request or inability to process. */
  WARN_OPEN_CHANNEL_REJECTED = 107,

  /** 111: A timeout occurred when switching to live video, possibly due to network or resource issues. */
  WARN_SWITCH_LIVE_VIDEO_TIMEOUT = 111,

  /** 118: A timeout occurred when setting the client role in the live broadcast profile, indicating a potential configuration issue. */
  WARN_SET_CLIENT_ROLE_TIMEOUT = 118,

  /** 121: The ticket provided for opening the channel is invalid, requiring a valid ticket to proceed. */
  WARN_OPEN_CHANNEL_INVALID_TICKET = 121,

  /** 122: The system is attempting to connect to another server, likely due to issues with the current server. */
  WARN_OPEN_CHANNEL_TRY_NEXT_VOS = 122,

  /** 131: The channel connection is unrecoverable, indicating a severe issue requiring immediate attention. */
  WARN_CHANNEL_CONNECTION_UNRECOVERABLE = 131,

  /** 132: The IP for the channel connection has changed, which may affect connectivity. */
  WARN_CHANNEL_CONNECTION_IP_CHANGED = 132,

  /** 133: The port for the channel connection has changed, which may affect connectivity. */
  WARN_CHANNEL_CONNECTION_PORT_CHANGED = 133,

  /** 701: An error occurred while attempting to open an audio mixing file, affecting audio processing. */
  WARN_AUDIO_MIXING_OPEN_ERROR = 701,

  /** 1014: A runtime warning in the audio device module related to playback device issues. */
  WARN_ADM_RUNTIME_PLAYOUT_WARNING = 1014,

  /** 1016: A runtime warning in the audio device module related to recording device issues. */
  WARN_ADM_RUNTIME_RECORDING_WARNING = 1016,

  /** 1019: No valid audio data is being collected by the recording device, indicating a potential hardware or configuration issue. */
  WARN_ADM_RECORD_AUDIO_SILENCE = 1019,

  /** 1020: The playback device has failed, affecting audio output. */
  WARN_ADM_PLAYOUT_MALFUNCTION = 1020,

  /** 1021: The recording device has failed, affecting audio input. */
  WARN_ADM_RECORD_MALFUNCTION = 1021,

  /** 1025: Audio operations are interrupted by system events, such as an incoming phone call. */
  WARN_ADM_CALL_INTERRUPTION = 1025,

  /** 1029: The audio session category is not set to `AVAudioSessionCategoryPlayAndRecord`, which may lead to improper audio handling. */
  WARN_ADM_IOS_CATEGORY_NOT_PLAYANDRECORD = 1029,

  /** 1030: The sample rate for the iOS audio device module has changed, which may affect audio quality or compatibility. */
  WARN_ADM_IOS_SAMPLERATE_CHANGE = 1030,

  /** 1031: The recorded audio volume is too low, which may be due to improper settings or hardware issues. */
  WARN_ADM_RECORD_AUDIO_LOWLEVEL = 1031,

  /** 1032: The playback audio volume is too low, which may be due to improper settings or hardware issues. */
  WARN_ADM_PLAYOUT_AUDIO_LOWLEVEL = 1032,

  /** 1040: An exception occurred with the audio driver on Windows, which may require updating or re-enabling the device. */
  WARN_ADM_WINDOWS_NO_DATA_READY_EVENT = 1040,

  /** 1051: Howling or feedback was detected by the audio device module, indicating an acoustic feedback loop. */
  WARN_APM_HOWLING = 1051,

  /** 1052: The audio device module is in a glitch state, possibly due to temporary audio issues. */
  WARN_ADM_GLITCH_STATE = 1052,

  /** 1053: Underlying audio settings have changed, which may affect audio performance or functionality. */
  WARN_ADM_IMPROPER_SETTINGS = 1053,

  /** 1322: No recording device is available in the audio device module on Windows, requiring the user to plug in an audio device. */
  WARN_ADM_WIN_CORE_NO_RECORDING_DEVICE = 1322,

  /** 1323: No playback device is available in the audio device module on Windows, requiring the user to plug in an audio device. */
  WARN_ADM_WIN_CORE_NO_PLAYOUT_DEVICE = 1323,

  /** 1324: The capture device was released improperly by the audio device module, which may require device re-enabling or driver updates. */
  WARN_ADM_WIN_CORE_IMPROPER_CAPTURE_RELEASE = 1324,

  /** 1610: Super-resolution feature warning: The original video dimensions of the remote user exceed the supported limit of 640x480. */
  WARN_SUPER_RESOLUTION_STREAM_OVER_LIMITATION = 1610,

  /** 1611: Super-resolution feature warning: Another user is already using the super-resolution feature. */
  WARN_SUPER_RESOLUTION_USER_COUNT_OVER_LIMITATION = 1611,

  /** 1612: The device is not supported for the super-resolution feature. */
  WARN_SUPER_RESOLUTION_DEVICE_NOT_SUPPORTED = 1612,

  /** 2005: A timeout occurred during the RTM (Real-Time Messaging) login process. */
  WARN_RTM_LOGIN_TIMEOUT = 2005,

  /** 2009: A timeout occurred during the RTM keep-alive process, indicating a potential connectivity issue. */
  WARN_RTM_KEEP_ALIVE_TIMEOUT = 2009,
};

/** Error code.
 */
enum ERROR_CODE_TYPE {
  /** 0: No error occurs. */
  ERR_OK = 0,

  // 1~1000
  /** 1: A general error occurs for an unspecified reason. */
  ERR_FAILED = 1,

  /** 2: An invalid parameter is used. */
  ERR_INVALID_ARGUMENT = 2,

  /** 3: The SDK module is not ready. Solutions include checking the audio device, ensuring the completeness of the application, or re-initializing the RTC engine. */
  ERR_NOT_READY = 3,

  /** 4: The function is not supported by the SDK. */
  ERR_NOT_SUPPORTED = 4,

  /** 5: The request is rejected. */
  ERR_REFUSED = 5,

  /** 6: The buffer size is not large enough to store the returned data. */
  ERR_BUFFER_TOO_SMALL = 6,

  /** 7: The SDK has not been initialized when the method is called. */
  ERR_NOT_INITIALIZED = 7,

  /** 9: No permission is granted. Check if the user has granted access to the audio or video device. */
  ERR_NO_PERMISSION = 9,

  /** 10: An API method timeout occurs because the request takes too long (more than 10 seconds) for the SDK to process. */
  ERR_TIMEDOUT = 10,

  /** 11: The request is canceled. This error is for internal SDK use only and does not return to the application through any method or callback. */
  ERR_CANCELED = 11,

  /** 12: The method is called too frequently. This error is for internal SDK use only and does not return to the application through any method or callback. */
  ERR_TOO_OFTEN = 12,

  /** 13: The SDK fails to bind to the network socket. This error is for internal SDK use only and does not return to the application through any method or callback. */
  ERR_BIND_SOCKET = 13,

  /** 14: The network is unavailable. This error is for internal SDK use only and does not return to the application through any method or callback. */
  ERR_NET_DOWN = 14,

  /** 15: No network buffers are available. This error is for internal SDK use only and does not return to the application through any method or callback. */
  ERR_NET_NOBUFS = 15,

  /** 17: The request to join the channel is rejected, possibly because the user is already in the channel. */
  ERR_JOIN_CHANNEL_REJECTED = 17,

  /** 18: The request to leave the channel is rejected, which may occur if the user has already left the channel or has not joined it. */
  ERR_LEAVE_CHANNEL_REJECTED = 18,

  /** 19: Resources are occupied and cannot be reused. */
  ERR_ALREADY_IN_USE = 19,

  /** 20: The SDK aborts the request due to an excessive number of requests. */
  ERR_ABORTED = 20,

  /** 21: In Windows, specific firewall settings may cause the SDK to fail to initialize and crash. */
  ERR_INIT_NET_ENGINE = 21,

  /** 22: The application uses too much of the system resources, causing the SDK to fail in allocating the required resources. */
  ERR_RESOURCE_LIMITED = 22,

  // ... Continue the pattern for other error codes, ensuring each is clearly explained.

  /** 101: The specified App ID is invalid. Ensure you rejoin the channel with a valid App ID. */
  ERR_INVALID_APP_ID = 101,

  /** 102: The specified channel name is invalid. Ensure you rejoin the channel with a valid channel name. */
  ERR_INVALID_CHANNEL_NAME = 102,

  /**
   * 109: **Deprecated** The token has expired. Use `CONNECTION_CHANGED_TOKEN_EXPIRED(9)` in the `onConnectionStateChanged` callback instead.
   * Deprecated since v2.4.1.
   */
  ERR_TOKEN_EXPIRED = 109,

  /**
   * 110: **Deprecated** The token is invalid. Use `CONNECTION_CHANGED_INVALID_TOKEN(8)` in the `onConnectionStateChanged` callback instead.
   * Deprecated since v2.4.1.
   */
  ERR_INVALID_TOKEN = 110,

  /** 111: The internet connection is interrupted. This error is specific to the Bbrtc Web SDK. */
  ERR_CONNECTION_INTERRUPTED = 111,

  /** 112: The internet connection is lost. This error is specific to the Bbrtc Web SDK. */
  ERR_CONNECTION_LOST = 112,

  /** 113: The user is not in the channel when attempting to call the 'sendStreamMessage' or 'getUserInfoByUserAccount' methods. */
  ERR_NOT_IN_CHANNEL = 113,

  /** 114: The size of the data sent exceeds the limit of 1024 bytes in the 'sendStreamMessage' method. */
  ERR_SIZE_TOO_LARGE = 114,

  /** 115: The bitrate of the sent data in the 'sendStreamMessage' method exceeds the limit of 6 Kbps. */
  ERR_BITRATE_LIMIT = 115,

  /** 116: Too many data streams are created (more than 5 streams) in the 'createDataStream' method. */
  ERR_TOO_MANY_DATA_STREAMS = 116,

  /** 117: The data stream transmission has timed out. */
  ERR_STREAM_MESSAGE_TIMEOUT = 117,

  /** 119: Failed to switch client roles. Consider rejoining the channel to resolve the issue. */
  ERR_SET_CLIENT_ROLE_NOT_AUTHORIZED = 119,

  /** 120: Decryption of the channel has failed. Verify the encryption settings or try rejoining the channel. */
  ERR_DECRYPTION_FAILED = 120,

  /** 123: The client has been banned by the server. */
  ERR_CLIENT_IS_BANNED_BY_SERVER = 123,

  /** 124: Incorrect parameter provided for the watermark file. */
  ERR_WATERMARK_PARAM = 124,

  /** 125: Incorrect file path specified for the watermark. */
  ERR_WATERMARK_PATH = 125,

  /** 126: Incorrect format for the watermark file; ensure it is a valid PNG. */
  ERR_WATERMARK_PNG = 126,

  /** 127: Incorrect information provided for the watermark file. */
  ERR_WATERMARKR_INFO = 127,

  /** 128: Incorrect data format for the watermark file; it should be in ARGB format. */
  ERR_WATERMARK_ARGB = 128,

  /** 129: An error occurred while reading the watermark file. */
  ERR_WATERMARK_READ = 129,

  /** 130: Encryption is enabled when attempting to add a publish stream URL for CDN live streaming, which does not support encrypted streams. */
  ERR_ENCRYPTED_STREAM_NOT_ALLOWED_PUBLISH = 130,

  /** 134: The provided user account is invalid. */
  ERR_INVALID_USER_ACCOUNT = 134,

  /** 151: An error related to CDN occurred. Resolve by removing the original URL and adding a new one using the 'removePublishStreamUrl' and 'addPublishStreamUrl' methods. */
  ERR_PUBLISH_STREAM_CDN_ERROR = 151,

  /** 152: The host has reached the limit of published URLs (more than 10). Remove unnecessary URLs before adding new ones. */
  ERR_PUBLISH_STREAM_NUM_REACH_LIMIT = 152,

  /** 153: The host is attempting to manipulate URLs of other hosts, which is not allowed. Review the application logic. */
  ERR_PUBLISH_STREAM_NOT_AUTHORIZED = 153,

  /** 154: An internal server error occurred in Bbrtc's streaming server. Retry publishing the stream using the 'addPublishStreamUrl' method. */
  ERR_PUBLISH_STREAM_INTERNAL_SERVER_ERROR = 154,

  /** 155: The server could not find the stream. */
  ERR_PUBLISH_STREAM_NOT_FOUND = 155,

  /** 156: The format of the provided RTMP stream URL is not supported. Verify the URL format. */
  ERR_PUBLISH_STREAM_FORMAT_NOT_SUPPORTED = 156,


  // Signaling errors: 400~600
  /** 400: An unspecified error occurred during the logout process. */
  ERR_LOGOUT_OTHER = 400,

  /** 401: The user has logged out. */
  ERR_LOGOUT_USER = 401,

  /** 402: A network failure has caused the user to log out. */
  ERR_LOGOUT_NET = 402,

  /** 403: The user has been logged out due to logging in on another device. */
  ERR_LOGOUT_KICKED = 403,

  /** 404: A packet-related issue has occurred during the logout process. */
  ERR_LOGOUT_PACKET = 404,

  /** 405: The user has been logged out because the token has expired. */
  ERR_LOGOUT_TOKEN_EXPIRED = 405,

  /** 406: The user has been logged out due to using an old version of the application. */
  ERR_LOGOUT_OLDVERSION = 406,

  /** 407: There is an issue with the token provided during the logout process. */
  ERR_LOGOUT_TOKEN_WRONG = 407,

  /** 408: The user was already logged out. */
  ERR_LOGOUT_ALREADY_LOGOUT = 408,

  /** 420: An unspecified error occurred during the login process. */
  ERR_LOGIN_OTHER = 420,

  /** 421: A network failure has occurred during the login process. */
  ERR_LOGIN_NET = 421,

  /** 422: The login attempt has failed. */
  ERR_LOGIN_FAILED = 422,

  /** 423: The login process was canceled. */
  ERR_LOGIN_CANCELED = 423,

  /** 424: The login attempt failed due to an expired token. */
  ERR_LOGIN_TOKEN_EXPIRED = 424,

  /** 425: The login attempt failed due to using an old version of the application. */
  ERR_LOGIN_OLD_VERSION = 425,

  /** 426: There is an issue with the token provided during the login process. */
  ERR_LOGIN_TOKEN_WRONG = 426,

  /** 427: The user was kicked out of the login process due to a token-related issue. */
  ERR_LOGIN_TOKEN_KICKED = 427,

  /** 428: The login attempt failed because the user was already logged in. */
  ERR_LOGIN_ALREADY_LOGIN = 428,

  /** 440: An unspecified error occurred when joining the channel. */
  ERR_JOIN_CHANNEL_OTHER = 440,

  /** 441: A timeout occurred when attempting to send a message. */
  ERR_SEND_MESSAGE_TIMEOUT = 441,

  /** 450: An unspecified error occurred when querying the number of users. */
  ERR_QUERY_USERNUM_OTHER = 450,

  /** 451: A timeout occurred when querying the number of users. */
  ERR_QUERY_USERNUM_TIMEOUT = 451,

  /** 452: An error occurred due to user-related issues when querying the number of users. */
  ERR_QUERY_USERNUM_BYUSER = 452,

  /** 460: An unspecified error occurred when leaving the channel. */
  ERR_LEAVE_CHANNEL_OTHER = 460,

  /** 461: The user was kicked out of the channel. */
  ERR_LEAVE_CHANNEL_KICKED = 461,

  /** 462: The user left the channel. */
  ERR_LEAVE_CHANNEL_BYUSER = 462,

  /** 463: The user was logged out when leaving the channel. */
  ERR_LEAVE_CHANNEL_LOGOUT = 463,

  /** 464: The user was disconnected when leaving the channel. */
  ERR_LEAVE_CHANNEL_DISCONNECTED = 464,

  /** 470: An unspecified error occurred during the invitation process. */
  ERR_INVITE_OTHER = 470,

  /** 471: The user was re-invited, which is not allowed. */
  ERR_INVITE_REINVITE = 471,

  /** 472: A network failure occurred during the invitation process. */
  ERR_INVITE_NET = 472,

  /** 473: The invitee is offline and could not receive the invitation. */
  ERR_INVITE_PEER_OFFLINE = 473,

  /** 474: A timeout occurred during the invitation process. */
  ERR_INVITE_TIMEOUT = 474,

  /** 475: The invitation could not be received by the invitee. */
  ERR_INVITE_CANT_RECV = 475,

  // Media engine errors: 1001~2000
  /** 1001: The media engine failed to load. */
  ERR_LOAD_MEDIA_ENGINE = 1001,


  // Media engine and audio device module errors: 1002~1201
  /** 1002: The call fails to start even after the media engine is enabled. */
  ERR_START_CALL = 1002,

  /**
   * 1003: **Deprecated** Fails to start the camera.
   * Deprecated as of v2.4.1. Use `LOCAL_VIDEO_STREAM_ERROR_CAPTURE_FAILURE(4)` in the `onConnectionStateChanged` callback instead.
   */
  ERR_START_CAMERA = 1003,

  /** 1004: The video rendering module fails to start. */
  ERR_START_VIDEO_RENDER = 1004,

  /** 1005: A general error occurs in the Audio Device Module for an unspecified reason. */
  ERR_ADM_GENERAL_ERROR = 1005,

  /** 1006: An error occurs in using the Java resources within the Audio Device Module. */
  ERR_ADM_JAVA_RESOURCE = 1006,

  /** 1007: An error occurs in setting the sampling frequency in the Audio Device Module. */
  ERR_ADM_SAMPLE_RATE = 1007,

  /** 1008: An error occurs in initializing the playback device in the Audio Device Module. */
  ERR_ADM_INIT_PLAYOUT = 1008,

  /** 1009: An error occurs in starting the playback device in the Audio Device Module. */
  ERR_ADM_START_PLAYOUT = 1009,

  /** 1010: An error occurs in stopping the playback device in the Audio Device Module. */
  ERR_ADM_STOP_PLAYOUT = 1010,

  /** 1011: An error occurs in initializing the recording device in the Audio Device Module. */
  ERR_ADM_INIT_RECORDING = 1011,

  /** 1012: An error occurs in starting the recording device in the Audio Device Module. */
  ERR_ADM_START_RECORDING = 1012,

  /** 1013: An error occurs in stopping the recording device in the Audio Device Module. */
  ERR_ADM_STOP_RECORDING = 1013,

  /** 1015: A runtime playback error occurs in the Audio Device Module. */
  ERR_ADM_RUNTIME_PLAYOUT_ERROR = 1015,

  /** 1017: A runtime recording error occurs in the Audio Device Module. */
  ERR_ADM_RUNTIME_RECORDING_ERROR = 1017,

  /** 1018: The Audio Device Module fails to record. */
  ERR_ADM_RECORD_AUDIO_FAILED = 1018,

  /** 1022: An error occurs in initializing the loopback device in the Audio Device Module. */
  ERR_ADM_INIT_LOOPBACK = 1022,

  /** 1023: An error occurs in starting the loopback device in the Audio Device Module. */
  ERR_ADM_START_LOOPBACK = 1023,

  /** 1027: No recording permission exists in the Audio Device Module. */
  ERR_ADM_NO_PERMISSION = 1027,

  /** 1033: The device is occupied in the Audio Device Module. */
  ERR_ADM_RECORD_AUDIO_IS_ACTIVE = 1033,

  /** 1101: A fatal exception occurs in the Audio Device Module on Android. */
  ERR_ADM_ANDROID_JNI_JAVA_RESOURCE = 1101,

  /** 1108: The recording frequency is lower than 50 in the Audio Device Module on Android. */
  ERR_ADM_ANDROID_JNI_NO_RECORD_FREQUENCY = 1108,

  /** 1109: The playback frequency is lower than 50 in the Audio Device Module on Android. */
  ERR_ADM_ANDROID_JNI_NO_PLAYBACK_FREQUENCY = 1109,

  /** 1111: AudioRecord fails to start up in the Audio Device Module on Android. */
  ERR_ADM_ANDROID_JNI_JAVA_START_RECORD = 1111,

  /** 1112: AudioTrack fails to start up in the Audio Device Module on Android. */
  ERR_ADM_ANDROID_JNI_JAVA_START_PLAYBACK = 1112,

  /** 1115: AudioRecord returns an error in the Audio Device Module on Android. */
  ERR_ADM_ANDROID_JNI_JAVA_RECORD_ERROR = 1115,

  /**
   * 1151: **Deprecated** Error related to creating the OpenSL engine in the Audio Device Module on Android.
   */
  ERR_ADM_ANDROID_OPENSL_CREATE_ENGINE = 1151,

  /**
   * 1153: **Deprecated** Error related to creating the audio recorder with OpenSL in the Audio Device Module on Android.
   */
  ERR_ADM_ANDROID_OPENSL_CREATE_AUDIO_RECORDER = 1153,

  /**
   * 1156: **Deprecated** Error starting the recorder thread with OpenSL in the Audio Device Module on Android.
   */
  ERR_ADM_ANDROID_OPENSL_START_RECORDER_THREAD = 1156,

  /**
   * 1157: **Deprecated** Error related to creating the audio player with OpenSL in the Audio Device Module on Android.
   */
  ERR_ADM_ANDROID_OPENSL_CREATE_AUDIO_PLAYER = 1157,

  /**
   * 1160: **Deprecated** Error starting the player thread with OpenSL in the Audio Device Module on Android.
   */
  ERR_ADM_ANDROID_OPENSL_START_PLAYER_THREAD = 1160,

  /** 1201: The current device does not support audio input in the Audio Device Module on iOS. */
  ERR_ADM_IOS_INPUT_NOT_AVAILABLE = 1201,

  // Audio Device Module errors on iOS: 1206~1221
  /** 1206: Audio device module on iOS: Cannot activate the Audio Session. */
  ERR_ADM_IOS_ACTIVATE_SESSION_FAIL = 1206,
  /** 1210: Audio device module on iOS: Fails to initialize the audio device, often due to incorrect audio device parameters. */
  ERR_ADM_IOS_VPIO_INIT_FAIL = 1210,
  /** 1213: Audio device module on iOS: Fails to re-initialize the audio device, often due to incorrect audio device parameters. */
  ERR_ADM_IOS_VPIO_REINIT_FAIL = 1213,
  /** 1214: Audio device module on iOS: Fails to restart the Audio Unit, possibly due to incompatible audio session category settings. */
  ERR_ADM_IOS_VPIO_RESTART_FAIL = 1214,
  /** 1219: Audio device module on iOS: Fails to set the render callback. */
  ERR_ADM_IOS_SET_RENDER_CALLBACK_FAIL = 1219,
  /**
   * 1221: **Deprecated** Audio device module on iOS: The audio session sample rate is zero.
   * Deprecated as of v2.4.1.
   */
  ERR_ADM_IOS_SESSION_SAMPLERATR_ZERO = 1221,

  // Audio Device Module errors on Windows: 1301~1360
  /** 1301: Audio device module on Windows: An audio driver abnormality or compatibility issue occurs. */
  ERR_ADM_WIN_CORE_INIT = 1301,
  /** 1303: Audio device module on Windows: A recording driver abnormality or compatibility issue occurs. */
  ERR_ADM_WIN_CORE_INIT_RECORDING = 1303,
  /** 1306: Audio device module on Windows: A playout driver abnormality or compatibility issue occurs. */
  ERR_ADM_WIN_CORE_INIT_PLAYOUT = 1306,
  /** 1307: Audio device module on Windows: No audio device is available. */
  ERR_ADM_WIN_CORE_INIT_PLAYOUT_NULL = 1307,
  /** 1309: Audio device module on Windows: An audio driver abnormality or compatibility issue occurs during recording. */
  ERR_ADM_WIN_CORE_START_RECORDING = 1309,
  /** 1311: Audio device module on Windows: Insufficient system memory or poor device performance. */
  ERR_ADM_WIN_CORE_CREATE_REC_THREAD = 1311,
  /** 1314: Audio device module on Windows: An audio driver abnormality occurs during capture. */
  ERR_ADM_WIN_CORE_CAPTURE_NOT_STARTUP = 1314,
  /** 1319: Audio device module on Windows: Insufficient system memory or poor device performance during rendering. */
  ERR_ADM_WIN_CORE_CREATE_RENDER_THREAD = 1319,
  /** 1320: Audio device module on Windows: An audio driver abnormality occurs during rendering. */
  ERR_ADM_WIN_CORE_RENDER_NOT_STARTUP = 1320,
  /** 1322: Audio device module on Windows: No recording device is available. */
  ERR_ADM_WIN_CORE_NO_RECORDING_DEVICE = 1322,
  /** 1323: Audio device module on Windows: No playback device is available. */
  ERR_ADM_WIN_CORE_NO_PLAYOUT_DEVICE = 1323,
  /** 1351: Audio device module on Windows: An audio driver abnormality or compatibility issue occurs with Wave initialization. */
  ERR_ADM_WIN_WAVE_INIT = 1351,
  /** 1353: Audio device module on Windows: An audio driver abnormality occurs with Wave recording initialization. */
  ERR_ADM_WIN_WAVE_INIT_RECORDING = 1353,
  /** 1354: Audio device module on Windows: An audio driver abnormality occurs with Wave microphone initialization. */
  ERR_ADM_WIN_WAVE_INIT_MICROPHONE = 1354,
  /** 1355: Audio device module on Windows: An audio driver abnormality occurs with Wave playout initialization. */
  ERR_ADM_WIN_WAVE_INIT_PLAYOUT = 1355,
  /** 1356: Audio device module on Windows: An audio driver abnormality occurs with Wave speaker initialization. */
  ERR_ADM_WIN_WAVE_INIT_SPEAKER = 1356,
  /** 1357: Audio device module on Windows: An audio driver abnormality occurs when starting Wave recording. */
  ERR_ADM_WIN_WAVE_START_RECORDING = 1357,
  /** 1358: Audio device module on Windows: An audio driver abnormality occurs when starting Wave playout. */
  ERR_ADM_WIN_WAVE_START_PLAYOUT = 1358,
  /** 1359: Audio device module: No recording device is available. */
  ERR_ADM_NO_RECORDING_DEVICE = 1359,
  /** 1360: Audio device module: No playback device is available. */
  ERR_ADM_NO_PLAYOUT_DEVICE = 1360,

  // Video Device Module errors: 1500~1502
  /** 1501: Video device module: The camera is unauthorized for use. */
  ERR_VDM_CAMERA_NOT_AUTHORIZED = 1501,
  /**
   * 1502: **Deprecated** Video device module: The camera is in use.
   * Deprecated as of v2.4.1. Use `LOCAL_VIDEO_STREAM_ERROR_DEVICE_BUSY(3)` in the `onConnectionStateChanged` callback instead.
   */
  ERR_VDM_WIN_DEVICE_IN_USE = 1502,

  // Video Coding Module errors: 1600~1604
  /** 1600: Video coding module: An unknown error occurs. */
  ERR_VCM_UNKNOWN_ERROR = 1600,
  /** 1601: Video coding module: An error occurs in initializing the video encoder. */
  ERR_VCM_ENCODER_INIT_ERROR = 1601,
  /** 1602: Video coding module: An error occurs during video encoding. */
  ERR_VCM_ENCODER_ENCODE_ERROR = 1602,
  /** 1603: Video coding module: An error occurs in setting the video encoder. */
  ERR_VCM_ENCODER_SET_ERROR = 1603,
  /** 1604: An error occurs when attempting to set the chorus role in the channel. */
  ERR_SET_CHORUS_ROLE_ERROR = 1604,
};

/**
 * Defines the log filter levels for outputting log information.
 */
enum LOG_FILTER_TYPE {
  /** 0: No log information is output. */
  LOG_FILTER_OFF = 0,

  /** 0x080f: Outputs all levels of log information.
   * Set this level if you require the most comprehensive logging for debugging purposes.
   */
  LOG_FILTER_DEBUG = 0x080f,

  /** 0x000f: Outputs log information at the CRITICAL, ERROR, WARNING, and INFO levels.
   * This is the recommended setting for general use to balance log detail with volume.
   */
  LOG_FILTER_INFO = 0x000f,

  /** 0x000e: Outputs log information at the CRITICAL, ERROR, and WARNING levels. */
  LOG_FILTER_WARN = 0x000e,

  /** 0x000c: Outputs only CRITICAL and ERROR level log information. */
  LOG_FILTER_ERROR = 0x000c,

  /** 0x0008: Outputs CRITICAL level log information only. */
  LOG_FILTER_CRITICAL = 0x0008,

  /** 0x80f: A bitmask that can be used to filter or manipulate log levels. */
  LOG_FILTER_MASK = 0x80f,
};
}  // namespace bbrtc

#endif /* BBRtcBase_h */
