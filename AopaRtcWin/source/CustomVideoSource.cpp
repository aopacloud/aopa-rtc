#include "CustomVideoSource.h"
#include <stdio.h>
#include <string.h>

void CustomVideoSource::pushData() {
    const int kWidth = 256;
    const int kHeight = 256;
    int size = kWidth * kHeight * 3 / 2;

    char filename[64];
    uint8_t* buffer = new uint8_t[size];
    sprintf(filename, "C:\\Data\\yuv\\lena.yuv");
    FILE* fp = fopen(filename, "rb");
    if (fp == nullptr) {
        fprintf(stderr, "Open file error.");
        return;
    }
    fread(buffer, 1, size, fp);
    fclose(fp);

    long timestamp = 0; 
    int rotation = 0;
    while (consumer_ != nullptr) {
        rotation = (rotation + 90) % 360;
        timestamp = GetTickCount();
        consumer_->consumeRawVideoFrame(buffer, bbrtc::media::ExternalVideoFrame::VIDEO_PIXEL_I420,
            kWidth, kHeight, rotation, timestamp);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    delete[] buffer;
}

