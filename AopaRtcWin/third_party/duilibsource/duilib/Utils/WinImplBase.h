#ifndef UI_UTILS_WINIMPLBASE_H_
#define UI_UTILS_WINIMPLBASE_H_

#pragma once

namespace ui
{

#define UI_WNDSTYLE_FRAME		(WS_VISIBLE | WS_OVERLAPPEDWINDOW)
#define UI_WNDSTYLE_DIALOG		(WS_VISIBLE | WS_POPUPWINDOW | WS_CAPTION | WS_DLGFRAME | WS_CLIPSIBLINGS | WS_CLIPCHILDREN)

#define UI_CLASSSTYLE_FRAME		(CS_VREDRAW | CS_HREDRAW)
#define UI_CLASSSTYLE_DIALOG	(CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_SAVEBITS)

#ifndef WM_DPICHANGED
#define WM_DPICHANGED       0x02E0
#endif

class UILIB_API WindowImplBase : public Window, public IUIMessageFilter
{
public:
	WindowImplBase();
	virtual ~WindowImplBase();

	/**
	 * @brief �����յ����ڴ�����Ϣʱ������
	 * @return ��
	 */
	virtual void InitWindow(){}

	/**
	 * @brief �����յ�����������Ϣʱ������
	 * @param[in] hWnd Ҫ���ٵĴ��ھ��
	 * @return ��
	 */
	virtual void OnFinalMessage( HWND hWnd ) override;

	/**
	 * @brief ��ȡ������ʽ
	 * @return ���ش�����ʽ
	 */
	virtual LONG GetStyle();

	/**
	 * @brief ��ȡ��������ʽ
	 * @return ���ش�������ʽ
	 */
	virtual UINT GetClassStyle() const override;

	/**
	 * @brief ������
	 * @param[in] ������
	 * @return ������
	 */
	virtual std::wstring GetResourceID() const;

	/**
	 * @brief ��Ҫ�����Ŀؼ����Ǳ�׼�Ŀؼ�����ʱ����øú���
	 * @param[in] pstrClass �ؼ�����
	 * @return ����һ���Զ���ؼ�ָ�룬һ������¸��� pstrClass ���������Զ���Ŀؼ�
	 */
	virtual Control* CreateControl(const std::wstring& pstrClass);

	/**
	 * @brief ����������Ϣ
	 * @param[in] uMsg ��Ϣ����
	 * @param[in] wParam ��Ϣ���Ӳ���
	 * @param[in] lParam ��Ϣ���Ӳ���
	 * @param[out] bHandled ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
	 * @return ������Ϣ�������
	 */
	virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;

	/**
	 * @brief ���յ����ڹر���Ϣʱ������
	 * @param[in] uMsg ��Ϣ����
	 * @param[in] wParam ��Ϣ���Ӳ���
	 * @param[in] lParam ��Ϣ���Ӳ���
	 * @param[out] bHandled ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
	 * @return ������Ϣ�������
	 */
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	/**
	 * @brief ���յ����ڱ�������Ϣʱ������
	 * @param[in] uMsg ��Ϣ����
	 * @param[in] wParam ��Ϣ���Ӳ���
	 * @param[in] lParam ��Ϣ���Ӳ���
	 * @param[out] bHandled ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
	 * @return ������Ϣ�������
	 */
	virtual LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	/**
	 * @brief ���յ����ǻ״̬��Ϣʱ������
	 * @param[in] uMsg ��Ϣ����
	 * @param[in] wParam ��Ϣ���Ӳ���
	 * @param[in] lParam ��Ϣ���Ӳ���
	 * @param[out] bHandled ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
	 * @return ������Ϣ�������
	 */
	virtual LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	/**
	 * @brief ���յ�Ҫ����ͻ������С��Ϣʱ��WM_NCCALCSIZE��������
	 * @param[in] uMsg ��Ϣ����
	 * @param[in] wParam ��Ϣ���Ӳ���
	 * @param[in] lParam ��Ϣ���Ӳ���
	 * @param[out] bHandled ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
	 * @return ������Ϣ�������
	 */
	virtual LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	/**
	 * @brief ����λ�û� Z �������ı�ʱ������
	 * @param[in] uMsg ��Ϣ����
	 * @param[in] wParam ��Ϣ���Ӳ���
	 * @param[in] lParam ��Ϣ���Ӳ���
	 * @param[out] bHandled ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
	 * @return ������Ϣ�������
	 */
	virtual LRESULT OnWindowPosChanging(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	/**
	 * @brief �����յ����Ʊ�����������Ϣʱ������
	 * @param[in] uMsg ��Ϣ����
	 * @param[in] wParam ��Ϣ���Ӳ���
	 * @param[in] lParam ��Ϣ���Ӳ���
	 * @param[out] bHandled ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
	 * @return ������Ϣ�������
	 */
	virtual LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	/**
	 * @brief �����յ�����������˫����Ϣʱ������
	 * @param[in] uMsg ��Ϣ����
	 * @param[in] wParam ��Ϣ���Ӳ���
	 * @param[in] lParam ��Ϣ���Ӳ���
	 * @param[out] bHandled ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
	 * @return ������Ϣ�������
	 */
	virtual LRESULT OnNcLButtonDbClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	/**
	 * @brief �����յ� WM_NCHITTEST ��Ϣʱ������
	 * @param[in] uMsg ��Ϣ����
	 * @param[in] wParam ��Ϣ���Ӳ���
	 * @param[in] lParam ��Ϣ���Ӳ���
	 * @param[out] bHandled ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
	 * @return ������Ϣ�������
	 */
	virtual LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	/**
	 * @brief �����յ� WM_GETMINMAXINFO ��Ϣʱ������
	 * @param[in] uMsg ��Ϣ����
	 * @param[in] wParam ��Ϣ���Ӳ���
	 * @param[in] lParam ��Ϣ���Ӳ���
	 * @param[out] bHandled ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
	 * @return ������Ϣ�������
	 */
	virtual LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	/**
	 * @brief �����յ����������Ϣʱ������
	 * @param[in] uMsg ��Ϣ����
	 * @param[in] wParam ��Ϣ���Ӳ���
	 * @param[in] lParam ��Ϣ���Ӳ���
	 * @param[out] bHandled ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
	 * @return ������Ϣ�������
	 */
	virtual LRESULT OnMouseWheel(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	/**
	 * @brief �����յ����ڴ�С�ı���Ϣʱ������
	 * @param[in] uMsg ��Ϣ����
	 * @param[in] wParam ��Ϣ���Ӳ���
	 * @param[in] lParam ��Ϣ���Ӳ���
	 * @param[out] bHandled ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
	 * @return ������Ϣ�������
	 */
	virtual LRESULT OnMouseHover(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	/**
	 * @brief �����յ�DPI�ı���Ϣʱ�����ã�ֻ���� Startup ��ָ������ DPI �����Żᴥ����
	 * @param[in] uMsg ��Ϣ����
	 * @param[in] wParam ��Ϣ���Ӳ���
	 * @param[in] lParam ��Ϣ���Ӳ���
	 * @param[out] bHandled ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
	 * @return ������Ϣ�������
	 */
	virtual LRESULT OnDpiChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	/**
	 * @brief �����յ����ڴ�С�ı���Ϣʱ������
	 * @param[in] uMsg ��Ϣ����
	 * @param[in] wParam ��Ϣ���Ӳ���
	 * @param[out] bHandled ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
	 * @return ������Ϣ�������
	 */
	virtual LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	/**
	 * @brief �����յ��ַ�������Ϣʱ��WM_CHAR��������
	 * @param[in] uMsg ��Ϣ����
	 * @param[in] wParam ��Ϣ���Ӳ���
	 * @param[in] lParam ��Ϣ���Ӳ���
	 * @param[out] bHandled ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
	 * @return ������Ϣ�������
	 */
	virtual LRESULT OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	/**
	 * @brief ���մ��ڿ���������Ϣʱ��WM_SYSCOMMAND��������
	 * @param[in] uMsg ��Ϣ����
	 * @param[in] wParam ��Ϣ���Ӳ���
	 * @param[in] lParam ��Ϣ���Ӳ���
	 * @param[out] bHandled ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
	 * @return ������Ϣ�������
	 */
	virtual LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	/**
	 * @brief ���ռ��̰���������Ϣʱ������
	 * @param[in] uMsg ��Ϣ����
	 * @param[in] wParam ��Ϣ���Ӳ���
	 * @param[in] lParam ��Ϣ���Ӳ���
	 * @param[out] bHandled ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
	 * @return ������Ϣ�������
	 */
	virtual LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	/**
	 * @brief ����ʧȥ������Ϣʱ������
	 * @param[in] uMsg ��Ϣ����
	 * @param[in] wParam ��Ϣ���Ӳ���
	 * @param[in] lParam ��Ϣ���Ӳ���
	 * @param[out] bHandled ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
	 * @return ������Ϣ�������
	 */
	virtual LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	/**
	 * @brief ���ջ�ȡ������Ϣʱ������
	 * @param[in] uMsg ��Ϣ����
	 * @param[in] wParam ��Ϣ���Ӳ���
	 * @param[in] lParam ��Ϣ���Ӳ���
	 * @param[out] bHandled ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
	 * @return ������Ϣ�������
	 */
	virtual LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	/**
	 * @brief ���յ�������������Ϣʱ������
	 * @param[in] uMsg ��Ϣ����
	 * @param[in] wParam ��Ϣ���Ӳ���
	 * @param[in] lParam ��Ϣ���Ӳ���
	 * @param[out] bHandled ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
	 * @return ������Ϣ�������
	 */
	virtual LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	/**
	 * @brief ���յ�������������Ϣʱ������
	 * @param[in] uMsg ��Ϣ����
	 * @param[in] wParam ��Ϣ���Ӳ���
	 * @param[in] lParam ��Ϣ���Ӳ���
	 * @param[out] bHandled ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
	 * @return ������Ϣ�������
	 */
	virtual LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	/**
	 * @brief ���յ�����ƶ���Ϣʱ������
	 * @param[in] uMsg ��Ϣ����
	 * @param[in] wParam ��Ϣ���Ӳ���
	 * @param[in] lParam ��Ϣ���Ӳ���
	 * @param[out] bHandled ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
	 * @return ������Ϣ�������
	 */
	virtual LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	/**
	 * @brief ������Ϣ���ɷ�����
	 * @param[in] uMsg ��Ϣ����
	 * @param[in] wParam ��Ϣ���Ӳ���
	 * @param[in] lParam ��Ϣ���Ӳ���
	 * @param[out] bHandled ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
	 * @return ������Ϣ�������
	 */
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

public:
	/**
	* @brief �����
	* @return void �޷���ֵ
	*/
	virtual void ActiveWindow();

	/**
	* @brief ���ô��ڱ���
	* @param[in] title ���ڱ���
	* @return void �޷���ֵ
	*/
	virtual void SetTaskbarTitle(const std::wstring &title);

	/**
	* @brief �ö�����
	* @param[in] forever �Ƿ�һֱ�ö�
	* @return void �޷���ֵ
	*/
	void ToTopMost(bool forever);
		
protected:
	/**
	 * @brief ��������ʱ�����ã�������ʵ�����Ի�ȡ����Ƥ��Ŀ¼
	 * @return ������ʵ�ֲ����ش���Ƥ��Ŀ¼
	 */
	virtual std::wstring GetSkinFolder() = 0;

	/**
	 * @brief ��������ʱ�����ã�������ʵ�����Ի�ȡ����Ƥ�� XML �����ļ�
	 * @return ������ʵ�ֲ����ش���Ƥ�� XML �����ļ�
	 */
	virtual std::wstring GetSkinFile() = 0;

	/**
	 * @brief ��������ʱ�����ã�������ʵ�����Ի�ȡ����Ψһ��������
	 * @return ������ʵ�ֲ����ش���Ψһ��������
	 */
	virtual std::wstring GetWindowClassName(void) const = 0 ;

private:
	/**
	 * @brief �յ����ڴ�����Ϣʱ�����ã���ʹ�� InitWindow �ӿ���ʵ���Զ�������
	 * @param[in] uMsg ��ϢID
	 * @param[in] wParam ��Ϣ���Ӳ���
	 * @param[in] lParam ��Ϣ���Ӳ���
	 * @param[out] bHandled ��Ϣ�Ƿ��Ѿ�������
	 * @return ������Ϣ�������
	 */
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	/**
	 * @brief ���ڹ��ܰ�ť�����ʱ����
	 * @param[in] param Я���Ĳ���
	 * @return ʼ�շ��� true
	 */
	bool OnButtonClick(EventArgs* param);
};

}

#endif // UI_UTILS_WINIMPLBASE_H_
