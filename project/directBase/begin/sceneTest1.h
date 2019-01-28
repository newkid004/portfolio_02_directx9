#pragma once
#include "kGlobalDefine.h"
#include "mainGame.h"

class sceneTest1 : public sceneBase
{
private :
	float _stackTime = 0.0f;
	int _count = 0;
	int _save = 0;
	json _json;

public:
	virtual void init(void) override;
	virtual void update(void) override;
	virtual void draw(void) override;
	virtual void drawUI(void) override;

public:
	void updateControl(void);

public:
	sceneTest1() {};
	~sceneTest1() {};
};

