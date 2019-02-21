#pragma once
#include "kGlobalDefine.h"
#include "renderObject.h"

class skyBox : public renderObject
{
public:
	struct mParam
	{
		std::string pathEffect;
		std::string pathTextureCube;
	};

private:
	mParam _param;

	LPD3DXMESH _mesh = nullptr;
	LPD3DXEFFECT _effect = nullptr;
	LPDIRECT3DTEXTURE9 _texture = nullptr;

public:
	virtual void update(void);
	virtual void drawPre(void)	override;
	virtual void drawDo(void)	override;
	virtual void drawPost(void)	override;

private:
	LPD3DXMESH createMesh(void);

public:
	skyBox(const mParam & param);
	virtual ~skyBox();
};

