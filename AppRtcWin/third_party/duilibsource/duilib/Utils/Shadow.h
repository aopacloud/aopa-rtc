#ifndef UI_UTILS_SHADOW_H_
#define UI_UTILS_SHADOW_H_

#pragma once

namespace ui 
{

class Box;
class Control;
class UILIB_API Shadow
{
public:
	Shadow();

	/**
	 * @brief �����Ƿ񸽼���ӰЧ��
	 * @param[in] bShadowAttached ���� true Ϊ�ǣ�false Ϊ��
	 * @return ��
	 */
	void SetShadowAttached(bool bShadowAttached) { m_bShadowAttached = bShadowAttached; }

	/**
	 * @brief �ж��Ƿ��Ѿ���������Ӱ
	 * @return ���� true ��ʾ�Ѿ����ӣ�����Ϊ false
	 */
	bool IsShadowAttached() const { return m_bShadowAttached; }

	/**
	 * @brief ������Ӱ�ľŹ�������
	 * @param[in] rect Ҫ���õľŹ�������
	 * @return ��
	 */
	void SetShadowCorner(const UiRect &rect);

	/**
	 * @brief ��ȡ��Ӱ�ľŹ�������
	 * @return ������Ӱ�ľŹ�������
	 */
	UiRect GetShadowCorner() const;

	/**
	 * @brief ���ݳ�ʼ������Ӱ��Χ������Ӱ�߿�
	 * @return ��
	 */
	void ResetShadowBox();

	/**
	 * @brief ������ӰͼƬ
	 * @param[in] image ͼƬ·��
	 * @return ��
	 */
	void SetShadowImage(const std::wstring &image);

	/**
	 * @brief ��ȡ��ӰͼƬλ��
	 * @return ������ӰͼƬλ��
	 */
	std::wstring GetShadowImage() const;

	/**
	 * @brief ����Ӱ���ӵ�����
	 * @param[in] pRoot ���ڵĶ�������
	 * @return ���ظ�����Ӱ�������ָ��
	 */
	Box* AttachShadow(Box* pRoot);

	/**
	 * @brief ���ô�����󻯻��ǻ�ԭ״̬
	 * @param[in] isMaximized ����Ϊ true ��ʾ��󻯣�false Ϊ��ԭ��ʼ״̬
	 * @return ��
	 */
	void MaximizedOrRestored(bool isMaximized);

	/**
	 * @brief ��ȡ������Ӱ�������ָ��
	 * @return ��������ָ��
	 */
	Control* GetRoot();

	/**
	 * @brief ����ͼƬ����
	 * @return ��
	 */
	void ClearImageCache();
private:
	bool m_bShadowAttached;
	bool m_bUseDefaultImage;
	std::wstring m_strImage;
	UiRect m_rcCurShadowCorner;
	UiRect m_rcDefaultShadowCorner;
	UiRect m_rcShadowCornerBackup;

	Box* m_pRoot;
};

}

#endif // UI_UTILS_SHADOW_H_