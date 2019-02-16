#pragma once
#include "kGlobalDefine.h"
#include "sceneBase.h"

class skinnedMesh;
class staticMesh;
class mapObject;
class boxObject;
class bulletManager;

class sceneCollisionTest : public sceneBase
{
public:
	struct Slab
	{
		float normal[3];
		float dNear;
		float dFar;
	};
private:

	skinnedMesh* m_pSkinnedMesh[10];
	staticMesh* m_pObjectMesh;
	boxObject* m_pBoxObject = nullptr;
	mapObject* m_pMapObject = nullptr;
	bulletManager* m_pBulletManager = nullptr;
	LPD3DXMESH m_pSphereMesh = nullptr;

	int m_nAnimationIndex = 0;

	std::vector<int> stopBulletList;
	std::vector<boundingSphere> m_vCollisionSphereList;
public:
	virtual void init(void) override;
	virtual void update(void) override;
	virtual void draw(void) override;
	
private:

	void initEvent(void);
	void updateControl(void);
	bool collisionCheck(void);
	bool collisionCheck2(void);

private:
	skinnedMesh* createZombieMesh(ECharacterType characterType = ECharacterType::NONE);
	staticMesh* createObjectMesh(void);
	LPD3DXMESH createSphereMesh(void);

public:
	sceneCollisionTest() {};
	~sceneCollisionTest();
};

