#pragma once
#include "kGlobalDefine.h"
#include "singletonBase.h"

class baseObject;
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
	void drawOutLine(staticMesh* obj, D3DXVECTOR4* color = nullptr);
	void drawOutLine(skinnedMesh* obj);

	void drawOutList(std::vector<baseObject*> & objList, D3DXVECTOR4* color = nullptr);

public :
	maptool_render();
	~maptool_render();
};