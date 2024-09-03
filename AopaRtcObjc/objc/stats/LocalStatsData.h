#ifndef LOCAL_STATS_DATA_H
#define LOCAL_STATS_DATA_H

#include "StatsData.h"

class LocalStatsData : public StatsData {
private:
     const char sFormat[1024] = "Local(%d)\n"
        "%dx%d %dfps\n"
        "LastMile delay: %dms\n"
        "tx/rx(kbps): %d/%d\n"
        "Loss tx/rx: %d%%/%d%%";

    int lastMileDelay;
    int videoSend;
    int videoRecv;
    int audioSend;
    int audioRecv;
    double cpuApp;
    double cpuTotal;
    int sendLoss;
    int recvLoss;

public:
    LocalStatsData() :
        lastMileDelay(0),
        videoSend(0),
        videoRecv(0),
        audioSend(0),
        audioRecv(0),
        cpuApp(0.0),
        cpuTotal(0.0),
        sendLoss(0),
        recvLoss(0) {}

    ~LocalStatsData() {}

    std::string toString() {
        char buffer[1024];
        sprintf(buffer, sFormat, getUid(),
                getWidth(), getHeight(), getFramerate(),
                getLastMileDelay(),
                getVideoSendBitrate(), getVideoRecvBitrate(),
                getSendLoss(), getRecvLoss());
        return std::string(buffer);
    }

    int getLastMileDelay() {
        return lastMileDelay;
    }

    void setLastMileDelay(int lastMileDelay) {
        this->lastMileDelay = lastMileDelay;
    }

    int getVideoSendBitrate() {
        return videoSend;
    }

    void setVideoSendBitrate(int videoSend) {
        this->videoSend = videoSend;
    }

    int getVideoRecvBitrate() {
        return videoRecv;
    }

    void setVideoRecvBitrate(int videoRecv) {
        this->videoRecv = videoRecv;
    }

    int getAudioSendBitrate() {
        return audioSend;
    }

    void setAudioSendBitrate(int audioSend) {
        this->audioSend = audioSend;
    }

    int getAudioRecvBitrate() {
        return audioRecv;
    }

    void setAudioRecvBitrate(int audioRecv) {
        this->audioRecv = audioRecv;
    }

    double getCpuApp() {
        return cpuApp;
    }

    void setCpuApp(double cpuApp) {
        this->cpuApp = cpuApp;
    }

    double getCpuTotal() {
        return cpuTotal;
    }

    void setCpuTotal(double cpuTotal) {
        this->cpuTotal = cpuTotal;
    }

    int getSendLoss() {
        return sendLoss;
    }

    void setSendLoss(int sendLoss) {
        this->sendLoss = sendLoss;
    }

    int getRecvLoss() {
        return recvLoss;
    }

    void setRecvLoss(int recvLoss) {
        this->recvLoss = recvLoss;
    }
};

#endif // LOCAL_STATS_DATA_H
