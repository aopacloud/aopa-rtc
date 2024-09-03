#pragma once

#include "stdafx.h"
#include <thread>
#include <functional>

class CustomVideoSource : public bbrtc::IVideoSource{
public:
    bool onInitialize(bbrtc::IVideoFrameConsumer* consumer) {
        consumer_ = consumer;
        return true;
    }

    void onDispose() {
        consumer_ = nullptr;
    }

    bool onStart() {
        std::thread th(std::bind(&CustomVideoSource::pushData, this));
        th.detach();
        return true;
    }

    void onStop() {
        consumer_ = nullptr;
    }

    bbrtc::media::ExternalVideoFrame::VIDEO_PIXEL_FORMAT getBufferType() {
        return bbrtc::media::ExternalVideoFrame::VIDEO_PIXEL_I420;
    }

    bbrtc::VIDEO_CAPTURE_TYPE getVideoCaptureType() {
        return bbrtc::VIDEO_CAPTURE_UNKNOWN;
    }

    bbrtc::VideoContentHint getVideoContentHint() {
        return bbrtc::CONTENT_HINT_NONE;
    }

    void pushData();

private:
    bbrtc::IVideoFrameConsumer* consumer_;
};
