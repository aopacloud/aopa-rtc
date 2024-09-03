#pragma once
#include <vector>

class MusicSelectSink {
public:
	virtual ~MusicSelectSink() {}
	virtual void OnMusicSelectFiles(const std::wstring& path, const std::vector<std::wstring>& vecFiles, int playIndex = -1) = 0;
};
class MusicForm : public ui::WindowImplBase
{
public:
	MusicForm(const std::wstring& class_name, const std::wstring& theme_directory, const std::wstring& layout_xml);
	~MusicForm();

	virtual std::wstring GetSkinFolder() override;
	virtual std::wstring GetSkinFile() override;
	virtual std::wstring GetWindowClassName() const override;
	virtual void InitWindow() override;
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	void setSink(MusicSelectSink* sink) { sink_ = sink; }
	void setPath(const std::wstring& path, const std::vector<std::wstring>& vecFiles, int playIndex);
public:
	static MusicForm* ShowCustomWindow(const std::wstring& class_name, const std::wstring& theme_directory, const std::wstring& layout_xml);
private:
	void FindFolder(const wchar_t* lpPath);
	void updateList();
private:
	std::wstring class_name_;
	std::wstring theme_directory_;
	std::wstring layout_xml_;
	std::vector<std::wstring> vecMusicFiles_;
	MusicSelectSink* sink_ = nullptr;
	std::wstring path_;
};

class myControlData : public ui::UserDataBase {
public:
	myControlData(int data) :index(data) {}
	int index;
};
