#pragma once
#include "kGlobalDefine.h"
#include "sceneBase.h"

class particlePoint;
class particleQuad;

class sceneTest4 : public sceneBase 
{
protected :
	particlePoint* _particle = nullptr;

public:
	virtual void init(void)		override;
	virtual void update(void)	override;
	virtual void draw(void)		override;
	virtual void drawUI(void)	override;

protected :
	particlePoint* createParticle(void);

public:
	sceneTest4() : sceneBase() {};
	~sceneTest4() {};
};

