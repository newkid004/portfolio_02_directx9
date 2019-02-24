#pragma once
#include "kGlobalDefine.h"
#include "pickRay.h"


static const D3DXMATRIXA16 g_IdentityNormal = {
		1, 0, 0 ,0,
		0, 1, 0 ,0,
		0, 0, 1 ,0,
		0, 0, 0 ,0
};
static const D3DXMATRIXA16 g_IdentityCoord = {
		1, 0, 0 ,0,
		0, 1, 0 ,0,
		0, 0, 1 ,0,
		0, 0, 0 ,1
};

class gFunc
{
public :
	// effect
	static void runEffectLoop(LPD3DXEFFECT effect, const std::string & technique, const std::function<void(int)> & callback);
	static void runRenderTarget(LPDIRECT3DTEXTURE9 renderTarget, int clearOption, LPDIRECT3DSURFACE9 depthStensil, const std::function<void(void)> & callback, bool isAlpha = false, D3DCOLOR backColor = BACK_COLOR(0));

	// UI
	static void drawText(int x, int y, std::string & text, int DT_align = DT_TOP | DT_LEFT, D3DCOLOR color = COLOR_WHITE(255));
	static void drawSprite(LPDIRECT3DTEXTURE9 texture, const D3DXVECTOR2 & pos, const D3DXVECTOR2 & size, const D3DXVECTOR2 & scale, float alpha = 1.0f, D3DXVECTOR2 * offset = NULL, RECT * clipSize = NULL, bool isClipPull = true);

	// creater
	static LPDIRECT3DVERTEXBUFFER9	createVertexBuffer(int size, DWORD options, DWORD FVF);
	static LPDIRECT3DINDEXBUFFER9	createIndexBuffer(int size, DWORD options, DWORD format);
	static LPD3DXMESH				createMesh(int faceSize, int vertexSize, DWORD options, DWORD FVF);
	static LPD3DXMESH				createMesh(int faceSize, int vertexSize, DWORD options, D3DVERTEXELEMENT9* elements);
	static pick::ray				createPickRay(const POINT & clickPos, const D3DXVECTOR3 & origin = D3DXVECTOR3(0, 0, 0));
	static LPDIRECT3DTEXTURE9		createRenderTarget(D3DXVECTOR2 size = D3DXVECTOR2(0, 0));
	static LPDIRECT3DTEXTURE9		createRenderTargetShadowMap(D3DXVECTOR2 size = D3DXVECTOR2(0, 0));
	static LPDIRECT3DSURFACE9		createDepthStensil(D3DXVECTOR2 size = D3DXVECTOR2(0, 0));

	// getter
	static void						getTextureSize(D3DXVECTOR2* out_size, LPDIRECT3DTEXTURE9 texture);
	static void						getNormal(D3DXVECTOR3* out, D3DXVECTOR3* v0, D3DXVECTOR3* v1, D3DXVECTOR3* v2);
	static float					getAngle(D3DXVECTOR2 v1, D3DXVECTOR2 v2);
	static float					getAngle(D3DXVECTOR3 v1, D3DXVECTOR3 v2);
	
	// 변환
	static D3DXVECTOR2				Vec2Mlt(const D3DXVECTOR2 & v1, const D3DXVECTOR2 & v2) { return D3DXVECTOR2(v1.x * v2.x, v1.y * v2.y); }
	static D3DXVECTOR2				Vec2Dev(const D3DXVECTOR2 & v1, const D3DXVECTOR2 & v2) { return D3DXVECTOR2(v1.x / v2.x, v1.y / v2.y); }
	static D3DXVECTOR2				Vec2Dir(const D3DXVECTOR2 & v1, const D3DXVECTOR2 & v2) { D3DXVECTOR2 result; D3DXVec2Normalize(&result, &(v2 - v1)); return result; }
	static float					Vec2Distance(const D3DXVECTOR2 & v1, const D3DXVECTOR2 & v2) { return D3DXVec2Length(&(v1 - v2)); }
	static D3DXVECTOR3				Vec3Mlt(const D3DXVECTOR3 & v1, const D3DXVECTOR3 & v2) { return D3DXVECTOR3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z); }
	static D3DXVECTOR3				Vec3Dev(const D3DXVECTOR3 & v1, const D3DXVECTOR3 & v2) { return D3DXVECTOR3(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z); }
	static D3DXVECTOR3				Vec2Dir(const D3DXVECTOR3 & v1, const D3DXVECTOR3 & v2) { D3DXVECTOR3 result; D3DXVec3Normalize(&result, &(v2 - v1)); return result; }
	static float					Vec3Distance(const D3DXVECTOR3 & v1, const D3DXVECTOR3 & v2) { return D3DXVec3Length(&(v1 - v2)); }
	static DWORD					float2DWORD(float input) { float* f = &input; return *((DWORD*)f); };
	static float					getSoundVolumeToPlayer(const D3DXVECTOR3 & position);
	
	// 보간
	template<typename T>
	inline static T					lerp(T & lerp1, T & lerp2, float percent) { return (1.0f - percent) * lerp1 + percent * lerp2; }

	// 난수
	static int						rndInt(int min, int max);
	static float					rndFloat(float min, float max);

	// 화면
	static bool						isMouseInRange(const D3DXVECTOR2 & pos, const D3DXVECTOR2 & size);

	// 충돌
	static boundingBox				createBoundingBox(LPD3DXMESH mesh);
	static boundingBox				createBoundingBox(D3DXVECTOR3 position, float width, float height, float depth);
	static boundingSphere			createBoundingSphere(LPD3DXMESH mesh);
	static boundingSphere			createBoundingSphere(D3DXVECTOR3 position, float radius);

	// 행렬
	static const D3DXMATRIXA16 *	getIdentity(bool isCoord = false) { return isCoord ? &g_IdentityCoord : &g_IdentityNormal; };

	static bool						isIntersect(const objectBox & boundA, const objectBox & boundB);
	static bool						isIntersect(const boundingBox & boundA, const boundingBox & boundB);
	static bool						isIntersect(const boundingSphere & boundA, const boundingSphere & boundB);
	static void						obj2bound(boundingBox* outBoundingBox, objectBox* inObjectBox);

private :
	gFunc() {};
	~gFunc() {};
};