#pragma once
#include "kGlobalDefine.h"
#include "sceneBase.h"

class spriteBase;

class menuScene : public sceneBase
{
private:

	struct bloodSpriteInfo
	{
		int type;
		LPDIRECT3DTEXTURE9 texture;
		D3DXVECTOR2 pos;
		D3DXVECTOR2 size;
		D3DXVECTOR2 scale;
		float alpha;
		float updateTime;
	};

	struct button
	{
		RECT rc;
		LPDIRECT3DTEXTURE9 texture[2];
	};

private:
	spriteBase* backGround = nullptr;
	bloodSpriteInfo blood[5];

	float _colorA = 255;
	bool _isIncrease = false;

	button mainGameButton;
	button mapToolButton;
	button exitButton;
	

public:
	virtual void init(void) override;
	virtual void update(void) override;
	virtual void draw(void) override;
	virtual void drawUI(void) override;

private:
	void initInfomation(void);
	void updateBlood(void);
	bool intersectMouseToRect(RECT rc);

public:
	menuScene() :sceneBase() {};
	virtual~menuScene();
};