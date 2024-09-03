#pragma once

namespace ui
{

	class UILIB_API VHLayout : public Layout
	{
	public:
		VHLayout();
		/// 重写父类方法，提供个性化功能，请参考父类声明
		virtual CSize ArrangeChild(const std::vector<Control*>& items, UiRect rc) override;
		virtual CSize AjustSizeByChild(const std::vector<Control*>& items, CSize szAvailable) override;
	};

	class UILIB_API VHBox : public Box
	{
	public:
		VHBox();
	};

}
