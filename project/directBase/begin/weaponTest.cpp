#include "weaponTest.h"
#include "gFunc.h"
#include "patternMesh.h"
#include "charaterArea.h"
#include "patternMeshDup.h"
#include "managerList.h"


/*
param 수정

*/
void weaponTest::init(void)
{
	sceneBase::init();

	_originMesh = this->createPatternMesh();
	_originMesh->setScale(0.01f);
	_originMesh->addChild(new charaterArea(10));


	for (int i = 0; i < MAX_NUM; ++i)
	{
		_cloneMesh[i] = new patternMeshDup(_originMesh);
		_cloneMesh[i]->getNextBit() =
			ATYPE_SURVIVOR |
			AWEAPON_PUMPSHOTGUN |
			AMAIN_RUN |
			AMIX_NONE |
			ARUN_STANDING;
		_cloneMesh[i]->setRotation(D3DXVECTOR3(0.0f, 180.0f+gFunc::rndFloat(0.0f, 360.0f), 180.0f));
	}
	_cloneMesh[0]->setRotation(D3DXVECTOR3(0.0f, 180.0f, 180.0f));

	for (int j = 0; j < 세로; ++j)
	{
		for (int i = 0; i < 가로; ++i)
		{
			_cloneMesh[j*가로 + i]->setPosition(D3DXVECTOR3(i*20.0f, 0.0f, j* 20.0f));
		}
	}
}

void weaponTest::update(void)
{
	sceneBase::update();

	for (int i = 0; i < MAX_NUM; ++i)
	{
		_cloneMesh[i]->update();
	}
	updateControl();
}

void weaponTest::draw(void)
{
	sceneBase::draw();

	for (int i = 0; i < MAX_NUM; ++i)
	{
		_cloneMesh[i]->draw();
	}
}

void weaponTest::drawUI(void)
{
	sceneBase::drawUI();
}

void weaponTest::updateControl(void)
{
	if (MN_KEY->keyPress(DIK_1))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneMesh[i]->getNextBit() =
				ATYPE_SURVIVOR |
				AWEAPON_PUMPSHOTGUN |
				AMAIN_WALK |
				AMIX_NONE |
				AWALK_SIT;
		}
	}
	else if (MN_KEY->keyPress(DIK_2))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneMesh[i]->getNextBit() =
				ATYPE_SURVIVOR |
				AWEAPON_PUMPSHOTGUN |
				AMIX_RELOAD;
		}
	}
	else if (MN_KEY->keyPress(DIK_3))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneMesh[i]->getNextBit() =
				ATYPE_SURVIVOR |
				AWEAPON_PUMPSHOTGUN |
				AMIX_SHOOT;
		}
	}
}

patternMesh * weaponTest::createPatternMesh(void)
{
	patternMesh::mParam param;
	int rndValue = 3;//gFunc::rndInt(0, 3);
	switch (rndValue)
	{
	case 0:
		param.filePath = "resource/mesh/L4D1/Biker/biker.x";
		break;
	case 1:
		param.filePath = "resource/mesh/L4D1/Manager/manager.x";
		break;
	case 2:
		param.filePath = "resource/mesh/L4D1/Namvet/namvet.x";
		break;
	case 3:
		param.filePath = "resource/mesh/L4D1/Teenangst/teenangst.x";
		break;
	}
	param.effectFilePath = "resource/effect/Survivor.fx";

	return new patternMesh(param);
}
