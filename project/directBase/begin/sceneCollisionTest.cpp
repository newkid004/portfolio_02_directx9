#include "sceneCollisionTest.h"

#include "gFunc.h"
#include "camera.h"

#include "managerList.h"

#include "eventBase.h"
#include "eventCatcher.h"
#include "animationController.h"
#include "skinnedMesh.h"
#include "staticMesh.h"
#include "boxObject.h"
#include "mapObject.h"

#define ZOMBIE_NUM 1
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
}

void sceneCollisionTest::init(void)
{
	sceneBase::init();

	this->initEvent();

	for (int i = 0; i < ZOMBIE_NUM; i++)
	{
		m_pSkinnedMesh[i] = this->createZombieMesh();

		m_pSkinnedMesh[i]->setDebugEnable(true);
		//m_pSkinnedMesh[i]->setDebugEnable(true, EDebugDrawType::SPHERE);

		m_pSkinnedMesh[i]->setScale(D3DXVECTOR3(0.003f, 0.003f, 0.003f));
		m_pSkinnedMesh[i]->setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		m_pSkinnedMesh[i]->rotateX(-90, true);
		m_pSkinnedMesh[i]->rotateZ(180, true);

	}

	//m_pSkinnedMesh[1] = this->createObjectMesh();
	//m_pSkinnedMesh[1]->setScale(D3DXVECTOR3(0.00021f, 0.0021f, 0.0021f));
	//m_pSkinnedMesh[1]->setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	
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
}

skinnedMesh * sceneCollisionTest::createZombieMesh(void)
{
	skinnedMesh::mParam stParameters = {
		//"resource/mesh/WitchApprentice/WitchApprentice.x",
		"resource/mesh/L4D1/male/male1.x",
		"resource/effect/skinnedMesh.fx"
	};
	return new skinnedMesh(stParameters);
}

skinnedMesh * sceneCollisionTest::createObjectMesh(void)
{
	skinnedMesh::mParam stParameters = {
	"resource/mesh/L4D1/c130/c130.x",
	"resource/effect/skinnedMesh.fx"
	};
	return new skinnedMesh(stParameters);
}
