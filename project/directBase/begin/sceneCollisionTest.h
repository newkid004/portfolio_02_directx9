#pragma once
#include "kGlobalDefine.h"
#include "sceneBase.h"

class skinnedMesh;
class staticMesh;
class mapObject;
class boxObject;
class bulletBase;
class skyBox;

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
	boxObject* m_pBoxObject = nullptr;
	mapObject* m_pMapObject = nullptr;
	skyBox* m_pSkybox = nullptr;

	int m_nAnimationIndex = 0;

	std::vector<int> stopBulletList;
	std::vector<int> m_vCollisionList;
public:
	virtual void init(void) override;
	virtual void update(void) override;
	virtual void draw(void) override;
	
private:

	void initEvent(void);
	void updateControl(void);
	//void collisionListSort(void);
	bool collisionNew(void);
	bool collisionCheck(void);
	bool collisionCheck2(void);

private:
	skinnedMesh* createZombieMesh(ECharacterType characterType = ECharacterType::NONE);
	skyBox* createSkybox(void);
public:
	sceneCollisionTest() {};
	~sceneCollisionTest();
};

