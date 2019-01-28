#pragma once
#include "kGlobalDefine.h"
#include "iUpdateble.h"

class windowBase;

typedef dbList<windowBase*> UI_LIST;
typedef UI_LIST::node*		UI_LIST_NODE;

class uiManager : public iUpdateble
{
private :
	STR_MAP(windowBase*)	_mWinCatalog;
	dbList<windowBase*>		_lWinOpen;

public :
	void update(void) override;
	void drawUI(void);

public :
	windowBase * add(std::string winName, windowBase* winAdd);
	windowBase* find(std::string winName);
	windowBase* getFocus(void) { if (_lWinOpen.empty()) return nullptr; return _lWinOpen.front(); }

	void show(std::string winName);
	void show(windowBase* winBase);
	void close(std::string winName);
	void close(windowBase* winBase);
	void trans(std::string winName);
	void trans(windowBase* winBase);

	UI_LIST_NODE getIgnoreNode(void) { return _lWinOpen.end()->next; };	// tail

public:
	uiManager();
	~uiManager();

public :
	DECLARE_SINGLETON(uiManager);
};

