#include "maptool_window.h"

#include "managerList.h"
#include "gFunc.h"

#include "windowStatic.h"
#include "windowRenderTarget.h"
#include "windowMoveable.h"

#include "buttonScrollVertical.h"

maptool_window::maptool_window()
{
	MN_UI->add("maptool_bottomBar",		_windowSet.bottomBar	= createBottomBar())->show();
	MN_UI->add("maptool_bottomTrans",	_windowSet.bottomTrans	= createBottomTrans())->show();
	MN_UI->add("maptool_minimap",		_windowSet.minimap		= createMinimap())->show();

	MN_UI->add("maptool_mnProp",		_windowSet.mv_prop		= create_mvProp());
	// MN_UI->add("maptool_mnCharacter",	_windowSet.mv_character	= create_mvCharacter());
	// MN_UI->add("maptool_mnEvent",		_windowSet.mv_event		= create_mvEvent());
	// MN_UI->add("maptool_mnFile",		_windowSet.mv_file		= create_mvFile());
	// MN_UI->add("maptool_mnOption",		_windowSet.mv_option	= create_mvOption());
}

maptool_window::~maptool_window()
{
}

windowStatic * maptool_window::createBottomBar(void)
{
	// ----- window ----- //
	uiInfo winInfo;
	winInfo.backImage = MN_SRC->getSpriteTexture("resource/texture/maptool/bottomBar/bottomBar.png");

	D3DXVECTOR2 textureSize;
	gFunc::getTextureSize(&textureSize, winInfo.backImage);

	winInfo.scale = D3DXVECTOR2(
		(WINSIZEX / 5.0f) / textureSize.x,
		(WINSIZEY / 16.0f) / textureSize.y);

	winInfo.size = gFunc::Vec2Mlt(textureSize, winInfo.scale);

	winInfo.pos = D3DXVECTOR2(
		(WINSIZEX - winInfo.size.x) / 2.0f,
		WINSIZEY - winInfo.size.y );
	
	windowStatic* result = new windowStatic(winInfo);

	// ----- button ----- //
	float btnCount = 0.0f;

	result->addButton("prop",		createButtonUnderBar(result, "resource/texture/maptool/bottomBar/prop.png", btnCount++))		->getActiveSet().press = [this](void)->UI_LIST_NODE { return _windowSet.mv_prop->trans(); };
	result->addButton("character",	createButtonUnderBar(result, "resource/texture/maptool/bottomBar/character.png", btnCount++))	->getActiveSet().press = [this](void)->UI_LIST_NODE { return _windowSet.mv_character->trans(); };
	result->addButton("event",		createButtonUnderBar(result, "resource/texture/maptool/bottomBar/event.png", btnCount++))		->getActiveSet().press = [this](void)->UI_LIST_NODE { return _windowSet.mv_event->trans(); };
	result->addButton("file",		createButtonUnderBar(result, "resource/texture/maptool/bottomBar/file.png", btnCount++))		->getActiveSet().press = [this](void)->UI_LIST_NODE { return _windowSet.mv_file->trans(); };
	result->addButton("option",		createButtonUnderBar(result, "resource/texture/maptool/bottomBar/option.png", btnCount++))		->getActiveSet().press = [this](void)->UI_LIST_NODE { return _windowSet.mv_option->trans(); };

	return result;
}

windowRenderTarget * maptool_window::createMinimap(void)
{
	uiInfo winInfo;
	winInfo.size = D3DXVECTOR2(
		WINSIZEX * 0.21f,
		WINSIZEY * 0.363);
	winInfo.pos = D3DXVECTOR2(WINSIZEX - winInfo.size.x, 0);

	return new windowRenderTarget(winInfo);
}

windowStatic * maptool_window::createBottomTrans(void)
{
	auto transTexture = MN_SRC->getSpriteTexture("resource/texture/maptool/bottomBar/trans.png");
	D3DXVECTOR2 textureSize;
	gFunc::getTextureSize(&textureSize, transTexture);

	uiInfo winInfo;
	winInfo.backImage = transTexture;
	winInfo.size = textureSize;
	winInfo.pos = D3DXVECTOR2(
		_windowSet.bottomBar->getInfo().pos.x + _windowSet.bottomBar->getInfo().size.x - (winInfo.size.x * 2.0f),
		WINSIZEY - _windowSet.bottomBar->getInfo().size.y - winInfo.size.y);

	auto result = new windowStatic(winInfo);

	// ----- button ----- //
	buttonBase* btnView = result->addButton("trans", new buttonStatic(result));
	btnView->getInfo().size = winInfo.size;

	btnView->getActiveSet().press = [&](void)->UI_LIST_NODE{
		auto resultNode = _windowSet.bottomBar->trans();

		_windowSet.bottomTrans->getInfo().pos.y = _windowSet.bottomBar->isShow() ?
			WINSIZEY - _windowSet.bottomBar->getInfo().size.y - _windowSet.bottomTrans->getInfo().size.y :
			WINSIZEY - _windowSet.bottomTrans->getInfo().size.y;

		return resultNode;
	};

	return result;
}

windowMoveable * maptool_window::create_mvProp(void)
{
	auto transTexture = MN_SRC->getSpriteTexture("resource/texture/maptool/common/window.png");
	D3DXVECTOR2 textureSize;
	gFunc::getTextureSize(&textureSize, transTexture);

	uiInfo winInfo;
	winInfo.backImage = transTexture;
	winInfo.size = textureSize;
	winInfo.pos = D3DXVECTOR2(
		(WINSIZEX - winInfo.size.x) / 2.0f,
		(WINSIZEY - winInfo.size.y) / 2.0f);

	auto result = new windowMoveable(winInfo);

	return result;
}

windowMoveable * maptool_window::create_mvCharacter(void)
{
	return nullptr;
}

windowMoveable * maptool_window::create_mvEvent(void)
{
	return nullptr;
}

windowMoveable * maptool_window::create_mvFile(void)
{
	return nullptr;
}

windowMoveable * maptool_window::create_mvOption(void)
{
	return nullptr;
}

buttonStatic * maptool_window::createButtonUnderBar(windowBase * bindWindow, const std::string & texture, float offsetNumber)
{
	constexpr float btnCount = 5.0f;
	constexpr float numInterval = 0.8f;

	buttonStatic* result = new buttonStatic(bindWindow);

	D3DXVECTOR2 winTextureSize;
	gFunc::getTextureSize(&winTextureSize, bindWindow->getInfo().backImage);

	D3DXVECTOR2 btnTextureSize;

	float btnInterval = bindWindow->getInfo().size.x / btnCount * (1.0f - numInterval);
	D3DXVECTOR2 btnSize = D3DXVECTOR2(
		winTextureSize.x / btnCount * numInterval,
		winTextureSize.y * numInterval);

	D3DXVECTOR2 btnOffset = D3DXVECTOR2(
		btnInterval / 2.0f,
		(bindWindow->getInfo().size.y - btnSize.y) / 5.0f);

	result->getInfo().pos = btnOffset;
	result->getInfo().backImage = MN_SRC->getSpriteTexture(texture);
	gFunc::getTextureSize(&btnTextureSize, result->getInfo().backImage);
	result->getInfo().size = btnTextureSize;
	result->getInfo().scale = gFunc::Vec2Dev(btnSize, btnTextureSize);

	result->getInfo().pos.x += (result->getAbsSize().x + btnInterval) * offsetNumber;

	return result;
}