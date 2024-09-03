#include "stdafx.h"
#include "MusicVolumeRealControl.h"

MusicVolumeRealControl::MusicVolumeRealControl() {
}

void MusicVolumeRealControl::setVolume(int volume) {
	if (volume_ == volume)
		return;
	volume_ = volume;
	Invalidate();
}

void MusicVolumeRealControl::setMute(bool mute) {
	if (mute_ == mute)
		return;
	mute_ = mute;
	volume_ = 0;
	Invalidate();
}

void MusicVolumeRealControl::Paint(ui::IRenderContext* pRender, const ui::UiRect& rcPaint) {
	ui::Control::Paint(pRender, rcPaint);
	ui::UiRect rc = this->GetPos();
	DWORD color = mute_ ? 0xFF121224 : 0xFF00FF00 ;
	int right = rc.GetWidth() / 255.f * volume_;
	if (mute_) right = rc.GetWidth();
	ui::UiRect draw_rc(rc.left, rc.top, rc.left + right, rc.bottom);
	pRender->DrawColor(draw_rc, color, 255);
}
