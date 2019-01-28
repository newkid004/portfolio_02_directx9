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
	_lWinOpen.run(&runner, [&](windowBase* win, UI_LIST_NODE & node)->void {
		auto beforeNode = node->prev;
		win->update();
		node = beforeNode->next;
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

void uiManager::show(std::string winName)
{
	gMng::findif(winName, _mWinCatalog, (function<void(windowBase*)>)[](windowBase* found)->void {
		found->show();
	});
}

void uiManager::show(windowBase * winBase)
{
	// 맨 앞으로 창 이동
	gMng::add(winBase, _lWinOpen);

	// manageNode 교체
	if (winBase->isClose())	winBase->getNode() = _lWinOpen.begin();
	else					_lWinOpen.erase(winBase->getNode());

	// 맨 앞의 iterator 삽입
	winBase->getNode() = _lWinOpen.begin();
}

void uiManager::close(std::string winName)
{
	gMng::findif(winName, _mWinCatalog, (function<void(windowBase*)>)[](windowBase* found)->void {
		found->close();
	});
}

void uiManager::close(windowBase * winBase)
{
	if (winBase->isClose())
		return;

	// 닫고 초기화
	UI_LIST_NODE nextNode = _lWinOpen.erase(winBase->getNode());
	winBase->getNode() = getIgnoreNode();
}

void uiManager::trans(std::string winName)
{
	gMng::findif(winName, _mWinCatalog, (function<void(windowBase*)>)[](windowBase* found)->void {
		found->trans();
	});
}

void uiManager::trans(windowBase * winBase)
{
	if (winBase->isClose())
		winBase->show();
	else
		winBase->close();
}
