#pragma once
#include "kGlobalDefine.h"
#include "sceneBase.h"

class spriteBase;

class deadScene :public sceneBase
{
private:
	spriteBase * _backGround = nullptr;

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