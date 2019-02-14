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
	boxObject * m_pBox = nullptr;

	ACInfo _cloneACInfo;
	D3DXVECTOR3 m_stPosition;
	D3DXVECTOR3 m_stRotation;
	D3DXVECTOR3 baseR;

	int _radius;
	float _speed;

public:
	virtual void init(void) override;
	virtual void update(void) override;
	virtual void draw(void) override;
	virtual void drawUI(void) override;

public:
	void updateControl(void);

private:
	bool isCollisionWall(D3DXVECTOR3 position, float radius, boxObject* box);

private:
	patternMesh * createSkinnedMesh(void);

public:
	wallCollision() :sceneBase() {};
	~wallCollision() {};
};

