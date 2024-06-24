#ifndef STATS_MANAGER_H
#define STATS_MANAGER_H

#include "LocalStatsData.h"
#include "RemoteStatsData.h"

#include <list>
#include <unordered_map>

class StatsManager {
private:
    std::unordered_map<long, StatsData*> mDataMap;
    bool mEnable = false;

public:
    StatsManager() {}

    ~StatsManager() {
        clearAllData();
    }
    
    void addUserStats(int uid, bool ifLocal) {
        auto it = mDataMap.find(uid);
        if (it != mDataMap.end()) {
            return;
        }

        StatsData* data = nullptr;
        if (ifLocal) {
            data = new LocalStatsData();
        } else {
            data = new RemoteStatsData();
        }
        // in case 32-bit unsigned integer uid is received
        data->setUid(uid & 0xFFFFFFFFL);
        mDataMap[uid] = data;
    }

    void removeUserStats(int uid) {
        auto it = mDataMap.find(uid);
        if (it != mDataMap.end()) {
            StatsData* data = it->second;
            if (data) {
                delete data;
                data = nullptr;
            }
            mDataMap.erase(it);
        }
    }

    StatsData* getStatsData(int uid) {
        auto it = mDataMap.find(uid);
        if (it != mDataMap.end()) {
            return mDataMap[uid];
        }
        return nullptr;
    }

    std::string qualityToString(int quality) {
        switch (quality) {
            case 0:
                return "Exc";
            case 1:
                return "Good";
            case 2:
                return "Poor";
            case 3:
                return "Bad";
            case 4:
                return "VBad";
            case 5:
                return "Down";
            default:
                return "Unk";
        }
    }

    void enableStats(bool enabled) {
        mEnable = enabled;
    }

    bool isEnabled() {
        return mEnable;
    }

    void clearAllData() {
        auto it = mDataMap.begin();
        for (; it != mDataMap.end(); ++it) {
            StatsData* data = it->second;
            if (data) {
                delete data;
                data = nullptr;
            }
        }
        mDataMap.clear();
    }
};

#endif // STATS_MANAGER_H
