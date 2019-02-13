#pragma once
#include "kGlobalDefine.h"
#include "mainGame.h"
#include "AnimationDef.h"

class patternMesh;

#define 가로 3
#define 세로 3
#define MAX_NUM		가로	 * 세로

#define SURVIVOR		1
#define ZOMBIE_MALE		2
#define ZOMBIE_FEMALE   3
#define ZOMBIE_HULK     4
#define ZOMBIE_SMOKER   5
#define AIRPLANE		6

#define CURRENT_MESH	AIRPLANE

class AnimationTester : public sceneBase
{
private:
	patternMesh * _skinnedMesh = nullptr;

private:
	patternMesh * createSkinnedMesh(void);

private:
	ACInfo _cloneACInfo[MAX_NUM];
	D3DXVECTOR3 m_stPosition[MAX_NUM];
	D3DXVECTOR3 m_stRotation[MAX_NUM];
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

