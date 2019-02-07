#include "windowSelection.h"

#include "managerList.h"
#include "gFunc.h"

#include "buttonScrollVertical.h"
#include "buttonMoveBar.h"

typedef windowBase::UI_LIST_NODE UI_LIST_NODE;

windowSelection::windowSelection(const uiInfo & info, windowBase * bindWindow) :
	windowStatic(info),
	_bindWindow(bindWindow)
{
	_info.backImage = MN_SRC->getSpriteTexture("resource/texture/maptool/common/catalog_outline.png");
}

void windowSelection::init(int viewX, int viewY)
{
	initBind();
	resize(viewX, viewY);
}

void windowSelection::drawUI(void)
{
	if (_bindIndex && _bindOffset && _isVisible && 
		0 <= *_bindIndex)
	{
		RECT clipRect = { 0, };

		if (_info.pos.y < BTN_MOVE_BAR_SIZE_Y)
			clipRect.top = std::fmodf(*_bindOffset, _info.size.y);
		else if (_bindWindow->getInfo().size.y < _info.pos.y + _info.size.y)
			clipRect.bottom = (_info.pos.y + _info.size.y) - _bindWindow->getInfo().size.y;

		gFunc::drawSprite(
			_info.backImage,
			_info.pos + _bindWindow->getInfo().pos,
			_info.size,
			_info.scale,
			_info.alpha,
			NULL,
			&clipRect, false);
	}
}

void windowSelection::resize(int viewX, int viewY)
{
	D3DXVECTOR2 texSize; gFunc::getTextureSize(&texSize, _info.backImage);

	_viewCount = D3DXVECTOR2(viewX, viewY);

	_info.scale = D3DXVECTOR2(
		((_bindWindow->getInfo().size.x - BTN_SCROLL_SIZE_X) / _viewCount.x) / texSize.x,
		((_bindWindow->getInfo().size.y - BTN_MOVE_BAR_SIZE_Y) / _viewCount.y) / texSize.y);

	_info.size = gFunc::Vec2Mlt(_info.scale, texSize);
}

UI_LIST_NODE windowSelection::updateWindow(void)
{
	_info.alpha = (std::cosf(MN_TIME->getRunningTime() * 3.0f) + 1.0f) / 2.0f;

	_info.pos.x = (*_bindIndex % (int)_viewCount.x) * _info.size.x;
	_info.pos.y = (*_bindIndex / (int)_viewCount.x) * _info.size.y - *_bindOffset + BTN_MOVE_BAR_SIZE_Y;

	_isVisible = true;
	if (_info.pos.y + _info.size.y <= BTN_MOVE_BAR_SIZE_Y)
		_isVisible = false;
	else if (_bindWindow->getInfo().size.y <= _info.pos.y)
		_isVisible = false;

	return _bindWindow->getNode();
}
