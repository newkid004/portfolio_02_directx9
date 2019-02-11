#pragma once
#include "kGlobalDefine.h"
#include "mainGame.h"
#include "AnimationDef.h"

class patternMesh;

#define 가로 5
#define 세로 5
#define MAX_ZOMBIE		가로	 * 세로

class AnimationTester : public sceneBase
{
private:
	patternMesh * _skinnedMesh = nullptr;

private:
	patternMesh * createSkinnedMesh(void);

private:
	ACInfo _cloneACInfo[MAX_ZOMBIE];
	D3DXVECTOR3 m_stPosition[MAX_ZOMBIE];
	D3DXVECTOR3 m_stRotation[MAX_ZOMBIE];
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

