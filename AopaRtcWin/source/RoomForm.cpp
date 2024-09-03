#include "stdafx.h"
#include "RoomForm.h"
#include "AppRtcWindow.h"
#include "item.h"
#include "RelayForm.h"
#include "LoginForm.h"

RoomForm::RoomForm(const std::wstring& class_name,
	const std::wstring& theme_directory,
	const std::wstring& layout_xml)
	: class_name_(class_name),
	theme_directory_(theme_directory),
	layout_xml_(layout_xml) {
	rtcEngine_ = MainThread::getRtcEngine();
}

RoomForm::~RoomForm() {}

std::wstring RoomForm::GetSkinFolder() {
	return theme_directory_;
}

std::wstring RoomForm::GetSkinFile() {
	return layout_xml_;
}

std::wstring RoomForm::GetWindowClassName() const {
	return class_name_;
}

LRESULT RoomForm::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (uMsg == WM_MSG_RELAY_RORM_CLOSE){
		startRelayMedia();
		return 0;
	}
	return ui::WindowImplBase::HandleMessage(uMsg, wParam, lParam);
}

void RoomForm::InitWindow() {
	stateLabel_ = dynamic_cast<ui::Label*>(FindControl(L"rtc_state_label"));
	vadBnt_ = dynamic_cast<ui::Button*>(FindControl(L"vad_button"));
	musicTimeLabel_ = dynamic_cast<ui::Label*>(FindControl(L"play_music_start_label")); 
	musicTotalTimeLabel_ = dynamic_cast<ui::Label*>(FindControl(L"play_music_end_label"));
	musicSlider_ = dynamic_cast<ui::Slider*>(FindControl(L"music_play_slider"));
	usersList_ = dynamic_cast<ui::ListBox*>(FindControl(L"user_list"));
    if (usersList_)
		usersList_->SetVerScrollUnitPixels(100);
	ui::Label* roomLable =  dynamic_cast<ui::Label*>(FindControl(L"room_label"));
	roomLable->SetText(nbase::UTF8ToUTF16(roomId_.c_str()));
	ui::Button* audioSwitchBtn = dynamic_cast<ui::Button*>(FindControl(L"audio_switch_bnt"));
	audioSwitchBtn->AttachClick([this, audioSwitchBtn](ui::EventArgs* args) {
		if (roleType_ == 2) {
			::MessageBox(NULL, L"please change audio state", L"notify", MB_OKCANCEL);
			return true;
		}
		if (audioOpen_) {
			rtcEngine_->muteLocalAudioStream(true);
			audioSwitchBtn->SetText(L"send local voice");
		}
		else {
			rtcEngine_->muteLocalAudioStream(false);
			audioSwitchBtn->SetText(L"not send");
		}
		audioOpen_ = !audioOpen_;
		return true;
	});

	ui::Button* videoSwitchBtn =
		dynamic_cast<ui::Button*>(FindControl(L"video_switch_bnt"));
	videoSwitchBtn->AttachClick([this, videoSwitchBtn](ui::EventArgs* args) {
		if (roleType_ == 2) {
			::MessageBox(NULL, L"please change audio state", L"notify", MB_OKCANCEL);
			return true;
		}
		if (videoOpen_) {
			rtcEngine_->enableLocalVideo(false);
			rtcEngine_->stopPreview();
			videoSwitchBtn->SetText(L"open video");
		}
		else {
			rtcEngine_->enableLocalVideo(true);
			rtcEngine_->startPreview();
			videoSwitchBtn->SetText(L"close video");
		}
		videoOpen_ = !videoOpen_;
		return true;
	});

	ui::Button* roleBtn = dynamic_cast<ui::Button*>(FindControl(L"role_bnt"));
	roleBtn->AttachClick([this, roleBtn, audioSwitchBtn, videoSwitchBtn](ui::EventArgs* args) {
		if (roleType_ == 1) {
			roleType_ = 2;
			audioOpen_ = false;
			videoOpen_ = false;
			rtcEngine_->stopPreview();
			rtcEngine_->enableLocalVideo(false);
			rtcEngine_->setClientRole(bbrtc::CLIENT_ROLE_AUDIENCE);
			roleBtn->SetText(L"on mic");
			audioSwitchBtn->SetText(L"open audio");
			videoSwitchBtn->SetText(L"open video");
			stopPlayMusic();
            enableButton(false);
		}
		else {
			roleType_ = 1;
            audioOpen_ = true;
            videoOpen_ = true;
            rtcEngine_->startPreview();
            rtcEngine_->enableLocalVideo(true);
			rtcEngine_->setClientRole(bbrtc::CLIENT_ROLE_BROADCASTER);
			roleBtn->SetText(L"down mic");
			audioSwitchBtn->SetText(L"close audio");
            videoSwitchBtn->SetText(L"close video");
            enableButton(true);
		}
		return true;
	});

	ui::Button* exitBtn = dynamic_cast<ui::Button*>(FindControl(L"exit_bnt"));
	exitBtn->AttachClick([this](ui::EventArgs* args) {
		Close();
		return true;
	});

	ui::Button* musicSelectBtn =
		dynamic_cast<ui::Button*>(FindControl(L"music_select_bnt"));
	musicSelectBtn->AttachClick([this](ui::EventArgs* args) {
		MusicForm* form =
			MusicForm::ShowCustomWindow(L"music", L"rtc", L"music.xml");
		form->setSink(this);
		form->setPath(musicDirectory_, vecMusicFiles_, currentPlayIndex_);
		return true;
	});

	ui::Button* musicPlayModeBtn =
		dynamic_cast<ui::Button*>(FindControl(L"music_play_mode_bnt"));
	musicPlayModeBtn->AttachClick([this, musicPlayModeBtn](ui::EventArgs* args) {
		music_play_mode_ = (MusicMode)((music_play_mode_ + 1) % 3);
		if (music_play_mode_ == music_loop) {
			musicPlayModeBtn->SetText(L"loop");
		}
		else if (music_play_mode_ == music_random) {
			musicPlayModeBtn->SetText(L"random");
		}
		else if (music_play_mode_ == music_repetition) {
			musicPlayModeBtn->SetText(L"repeat");
		}
		return true;
	});

	ui::RichEdit* musicNameEdit = dynamic_cast<ui::RichEdit*>(FindControl(L"play_music_name_edit"));
	musicNameEdit->SetText(L"https://xs-voice.oss-cn-hangzhou.aliyuncs.com/upload/music/de29ca47f33a997ac6ecf8bdcff1a095.mp3");
	ui::Button* musicPlayBtn =
		dynamic_cast<ui::Button*>(FindControl(L"music_play_bnt"));
	musicPlayBtn->AttachClick([this, musicNameEdit](ui::EventArgs* args) {
		if (musicPlaying_) {
			stopPlayMusic();
		}
		else {
			musicPath_ = nbase::UTF16ToUTF8(musicNameEdit->GetText());
			startPlayMusic();
		}
		return true;
	});

	ui::Button* musicPauseBtn =
		dynamic_cast<ui::Button*>(FindControl(L"music_pause_bnt"));
	musicPauseBtn->AttachClick([this, musicPauseBtn](ui::EventArgs* args) {
		if (!musicPlaying_)
			return true;
		if (!musicPaused_) {
			rtcEngine_->pauseAudioMixing();
			musicPauseBtn->SetText(L"resume");
		}
		else {
			rtcEngine_->resumeAudioMixing();
			musicPauseBtn->SetText(L"pause");
		}
		musicPaused_ = !musicPaused_;
		return true; });

	ui::Label* recordVolumeLabel = dynamic_cast<ui::Label*>(FindControl(L"record_volume_value_label"));
	ui::Slider* recordVolumeSlider = dynamic_cast<ui::Slider*>(FindControl(L"record_volume_slider"));
	recordVolumeSlider->AttachValueChange([this, recordVolumeSlider, recordVolumeLabel](ui::EventArgs* args) {
		int value = recordVolumeSlider->GetValue();
		recordVolumeLabel->SetText(nbase::StringPrintf(L"%d", value));
		rtcEngine_->adjustRecordingSignalVolume(value);
		return true;
	});
	ui::Label* playoutVolumeLabel = dynamic_cast<ui::Label*>(FindControl(L"play_volume_value_label"));
	ui::Slider* playoutVolumeSlider = dynamic_cast<ui::Slider*>(FindControl(L"play_volume_slider"));
	playoutVolumeSlider->AttachValueChange([this, playoutVolumeSlider, playoutVolumeLabel](ui::EventArgs* args) {
		int value = playoutVolumeSlider->GetValue();
		playoutVolumeLabel->SetText(nbase::StringPrintf(L"%d", value));
		rtcEngine_->adjustPlaybackSignalVolume(value);
		return true;
	});
	ui::Label* musicVolumeLabel = dynamic_cast<ui::Label*>(FindControl(L"music_volume_value_label"));
	ui::Slider* musicVolumeSlider = dynamic_cast<ui::Slider*>(FindControl(L"music_volume_slider"));
	musicVolumeSlider->AttachValueChange([this, musicVolumeSlider, musicVolumeLabel](ui::EventArgs* args) {
		int value = musicVolumeSlider->GetValue();
		musicVolumeLabel->SetText(nbase::StringPrintf(L"%d", value));
		rtcEngine_->adjustAudioMixingVolume(value);
		return true;
	});

	ui::Label* musicProgressLabel = dynamic_cast<ui::Label*>(FindControl(L"play_music_start_label"));
	ui::Slider* musicProgressSlider = dynamic_cast<ui::Slider*>(FindControl(L"music_play_slider"));
	musicProgressSlider->AttachValueChange([this, musicProgressSlider, musicProgressLabel](ui::EventArgs* args) {
		int value = musicProgressSlider->GetValue();
		musicProgressLabel->SetText(nbase::StringPrintf(L"%02d:%02d", value / 1000 / 60, value / 1000 % 60));
		rtcEngine_->setAudioMixingPosition(value * 1000);
		return true;
	});
	relayMediaBnt_ = dynamic_cast<ui::Button*>(FindControl(L"relay_media_bnt"));
	relayMediaBnt_->AttachClick([this](ui::EventArgs* args) {
		if (!relayState_) {
			RelayForm::ShowCustomWindow(L"Relay", L"rtc", L"relay.xml", this->GetHWND());
		}
		else {
			stopRelayMedia();
		}
		return true;
	});

    ui::Button* videoSubscribeBtn =
        dynamic_cast<ui::Button*>(FindControl(L"video_subscribe_btn"));
    videoSubscribeBtn->AttachClick([this, videoSubscribeBtn](ui::EventArgs* args) {
        if (videoSubscribe_) {
            rtcEngine_->muteAllRemoteVideoStreams(true);
            videoSubscribeBtn->SetText(L"sub video");
        }
        else {
            rtcEngine_->muteAllRemoteVideoStreams(false);
            videoSubscribeBtn->SetText(L"cancel sub video");
        }
        videoSubscribe_ = !videoSubscribe_;
        return true;
    });
    ui::Button* audioSubscribeBtn =
        dynamic_cast<ui::Button*>(FindControl(L"audio_subscribe_btn"));
    audioSubscribeBtn->AttachClick([this, audioSubscribeBtn](ui::EventArgs* args) {
        if (audioSubscribe_) {
           rtcEngine_->muteAllRemoteAudioStreams(true);
            audioSubscribeBtn->SetText(L"sub audio");
        }
        else {
           rtcEngine_->muteAllRemoteAudioStreams(false);
            audioSubscribeBtn->SetText(L"cancel sub audio");
        }
        audioSubscribe_ = !audioSubscribe_;
        return true;
    });

	joinRoom();
}

LRESULT RoomForm::OnClose(UINT uMsg,
	WPARAM wParam,
	LPARAM lParam,
	BOOL& bHandled) {
	stopPlayMusic();
	rtcEngine_->stopPreview();
	rtcEngine_->leaveChannel();
	rtcEngine_->unregisterEventHandler(this);
	LoginForm::ShowCustomWindow(L"login", L"rtc", L"login.xml");
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}

void RoomForm::ShowCustomWindow(const std::wstring& class_name,
	const std::wstring& theme_directory,
	const std::wstring& layout_xml) {
	RoomForm* window = new RoomForm(class_name, theme_directory, layout_xml);
	window->Create(NULL, class_name.c_str(),
		WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 0);
	window->CenterWindow();
	window->ShowWindow();
}

void RoomForm::startRelayMedia() {
	if (RelayForm::relay_room_name_.empty()) {
		return;
	}
	bbrtc::ChannelMediaRelayConfiguration config;
	bbrtc::ChannelMediaInfo src_info;
	src_info.channelName = roomId_.c_str();
	src_info.uid = 0;
	src_info.token = nullptr;
	config.srcInfo = &src_info;
	bbrtc::ChannelMediaInfo dst_info;
	dst_info.channelName = RelayForm::relay_room_name_.c_str();
	dst_info.uid = userId_;
	dst_info.token = nullptr;
	config.destInfos = &dst_info;
	config.destCount = 1;
	rtcEngine_->startChannelMediaRelay(config);
}
void RoomForm::stopRelayMedia() {
	rtcEngine_->stopChannelMediaRelay();
	relayState_ = false;
	relayMediaBnt_->SetText(L"start relay");
}

void RoomForm::OnMusicSelectFiles(const std::wstring& path,
	const std::vector<std::wstring>& vecFiles,
	int playIndex) {
	if (vecFiles.empty())
		return;
	if (playIndex == -1)
		playIndex = 0;
	musicDirectory_ = path;
	vecMusicFiles_.assign(vecFiles.begin(), vecFiles.end());
	if (playIndex != -1) {
		currentPlayIndex_ = playIndex;
		musicPath_ = nbase::UTF16ToUTF8(vecFiles[playIndex]);
		ui::RichEdit* musicNameEdit = dynamic_cast<ui::RichEdit*>(FindControl(L"play_music_name_edit"));
		musicNameEdit->SetText(vecFiles[playIndex]);
		startPlayMusic();
	}
}



void RoomForm::joinRoom() {
	rtcEngine_->registerEventHandler(this);
	rtcEngine_->enableAudio();
	rtcEngine_->enableVideo();
	rtcEngine_->enableLocalAudio(true);
	rtcEngine_->enableLocalVideo(false);
	rtcEngine_->setClientRole((bbrtc::CLIENT_ROLE_TYPE)roleType_);
	rtcEngine_->setChannelProfile(bbrtc::CHANNEL_PROFILE_LIVE_BROADCASTING);
	rtcEngine_->setAudioProfile((bbrtc::AUDIO_PROFILE_TYPE)audioQuality_,
		bbrtc::AUDIO_SCENARIO_SHOWROOM);
	rtcEngine_->enableDualStreamMode(false);
	bbrtc::VideoEncoderConfiguration config_;
	config_.dimensions.width = 640;
	config_.dimensions.height = 480;
	config_.frameRate = (bbrtc::FRAME_RATE)15;
	config_.minFrameRate = 5;
	config_.bitrate = 600;
	config_.minBitrate = 300;
	config_.mirrorMode = bbrtc::VIDEO_MIRROR_MODE_AUTO;
	config_.degradationPreference = bbrtc::MAINTAIN_QUALITY;
	rtcEngine_->setVideoEncoderConfiguration(config_);
	rtcEngine_->setParameters("{\"che.network.enable.quic\":false}");
	rtcEngine_->joinChannel(token_.c_str(), roomId_.c_str(), "", userId_);
	rtcEngine_->enableAudioVolumeIndication(500, 3, true);
	ui::Button* roleBtn = dynamic_cast<ui::Button*>(FindControl(L"role_bnt"));
	if (roleType_ == 1) {
		roleBtn->SetText(L"down mic");
		audioOpen_ = true;
	}
	else {
		roleBtn->SetText(L"up mic");
		audioOpen_ = false;
        enableButton(false);
	}
	addUserItem(userId_);

}

void RoomForm::startPlayMusic() {
	if (musicPath_.empty() || roleType_ == 2 || !isJoined_)
		return;
	if (musicPlaying_)
		stopPlayMusic();

	if (rtcEngine_->startAudioMixing(musicPath_.c_str(), false, true, -1) != 0) {
		::MessageBox(NULL, L"open music file failed!", L"notify", MB_OKCANCEL);
		return;
	}

	musicPlaying_ = true;
	musicPaused_ = false;
	ui::Button* palyBnt = dynamic_cast<ui::Button*>(FindControl(L"music_play_bnt"));
	ui::Button* pauseBnt = dynamic_cast<ui::Button*>(FindControl(L"music_pause_bnt"));
	ui::Slider* slider = dynamic_cast<ui::Slider*>(FindControl(L"music_play_slider"));
	ui::Label* startLabel = dynamic_cast<ui::Label*>(FindControl(L"play_music_start_label"));
	ui::Label* endLabel = dynamic_cast<ui::Label*>(FindControl(L"play_music_end_label"));

	palyBnt->SetText(L"stop");
	pauseBnt->SetText(L"pause");
	startLabel->SetText(L"00:00");
	endLabel->SetText(L"00:00");
}

void RoomForm::stopPlayMusic() {
	if (!musicPlaying_)
		return;
	musicPlaying_ = false;
	musicPaused_ = false;
	rtcEngine_->stopAudioMixing();
	ui::Button* palyBnt = dynamic_cast<ui::Button*>(FindControl(L"music_play_bnt"));
	ui::Button* pauseBnt = dynamic_cast<ui::Button*>(FindControl(L"music_pause_bnt"));
	ui::Slider* slider = dynamic_cast<ui::Slider*>(FindControl(L"music_play_slider"));
	ui::Label* startLabel = dynamic_cast<ui::Label*>(FindControl(L"play_music_start_label"));
	ui::Label* endLabel = dynamic_cast<ui::Label*>(FindControl(L"play_music_end_label"));

	palyBnt->SetText(L"play");
	pauseBnt->SetText(L"pause");
	slider->SetValue(0);
	startLabel->SetText(L"00:00");
	endLabel->SetText(L"00:00");
}

void RoomForm::enableButton(bool enable) {
    ui::Button* audioSwitchBtn = dynamic_cast<ui::Button*>(FindControl(L"audio_switch_bnt"));
    audioSwitchBtn->SetEnabled(enable);

    ui::Button* videoSwitchBtn = dynamic_cast<ui::Button*>(FindControl(L"video_switch_bnt"));
    videoSwitchBtn->SetEnabled(enable);

    ui::Button* videoSubscribeBtn = dynamic_cast<ui::Button*>(FindControl(L"video_subscribe_btn"));
    videoSubscribeBtn->SetEnabled(enable);

    ui::Button* audioSubscribeBtn = dynamic_cast<ui::Button*>(FindControl(L"audio_subscribe_btn"));
    audioSubscribeBtn->SetEnabled(enable);

    relayMediaBnt_->SetEnabled(enable);
}

void RoomForm::addUserItem(uint32_t userId) {
  if (usersList_) {
    int count = usersList_->GetCount();
    for (int i = 0; i < count; ++i) {
      Item* item = (Item*)usersList_->GetItemAt(i);
      if (item->getUserId() == userId) {
        return;
      }
    }
    Item* item = new Item;
    ui::GlobalManager::FillBoxWithCache(item, L"rtc/item.xml");
    item->setSink(this);
    item->InitSubControls(userId);
    usersList_->Add(item);
  }
}
void RoomForm::removeUserItem(uint32_t userId) {
  if (usersList_) {
    int count = usersList_->GetCount();
    for (int i = 0; i < count; ++i) {
      Item* item = (Item*)usersList_->GetItemAt(i);
      if (item->getUserId() == userId) {
        usersList_->RemoveAt(i);
        break;
      }
    }
  }
}
Item* RoomForm::getItem(uint32_t userId) {
  if (usersList_) {
    int count = usersList_->GetCount();
    for (int i = 0; i < count; ++i) {
      Item* item = (Item*)usersList_->GetItemAt(i);
      if (item->getUserId() == userId) {
        return item;
        break;
      }
    }
  }
	return NULL;
}

void RoomForm::readMusicPostion() {
	if (!musicPlaying_)
		return;
	int pos = rtcEngine_->getAudioMixingCurrentPosition();
	musicTimeLabel_->SetText(nbase::StringPrintf(L"%02d:%02d", pos / 1000 / 60, pos / 1000 % 60));
	musicSlider_->SetValue(pos/1000);
	nbase::ThreadManager::PostDelayedTask(kThreadUI, [this]() {
		readMusicPostion();
	}, nbase::TimeDelta::FromMicroseconds(1000000));
}

void RoomForm::onItemVolumeChange(uint32_t userId, int volume) {
	rtcEngine_->adjustUserPlaybackSignalVolume(userId, volume);
}

void RoomForm::onItemAudioMuteSateChange(uint32_t userId, bool mute) {
	rtcEngine_->muteRemoteAudioStream(userId, mute);
}

void RoomForm::onItemVideoMuteSateChange(uint32_t userId, bool mute) {
    rtcEngine_->muteRemoteVideoStream(userId, mute);
}

void RoomForm::onItemCreateFinish(uint32_t userId, HWND hWnd) {
	bbrtc::VideoCanvas canvas;
	canvas.uid = userId;
	canvas.renderMode = bbrtc::RENDER_MODE_FIT;
	canvas.mirrorMode = bbrtc::VIDEO_MIRROR_MODE_AUTO;
	canvas.view = (bbrtc::view_t)hWnd;
	if (userId == userId_) {
		rtcEngine_->setupLocalVideo(canvas);
	}
	else {
		rtcEngine_->setupRemoteVideo(canvas);
	}
}

void RoomForm::onItemVideoStreamChange(uint32_t userId, bool streamType) {
	bbrtc::REMOTE_VIDEO_STREAM_TYPE type = streamType ? bbrtc::REMOTE_VIDEO_STREAM_HIGH: bbrtc::REMOTE_VIDEO_STREAM_LOW;
	rtcEngine_->setRemoteVideoStreamType(userId, type);
}

void RoomForm::onWarning(int warn, const char* msg) {
}
void RoomForm::onError(int err, const char* msg) {

}
void RoomForm::onJoinChannelSuccess(const char* channel, bbrtc::uid_t uid, int elapsed) {
	nbase::ThreadManager::PostTask(kThreadUI, [this]() {
		stateLabel_->SetText(L"join room suc");
	});
}
void RoomForm::onRejoinChannelSuccess(const char* channel, bbrtc::uid_t uid, int elapsed) {
	nbase::ThreadManager::PostTask(kThreadUI, [this]() {
		stateLabel_->SetText(L"reconnecting suc");
	});
}
void RoomForm::onLeaveChannel(const bbrtc::RtcStats& stats) {
	nbase::ThreadManager::PostTask(kThreadUI, [this]() {
		stateLabel_->SetText(L"exit room suc");
	});
}
void RoomForm::onClientRoleChanged(bbrtc::CLIENT_ROLE_TYPE oldRole, bbrtc::CLIENT_ROLE_TYPE newRole) {

}
void RoomForm::onUserJoined(bbrtc::uid_t uid, int elapsed) {
	nbase::ThreadManager::PostTask(kThreadUI, [this, uid]() {
		addUserItem(uid);
		return true;
	});
}
void RoomForm::onUserOffline(bbrtc::uid_t uid, bbrtc::USER_OFFLINE_REASON_TYPE reason) {
	nbase::ThreadManager::PostTask(kThreadUI, [this, uid]() {
        if (uid != userId_) {
            removeUserItem(uid);
        }
	});
}
void RoomForm::onRemoteAudioStateChanged(bbrtc::uid_t uid, bbrtc::REMOTE_AUDIO_STATE state, bbrtc::REMOTE_AUDIO_STATE_REASON reason, int elapsed) {
	nbase::ThreadManager::PostTask(kThreadUI, [this, uid, state, reason]() {
		switch (state) {
		case bbrtc::REMOTE_AUDIO_STATE_STOPPED:
			if (reason == bbrtc::REMOTE_AUDIO_REASON_LOCAL_MUTED) {
				Item *item = getItem(uid);
				if (item)item->setVolume(0);
			}
			else if (reason == bbrtc::REMOTE_AUDIO_REASON_REMOTE_MUTED) {
				Item *item = getItem(uid);
				if (item)item->setMute(true);
			}
			else if (reason == bbrtc::REMOTE_AUDIO_REASON_REMOTE_OFFLINE) {
				Item *item = getItem(uid);
				if (item)item->setMute(false);
			}
			break;
		case bbrtc::REMOTE_AUDIO_STATE_STARTING:

			break;
		case bbrtc::REMOTE_AUDIO_STATE_DECODING:
			if (reason == bbrtc::REMOTE_AUDIO_REASON_NETWORK_RECOVERY) {

			}
			else if (reason == bbrtc::REMOTE_AUDIO_REASON_LOCAL_UNMUTED) {

			}
			else if (reason == bbrtc::REMOTE_AUDIO_REASON_REMOTE_UNMUTED) {
				Item *item = getItem(uid);
				if (item)item->setMute(false);
			}
			break;
		case bbrtc::REMOTE_AUDIO_STATE_FROZEN:
			break;
		case bbrtc::REMOTE_AUDIO_STATE_FAILED:
			break;
		}
	});

}
void RoomForm::onAudioVolumeIndication(const bbrtc::AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume) {
	std::vector<bbrtc::AudioVolumeInfo> vecInfos;
	for (int i = 0; i < speakerNumber; i++) {
		vecInfos.push_back(speakers[i]);
	}
	nbase::ThreadManager::PostTask(kThreadUI, [this, vecInfos]() {
		bool vad = false;
		for (size_t i = 0; i < vecInfos.size(); ++i) {
			Item* item = getItem(vecInfos[i].uid);
			if (item) {
				item->setVolume(vecInfos[i].volume);
			}
			vad = vecInfos[i].vad;
		}

		std::wstring color = vad ? L"green2" : L"white";
		vadBnt_->SetBkColor(color);
	});
}
void RoomForm::onAudioMixingFinished() {
	nbase::ThreadManager::PostTask(kThreadUI, [this]() {
		ui::RichEdit* musicNameEdit = dynamic_cast<ui::RichEdit*>(FindControl(L"play_music_name_edit"));
		if (music_play_mode_ == music_loop) {
			if (vecMusicFiles_.empty()) {
				musicPath_.clear();
			}
			else {
				currentPlayIndex_ = (currentPlayIndex_ + 1) % vecMusicFiles_.size();
				musicPath_ = nbase::UTF16ToUTF8(vecMusicFiles_[currentPlayIndex_]);
			}
		}
		else if (music_play_mode_ == music_random) {
			if (vecMusicFiles_.empty()) {
				musicPath_.clear();
			}
			else {
				int tmp = currentPlayIndex_;
				while (vecMusicFiles_.size() > 1 && currentPlayIndex_ != tmp) {
					tmp = rand() % vecMusicFiles_.size();
				}
				currentPlayIndex_ = tmp;
				musicPath_ = nbase::UTF16ToUTF8(vecMusicFiles_[currentPlayIndex_]);
			}
		}
		else if (music_play_mode_ == music_repetition) {

		}
		if (!musicPath_.empty()) {
			musicNameEdit->SetText(nbase::UTF8ToUTF16(musicPath_));
			startPlayMusic();
		}
		else {
			stopPlayMusic();
		}
	});
}
void RoomForm::onAudioMixingStateChanged(bbrtc::AUDIO_MIXING_STATE_TYPE state, bbrtc::AUDIO_MIXING_REASON_TYPE errorCode) {
	nbase::ThreadManager::PostTask(kThreadUI, [this, state, errorCode]() {
		switch (state) {
		case bbrtc::AUDIO_MIXING_STATE_PLAYING: {
			stateLabel_->SetText(L"play music suc");
			musicTotalTimeMs_ = rtcEngine_->getAudioMixingDuration();
			musicTotalTimeLabel_->SetText(nbase::StringPrintf(L"%02d:%02d", (int)musicTotalTimeMs_/1000/60, (int)musicTotalTimeMs_/1000%60));
			musicSlider_->SetMaxValue(musicTotalTimeMs_ / 1000);
			musicSlider_->SetMinValue(0);
			musicSlider_->SetValue(0);
			readMusicPostion();
		}
			break;
		case bbrtc::AUDIO_MIXING_STATE_PAUSED:
			stateLabel_->SetText(L"play music pause");
			break;
		case bbrtc::AUDIO_MIXING_STATE_STOPPED:
			stateLabel_->SetText(L"play music end");
			break;
		case bbrtc::AUDIO_MIXING_STATE_FAILED: {
			switch (errorCode) {
			case bbrtc::AUDIO_MIXING_REASON_CAN_NOT_OPEN:
				stateLabel_->SetText(L"open music failed");
				stopPlayMusic();
				break;
			case bbrtc::AUDIO_MIXING_REASON_TOO_FREQUENT_CALL:
				stateLabel_->SetText(L"open music call too fre");
				break;
			case bbrtc::AUDIO_MIXING_REASON_INTERRUPTED_EOF:
				stateLabel_->SetText(L"open music interruption");
				stopPlayMusic();
				break;
			default:
				break;
			}
			break;
		}
		}
	});
}
void RoomForm::onConnectionStateChanged(bbrtc::CONNECTION_STATE_TYPE state, bbrtc::CONNECTION_CHANGED_REASON_TYPE reason) {
	nbase::ThreadManager::PostTask(kThreadUI, [this, state, reason]() {
		switch (state) {
		case bbrtc::CONNECTION_STATE_DISCONNECTED:
		{
			switch (reason) {
			case bbrtc::CONNECTION_CHANGED_INTERRUPTED:
				stateLabel_->SetText(L"disconnecting net error");
				break;
			case bbrtc::CONNECTION_CHANGED_JOIN_FAILED:
				stateLabel_->SetText(L"disconnecting join failed");
				break;
			case bbrtc::CONNECTION_CHANGED_LEAVE_CHANNEL:
				stateLabel_->SetText(L"disconnect leave channel");
				break;
			case bbrtc::CONNECTION_CHANGED_INVALID_CHANNEL_NAME:
				stateLabel_->SetText(L"disconnect,invalid channel name");
				break;
			case bbrtc::CONNECTION_CHANGED_BANNED_BY_SERVER:
				stateLabel_->SetText(L"disconnect,rejected join");
				break;
			case bbrtc::CONNECTION_CHANGED_KEEP_ALIVE_TIMEOUT:
				stateLabel_->SetText(L"disconnect,heartbeat timeout");
				break;
			default:
				stateLabel_->SetText(L"disconnect");
				break;
			}
		}break;
		case bbrtc::CONNECTION_STATE_CONNECTING:
			switch (reason) {
			case bbrtc::CONNECTION_CHANGED_JOIN_SUCCESS:
				stateLabel_->SetText(L"connecting ,join channel suc..");
				break;
			default:
				stateLabel_->SetText(L"connecting...");
				break;
			}
			break;
		case bbrtc::CONNECTION_STATE_CONNECTED:
			stateLabel_->SetText(L"connected suc");
			isJoined_ = true;
			break;
		case bbrtc::CONNECTION_STATE_RECONNECTING:
			stateLabel_->SetText(L"connecting...");
			break;
		case bbrtc::CONNECTION_STATE_FAILED:
			stateLabel_->SetText(L"connect failed");
			rtcEngine_->leaveChannel();
			break;
		}
	});
}

void RoomForm::onChannelMediaRelayStateChanged(bbrtc::CHANNEL_MEDIA_RELAY_STATE state, bbrtc::CHANNEL_MEDIA_RELAY_ERROR code)
{
		nbase::ThreadManager::PostTask(kThreadUI, [this, state, code]() {
			if (state == bbrtc::RELAY_STATE_RUNNING && code == bbrtc::RELAY_OK) {
				stateLabel_->SetText(L"relay suc");
			}
			else if (state == bbrtc::RELAY_STATE_FAILURE) {
				wchar_t msg[128] = { 0 };
				wsprintf(msg, L"relay failed, code:%d", code);
				stateLabel_->SetText(msg);
				stopRelayMedia();
			}
		});
}

void RoomForm::onChannelMediaRelayEvent(bbrtc::CHANNEL_MEDIA_RELAY_EVENT code)
{
	nbase::ThreadManager::PostTask(kThreadUI, [this, code]() {
		if (code == bbrtc::RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL_IS_NULL) {
			stateLabel_->SetText(L"relay failed, channel not exit");
			stopRelayMedia();
		}
		else {
			wchar_t msg[128] = { 0 };
			wsprintf(msg, L"relay event, event:%d", code);
			stateLabel_->SetText(msg);
		}
	});
}
