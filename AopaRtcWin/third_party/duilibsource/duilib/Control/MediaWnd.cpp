#include "StdAfx.h"
#include "MediaWnd.h"
namespace ui {
	LRESULT CALLBACK MediaWindowProc(
		_In_  HWND hwnd,
		_In_  UINT uMsg,
		_In_  WPARAM wParam,
		_In_  LPARAM lParam)
	{
		return  DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	MediaWnd::MediaWnd() {
		
	}
	MediaWnd::~MediaWnd() {
		if (hWnd_) {
			::PostMessage(hWnd_, WM_CLOSE, 0, 0);
			TCHAR classname[64];
			_stprintf(classname, _T("media_%p"), this);
			UnregisterClass(classname, GetModuleHandle(NULL));
			hWnd_ = NULL;
		}
	}
	void MediaWnd::SetPos(UiRect rc) {
		Control::SetPos(rc);
		if (hWnd_)
			::SetWindowPos(hWnd_, HWND_TOPMOST, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER);
	}
	void MediaWnd::SetVisible(bool bVisible) {
		Control::SetVisible(bVisible);
		if (hWnd_)
			::ShowWindow(hWnd_, bVisible ? SW_SHOW : SW_HIDE);
	}

	void MediaWnd::DoInit() {
		Control::DoInit();
		HINSTANCE hInstance = GetModuleHandle(NULL);
		HWND hParentWnd = m_pWindow->GetHWND();
		TCHAR classname[64];
		_stprintf(classname, _T("media_%p"), this);
		WNDCLASSEX wc;
		memset(&wc, 0, sizeof(WNDCLASSEX));
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hCursor = NULL;
		wc.hIcon = NULL;
		wc.lpszMenuName = NULL;
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.hbrBackground = ::CreateSolidBrush(RGB(0, 0, 0));
		wc.lpfnWndProc = MediaWindowProc;
		wc.lpszClassName = classname;
		wc.hInstance = hInstance;
		if (!RegisterClassEx(&wc)){
			OutputDebugString(_T("MediaWnd create failed.\n"));
			return;
		}

		hWnd_ = ::CreateWindowEx(
			0,
			classname,
			_T(" "),
			WS_VISIBLE | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
			0,
			0,
			1,
			1,
			hParentWnd,
			0,
			hInstance,
			NULL);
		if (!hWnd_) {
			int code = GetLastError();
			OutputDebugString(_T("MediaWnd create failed.\n"));
			return;
		}
		ShowWindow(hWnd_, SW_SHOW);
		UpdateWindow(hWnd_);
	}
}
