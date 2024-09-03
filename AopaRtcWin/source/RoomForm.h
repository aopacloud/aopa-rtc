#pragma once
#include "MusicForm.h"
#include "item.h"
#include "CustomVideoSource.h"

class RoomForm :
	public ui::WindowImplBase,
	public MusicSelectSink,
    public bbrtc::IRtcEngineEventHandler,
    public ItemSink
{
 public:
  RoomForm(const std::wstring& class_name,
           const std::wstring& theme_directory,
           const std::wstring& layout_xml);
  ~RoomForm();

  virtual std::wstring GetSkinFolder() override;
  virtual std::wstring GetSkinFile() override;
  virtual std::wstring GetWindowClassName() const override;
  virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
  virtual void InitWindow() override;
  virtual LRESULT OnClose(UINT uMsg,
                          WPARAM wParam,
                          LPARAM lParam,
                          BOOL& bHandled);
  void OnMusicSelectFiles(const std::wstring& path,
                          const std::vector<std::wstring>& vecFiles,
                          int playIndex = -1) override;
  void onItemVolumeChange(uint32_t userId, int volume) override;
  void onItemAudioMuteSateChange(uint32_t userId, bool mute) override;
  void onItemVideoMuteSateChange(uint32_t userId, bool mute) override;
  void onItemCreateFinish(uint32_t userId, HWND hWnd) override;
  void onItemVideoStreamChange(uint32_t userId, bool streamType) override;

  void onWarning(int warn, const char* msg) override;
  void onError(int err, const char* msg) override;
  void onJoinChannelSuccess(const char* channel, bbrtc::uid_t uid, int elapsed) override;
  void onRejoinChannelSuccess(const char* channel, bbrtc::uid_t uid, int elapsed) override;
  void onLeaveChannel(const bbrtc::RtcStats& stats) override;
  void onClientRoleChanged(bbrtc::CLIENT_ROLE_TYPE oldRole, bbrtc::CLIENT_ROLE_TYPE newRole) override;
  void onUserJoined(bbrtc::uid_t uid, int elapsed) override;
  void onUserOffline(bbrtc::uid_t uid, bbrtc::USER_OFFLINE_REASON_TYPE reason) override;
  void onRemoteAudioStateChanged(bbrtc::uid_t uid, bbrtc::REMOTE_AUDIO_STATE state, bbrtc::REMOTE_AUDIO_STATE_REASON reason, int elapsed) override;
  void onAudioVolumeIndication(const bbrtc::AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume)override;
  void onAudioMixingFinished() override;
  void onAudioMixingStateChanged(bbrtc::AUDIO_MIXING_STATE_TYPE state, bbrtc::AUDIO_MIXING_REASON_TYPE errorCode)override;
  void onConnectionStateChanged(bbrtc::CONNECTION_STATE_TYPE state, bbrtc::CONNECTION_CHANGED_REASON_TYPE reason)override;
  void onChannelMediaRelayStateChanged(bbrtc::CHANNEL_MEDIA_RELAY_STATE state, bbrtc::CHANNEL_MEDIA_RELAY_ERROR code) override;
  void onChannelMediaRelayEvent(bbrtc::CHANNEL_MEDIA_RELAY_EVENT code)override;
public:
  static void ShowCustomWindow(const std::wstring& class_name,
                               const std::wstring& theme_directory,
                               const std::wstring& layout_xml);

private:
  void joinRoom();
  void startPlayMusic();
  void stopPlayMusic();
  void addUserItem(uint32_t userId);
  void removeUserItem(uint32_t userId);
  Item* getItem(uint32_t userId);
  void readMusicPostion();
  void startRelayMedia();
  void stopRelayMedia();

  void enableButton(bool enable);
private:
  std::wstring class_name_;
  std::wstring theme_directory_;
  std::wstring layout_xml_;
  std::vector<std::wstring> vecMusicFiles_;
  std::wstring musicDirectory_;
  int currentPlayIndex_ = 0;
  enum MusicMode {
    music_loop,
    music_random,
    music_repetition,
  } music_play_mode_ = music_loop;
  bbrtc::IRtcEngine* rtcEngine_;
  
  bool videoSubscribe_ = true;
  bool audioSubscribe_ = true;
  bool isJoined_ = false;
  bool videoOpen_ = true;
  bool audioOpen_ = true;
  bool musicPlaying_ = false;
  bool musicPaused_ = false;
  std::string musicPath_;

  ui::ListBox* usersList_;
  ui::Label* stateLabel_;
  ui::Button* vadBnt_;
  ui::Label* musicTimeLabel_;
  ui::Label* musicTotalTimeLabel_;
  ui::Slider* musicSlider_;
  ui::Button* relayMediaBnt_;
  int64_t musicTotalTimeMs_ = 0;
  bool relayState_ = false;
 public:
  std::string roomId_;
  int roleType_;
  int audioQuality_;
  uint32_t userId_;
  std::string token_;

  CustomVideoSource video_source_;
};
