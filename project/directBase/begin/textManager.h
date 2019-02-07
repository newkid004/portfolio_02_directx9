#pragma once
#include "kGlobalDefine.h"
#include "singletonBase.h"

class textManager : public singletonBase<textManager>
{
private :
	std::unordered_map<std::string, LPD3DXMESH> _mText;

	LPDIRECT3DTEXTURE9 _renderTarget = nullptr;
	LPDIRECT3DSURFACE9 _depthStensil = nullptr;

public :
	void draw(std::string & text, D3DXVECTOR2 & pos);

private :
	LPD3DXMESH add(std::string & text);

public:
	textManager();
	~textManager();
};

#define MN_TEXT textManager::getInstance()