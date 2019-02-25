#pragma once
#include "kGlobalDefine.h"
#include "spriteBase.h"

class sceneUI
{
private:
	spriteBase* _crosshair[2];
	spriteBase* _itemSlot[2];
	spriteBase* _m16[2];
	spriteBase* _shotGun[2];
	spriteBase* _healKit[2];
	spriteBase* _hpBarBg;
	spriteBase* _hpFont;
	spriteBase* _profile;


	LPDIRECT3DTEXTURE9 _number[5];
	LPDIRECT3DTEXTURE9 _hpBar[3];

	LPDIRECT3DTEXTURE9 _timer[2];
public:
	void update(void);
	void draw(void);

private:
	void initResource(void);
	void initUI(void);
	void drawNumber(LPDIRECT3DTEXTURE9 texture, int num,D3DXVECTOR2 position,D3DXVECTOR2 scale = D3DXVECTOR2(1.0f,1.0f));

public:
	sceneUI();
	~sceneUI();
};