package org.banban.demo;

import androidx.annotation.CallSuper;
import androidx.annotation.Nullable;
import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.text.InputType;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.ArrayAdapter;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;
import android.text.method.DigitsKeyListener;

import org.banban.rtc.RtcEngine;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Properties;
import org.json.JSONObject;

import static org.banban.rtc.Constants.LOG_FILTER_DEBUG;
import static org.banban.rtc.Constants.LOG_FILTER_INFO;

import com.tencent.bugly.crashreport.CrashReport;

public class MainActivity extends AppCompatActivity {
  private String TAG = "MainActivity";
  private String [] servers = {"{\"signaling\":\"wss://rtc-gateway-oversea.aopacloud.net:6080/rtc/channel\",\"rtconfig\":\"https://rtc-gateway-oversea.aopacloud.net:6080/rtc/get_rtc_config\",\"log\":\"https://rtc-gateway-oversea.aopacloud.net:6080/ali/v1/get_upload_url\",\"quic\":\"rtc-gateway-oversea-quic.aopacloud.net:16081\",\"report\":\"https://rtc-gateway-oversea.aopacloud.net:6080/rtc/rtc_event_report\"}"};
  private String [] appIdList = {
          "6MHg9hZqMMcKjNyiauSyU8H5b3eTr4qM"
  };

  private Spinner mSpinnerQuality = null;
  private Spinner mSpinnerScenario = null;
  private Spinner mSpinnerRole = null;
  private Spinner mResolutionSpinner = null;
  private Spinner mAppIdSpinner = null;
  private TextView mVersionText;
  private EditText mRoomIdEditText;
  private EditText mUserIdEditText;
  private Spinner mServerSpinner;
  private EditText mCustomServerEditText;
  private CheckBox mTokenCheckBox;
  private CheckBox mStatsCheckBox;
  private CheckBox mSpeakerCheckBox;
  private CheckBox mInearCheckBox;
  private CheckBox m3ACheckBox;
  private CheckBox mReverbCheckBox;
  private CheckBox mVideoCheckBox;
  private CheckBox mQuicCheckBox;
  private CheckBox mMulticastCheckBox;
  private CheckBox mDetachCheckBox;
  private boolean mIsJoinRoom = false;
  private String mAppId = "bbrtc";
  private String mToken = "";
  private boolean mTokenCheck = true;
  private boolean mStatsCheck = true;
  private boolean mSpeakerEnabled = false;
  private boolean mInearEnabled = false;
  private boolean m3AEnabled = true;
  private boolean mReverbEnabled = false;
  private boolean mQuicEnabled = true;
  private boolean mMulticastEnabled = true;
  private boolean mDetachEnabled = false;
  private String mRoomId = "room888";
  private int mAppIdType = 0;
  private int mQualityType = 5;
  private int mRoleType = 0;
  private int mServerType = 2;
  private int mResolutionType = 0;
  private int mScenarioType = 0;
  private Handler mHandler = new Handler();
  private Thread mThread;
  private int mUserId = 0;
  private boolean mReqToken = false;
  private boolean mVideoEnabled = true;
  private String mCustomServerIp = "";
  private boolean mSingleRoom = false;
  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    CrashReport.initCrashReport(getApplicationContext(), "d70c19f574", false);
    supportRequestWindowFeature(Window.FEATURE_NO_TITLE);
    setContentView(R.layout.activity_main);
    getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
    mVersionText = findViewById(R.id.VersionText);
    mRoomIdEditText = findViewById(R.id.RoomIdEditText);
    mUserIdEditText = findViewById(R.id.UserIdEditText);
    mAppIdSpinner = findViewById(R.id.AppIdSpinner);
    mSpinnerQuality = findViewById(R.id.AudioQualitySpinner);
    mSpinnerScenario = findViewById(R.id.ScenarioSpinner);
    mSpinnerRole = findViewById(R.id.RoleSpinner);
    mServerSpinner = findViewById(R.id.ServerSpinner);
    mResolutionSpinner = findViewById(R.id.ResolutionSpinner);
    mCustomServerEditText = findViewById(R.id.CustomServerEditText);
    mCustomServerEditText.setInputType(InputType.TYPE_CLASS_NUMBER);
    mCustomServerEditText.setKeyListener(DigitsKeyListener.getInstance("0123456789."));
    mTokenCheckBox = findViewById(R.id.TokenCheckBox);
    mStatsCheckBox = findViewById(R.id.StatsCheckBox);
    mSpeakerCheckBox = findViewById(R.id.SpeakerCheckBox);
    mInearCheckBox = findViewById(R.id.InearCheckBox);
    m3ACheckBox = findViewById(R.id.AAACheckBox);
    mReverbCheckBox = findViewById(R.id.ReverbCheckBox);
    mVideoCheckBox = findViewById(R.id.VideoCheckBox);
    mQuicCheckBox = findViewById(R.id.QuicCheckBox);
    mUserIdEditText.setInputType(InputType.TYPE_CLASS_NUMBER);
    mMulticastCheckBox = findViewById(R.id.MulticastCheckBox);
    mDetachCheckBox = findViewById(R.id.DetachCheckBox);

    ArrayAdapter<String> appidAdapter = new ArrayAdapter<String>(getApplicationContext(), android.R.layout.simple_spinner_item, appIdList);
    appidAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
    mAppIdSpinner.setAdapter(appidAdapter);


    String[] quelityTypes = new String[]{"默认", "32k单声道", "48k单声道", "48k双声道", "48k单声道高音质", "48k双声道高音质"};
    ArrayAdapter<String> quelityAdapter = new ArrayAdapter<String>(getApplicationContext(), android.R.layout.simple_spinner_item, quelityTypes);
    quelityAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
    mSpinnerQuality.setAdapter(quelityAdapter);

    String[] scenarioTypes = new String[]{"ShowRoom", "GameStreaming", "Chorus"};
    ArrayAdapter<String> scenarioAdapter = new ArrayAdapter<String>(getApplicationContext(), android.R.layout.simple_spinner_item, scenarioTypes);
    scenarioAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
    mSpinnerScenario.setAdapter(scenarioAdapter);

    String[] roleTypes = new String[]{"主播", "观众"};
    ArrayAdapter<String> roleAdapter = new ArrayAdapter<String>(getApplicationContext(), android.R.layout.simple_spinner_item, roleTypes);
    roleAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
    mSpinnerRole.setAdapter(roleAdapter);

    String[] serverTypes = new String[]{"奥帕云正式环境","BB正式环境", "测试环境", "测试环境V2", "内网环境", "自定义", "P2P"};
    ArrayAdapter<String> serverAdapter = new ArrayAdapter<String>(getApplicationContext(), android.R.layout.simple_spinner_item, serverTypes);
    serverAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
    mServerSpinner.setAdapter(serverAdapter);

    String[] resolutionTypes = new String[]{"360x640", "480x640", "540x960" ,"720x1280", "1080x1920"};
    ArrayAdapter<String> resolutionAdapter = new ArrayAdapter<String>(getApplicationContext(), android.R.layout.simple_spinner_item, resolutionTypes);
    resolutionAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
    mResolutionSpinner.setAdapter(resolutionAdapter);

    loadProperty();
    mRoomIdEditText.setText(mRoomId);
    mAppIdSpinner.setSelection(mAppIdType);
    mServerSpinner.setSelection(mServerType);
    mSpinnerQuality.setSelection(mQualityType);
    mSpinnerRole.setSelection(mRoleType);
    mResolutionSpinner.setSelection(mResolutionType);
    mTokenCheckBox.setChecked(mTokenCheck);
    mStatsCheckBox.setChecked(mStatsCheck);
    mSpeakerCheckBox.setChecked(mSpeakerEnabled);
    mInearCheckBox.setChecked(mInearEnabled);
    m3ACheckBox.setChecked(m3AEnabled);
    mReverbCheckBox.setChecked(mReverbEnabled);
    mVideoCheckBox.setChecked(mVideoEnabled);
    mQuicCheckBox.setChecked(mQuicEnabled);
    mCustomServerEditText.setText(mCustomServerIp);
    mMulticastCheckBox.setChecked(mMulticastEnabled);
    mSpinnerScenario.setSelection(mScenarioType);
    mDetachCheckBox.setChecked(mDetachEnabled);
    String version = RtcEngine.getSdkVersion();
    mVersionText.setText(version);
    mUserId = (int) (Math.random() * 10000);
    mUserIdEditText.setText(String.valueOf(mUserId));
   // runTest();
  }

  private void runTest(){
    mRoomIdEditText.setText(String.valueOf((int)(Math.random() * 10000)%4 + 1));
    mRoomIdEditText.setEnabled(false);
    mUserIdEditText.setEnabled(false);
    mServerSpinner.setEnabled(false);
    mResolutionSpinner.setEnabled(false);
    mMulticastCheckBox.setEnabled(false);
    mVideoCheckBox.setEnabled(false);
    mSpinnerRole.setEnabled(false);
    mAppIdSpinner.setEnabled(false);
    mTokenCheckBox.setEnabled(false);

    //onJoinClick(null);
  }

  @Override
  protected void onDestroy() {
    super.onDestroy();
  }

  public void onJoinClick(View view) {
    mSingleRoom = false;
    if(mIsJoinRoom)
       return;
    String [] Permissions = Build.VERSION.SDK_INT > 30 ? PERMISSION_LIST12 : PERMISSION_LIST;
    if(applyPermissions(Permissions)){
      joinRoom();
    }
  }

  public void onSingleClick(View view) {
    mSingleRoom = true;
    if(mIsJoinRoom)
      return;
    String [] Permissions = Build.VERSION.SDK_INT > 30 ? PERMISSION_LIST12 : PERMISSION_LIST;
    if(applyPermissions(Permissions)){
      joinRoom();
    }
  }

  //文件拷贝
  //要复制的目录下的所有非子目录(文件夹)文件拷贝
  public static int copySdcardFile(String fromFile, String toFile) {

    try {
      FileInputStream fosfrom = new FileInputStream(fromFile);
      FileOutputStream fosto = new FileOutputStream(toFile);
      ByteArrayOutputStream baos = new ByteArrayOutputStream();
      byte[] buffer = new byte[1024];
      int len = -1;
      while ((len = fosfrom.read(buffer)) != -1) {
        baos.write(buffer, 0, len);
      }
      // 从内存到写入到具体文件
      fosto.write(baos.toByteArray());
      // 关闭文件流
      baos.close();
      fosto.close();
      fosfrom.close();
      return 0;

    } catch (Exception ex) {
      ex.printStackTrace();
      return -1;
    }
  }

  private synchronized void joinRoom(){
    mRoomId = mRoomIdEditText.getText().toString();
    mAppIdType = mAppIdSpinner.getSelectedItemPosition();
    mQualityType = mSpinnerQuality.getSelectedItemPosition();
    mRoleType = mSpinnerRole.getSelectedItemPosition();
    mServerType = mServerSpinner.getSelectedItemPosition();
    mResolutionType = mResolutionSpinner.getSelectedItemPosition();
    mScenarioType = mSpinnerScenario.getSelectedItemPosition();
    mTokenCheck = mTokenCheckBox.isChecked();
    mStatsCheck = mStatsCheckBox.isChecked();
    mSpeakerEnabled = mSpeakerCheckBox.isChecked();
    mInearEnabled = mInearCheckBox.isChecked();
    m3AEnabled = m3ACheckBox.isChecked();
    mReverbEnabled = mReverbCheckBox.isChecked();
    mVideoEnabled = mVideoCheckBox.isChecked();
    mQuicEnabled = mQuicCheckBox.isChecked();
    mCustomServerIp = mCustomServerEditText.getText().toString();
    mMulticastEnabled = mMulticastCheckBox.isChecked();
    mDetachEnabled = mDetachCheckBox.isChecked();
    if(!mUserIdEditText.getText().toString().isEmpty()){
       mUserId = Integer.valueOf(mUserIdEditText.getText().toString()).intValue();
    }

    if (mToken.isEmpty() && mTokenCheck ) {
      getToken((mServerType > 1 ? mAppId : "online"), String.valueOf(mUserId), mRoomId, mRoleType == 0 ? "broadcaster" : "audience");
      return;
    }
    if(mIsJoinRoom)
      return;
    mIsJoinRoom = true;
    Log.i(TAG, "joinRoom appid:" + appIdList[mAppIdType]);
    try {
      if(mServerType >= servers.length) mServerType = 0;
      String serverAddr;
      if(mServerType == 5){
        serverAddr = servers[4];
        serverAddr = serverAddr.replaceAll("192.168.11.47", mCustomServerIp);
      }
      else{
        serverAddr = servers[mServerType];
      }
      JSONObject jsonObject = new JSONObject(serverAddr);
      jsonObject.put("uid", mUserId);
      String addr = jsonObject.toString();
      addr = addr.replace("\\/", "/");
      RtcEngine.setBBRtcServerAddress(addr, this);
      RtcEngine.create(this, appIdList[mAppIdType], null);
    } catch (Exception e) {
      e.printStackTrace();
      return;
    }
    saveProperty();
    if(RtcEngine.getInstance() == null){
      mIsJoinRoom = false;
      mToken = "";
      return;
    }
    if(mServerType == 6){
      RtcEngine.getInstance().setParameters("{\"che.p2p.enable\":true}");
    }
    RtcEngine.getInstance().setLogFilter(LOG_FILTER_DEBUG);
    Intent intent = new Intent(getApplicationContext(), mSingleRoom ? SingleActivity.class : RoomActivity.class);
    intent.putExtra("userId", mUserId);
    intent.putExtra("roomId", mRoomId);
    intent.putExtra("qualityType", mQualityType);
    intent.putExtra("scenarioType", mScenarioType);
    intent.putExtra("roleType", (mRoleType + 1));
    intent.putExtra("resolution", mResolutionType);
    intent.putExtra("token", mToken);
    intent.putExtra("speaker", mSpeakerEnabled);
    intent.putExtra("inear", mInearEnabled);
    intent.putExtra("3A", m3AEnabled);
    intent.putExtra("reverb", mReverbEnabled);
    intent.putExtra("videoEnabled", mVideoEnabled);
    intent.putExtra("quic", mQuicEnabled);
    intent.putExtra("stats", mStatsCheck);
    intent.putExtra("multicast", mMulticastEnabled);
    intent.putExtra("detach", mDetachEnabled);
    startActivityForResult(intent, 1);
    mToken = "";
  }

  private String[] PERMISSION_LIST = {
          Manifest.permission.RECORD_AUDIO,
          Manifest.permission.MODIFY_AUDIO_SETTINGS,
          Manifest.permission.WRITE_EXTERNAL_STORAGE,
          Manifest.permission.READ_EXTERNAL_STORAGE,
          Manifest.permission.CAMERA,
          Manifest.permission.ACCESS_COARSE_LOCATION,
          Manifest.permission.ACCESS_FINE_LOCATION
  };

  private String[] PERMISSION_LIST12 = {
          Manifest.permission.RECORD_AUDIO,
          Manifest.permission.MODIFY_AUDIO_SETTINGS,
          Manifest.permission.WRITE_EXTERNAL_STORAGE,
          Manifest.permission.READ_EXTERNAL_STORAGE,
          Manifest.permission.CAMERA,
          Manifest.permission.ACCESS_COARSE_LOCATION,
          Manifest.permission.ACCESS_FINE_LOCATION
        //  "android.permission.BLUETOOTH_CONNECT"
  };

  //权限申请标记
  public static final int APPLY_PERMISSIONS = 154;
  public  boolean applyPermissions(String[] permissions) {
    //1.筛选未申请的权限：
    ArrayList<String> unApplyList = new ArrayList<String>();
    for (int i = 0; permissions!=null&&i < permissions.length; i++) {
      //筛选未拥有&&满足API要求的权限
      if (ActivityCompat.checkSelfPermission(getApplicationContext(), permissions[i]) != PackageManager.PERMISSION_GRANTED) {//未拥有的权限
        if (permissions[i].equals(Manifest.permission.READ_EXTERNAL_STORAGE) && getSDKVersionNumber() < 16) {//读取文件权限要求16以上
        } else if (permissions[i].equals(Manifest.permission.BODY_SENSORS) && getSDKVersionNumber() < 20) {//获取体征数据要求20以上
        } else if (permissions[i].equals(Manifest.permission.READ_CALL_LOG) && getSDKVersionNumber() < 16) {//读取手机通讯录要求16以上
        } else if (permissions[i].equals(Manifest.permission.WRITE_CALL_LOG) && getSDKVersionNumber() < 16) {//写入手机通讯录要求16以上
        } else if (permissions[i].equals(Manifest.permission.ADD_VOICEMAIL) && getSDKVersionNumber() < 14) {//添加语音信箱要求14以上
        } else {
          unApplyList.add(permissions[i]);
        }
      }
    }
    //2.如果所有权限都拥有了，返回true，否则申请所有未申请的权限
    if (unApplyList.size() == 0) {
      return true;
    }
    else {
      if (getSDKVersionNumber() < 23) {
        Toast.makeText(getApplicationContext(), "权限不足，请到设置页面给予应用相应的权限！", Toast.LENGTH_SHORT).show();
        return false;
      } else {
        String[] unApplyArray = new String[unApplyList.size()];
        for (int i = 0; i < unApplyArray.length; i++) {
          unApplyArray[i] = unApplyList.get(i);
        }
        ActivityCompat.requestPermissions(this, unApplyArray, APPLY_PERMISSIONS);
        return false;
      }
    }
  }

  public  int getSDKVersionNumber() {
    int sdkVersion;
    try {
      sdkVersion = Integer.valueOf(android.os.Build.VERSION.SDK);
    } catch (NumberFormatException e) {
      sdkVersion = 0;
    }
    return sdkVersion;
  }

  @RequiresApi(api = 23)
  @Override
  public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults)
  {
    //申请所有权限的回调结果：
    if (requestCode == APPLY_PERMISSIONS) {
      for (int i = 0; i < permissions.length; i++) {
        if (grantResults[i] != PackageManager.PERMISSION_GRANTED) {//如果有权限被拒绝
          Toast.makeText(getApplicationContext(), "对不起，您未给予相应的权限，程序将退出。", Toast.LENGTH_SHORT).show();
          return;
        }
      }
      //如果全部都同意了就进行配置加载
      joinRoom();
      return;
    }
    super.onRequestPermissionsResult(requestCode, permissions, grantResults);
  }
  @Override
  @CallSuper
  protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data){
    super.onActivityResult(requestCode, resultCode, data);
    Log.i(TAG, "onActivityResult");
    mHandler.postDelayed(()->{
      //RtcEngine.destroy();
      mIsJoinRoom = false;
    },500);

  }

  private void getToken(String appId, String userId, String channelId, String role){
    if(mReqToken)
      return;
    mReqToken = true;
    Log.i(TAG, "getToken start. 0");
    mThread = new Thread(){
      @Override
      public void run() {
        Log.i(TAG, "getToken start.");
        String url = "https://rtc-dev-gateway.aopacloud.net:6080/bbrtc/sign/getToken";
        String param = String.format("appName=%s&channel=%s&role=%s&uid=%s", appId, channelId, role, userId);
        String ret = HttpClient.doPost(url, param);
        if (ret == null || ret.isEmpty()){
          //mIsJoinRoom = false;
          mReqToken = false;
          Log.i(TAG, "getToken failed.");
          return;
        }
        try{
          JSONObject jObject = new JSONObject(ret);
          int code = jObject.getInt("code");
          if (code == 200){
           String token = jObject.getString("token");
            mHandler.post(()->{
               mToken = token;
               joinRoom();
            });
          }
          else {
            String msg = jObject.getString("err_msg");
            Log.i(TAG, "get token error:" + code + ", msg:" + msg + ", ret:" + ret);
          }
        }catch (JSONException e){
          e.printStackTrace();
          Log.i(TAG, "JSONException:" + e.toString());
        }
        mReqToken = false;
        Log.i(TAG, "getToken end.");
      }
    };
    mThread.start();
  }

  private void loadProperty(){
    try {
      Properties properties = new Properties();
      String filepath  = getApplicationContext().getExternalFilesDir("").getAbsolutePath() ;
      File file = new File(filepath);
      if (!file.exists()) {
        if(!file.mkdir()){
          Log.e(TAG, "+++ create folder failed." + filepath);
          return;
        }
      }
      String filename = filepath + "/config.properties";
      file = new File(filename);
      InputStream fis = new FileInputStream(file);
      properties.load(fis);
      fis.close();
      mRoomId = properties.getProperty("roomId", "room123");
      mServerType = Integer.valueOf(properties.getProperty("serverType", "2")).intValue();
      mQualityType = Integer.valueOf(properties.getProperty("qualityType", "3")).intValue();
      mRoleType =  Integer.valueOf(properties.getProperty("RoleType", "0")).intValue();
      mTokenCheck =  properties.getProperty("TokenCheck", "true").compareTo("true") == 0;
      mSpeakerEnabled =  properties.getProperty("Speaker", "true").compareTo("true") == 0;
      mInearEnabled =  properties.getProperty("Inear", "false").compareTo("true") == 0;
      m3AEnabled =  properties.getProperty("Inear", "true").compareTo("true") == 0;
      mReverbEnabled =  properties.getProperty("Reverb", "true").compareTo("true") == 0;
      m3AEnabled =  properties.getProperty("3A", "true").compareTo("true") == 0;
      mVideoEnabled =  properties.getProperty("videoEnabled", "true").compareTo("true") == 0;
      mQuicEnabled =  properties.getProperty("quic", "true").compareTo("true") == 0;
      mCustomServerIp = properties.getProperty("CustomServer", "");
      mMulticastEnabled = properties.getProperty("multicast", "true").compareTo("true") == 0;
      mScenarioType =  Integer.valueOf(properties.getProperty("scenarioType", "0")).intValue();
      mDetachEnabled =  properties.getProperty("detach", "true").compareTo("true") == 0;
      mResolutionType = Integer.valueOf(properties.getProperty("resolutionType", "0")).intValue();

    }catch (IOException | SecurityException | NullPointerException e){
      e.printStackTrace();
      Log.e(TAG, "Load config failed e:" + e.toString());
    }
  }

  private void saveProperty() {
    try {
      Properties properties = new Properties();
      String filepath  = getApplicationContext().getExternalFilesDir("").getAbsolutePath() ;
      String filename = filepath + "/config.properties";
      File file = new File(filename);
      if(file == null)
        return;
      file.createNewFile();
      InputStream fis = new FileInputStream(file);
      properties.load(fis);
      //一定要在修改值之前关闭fis
      fis.close();
      OutputStream fos = new FileOutputStream(filename);
      properties.setProperty("roomId", mRoomId);
      properties.setProperty("serverType", String.valueOf(mServerType));
      properties.setProperty("qualityType", String.valueOf(mQualityType));
      properties.setProperty("RoleType", String.valueOf(mRoleType));
      properties.setProperty("TokenCheck", String.valueOf(mTokenCheck));
      properties.setProperty("Speaker", String.valueOf(mSpeakerEnabled));
      properties.setProperty("Inear", String.valueOf(mInearEnabled));
      properties.setProperty("3A", String.valueOf(m3AEnabled));
      properties.setProperty("Reverb", String.valueOf(mReverbEnabled));
      properties.setProperty("videoEnabled", String.valueOf(mVideoEnabled));
      properties.setProperty("quic", String.valueOf(mQuicEnabled));
      properties.setProperty("CustomServer", mCustomServerIp);
      properties.setProperty("multicast", String.valueOf(mMulticastEnabled));
      properties.setProperty("scenarioType", String.valueOf(mScenarioType));
      properties.setProperty("detach", String.valueOf(mDetachEnabled));
      properties.setProperty("resolutionType", String.valueOf(mResolutionType));
      //保存，并加入注释
      properties.store(fos, "config");
      fos.close();
    }
    catch (IOException | SecurityException | NullPointerException e){
      e.printStackTrace();
    }
  }

}
