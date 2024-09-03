#ifndef UI_CORE_PLACE_HOLDER_H_
#define UI_CORE_PLACE_HOLDER_H_

#pragma once
#include "Window.h"

namespace ui 
{

class UILIB_API PlaceHolder : public virtual nbase::SupportWeakCallback
{
public:
	PlaceHolder();
	PlaceHolder(const PlaceHolder& r);
	PlaceHolder& operator=(const PlaceHolder& r) = delete;
	virtual ~PlaceHolder();

	/**
	 * @brief ��ȡ������ָ��
	 * @return ���ظ�����ָ��
	 */
	Box* GetParent() const { return m_pParent;}

	/**
	 * @brief �������ƻ�ȡ��������ָ��
	 * @param[in] strName Ҫ��ȡ��������������
	 * @return ������������ָ��
	 */
	Box* GetAncestor(const std::wstring& strName);

	/**
	 * @brief ��ȡ�ؼ����ƣ���Ӧ xml �� name ����
	 * @return ���ؿؼ�����
	 */
	std::wstring GetName() const;

	/**
	 * @brief ��ȡ�ؼ����ƣ���Ӧ xml �� name ����
	 * @return ���ؿؼ����ƣ�UTF8 ���룩
	 */
	std::string GetUTF8Name() const;

	/**
	 * @brief ���ÿؼ����ƣ��ڴ������ò���д�� xml ��
	 * @param[in] strName Ҫ���õ�����
	 * @return ��
	 */
	void SetName(const std::wstring& strName);

	/**
	 * @brief ���ÿؼ����ƣ��ڴ������ò���д�� xml �У�UTF8 ���룩
	 * @param[in] strName Ҫ���õ�����
	 * @return ��
	 */
	void SetUTF8Name(const std::string& strName);

	/**
	 * @brief ��ȡ�����Ĵ���ָ��
	 * @return ���ع������ڵ�ָ��
	 */
	virtual Window* GetWindow() const;

	/**
	 * @brief ����������������
	 * @param[in] pManager ����ָ��
	 * @param[in] pParent ������
	 * @param[in] bInit ���ú��Ƿ���� Init ��ʼ���ؼ�
	 * @return ��
	 */
	virtual void SetWindow(Window* pManager, Box* pParent, bool bInit = true);

	/**
	 * @brief ����������������
	 * @param[in] pManager ����ָ��
	 * @return ��
	 */
	virtual void SetWindow(Window* pManager);

	/**
	 * @brief ��ʼ������
	 * @return ��
	 */
	virtual void Init();

	/**
	 * @brief �� Init ���ã������� Init ��ͬ
	 * @return ��
	 */
	virtual void DoInit();

	/**
	 * @brief �ж��Ƿ�ɼ�
	 * @return ���� true Ϊ�ɼ������� false Ϊ���ɼ�
	 */
	virtual bool IsVisible() const;

	/**
	 * @brief ������
	 * @param[in] ������
	 * @return ������
	 */
	bool IsInternVisible() const;

	/**
	 * @brief �жϿؼ��Ƿ񸡶�����Ӧ xml �� float ����
	 * @return ���� true �Ǹ���״̬������ false Ϊ�Ǹ���״̬
	 */
	bool IsFloat() const;

	/**
	 * @brief ���ÿؼ��Ƿ񸡶�
	 * @param[in] bFloat ����Ϊ true Ϊ������false Ϊ������
	 * @return ��
	 */
	void SetFloat(bool bFloat = true);

	/**
	 * @brief ��ȡ�̶����ȣ���Ӧ xml �� width ����
	 * @return ���ؿؼ�����
	 */
	int GetFixedWidth() const;

	/**
	 * @brief ���ÿؼ��̶�����
	 * @param[in] cx Ҫ���õĿ���
	 * @param[in] bArrange �Ƿ��������У�Ĭ��Ϊ true
	 * @param[in] bNeedDpiScale ���� DPI ���ţ�Ĭ��Ϊ true
	 * @return ��
	 */
	void SetFixedWidth(int cx, bool bArrange = true, bool bNeedDpiScale = true);

	/**
	 * @brief ��ȡ�̶��߶�
	 * @return ���ع̶��߶�
	 */
	int GetFixedHeight() const;

	/**
	 * @brief ���ù̶��߶�
	 * @param[in] cy Ҫ���õĹ̶��߶�
	 * @param[in] bNeedDpiScale ���� DPI ���ţ�Ĭ��Ϊ true
	 * @return ��
	 */
	void SetFixedHeight(int cy, bool bNeedDpiScale = true);

	/**
	 * @brief ��ȡ��С����
	 * @return ������С����
	 */
	int GetMinWidth() const;

	/**
	 * @brief ������С����
	 * @param[in] cx Ҫ���õ���С����
	 * @return ��
	 */
	void SetMinWidth(int cx);

	/**
	 * @brief ��ȡ������
	 * @return ����������
	 */
	int GetMaxWidth() const;

	/**
	 * @brief ����������
	 * @param[in] cx Ҫ���õ�������
	 * @return ��
	 */
	void SetMaxWidth(int cx);

	/**
	 * @brief ��ȡ��С�߶�
	 * @return ������С�߶�
	 */
	int GetMinHeight() const;

	/**
	 * @brief ������С�߶�
	 * @param[in] cy Ҫ���õ���С�߶�
	 * @return ��
	 */
	void SetMinHeight(int cy);

	/**
	 * @brief ��ȡ���߶�
	 * @return �������߶�
	 */
	int GetMaxHeight() const;

	/**
	 * @brief �������߶�
	 * @param[in] cy Ҫ���õ����߶�
	 * @return ��
	 */
	void SetMaxHeight(int cy);

	/**
	 * @brief ��ȡʵ�ʿ���
	 * @return ����ʵ�ʿ���
	 */
	int GetWidth() const;

	/**
	 * @brief ��ȡʵ�ʸ߶�
	 * @return ����ʵ�ʸ߶�
	 */
	int GetHeight() const;

	/**
	 * @brief ��ȡˮƽ���뷽ʽ
	 * @return ����ˮƽ���뷽ʽ���ο� HorAlignType ö��
	 */
	HorAlignType GetHorAlignType() const;

	/**
	 * @brief ����ˮƽ���뷽ʽ
	 * @param[in] horAlignType Ҫ���õĶ��뷽ʽ���ο� HorAlignType ö��
	 * @return ��
	 */
	void SetHorAlignType(HorAlignType horAlignType);

	/**
	 * @brief ��ȡ��ֱ���뷽ʽ
	 * @return ���ش�ֱ���뷽ʽ���μ� VerAlignType ö��
	 */
	VerAlignType GetVerAlignType() const;

	/**
	 * @brief ���ô�ֱ���뷽ʽ
	 * @param[in] vorAlignType Ҫ���õĶ��뷽ʽ���ο� VerAlignType ö��
	 * @return ��
	 */
	void SetVerAlignType(VerAlignType verAlignType);

	/**
	 * @brief ������
	 * @param[in] ������
	 * @return ������
	 */
	bool IsReEstimateSize() const;

	/**
	 * @brief ������
	 * @param[in] ������
	 * @return ������
	 */
	void SetReEstimateSize(bool bReEstimateSize);

	/**
	 * @brief ������
	 * @param[in] ������
	 * @return ������
	 */
	virtual CSize EstimateSize(CSize szAvailable);

	/**
	 * @brief ��ȡ�ؼ�λ��
	 * @param[in] bContainShadow �Ƿ������Ӱλ�ã�Ĭ��Ϊ true
	 * @return ���ؿؼ�λ��
	 */
	virtual	UiRect GetPos(bool bContainShadow = true) const;

	/**
	 * @brief ���ÿؼ�λ��
	 * @param[in] rc Ҫ���õ�λ����Ϣ
	 * @return ��
	 */
	virtual void SetPos(UiRect rc);

	/**
	 * @brief ���в���
	 * @return ��
	 */
	virtual void Arrange();

	/**
	 * @brief �ø���������
	 * @return ��
	 */
	virtual void ArrangeAncestor();

	/**
	 * @brief �ж��Ƿ��Ѿ����й�
	 * @return true Ϊ�Ѿ����й���false Ϊ��δ����
	 */
	bool IsArranged() const;

	void SetUseCache(bool cache);
	bool IsUseCache() { return m_bUseCache; }
	void SetCacheDirty(bool dirty);
	bool IsCacheDirty() { return m_bUseCache && m_bCacheDirty; }

	/**
	 * @brief �ػ�ؼ�
	 * @return ��
	 */
	virtual void Invalidate();

	/**
	 * @brief ������
	 * @param[in] ������
	 * @return ������
	 */
	UiRect GetPosWithScrollOffset() const;

	/**
	 * @brief ������
	 * @param[in] ������
	 * @return ������
	 */
	CPoint GetScrollOffset() const;

	static bool IsChild(PlaceHolder* pAncestor, PlaceHolder* pChild);
protected:
	/**
	 * @brief ������
	 * @param[in] ������
	 * @return ������
	 */
	virtual void ArrangeSelf();

protected:
	std::wstring m_sName;
	Window *m_pWindow;
	Box* m_pParent;
	CSize m_cxyFixed;
	CSize m_cxyMin;
	CSize m_cxyMax;
	UiRect m_rcItem;
	HorAlignType m_horAlignType;
	VerAlignType m_verAlignType;
	bool m_bFloat;
	bool m_bReEstimateSize;
	bool m_bVisible;
	bool m_bInternVisible;
	bool m_bIsArranged;

	bool m_bUseCache;
	bool m_bCacheDirty;
	std::unique_ptr<IRenderContext> m_renderContext;
};

} // namespace ui

#endif // UI_CORE_PLACE_HOLDER_H_
