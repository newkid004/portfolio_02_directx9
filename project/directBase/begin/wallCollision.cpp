#include "wallCollision.h"
#include "patternMesh.h"
#include "gFunc.h"
#include "charaterArea.h"
#include "managerList.h"
#include "boxObject.h"
#include "staticMesh.h"

void wallCollision::init(void)
{
	sceneBase::init();

	_radius = 10.0f;
	_speed = 0.1f;

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
	m_pBox->setScale(5.0f);
	m_pBox->setDebugEnable(true,EDebugDrawType::BOX);
	m_pBox->getBoundingBoxFinal(&m_pBox->getBoundingBoxList()[0]);

	m_pStaticMesh = this->createStaticMesh();
	m_pStaticMesh->setScale(0.01f);
	m_pStaticMesh->setBoundingBox(gFunc::createBoundingBox(m_pStaticMesh->getMeshSet()->mesh));
	m_pStaticMesh->setDebugEnable(true, EDebugDrawType::BOX);
	m_pStaticMesh->getBoundingBoxFinal(&m_pStaticMesh->getBoundingBoxList()[0]);
}

void wallCollision::update(void)
{
	sceneBase::update();

	updateControl();

	m_pBox->update();
	m_pStaticMesh->update();

	if (isCollisionWall(m_stPosition, _radius, &m_pBox->getBoundingBoxList()[0]))
	{
		boxToObjectBounce(m_stPosition, _radius, &m_pBox->getBoundingBoxList()[0]);
	}

	if (isCollisionWall(m_stPosition, _radius, &m_pStaticMesh->getBoundingBoxList()[0]))
	{
		boxToObjectBounce(m_stPosition, _radius, &m_pStaticMesh->getBoundingBoxList()[0]);
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
	m_pStaticMesh->draw();
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

bool wallCollision::isCollisionWall(const D3DXVECTOR3 position,const float radius, boundingBox* box)
{
	D3DXVECTOR2 boxCenter = D3DXVECTOR2((box->max.x + box->min.x)/2.0f,
		(box->max.z + box->min.z) / 2.0f);
	
	float distanceX = std::fabsf((box->max.x - box->min.x) / 2.0f);
	float distanceZ = std::fabsf((box->max.z - box->min.z) / 2.0f);

	float centerGap = gFunc::Vec2Distance(D3DXVECTOR2(boxCenter.x, boxCenter.y), D3DXVECTOR2(position.x , position.z));

	float cornerD = gFunc::Vec2Distance(boxCenter,D3DXVECTOR2(boxCenter.x + distanceX, boxCenter.y + distanceZ));

	//이탈 범위 재조사
	if ((centerGap * centerGap) > (FLT_EPSILON + (cornerD + radius) * (cornerD + radius)))
	{
		return false;
	}

	//케이스 1
	if (((boxCenter.x - distanceX) <= position.x) &&
		(position.x <= (boxCenter.x + distanceX)))
	{
		if (std::abs(boxCenter.y - position.z) < (radius + distanceZ))
		{
			return true;
		}
	} 
	else if (((boxCenter.y - distanceZ) <= position.z) &&
		(position.z <= (boxCenter.y + distanceZ)))
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
			if (position.z >= boxCenter.y)
			{
				if ((radius*radius) >=
					((cornerX - position.x)*(cornerX - position.x) + (cornerZ - position.z)*(cornerZ - position.z)))
				{
					return true;
				}
			}
			// 오른쪽 아래 모서리
			else
			{
				cornerZ = boxCenter.y - distanceZ;
				if ((radius*radius) >=
					((cornerX - position.x)*(cornerX - position.x) + (cornerZ - position.z)*(cornerZ - position.z)))
				{
					return true;
				}
			}
		}
		else
		{
			// 왼쪽 위 모서리
			if (position.z >= boxCenter.y)
			{
				cornerX = boxCenter.x - distanceX;
				cornerZ = boxCenter.y + distanceZ;
				if ((radius*radius) >=
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
				if ((radius*radius) >=
					((cornerX - position.x)*(cornerX - position.x) + (cornerZ - position.z)*(cornerZ - position.z)))
				{
					return true;
				}
			}
		}
	}
	return false;
}

void wallCollision::boxToObjectBounce(D3DXVECTOR3 & position,const float radius, boundingBox * box)
{
	D3DXVECTOR2 boxCenter = D3DXVECTOR2((box->max.x + box->min.x) / 2.0f,
		(box->max.z + box->min.z) / 2.0f);

	float boxWidth = std::fabsf(box->max.x - boxCenter.x);
	float boxHeight = std::fabsf(box->max.z - boxCenter.y);

	//상하
	if (boxCenter.x - boxWidth <= position.x &&
		position.x <= boxCenter.x + boxWidth)
	{
		//상
		if (boxCenter.y < position.z)
		{
			position.z = boxCenter.y + boxHeight + radius;
		}
		//하
		else 
		{
			position.z = boxCenter.y - boxHeight - radius;
		}
	}
	//좌우
	else if (boxCenter.y - boxHeight <= position.z &&
		position.z <= boxCenter.y + boxHeight)
	{
		//좌
		if (boxCenter.x > position.x)
		{
			position.x = boxCenter.x - boxWidth - radius;
		}
		//우
		else
		{
			position.x = boxCenter.x + boxWidth + radius;
		}
	}
	//꼭지점
	else
	{
		float cornerX = boxCenter.x + boxWidth;
		float cornerZ = boxCenter.y + boxHeight;
		if (position.x > boxCenter.x)
		{
			// 오른쪽 위 모서리
			if (position.z >= boxCenter.y);
			// 오른쪽 아래 모서리
			else
			{
				cornerZ = boxCenter.y - boxHeight; 
			}
		}
		else
		{
			cornerX = boxCenter.x - boxWidth;
			// 왼쪽 위 모서리
			if (position.z >= boxCenter.y)
			{
				cornerZ = boxCenter.y + boxHeight;
			}
			// 왼쪽 아래 모서리
			else
			{
				cornerZ = boxCenter.y - boxHeight;
			}
		}
		D3DXVECTOR2 stDirection = D3DXVECTOR2((position.x - cornerX), (position.z - cornerZ));
		D3DXVec2Normalize(&stDirection, &stDirection);
		position.x = cornerX + stDirection.x * radius;
		position.z = cornerZ + stDirection.y * radius;
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

staticMesh * wallCollision::createStaticMesh(void)
{
	staticMesh::mParam stParam =
	{
		"resource/mesh/L4D1/props/bathtube.x",
		"resource/effect/example_15.fx"
	};

	return new staticMesh(stParam);
}
