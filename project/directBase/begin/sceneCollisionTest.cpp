#include "sceneCollisionTest.h"

#include "gFunc.h"
#include "camera.h"
#include "pickRay.h"

#include "managerList.h"

#include "eventBase.h"
#include "eventCatcher.h"
#include "animationController.h"
#include "skinnedMesh.h"
#include "staticMesh.h"
#include "boxObject.h"
#include "mapObject.h"
#include "bulletManager.h"

#define ZOMBIE_NUM 1
#define FLAGPOSITION 0.16 / 1015.227

#define DEBUG_TYPE_MAP			1
#define DEBUG_TYPE_COLLISION	2
#define DEBUG_TYPE				DEBUG_TYPE_COLLISION
sceneCollisionTest::~sceneCollisionTest()
{
	SAFE_DELETE(m_pBoxObject);

	for (int i = 0; i < ZOMBIE_NUM; i++)
	{
		SAFE_DELETE(m_pSkinnedMesh[i]);
	}

	SAFE_DELETE(m_pMapObject);
	SAFE_DELETE(m_pBulletManager);

	SAFE_RELEASE(m_pSphereMesh);
}

void sceneCollisionTest::init(void)
{
	sceneBase::init();

	this->initEvent();

	for (int i = 0; i < ZOMBIE_NUM; i++)
	{
		m_pSkinnedMesh[i] = this->createZombieMesh(ECharacterType::NORMAL_ZOMBIE);

		m_pSkinnedMesh[i]->setupBoneInfo("ValveBiped_Bip01_Head1",			FLAGPOSITION * D3DXVECTOR3(       0,   915.227, 380.302), 9, 9, 9);
		m_pSkinnedMesh[i]->setupBoneInfo("ValveBiped_Bip01_Spine1",			FLAGPOSITION * D3DXVECTOR3(       0,   324.65,  -7.926), 25, 17, 12);
		m_pSkinnedMesh[i]->setupBoneInfo("ValveBiped_Bip01_L_Foot",			FLAGPOSITION * D3DXVECTOR3( 39.007,  -251.624,  30.187), 8, 8, 8);
		m_pSkinnedMesh[i]->setupBoneInfo("ValveBiped_Bip01_R_Foot",			FLAGPOSITION * D3DXVECTOR3(-39.007,  -251.624,  30.187), 8, 8, 8);
		m_pSkinnedMesh[i]->setupBoneInfo("ValveBiped_Bip01_L_Calf",			FLAGPOSITION * D3DXVECTOR3( 192.893,  -304.16,  -13.551), 9, 9, 9);
		m_pSkinnedMesh[i]->setupBoneInfo("ValveBiped_Bip01_R_Calf",			FLAGPOSITION * D3DXVECTOR3(-192.893,  -304.16,  -13.551), 9, 9, 9);
		m_pSkinnedMesh[i]->setupBoneInfo("ValveBiped_Bip01_L_Hand",			FLAGPOSITION * D3DXVECTOR3( 178.917, -200.057,  230.219), 8, 8, 8);
		m_pSkinnedMesh[i]->setupBoneInfo("ValveBiped_Bip01_R_Hand",			FLAGPOSITION * D3DXVECTOR3(-178.917, -200.057,  230.219), 8, 8, 8);
		m_pSkinnedMesh[i]->setupBoneInfo("ValveBiped_Bip01_L_Forearm",		FLAGPOSITION * D3DXVECTOR3( 563.117,   178.276, -94.635), 8, 8, 8);
		m_pSkinnedMesh[i]->setupBoneInfo("ValveBiped_Bip01_R_Forearm",		FLAGPOSITION * D3DXVECTOR3(-563.117,   178.276, -94.635), 8, 8, 8);
		m_pSkinnedMesh[i]->setupBoneInfo("ValveBiped_Bip01_L_UpperArm",		FLAGPOSITION * D3DXVECTOR3( 263.026,   788.266, -35.374), 7, 7, 7);
		m_pSkinnedMesh[i]->setupBoneInfo("ValveBiped_Bip01_R_UpperArm",		FLAGPOSITION * D3DXVECTOR3(-263.026,   788.266, -35.374), 7, 7, 7);

		m_pSkinnedMesh[i]->init();

		m_pSkinnedMesh[i]->setDebugEnable(true, EDebugDrawType::SPHERE);

		m_pSkinnedMesh[i]->setScale(D3DXVECTOR3(0.03f, 0.03f, 0.03f));
		m_pSkinnedMesh[i]->setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		m_pSkinnedMesh[i]->rotateX(-90, true);
		m_pSkinnedMesh[i]->rotateZ(180, true);

	}

	m_pBulletManager = new bulletManager;
	m_pSphereMesh = this->createSphereMesh();
	
#if DEBUG_TYPE == DEBUG_TYPE_MAP
	m_pMapObject = new mapObject;
	m_pMapObject->init();
	m_pMapObject->setDebugEnable(true);
#else
	m_pBoxObject = new boxObject;
	m_pBoxObject->moveZ(4);
	m_pBoxObject->moveY(4);

	m_pBoxObject->setDebugEnable(true);
#endif // DEBUG_TYPE == DEBUG_TYPE_MAP
	
}

void sceneCollisionTest::update(void)
{
	sceneBase::update();

	this->updateControl();

	for (int i = 0; i < ZOMBIE_NUM; i++)
	{
		m_pSkinnedMesh[i]->update();
		
		//gFunc::obj2bound(m_pSkinnedMesh[i]->getObjectBox(),)
	}
	//m_pObjectMesh->update();
	m_pBulletManager->update();

#if DEBUG_TYPE == DEBUG_TYPE_MAP
	m_pMapObject->update();
#else
	m_pBoxObject->update();
#endif // DEBUG_TYPE == DEBUG_TYPE_MAP
}

void sceneCollisionTest::draw(void)
{
	sceneBase::draw();

	for (int i = 0; i < ZOMBIE_NUM; i++)
	{
		m_pSkinnedMesh[i]->draw();
	}
	D3DXMATRIXA16 stWorld;
	D3DXMatrixIdentity(&stWorld);
	MN_DEV->SetTransform(D3DTS_WORLD, &stWorld);
	MN_DEV->SetRenderState(D3DRS_LIGHTING, false);
	m_pSphereMesh->DrawSubset(0);
	MN_DEV->SetRenderState(D3DRS_LIGHTING, true);
	//m_pObjectMesh->draw();
	m_pBulletManager->draw();

#if DEBUG_TYPE == DEBUG_TYPE_MAP
	m_pMapObject->draw();
#else
	//m_pBoxObject->draw();
#endif // DEBUG_TYPE == DEBUG_TYPE_MAP
}

void sceneCollisionTest::initEvent(void)
{
	eventCatcher* stEventCatcher1 = new eventCatcher;
	eventCatcher* stEventCatcher2 = new eventCatcher;

	stEventCatcher1->getParam() = makeDestParam(
		ET_CHARACTER |
		EK_CHARACTER_PLAYER |
		EA_CHARACTER_RUN |
		EC_PLAYER_STATE_CHANGE_INCREASE);

	stEventCatcher1->getAfterActive() = [this](eventBase* e) -> void {
		((skinnedMesh*)e->getDest())->moveY(2.0f * MN_TIME->getDeltaTime());
	};

	stEventCatcher2->getParam() = makeDestParam(
		ET_CHARACTER |
		EK_CHARACTER_PLAYER |
		EA_CHARACTER_RUN |
		EC_PLAYER_STATE_CHANGE_DECREASE);

	stEventCatcher2->getAfterActive() = [this](eventBase* e) -> void {
		((skinnedMesh*)e->getDest())->moveY(-2.0f * MN_TIME->getDeltaTime());
	};

	MN_EVENT->getEventCatcherArray(stEventCatcher1->getParam()).push_back(stEventCatcher1);
	MN_EVENT->getEventCatcherArray(stEventCatcher2->getParam()).push_back(stEventCatcher2);
}

void sceneCollisionTest::updateControl(void)
{
	for (int i = 0; i < ZOMBIE_NUM; i++)
	{
		auto oAnimationNameList = m_pSkinnedMesh[i]->getAniController()->getAnimationNameList();

		if (MN_KEY->keyDown(DIK_UP))
		{
			MN_EVENT->add(new eventBase(NULL, m_pSkinnedMesh[0],
				makeDestParam(ET_CHARACTER | EK_CHARACTER_PLAYER | EA_CHARACTER_RUN | EC_PLAYER_STATE_CHANGE_INCREASE),
				0.01));
		}
		else if (MN_KEY->keyDown(DIK_DOWN))
		{
			MN_EVENT->add(new eventBase(NULL, m_pSkinnedMesh[0],
				makeDestParam(ET_CHARACTER | EK_CHARACTER_PLAYER | EA_CHARACTER_RUN | EC_PLAYER_STATE_CHANGE_DECREASE),
				0.01));
		}

		if (MN_KEY->keyPress(DIK_LEFT))
		{
			m_nAnimationIndex--;
			m_nAnimationIndex = max(0, m_nAnimationIndex);
			m_pSkinnedMesh[i]->getAniController()->play(oAnimationNameList[m_nAnimationIndex], true);
			printf("%s\n", oAnimationNameList[m_nAnimationIndex].c_str());
		}
		else if (MN_KEY->keyPress(DIK_RIGHT))
		{
			m_nAnimationIndex++;
			m_nAnimationIndex = min(m_nAnimationIndex, oAnimationNameList.size() - 1);
			m_pSkinnedMesh[i]->getAniController()->play(oAnimationNameList[m_nAnimationIndex], true);
			printf("%s\n", oAnimationNameList[m_nAnimationIndex].c_str());
		}
	}

	if (MN_KEY->mouseDown(EMouseInput::LEFT))
	{
		auto stRay = gFunc::createPickRay(MN_KEY->getMousePos(), GET_CAMERA()->getPosition());

		m_pBulletManager->addBullet(stRay.origin, stRay.direction, 1);
	}

	auto mBoundSet = m_pSkinnedMesh[0]->getBoundingBoxSetList();
	auto mSphere = m_pSkinnedMesh[0]->getBoundingSphere();
	auto vBullet = m_pBulletManager->getBulletList();
	mSphere.center = D3DXVECTOR3(0, 0, 0);
	mSphere.radius = 3;

	for (int i = 0; i < vBullet.size(); i++)
	{
		//printf("%d vBullet To Sphere Distance : %f\n", i, gFunc::Vec3Distance(vBullet[i]->getPosition(), mSphere.center * 0.03));
		if (pick::chkPick(&vBullet[i]->getPickRay(), &mSphere))
		{
			if (pick::chkPick(&vBullet[i]->getPickRay(), vBullet[i]->getPosition(), vBullet[i]->getSpeed(), &mSphere))
			{
				printf("Ãæµ¹!!\n");
				m_pBulletManager->deleteBullet(i);
			}
		}
	}
	
	
}

skinnedMesh * sceneCollisionTest::createZombieMesh(ECharacterType characterType)
{
	skinnedMesh::mParam stParameters = {
		//"resource/mesh/WitchApprentice/WitchApprentice.x",
		"resource/mesh/L4D1/male/male1.x",
		"resource/effect/skinnedMesh.fx"
	};
	return new skinnedMesh(stParameters, characterType);
}

staticMesh * sceneCollisionTest::createObjectMesh(void)
{
	staticMesh::mParam stParameters = {
	"resource/mesh/L4D1/items/uzi.x",
	"resource/effect/example_16.fx"
	};
	return new staticMesh(stParameters);
}

LPD3DXMESH sceneCollisionTest::createSphereMesh(void)
{
	LPD3DXMESH pMesh = nullptr;

	D3DXCreateSphere(MN_DEV,
		3, 10, 10, &pMesh, NULL);

	return pMesh;
}
