#ifndef REMOTE_STATS_DATA_H
#define REMOTE_STATS_DATA_H

#include "StatsData.h"

class RemoteStatsData : public StatsData {
private:
    const char sFormat[1024] = "Remote(%d)\n"
            "%dx%d %dfps\n"
            "Video rx: %d\n"
            "Video delay: %dms\n"
            "Audio rx: %d\n"
            "Audio delay: %dms\n"
            "Audio jitter: %dms\n"
            "Audio loss: %d%%";

    int frozenTime;
    int videoRx;
    int videoDelay;
    int audioRx;
    int audioNetDelay;
    int audioNetJitter;
    int audioLoss;
    std::string audioQuality;

public:
    RemoteStatsData() :
        frozenTime(0),
        videoRx(0),
        videoDelay(0),
        audioRx(0),
        audioNetDelay(0),
        audioNetJitter(0),
        audioLoss(0),
        audioQuality(std::string("")) {}

    ~RemoteStatsData() {}

    std::string toString() {
        char buffer[1024];
        sprintf(buffer, sFormat, getUid(),
                getWidth(), getHeight(), getFramerate(),
                getVideoRx(),
                getVideoDelay(),
                getAudioRx(),
                getAudioNetDelay(),
                getAudioNetJitter(),
                getAudioLoss());
        return std::string(buffer);
    }
    
    int getFrozenTime() {
        return frozenTime;
    }

    void setFrozenTime(int ft) {
        this->frozenTime = ft;
    }

    int getVideoRx() {
        return videoRx;
    }

    void setVideoRx(int rx) {
        this->videoRx = rx;
    }

    int getVideoDelay() {
        return videoDelay;
    }

    void setVideoDelay(int videoDelay) {
        this->videoDelay = videoDelay;
    }

    int getAudioRx() {
        return audioRx;
    }

    void setAudioRx(int rx) {
        this->audioRx = rx;
    }

    int getAudioNetDelay() {
        return audioNetDelay;
    }

    void setAudioNetDelay(int audioNetDelay) {
        this->audioNetDelay = audioNetDelay;
    }

    int getAudioNetJitter() {
        return audioNetJitter;
    }

    void setAudioNetJitter(int audioNetJitter) {
        this->audioNetJitter = audioNetJitter;
    }

    int getAudioLoss() {
        return audioLoss;
    }

    void setAudioLoss(int audioLoss) {
        this->audioLoss = audioLoss;
    }

    std::string getAudioQuality() {
        return audioQuality;
    }

    void setAudioQuality(const std::string& audioQuality) {
        this->audioQuality = audioQuality;
    }
};

#endif // REMOTE_STATS_DATA_H
