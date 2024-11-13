package com.aopa.aopartcandroid.stats;

import java.util.Locale;

public class RemoteStatsData extends StatsData {
    private static final String FORMAT = "Remote(%d)\n" +
            "%dx%d %dfps\n" +
            "Video rx: %d\n" +
            "Video delay: %dms\n" +
            "Audio rx: %d\n" +
            "Audio delay: %dms\n" +
            "Audio jitter: %dms\n" +
            "Audio loss: %d%%";

    private int videoRx;
    private int videoDelay;
    private int audioRx;
    private int audioNetDelay;
    private int audioNetJitter;
    private int audioLoss;
    private String audioQuality;


    @Override
    public String toString() {
        return String.format(Locale.getDefault(), FORMAT,
                getUid(),
                getWidth(), getHeight(), getFramerate(),
                getVideoRx(),
                getVideoDelay(),
                getAudioRx(),
                getAudioNetDelay(),
                getAudioNetJitter(),
                getAudioLoss());
    }

    public static String getFORMAT() {
        return FORMAT;
    }

    public int getVideoRx() {
        return videoRx;
    }

    public void setVideoRx(int rx) {
        this.videoRx = rx;
    }

    public int getVideoDelay() {
        return videoDelay;
    }

    public void setVideoDelay(int videoDelay) {
        this.videoDelay = videoDelay;
    }

    public int getAudioRx() {
        return audioRx;
    }

    public void setAudioRx(int rx) {
        this.audioRx = rx;
    }

    public int getAudioNetDelay() {
        return audioNetDelay;
    }

    public void setAudioNetDelay(int audioNetDelay) {
        this.audioNetDelay = audioNetDelay;
    }

    public int getAudioNetJitter() {
        return audioNetJitter;
    }

    public void setAudioNetJitter(int audioNetJitter) {
        this.audioNetJitter = audioNetJitter;
    }

    public int getAudioLoss() {
        return audioLoss;
    }

    public void setAudioLoss(int audioLoss) {
        this.audioLoss = audioLoss;
    }

    public String getAudioQuality() {
        return audioQuality;
    }

    public void setAudioQuality(String audioQuality) {
        this.audioQuality = audioQuality;
    }
}
