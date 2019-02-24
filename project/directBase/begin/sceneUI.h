#pragma once
#include "kGlobalDefine.h"
#include "spriteBase.h"

class sceneUI
{
private:
	spriteBase* _crosshair[2];
	spriteBase* _number[2];
	spriteBase* _itemSlot[2];
	spriteBase* _m16[2];
	spriteBase* _shotGun[2];
	spriteBase* _healKit[2];
	spriteBase* _hpBarBg;
	spriteBase* _hpBar;
	spriteBase* _hpFont;
	spriteBase* _profile;

public:
	void update(void);
	void draw(void);

private:
	void initResource(void);
	void initUI(void);


public:
	sceneUI();
	~sceneUI();
};