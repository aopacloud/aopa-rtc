#pragma once
#include "MusicVolumeRealControl.h"

class ItemSink {
public:
	virtual ~ItemSink() {}
	virtual void onItemVolumeChange(uint32_t userId, int volume) = 0;
	virtual void onItemAudioMuteSateChange(uint32_t userId, bool mute) = 0;
    virtual void onItemVideoMuteSateChange(uint32_t userId, bool mute) = 0;
	virtual void onItemCreateFinish(uint32_t userId, HWND hWnd) = 0;
	virtual void onItemVideoStreamChange(uint32_t userId, bool streamType) = 0;
};
class Item : public ui::ListContainerElement
{
public:
	Item();
	~Item();
	void setSink(ItemSink* sink) { sink_ = sink; }
	void InitSubControls(uint32_t userId);
	void setVolume(int volume);
	void setMute(bool mute);
	uint32_t getUserId() { return userId_; }

	void SetWindow(ui::Window* pManager, ui::Box* pParent, bool bInit = true) override;
private:
	bool OnRemove(ui::EventArgs* args);

private:
	uint32_t userId_;
    bool isVideoMute_ = false;
	bool isAudioMute_ = false;
	bool isBigStream = true;
	ItemSink* sink_ = nullptr;
	ui::Label*  current_volume_lable_;
	ui::MediaWnd* video_view_;
	MusicVolumeRealControl*	current_volume_bar_;
	bool isCallbacked_ = false;

};

