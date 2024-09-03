package org.banban.demo;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.util.AttributeSet;
import android.view.View;

public class VolumeView extends View {
  private Paint mPaint1;
  private Paint mPaint2;
  private int mVolume = 0;
  private boolean mMute = false;

  public VolumeView(Context context, AttributeSet attrs) {
    super(context, attrs);
    mPaint1 = new Paint(Paint.ANTI_ALIAS_FLAG);
    mPaint1.setColor(Color.parseColor("#00FF00"));
    mPaint1.setStrokeWidth(3.f);

    mPaint2 = new Paint(Paint.ANTI_ALIAS_FLAG);
    mPaint2.setColor(Color.parseColor("#808080"));
    mPaint1.setStrokeWidth(3.f);

  }

  @Override
  protected void onDraw(Canvas canvas) {
    super.onDraw(canvas);
    int line = mVolume/10;
    int num = 25;
    int height = 7;
    if (getHeight() / num < height){
      num = getHeight()/height;
      line = mVolume/(255/num);
    }
    for (int i = 0; i < num ; i++) {
      int start_y = height*num  - i * height ;
      if (i < line) {
         mPaint1.setColor(Color.parseColor("#00FF00"));
         canvas.drawLine(0,start_y, getWidth(),start_y, mPaint1);
      }else{
          mPaint1.setColor(Color.parseColor("#808080"));
         canvas.drawLine(0,start_y, getWidth(),start_y, mPaint1);
      }
    }
    if(mMute){
      mPaint1.setColor(Color.parseColor("#FF0000"));
      canvas.drawLine(0, 0, getWidth(), height*num, mPaint1);
      canvas.drawLine(getWidth(), 0, 0, height*num, mPaint1);
    }
  }

  void setVolume(int vaule){
    mVolume = vaule;
    invalidate();
  }

  void setMuete(boolean mute){
    mMute = mute;
    invalidate();
  }

}
