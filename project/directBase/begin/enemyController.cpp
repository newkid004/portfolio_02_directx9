#include "enemyController.h"

#include "managerList.h"
#include "gDigit.h"
#include "gFunc.h"

#include "inGame_digit.h"
#include "inGame_value.h"
#include "aStar_node.h"
#include "aStar_path.h"
#include "characterBase.h"
#include "AnimationDef.h"
#include "patternMesh.h"
#include "gFunc.h"

using DIGIT = inGame_digit;

#include "aStar_node.h"
#include "inGame_node.h"

#include "enemyBase.h"

enemyController::enemyController(characterBase * bindCharacter) :
	controllerBase(bindCharacter)
{
	gDigit::put(_bindCharacter->getInfoCharacter().status, DIGIT::CHAR::IDLE);
}

enemyController::~enemyController()
{
}

void enemyController::update(void)
{
	controllerBase::update();
}

void enemyController::update2bit(void)
{
	// 기본 상태
	_path->getDistance();
	// 경계 상태
		//둘러보고
		//회전하고
		//걷고

	// 달리기
	// 공격
	// 낙하
	// 넘어지는 상태(죽음)
	// 피격 상태
}

void enemyController::changeBindBit(aniDefine::ANIBIT minusBit, int plusBit)
{
	CHANGE_BIT(_bindCharacter->getNextBit(),minusBit, plusBit);
}

void enemyController::basebit(void)
{
	int random = gFunc::rndInt(0, 3);

	std::string basePath = _bindCharacter->getOriginMesh()->getBasePath();
	if (basePath.find("female") != std::string::npos)
	{
		changeBindBit(aniDefine::ANIBIT::TYPE, ATYPE_ZOMBIE_FEMALE);
	}
	else
	{
		changeBindBit(aniDefine::ANIBIT::TYPE, ATYPE_ZOMBIE_MALE);
		changeBindBit(aniDefine::ANIBIT::MAIN, MALE_IDLE);
		switch (random)
		{
		case 0:
			changeBindBit(aniDefine::ANIBIT::SUB, MALE_IDLE_NEUTRAL1);
			break;
		case 1:
			changeBindBit(aniDefine::ANIBIT::SUB, MALE_IDLE_NEUTRAL2);
			break;
		case 2:
			changeBindBit(aniDefine::ANIBIT::SUB, MALE_IDLE_NEUTRAL3);
			break;
		}

	}
}

void enemyController::updateFootPrint(void)
{
	auto & placedNode = _bindCharacter->getPlacedNode();
	auto beforeNode = placedNode;

	controllerBase::updateFootPrint();

	if (beforeNode != placedNode)
	{
		auto & nextPlacePos = static_cast<enemyBase*>(_bindCharacter)->refNextPlacePos();
		auto nodeData = inGame_node::getData(placedNode);
		nextPlacePos = nodeData->getPosition();

		float interval = nodeData->getRadius() * 0.875f;
		nextPlacePos.x += gFunc::rndFloat(-interval, interval);
		nextPlacePos.y += gFunc::rndFloat(-interval, interval);

		_bindCharacter->rotate2Pos(
			D3DXVECTOR3(
				nextPlacePos.x,
				0.0f,
				nextPlacePos.y),
			true, true);
	}
}
