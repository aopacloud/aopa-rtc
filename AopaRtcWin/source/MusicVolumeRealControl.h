#pragma once

class MusicVolumeRealControl : public ui::Control
{
public:
	MusicVolumeRealControl();
	void setVolume(int volume);
	void setMute(bool mute);
protected:
	void Paint(ui::IRenderContext* pRender, const ui::UiRect& rcPaint) override;
private:
	int volume_ = 0;
	bool mute_ = false;
};

