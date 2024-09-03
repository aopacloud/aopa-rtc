#include "VideoFrameObserver.h"
#include <iostream>

VideoFrameObserver::VideoFrameObserver() {
}

VideoFrameObserver::~VideoFrameObserver() {
}

bool VideoFrameObserver::onCaptureVideoFrame(VideoFrame& videoFrame) {
    return true;
}

bool VideoFrameObserver::onPreEncodeVideoFrame(VideoFrame& videoFrame) {
    return true;
}

bool VideoFrameObserver::onRenderVideoFrame(unsigned int uid, VideoFrame& videoFrame) {
    return true;
}