#pragma once
#include "kGlobalDefine.h"
#include "sceneBase.h"

class spriteBase;

class deadScene :public sceneBase
{
private:
	struct handInfo
	{
		LPDIRECT3DTEXTURE9 texture;
		D3DXVECTOR2 size;
		D3DXVECTOR2 position;
		D3DXVECTOR2 scale;
	};
private:
	spriteBase * _backGround = nullptr;
	spriteBase * _died = nullptr;

	handInfo _hand[2];

	int _type;
	float _downColor;

public:
	virtual void init(void) override;
	virtual void update(void) override;
	virtual void draw(void) override;
	virtual void drawUI(void) override;

private:
	void initResource(void);
	void initSetting(void);

public:
	deadScene() :sceneBase() {};
	virtual ~deadScene();
};