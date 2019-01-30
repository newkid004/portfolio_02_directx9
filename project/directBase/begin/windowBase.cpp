#include "windowBase.h"

#include "managerList.h"
#include "gFunc.h"
#include "gMng.h"

#include "buttonBase.h"


windowBase::windowBase(const uiInfo & info) :
	_info(info)
{
	if (_info.size == D3DXVECTOR2() && _info.backImage != nullptr)
	{
		D3DSURFACE_DESC sDesc;
		_info.backImage->GetLevelDesc(0, &sDesc);
		_info.size = D3DXVECTOR2(sDesc.Width, sDesc.Height);
	}

	if (_info.pos == D3DXVECTOR2())
	{
		_info.pos = D3DXVECTOR2(
			(WINSIZEX - _info.size.x) / 2.0f,
			(WINSIZEY - _info.size.y) / 2.0f);
	}
}


windowBase::~windowBase()
{
	for (auto i : _mButton)
		SAFE_DELETE(i.second);
}

UI_LIST_NODE windowBase::update(void)
{
	UI_LIST_NODE resultNode = _managedNode;
	resultNode = updateAlways();

	if (resultNode != _managedNode)
		return resultNode;

	if (!MN_KEY->getClickIgnore())
	{
		resultNode = updateWindow();
		if (resultNode != _managedNode)
			return resultNode;

		for (auto i : _mButton)
		{
			resultNode = i.second->updateActice();

			if (resultNode != _managedNode)
				return resultNode;
		}
		
		resultNode = updateFocus();

		if (resultNode != _managedNode)
			return resultNode;
	}
	
	return resultNode;
}

void windowBase::drawUI(void)
{
	if (_info.backImage)
	{
		gFunc::drawSprite(
			_info.backImage,
			_info.pos,
			_info.size,
			_info.scale,
			_info.alpha);
	}

	for (auto i : _mButton)
		i.second->drawUI();
}

UI_LIST_NODE windowBase::updateAlways(void)
{
	UI_LIST_NODE resultNode = _managedNode;

	for (auto i : _mButton)
	{
		resultNode = i.second->updateAlways();

		if (resultNode != _managedNode)
			return resultNode;
	}

	return _managedNode;
}

UI_LIST_NODE windowBase::updateFocus(void)
{
	UI_LIST_NODE resultNode = _managedNode;

	if(gFunc::isMouseInRange(_info.pos, getAbsSize()))
	{
		// 해당 윈도우를 맨 앞으로
		if (MN_KEY->mousePress())
			resultNode = this->show();

		// 뒷 창 무시
		MN_KEY->setClickIgnore();
	}

	return resultNode;
}

UI_LIST_NODE windowBase::show(void)
{
	return MN_UI->show(this);
}

UI_LIST_NODE windowBase::close(void)
{
	return MN_UI->close(this);
}

UI_LIST_NODE windowBase::trans(void)
{
	return MN_UI->trans(this);
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

D3DXVECTOR2 windowBase::getAbsSize(void)
{
	return gFunc::Vec2Mlt(_info.size, _info.scale);
}