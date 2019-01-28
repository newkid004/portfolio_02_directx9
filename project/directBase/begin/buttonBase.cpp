#include "buttonBase.h"

#include "managerList.h"
#include "gFunc.h"

buttonBase::buttonBase()
{
}


buttonBase::~buttonBase()
{
}

void buttonBase::updateActice(void)
{
	if (gFunc::isMouseInRange(_info.pos, _info.size))
	{
		if (MN_KEY->mouseUp())		_activeSet.up();
		if (MN_KEY->mousePress())	_activeSet.press();
		if (MN_KEY->mouseDown())	_activeSet.down();
	}
}

void buttonBase::drawUI(void)
{
	gFunc::drawSprite(
		_info.backImage,
		_info.pos,
		_info.size,
		_info.scale,
		_info.alpha);
}
