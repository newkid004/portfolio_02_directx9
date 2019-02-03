#pragma once
#include "kGlobalDefine.h"
#include "sceneBase.h"

class skinnedMesh;
class boxObject;

class sceneCollisionTest : public sceneBase
{
private:

	skinnedMesh* m_pSkinnedMesh[10];
	boxObject* m_pBoxObject = nullptr;

	int m_nAnimationIndex = 0;

public:
	virtual void init(void) override;
	virtual void update(void) override;
	virtual void draw(void) override;

private:
	void updateControl(void);

private:
	skinnedMesh* createSkinnedMesh(void);

public:
	sceneCollisionTest() {};
	~sceneCollisionTest();
};

