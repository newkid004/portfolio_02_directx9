#include "maptool_window.h"

#include "managerList.h"
#include "gFunc.h"

#include "windowStatic.h"
#include "windowRenderTarget.h"
#include "windowMoveable.h"
#include "windowCtlogMaptool.h"
#include "windowMvList.h"

#include "buttonScrollVertical.h"

#include "staticMesh.h"
#include "skinnedMesh.h"
#include "nodeMesh.h"

typedef maptool_data_catalog CATALOG;

maptool_window::maptool_window()
{
	MN_UI->add("maptool_minimap",		_windowSet.minimap		= createMinimap())->show();
	MN_UI->add("maptool_bottomBar",		_windowSet.bottomBar	= createBottomBar())->show();
	MN_UI->add("maptool_bottomTrans",	_windowSet.bottomTrans	= createBottomTrans())->show();

	vector<windowBase*> vWindow;
	vWindow.push_back(MN_UI->add("maptool_mnProp",		_windowSet.mv_prop		= create_mvProp()));
	vWindow.push_back(MN_UI->add("maptool_mnBump",		_windowSet.mv_bump		= create_mvBump()));
	vWindow.push_back(MN_UI->add("maptool_mnEvent",		_windowSet.mv_node		= create_mvNode()));
	vWindow.push_back(MN_UI->add("maptool_mnTrigger",	_windowSet.mv_trigger	= create_mvTrigger()));
	vWindow.push_back(MN_UI->add("maptool_mnFile",		_windowSet.mv_file		= create_mvFile()));

	for (auto i : vWindow)
		i->getInfo().pos += D3DXVECTOR2(gFunc::rndFloat(-100, 100), gFunc::rndFloat(-100, 100));

	_activeWindow = vWindow.size();
}

maptool_window::~maptool_window()
{
}

void maptool_window::update(void)
{
	auto focusWindow = MN_UI->getFocus();
	auto offsetedWindowSet = ((windowCtlogMaptool**)&_windowSet) + 3;
	
	for (int i = 0; i < _activeWindow; ++i)
	{
		auto lookWindow = *(offsetedWindowSet + i);

		if (focusWindow == lookWindow)
		{
			_windowSet.focusedWindow = lookWindow;
			break;
		}
	}
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

	result->addButton("prop",	createButtonUnderBar(result, "resource/texture/maptool/bottomBar/prop.png", btnCount++))	->getActiveSet().press = [this](void)->UI_LIST_NODE { return _windowSet.mv_prop->trans(); };
	result->addButton("bump",	createButtonUnderBar(result, "resource/texture/maptool/bottomBar/bump.png", btnCount++))	->getActiveSet().press = [this](void)->UI_LIST_NODE { return _windowSet.mv_bump->trans(); };
	result->addButton("event",	createButtonUnderBar(result, "resource/texture/maptool/bottomBar/event.png", btnCount++))	->getActiveSet().press = [this](void)->UI_LIST_NODE { return _windowSet.mv_node->trans(); };
	result->addButton("trigger",createButtonUnderBar(result, "resource/texture/maptool/bottomBar/trigger.png", btnCount++))	->getActiveSet().press = [this](void)->UI_LIST_NODE { return _windowSet.mv_trigger->trans(); };
	result->addButton("file",	createButtonUnderBar(result, "resource/texture/maptool/bottomBar/file.png", btnCount++))	->getActiveSet().press = [this](void)->UI_LIST_NODE { return _windowSet.mv_file->trans(); };

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

		_windowSet.bottomTrans->show();

		return resultNode;
	};

	return result;
}


windowCtlogMaptool * maptool_window::create_mvProp(void)
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

	auto result = new windowCtlogMaptool(winInfo);

	vector<CATALOG::OBJ::PROP*> content;
	createContent_prop(content);

	for (auto i : content)
		result->addItem(i);

	return result;
}

windowCtlogMaptool * maptool_window::create_mvBump(void)
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

	auto result = new windowCtlogMaptool(winInfo);

	vector<CATALOG::OBJ::BUMP*> content;
	createContent_bump(content);

	for (auto i : content)
		result->addItem(i);

	return result;
}

windowCtlogMaptool * maptool_window::create_mvNode(void)
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

	auto result = new windowCtlogMaptool(winInfo);

	vector<CATALOG::OBJ::NODE*> content;
	createContent_node(content);

	for (auto i : content)
		result->addItem(i);

	return result;
}

windowCtlogMaptool * maptool_window::create_mvTrigger(void)
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

	auto result = new windowCtlogMaptool(winInfo);

	vector<CATALOG::OBJ::NODE*> content;
	createContent_node(content);

	for (auto i : content)
		result->addItem(i);

	return result;
}

windowCtlogMaptool * maptool_window::create_mvFile(void)
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

	auto result = new windowCtlogMaptool(winInfo, D3DXVECTOR2(1, 3));

	vector<CATALOG::OBJ::FILE*> content;
	createContent_file(content);

	for (auto i : content)
		result->addItem(i);


	for (int i = 0; i < 3; ++i)
	{
		auto b = new maptool_data_catalog::OBJ::FILE();

		string filename = "map_" + to_string(i) + ".png";
		b->_standImage = MN_SRC->getSpriteTexture("resource/texture/maptool/file/" + filename);

		result->addItem(b);
	}
	result->getIndex() = 0;

	return result;
}

void maptool_window::createContent_prop(std::vector<CATALOG::OBJ::PROP*>& vContent)
{
	CATALOG::OBJ::PROP* item = nullptr;
	staticMesh::mParam param;
	param.effectFilePath = "resource/effect/example_15.fx";

	string xPath = "resource/mesh/L4D1/props/";
	string tPath = "resource/texture/maptool/catalog/prop/funitures/";

	function<void(char*)> inputContent = [&](char* fName)->void {
		param.meshFilePath = xPath + fName + ".X";
		CATALOG::create(&item, &param);
		item->_standImage = MN_SRC->getSpriteTexture(tPath + fName + ".PNG");
		vContent.push_back(item);
	};

	inputContent("cafe_barstool1");
	inputContent("chair2");
	inputContent("chandelier1");
	inputContent("kitchen_shelf");
	inputContent("lamp1");
	inputContent("picture_frame1");
	inputContent("picture_frame10");
}

void maptool_window::createContent_bump(std::vector<CATALOG::OBJ::BUMP*>& vContent)
{
	CATALOG::OBJ::BUMP* item = nullptr;
	staticMesh::mParam param;
	param.effectFilePath = "resource/effect/example_15.fx";

	string xPath = "resource/mesh/L4D1/props/";
	string tPath = "resource/texture/maptool/catalog/prop/funitures/";

	function<void(char*)> inputContent = [&](char* fName)->void {
		param.meshFilePath = xPath + fName + ".X";
		CATALOG::create(&item, &param);
		item->_standImage = MN_SRC->getSpriteTexture(tPath + fName + ".PNG");
		vContent.push_back(item);
	};

	inputContent("bathtube");
	inputContent("cupboard1");
	inputContent("desk1");
	inputContent("drawer1");
	inputContent("dresser1");
	inputContent("kitchen_cabinet");
	inputContent("kitchen_countertop");
	inputContent("piano");
	inputContent("shelf");
}

void maptool_window::createContent_node(std::vector<CATALOG::OBJ::NODE*>& vContent)
{
	CATALOG::OBJ::NODE* item = nullptr;
	nodeMesh::mParam param;

	// 00. path
	param.meshFilePath = "resource/mesh/sphere.x";
	param.effectFilePath = "resource/effect/field_node.fx";

	CATALOG::create(&item, &param);
	item->_standImage = MN_SRC->getSpriteTexture("resource/texture/maptool/catalog/node/node.png");

	vContent.push_back(item);
}

void maptool_window::createContent_trigger(std::vector<maptool_data_catalog::OBJ::TRIGGER*>& vContent)
{
	CATALOG::OBJ::TRIGGER* item = nullptr;
	staticMesh::mParam param;

	// weapon
	param.meshFilePath = "resource/mesh/Elementalist/Elementalist.x";
	param.effectFilePath = "resource/effect/example_15.fx";

	CATALOG::create(&item, &param);
	item->_standImage = MN_SRC->getSpriteTexture("resource/texture/maptool/catalog/00_test.PNG");

	vContent.push_back(item);
}

void maptool_window::createContent_file(std::vector<CATALOG::OBJ::FILE*>& vContent)
{
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
