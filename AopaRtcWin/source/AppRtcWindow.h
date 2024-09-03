#pragma once

#include "stdafx.h"

enum ThreadId { kThreadUI };
static const char* appid = "6MHg9hZqMMcKjNyiauSyU8H5b3eTr4qM";
class MainThread : public nbase::FrameworkThread {
 public:
  MainThread() : nbase::FrameworkThread("MainThread") {}
  virtual ~MainThread() {}
  static bbrtc::IRtcEngine* getRtcEngine() { return rtcEngine_; }
 private:
  virtual void Init() override;

  virtual void Cleanup() override;

 private:
  static bbrtc::IRtcEngine* rtcEngine_;
};
