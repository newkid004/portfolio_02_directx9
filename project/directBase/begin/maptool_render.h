#pragma once
#include "kGlobalDefine.h"
#include "singletonBase.h"

class staticMesh;
class skinnedMesh;

class maptool_render
{
private :
	struct vertex
	{
		enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };

		D3DXVECTOR3 pos;
		D3DXVECTOR2 uv;
	};

public :
	struct renderSet
	{
		LPDIRECT3DTEXTURE9 renderTarget;
		LPDIRECT3DSURFACE9 depthStensil;
	};

private :
	std::vector<renderSet> _vRenderTarget;

	LPD3DXEFFECT _outline = nullptr;

	LPD3DXMESH _screen = nullptr;

private :
	void createRenderSet(renderSet* out);
	void createScreen(LPD3DXMESH* out);

public :
	void drawOutLine(staticMesh* obj);
	void drawOutLine(skinnedMesh* obj);

public :
	maptool_render();
	~maptool_render();
};