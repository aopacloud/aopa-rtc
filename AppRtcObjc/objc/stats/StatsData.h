#ifndef STATS_DATA_H
#define STATS_DATA_H

#include <string>

class StatsData {
private:
    int uid;
    int width;
    int height;
    int framerate;
    std::string recvQuality;
    std::string sendQuality;

public:  
    StatsData() :
        uid(0),
        width(0),
        height(0),
        framerate(0),
        recvQuality(std::string("")),
        sendQuality(std::string("")) {}

    virtual ~StatsData() {}
    
    virtual std::string toString() {
        return std::string("");
    }

    int getUid() {
        return uid;
    }

    void setUid(int uid) {
        this->uid = uid;
    }

    int getWidth() {
        return width;
    }

    void setWidth(int width) {
        this->width = width;
    }

    int getHeight() {
        return height;
    }

    void setHeight(int height) {
        this->height = height;
    }

    int getFramerate() {
        return framerate;
    }

    void setFramerate(int framerate) {
        this->framerate = framerate;
    }

    std::string getRecvQuality() {
        return recvQuality;
    }

    void setRecvQuality(const std::string& recvQuality) {
        this->recvQuality = recvQuality;
    }

    std::string getSendQuality() {
        return sendQuality;
    }

    void setSendQuality(std::string sendQuality) {
        this->sendQuality = sendQuality;
    }
};

#endif // STATS_DATA_H
