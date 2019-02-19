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
#include "bulletBase.h"
#include "skyBox.h"

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
	SAFE_DELETE(m_pSkybox);
}

void sceneCollisionTest::init(void)
{
	sceneBase::init();

	this->initEvent();

	for (int i = 0; i < ZOMBIE_NUM; i++)
	{
		m_pSkinnedMesh[i] = this->createZombieMesh(ECharacterType::NORMAL_ZOMBIE);

		m_pSkinnedMesh[i]->setupBoneInfo("ValveBiped_Bip01_Head1",			FLAGPOSITION * D3DXVECTOR3(       0,   915.227, 380.302), 8, 8, 8);
		m_pSkinnedMesh[i]->setupBoneInfo("ValveBiped_Bip01_Spine1",			FLAGPOSITION * D3DXVECTOR3(       0,   324.65,  -7.926), 12, 17, 12);
		m_pSkinnedMesh[i]->setupBoneInfo("ValveBiped_Bip01_L_Foot",			FLAGPOSITION * D3DXVECTOR3( 39.007,  -251.624,  30.187), 8, 8, 8);
		m_pSkinnedMesh[i]->setupBoneInfo("ValveBiped_Bip01_R_Foot",			FLAGPOSITION * D3DXVECTOR3(-39.007,  -251.624,  30.187), 8, 8, 8);
		m_pSkinnedMesh[i]->setupBoneInfo("ValveBiped_Bip01_L_Calf",			FLAGPOSITION * D3DXVECTOR3( 192.893,  -104.16,  -13.551), 9, 9, 9);
		m_pSkinnedMesh[i]->setupBoneInfo("ValveBiped_Bip01_R_Calf",			FLAGPOSITION * D3DXVECTOR3(-192.893,  -104.16,  -13.551), 9, 9, 9);
		m_pSkinnedMesh[i]->setupBoneInfo("ValveBiped_Bip01_L_Thigh",		FLAGPOSITION * D3DXVECTOR3( 63.026,  -518.266, -35.374), 9, 9, 9);
		m_pSkinnedMesh[i]->setupBoneInfo("ValveBiped_Bip01_R_Thigh",		FLAGPOSITION * D3DXVECTOR3(-63.026,  -518.266, -35.374), 9, 9, 9);
		m_pSkinnedMesh[i]->setupBoneInfo("ValveBiped_Bip01_L_Hand",			FLAGPOSITION * D3DXVECTOR3( 178.917, -200.057,  230.219), 8, 8, 8);
		m_pSkinnedMesh[i]->setupBoneInfo("ValveBiped_Bip01_R_Hand",			FLAGPOSITION * D3DXVECTOR3(-178.917, -200.057,  230.219), 8, 8, 8);
		m_pSkinnedMesh[i]->setupBoneInfo("ValveBiped_Bip01_L_Forearm",		FLAGPOSITION * D3DXVECTOR3( 563.117,   108.276, -94.635), 8, 8, 8);
		m_pSkinnedMesh[i]->setupBoneInfo("ValveBiped_Bip01_R_Forearm",		FLAGPOSITION * D3DXVECTOR3(-563.117,   108.276, -94.635), 8, 8, 8);
		m_pSkinnedMesh[i]->setupBoneInfo("ValveBiped_Bip01_L_UpperArm",		FLAGPOSITION * D3DXVECTOR3( 363.026,   18.266, -35.374), 7, 7, 7);
		m_pSkinnedMesh[i]->setupBoneInfo("ValveBiped_Bip01_R_UpperArm",		FLAGPOSITION * D3DXVECTOR3(-363.026,   18.266, -35.374), 7, 7, 7);

		m_pSkinnedMesh[i]->init();

		m_pSkinnedMesh[i]->setDebugEnable(true, EDebugDrawType::SPHERE);

		m_pSkinnedMesh[i]->setScale(D3DXVECTOR3(0.03f, 0.03f, 0.03f));
		m_pSkinnedMesh[i]->setPosition(D3DXVECTOR3(i*5.0f, 0.0f, i*10.0f));

		m_pSkinnedMesh[i]->rotateX(-90, true);
		m_pSkinnedMesh[i]->rotateZ(180, true);

	}
	m_pSkybox = this->createSkybox();

#if DEBUG_TYPE == DEBUG_TYPE_MAP
	m_pMapObject = new mapObject;
	m_pMapObject->init();
	m_pMapObject->setDebugEnable(true);
#else
	m_pBoxObject = new boxObject;
	m_pBoxObject->moveZ(4);
	m_pBoxObject->moveY(4);

	m_pBoxObject->setDebugEnable(true, EDebugDrawType::BOX);
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
	//collisionCheck();
	//collisionCheck2();
	collisionNew();
	m_pSkybox->update();
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

	MN_BULLET->draw();
	//m_pSkybox->draw();
#if DEBUG_TYPE == DEBUG_TYPE_MAP
	m_pMapObject->draw();
#else
	m_pBoxObject->draw();
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
		((skinnedMesh*)e->getDest())->moveX(2.0f * MN_TIME->getDeltaTime());
	};

	stEventCatcher2->getParam() = makeDestParam(
		ET_CHARACTER |
		EK_CHARACTER_PLAYER |
		EA_CHARACTER_RUN |
		EC_PLAYER_STATE_CHANGE_DECREASE);

	stEventCatcher2->getAfterActive() = [this](eventBase* e) -> void {
		((skinnedMesh*)e->getDest())->moveX(-2.0f * MN_TIME->getDeltaTime());
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

		MN_BULLET->addBullet(stRay.origin, stRay.direction, 1, bulletBase::EBulletType::B_RIFLE);
	}
	if (MN_KEY->keyPress(DIK_SPACE))
	{
		auto stRay = gFunc::createPickRay(MN_KEY->getMousePos(), GET_CAMERA()->getPosition());

		MN_BULLET->addBullet(stRay.origin, stRay.direction, 1, bulletBase::EBulletType::B_SHOTGUN);
	}
	if (MN_KEY->keyPress(DIK_V))
	{
		auto stRay = gFunc::createPickRay(MN_KEY->getMousePos(), GET_CAMERA()->getPosition());

		MN_BULLET->addBullet(stRay.origin, stRay.direction, 1, bulletBase::EBulletType::B_FIST);
	}
}

bool sceneCollisionTest::collisionNew(void)
{
	auto vGunBullet = MN_BULLET->getGunBulletList();
	auto vFistBullet = MN_BULLET->getFistBulletList();
	//auto sphere = m_pBoxObject->getBoundingSphere();
	//m_pBoxObject->getBoundingSphereFinal(&sphere);
	auto box = m_pBoxObject->getBoundingBoxList();
	m_pBoxObject->getBoundingBoxFinal(&box[0]);

	//for (int index = 0; index < vGunBullet.size(); index++)
	//{
	//	if (pick::isLine2Box(&vGunBullet[index]->getRay(), vGunBullet[index]->getSpeed(), box[0]))
	//	{
	//		pick::info info;
	//		pick::applyMatrix(&vGunBullet[index]->getRay(), &vGunBullet[index]->getRay(), &m_pBoxObject->getMatrixFinal());
	//		if (pick::chkPick(&info, &vGunBullet[index]->getRay(), m_pBoxObject->getMesh()))
	//		{
	//			//printf("충돌!! %d\n", rand() % 100);
	//
	//			D3DXMATRIXA16 matrix = m_pBoxObject->getMatrixFinal();
	//			D3DXMatrixInverse(&matrix, NULL, &matrix);
	//			pick::applyMatrix(&vGunBullet[index]->getRay(), &vGunBullet[index]->getRay(), &matrix);
	//			D3DXVECTOR3 intersect = vGunBullet[index]->getRay().origin + info.distance * vGunBullet[index]->getRay().direction;
	//			//m_pBulletManager->setPosition(index,
	//			//	intersect,
	//			//	false);
	//			printf("충돌!! %d, intersect point : %f, %f, %f\n", rand() % 100,
	//				intersect.x, intersect.y, intersect.z);
	//			//stopBulletList.push_back(index);
	//			MN_BULLET->eraseGunBullet(index);
	//
	//			return true;
	//		}
	//	}
	//}

	for (int i = 0; i < vFistBullet.size(); i++)
	{
		//if (pick::isLine2Box(&vFistBullet[i]->getRay(), vFistBullet[i]->getSpeed(), box[0]))
		//{
			for (int j = 0; j < ZOMBIE_NUM; j++)
			{
				auto mBoundBoxSet = m_pSkinnedMesh[j]->getBoundingBoxSetList();
				auto mBoundSphereSet = m_pSkinnedMesh[j]->getBoundingSphereSetList();
				auto mSphere = m_pSkinnedMesh[j]->getBoundingSphere();
				D3DXVECTOR3 intersect;
				D3DXVECTOR3 intersect2;
				if (pick::isLine2Sphere(&vFistBullet[i]->getRay(), &intersect,
					vFistBullet[i]->getSpeed(), mSphere))
				{
					for (auto rValue : mBoundSphereSet)
					{
						auto sphere = rValue.second.sphere;
						sphere.center = rValue.second.drawPosition;
						sphere.radius *= m_pSkinnedMesh[j]->getScale().x;

						if (pick::isLine2Sphere(&vFistBullet[i]->getRay(), &intersect2,
							vFistBullet[i]->getSpeed(), sphere))
						{
							printf("캐릭 충돌!! %d, intersect point : %f, %f, %f\n%s\n", rand() % 100, intersect2.x, intersect2.y, intersect2.z, rValue.first.c_str());
							//printf("%d 캐릭 %s 충돌!! %d\n", index, rValue.first.c_str(), rand() % 100);
							
							//printf("충돌!! %d\n", rand() % 100);
							MN_BULLET->eraseFistBullet(i);
							//return true;
						}
					}
				}

			}
		//}
	}
	return false;
}

bool sceneCollisionTest::collisionCheck(void)
{
	auto vBullet = MN_BULLET->getGunBulletList();

	for (int i = 0; i < vBullet.size(); i++)
	{
		for (int j = 0; j < ZOMBIE_NUM; j++)
		{
			auto mBoundBoxSet = m_pSkinnedMesh[j]->getBoundingBoxSetList();
			auto mBoundSphereSet = m_pSkinnedMesh[j]->getBoundingSphereSetList();
			auto mSphere = m_pSkinnedMesh[j]->getBoundingSphere();
			D3DXVECTOR3 intersect;
			D3DXVECTOR3 intersect2;
			if (pick::isLine2Sphere(&vBullet[i]->getRay(), &intersect,
				vBullet[i]->getSpeed(), mSphere))
			{
				for (auto rValue : mBoundSphereSet)
				{
					auto sphere = rValue.second.sphere;
					sphere.center = rValue.second.drawPosition;
					sphere.radius *= m_pSkinnedMesh[j]->getScale().x;

					if (pick::isLine2Sphere(&vBullet[i]->getRay(), &intersect2,
						vBullet[i]->getSpeed(), sphere))
					{
						printf("캐릭 충돌!! %d, intersect point : %f, %f, %f\n%s\n", rand() % 100, intersect2.x, intersect2.y, intersect2.z, rValue.first.c_str());
						//printf("%d 캐릭 %s 충돌!! %d\n", index, rValue.first.c_str(), rand() % 100);
						//m_pBulletManager->setPosition(i,
						//	intersect2,
						//	false);
						//stopBulletList.push_back(i);
						//m_pBulletManager->setPosition(i, intersect2, false);
						//m_pBulletManager->deleteBullet(i);
						//return true;
					}
				}
			}

		}
	}
	
	return false;
}

bool sceneCollisionTest::collisionCheck2(void)
{
	auto vBullet = MN_BULLET->getGunBulletList();
	//auto sphere = m_pBoxObject->getBoundingSphere();
	//m_pBoxObject->getBoundingSphereFinal(&sphere);
	auto box = m_pBoxObject->getBoundingBoxList();
	m_pBoxObject->getBoundingBoxFinal(&box[0]);
	
	for (int index = 0; index < vBullet.size(); index++)
	{
		//if (pick::isLine2Sphere(&vBullet[index]->getRay(), &vBullet[index]->getPosition(), vBullet[index]->getSpeed(), sphere))
		//{

		if (pick::isLine2Box(&vBullet[index]->getRay(), vBullet[index]->getSpeed(), box[0]))
		{
			pick::info info;
			pick::applyMatrix(&vBullet[index]->getRay(), &vBullet[index]->getRay(), &m_pBoxObject->getMatrixFinal());
			if (pick::chkPick(&info, &vBullet[index]->getRay(), m_pBoxObject->getMesh()))
			{
				//if (!vBullet[index]->getOnOff())
				//{
				//	continue;
				//}
				////printf("충돌!! %d\n", rand() % 100);
		
				D3DXMATRIXA16 matrix = m_pBoxObject->getMatrixFinal();
				D3DXMatrixInverse(&matrix, NULL, &matrix);
				pick::applyMatrix(&vBullet[index]->getRay(), &vBullet[index]->getRay(), &matrix);
				D3DXVECTOR3 intersect = vBullet[index]->getRay().origin + info.distance * vBullet[index]->getRay().direction;
			
				printf("충돌!! %d, intersect point : %f, %f, %f\n", rand() % 100,
					intersect.x, intersect.y, intersect.z);

				//m_pBulletManager->deleteBullet(index);
				//return true;
			}
		}
		
	//	}
	}
	
	return false;
}

skinnedMesh * sceneCollisionTest::createZombieMesh(ECharacterType characterType)
{
	skinnedMesh::mParam stParameters = {
		"resource/mesh/L4D1/male/male1.x",
		"resource/effect/skinnedMesh.fx"
	};
	return new skinnedMesh(stParameters, characterType);
}

skyBox * sceneCollisionTest::createSkybox(void)
{
	skyBox::mParam stParameters = {
		"resource/effect/skybox.fx",
		"resource/texture/skybox/sky.dds"
	};

	auto pSkybox = new skyBox(stParameters);
	pSkybox->setScale(D3DXVECTOR3(500.0f, 500.0f, 500.0f));

	return pSkybox;
}