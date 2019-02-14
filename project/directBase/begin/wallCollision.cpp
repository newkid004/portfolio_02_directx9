#include "wallCollision.h"
#include "patternMesh.h"
#include "gFunc.h"
#include "charaterArea.h"
#include "managerList.h"
#include "boxObject.h"

void wallCollision::init(void)
{
	sceneBase::init();

	_circle = 10;
	_speed = 0.01f;

	_skinnedMesh = this->createSkinnedMesh();
	_skinnedMesh->setScale(0.01f);
	_skinnedMesh->addChild(new charaterArea(_circle));

	ZeroMemory(&_cloneACInfo, sizeof(_cloneACInfo));
	_cloneACInfo.NextMotionBit = ATYPE_SURVIVOR |
		AWEAPON_PUMPSHOTGUN |
		AMAIN_RUN |
		AMIX_NONE |
		ARUN_STANDING;


	ZeroMemory(&m_stPosition, sizeof(m_stPosition));
	ZeroMemory(&m_stRotation, sizeof(m_stRotation));
	baseR = D3DXVECTOR3(0.0f, 180.0f, 180.0f);

	m_pBox = new boxObject();
	m_pBox->moveZ(10);
	m_pBox->moveY(10);

	m_pBox->setDebugEnable(true,EDebugDrawType::BOX);
}

void wallCollision::update(void)
{
	sceneBase::update();

	//_skinnedMesh->getChildren()[0]->getPosition() = m_stPosition;
	updateControl();

	m_pBox->update();
}

void wallCollision::draw(void)
{
	sceneBase::draw();
	_skinnedMesh->setPosition(m_stPosition);
	_skinnedMesh->setRotation(baseR + m_stRotation);
	_skinnedMesh->update();
	_skinnedMesh->drawpreMesh(_cloneACInfo);
	_skinnedMesh->draw();

	m_pBox->draw();
}

void wallCollision::drawUI(void)
{
	sceneBase::drawUI();
}

void wallCollision::updateControl(void)
{
	if (MN_KEY->keyDown(DIK_UP))
	{
		m_stPosition += _skinnedMesh->getDirectForward()*_speed;
	}
	else if (MN_KEY->keyDown(DIK_DOWN))
	{
		m_stPosition -= _skinnedMesh->getDirectForward()*_speed;
	}
	if (MN_KEY->keyDown(DIK_LEFT))
	{
		m_stRotation.y -= 50.0f * MN_TIME->getDeltaTime();
	}
	else if (MN_KEY->keyDown(DIK_RIGHT))
	{
		m_stRotation.y += 50.0f * MN_TIME->getDeltaTime();
	}

	if (MN_KEY->keyDown(DIK_SPACE))
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				printf("%f ", _skinnedMesh->getMatrixFinal()(i, j));
			}
			printf("\n");
		}
		printf("\n");
	}
}

patternMesh * wallCollision::createSkinnedMesh(void)
{
	patternMesh::mParam param;

	int rndValue =  gFunc::rndInt(0, 3);
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

bool wallCollision::isCollsionWall(void)
{
	return false;
}
