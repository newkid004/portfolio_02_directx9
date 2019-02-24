#pragma once
#include "kGlobalDefine.h"
#include "sceneBase.h"
#include "spriteBase.h"
#include "sceneUI.h"

class skyBox;

class sceneInGame : public sceneBase
{
private:
	spriteBase* _crosshair[2];
	sceneUI* _ui;
	skyBox* _skyBox;

public:
	virtual void init(void)		override;
	virtual void update(void)	override;
	virtual void draw(void)		override;
	virtual void drawUI(void)	override;

private :
	void initResource(void);
	void initSystem(void);
	void initField(void);

	void initEvent(void);
	void initEventTrigger(void);
	void initEventWeapon(void);

	void initUI(void);
	void initSound(void);
	
	skyBox* createSkyBox(void);
public:
	sceneInGame() {};
	~sceneInGame();
};