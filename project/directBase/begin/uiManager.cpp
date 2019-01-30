#include "uiManager.h"
#include "managerList.h"
#include "gFunc.h"
#include "gMng.h"

#include "windowBase.h"

using namespace std;

uiManager::uiManager()
{
}

uiManager::~uiManager()
{
	for (auto iter = _mWinCatalog.begin(); iter != _mWinCatalog.end(); ++iter)
	{
		windowBase * winView = iter->second;
		SAFE_DELETE(winView);
	}
}

void uiManager::update(void)
{
	bool runner = true;
	bool isIgnore = false;

	UI_LIST_NODE resultNode = nullptr;
	_lWinOpen.run(&runner, [&](windowBase* win, UI_LIST_NODE & node)->void {
		resultNode = win->update();
		
		if (resultNode == getIgnoreNode())
			runner = false;

		node = resultNode;
	});
}

void uiManager::drawUI(void)
{
	bool runner = true;
	_lWinOpen.run(&runner, [](windowBase* found, UI_LIST_NODE & curNode)->void {
		found->drawUI();
	}, UI_LIST::runDirection::REVERSE);
}

windowBase * uiManager::add(std::string winName, windowBase * winAdd)
{
	auto winResult = gMng::add(winName, winAdd, _mWinCatalog);

	if (winResult)
	{
		winResult->getNode() = getIgnoreNode();
		winResult->getInfo().nameP = (string*)&_mWinCatalog.find(winName)->first;
	}

	return winResult;
}

windowBase * uiManager::find(std::string winName)
{
	return gMng::find(winName, _mWinCatalog);
}

UI_LIST_NODE uiManager::show(std::string winName)
{
	windowBase* f = nullptr;
	gMng::findif(winName, _mWinCatalog, (function<void(windowBase*)>)[&](windowBase* found)->void {
		(f = found)->show();
	});
	return f->getNode();
}

UI_LIST_NODE uiManager::show(windowBase * winBase)
{
	// ���� managedNode ����
	if (winBase->isShow())
		_lWinOpen.erase(winBase->getNode());
	
	// �� ������ â �̵�
	gMng::add(winBase, _lWinOpen, gMng::PLACE::FRONT);

	// �� ���� iterator ����
	winBase->getNode() = _lWinOpen.begin();

	return getIgnoreNode();
}

UI_LIST_NODE uiManager::close(std::string winName)
{
	windowBase* f = nullptr;
	gMng::findif(winName, _mWinCatalog, (function<void(windowBase*)>)[&](windowBase* found)->void {
		(f = found)->close();
	});
	return f->getNode();
}

UI_LIST_NODE uiManager::close(windowBase * winBase)
{
	if (winBase->isClose())
		return winBase->getNode();

	// ��Ͽ��� ����
	auto resultNode = _lWinOpen.erase(winBase->getNode());
	winBase->getNode() = getIgnoreNode();

	return resultNode;
}

UI_LIST_NODE uiManager::trans(std::string winName)
{
	windowBase* f = nullptr;
	gMng::findif(winName, _mWinCatalog, (function<void(windowBase*)>)[&](windowBase* found)->void {
		(f = found)->trans();
	});

	return f->getNode();
}

UI_LIST_NODE uiManager::trans(windowBase * winBase)
{
	if (winBase->isClose())
		return show(winBase);
	else
		return close(winBase);
}
