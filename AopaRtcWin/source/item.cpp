#include "stdafx.h"
#include "item.h"


Item::Item()
{
}


Item::~Item()
{
}

void Item::InitSubControls(uint32_t userId)
{
	video_view_ = dynamic_cast<ui::MediaWnd*>(FindSubControl(L"video_view"));
	ui::Label* userIdLable = dynamic_cast<ui::Label*>(FindSubControl(L"userid_label"));
	userIdLable->SetText(nbase::StringPrintf(L"%u", userId));
	current_volume_lable_ = dynamic_cast<ui::Label*>(FindSubControl(L"current_volume_label"));
	current_volume_bar_ = dynamic_cast<MusicVolumeRealControl*>(FindSubControl(L"current_volume_bar"));
	ui::Label* volumeLabel = dynamic_cast<ui::Label*>(FindSubControl(L"music_volume_value_label"));
	ui::Slider* slider = dynamic_cast<ui::Slider*>(FindSubControl(L"volume_slider"));
	slider->AttachValueChange([this, slider, volumeLabel](ui::EventArgs* args) {
		int value = slider->GetValue();
		volumeLabel->SetText(nbase::StringPrintf(L"%d", value));
		if (sink_)
			sink_->onItemVolumeChange(userId_, value);
		return true;
	});

	ui::Button* muteBnt = dynamic_cast<ui::Button*>(FindSubControl(L"audio_mute_bnt"));
	muteBnt->AttachClick([this, muteBnt](ui::EventArgs* args) {
		if (isAudioMute_) {
			muteBnt->SetText(L"mute");
		}
		else {
			muteBnt->SetText(L"play");
		}
        isAudioMute_ = !isAudioMute_;
		if (sink_)
			sink_->onItemAudioMuteSateChange(userId_, isAudioMute_);
		return true;
	});

    ui::Button* videoMuteBnt = dynamic_cast<ui::Button*>(FindSubControl(L"video_mute_bnt"));
    videoMuteBnt->AttachClick([this, videoMuteBnt](ui::EventArgs* args) {
        if (isVideoMute_) {
            videoMuteBnt->SetText(L"close video");
        }
        else {
            videoMuteBnt->SetText(L"sub video");
        }
        isVideoMute_ = !isVideoMute_;
        if (sink_)
            sink_->onItemVideoMuteSateChange(userId_, isVideoMute_);
        return true;
    });

	ui::Button* doubleStreamBnt = dynamic_cast<ui::Button*>(FindSubControl(L"double_stream_bnt"));
	doubleStreamBnt->AttachClick([this, doubleStreamBnt](ui::EventArgs* args) {
		if (isBigStream) {
			doubleStreamBnt->SetText(L"low stream");
		}
		else {
			doubleStreamBnt->SetText(L"high stream");
		}
		isBigStream = !isBigStream;
		if (sink_)
			sink_->onItemVideoStreamChange(userId_, isBigStream);
		return true;
	});
	userId_ = userId;
	
	
}

bool Item::OnRemove(ui::EventArgs* args)
{
	ui::ListBox* parent = dynamic_cast<ui::ListBox*>(this->GetParent());
	return parent->Remove(this);
}

void Item::setVolume(int volume) {
	current_volume_lable_->SetText(nbase::StringPrintf(L"%d", volume));
	current_volume_bar_->setVolume(volume);
}
void Item::setMute(bool mute) {
	current_volume_bar_->setMute(mute);
}

void Item::SetWindow(ui::Window* pManager, ui::Box* pParent, bool bInit) {
	ui::ListContainerElement::SetWindow(pManager, pParent, bInit);
  HWND hwnd = video_view_->GetWND();
	if (hwnd && !isCallbacked_) {
		sink_->onItemCreateFinish(userId_, hwnd);
		isCallbacked_ = true;
	}
}