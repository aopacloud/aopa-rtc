package com.aopa.aopartcandroid;

import static android.widget.Toast.LENGTH_SHORT;
import static org.banban.rtc.Constants.CHANNEL_PROFILE_LIVE_BROADCASTING;
import static org.banban.rtc.Constants.CLIENT_ROLE_AUDIENCE;
import static org.banban.rtc.Constants.CLIENT_ROLE_BROADCASTER;
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
import static org.banban.rtc.Constants.REMOTE_AUDIO_REASON_LOCAL_MUTED;
import static org.banban.rtc.Constants.REMOTE_AUDIO_REASON_LOCAL_UNMUTED;
import static org.banban.rtc.Constants.REMOTE_AUDIO_REASON_NETWORK_RECOVERY;
import static org.banban.rtc.Constants.REMOTE_AUDIO_REASON_REMOTE_MUTED;
import static org.banban.rtc.Constants.REMOTE_AUDIO_REASON_REMOTE_OFFLINE;
import static org.banban.rtc.Constants.REMOTE_AUDIO_REASON_REMOTE_UNMUTED;
import static org.banban.rtc.Constants.REMOTE_AUDIO_STATE_DECODING;
import static org.banban.rtc.Constants.REMOTE_AUDIO_STATE_FAILED;
import static org.banban.rtc.Constants.REMOTE_AUDIO_STATE_FROZEN;
import static org.banban.rtc.Constants.REMOTE_AUDIO_STATE_STARTING;
import static org.banban.rtc.Constants.REMOTE_AUDIO_STATE_STOPPED;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.ContentUris;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.database.Cursor;
import android.graphics.Rect;
import android.graphics.drawable.Drawable;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Looper;
import android.provider.DocumentsContract;
import android.provider.MediaStore;
import android.util.Log;
import android.view.SurfaceView;
import android.view.TextureView;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.view.WindowManager;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.RelativeLayout;
import android.widget.SeekBar;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.CallSuper;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.RecyclerView;
import androidx.recyclerview.widget.SimpleItemAnimator;
import androidx.recyclerview.widget.StaggeredGridLayoutManager;

import org.banban.rtc.Constants;
import org.banban.rtc.IRtcEngineEventHandler;
import org.banban.rtc.RtcEngine;
import org.banban.rtc.video.CameraCapturerConfiguration;
import org.banban.rtc.video.ChannelMediaInfo;
import org.banban.rtc.video.ChannelMediaRelayConfiguration;
import org.banban.rtc.video.VideoCanvas;
import org.banban.rtc.video.VideoEncoderConfiguration;
import org.webrtc.TextureViewRenderer;

import java.util.ArrayList;
import java.util.Timer;
import java.util.TimerTask;

import com.aopa.aopartcandroid.stats.LocalStatsData;
import com.aopa.aopartcandroid.stats.RemoteStatsData;
import com.aopa.aopartcandroid.stats.StatsData;
import com.aopa.aopartcandroid.stats.StatsManager;

public class RoomActivity extends AppCompatActivity implements UserViewInterface {
  private final String TAG = "RoomActivity";
  private Drawable mDefaultDrawable;
  private Drawable mRedDrawable;
  private RecyclerView mRecyclerView;
  private SimpleRecycleAdapter mSimpleRecycleAdapter;
  private TextView mStateTextView;
  private View mVadStateView;
  private TextView mLocalVolumeTextView;
  private TextView mRemoteVolumeTextView;
  private Button mRoleSwitchButton;
  private Button mAudioSwitchButton;
  private Button mVideoSwitchButton;
  private Button mCameraSwitchButton;
  private Button mRelayMediaButton;
  private SeekBar mPlayBackSeekBar;
  private SeekBar mRecordSeekBar;
  private TextView mMusicVolumeTextView;
  private SeekBar mMusicVolumeSeekBar;
  private EditText mMusicNameEditText;
  private SeekBar mMusicSeekBar;
  private TextView mMusicTotalTimeTextView;
  private TextView mMusicCurrentTimeTextView;
  private TextView mInearVolumeTextView;
  private SeekBar mInearVolumeSeekBar;
  private Button mMusicPlayButton;
  private Button mMusicPauseButton;
  private Button mMusicSelectButton;
  private String mRoomId;
  private int mUserId;
  private int mQualityType;
  private int mRoleType;
  private int mResolutionType;
  private String mToken;
  private boolean mMuteLocalAudioStream = false;
  private boolean mEnableLocalVideo = false;
  private boolean mRelayState = false;
  private int mVadState = 0;
  private int mMusicTotalTimeMs = 0;
  private boolean mMusicIsPlayed = false;
  private boolean mMusicIsPause = false;
  private RtcEngineEventImpl mRtcEngineEventImpl;
  private StatsManager mStatsManager = new StatsManager();
  private Handler mHandler;
  private Timer mMusicTimer;
  private boolean mIsSpeaker;
  private boolean mVideoEnabled;
  private boolean mStatsEnabled = false;
  private Spinner mSpinnerQuality;
  private Object timeLock = new Object();
  private int mAudioScenario = Constants.AUDIO_SCENARIO_CHORUS;

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    supportRequestWindowFeature(Window.FEATURE_NO_TITLE);
    setContentView(R.layout.activity_room);
    getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
    mHandler = new Handler();
    Intent intent = getIntent();
    mUserId = intent.getIntExtra("userId", 0);
    mRoomId = intent.getStringExtra("roomId");
    mQualityType = intent.getIntExtra("qualityType", 0);
    mRoleType = intent.getIntExtra("roleType", 0);
    mResolutionType = intent.getIntExtra("resolution", 0);
    mIsSpeaker = intent.getBooleanExtra("speaker", false);
    mVideoEnabled = intent.getBooleanExtra("videoEnabled", true);
    mStateTextView = findViewById(R.id.stateTextView);
    mVadStateView = findViewById(R.id.vadView);
    mLocalVolumeTextView = findViewById(R.id.RecordVolumeValue);
    mRemoteVolumeTextView = findViewById(R.id.PlayBackVolumeValue);
    mRoleSwitchButton = findViewById(R.id.roleSwitchButton);
    mAudioSwitchButton = findViewById(R.id.audioSwitchButton);
    mVideoSwitchButton = findViewById(R.id.videoSwitchButton);
    mCameraSwitchButton = findViewById(R.id.cameraSwitchButton);
    mRelayMediaButton = findViewById(R.id.relaySwitchButton);
    mRecyclerView = findViewById(R.id.recycler_view);
    mMusicNameEditText = findViewById(R.id.MusicFileEditText);
    mMusicSeekBar = findViewById(R.id.MusicSeekBar);
    mMusicPlayButton = findViewById(R.id.MusicPlayButton);
    mMusicPauseButton = findViewById(R.id.MusicPauseButton);
    mMusicSelectButton = findViewById(R.id.MusicSelectButton);
    mMusicTotalTimeTextView = findViewById(R.id.MusicTotalTimeTextView);
    mMusicCurrentTimeTextView = findViewById(R.id.MusicCurrentTimeTextView);
    mMusicVolumeTextView = findViewById(R.id.MusicVolumeValue);
    mMusicVolumeSeekBar = findViewById(R.id.MusicVolumeSeekBar);
    mInearVolumeTextView = findViewById(R.id.InearVolumeValue);
    mInearVolumeSeekBar = findViewById(R.id.InearVolumeSeekBar);
    mSpinnerQuality = findViewById(R.id.AudioQualitySpinner);
    int audioScenario = intent.getIntExtra("scenarioType", 0);
    if(audioScenario == 0){
      mAudioScenario = Constants.AUDIO_SCENARIO_SHOWROOM;
    }else if(audioScenario == 1){
      mAudioScenario = Constants.AUDIO_SCENARIO_GAME_STREAMING;
    }else if(audioScenario == 2){
      mAudioScenario = Constants.AUDIO_SCENARIO_CHORUS;
      //Need to add local accompaniment file
      //...
    }

    String[] quelityTypes = new String[]{"default", "32kMono", "48kMono", "48kStero", "48kMonoHighQulity", "48kSteroHighQulity"};
    ArrayAdapter<String> quelityAdapter = new ArrayAdapter<String>(getApplicationContext(), android.R.layout.simple_spinner_item, quelityTypes);
    quelityAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
    mSpinnerQuality.setAdapter(quelityAdapter);
    mSpinnerQuality.setSelection(mQualityType);

    mSimpleRecycleAdapter = new SimpleRecycleAdapter(getApplicationContext(), this, mStatsManager);
    mRecyclerView.setAdapter(mSimpleRecycleAdapter);
    StaggeredGridLayoutManager layoutManager = new StaggeredGridLayoutManager(2,StaggeredGridLayoutManager.VERTICAL);
    mRecyclerView.setLayoutManager(layoutManager);
    mRecyclerView.addItemDecoration(new SpaceItemDecoration(10, 10));
    mRecyclerView.setItemViewCacheSize(0);
    ((SimpleItemAnimator)mRecyclerView.getItemAnimator()).setSupportsChangeAnimations(false);
    mStatsManager.enableStats(mStatsEnabled);
    mRtcEngineEventImpl = new RtcEngineEventImpl();
    mDefaultDrawable = getResources().getDrawable(R.drawable.bnt_shape_default);
    mRedDrawable = getResources().getDrawable(R.drawable.btn_shape);
    mVadStateView.setBackground(mDefaultDrawable);
    mRecordSeekBar = findViewById(R.id.RecordSeekBar);
    mRecordSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
      @Override
      public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
        if(RtcEngine.getInstance() == null) return ;
        mLocalVolumeTextView.setText(Integer.toString(progress));
        RtcEngine.getInstance().adjustRecordingSignalVolume(progress);
      }

      @Override
      public void onStartTrackingTouch(SeekBar seekBar) {
      }

      @Override
      public void onStopTrackingTouch(SeekBar seekBar) {
      }
    });

    mPlayBackSeekBar = findViewById(R.id.PlayBackSeekBar);
    mPlayBackSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
      @Override
      public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
        if(RtcEngine.getInstance() == null) return ;
        mRemoteVolumeTextView.setText(Integer.toString(progress));
        RtcEngine.getInstance().adjustPlaybackSignalVolume(progress);
      }

      @Override
      public void onStartTrackingTouch(SeekBar seekBar) {
      }

      @Override
      public void onStopTrackingTouch(SeekBar seekBar) {

      }
    });

    mMusicSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
      @Override
      public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
      }

      @Override
      public void onStartTrackingTouch(SeekBar seekBar) {
      }

      @Override
      public void onStopTrackingTouch(SeekBar seekBar) {
        if(RtcEngine.getInstance() == null) return ;
        if (!mMusicIsPlayed)
          return;
        int pos = (int)(mMusicTotalTimeMs*(seekBar.getProgress() *1.0f/100));
        RtcEngine.getInstance().setAudioMixingPosition(pos);
      }
    });

    mInearVolumeSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
      @Override
      public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
        if(RtcEngine.getInstance() == null) return ;
        mInearVolumeTextView.setText(Integer.toString(progress));
        RtcEngine.getInstance().setInEarMonitoringVolume(progress);
      }

      @Override
      public void onStartTrackingTouch(SeekBar seekBar) {
      }

      @Override
      public void onStopTrackingTouch(SeekBar seekBar) {

      }
    });

    mMusicVolumeSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
      @Override
      public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
        if(RtcEngine.getInstance() == null) return ;
        mMusicVolumeTextView.setText(Integer.toString(progress));
        RtcEngine.getInstance().adjustAudioMixingVolume(progress);
      }

      @Override
      public void onStartTrackingTouch(SeekBar seekBar) {
      }

      @Override
      public void onStopTrackingTouch(SeekBar seekBar) {

      }
    });
    mSpinnerQuality.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener(){
      @Override
      public void onItemSelected(AdapterView<?> parent,View view, int position, long id){
        if(view == null) return;
        TextView tv = (TextView)view;
        tv.setTextSize(12.0f);
        mQualityType = position;
        RtcEngine.getInstance().setAudioProfile(mQualityType, mAudioScenario);
      }
      @Override
      public void onNothingSelected(AdapterView<?>parent){}
    });

    joinRoom();
    mRoleSwitchButton.setText(mRoleType == CLIENT_ROLE_BROADCASTER ? "down" : "up");
    mAudioSwitchButton.setText(mMuteLocalAudioStream ? "voice on" : "voice off");
    mVideoSwitchButton.setText(mEnableLocalVideo ? "video off" : "video on");
    updateStatus(mRoleType == CLIENT_ROLE_BROADCASTER);
  }

  private void joinRoom(){
    try {
      String testAppId = "6MHg9hZqMMcKjNyiauSyU8H5b3eTr4qM";
      RtcEngine.create(getApplicationContext(), testAppId, null);
    }catch (Exception e) {
      e.printStackTrace();
      return;
    }
    RtcEngine.getInstance().addHandler(mRtcEngineEventImpl);
    RtcEngine.getInstance().enableAudio();
    RtcEngine.getInstance().setClientRole(mRoleType);
    RtcEngine.getInstance().setChannelProfile(CHANNEL_PROFILE_LIVE_BROADCASTING);
    RtcEngine.getInstance().setAudioProfile(mQualityType, mAudioScenario);
    RtcEngine.getInstance().setDefaultAudioRouteToSpeakerphone(mIsSpeaker);
    if(mVideoEnabled){
      RtcEngine.getInstance().enableVideo();
      CameraCapturerConfiguration.CaptureDimensions dimensions;
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
      CameraCapturerConfiguration cameraConfig = new CameraCapturerConfiguration(dimensions,
              CameraCapturerConfiguration.CAMERA_DIRECTION.CAMERA_FRONT);
      RtcEngine.getInstance().setCameraCapturerConfiguration(cameraConfig);

      VideoEncoderConfiguration videoConfig = new VideoEncoderConfiguration();
      videoConfig.dimensions.width = dimensions.width;
      videoConfig.dimensions.height = dimensions.height;
      videoConfig.frameRate = 15;
      videoConfig.minFrameRate = 5;
      videoConfig.orientationMode = VideoEncoderConfiguration.ORIENTATION_MODE.ORIENTATION_MODE_FIXED_PORTRAIT;
      videoConfig.degradationPrefer = VideoEncoderConfiguration.DEGRADATION_PREFERENCE.MAINTAIN_FRAMERATE;
      RtcEngine.getInstance().setVideoEncoderConfiguration(videoConfig);
      RtcEngine.getInstance().enableVideo();
      RtcEngine.getInstance().enableLocalVideo(true);
      mEnableLocalVideo = true;
    }
    else{
      RtcEngine.getInstance().disableVideo();
      mEnableLocalVideo = false;
    }

    int ret = RtcEngine.getInstance().joinChannel(mToken, mRoomId, "", mUserId);
    if (ret != 0){
      Log.e(TAG, "JoinChannel failed, " + ret);
    }
    if(mRoleType == CLIENT_ROLE_BROADCASTER){
      mMuteLocalAudioStream = true;
      mEnableLocalVideo = mVideoEnabled;
      mSimpleRecycleAdapter.addItem(mUserId, true);
    }
    else{
      mMuteLocalAudioStream = false;
      mEnableLocalVideo = false;
    }
    RtcEngine.getInstance().enableAudioVolumeIndication(500, 3, true);
  }
  private void updateStatus(boolean enabled){
    mMusicNameEditText.setEnabled(false);
    mRelayMediaButton.setEnabled(false);
    mMusicSelectButton.setEnabled(false);
    mRelayMediaButton.setEnabled(enabled);
    mMusicSelectButton.setEnabled(enabled);
    mAudioSwitchButton.setEnabled(enabled);
    mVideoSwitchButton.setEnabled(enabled);
    mCameraSwitchButton.setEnabled(enabled);
    mPlayBackSeekBar.setEnabled(enabled);
    mRecordSeekBar.setEnabled(enabled);
    mMusicVolumeTextView.setEnabled(enabled);
    mMusicVolumeSeekBar.setEnabled(enabled);
    mMusicSeekBar.setEnabled(enabled);
    mMusicPlayButton.setEnabled(enabled);
    mMusicPauseButton.setEnabled(enabled);
  }

  @Override
  protected void onStop() {
    super.onStop();
    Log.i(TAG, "onStop");
  }

  @Override
  public boolean onUserAudioMuteEnable(int userId, boolean mute){
    if (RtcEngine.getInstance().muteRemoteAudioStream(userId, mute) == 0){
      return true;
    }
    return false;
  }

  @Override
  public boolean onUserVideoMuteEnable(int userId, boolean mute){
    if (RtcEngine.getInstance().muteRemoteVideoStream(userId, mute) == 0){
      return true;
    }
    return false;
  }

  @Override
  public boolean onUserVolumeChange(int userId, int volume){
    if (RtcEngine.getInstance().adjustUserPlaybackSignalVolume(userId, volume) == 0){
      return true;
    }
    return false;
  }

  @Override
  public boolean onUserStreamStateChange(int userId, boolean isBig){
    if (RtcEngine.getInstance().setRemoteVideoStreamType(userId, isBig ? 0 : 1) == 0){
      return true;
    }
    return false;
  }

  @Override
  public void onUserAdd(int userId, RelativeLayout layout){
    if(RtcEngine.getInstance() == null) return;
    //SurfaceViewRenderer view = (SurfaceViewRenderer)RtcEngine.createRendererView(getApplicationContext());
    TextureViewRenderer view = (TextureViewRenderer)RtcEngine.CreateTextureView(getApplicationContext());
    layout.addView(view, 0);
    VideoCanvas canvas = new VideoCanvas(view, Constants.RENDER_MODE_HIDDEN, userId, Constants.VIDEO_MIRROR_MODE_DISABLED);
    if(userId == mUserId){
      RtcEngine.getInstance().setupLocalVideo(canvas);
    }else{
      RtcEngine.getInstance().setupRemoteVideo(canvas);
    }
  }

  @Override
  public  void onUserRemoved(int userId, RelativeLayout layout){
    if(layout == null || layout.getChildCount() == 0 || RtcEngine.getInstance() == null)
      return;

    for (int i = 0; i < layout.getChildCount(); i++){
      View view = layout.getChildAt(i);
      if((view instanceof SurfaceView) || (view instanceof TextureView)){
        VideoCanvas canvas = new VideoCanvas(null, Constants.RENDER_MODE_HIDDEN, userId, Constants.VIDEO_MIRROR_MODE_AUTO);
        if(userId == mUserId){
          RtcEngine.getInstance().setupLocalVideo(canvas);
        }else{
          RtcEngine.getInstance().setupRemoteVideo(canvas);
        }
        RtcEngine.releaseRenderView(view);
      }
    }
    layout.removeAllViews();
  }

  public void onRoleSwitchClick(View view){
     if(mRoleType == CLIENT_ROLE_BROADCASTER){
       mRoleType = CLIENT_ROLE_AUDIENCE;
       RtcEngine.getInstance().setClientRole(CLIENT_ROLE_AUDIENCE);
       mRoleSwitchButton.setText("up");
     }else{
       mRoleType = CLIENT_ROLE_BROADCASTER;
       RtcEngine.getInstance().setClientRole(CLIENT_ROLE_BROADCASTER);
       mRoleSwitchButton.setText("down");
     }
     updateStatus(mRoleType == CLIENT_ROLE_BROADCASTER);
  }

  public void onAudioSwitchClick(View view){
    mMuteLocalAudioStream = !mMuteLocalAudioStream;
    RtcEngine.getInstance().muteLocalAudioStream(mMuteLocalAudioStream);
    mAudioSwitchButton.setText(mMuteLocalAudioStream ? "voice on" : "voice off");
  }

  public void onVideoSwitchClick(View view){
    mEnableLocalVideo = !mEnableLocalVideo;
    RtcEngine.getInstance().enableLocalVideo(mEnableLocalVideo);
    mVideoSwitchButton.setText(mEnableLocalVideo ? "video off" : "video on");
  }

  public void onCameraSwitchClick(View view){
    RtcEngine.getInstance().switchCamera();
  }

  public void onRelaySwitchClick(View view){
    mRelayState = !mRelayState;
    if(mRelayState){
      startRelayMedia();
    }else{
      stopRelayMedia();
    }
  }

  private void startRelayMedia(){
    AlertDialog.Builder builder = new AlertDialog.Builder(this);
    builder.setTitle("Relay");
    builder.setMessage("Insert RoomId");
    final EditText edit = new EditText(this);
    builder.setView(edit);
    builder.setPositiveButton("sure", new DialogInterface.OnClickListener() {
      @Override
      public void onClick(DialogInterface dialog, int which) {
        String name = edit.getText().toString();
        if (name.isEmpty()){
          dialog.dismiss();
          return;
        }
        ChannelMediaRelayConfiguration configurations = new ChannelMediaRelayConfiguration();
        configurations.setSrcChannelInfo(new ChannelMediaInfo(mRoomId, "", 0));
        configurations.setDestChannelInfo(name, new ChannelMediaInfo(name, "", mUserId));
        int ret = RtcEngine.getInstance().startChannelMediaRelay(configurations);
        if (ret == 0){
          mRelayState = true;
          mRelayMediaButton.setText("stop relay");
        }
        else{
          showToast("Failed to start the relay, err:" + ret);
        }
        dialog.dismiss();
      }
    });
    builder.setNegativeButton("cancel", new DialogInterface.OnClickListener() {
      @Override
      public void onClick(DialogInterface dialog, int which) {
        dialog.dismiss();
      }
    });
    AlertDialog dialog = builder.create();
    dialog.show();
  }


  private void stopRelayMedia(){
    RtcEngine.getInstance().stopChannelMediaRelay();
    mRelayState = false;
    mRelayMediaButton.setText("Start relay");
  }

  private void exitRoom(){
    Log.i(TAG, "exitRoom");
    if(RtcEngine.getInstance() != null){
      RtcEngine.getInstance().leaveChannel();
      RtcEngine.getInstance().removeHandler(mRtcEngineEventImpl);
    }
    mSimpleRecycleAdapter.removeAllViewHolder();
    mRecyclerView.removeAllViews();
    RtcEngine.destroy();
    finish();
  }

  public void onExitRoomClick(View view){
    exitRoom();
  }

  public void onMusicSelectClick(View view){
    final String type = "audio/*";
    final String[] mimeTypes = null;
    pick(this, null, type, mimeTypes, false, 1000);
  }
  public void onMusicPlayClick(View view){
    if (mMusicIsPlayed){
      stopMusic();
    }
    else {
      String filename = mMusicNameEditText.getText().toString();
      startMusic(filename);
    }
  }
  public void onMusicPauseClick(View view){
    if(RtcEngine.getInstance() == null) return ;
     if(!mMusicIsPlayed)
       return;
     if (mMusicIsPause){
       RtcEngine.getInstance().resumeAudioMixing();
       mMusicPauseButton.setText("pause");
       mMusicIsPause = false;
     }else{
       RtcEngine.getInstance().pauseAudioMixing();
       mMusicPauseButton.setText("resume");
       mMusicIsPause = true;
     }
  }

  public boolean pick(Activity context, Activity fragment,
                                   String type, String[] mimeTypes,
                                   boolean documentOnly, int requestCode) {

    boolean result = false;
    if (context == null && fragment == null) {
      return false;
    }
    ArrayList<String> list = new ArrayList<>();
    list.add(Intent.ACTION_OPEN_DOCUMENT);
    list.add(Intent.ACTION_GET_CONTENT);
    if (!documentOnly) {
      list.add(0, Intent.ACTION_PICK);
    }
    for (String action : list) {
      if (action.equalsIgnoreCase(Intent.ACTION_PICK)) {
        if (mimeTypes != null && mimeTypes.length > 1) {
          continue;
        }
      }

      Intent intent = new Intent();
      intent.setAction(action);
      intent.setType(type);
      intent.putExtra(Intent.EXTRA_ALLOW_MULTIPLE, true);
      intent.putExtra(Intent.EXTRA_LOCAL_ONLY, false);
      if (mimeTypes != null && mimeTypes.length > 0) {
        intent.putExtra(Intent.EXTRA_MIME_TYPES, mimeTypes);
      }
      if (action.equalsIgnoreCase(Intent.ACTION_OPEN_DOCUMENT)
          || action.equalsIgnoreCase(Intent.ACTION_GET_CONTENT)) {
        intent.addCategory(Intent.CATEGORY_OPENABLE);
      }
      try {
        if (fragment != null) {
          fragment.startActivityForResult(intent, requestCode);
        } else {
          context.startActivityForResult(intent, requestCode);
        }
        result = true;
        break;

      } catch (Exception e) {
        e.printStackTrace();
      }
    }
    return result;
  }

  @Override
  @CallSuper
  protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data){
    super.onActivityResult(requestCode, resultCode, data);
    if (requestCode == 1000){
      if(resultCode == Activity.RESULT_OK){
          if(data != null ){
            Uri url = data.getData();
            String filepath = getPath(getApplicationContext(), url);
            if(filepath == null || filepath.isEmpty())
              return;
            startMusic(filepath);
          }
      }
    }

  }

  private void startMusic(String filepath){
    stopMusic();
    synchronized (timeLock) {
      if (RtcEngine.getInstance().startAudioMixing(filepath, false, false, -1) == 0) {
        mMusicIsPlayed = true;
        mMusicIsPause = false;
        mMusicPlayButton.setText("stop");
        mMusicPauseButton.setText("pause");
        mMusicTimer = new Timer();
        mMusicTotalTimeMs = 0;
        mMusicTimer.schedule(new MusicTimerTask(), 1000, 1000);
      } else {
        showToast("play music failed");
      }
    }
    mMusicNameEditText.setText(filepath);
  }

  private void stopMusic(){
      synchronized (timeLock){
       if(!mMusicIsPlayed) {
         return;
       }
       mMusicIsPause = false;
       mMusicIsPlayed = false;
       mMusicTimer.cancel();
       mMusicTimer = null;
       mMusicSeekBar.setProgress(0);
       mMusicTotalTimeTextView.setText("00:00");
       mMusicCurrentTimeTextView.setText("00:00");
       mMusicPlayButton.setText("play");
       mMusicPauseButton.setText("pause");
       if(RtcEngine.getInstance() == null) return ;
       RtcEngine.getInstance().stopAudioMixing();
     }
  }

 private class MusicTimerTask extends TimerTask{
   @Override
   public void run() {
     synchronized (timeLock){
       if(mMusicTotalTimeMs != 0 && mMusicIsPlayed && RtcEngine.getInstance() != null){
         int pts = RtcEngine.getInstance().getAudioMixingCurrentPosition();
         int pos = (int)(pts*1.0f/mMusicTotalTimeMs * 100);
         mHandler.post(()->{
           String str = String.format("%02d:%02d", pts/1000/60, pts/1000%60);
           mMusicCurrentTimeTextView.setText(str);
           mMusicSeekBar.setProgress(pos);
         });
       }
     }
   }
  };


  public  String getPath(final Context context, final Uri uri) {
    if(uri == null)
      return null;
    final boolean isKitKat = Build.VERSION.SDK_INT >= Build.VERSION_CODES.KITKAT;
    try{
      if (isKitKat && DocumentsContract.isDocumentUri(context, uri)) {
        if (isExternalStorageDocument(uri)) {
          final String docId = DocumentsContract.getDocumentId(uri);
          final String[] split = docId.split(":");
          final String type = split[0];

          if ("primary".equalsIgnoreCase(type)) {
            return Environment.getExternalStorageDirectory() + "/" + split[1];
          }
        }
        else if (isDownloadsDocument(uri)) {

          final String id = DocumentsContract.getDocumentId(uri);
          if(id.indexOf(":") > 0){
            final String[] split = id.split(":");
            return split[1];
          }
          final Uri contentUri = ContentUris.withAppendedId(
                  Uri.parse("content://downloads/public_downloads"), Long.valueOf(id));

          return getDataColumn(context, contentUri, null, null);
        }
        else if (isMediaDocument(uri)) {
          final String docId = DocumentsContract.getDocumentId(uri);
          final String[] split = docId.split(":");
          final String type = split[0];

          Uri contentUri = null;
          if ("image".equals(type)) {
            contentUri = MediaStore.Images.Media.EXTERNAL_CONTENT_URI;
          } else if ("video".equals(type)) {
            contentUri = MediaStore.Video.Media.EXTERNAL_CONTENT_URI;
          } else if ("audio".equals(type)) {
            contentUri = MediaStore.Audio.Media.EXTERNAL_CONTENT_URI;
          }

          final String selection = "_id=?";
          final String[] selectionArgs = new String[] {
                  split[1]
          };

          return getDataColumn(context, contentUri, selection, selectionArgs);
        }
      }
      else if ("content".equalsIgnoreCase(uri.getScheme())) {
        return getDataColumn(context, uri, null, null);
      }
      else if ("file".equalsIgnoreCase(uri.getScheme())) {
        return uri.getPath();
      }
    }catch (NullPointerException e){
      e.printStackTrace();
    }


    return null;
  }

  public  String getDataColumn(Context context, Uri uri, String selection,
                               String[] selectionArgs) {
    Cursor cursor = null;
    final String column = "_data";
    final String[] projection = {
        column
    };

    try {
      cursor = context.getContentResolver().query(uri, projection, selection, selectionArgs,
          null);
      if (cursor != null && cursor.moveToFirst()) {
        final int column_index = cursor.getColumnIndexOrThrow(column);
        return cursor.getString(column_index);
      }
    } finally {
      if (cursor != null)
        cursor.close();
    }
    return null;
  }

  public  boolean isExternalStorageDocument(Uri uri) {
    return "com.android.externalstorage.documents".equals(uri.getAuthority());
  }

  public  boolean isDownloadsDocument(Uri uri) {
    return "com.android.providers.downloads.documents".equals(uri.getAuthority());
  }

  public static boolean isMediaDocument(Uri uri) {
    return "com.android.providers.media.documents".equals(uri.getAuthority());
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
      showToast("err:" + err);
    }

    @Override public void  onJoinChannelSuccess(String channel, int uid, int elapsed) {
    }

    @Override public void  onRejoinChannelSuccess(String channel, int uid, int elapsed) {
      mHandler.post(()-> {
          mStateTextView.setText("Reconnection successful");
      });
    }

    @Override public void  onLeaveChannel(RtcStats stats) {
    }

    @Override public void  onClientRoleChanged(int oldRole, int newRole) {
        showToast("Role Switching:" + oldRole + "->" + newRole);
    }


    @Override public void  onUserJoined(int uid, int elapsed) {
      mHandler.post(()->{
        mSimpleRecycleAdapter.addItem(uid);
      });
    }

    @Override public void  onUserOffline(int uid, int reason) {
      mHandler.post(()->{
        mSimpleRecycleAdapter.removeItem(uid);
      });
    }

    @Override public void  onConnectionStateChanged(int state, int reason) {
      Log.i(TAG, "onConnectionStateChanged state:" + state);
      mHandler.post(()->{
        switch(state){
          case CONNECTION_STATE_DISCONNECTED:
          {
            switch (reason) {
              case CONNECTION_CHANGED_INTERRUPTED:
                mStateTextView.setText("Disconnect, Network error");
                break;
              case CONNECTION_CHANGED_JOIN_FAILED:
                mStateTextView.setText("Disconnect, Failed to join the room");
                break;
              case CONNECTION_CHANGED_LEAVE_CHANNEL:
                mStateTextView.setText("Disconnect, Leave room ");
                break;
              case CONNECTION_CHANGED_INVALID_CHANNEL_NAME:
                mStateTextView.setText("Disconnect, Invalid room ");
                break;
              case CONNECTION_CHANGED_BANNED_BY_SERVER:
                mStateTextView.setText("Disconnect, Kicked out");
                showToast("You have been kicked out");
                break;
              case CONNECTION_CHANGED_KEEP_ALIVE_TIMEOUT:
                mStateTextView.setText("Disconnect, Heatbeat timeout ");
                break;
              case CONNECTION_CHANGED_INVALID_APP_ID:
                mStateTextView.setText("Disconnect, Invalid appid");
                break;
              case CONNECTION_CHANGED_TOKEN_EXPIRED:
                mStateTextView.setText("Disconnect,Token expired");
                break;
              case CONNECTION_CHANGED_INVALID_TOKEN:
                mStateTextView.setText("Disconnect, Invalid token");
                break;
              case CONNECTION_CHANGED_REJECTED_BY_SERVER:
                mStateTextView.setText("Disconnect, Rejected by service");
                break;
              case CONNECTION_CHANGED_CLIENT_IP_ADDRESS_CHANGED:
                mStateTextView.setText("Disconnect, Network change");
                break;
              default:
                mStateTextView.setText("Disconnect");
                break;
            }
            mSimpleRecycleAdapter.addItem(mUserId, true);
          }break;
          case CONNECTION_STATE_CONNECTING:
            switch (reason) {
              case CONNECTION_CHANGED_JOIN_SUCCESS:
                mStateTextView.setText("Connecting，ice");
                break;
              default:
                mStateTextView.setText("Connectting... ");
                break;
            }
            break;
          case CONNECTION_STATE_CONNECTED:
            mStateTextView.setText("Join success");
            break;
          case CONNECTION_STATE_RECONNECTING:
            mStateTextView.setText("Reconnecting... ");
            break;
          case CONNECTION_STATE_FAILED:
            mStateTextView.setText("Connect failed");
            if(RtcEngine.getInstance() != null)
               RtcEngine.getInstance().leaveChannel();
            break;
        }
      });
    }

    @Override public void  onAudioVolumeIndication(AudioVolumeInfo[] speakers, int totalVolume) {
      if (speakers.length == 0)
        return;
      mHandler.post(()->{
        if(mVadState != speakers[0].vad){
          mVadStateView.setBackground(speakers[0].vad == 0 ? mDefaultDrawable : mRedDrawable);
          mVadState = speakers[0].vad;
        }
        for (AudioVolumeInfo info : speakers){
          mSimpleRecycleAdapter.setRealTimeVolume(info.uid, info.volume);
        }
      });

    }

    @Override public void  onRemoteAudioStateChanged(int uid, int state, int reason, int elapsed) {
      mHandler.post(()-> {
        switch (state) {
          case REMOTE_AUDIO_STATE_STOPPED:
            if (reason == REMOTE_AUDIO_REASON_LOCAL_MUTED) {
              mSimpleRecycleAdapter.setRealTimeVolume(uid, 0);
            } else if (reason == REMOTE_AUDIO_REASON_REMOTE_MUTED) {
              mSimpleRecycleAdapter.setRemoteMuteState(uid, true);
            } else if (reason == REMOTE_AUDIO_REASON_REMOTE_OFFLINE) {
              mSimpleRecycleAdapter.setRemoteMuteState(uid, false);
            }
            break;
          case REMOTE_AUDIO_STATE_STARTING:

            break;
          case REMOTE_AUDIO_STATE_DECODING:
            if (reason == REMOTE_AUDIO_REASON_NETWORK_RECOVERY) {

            } else if (reason == REMOTE_AUDIO_REASON_LOCAL_UNMUTED) {

            } else if (reason == REMOTE_AUDIO_REASON_REMOTE_UNMUTED) {
              mSimpleRecycleAdapter.setRemoteMuteState(uid, false);
            }
            break;
          case REMOTE_AUDIO_STATE_FROZEN:
            break;
          case REMOTE_AUDIO_STATE_FAILED:
            break;
        }
      });
    }

    @Override public void  onChannelMediaRelayStateChanged(int state, int code) {
      mHandler.post(()-> {
        if (state == RELAY_STATE_RUNNING && code == RELAY_OK) {
          mStateTextView.setText("relay suc");
        } else if (state == RELAY_STATE_FAILURE) {
          mStateTextView.setText("relay failed, code:" + code);
          stopRelayMedia();
        }
      });
    }

    @Override public void  onChannelMediaRelayEvent(int code) {
      mHandler.post(()-> {
        if (code == RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL_IS_NULL) {
          mStateTextView.setText("relay failed,room not exit");
          stopRelayMedia();
        } else {
          mStateTextView.setText("relay event, event:" + code);
        }
      });
    }

    @Override public void  onRtcStats(RtcStats stats) {
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

    @Override public void  onLocalVideoStats(LocalVideoStats stats) {
      LocalStatsData data = (LocalStatsData) mStatsManager.getStatsData(mUserId);
      if (data == null) return;

      data.setWidth(stats.encodedFrameWidth);
      data.setHeight(stats.encodedFrameHeight);
      data.setFramerate(stats.sentFrameRate);
    }

    @Override public void  onRemoteVideoStats(RemoteVideoStats stats) {
      RemoteStatsData data = (RemoteStatsData) mStatsManager.getStatsData(stats.uid);
      if (data == null) return;

      data.setWidth(stats.width);
      data.setHeight(stats.height);
      data.setFramerate(stats.rendererOutputFrameRate);
      data.setVideoRx(stats.receivedBitrate);
      data.setVideoDelay(stats.delay);
    }

    @Override public void  onLocalAudioStats(LocalAudioStats stats) {
      LocalStatsData data = (LocalStatsData) mStatsManager.getStatsData(mUserId);
      if (data == null) return;
    }

    @Override public void  onRemoteAudioStats(RemoteAudioStats stats) {
      RemoteStatsData data = (RemoteStatsData) mStatsManager.getStatsData(stats.uid);
      if (data == null) return;

      data.setAudioRx(stats.receivedBitrate);
      data.setAudioNetDelay(stats.networkTransportDelay);
      data.setAudioNetJitter(stats.jitterBufferDelay);
      data.setAudioLoss(stats.audioLossRate);
      data.setAudioQuality(mStatsManager.qualityToString(stats.quality));
    }

    @Override public void  onAudioMixingStateChanged(int state, int errorCode) {
      mHandler.post(()-> {
        switch (state) {
          case MEDIA_ENGINE_AUDIO_EVENT_MIXING_PLAY:
            synchronized (timeLock){
              if( RtcEngine.getInstance() != null){
                mMusicTotalTimeMs = RtcEngine.getInstance().getAudioMixingDuration();
                String str = String.format("%02d:%02d", mMusicTotalTimeMs/1000/60, mMusicTotalTimeMs/1000%60);
                mMusicTotalTimeTextView.setText(str);
              }
            }
            showToast("play music suc");
            break;
          case MEDIA_ENGINE_AUDIO_EVENT_MIXING_PAUSED:
            showToast("play music pause");
            break;
          case MEDIA_ENGINE_AUDIO_EVENT_MIXING_RESTART:
            showToast("play music resume");
            break;
          case MEDIA_ENGINE_AUDIO_EVENT_MIXING_STOPPED:
            showToast("play music ended");
            stopMusic();
            break;
          case MEDIA_ENGINE_AUDIO_EVENT_MIXING_ERROR:
            switch (errorCode) {
              case MEDIA_ENGINE_AUDIO_ERROR_MIXING_OPEN:
                showToast("play music open failed");
                stopMusic();
                break;
              case MEDIA_ENGINE_AUDIO_EVENT_MIXING_INTERRUPTED_EOF:
                showToast("play music interrupt");
                stopMusic();
                break;
              case MEDIA_ENGINE_AUDIO_EVENT_MIXING_NETWORK_UNSTABLE:
                showToast("play music bad network");
                break;
            }
            break;
        }
      });
    }
  }
}
