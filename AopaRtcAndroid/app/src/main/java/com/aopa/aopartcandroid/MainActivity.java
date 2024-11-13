package com.aopa.aopartcandroid;

import androidx.annotation.CallSuper;
import androidx.annotation.Nullable;
import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.os.Build;
import android.os.Bundle;
import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.text.InputType;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.ArrayAdapter;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.Toast;
import java.util.ArrayList;


public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity";
    public static final int APPLY_PERMISSIONS = 154;
    private Spinner mSpinnerQuality = null;
    private Spinner mSpinnerScenario = null;
    private Spinner mSpinnerRole = null;
    private Spinner mResolutionSpinner = null;
    private EditText mRoomIdEditText;
    private EditText mUserIdEditText;
    private CheckBox mSpeakerCheckBox;
    private CheckBox mVideoCheckBox;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        supportRequestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.activity_main);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        mRoomIdEditText = findViewById(R.id.RoomIdEditText);
        mUserIdEditText = findViewById(R.id.UserIdEditText);
        mSpinnerQuality = findViewById(R.id.AudioQualitySpinner);
        mSpinnerScenario = findViewById(R.id.ScenarioSpinner);
        mSpinnerRole = findViewById(R.id.RoleSpinner);
        mResolutionSpinner = findViewById(R.id.ResolutionSpinner);
        mSpeakerCheckBox = findViewById(R.id.SpeakerCheckBox);
        mVideoCheckBox = findViewById(R.id.VideoCheckBox);
        mUserIdEditText.setInputType(InputType.TYPE_CLASS_NUMBER);


        String[] quelityTypes = new String[]{"default", "32kMono", "48kMono", "48kStero", "48kMonoHighQulity", "48kSteroHighQulity"};
        ArrayAdapter<String> quelityAdapter = new ArrayAdapter<String>(getApplicationContext(), android.R.layout.simple_spinner_item, quelityTypes);
        quelityAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        mSpinnerQuality.setAdapter(quelityAdapter);
        mSpinnerQuality.setSelection(5);

        String[] scenarioTypes = new String[]{"ShowRoom", "GameStreaming", "Chorus"};
        ArrayAdapter<String> scenarioAdapter = new ArrayAdapter<String>(getApplicationContext(), android.R.layout.simple_spinner_item, scenarioTypes);
        scenarioAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        mSpinnerScenario.setAdapter(scenarioAdapter);

        String[] roleTypes = new String[]{"Broadcaster", "Audience"};
        ArrayAdapter<String> roleAdapter = new ArrayAdapter<String>(getApplicationContext(), android.R.layout.simple_spinner_item, roleTypes);
        roleAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        mSpinnerRole.setAdapter(roleAdapter);

        String[] resolutionTypes = new String[]{"360x640", "480x640", "540x960" ,"720x1280", "1080x1920"};
        ArrayAdapter<String> resolutionAdapter = new ArrayAdapter<String>(getApplicationContext(), android.R.layout.simple_spinner_item, resolutionTypes);
        resolutionAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        mResolutionSpinner.setAdapter(resolutionAdapter);

        mUserIdEditText.setText(String.valueOf((int) (Math.random() * 10000)));
        mSpeakerCheckBox.setChecked(true);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
    }

    public void onJoinClick(View view) {
        String [] Permissions = PERMISSION_LIST;
        if(applyPermissions(Permissions)){
            joinRoom();
        }
    }


    private synchronized void joinRoom(){
        String userId = mUserIdEditText.getText().toString();
        String roomId = mRoomIdEditText.getText().toString();
        int qualityType = mSpinnerQuality.getSelectedItemPosition();
        int roleType = mSpinnerRole.getSelectedItemPosition();
        int resolutionType = mResolutionSpinner.getSelectedItemPosition();
        int scenarioType = mSpinnerScenario.getSelectedItemPosition();
        boolean speakerEnabled = mSpeakerCheckBox.isChecked();
        boolean videoEnabled = mVideoCheckBox.isChecked();

        Intent intent = new Intent(getApplicationContext(), RoomActivity.class);
        intent.putExtra("userId", userId);
        intent.putExtra("roomId", roomId);
        intent.putExtra("qualityType", qualityType);
        intent.putExtra("scenarioType", scenarioType);
        intent.putExtra("roleType", (roleType + 1));
        intent.putExtra("resolution", resolutionType);
        intent.putExtra("speaker", speakerEnabled);
        intent.putExtra("videoEnabled", videoEnabled);
        startActivity(intent);
    }

    private static String[] PERMISSION_LIST = {
            Manifest.permission.RECORD_AUDIO,
            Manifest.permission.MODIFY_AUDIO_SETTINGS,
            Manifest.permission.WRITE_EXTERNAL_STORAGE,
            Manifest.permission.READ_EXTERNAL_STORAGE,
            Manifest.permission.CAMERA,
    };
    public  boolean applyPermissions(String[] permissions) {
        ArrayList<String> unApplyList = new ArrayList<String>();
        for (int i = 0; i < permissions.length; i++) {
            if (ActivityCompat.checkSelfPermission(getApplicationContext(), permissions[i]) != PackageManager.PERMISSION_GRANTED) {
                unApplyList.add(permissions[i]);
            }
        }
        if (unApplyList.size() == 0) {
            return true;
        }
        else {
            if (getSDKVersionNumber() < 23) {
                Toast.makeText(getApplicationContext(), "Permission deny,please set effient right in setting", Toast.LENGTH_SHORT).show();
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
            sdkVersion = Integer.valueOf(Build.VERSION.SDK_INT);
        } catch (NumberFormatException e) {
            sdkVersion = 0;
        }
        return sdkVersion;
    }

    @RequiresApi(api = 23)
    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults)
    {
        if (requestCode == APPLY_PERMISSIONS) {
            for (int i = 0; i < permissions.length; i++) {
                if (grantResults[i] != PackageManager.PERMISSION_GRANTED) {
                    Toast.makeText(getApplicationContext(), "Permission deny,App exited", Toast.LENGTH_SHORT).show();
                    return;
                }
            }
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
      //  joinRoom();

    }

}
