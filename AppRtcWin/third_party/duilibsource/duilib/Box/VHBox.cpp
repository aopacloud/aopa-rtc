#include "stdafx.h"
#include "VHBox.h"


namespace ui
{

	VHLayout::VHLayout()
	{

	}

	CSize VHLayout::ArrangeChild(const std::vector<Control*>& items, UiRect rc)
	{
		// Determine the minimum size
		CSize szAvailable(rc.right - rc.left, rc.bottom - rc.top);
		int rowNum = 1;
		int width = 100;
		int height = 100;
		int hspace = 0;
		UiRect rcMargin;
		if (items.size()) {
			rcMargin = items[0]->GetMargin();
			CSize sz = items[0]->EstimateSize(szAvailable);
			width = sz.cx + rcMargin.left + rcMargin.right;
			height = sz.cy + rcMargin.top + rcMargin.bottom;
			rowNum = szAvailable.cx / width;
			hspace = (int)(szAvailable.cx - rowNum * width) * 1.f / (rowNum + 1);
		}
		int i = 0;
		int cyNeeded = 0;
		CSize szRemaining = szAvailable;
		for (auto it = items.begin(); it != items.end(); it++) {
			auto pControl = *it;
			if (!pControl->IsVisible()) continue;
			if (pControl->IsFloat()) {
				SetFloatPos(pControl, rc);
				continue;
			}

			CSize sz = pControl->EstimateSize(szRemaining);
			if (sz.cy < pControl->GetMinHeight()) sz.cy = pControl->GetMinHeight();
			if (sz.cy > pControl->GetMaxHeight()) sz.cy = pControl->GetMaxHeight();

			if (sz.cx < 0) sz.cx = 0;
			if (sz.cx < pControl->GetMinWidth()) sz.cx = pControl->GetMinWidth();
			if (pControl->GetMaxWidth() >= 0 && sz.cx > pControl->GetMaxWidth()) sz.cx = pControl->GetMaxWidth();
			
			UiRect rcCtrl;
			rcCtrl.left = rc.left + rcMargin.left + i % rowNum * width + hspace * (i % rowNum + 1);
			rcCtrl.top = rc.top + rcMargin.top + i / rowNum * height;
			rcCtrl.right = rcCtrl.left + sz.cx;
			rcCtrl.bottom = rcCtrl.top + sz.cy;
			pControl->SetPos(rcCtrl);
			if (i++ % rowNum == 0) {
				cyNeeded += sz.cy + rcMargin.top + rcMargin.bottom;
				szAvailable.cy -= height;
			}
		}
		CSize size(szAvailable.cx, cyNeeded);
		return size;
	}

	CSize VHLayout::AjustSizeByChild(const std::vector<Control*>& items, CSize szAvailable)
	{
		int rowNum = 1;
		int width = 100;
		int height = 100;
		UiRect rcMargin;
		if (items.size()) {
			rcMargin = items[0]->GetMargin();
			CSize sz = items[0]->EstimateSize(szAvailable);
			width = sz.cx + rcMargin.left + rcMargin.right;
			height = sz.cy + rcMargin.top + rcMargin.bottom;
			rowNum = szAvailable.cx / width;
		}
		int i = 0;
		int cyNeeded = 0;
		CSize szRemaining = szAvailable;
		for (auto it = items.begin(); it != items.end(); it++) {
			auto pControl = *it;
			if (!pControl->IsVisible() || pControl->IsFloat()) {
				continue;
			}

			CSize sz = pControl->EstimateSize(szRemaining);
			if (sz.cy < pControl->GetMinHeight()) sz.cy = pControl->GetMinHeight();
			if (sz.cy > pControl->GetMaxHeight()) sz.cy = pControl->GetMaxHeight();

			if (sz.cx < 0) sz.cx = 0;
			if (sz.cx < pControl->GetMinWidth()) sz.cx = pControl->GetMinWidth();
			if (pControl->GetMaxWidth() >= 0 && sz.cx > pControl->GetMaxWidth()) sz.cx = pControl->GetMaxWidth();

			if (i++ % rowNum == 0) {
				cyNeeded += sz.cy + rcMargin.top + rcMargin.bottom;
			}
		}
		cyNeeded += m_rcPadding.top + m_rcPadding.bottom;
		CSize size(szAvailable.cx, cyNeeded);
		return size;

	}

	VHBox::VHBox() : Box(new VHLayout())
	{

	}

}
