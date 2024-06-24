// AppRtcWin.cpp : 定义应用程序的入口点。
//
#include "stdafx.h"
#include "AppRtcWindow.h"
#include "LoginForm.h"
#include "MusicForm.h"
#include "MusicVolumeRealControl.h"
#include "RoomForm.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_ LPWSTR lpCmdLine,
                      _In_ int nCmdShow) {
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  // 创建主线程
  MainThread thread;
  thread.RunOnCurrentThreadWithLoop(nbase::MessageLoop::kUIMessageLoop);

  return 0;
}
bbrtc::IRtcEngine* MainThread::rtcEngine_ = NULL;

void MainThread::Init() {
  nbase::ThreadManager::RegisterThread(kThreadUI);

  std::wstring theme_dir = nbase::win32::GetCurrentModuleDirectory();
   ui::GlobalManager::Startup(
      theme_dir + L"resources\\",
      [this](const std::wstring& pstrClass) {
        if (pstrClass.compare(L"VolumeRealControl") == 0) {
          return new MusicVolumeRealControl();
        }
        return (MusicVolumeRealControl*)nullptr;
      },
      false);
  bbrtc::RtcEngineContext context;
  context.appId = appid;
  context.context = NULL;
  context.eventHandler = NULL;
  rtcEngine_ = createRtcEngine();
  rtcEngine_->initialize(context);
  rtcEngine_->setLogFilter(bbrtc::LOG_FILTER_DEBUG);
  LoginForm::ShowCustomWindow(L"login", L"rtc", L"login.xml");
}

void MainThread::Cleanup() {
  releaseRtcEngine(rtcEngine_);
  ui::GlobalManager::Shutdown();
  SetThreadWasQuitProperly(true);
  nbase::ThreadManager::UnregisterThread();
}
