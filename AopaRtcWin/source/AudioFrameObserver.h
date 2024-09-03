#pragma once

#include "stdafx.h"

class AudioFrameObserver : public bbrtc::media::IAudioFrameObserver {
public:
    AudioFrameObserver();
    ~AudioFrameObserver();

    bool onRecordAudioFrame(AudioFrame& audioFrame) override;
    
    bool onPlaybackAudioFrame(AudioFrame& audioFrame) override;
    
    bool onMixedAudioFrame(AudioFrame& audioFrame) override;
    
    bool onPlaybackAudioFrameBeforeMixing(unsigned int uid, AudioFrame& audioFrame) override;
};
