#pragma once

#define WM_MSG_RELAY_RORM_CLOSE         0x1900
class RelayForm : public ui::WindowImplBase
{
public:
	RelayForm(const std::wstring& class_name, const std::wstring& theme_directory, const std::wstring& layout_xml);
	~RelayForm();
	virtual std::wstring GetSkinFolder() override;
	virtual std::wstring GetSkinFile() override;
	virtual std::wstring GetWindowClassName() const override;
	virtual void InitWindow() override;

public:
	static void ShowCustomWindow(const std::wstring& class_name,
		const std::wstring& theme_directory,
		const std::wstring& layout_xml,
		HWND hParent);
	static std::string relay_room_name_;
private:
	std::wstring class_name_;
	std::wstring theme_directory_;
	std::wstring layout_xml_;
};

