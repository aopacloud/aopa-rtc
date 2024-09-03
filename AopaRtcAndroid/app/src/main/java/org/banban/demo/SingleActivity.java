package org.banban.demo;

import android.content.Intent;
import android.graphics.Rect;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;
import android.view.SurfaceView;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.FrameLayout;
import android.widget.TextView;
import android.widget.Toast;

import org.banban.demo.stats.StatsManager;
import org.banban.demo.stats.StatsData;
import org.banban.demo.stats.LocalStatsData;
import org.banban.demo.stats.RemoteStatsData;

import org.banban.rtc.Constants;
import org.banban.rtc.IRtcEngineEventHandler;
import org.banban.rtc.RtcEngine;

import org.banban.rtc.engine.UserInfo;
import org.banban.rtc.video.CameraCapturerConfiguration;
import org.banban.rtc.video.VideoCanvas;
import org.banban.rtc.video.VideoEncoderConfiguration;
import org.webrtc.SurfaceViewRenderer;
import org.webrtc.TextureViewRenderer;

import androidx.appcompat.app.AppCompatActivity;

import static android.widget.Toast.LENGTH_SHORT;
import static org.banban.rtc.Constants.AUDIO_REVERB_KTV;
import static org.banban.rtc.Constants.CHANNEL_PROFILE_LIVE_BROADCASTING;
import static org.banban.rtc.Constants.CONNECTION_CHANGED_BANNED_BY_SERVER;
import static org.banban.rtc.Constants.CONNECTION_CHANGED_CLIENT_IP_ADDRESS_CHANGED;
import static org.banban.rtc.Constants.CONNECTION_CHANGED_INTERRUPTED;
import static org.banban.rtc.Constants.CONNECTION_CHANGED_INVALID_APP_ID;
import static org.banban.rtc.Constants.CONNECTION_CHANGED_INVALID_CHANNEL_NAME;
import static org.banban.rtc.Constants.CONNECTION_CHANGED_INVALID_TOKEN;
import static org.banban.rtc.Constants.CONNECTION_CHANGED_JOIN_FAILED;
import static org.banban.rtc.Constants.CONNECTION_CHANGED_JOIN_SUCCESS;
import static org.banban.rtc.Constants.CONNECTION_CHANGED_KEEP_ALIVE_TIMEOUT;
import static org.banban.rtc.Constants.CONNECTION_CHANGED_LEAVE_CHANNEL;
import static org.banban.rtc.Constants.CONNECTION_CHANGED_REJECTED_BY_SERVER;
import static org.banban.rtc.Constants.CONNECTION_CHANGED_TOKEN_EXPIRED;
import static org.banban.rtc.Constants.CONNECTION_STATE_CONNECTED;
import static org.banban.rtc.Constants.CONNECTION_STATE_CONNECTING;
import static org.banban.rtc.Constants.CONNECTION_STATE_DISCONNECTED;
import static org.banban.rtc.Constants.CONNECTION_STATE_FAILED;
import static org.banban.rtc.Constants.CONNECTION_STATE_RECONNECTING;
import static org.banban.rtc.Constants.MEDIA_ENGINE_AUDIO_ERROR_MIXING_OPEN;
import static org.banban.rtc.Constants.MEDIA_ENGINE_AUDIO_EVENT_MIXING_ERROR;
import static org.banban.rtc.Constants.MEDIA_ENGINE_AUDIO_EVENT_MIXING_INTERRUPTED_EOF;
import static org.banban.rtc.Constants.MEDIA_ENGINE_AUDIO_EVENT_MIXING_NETWORK_UNSTABLE;
import static org.banban.rtc.Constants.MEDIA_ENGINE_AUDIO_EVENT_MIXING_PAUSED;
import static org.banban.rtc.Constants.MEDIA_ENGINE_AUDIO_EVENT_MIXING_PLAY;
import static org.banban.rtc.Constants.MEDIA_ENGINE_AUDIO_EVENT_MIXING_RESTART;
import static org.banban.rtc.Constants.MEDIA_ENGINE_AUDIO_EVENT_MIXING_STOPPED;
import static org.banban.rtc.Constants.RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL_IS_NULL;
import static org.banban.rtc.Constants.RELAY_OK;
import static org.banban.rtc.Constants.RELAY_STATE_FAILURE;
import static org.banban.rtc.Constants.RELAY_STATE_RUNNING;

public class SingleActivity extends AppCompatActivity {
    private final String TAG = "SingleActivity";
    private Drawable mDefualtDrawable;
    private Drawable mRedDrawable;
    private FrameLayout mRemoteViewContainer;
    private TextView mStatsTextView;
    private TextView mStateTextView;
    private View mVadStateView;
    private String mRoomId;
    private int mUserId;
    private int mQualityType;
    private int mRoleType;
    private int mResolutionType;
    private String mToken;
    private int mVadState = 0;
    private boolean mIsExitRoom = true;
    private RtcEngineEventImpl mRtcEngineEventImpl;
    private StatsManager mStatsManager = new StatsManager();
    private Handler mHandler;
    private boolean mIsSpeaker;
    private boolean mIsInear;
    private boolean mReverbEnabled;
    private boolean mVideoEnabled;
    private boolean mQuicEnabled;
    private boolean mStatsEnabled;
    private int audioScenario = Constants.AUDIO_SCENARIO_SHOWROOM;
    private int mRemoteUid = -1;
    private TextureViewRenderer mSurfaceView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        supportRequestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.activity_single);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        mHandler = new Handler();
        Intent intent = getIntent();
        mUserId = intent.getIntExtra("userId", 0);
        mRoomId = intent.getStringExtra("roomId");
        mQualityType = intent.getIntExtra("qualityType", 0);
        mRoleType = intent.getIntExtra("roleType", 0);
        mResolutionType = intent.getIntExtra("resolution", 0);
        mToken = intent.getStringExtra("token");
        mIsSpeaker = intent.getBooleanExtra("speaker", false);
        mIsInear = intent.getBooleanExtra("inear", false);
        mReverbEnabled = intent.getBooleanExtra("reverb", false);
        mVideoEnabled = intent.getBooleanExtra("videoEnabled", true);
        mQuicEnabled = intent.getBooleanExtra("quic", true);
        mStatsEnabled = intent.getBooleanExtra("stats", true);
        mStateTextView = findViewById(R.id.stateTextView);
        mVadStateView = findViewById(R.id.vadView);
        mStatsTextView = findViewById(R.id.statsTextView);
        mRemoteViewContainer = findViewById(R.id.remote_video_view);

        if(RtcEngine.getInstance() == null){
            mHandler.postDelayed(()->{finish();}, 100);
            return;
        }
        mStatsManager.enableStats(mStatsEnabled);
        mRtcEngineEventImpl = new RtcEngineEventImpl();
        RtcEngine.getInstance().addHandler(mRtcEngineEventImpl);
        RtcEngine.getInstance().enableAudio();
        RtcEngine.getInstance().enableVideo();
        RtcEngine.getInstance().setClientRole(mRoleType);
        RtcEngine.getInstance().setChannelProfile(CHANNEL_PROFILE_LIVE_BROADCASTING);
        RtcEngine.getInstance().setAudioProfile(mQualityType, audioScenario);
        if(mVideoEnabled){
            CameraCapturerConfiguration.CaptureDimensions dimensions = CameraCapturerConfiguration.CD_640x480;
            if (mResolutionType == 0) {
                dimensions = new CameraCapturerConfiguration.CaptureDimensions(640, 360);
            } else if (mResolutionType == 1) {
                dimensions = new CameraCapturerConfiguration.CaptureDimensions(640, 480);
            }  else if (mResolutionType == 2) {
                dimensions = new CameraCapturerConfiguration.CaptureDimensions(960, 540);
            } else if (mResolutionType == 3) {
                dimensions = new CameraCapturerConfiguration.CaptureDimensions(1280, 720);
            } else if (mResolutionType == 4) {
                dimensions = new CameraCapturerConfiguration.CaptureDimensions(1080, 1920);
            }else {
                dimensions = new CameraCapturerConfiguration.CaptureDimensions(640, 360);
            }
            VideoEncoderConfiguration videoConfig = new VideoEncoderConfiguration();
            videoConfig.dimensions.width = dimensions.width;
            videoConfig.dimensions.height = dimensions.height;
            videoConfig.frameRate = 15;
            videoConfig.minFrameRate = 5;
            videoConfig.orientationMode = VideoEncoderConfiguration.ORIENTATION_MODE.ORIENTATION_MODE_FIXED_PORTRAIT;
            videoConfig.degradationPrefer = VideoEncoderConfiguration.DEGRADATION_PREFERENCE.MAINTAIN_FRAMERATE;

            RtcEngine.getInstance().setVideoEncoderConfiguration(videoConfig);
            RtcEngine.getInstance().enableLocalVideo(true);
        }
        else{
            RtcEngine.getInstance().enableLocalVideo(false);
        }
        if(intent.getBooleanExtra("multicast", false)){
            RtcEngine.getInstance().enableDualStreamMode(true);
        }
        RtcEngine.getInstance().setDefaultAudioRouteToSpeakerphone(mIsSpeaker);
        if (mRoleType == 1 && mReverbEnabled){
            RtcEngine.getInstance().setLocalVoiceReverbPreset(AUDIO_REVERB_KTV);
        }
        if(!intent.getBooleanExtra("3A", true)){
            RtcEngine.getInstance().setParameters("{\"che.audio.enable.3a\":false}");
        }
        if(intent.getBooleanExtra("detach", true)){
            RtcEngine.getInstance().setParameters("{\"che.media.detach\":true}");
        }else{
            RtcEngine.getInstance().setParameters("{\"che.media.detach\":false}");
        }
        RtcEngine.getInstance().setParameters(String.format("{\"che.network.enable.quic\":%b}", mQuicEnabled));
        int ret = RtcEngine.getInstance().joinChannel(mToken, mRoomId, "", mUserId);
        if (ret != 0){
            Log.e(TAG, "JoinChannel failed, " + ret);
        }

        RtcEngine.getInstance().enableInEarMonitoring(mIsInear);
        RtcEngine.getInstance().enableAudioVolumeIndication(500, 3, true);

        mDefualtDrawable = getResources().getDrawable(R.drawable.bnt_shape_default);
        mRedDrawable = getResources().getDrawable(R.drawable.btn_shape);
        mVadStateView.setBackground(mDefualtDrawable);
        mIsExitRoom = false;
        RefreshStats();
        setRemoteVideoView(mUserId);
    }

    @Override
    protected void onStop() {
        super.onStop();
        exitRoom();
        RtcEngine.destroy();
        Log.i(TAG, "onStop");
    }

    public void RefreshStats() {
        mHandler.postDelayed(()->{
            if (mStatsManager != null && mStatsManager.isEnabled()) {
                if (mStatsTextView != null) {
                    StatsData data = mStatsManager.getStatsData(mRemoteUid);
                    String info = data != null ? data.toString() : null;
                    if (info != null) mStatsTextView.setText(info);
                }
                RefreshStats();
            }}, 2000);
    }

    private void setRemoteVideoView(int uid) {
        if(RtcEngine.getInstance() == null) return;
        TextureViewRenderer surfaceView = (TextureViewRenderer)RtcEngine.CreateTextureView(getApplicationContext());
        if(uid == mUserId){
            RtcEngine.getInstance().setupLocalVideo(new VideoCanvas(
                    surfaceView, VideoCanvas.RENDER_MODE_HIDDEN, uid));
        }else{
            RtcEngine.getInstance().setupRemoteVideo(new VideoCanvas(
                    surfaceView, VideoCanvas.RENDER_MODE_HIDDEN, uid));
        }
        mSurfaceView = surfaceView;
        mRemoteViewContainer.addView(surfaceView);
    }

    private void onRemoteUserLeft() {
        mStatsManager.removeUserStats(mRemoteUid);
        mRemoteUid = -1;
        mRemoteViewContainer.removeAllViews();
    }

    public void onCameraSwitchClick(View view){
        if(RtcEngine.getInstance() == null) return ;
        RtcEngine.getInstance().switchCamera();
    }

    private void exitRoom(){
        Log.i(TAG, "exitRoom");
        if(mIsExitRoom)
            return;
        mIsExitRoom = true;
        if(RtcEngine.getInstance() != null){
            RtcEngine.getInstance().enableLocalVideo(false);
            RtcEngine.getInstance().leaveChannel();
            RtcEngine.getInstance().removeHandler(mRtcEngineEventImpl);
        }
        finish();
    }

    public void onExitRoomClick(View view){
        exitRoom();
    }

    @Override
    public void onBackPressed() {
        exitRoom();
    }

    void showToast(String msg){
        if (Thread.currentThread() == Looper.getMainLooper().getThread()) {
            Toast.makeText(getApplicationContext(), msg, LENGTH_SHORT).show();
        }
        else{
            mHandler.post(()->{
                Toast.makeText(getApplicationContext(), msg, LENGTH_SHORT).show();
            });
        }
    }

    private class RtcEngineEventImpl extends IRtcEngineEventHandler {
        public RtcEngineEventImpl(){

        }
        @Override public void  onWarning(int warn) {
        }

        @Override public void  onError(int err) {
            showToast("错误:" + err);
        }

        @Override public void  onJoinChannelSuccess(String channel, int uid, int elapsed) {
            mHandler.post(()-> {
                mStateTextView.setText("join room suc");
            });
            Log.i(TAG, "+++ onJoinChannelSuccess channelid:" + channel + " uid:" + uid + " elapsed:" + elapsed);
        }

        @Override public void  onRejoinChannelSuccess(String channel, int uid, int elapsed) {
            mHandler.post(()-> {
                mStateTextView.setText("rejoin room suc");
            });
            Log.i(TAG, "+++ onRejoinChannelSuccess channelid:" + channel + " uid:" + uid + " elapsed:" + elapsed);
        }

        @Override public void  onLeaveChannel(IRtcEngineEventHandler.RtcStats stats) {
            mHandler.post(()->{
                mStateTextView.setText("exit room suc");
            });
        }

        @Override public void  onClientRoleChanged(int oldRole, int newRole) {
            showToast("role change:" + oldRole + "->" + newRole);
        }

        @Override public void  onUserJoined(int uid, int elapsed) {
            if (mRemoteUid == -1) {
                runOnUiThread(() -> {
                    mRemoteUid = uid;
                    mStatsManager.addUserStats(mRemoteUid, false);
                    setRemoteVideoView(uid);
                });
            }
        }

        @Override public void  onUserOffline(int uid, int reason) {
            mHandler.post(()->{
                onRemoteUserLeft();
            });
        }
    
    @Override public void  onConnectionStateChanged(int state, int reason) {
        Log.i(TAG, "onConnectionStateChanged state:" + state);
        if(mIsExitRoom)
          return;
        mHandler.post(()->{
          if(mIsExitRoom)
            return;
          switch(state){
            case CONNECTION_STATE_DISCONNECTED:
            {
              switch (reason) {
                case CONNECTION_CHANGED_INTERRUPTED:
                  mStateTextView.setText("disconnect, net error");
                  break;
                case CONNECTION_CHANGED_JOIN_FAILED:
                  mStateTextView.setText("disconnect, joinroom fail ");
                  break;
                case CONNECTION_CHANGED_LEAVE_CHANNEL:
                  mStateTextView.setText("disconnect, leave room ");
                  break;
                case CONNECTION_CHANGED_INVALID_CHANNEL_NAME:
                  mStateTextView.setText("disconnect, invalid room ");
                  break;
                case CONNECTION_CHANGED_BANNED_BY_SERVER:
                  mStateTextView.setText("disconnect, be kicked");
                  showToast("你已被踢出");
                  break;
                case CONNECTION_CHANGED_KEEP_ALIVE_TIMEOUT:
                  mStateTextView.setText("disconnect, heatbeat timeout ");
                  break;
                case CONNECTION_CHANGED_INVALID_APP_ID:
                  mStateTextView.setText("disconnect, invalidAPPID");
                  break;
                case CONNECTION_CHANGED_TOKEN_EXPIRED:
                  mStateTextView.setText("disconnect,Token timeout");
                  break;
                case CONNECTION_CHANGED_INVALID_TOKEN:
                  mStateTextView.setText("disconnect, invalid token");
                  break;
                case CONNECTION_CHANGED_REJECTED_BY_SERVER:
                  mStateTextView.setText("disconnect, multi device join");
                  break;
                case CONNECTION_CHANGED_CLIENT_IP_ADDRESS_CHANGED:
                  mStateTextView.setText("disconnect, net change");
                  break;
                default:
                  mStateTextView.setText("disconnect");
                  break;
              }
            }break;
            case CONNECTION_STATE_CONNECTING:
              switch (reason) {
                case CONNECTION_CHANGED_JOIN_SUCCESS:
                  mStateTextView.setText("connecting，join room suc... ");
                  break;
                default:
                  mStateTextView.setText("connectting... ");
                  break;
              }
              break;
            case CONNECTION_STATE_CONNECTED:
              mStateTextView.setText("join suc ");
              break;
            case CONNECTION_STATE_RECONNECTING:
              mStateTextView.setText("reconnecting... ");
              break;
            case CONNECTION_STATE_FAILED:
              mStateTextView.setText("connect failed");
              if(RtcEngine.getInstance() != null)
                 RtcEngine.getInstance().leaveChannel();
              break;
          }
        });
      }
  
        @Override public void  onConnectionLost() {
            showToast("connect lost");
        }


        @Override public void  onApiCallExecuted(int error, String api, String result) {
        }

        @Override public void  onTokenPrivilegeWillExpire(String token) {
        }

        @Override public void  onRequestToken() {
        }

        @Override public void  onAudioVolumeIndication(IRtcEngineEventHandler.AudioVolumeInfo[] speakers, int totalVolume) {
            if (speakers.length == 0)
                return;
            mHandler.post(()->{
                if(mVadState != speakers[0].vad){
                    mVadStateView.setBackground(speakers[0].vad == 0 ? mDefualtDrawable : mRedDrawable);
                    mVadState = speakers[0].vad;
                }
            });
        }

        @Override public void  onActiveSpeaker(int uid) {

        }

        @Override public void  onFirstLocalAudioFrame(int elapsed) {
            Log.i(TAG,"+++ onFirstLocalAudioFrame elapsed:" + elapsed);
        }

        @Override public void  onFirstLocalVideoFrame(int width, int height, int elapsed) {
            Log.i(TAG,"+++ onFirstLocalVideoFrame width:" + width + ", height:" + height  + ", elapsed:" + elapsed);
        }

        @Override public void onFirstRemoteVideoFrame(int uid, int width, int height, int elapsed) {
            Log.i(TAG,"+++ onFirstRemoteVideoFrame uid:" + uid + ", width:" + width + ", height:" + height  + ", elapsed:" + elapsed);
        }

        @Override public void  onVideoSizeChanged(int uid, int width, int height, int rotation) {
        }

        @Override public void  onRemoteAudioStateChanged(int uid, int state, int reason, int elapsed) {
            Log.i(TAG,"+++ onRemoteAudioStateChanged uid:" + uid + ", state:" + state + ", reason:" + reason + ", elapsed:" + elapsed);
        }

        @Override public void  onRemoteVideoStateChanged(int uid, int state, int reason, int elapsed) {
            Log.i(TAG,"+++ onRemoteVideoStateChanged uid:" + uid + ", state:" + state + ", reason:" + reason + ", elapsed:" + elapsed);
        }

        @Override public void  onChannelMediaRelayStateChanged(int state, int code) {
            Log.i(TAG, "channelMediaRelayStateDidChange state:" + state + ", code:" + code);
            mHandler.post(()-> {
                if (state == RELAY_STATE_RUNNING && code == RELAY_OK) {
                    mStateTextView.setText("media releay suc");
                } else if (state == RELAY_STATE_FAILURE) {
                    mStateTextView.setText("media reley failed, code:" + code);
                }
            });
        }

        @Override public void  onChannelMediaRelayEvent(int code) {
            Log.i(TAG, "didReceiveChannelMediaRelayEvent event:" + code);
            mHandler.post(()-> {
                if (code == RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL_IS_NULL) {
                    mStateTextView.setText("media relay failed,room not exit");
                } else {
                    mStateTextView.setText("media relay, event:" + code);
                }
            });
        }

        @Override public void  onLocalPublishFallbackToAudioOnly(boolean isFallbackOrRecover) {
        }

        @Override public void  onRemoteSubscribeFallbackToAudioOnly(int uid, boolean isFallbackOrRecover) {
        }

        @Override public void  onAudioRouteChanged(int routing) {
            showToast("audio route change:" + routing);
        }

        @Override public void  onCameraFocusAreaChanged(Rect rect) {
        }

        @Override public void  onCameraExposureAreaChanged(Rect rect) {
        }

        @Override public void  onRtcStats(IRtcEngineEventHandler.RtcStats stats) {
            LocalStatsData data = (LocalStatsData) mStatsManager.getStatsData(mUserId);
            if (data == null) return;

            data.setLastMileDelay(stats.lastmileDelay);
            data.setVideoSendBitrate(stats.txKBitRate);
            data.setVideoRecvBitrate(stats.rxKBitRate);
            data.setSendLoss(stats.txPacketLossRate);
            data.setRecvLoss(stats.rxPacketLossRate);
        }

        @Override public void  onLastmileQuality(int quality) {
        }

        @Override public void  onNetworkQuality(int uid, int txQuality, int rxQuality) {
            StatsData data = mStatsManager.getStatsData(uid);
            if (data == null) return;

            data.setSendQuality(mStatsManager.qualityToString(txQuality));
            data.setRecvQuality(mStatsManager.qualityToString(rxQuality));
        }

        @Override public void  onLocalVideoStats(IRtcEngineEventHandler.LocalVideoStats stats) {
            LocalStatsData data = (LocalStatsData) mStatsManager.getStatsData(mUserId);
            if (data == null) return;

            data.setWidth(stats.encodedFrameWidth);
            data.setHeight(stats.encodedFrameHeight);
            data.setFramerate(stats.sentFrameRate);
        }

        @Override public void  onRemoteVideoStats(IRtcEngineEventHandler.RemoteVideoStats stats) {
            RemoteStatsData data = (RemoteStatsData) mStatsManager.getStatsData(stats.uid);
            if (data == null) return;

            data.setWidth(stats.width);
            data.setHeight(stats.height);
            data.setFramerate(stats.rendererOutputFrameRate);
            data.setVideoRx(stats.receivedBitrate);
            data.setVideoDelay(stats.delay);
        }

        @Override public void  onLocalAudioStats(IRtcEngineEventHandler.LocalAudioStats stats) {
            LocalStatsData data = (LocalStatsData) mStatsManager.getStatsData(mUserId);
            if (data == null) return;
        }

        @Override public void  onRemoteAudioStats(IRtcEngineEventHandler.RemoteAudioStats stats) {
            RemoteStatsData data = (RemoteStatsData) mStatsManager.getStatsData(stats.uid);
            if (data == null) return;

            data.setAudioRx(stats.receivedBitrate);
            data.setAudioNetDelay(stats.networkTransportDelay);
            data.setAudioNetJitter(stats.jitterBufferDelay);
            data.setAudioLoss(stats.audioLossRate);
            data.setAudioQuality(mStatsManager.qualityToString(stats.quality));
        }

        @Override public void onAudioSubscribeStateChanged(String channel, int uid, int oldState, int newState, int elapseSinceLastState) {
            Log.i(TAG, "onAudioSubscribeStateChanged uid:" + uid + ", oldState:" + oldState + ", newState:" + newState + ", tm:" + elapseSinceLastState);
        }

        @Override public void onVideoSubscribeStateChanged(String channel, int uid, int oldState, int newState, int elapseSinceLastState) {
            Log.i(TAG, "onVideoSubscribeStateChanged uid:" + uid + ", oldState:" + oldState + ", newState:" + newState + ", tm:" + elapseSinceLastState);
        }

        @Override public void  onAudioMixingStateChanged(int state, int errorCode) {
            mHandler.post(()-> {
                switch (state) {
                    case MEDIA_ENGINE_AUDIO_EVENT_MIXING_PLAY:
                        showToast("play auido suc");
                        break;
                    case MEDIA_ENGINE_AUDIO_EVENT_MIXING_PAUSED:
                        showToast("play auido pause");
                        break;
                    case MEDIA_ENGINE_AUDIO_EVENT_MIXING_RESTART:
                        showToast("play auido resume");
                        break;
                    case MEDIA_ENGINE_AUDIO_EVENT_MIXING_STOPPED:
                        showToast("play auido ended");
                        break;
                    case MEDIA_ENGINE_AUDIO_EVENT_MIXING_ERROR:
                        switch (errorCode) {
                            case MEDIA_ENGINE_AUDIO_ERROR_MIXING_OPEN:
                                showToast("play auido open failed");
                                break;
                            case MEDIA_ENGINE_AUDIO_EVENT_MIXING_INTERRUPTED_EOF:
                                showToast("play auido interrupt");
                                break;
                            case MEDIA_ENGINE_AUDIO_EVENT_MIXING_NETWORK_UNSTABLE:
                                showToast("play auido bad network");
                                break;
                        }
                        break;
                }
            });
        }


        @Override public void  onAudioEffectFinished(int soundId) {
            Log.i(TAG, "onAudioEffectFinished soundId:" + soundId);
        }


        @Override public void  onLocalAudioStateChanged(int state, int error) {
            showToast("local audio route change:" + state);
        }

        @Override public void  onLocalVideoStateChanged(int localVideoState, int error) {
        }

        @Override public void  onRtmpStreamingStateChanged(String url, int state, int errCode) {
        }

        @Override public void  onTranscodingUpdated() {
        }

        @Override public void  onStreamInjectedStatus(String url, int uid, int status) {
        }

        @Override public void  onStreamMessage(int uid, int streamId, byte[] data) {
        }

        @Override public void  onStreamMessageError(int uid, int streamId, int error, int missed, int cached) {
        }

        @Override public void  onMediaEngineLoadSuccess() {
        }

        @Override public void  onMediaEngineStartCallSuccess() {
        }

        @Override public void  onNetworkTypeChanged(int type) {
            showToast("net type change:" + type);
        }

    }
}

