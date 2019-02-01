#include "IbuttonScroll.h"

#include "managerList.h"
#include "gFunc.h"

typedef windowBase::UI_LIST_NODE UI_LIST_NODE;

IbuttonScroll::IbuttonScroll(buttonBase* bindButton) :
	_bindButton(bindButton)
{
}

IbuttonScroll::~IbuttonScroll()
{
}

UI_LIST_NODE IbuttonScroll::updateActiveScroll(void)
{
	UI_LIST_NODE curNode = _bindButton->getWindow()->getNode();

	if (gFunc::isMouseInRange(_bindButton->getAbsPos(), _bindButton->getAbsSize()))
		curNode = updateActiveScrollAnyway();

	return curNode;
}

UI_LIST_NODE IbuttonScroll::updateActiveScrollAnyway(void)
{
	UI_LIST_NODE curNode = _bindButton->getWindow()->getNode();

	if (MN_KEY->wheelUp() && _activeScrollSet.up)			curNode = _activeScrollSet.up();
	if (curNode != _bindButton->getWindow()->getNode())		return curNode;

	if (MN_KEY->wheelDown() && _activeScrollSet.down)		curNode = _activeScrollSet.down();
	if (curNode != _bindButton->getWindow()->getNode())		return curNode;

	return curNode;
}
