package com.aopa.aopartcandroid;

import android.os.Handler;
import android.view.View;
import android.widget.Button;
import android.widget.RelativeLayout;
import android.widget.SeekBar;
import android.widget.TextView;

import androidx.recyclerview.widget.RecyclerView;

import com.aopa.aopartcandroid.stats.StatsData;
import com.aopa.aopartcandroid.stats.StatsManager;

import java.lang.ref.WeakReference;

public class SimpleHolder extends RecyclerView.ViewHolder {
  private StatsManager mStatsManager;
  private TextView mStatsText;
  private TextView mUserIdText;
  private TextView mLiveVolumeText;
  private VolumeView mVolumeView;
  private Button mAudioMuteBnt;
  private Button mVideoMuteBnt;
  private Button mVideoDoubleStreamBnt;
  private TextView mVolumeText;
  private SeekBar mSeekBar;
  private WeakReference<UserViewInterface> mDelegate;
  private RelativeLayout mVideoView;
  public  boolean isAudioMute = false;
  public  boolean isVideoMute = false;
  public  boolean isBigStream = true;
  private int mUserId = 0;
  private Handler mHandler;
  public SimpleHolder(View itemView, UserViewInterface delegate, StatsManager sg) {
    super(itemView);
    mStatsText = itemView.findViewById(R.id.statsTextView);
    mUserIdText = itemView.findViewById(R.id.userIDTextView);
    mLiveVolumeText = itemView.findViewById(R.id.liveVolumeTextView);
    mVolumeView = itemView.findViewById(R.id.liveVolumeView);
    mAudioMuteBnt = itemView.findViewById(R.id.audioMuteButton);
    mVideoMuteBnt = itemView.findViewById(R.id.videoMuteButton);
    mVideoDoubleStreamBnt = itemView.findViewById(R.id.videoDoubleStreamButton);
    mVolumeText = itemView.findViewById(R.id.volumeVauleTextView);
    mSeekBar = itemView.findViewById(R.id.seekBar);
    mVideoView = itemView.findViewById(R.id.videoView);
    mDelegate = new WeakReference<UserViewInterface>(delegate);
    mStatsManager = sg;
    mHandler = new Handler();
    mAudioMuteBnt.setOnClickListener(new View.OnClickListener() {
      @Override
      public void onClick(View view) {
        onAudioMuteClick(view);
      }
    });

    mVideoMuteBnt.setOnClickListener(new View.OnClickListener() {
      @Override
      public void onClick(View view) {
        onVideoMuteClick(view);
      }
    });

    mVideoDoubleStreamBnt.setOnClickListener(new View.OnClickListener() {
      @Override
      public void onClick(View view) {
        onDoubleStreamClick(view);
      }
    });

    mSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
      @Override
      public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
        mVolumeText.setText(Integer.toString(progress));
        if(mDelegate.get() != null)
          mDelegate.get().onUserVolumeChange(mUserId, progress);
      }

      @Override
      public void onStartTrackingTouch(SeekBar seekBar) {
      }

      @Override
      public void onStopTrackingTouch(SeekBar seekBar) {
      }
    });
    RefreshStats();
  }

  public void setUserId(int userId){
     mUserId = userId;
     mUserIdText.setText(String.valueOf(userId));
  }

  public void updateState(){
    mAudioMuteBnt.setText(isAudioMute ? "Audio Play" : "Audio Mute");
    mVideoMuteBnt.setText(isVideoMute ? "Video Play" : "Video Mute");
    mVideoDoubleStreamBnt.setText(isBigStream ? "high" : "low");
  }

  public int getUserId(){
    return mUserId;
  }

  public void setRealTimeVolume(int volume){
    mLiveVolumeText.setText(String.valueOf(volume));
    mVolumeView.setVolume(volume);
  }

  public void setRemoteMute(boolean mute){
    mVolumeView.setMuete(mute);
  }

  public void setVideoMute(boolean mute){
    isVideoMute = mute;
  }

  public void setAudioMute(boolean mute){
    isAudioMute = mute;
  }

  public void setBigStream(boolean bigstream){
    isBigStream = bigstream;
  }

  void onAudioMuteClick(View view) {
    if (mDelegate.get() != null && mDelegate.get().onUserAudioMuteEnable(mUserId, !isAudioMute))
      isAudioMute = !isAudioMute;
    mAudioMuteBnt.setText(isAudioMute ? "Audio Play" : "Audio Mute");
  }

  void onVideoMuteClick(View view) {
    if (mDelegate.get() != null &&  mDelegate.get().onUserVideoMuteEnable(mUserId, !isVideoMute))
      isVideoMute = !isVideoMute;
    mVideoMuteBnt.setText(isVideoMute ? "Video Play" : "Video Mute");
    mVideoView.refreshDrawableState();
  }

  void onDoubleStreamClick(View view){
    if (mDelegate.get() != null &&  mDelegate.get().onUserStreamStateChange(mUserId, !isBigStream))
      isBigStream = !isBigStream;
    mVideoDoubleStreamBnt.setText(isBigStream ? "high" : "low");
  }

  RelativeLayout getVideoView(){
    return mVideoView;
  }

  public void RefreshStats() {
    mHandler.postDelayed(()->{
     if (mStatsManager != null && mStatsManager.isEnabled()) {
       if (mStatsText != null) {
         StatsData data = mStatsManager.getStatsData(mUserId);
         String info = data != null ? data.toString() : null;
         if (info != null) mStatsText.setText(info);
         RefreshStats();
       }
    }}, 2000);
  }
}
