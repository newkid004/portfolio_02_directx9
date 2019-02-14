#pragma once
#include "kGlobalDefine.h"
#include "mainGame.h"
#include "AnimationDef.h"

class patternMesh;
class boxObject;

class wallCollision : public sceneBase
{
private:
	patternMesh * _skinnedMesh = nullptr;

private:
	patternMesh * createSkinnedMesh(void);

private:
	boxObject * m_pBox = nullptr;

	ACInfo _cloneACInfo;
	D3DXVECTOR3 m_stPosition;
	D3DXVECTOR3 m_stRotation;
	D3DXVECTOR3 baseR;

	int _circle;
	float _speed;

private:
	bool isCollsionWall(void);
	
public:
	virtual void init(void) override;
	virtual void update(void) override;
	virtual void draw(void) override;
	virtual void drawUI(void) override;

public:
	void updateControl(void);

public:
	wallCollision() :sceneBase() {};
	~wallCollision() {};
};

