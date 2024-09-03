#include "AudioFrameObserver.h"
#include <iostream>

AudioFrameObserver::AudioFrameObserver() {
}

AudioFrameObserver::~AudioFrameObserver() {
}

bool AudioFrameObserver::onRecordAudioFrame(AudioFrame& audioFrame) {
    return true;
}

bool AudioFrameObserver::onPlaybackAudioFrame(AudioFrame& audioFrame) {
    return true;
}

bool AudioFrameObserver::onMixedAudioFrame(AudioFrame& audioFrame) {
    std::cout << "onAudioFrame Mixed size:" << audioFrame.samples;
    return true;
}

bool AudioFrameObserver::onPlaybackAudioFrameBeforeMixing(unsigned int uid, 
    AudioFrame& audioFrame) {
    return true;
}