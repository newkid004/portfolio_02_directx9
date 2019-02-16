#pragma once
#include "kGlobalDefine.h"
#include "mainGame.h"
#include "AnimationDef.h"

class patternMesh;
class boxObject;
class staticMesh;

class wallCollision : public sceneBase
{
private:
	patternMesh * _skinnedMesh = nullptr;

private:
	boxObject * m_pBox = nullptr;
	staticMesh* m_pStaticMesh = nullptr;

	ACInfo _cloneACInfo;
	D3DXVECTOR3 m_stPosition;
	D3DXVECTOR3 m_stRotation;
	D3DXVECTOR3 baseR;

	float _radius;
	float _speed;

public:
	virtual void init(void) override;
	virtual void update(void) override;
	virtual void draw(void) override;
	virtual void drawUI(void) override;

public:
	void updateControl(void);

private:
	bool isCollisionWall(const D3DXVECTOR3 position,const float radius, boundingBox* box);

	void boxToObjectBounce(D3DXVECTOR3& position,const float radius, boundingBox* box);

private:
	patternMesh * createSkinnedMesh(void);
	staticMesh * createStaticMesh(void);
public:
	wallCollision() :sceneBase() {};
	~wallCollision() {};
};

