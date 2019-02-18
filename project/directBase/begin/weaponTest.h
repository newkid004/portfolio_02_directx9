#pragma once
#include "kGlobalDefine.h"
#include "mainGame.h"
#include "AnimationDef.h"

class patternMesh;
class patternMeshDup;

#define 가로 1
#define 세로 1
#define MAX_NUM 가로*세로

class weaponTest :public sceneBase
{
private:
	patternMesh * _originMesh = nullptr;
	patternMeshDup* _cloneMesh[MAX_NUM];
private:
	patternMesh * createPatternMesh(void);
	
public:
	virtual void init(void) override;
	virtual void update(void) override;
	virtual void draw(void) override;
	virtual void drawUI(void) override;

public:
	void updateControl(void);

public:
	weaponTest() :sceneBase() {};
	~weaponTest() {};
};