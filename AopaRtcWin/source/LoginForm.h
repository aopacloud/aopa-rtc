#pragma once

class LoginForm : public ui::WindowImplBase
{
public:
	LoginForm(const std::wstring& class_name, const std::wstring& theme_directory, const std::wstring& layout_xml);
	~LoginForm();

	virtual std::wstring GetSkinFolder() override;
	virtual std::wstring GetSkinFile() override;
	virtual std::wstring GetWindowClassName() const override;
	virtual void InitWindow() override;
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	void joinRoom();
	std::string getToken(const std::string& roomId, int userId, int role, bool online);
public:
	static void ShowCustomWindow(const std::wstring& class_name, const std::wstring& theme_directory, const std::wstring& layout_xml);

private:
	std::wstring class_name_;
	std::wstring theme_directory_;
	std::wstring layout_xml_;
	bool isQuit_ = true;
	std::string token_;
	int userId_;
	bool isJoined;
};


