#pragma once

#include "api/IBBMediaEngine.h"

class VideoFrameObserver : public bbrtc::media::IVideoFrameObserver {
public:
    VideoFrameObserver();
    ~VideoFrameObserver();

    bool onCaptureVideoFrame(VideoFrame& videoFrame) override;

    bool onPreEncodeVideoFrame(VideoFrame& videoFrame) override;

    bool onRenderVideoFrame(unsigned int uid, VideoFrame& videoFrame) override;
};
