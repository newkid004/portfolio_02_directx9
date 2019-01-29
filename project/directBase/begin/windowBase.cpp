#include "windowBase.h"

#include "managerList.h"
#include "gFunc.h"
#include "gMng.h"

#include "buttonBase.h"

windowBase::windowBase(const uiInfo & info) :
	_info(info)
{
	if (_info.size == D3DXVECTOR2())
	{
		D3DSURFACE_DESC sDesc;
		_info.backImage->GetLevelDesc(0, &sDesc);
		_info.size = D3DXVECTOR2(sDesc.Width, sDesc.Height);
	}

	if (_info.pos == D3DXVECTOR2())
	{
		_info.pos = D3DXVECTOR2(
			(WINSIZEX + _info.size.x) / 2.0f,
			(WINSIZEY + _info.size.y) / 2.0f);
	}
}


windowBase::~windowBase()
{
	for (auto i : _mButton)
		SAFE_DELETE(i.second);
}

void windowBase::update(void)
{
	updateAlways();

	if (!MN_KEY->getClickIgnore())
	{
		updateWindow();
		for (auto i : _mButton)
			i.second->updateActice();
		
		updateFocus();
	}
}

void windowBase::drawUI(void)
{
	gFunc::drawSprite(
		_info.backImage,
		_info.pos,
		_info.size,
		_info.scale,
		_info.alpha);
}

void windowBase::updateAlways(void)
{
	for (auto i : _mButton)
		i.second->updateAlways();
}

void windowBase::updateFocus(void)
{
	if (gFunc::isMouseInRange(_info.pos, _info.size))
	{
		// 해당 윈도우를 맨 앞으로
		if (MN_KEY->mousePress())
			this->show();

		// 뒷 창 무시
		MN_KEY->setClickIgnore();
	}
}

void windowBase::show(void)
{
	MN_UI->show(this);
}

void windowBase::close(void)
{
	MN_UI->close(this);
}

void windowBase::trans(void)
{
	MN_UI->trans(this);
}

bool windowBase::isShow(void)
{
	return !(_managedNode == MN_UI->getIgnoreNode());
}

bool windowBase::isClose(void)
{
	return _managedNode == MN_UI->getIgnoreNode();
}

buttonBase * windowBase::addButton(const std::string & name, buttonBase * addition)
{
	buttonBase* b = gMng::add((std::string)name, addition, _mButton);
	b->getWindow() = this;
	return b;
}

buttonBase * windowBase::findButton(const std::string & name)
{
	return gMng::find((std::string)name, _mButton);;
}