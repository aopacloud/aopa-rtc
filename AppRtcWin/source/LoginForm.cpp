#include "stdafx.h"
#include "LoginForm.h"
#include "RoomForm.h"
#include "HttpClient.h"
#include "AppRtcWindow.h"


std::string servers_[] = {
    "{\"signaling\":\"wss://rtc-gateway-oversea.aopacloud.net:6080/rtc/channel\",\"rtconfig\":\"https://rtc-gateway-oversea.aopacloud.net:6080/rtc/get_rtc_config\",\"log\":\"https://rtc-gateway-oversea.aopacloud.net:6080/ali/v1/get_upload_url\",\"quic\":\"rtc-gateway-oversea-quic.aopacloud.net:16081\",\"report\":\"https://rtc-gateway-oversea.aopacloud.net:6080/rtc/rtc_event_report\"}"};
LoginForm::LoginForm(const std::wstring& class_name,
                     const std::wstring& theme_directory,
                     const std::wstring& layout_xml)
    : class_name_(class_name),
      theme_directory_(theme_directory),
      layout_xml_(layout_xml) {
  userId_ = GetTickCount() % 100000;
	isJoined = false;
}

LoginForm::~LoginForm() {}

std::wstring LoginForm::GetSkinFolder() {
  return theme_directory_;
}

std::wstring LoginForm::GetSkinFile() {
  return layout_xml_;
}

std::wstring LoginForm::GetWindowClassName() const {
  return class_name_;
}

void LoginForm::InitWindow() {
  ui::RichEdit* roomIdEdit =
      dynamic_cast<ui::RichEdit*>(FindControl(L"roomid_edit"));
  roomIdEdit->SetText(L"8899");
  roomIdEdit->SetEnabled(true);
  std::wstring audioQualitys[] = {
      L"default",      L"32kmono",       L"48kmono",
      L"48kstero",   L"48kmonohigh", L"48ksterohigh", L"48sterosuperhigh"};
  ui::Combo* audioCombox =
      dynamic_cast<ui::Combo*>(FindControl(L"audio_combox"));
  for (auto i = 0; i < 7; i++) {
    ui::ListContainerElement* element = new ui::ListContainerElement;
    element->SetClass(L"listitem");
    element->SetFixedHeight(30);
    element->SetBkColor(L"white");
    element->SetTextPadding({6, 0, 6, 0});
    element->SetText(audioQualitys[i]);
    audioCombox->Add(element);
  }
  audioCombox->SelectItem(5);

  std::wstring userRoles[] = {L"broad", L"audience"};
  ui::Combo* roleCombox = dynamic_cast<ui::Combo*>(FindControl(L"role_combox"));
  for (auto i = 0; i < 2; i++) {
    ui::ListContainerElement* element = new ui::ListContainerElement;
    element->SetClass(L"listitem");
    element->SetFixedHeight(30);
    element->SetBkColor(L"white");
    element->SetTextPadding({6, 0, 6, 0});
    element->SetText(userRoles[i]);
    roleCombox->Add(element);
  }
  roleCombox->SelectItem(0);

   std::wstring servers[] = {L"aopa fromal env"};
  ui::Combo* serverCombox = dynamic_cast<ui::Combo*>(FindControl(L"server_combox"));
  for (auto i = 0; i < 1; i++) {
    ui::ListContainerElement* element = new ui::ListContainerElement;
    element->SetClass(L"listitem");
    element->SetFixedHeight(30);
    element->SetBkColor(L"white");
    element->SetTextPadding({6, 0, 6, 0});
    element->SetText(servers[i]);
    serverCombox->Add(element);
  }
  serverCombox->SelectItem(0);

  ui::Button* enterBtn = dynamic_cast<ui::Button*>(FindControl(L"enter_login"));
  enterBtn->AttachClick([this](ui::EventArgs* args) {
	 if (!isJoined) {
		 joinRoom();
	 }
    return true;
  });


}

LRESULT LoginForm::OnClose(UINT uMsg,
                           WPARAM wParam,
                           LPARAM lParam,
                           BOOL& bHandled) {
  if (isQuit_)
   PostQuitMessage(0L);
  return __super::OnClose(uMsg, wParam, lParam, bHandled);
}

void LoginForm::ShowCustomWindow(const std::wstring& class_name,
                                 const std::wstring& theme_directory,
                                 const std::wstring& layout_xml) {
 
  LoginForm* window = new LoginForm(class_name, theme_directory, layout_xml);
  window->Create(NULL, class_name.c_str(),
                 WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 0);
  window->CenterWindow();
  window->ShowWindow();
}

void LoginForm::joinRoom() {
	isJoined = true;
	ui::RichEdit* roomIdEdit =
		dynamic_cast<ui::RichEdit*>(FindControl(L"roomid_edit"));
	ui::Combo* audioCombox =
		dynamic_cast<ui::Combo*>(FindControl(L"audio_combox"));
	ui::Combo* roleCombox =
		dynamic_cast<ui::Combo*>(FindControl(L"role_combox"));
    ui::Combo* serverCombox =
		dynamic_cast<ui::Combo*>(FindControl(L"server_combox"));
    int indexServer  = serverCombox->GetCurSel();
    if (indexServer != 0) {
      token_ = getToken(nbase::UTF16ToUTF8(roomIdEdit->GetText()), userId_,
                        roleCombox->GetCurSel() + 1, indexServer == 0);
      if (token_.empty()) {
        isJoined = false;
        return;
      }
	}
    ::setRtcServerAddress(servers_[indexServer].c_str());
	RoomForm* window = new RoomForm(L"room", L"rtc", L"room.xml");
	window->roomId_ = nbase::UTF16ToUTF8(roomIdEdit->GetText());
	window->roleType_ = roleCombox->GetCurSel() + 1;
	window->audioQuality_ = audioCombox->GetCurSel();
	window->userId_ = userId_;
	window->token_ = token_;
	window->Create(NULL, L"room",
		WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 0);
	window->CenterWindow();
	window->ShowWindow();
	isQuit_ = false;
	this->Close();
}

std::string LoginForm::getToken(const std::string& roomId, int userId, int role, bool online) {
	std::string ret;
	std::string url = "http://47.114.166.11:6080/bbrtc/sign/getToken";
	char param[1024];
	sprintf(param, "appName=%s&channel=%s&role=%s&uid=%d",
                online ? "online" : "bbrtc",
		roomId.c_str(),
		role == 1 ? "broadcaster" : "audience",
		userId);
	std::string msg = HttpClient::post(url, param);
	if (msg.empty()) {
		return ret;
	}
	int code;
	char token[128] = { 0 };
	const char* p = strstr(msg.c_str(), "\"code\":");
	if (sscanf(p, "\"code\":%d,", &code) != 1) {
		return ret;
	}
	if (code != 200)
		return ret;
	p = strstr(msg.c_str(), "\"token\":");
	if (sscanf(p, "\"token\":\"%[^\"]", token) != 1) {
		return ret;
	}
	ret = token;
	return ret;
}
