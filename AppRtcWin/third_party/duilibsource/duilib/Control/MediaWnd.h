#pragma once
namespace ui
{
	class Control;
	class MediaWnd : public Control
	{
	public:
		MediaWnd();
		~MediaWnd();
		void SetPos(UiRect rc) override;
		void SetVisible(bool bVisible = true) override;
		void DoInit() override;
		HWND GetWND() { return hWnd_; }
		
	private:
		HWND  hWnd_ = NULL;
	};

}