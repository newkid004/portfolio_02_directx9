#include "buttonBase.h"

#include "managerList.h"
#include "gFunc.h"

UI_LIST_NODE buttonBase::updateActive(void)
{
	UI_LIST_NODE curNode = _bindWindow->getNode();

	if (gFunc::isMouseInRange(getAbsPos(), getAbsSize()))
		curNode = updateActiveAnyway();

	return curNode;
}

UI_LIST_NODE buttonBase::updateActiveAnyway(void)
{
	UI_LIST_NODE curNode = _bindWindow->getNode();

	if (MN_KEY->mouseUp() && _activeSet.up)			curNode = _activeSet.up();
	if (curNode != _bindWindow->getNode())			return curNode;

	if (MN_KEY->mousePress() && _activeSet.press)	curNode = _activeSet.press();
	if (curNode != _bindWindow->getNode())			return curNode;

	if (MN_KEY->mouseDown() && _activeSet.down)		curNode = _activeSet.down();
	if (curNode != _bindWindow->getNode())			return curNode;

	return curNode;
}

UI_LIST_NODE buttonBase::updateActiveScroll(buttonBase * own, activeScrollSet & scrollSet)
{
	UI_LIST_NODE curNode = own->_bindWindow->getNode();

	if (gFunc::isMouseInRange(own->getAbsPos(), own->getAbsSize()))
		curNode = updateActiveScrollAnyway(own, scrollSet);

	return curNode;
}

UI_LIST_NODE buttonBase::updateActiveScrollAnyway(buttonBase * own, activeScrollSet & scrollSet)
{
	UI_LIST_NODE curNode = own->_bindWindow->getNode();

	if (MN_KEY->wheelUp() && scrollSet.up)			curNode = scrollSet.up();
	if (curNode != own->_bindWindow->getNode())		return curNode;

	if (MN_KEY->wheelDown() && scrollSet.down)		curNode = scrollSet.down();
	if (curNode != own->_bindWindow->getNode())		return curNode;

	return curNode;
}

void buttonBase::drawUI(void)
{
	if (_info.backImage)
	{
		gFunc::drawSprite(
			_info.backImage,
			getAbsPos(),
			getAbsSize(),
			getAbsScale(),
			getAbsAlpha());
	}
}

D3DXVECTOR2 buttonBase::getAbsPos(void)
{
	return _bindWindow->getInfo().pos + _info.pos;
}

D3DXVECTOR2 buttonBase::getAbsSize(void)
{
	return  gFunc::Vec2Mlt(_info.size, getAbsScale());
}

D3DXVECTOR2 buttonBase::getAbsScale(void)
{
	return gFunc::Vec2Mlt(_info.scale, _bindWindow->getInfo().scale);
}
