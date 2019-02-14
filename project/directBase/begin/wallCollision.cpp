#include "wallCollision.h"
#include "patternMesh.h"
#include "gFunc.h"
#include "charaterArea.h"
#include "managerList.h"
#include "boxObject.h"

void wallCollision::init(void)
{
	sceneBase::init();

	_radius = 10;
	_speed = 0.05f;

	_skinnedMesh = this->createSkinnedMesh();
	_skinnedMesh->setScale(0.01f);
	_skinnedMesh->addChild(new charaterArea(_radius));

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
	//m_pBox->setScale(5.0f);
	//m_pBox->moveZ(5.0f);

	m_pBox->setDebugEnable(true,EDebugDrawType::BOX);

	//m_pBox->getBoundingBoxFinal(&m_pBox->getBoundingBoxList()[0]);
}

void wallCollision::update(void)
{
	sceneBase::update();

	//_skinnedMesh->getChildren()[0]->getPosition() = m_stPosition;
	updateControl();

	m_pBox->update();

	if (isCollisionWall(m_stPosition, _radius, m_pBox))
	{
		printf("충돌 발생 !! %d\n", gFunc::rndInt(1,10));
	}
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
		m_stRotation.y -= 100.0f * MN_TIME->getDeltaTime();
	}
	else if (MN_KEY->keyDown(DIK_RIGHT))
	{
		m_stRotation.y += 100.0f * MN_TIME->getDeltaTime();
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

bool wallCollision::isCollisionWall(D3DXVECTOR3 position, float radius, boxObject* box)
{
	D3DXVECTOR2 boxCenter = D3DXVECTOR2((box->getBoundingBoxList()[0].max.x + box->getBoundingBoxList()[0].min.x)/2.0f,
		(box->getBoundingBoxList()[0].max.z + box->getBoundingBoxList()[0].min.z) / 2.0f);
	
	float distanceX = std::fabsf((box->getBoundingBoxList()[0].max.x - box->getBoundingBoxList()[0].min.x) / 2.0f);
	float distanceZ = std::fabsf((box->getBoundingBoxList()[0].max.z - box->getBoundingBoxList()[0].min.z) / 2.0f);

	float centerDX = (boxCenter.x - position.x);
	float centerDZ = (boxCenter.y - position.z);

	float corner = std::sqrtf((distanceX * distanceX) + (distanceZ * distanceZ));

	//이탈 범위 재조사
	if ((centerDX*centerDX + centerDZ * centerDZ) > ((corner + radius) * (corner + radius)))
	{
		printf("충돌 범위를 이탈하였습니다\n");
		return false;
	}

	//케이스 1
	if (((boxCenter.x - distanceX) < position.x) &&
		(position.x < (boxCenter.x + distanceX)))
	{
		if (std::abs(boxCenter.y - position.z) < (radius + distanceZ))
		{
			return true;
		}
	} 
	else if (((boxCenter.y - distanceZ) < position.z) &&
		(position.z < (boxCenter.y + distanceZ)))
	{
		if (std::abs(boxCenter.x - position.x) < (radius + distanceX))
		{
			return true;
		}
	}
	
	//케이스 2
	else
	{
		float cornerX = boxCenter.x + distanceX;
		float cornerZ = boxCenter.y + distanceZ;
		if (position.x > boxCenter.x)
		{
			// 오른쪽 위 모서리
			if (position.z > boxCenter.y)
			{
				if ((radius*radius) >
					((cornerX - position.x)*(cornerX - position.x) + (cornerZ - position.z)*(cornerZ - position.z)))
				{
					return true;
				}
			}
			// 오른쪽 아래 모서리
			else
			{
				cornerZ = boxCenter.y - distanceZ;
				if ((radius*radius) >
					((cornerX - position.x)*(cornerX - position.x) + (cornerZ - position.z)*(cornerZ - position.z)))
				{
					return true;
				}
			}
		}
		else
		{
			// 왼쪽 위 모서리
			if (position.z > boxCenter.y)
			{
				cornerX = boxCenter.x - distanceX;
				cornerZ = boxCenter.y + distanceZ;
				if ((radius*radius) >
					((cornerX - position.x)*(cornerX - position.x) + (cornerZ - position.z)*(cornerZ - position.z)))
				{
					return true;
				}
			}
			// 왼쪽 아래 모서리
			else
			{
				cornerX = boxCenter.x - distanceX;
				cornerZ = boxCenter.y - distanceZ;
				if ((radius*radius) >
					((cornerX - position.x)*(cornerX - position.x) + (cornerZ - position.z)*(cornerZ - position.z)))
				{
					return true;
				}
			}
		}
	}
	return false;
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
