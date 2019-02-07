#include "buttonItemText.h"

#include "managerList.h"
#include "gFunc.h"

#include "buttonMoveBar.h"

#include "windowMvList.h"

buttonItemText::buttonItemText(windowBase * bind, int index, int * bindIndex, float * bindOffset, int countY) :
	buttonItem(bind, index, bindIndex, bindOffset, 1, countY)
{
	_activeSet.press = [this](void)->UI_LIST_NODE {
		if (_bindString)
			*_bindIndex = _index + (int)(*_bindOffset / getAbsSize().y) * (int)_viewCount.x;

		return _bindWindow->getNode();
	};
}

buttonItemText::~buttonItemText()
{
}

void buttonItemText::drawUI(void)
{
	if (_bindString)
	{
		windowMvList* bindWindow = (windowMvList*)_bindWindow;
		static constexpr float defColor = 255.0f;
		static constexpr float minColor = 128.0f;
		D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255);

		float minPos = (bindWindow->getInfo().size.y + BTN_MOVE_BAR_SIZE_Y) * 0.1f;
		float maxPos = (bindWindow->getInfo().size.y - _info.size.y);

		if (_info.pos.y < minPos)
		{
			float percent = _info.pos.y / minPos;
			int colorValue = minColor * (1.0f - percent) + defColor * percent;

			color = D3DCOLOR_XRGB(colorValue, colorValue, colorValue);
		}
		else if (maxPos * 0.9f < _info.pos.y)
		{
			float height = maxPos * 0.9f;
			float posHeight = maxPos - _info.pos.y;
			float percent = posHeight / height;
			int colorValue = minColor * (1.0f - percent) + defColor * percent;

			color = D3DCOLOR_XRGB(colorValue, colorValue, colorValue);
		}

		auto absPos = getAbsPos();
		gFunc::drawText(
			absPos.x - 200, absPos.y,
			*_bindString,
			0,
			color
		);
	}
}