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

	UI_LIST_NODE show(std::string winName);
	UI_LIST_NODE show(windowBase* winBase);
	UI_LIST_NODE close(std::string winName);
	UI_LIST_NODE close(windowBase* winBase);
	UI_LIST_NODE trans(std::string winName);
	UI_LIST_NODE trans(windowBase* winBase);

public :
	windowBase* getFocus(void) { if (_lWinOpen.empty()) return nullptr; return _lWinOpen.front(); }
	UI_LIST_NODE getIgnoreNode(void) { return _lWinOpen.end(); }

public:
	uiManager();
	~uiManager();

public :
	DECLARE_SINGLETON(uiManager);
};

