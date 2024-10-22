#pragma once
#include "kGlobalDefine.h"

class buttonBase;

struct uiInfo
{
	LPDIRECT3DTEXTURE9 backImage = nullptr;
	std::string * nameP = nullptr;
	D3DXVECTOR2 pos = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR2 size = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR2 scale = D3DXVECTOR2(1.0f, 1.0f);
	float alpha = 1.0f;
};

class windowBase
{
public :
	typedef dbList<windowBase*> UI_LIST;
	typedef UI_LIST::node*		UI_LIST_NODE;

protected :
	uiInfo _info;
	UI_LIST_NODE _managedNode = nullptr;
	std::unordered_map<std::string, buttonBase*> _mButton;

public :
	UI_LIST_NODE update(void);
	virtual void drawUI(void);

protected :
	virtual UI_LIST_NODE updateAlways(void);
	virtual UI_LIST_NODE updateWindow(void) = 0;
	virtual UI_LIST_NODE updateFocus(void);

public:	// ----- window ----- //
	virtual UI_LIST_NODE show(void);
	virtual UI_LIST_NODE close(void);
	virtual UI_LIST_NODE trans(void);
	virtual bool isShow(void);
	virtual bool isClose(void);

public:	// ----- button ----- //
	buttonBase* addButton(const std::string & name, buttonBase* addition);
	buttonBase* findButton(const std::string & name);

public :	// ----- get / set ----- //
	uiInfo & getInfo(void) { return _info; }
	UI_LIST_NODE & getNode(void) { return _managedNode; }
	D3DXVECTOR2 getAbsSize(void);
	D3DXVECTOR2 getSizePos(void);

public:
	windowBase(const uiInfo & info);
	virtual ~windowBase();
};

