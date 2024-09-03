#pragma once

namespace ui
{

	class UILIB_API VHLayout : public Layout
	{
	public:
		VHLayout();
		/// ��д���෽�����ṩ���Ի����ܣ���ο���������
		virtual CSize ArrangeChild(const std::vector<Control*>& items, UiRect rc) override;
		virtual CSize AjustSizeByChild(const std::vector<Control*>& items, CSize szAvailable) override;
	};

	class UILIB_API VHBox : public Box
	{
	public:
		VHBox();
	};

}
