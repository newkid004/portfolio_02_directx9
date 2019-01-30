#pragma once
#include "kGlobalDefine.h"
#include "pickRay.h"

class gFunc
{
public :
	// effect
	static void runEffectLoop(LPD3DXEFFECT effect, const std::string & technique, const std::function<void(int)> & callback);
	static void runRenderTarget(LPDIRECT3DTEXTURE9 renderTarget, int clearOption, LPDIRECT3DSURFACE9 depthStensil, const std::function<void(void)> & callback, D3DCOLOR backColor = BACK_COLOR(255));

	// UI
	static void drawText(int x, int y, const std::string & text, int DT_align = DT_TOP | DT_LEFT);
	static void drawSprite(LPDIRECT3DTEXTURE9 texture, const D3DXVECTOR2 & pos, const D3DXVECTOR2 & size, const D3DXVECTOR2 & scale, float alpha = 1.0f);

	// creater
	static LPDIRECT3DVERTEXBUFFER9	createVertexBuffer(int size, DWORD options, DWORD FVF);
	static LPDIRECT3DINDEXBUFFER9	createIndexBuffer(int size, DWORD options, DWORD format);
	static LPD3DXMESH				createMesh(int faceSize, int vertexSize, DWORD options, DWORD FVF);
	static LPD3DXMESH				createMesh(int faceSize, int vertexSize, DWORD options, D3DVERTEXELEMENT9* elements);
	static pick::ray				createPickRay(const POINT & clickPos);
	static LPDIRECT3DTEXTURE9		createRenderTarget(D3DXVECTOR2 size = D3DXVECTOR2(0, 0));
	static LPDIRECT3DSURFACE9		createDepthStensil(D3DXVECTOR2 size = D3DXVECTOR2(0, 0));

	// getter
	static void						getTextureSize(D3DXVECTOR2* out_size, LPDIRECT3DTEXTURE9 texture);
	
	// 변환
	static D3DXVECTOR2				Vec2Mlt(D3DXVECTOR2 & v1, D3DXVECTOR2 & v2) { return D3DXVECTOR2(v1.x * v2.x, v1.y * v2.y); }
	static D3DXVECTOR2				Vec2Dev(D3DXVECTOR2 & v1, D3DXVECTOR2 & v2) { return D3DXVECTOR2(v1.x / v2.x, v1.y / v2.y); }
	static DWORD					float2DWORD(float input) { float* f = &input; return *((DWORD*)f); };

	// 난수
	static int						rndInt(int min, int max);
	static float					rndFloat(float min, float max);

	// 화면
	static bool						isMouseInRange(const D3DXVECTOR2 & pos, const D3DXVECTOR2 & size);

	// 충돌
	static boundingBox				createBoundingBox(LPD3DXMESH mesh);
	static boundingSphere			createBoundingSphere(LPD3DXMESH mesh);

	static bool						isIntersect(const objectBox & boundA, const objectBox & boundB);
	static bool						isIntersect(const boundingBox & boundA, const boundingBox & boundB);
	static bool						isIntersect(const boundingSphere & boundA, const boundingSphere & boundB);
	static void						obj2bound(boundingBox* outBoundingBox, objectBox* inObjectBox);

private :
	gFunc() {};
	~gFunc() {};
};

