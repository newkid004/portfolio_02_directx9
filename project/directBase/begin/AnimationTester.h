#pragma once
#include "kGlobalDefine.h"
#include "mainGame.h"

class skinnedMesh;

class AnimationTester : public sceneBase
{
private:
	skinnedMesh * _skinnedMesh = nullptr;

private:
	skinnedMesh * createSkinnedMesh(void);

public:
	virtual void init(void) override;
	virtual void update(void) override;
	virtual void draw(void) override;
	virtual void drawUI(void) override;

public:
	void updateControl(void);

public:
	AnimationTester():sceneBase() {};
	~AnimationTester() {};
};

