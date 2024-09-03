package org.banban.demo;

import android.content.Context;
import android.graphics.Rect;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import java.lang.ref.WeakReference;
import java.util.ArrayList;
import java.util.List;
import androidx.recyclerview.widget.RecyclerView;

import org.banban.demo.stats.StatsManager;


public class SimpleRecycleAdapter extends RecyclerView.Adapter<SimpleHolder> {
  private List<UserInfo> mList;
  private WeakReference<Context> mContext;
  private WeakReference<UserViewInterface> mDelegate;
  private StatsManager mStatsManager;
  public SimpleRecycleAdapter(Context context,  UserViewInterface delegate, StatsManager sg) {
    this.mContext = new WeakReference<Context>(context);
    this.mDelegate = new WeakReference<UserViewInterface>(delegate);
    this.mStatsManager = sg;
    mList = new ArrayList<UserInfo>();

  }

  public void addItem(Integer userId) {
    addItem(userId, false);
  }

  public void addItem(Integer userId, boolean local){
    for (int i = 0; i < mList.size(); i++){
      if (mList.get(i).userId.equals(userId))
         return;
    }
    mList.add(new UserInfo(userId));
    this.notifyItemInserted(mList.size());

    mStatsManager.addUserStats(userId, local);
  }

  public void removeItem(Integer userId){
    for (int i = 0; i < mList.size(); i++){
      if (mList.get(i).userId.equals(userId)){
        if(mList.get(i).holder != null){
          mDelegate.get().onUserRemoved(userId, mList.get(i).holder.getVideoView());

          mList.get(i).holder.setUserId(0);
          mList.get(i).holder = null;
        }
        mList.remove(i);
        mStatsManager.removeUserStats(userId);
        break;
      }
    }
    this.notifyDataSetChanged();
  }

  public void setRealTimeVolume(Integer userId, int volume){
    for (int i = 0; i < mList.size(); i++) {
      if (mList.get(i).userId.equals(userId)) {
        mList.get(i).volume = volume;
        ParamInfo info = new ParamInfo();
        info.type = 0;
        info.volume = volume;
        this.notifyItemChanged(i, info);
        break;
      }
    }
  }

  public void setRemoteMuteState(Integer userId, boolean mute){
    for (int i = 0; i < mList.size(); i++) {
      if (mList.get(i).userId.equals(userId)) {
        mList.get(i).mute = mute;
        ParamInfo info = new ParamInfo();
        info.type = 1;
        info.mute = mute;
        this.notifyItemChanged(i, info);
        break;
      }
    }
  }

  public void removeAllViewHolder(){
    for (int i = 0; i < mList.size(); i++) {
      UserInfo info = mList.get(i);
      if(info.holder != null) {
        mDelegate.get().onUserRemoved(info.userId, info.holder.getVideoView());
      }
    }
    mList.clear();
    this.notifyDataSetChanged();
  }

  @Override
  public int getItemCount() {
    return mList.size();
  }

  @Override
  public SimpleHolder onCreateViewHolder(ViewGroup parent, int viewType) {
    View view = LayoutInflater.from(mContext.get()).inflate(R.layout.user_item , parent,false);
    DisplayMetrics metrics = mContext.get().getResources().getDisplayMetrics();
    int widthPixels = metrics.widthPixels;
    ViewGroup.LayoutParams layoutParams = view.getLayoutParams();
    layoutParams.width = widthPixels/2;
    layoutParams.height = layoutParams.width/3*4;
    SimpleHolder holder = new SimpleHolder(view, mDelegate.get(), mStatsManager);
    holder.setIsRecyclable(true);
    return holder;
  }

  @Override
  public void onBindViewHolder(SimpleHolder holder, int position) {
    updateData(holder, position);
  }

  @Override
  public void onBindViewHolder(SimpleHolder holder, int position, List<Object> payloads) {
    if(mList.size() <= 0){
      return;
    }
    if (holder.getUserId() == mList.get(position).userId){
      if(payloads.size() > 0) {
        ParamInfo info = (ParamInfo) payloads.get(payloads.size() - 1);
        if (info.type == 0)
          holder.setRealTimeVolume(info.volume);
        else if (info.type == 1)
          holder.setRemoteMute(info.mute);
        return;
      }
    }else {
      updateData(holder, position);
      mDelegate.get().onUserRemoved(mList.get(position).userId, mList.get(position).holder.getVideoView());
      mDelegate.get().onUserAdd(mList.get(position).userId, holder.getVideoView());
      holder.updateState();
    }
  }
  public void updateData(SimpleHolder holder, int position){
    holder.setUserId(mList.get(position).userId);
    holder.setRemoteMute(mList.get(position).mute);
    holder.setRealTimeVolume(mList.get(position).volume);
    if(mList.get(position).holder != null) {
      holder.setVideoMute(mList.get(position).holder.isVideoMute);
      holder.setAudioMute(mList.get(position).holder.isAudioMute);
      holder.setBigStream(mList.get(position).holder.isBigStream);
    }
    mList.get(position).holder = holder;
  }

  private class UserInfo{
    Integer userId;
    int volume = 0;
    boolean mute = false;
    SimpleHolder holder = null;
    public UserInfo(Integer uid){
      userId = uid;
    }
    private UserInfo(UserInfo info){
       this.userId = info.userId;
       this.mute = info.mute;
       this.volume = info.volume;
    }
  }

  private class ParamInfo{
    int type;
    int volume;
    boolean mute;
  }

}
