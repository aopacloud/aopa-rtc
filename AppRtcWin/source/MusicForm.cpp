#include "stdafx.h"
#include "MusicForm.h"
#include <Shlobj.h>
#include <Windows.h>
#pragma comment(lib, "Shlwapi")
MusicForm::MusicForm(const std::wstring& class_name, const std::wstring& theme_directory, const std::wstring& layout_xml)
	: class_name_(class_name)
	, theme_directory_(theme_directory)
	, layout_xml_(layout_xml)
{
}


MusicForm::~MusicForm()
{
}

std::wstring MusicForm::GetSkinFolder()
{
	return theme_directory_;
}

std::wstring MusicForm::GetSkinFile()
{
	return layout_xml_;
}

std::wstring MusicForm::GetWindowClassName() const
{
	return class_name_;
}

void MusicForm::InitWindow()
{
	ui::RichEdit* pathEdit = dynamic_cast<ui::RichEdit*>(FindControl(L"path_edit"));
	ui::Button* enterBtn = dynamic_cast<ui::Button*>(FindControl(L"select_btn"));
	enterBtn->AttachClick([this, pathEdit](ui::EventArgs* args) {
		wchar_t szDir[MAX_PATH];
		BROWSEINFO bi;
		ZeroMemory(&bi, sizeof(BROWSEINFO));
		LPITEMIDLIST pidl;
		bi.hwndOwner = this->m_hWnd;
		bi.pidlRoot = NULL;
		bi.pszDisplayName = szDir;
		bi.lpszTitle = L"请选择目录";
		bi.ulFlags = BIF_STATUSTEXT | BIF_USENEWUI | BIF_RETURNONLYFSDIRS;
		bi.lpfn = NULL;
		bi.lParam = 0;
		bi.iImage = 0;
		pidl = SHBrowseForFolderW(&bi);
		if (pidl != NULL && SHGetPathFromIDList(pidl, szDir)) {
			path_ = szDir;
			pathEdit->SetText(szDir);
			vecMusicFiles_.clear();
			FindFolder(szDir);
			updateList();
		}
		else {
			::MessageBox(NULL, L"请选择正确文件夹", L"音乐目录", MB_OKCANCEL);
		}
		return true;
	});


}

LRESULT MusicForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}

MusicForm* MusicForm::ShowCustomWindow(const std::wstring& class_name, const std::wstring& theme_directory, const std::wstring& layout_xml)
{
	MusicForm* window = new MusicForm(class_name, theme_directory, layout_xml);
	window->Create(NULL, class_name.c_str(), ((WS_OVERLAPPEDWINDOW & (~WS_MAXIMIZEBOX)) | WS_TABSTOP), 0);
	window->CenterWindow();
	window->ShowWindow();
	return window;
}


void MusicForm::FindFolder(const wchar_t* lpPath) {
	wchar_t szFind[MAX_PATH] = { 0 };
	wchar_t szFile[MAX_PATH] = { 0 };
	WIN32_FIND_DATA FindFileData;
	wcscpy(szFind, lpPath);
	wcscat(szFind, L"\\*.*");

	HANDLE hFind = ::FindFirstFile(szFind, &FindFileData);
	if (INVALID_HANDLE_VALUE == hFind)
		return;
	while (TRUE)
	{
		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (FindFileData.cFileName[0] != '.')
			{
				memset(szFile, 0, sizeof(szFile));
				wcscpy(szFile, lpPath);
				wcscat(szFile, L"\\");
				wcscat(szFile, FindFileData.cFileName);
				FindFolder(szFile);
			}
		}
		else if (wcsstr(FindFileData.cFileName, L".mp3") ||
			wcsstr(FindFileData.cFileName, L".wav") ||
			wcsstr(FindFileData.cFileName, L".ape") ||
            wcsstr(FindFileData.cFileName, L".flac"))
		{
			memset(szFile, 0, sizeof(szFile));
			wcscpy(szFile, lpPath);
			wcscat(szFile, L"\\");
			wcscat(szFile, FindFileData.cFileName);
			vecMusicFiles_.push_back(szFile);
		}
		if (!FindNextFile(hFind, &FindFileData))
			break;
	}
	FindClose(hFind);
}



void MusicForm::updateList() {
	ui::ListBox* list = dynamic_cast<ui::ListBox*>(FindControl(L"music_list"));
	list->RemoveAll();
	for (size_t i = 0; i < vecMusicFiles_.size(); i++)
	{
		ui::ListContainerElement* element = new ui::ListContainerElement;
		element->SetText(vecMusicFiles_[i]);
		element->SetClass(L"listitem");
		element->SetFixedHeight(20);
		myControlData* data = new myControlData((int)i);
		element->SetUserDataBase(data);
		list->Add(element);
		element->AttachDoubleClick([this](ui::EventArgs* args) {
			myControlData* data = (myControlData*)args->pSender->GetUserDataBase();
			if (path_.empty() || !data)
				return true;
			if (sink_) {
				sink_->OnMusicSelectFiles(path_, vecMusicFiles_, data->index);
			}
			Close();
			return true;
		});
	}
}

void MusicForm::setPath(const std::wstring& path, const std::vector<std::wstring>& vecFiles, int playIndex) {
	if (path.empty())
		return;
	ui::ListBox* list = dynamic_cast<ui::ListBox*>(FindControl(L"music_list"));
	ui::RichEdit* pathEdit = dynamic_cast<ui::RichEdit*>(FindControl(L"path_edit"));
	pathEdit->SetText(path);
	vecMusicFiles_.assign(vecFiles.begin(), vecFiles.end());
	//FindFolder(path.c_str());
	updateList();
	list->SelectItem(playIndex);
	path_ = path;
}
