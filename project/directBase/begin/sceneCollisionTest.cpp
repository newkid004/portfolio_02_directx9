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

#define ZOMBIE_NUM 1

sceneCollisionTest::~sceneCollisionTest()
{
	SAFE_DELETE(m_pBoxObject);

	for (int i = 0; i < ZOMBIE_NUM; i++)
	{
		SAFE_DELETE(m_pSkinnedMesh[i]);
	}

	SAFE_DELETE(m_pMapMesh);
}

void sceneCollisionTest::init(void)
{
	sceneBase::init();

	this->initEvent();

	for (int i = 0; i < ZOMBIE_NUM; i++)
	{
		m_pSkinnedMesh[i] = this->createSkinnedMesh();

		m_pSkinnedMesh[i]->setScale(D3DXVECTOR3(0.001f, 0.001f, 0.001f));
		m_pSkinnedMesh[i]->setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		m_pSkinnedMesh[i]->rotateX(-90, true);
		m_pSkinnedMesh[i]->rotateZ(180, true);
	}

	m_pMapMesh = this->createMapMesh();
	m_pMapMesh->setScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	m_pMapMesh->moveY(10);

	m_pBoxObject = new boxObject;
	m_pBoxObject->moveZ(4);
	m_pBoxObject->moveY(4);

	m_pBoxObject->setDebugEnable(true, EDebugDrawType::SPHERE);
	
}

void sceneCollisionTest::update(void)
{
	sceneBase::update();

	this->updateControl();

	for (int i = 0; i < ZOMBIE_NUM; i++)
	{
		m_pSkinnedMesh[i]->update();
	}
	m_pMapMesh->update();

	m_pBoxObject->update();
}

void sceneCollisionTest::draw(void)
{
	sceneBase::draw();

	for (int i = 0; i < ZOMBIE_NUM; i++)
	{
		m_pSkinnedMesh[i]->draw();
	}

	//m_pMapMesh->draw();
	m_pBoxObject->draw();
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

skinnedMesh * sceneCollisionTest::createSkinnedMesh(void)
{
	skinnedMesh::mParam stParameters = {
		"resource/mesh/L4D1/male/male.x",
		"resource/effect/skinnedMesh.fx"
	};
	return new skinnedMesh(stParameters);
}

staticMesh * sceneCollisionTest::createMapMesh(void)
{
	staticMesh::mParam stParameters = {
		"resource/mesh/L4D1/map/apartment.x",
		"resource/effect/example_16.fx"
	};
	return new staticMesh(stParameters);
}
