#pragma once
#include "kGlobalDefine.h"
#include "mainGame.h"

class sceneTest2 : public sceneBase
{
private:
	float _stackTime = 0.0f;

public:
	virtual void init(void) override;
	virtual void update(void) override;
	virtual void draw(void) override;
	virtual void drawUI(void) override;

public :
	void updateControl(void);

public:
	sceneTest2() {};
	~sceneTest2() {};
};

