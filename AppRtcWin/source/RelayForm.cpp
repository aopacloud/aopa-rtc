#include "stdafx.h"
#include "RelayForm.h"

std::string RelayForm::relay_room_name_;
RelayForm::RelayForm(const std::wstring& class_name,
                     const std::wstring& theme_directory,
                     const std::wstring& layout_xml)
    : class_name_(class_name),
      theme_directory_(theme_directory),
      layout_xml_(layout_xml) {
	relay_room_name_ = "";
}

RelayForm::~RelayForm() {}

std::wstring RelayForm::GetSkinFolder() {
  return theme_directory_;
}

std::wstring RelayForm::GetSkinFile() {
  return layout_xml_;
}

std::wstring RelayForm::GetWindowClassName() const {
  return class_name_;
}

void RelayForm::InitWindow() {
  ui::RichEdit* roomIdEdit =
      dynamic_cast<ui::RichEdit*>(FindControl(L"roomid_edit"));

  ui::Button* cancelBtn = dynamic_cast<ui::Button*>(FindControl(L"cancel_bnt"));
  cancelBtn->AttachClick([this](ui::EventArgs* args) {

    this->Close();
    return true;
  });

  ui::Button* enterBtn = dynamic_cast<ui::Button*>(FindControl(L"enter_bnt"));
  enterBtn->AttachClick([this, roomIdEdit](ui::EventArgs* args) {
	  relay_room_name_ = nbase::UTF16ToUTF8(roomIdEdit->GetText());
	  if (relay_room_name_.empty()) {
		  ::MessageBox(NULL, L"The room name cannot be empty.", L"warning", IDOK);
		  return true;
	  }
	  auto p_hwnd = GetWindowOwner(m_hWnd);
	  if(p_hwnd && IsWindow(p_hwnd))
	     ::PostMessage(p_hwnd, WM_MSG_RELAY_RORM_CLOSE, 1, 0);
	  this->Close();
	  return true;
  });

}

void RelayForm::ShowCustomWindow(const std::wstring& class_name,
                                 const std::wstring& theme_directory,
                                 const std::wstring& layout_xml,
	                             HWND hParent) {
 
  RelayForm* window = new RelayForm(class_name, theme_directory, layout_xml);
  window->Create(hParent, class_name.c_str(),
                 WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 0);
  window->CenterWindow();
  window->ShowModalFake(hParent);
}

