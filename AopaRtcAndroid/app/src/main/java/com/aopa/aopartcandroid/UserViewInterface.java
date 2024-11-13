package com.aopa.aopartcandroid;

import android.widget.RelativeLayout;

public interface UserViewInterface {
   boolean onUserAudioMuteEnable(int userId, boolean mute);
   boolean onUserVideoMuteEnable(int userId, boolean mute);
   boolean onUserVolumeChange(int userId, int volume);
   void    onUserAdd(int userId, RelativeLayout layout);
   void    onUserRemoved(int userId, RelativeLayout layout);
   boolean onUserStreamStateChange(int userId, boolean isBig);

}
