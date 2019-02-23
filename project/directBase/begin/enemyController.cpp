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
#include "enemyBase.h"
#include "player.h"

#include "inGame_node.h"

#include "enemyBase.h"

#include "gameSystem.h"
#include "characterBase.h"
#include "patternMesh.h"

using DIGIT = inGame_digit;
using VALUE = inGame_value::enemy;
using ANIBIT = aniDefine::ANIBIT;


enemyController::enemyController(characterBase * bindCharacter) :
	controllerBase(bindCharacter)
{
	_bindCharacter->getInfoCharacter().status = DIGIT::CHAR::IDLE;
	_infoTimeEnemy.timeNextActive = MN_TIME->getRunningTime();
	_delay = VALUE::delayHangOut;

	
	_isFemale = (_bindCharacter->getOriginMesh()->getOriginType() 
		== patternMesh::type::feMale_zombie ) ? true : false;
	baseBit();
}

enemyController::~enemyController()
{
}

void enemyController::update(void)
{
	if (_infoTimeEnemy.timeNextActive <= MN_TIME->getRunningTime())
	{
		controllerBase::update();
		_infoTimeEnemy.timeNextActive = MN_TIME->getRunningTime() + _delay;
	}
	update2bit();
}

void enemyController::update2bit(void)
{
	// 넘어지는 상태(죽음)
	if (gDigit::chk(_bindCharacter->getInfoCharacter().status, DIGIT::CHAR::DEAD))
	{
		if (_isFemale)
		{
			changeBindBit(aniDefine::ANIBIT::MAIN, FEMALE_LYING);
			//뒤로
			changeBindBit(aniDefine::ANIBIT::SUB, FEMALE_LYING_BACKWARD);
			//왼쪽
			//changeBindBit(aniDefine::ANIBIT::SUB, FEMALE_LYING_LEFTWARD);
			//오른쪽
			//changeBindBit(aniDefine::ANIBIT::SUB, FEMALE_LYING_RIGHTWARD);
			//앞으로
			//changeBindBit(aniDefine::ANIBIT::SUB, FEMALE_LYING_FRONTWARD);
		}
		else
		{
			//뒤로
			changeBindBit(aniDefine::ANIBIT::MAIN, MALE_LYING);
			changeBindBit(aniDefine::ANIBIT::SUB, MALE_LYING_BACKWARD);

			//왼쪽으로
			//changeBindBit(aniDefine::ANIBIT::SUB, MALE_LYING_LEFTWARD);
			//앞으로
			//changeBindBit(aniDefine::ANIBIT::SUB, MALE_LYING_FRONTWARD);
		}
		_delay = VALUE::delayHangOut;
		// 3초뒤 사라짐
		_infoTimeEnemy.timeNextDisappear = MN_TIME->getRunningTime() + 3.0f;
		return;
	}
	
	// 피격 상태(총)
	else if (gDigit::chk(_bindCharacter->getInfoCharacter().status, DIGIT::CHAR::BESHOT))
	{
		updateBeShot();
		return;
	}
	
	// 피격 상태(밀쳐진)
	else if (gDigit::chk(_bindCharacter->getInfoCharacter().status, DIGIT::CHAR::SHOVED))
	{
		//밀쳐진 애니메이션이 끝났을 경우
		if ((_bindCharacter->getAControllInfo().CurrentMotionBit& GET_ANIBITMASK(aniDefine::ANIBIT::MAIN))
			== MALE_SHOVED)
		{
			if (_bindCharacter->getAControllInfo().persent >= 0.8f)
			{
				gDigit::pick(_bindCharacter->getInfoCharacter().status, DIGIT::CHAR::SHOVED);
			}
		}
		else
		{
			changeBindBit(aniDefine::ANIBIT::MAIN, FEMALE_SHOVED);

			/*
			이것으로 움직이는  지를 체크 가능한가?
			*/
			D3DXVECTOR3 playerToEnemyDirection = _bindCharacter->getPosition() - SGT_GAME->getSet().player->getPosition();
			float angle = D3DXVec2Dot(&D3DXVECTOR2(_bindCharacter->getDirectForward().x,_bindCharacter->getDirectForward().z),
				&D3DXVECTOR2(playerToEnemyDirection.x, playerToEnemyDirection.z));
			if (gDigit::chk(_bindCharacter->getInfoMove().status, DIGIT::MOVE::MOVEING))
			{
				if (angle < 0)
				{
					//달리는 도중 뒤에서
					changeBindBit(aniDefine::ANIBIT::SUB, FEMALE_SHOVED_BACK_RUN);
				}
				else
				{
					//달리는 도중 앞에서
					changeBindBit(aniDefine::ANIBIT::SUB, FEMALE_SHOVED_FRONT_RUN);
				}
			}
			else
			{
				if (angle < 0)
				{
					//뒤에서
					changeBindBit(aniDefine::ANIBIT::SUB, FEMALE_SHOVED_BACKWARD);
				}
				else
				{
					//앞에서
					changeBindBit(aniDefine::ANIBIT::SUB, FEMALE_SHOVED_FRONTWARD);
				}

			}
		}
		_delay = VALUE::findSomthingDistance;
		return;
	}

	// 공격
	else if (gDigit::chk(_bindCharacter->getInfoCharacter().status, DIGIT::CHAR::ADJACENT))
		//공격 딜레이추가?
	{
		if ((_bindCharacter->getAControllInfo().CurrentMotionBit & GET_ANIBITMASK(aniDefine::ANIBIT::MAIN))
			== MALE_ATTACK)
		{
			if (_bindCharacter->getAControllInfo().persent >= 0.8f)
			{
				gDigit::pick(_bindCharacter->getInfoCharacter().status, DIGIT::CHAR::ATTACK);
			}
		}
		else
		{
			changeBindBit(aniDefine::ANIBIT::MAIN, MALE_ATTACK);
			changeBindBit(aniDefine::ANIBIT::SUB, MALE_ATTACK_NONE);
			gDigit::put(_bindCharacter->getInfoCharacter().status, DIGIT::CHAR::ATTACK);
		}
		_delay = VALUE::delayMove;
		return;
	}


	// 기본 상태
	else if (_path->getDistance() > VALUE::aletyDistance)
	{
		if (_isFemale)
		{
			changeBindBit(aniDefine::ANIBIT::MAIN, FEMALE_IDLE);
			changeBindBit(aniDefine::ANIBIT::SUB, FEMALE_IDLE_NEUTRAL1);
		}
		else
		{
			changeBindBit(aniDefine::ANIBIT::MAIN, MALE_IDLE);
			changeBindBit(aniDefine::ANIBIT::SUB, MALE_IDLE_NEUTRAL1);
		}
		_delay = VALUE::delayHangOut;
		_bindCharacter->getInfoCharacter().status =  DIGIT::CHAR::IDLE;
	}
	// 경계 상태
	else if (_path->getDistance() <= VALUE::aletyDistance &&
		_path->getDistance() >= VALUE::findSomthingDistance)
	{
		//D3DXVECTOR3 direction =  ((enemyBase*)_bindCharacter)->refNextPlacePos() - _bindCharacter->getPosition();
		//float cosValue = D3DXVec2Dot(&D3DXVECTOR2(_bindCharacter->getDirectForward().x, _bindCharacter->getDirectForward().z),
		//	&D3DXVECTOR2(direction.x, direction.z));
		//if (cosValue <= FLT_EPSILON)
		{
			// 둘러보고
			if (_isFemale)
			{
				changeBindBit(aniDefine::ANIBIT::MAIN, FEMALE_IDLE);
				changeBindBit(aniDefine::ANIBIT::SUB, FEMALE_IDLE_ALERT);
			}
			else
			{
				changeBindBit(aniDefine::ANIBIT::MAIN, MALE_IDLE);
				changeBindBit(aniDefine::ANIBIT::SUB, MALE_IDLE_ALERT);
			}
			_bindCharacter->getInfoCharacter().status = DIGIT::CHAR::ALERT;
		}
		//}
		//// 회전하고
		//else
		//{
		//	//다음노드를 향해서 왼쪽으로 회전
		//	if (cosValue > 0.0f)
		//	{
		//		changeBindBit(aniDefine::ANIBIT::MAIN, MALE_TURN);
		//		changeBindBit(aniDefine::ANIBIT::SUB, MALE_TURN_LEFT);
		//		_bindCharacter->getInfoCharacter().status = DIGIT::CHAR::LROTATE;
		//	}
		//	//다음 노드를 향해서 오른쪽으로 회전
		//	else
		//	{
		//		changeBindBit(aniDefine::ANIBIT::MAIN, MALE_TURN);
		//		changeBindBit(aniDefine::ANIBIT::SUB, MALE_TURN_RIGHT);
		//		_bindCharacter->getInfoCharacter().status = DIGIT::CHAR::RROTATE;
		//	}
		//}
		_delay = VALUE::delayAlert;
	}
	// 달리기
	else if (_path->getDistance() < VALUE::findSomthingDistance)
	{
		changeBindBit(aniDefine::ANIBIT::MAIN, MALE_RUN);
		changeBindBit(aniDefine::ANIBIT::SUB, MALE_RUN_NONE);
		_delay = VALUE::delayMove;
		_bindCharacter->getInfoCharacter().status = DIGIT::CHAR::APPROACH;
	}

	// 낙하
	  /*
	  nothing
	  */
}

void enemyController::baseBit(void)
{
	int random = gFunc::rndInt(0, 3);

	if (_isFemale)
	{
		changeBindBit(aniDefine::ANIBIT::TYPE, ATYPE_ZOMBIE_FEMALE);
		changeBindBit(aniDefine::ANIBIT::MAIN, FEMALE_IDLE);
		switch (random)
		{
		case 0:
			changeBindBit(aniDefine::ANIBIT::SUB, FEMALE_IDLE_NEUTRAL1);
			break;
		case 1:
			changeBindBit(aniDefine::ANIBIT::SUB, FEMALE_IDLE_NEUTRAL2);
			break;
		case 2:
			changeBindBit(aniDefine::ANIBIT::SUB, FEMALE_IDLE_NEUTRAL3);
			break;
		}
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

void enemyController::changeBindBit(aniDefine::ANIBIT minusBit, int plusBit)
{
	CHANGE_BIT(_bindCharacter->getNextBit(), minusBit, plusBit);
}

float enemyController::getDistance2player(void)
{
	auto viewPlayer = SGT_GAME->getSet().player;

	auto placedNode = _bindCharacter->getPlacedNode();
	auto playerNode = viewPlayer->getPlacedNode();

	auto & path = _path->unpack();

	if (placedNode == playerNode || path.size() < 2)
		return gFunc::Vec3Distance(_bindCharacter->getPosition(), viewPlayer->getPosition());

	else
	{
		auto & nextPathOwn = path.front()->getMember().nextRunner;
		auto & prevPathPlayer = path.back()->getMember().prevRunner;
		float intervalOwn = aStar_node::getInterval(placedNode, nextPathOwn->getMember().placedNode);
		float intervalPlayer = aStar_node::getInterval(viewPlayer->getPlacedNode(), prevPathPlayer->getMember().prevNode);

		aStar_node::info *infoOwn, *infoPlayer;
		nextPathOwn->getMember().placedNode->getInfo(infoOwn);
		prevPathPlayer->getMember().placedNode->getInfo(infoPlayer);

		intervalOwn -= gFunc::Vec3Distance(infoOwn->pos, _bindCharacter->getPosition());
		intervalPlayer -= gFunc::Vec3Distance(infoPlayer->pos, viewPlayer->getPosition());

		return _path->getDistance() + intervalOwn + intervalPlayer;
	}
}

void enemyController::updateBeShot(void)
{
	//피격 모션이 끝났을 경우
	if ((_bindCharacter->getAControllInfo().CurrentMotionBit & GET_ANIBITMASK(aniDefine::ANIBIT::MAIN))
		== MALE_DEAD)
	{
		if (_bindCharacter->getAControllInfo().persent >= 0.8f)
		{
			gDigit::pick(_bindCharacter->getInfoCharacter().status, DIGIT::CHAR::BESHOT);
			changeBindBit(ANIBIT::WEAPON, AWEAPON_NONE);
			_bindCharacter->getStatusBeShot() = 0;
		}
	}
	else
	{
		if (!gDigit::chk(_bindCharacter->getInfoCharacter().status, DIGIT::CHAR::APPROACH))
		{
			if (gDigit::chk(_bindCharacter->getStatusBeShot(), DIGIT::PART::BYSHOTGUN))
			{
				//샷건, 피격, 머리/앞
				if (gDigit::chk(_bindCharacter->getStatusBeShot(), DIGIT::PART::HEAD))
				{
					if (_isFemale)
					{

					}
					else
					{
						changeBindBit(ANIBIT::WEAPON, AWEAPON_PUMPSHOTGUN);
						changeBindBit(ANIBIT::MAIN, MALE_DEAD);
						changeBindBit(ANIBIT::SUB, MALE_DEAD_HEAD_FRONT);
					}
					gDigit::pick(_bindCharacter->getStatusBeShot(), DIGIT::PART::HEAD);
				}
				//샷건, 피격, 왼쪽/앞
				else if (gDigit::chk(_bindCharacter->getStatusBeShot(), DIGIT::PART::LEFT))
				{
					if (_isFemale)
					{

					}
					else
					{
						changeBindBit(ANIBIT::WEAPON, AWEAPON_PUMPSHOTGUN);
						changeBindBit(ANIBIT::MAIN, MALE_DEAD);
						changeBindBit(ANIBIT::SUB, MALE_DEAD_LEFT_FRONT);
					}
					gDigit::pick(_bindCharacter->getStatusBeShot(), DIGIT::PART::LEFT);
				}
				//샷건, 피격, 오른쪽/앞
				else if (gDigit::chk(_bindCharacter->getStatusBeShot(), DIGIT::PART::RIGHT))
				{
					if (_isFemale)
					{

					}
					else
					{
						changeBindBit(ANIBIT::WEAPON, AWEAPON_PUMPSHOTGUN);
						changeBindBit(ANIBIT::MAIN, MALE_DEAD);
						changeBindBit(ANIBIT::SUB, MALE_DEAD_RIGHT_FRONT);
					}
					gDigit::pick(_bindCharacter->getStatusBeShot(), DIGIT::PART::RIGHT);
				}
				//샷건, 피격, 중간/앞
				else if (gDigit::chk(_bindCharacter->getStatusBeShot(), DIGIT::PART::MIDDLE))
				{
					if (_isFemale)
					{

					}
					else
					{
						changeBindBit(ANIBIT::WEAPON, AWEAPON_PUMPSHOTGUN);
						changeBindBit(ANIBIT::MAIN, MALE_DEAD);
						changeBindBit(ANIBIT::SUB, MALE_DEAD_MIDDLE_FRONT);
					}
					gDigit::pick(_bindCharacter->getStatusBeShot(), DIGIT::PART::MIDDLE);
				}


				//샷건, 피격, 왼쪽/뒤
				//샷건, 피격, 오른쪽/뒤
				//샷건, 피격, 중간/뒤
				//샷건, 피격, 머리/뒤
			}
			else
			{
				//라이플, 피격, 머리/앞
				if (gDigit::chk(_bindCharacter->getStatusBeShot(), DIGIT::PART::HEAD))
				{
					if (_isFemale)
					{

					}
					else
					{
						changeBindBit(ANIBIT::WEAPON, AWEAPON_RIFLE);
						changeBindBit(ANIBIT::MAIN, MALE_DEAD);
						changeBindBit(ANIBIT::SUB, MALE_DEAD_HEAD_FRONT);
					}
					gDigit::pick(_bindCharacter->getStatusBeShot(), DIGIT::PART::HEAD);
				}
				//라이플, 피격, 왼쪽/앞
				else if (gDigit::chk(_bindCharacter->getStatusBeShot(), DIGIT::PART::LEFT))
				{
					if (_isFemale)
					{

					}
					else
					{
						changeBindBit(ANIBIT::WEAPON, AWEAPON_RIFLE);
						changeBindBit(ANIBIT::MAIN, MALE_DEAD);
						changeBindBit(ANIBIT::SUB, MALE_DEAD_LEFT_FRONT);
					}
					gDigit::pick(_bindCharacter->getStatusBeShot(), DIGIT::PART::LEFT);
				}
				//라이플, 피격, 오른쪽/앞
				else if (gDigit::chk(_bindCharacter->getStatusBeShot(), DIGIT::PART::RIGHT))
				{
					if (_isFemale)
					{

					}
					else
					{
						changeBindBit(ANIBIT::WEAPON, AWEAPON_RIFLE);
						changeBindBit(ANIBIT::MAIN, MALE_DEAD);
						changeBindBit(ANIBIT::SUB, MALE_DEAD_RIGHT_FRONT);
					}
					gDigit::pick(_bindCharacter->getStatusBeShot(), DIGIT::PART::RIGHT);
				}
				//라이플, 피격, 중간/앞
				else if (gDigit::chk(_bindCharacter->getStatusBeShot(), DIGIT::PART::MIDDLE))
				{
					if (_isFemale)
					{

					}
					else
					{
						changeBindBit(ANIBIT::WEAPON, AWEAPON_RIFLE);
						changeBindBit(ANIBIT::MAIN, MALE_DEAD);
						changeBindBit(ANIBIT::SUB, MALE_DEAD_MIDDLE_FRONT);
					}
					gDigit::pick(_bindCharacter->getStatusBeShot(), DIGIT::PART::MIDDLE);
				}

				//라이플, 피격, 왼쪽/뒤
				//라이플, 피격, 오른쪽/뒤
				//라이플, 피격, 중간/뒤
				//라이플, 피격, 머리/뒤
			}
		}
		else if (_isFemale)
		{
			//--, 달리는 중 피격, 머리
			if (gDigit::chk(_bindCharacter->getStatusBeShot(), DIGIT::PART::HEAD))
			{

				gDigit::pick(_bindCharacter->getStatusBeShot(), DIGIT::PART::HEAD);
			}
			//--, 달리는 중 피격, 중간
			else if (gDigit::chk(_bindCharacter->getStatusBeShot(), DIGIT::PART::MIDDLE))
			{

				gDigit::pick(_bindCharacter->getStatusBeShot(), DIGIT::PART::MIDDLE);
			}
			//--, 달리는 중 피격, 다른부위
			else if (gDigit::chk(_bindCharacter->getStatusBeShot(), DIGIT::PART::ORDER) ||
				gDigit::chk(_bindCharacter->getStatusBeShot(), DIGIT::PART::RIGHT) ||
				gDigit::chk(_bindCharacter->getStatusBeShot(), DIGIT::PART::LEFT))
			{

				gDigit::pick(_bindCharacter->getStatusBeShot(), DIGIT::PART::ORDER);
				gDigit::pick(_bindCharacter->getStatusBeShot(), DIGIT::PART::RIGHT);
				gDigit::pick(_bindCharacter->getStatusBeShot(), DIGIT::PART::LEFT);
			}
		}
		else
		{
			if (gDigit::chk(_bindCharacter->getStatusBeShot(), DIGIT::PART::BYSHOTGUN))
			{
				//샷건, 달리는 중 피격, 머리
				if (gDigit::chk(_bindCharacter->getStatusBeShot(), DIGIT::PART::HEAD))
				{
					changeBindBit(ANIBIT::WEAPON, AWEAPON_PUMPSHOTGUN);
					changeBindBit(ANIBIT::MAIN, MALE_RUNNING_DEAD);
					changeBindBit(ANIBIT::SUB, MALE_RD_HEAD);
					gDigit::pick(_bindCharacter->getStatusBeShot(), DIGIT::PART::HEAD);
				}
				//샷건, 달리는 중 피격, 몸통
				else if (gDigit::chk(_bindCharacter->getStatusBeShot(), DIGIT::PART::MIDDLE))
				{
					changeBindBit(ANIBIT::WEAPON, AWEAPON_PUMPSHOTGUN);
					changeBindBit(ANIBIT::MAIN, MALE_RUNNING_DEAD);
					changeBindBit(ANIBIT::SUB, MALE_RD_MIDDLE);
					gDigit::pick(_bindCharacter->getStatusBeShot(), DIGIT::PART::MIDDLE);
				}
				//샷건, 달리는 중 피격, 나머지 부분
				else if (gDigit::chk(_bindCharacter->getStatusBeShot(), DIGIT::PART::ORDER) ||
					gDigit::chk(_bindCharacter->getStatusBeShot(), DIGIT::PART::RIGHT) ||
					gDigit::chk(_bindCharacter->getStatusBeShot(), DIGIT::PART::LEFT))
				{
					changeBindBit(ANIBIT::WEAPON, AWEAPON_PUMPSHOTGUN);
					changeBindBit(ANIBIT::MAIN, MALE_RUNNING_DEAD);
					changeBindBit(ANIBIT::SUB, MALE_RD_ORDER);
					gDigit::pick(_bindCharacter->getStatusBeShot(), DIGIT::PART::ORDER);
					gDigit::pick(_bindCharacter->getStatusBeShot(), DIGIT::PART::RIGHT);
					gDigit::pick(_bindCharacter->getStatusBeShot(), DIGIT::PART::LEFT);
				}
			}
			else
			{
				//라이플, 달리는 중 피격, 머리
				if (gDigit::chk(_bindCharacter->getStatusBeShot(), DIGIT::PART::HEAD))
				{
					changeBindBit(ANIBIT::WEAPON, AWEAPON_RIFLE);
					changeBindBit(ANIBIT::MAIN, MALE_RUNNING_DEAD);
					changeBindBit(ANIBIT::SUB, MALE_RD_HEAD);
					gDigit::pick(_bindCharacter->getStatusBeShot(), DIGIT::PART::HEAD);
				}
				//라이플, 달리는 중 피격, 몸통
				else if (gDigit::chk(_bindCharacter->getStatusBeShot(), DIGIT::PART::MIDDLE))
				{
					changeBindBit(ANIBIT::WEAPON, AWEAPON_RIFLE);
					changeBindBit(ANIBIT::MAIN, MALE_RUNNING_DEAD);
					changeBindBit(ANIBIT::SUB, MALE_RD_MIDDLE);
					gDigit::pick(_bindCharacter->getStatusBeShot(), DIGIT::PART::MIDDLE);
				}
				//라이플, 달리는 중 피격, 나머지 부분
				else if (gDigit::chk(_bindCharacter->getStatusBeShot(), DIGIT::PART::ORDER) ||
					gDigit::chk(_bindCharacter->getStatusBeShot(), DIGIT::PART::RIGHT) ||
					gDigit::chk(_bindCharacter->getStatusBeShot(), DIGIT::PART::LEFT))
				{
					changeBindBit(ANIBIT::WEAPON, AWEAPON_RIFLE);
					changeBindBit(ANIBIT::MAIN, MALE_RUNNING_DEAD);
					changeBindBit(ANIBIT::SUB, MALE_RD_ORDER);
					gDigit::pick(_bindCharacter->getStatusBeShot(), DIGIT::PART::ORDER);
					gDigit::pick(_bindCharacter->getStatusBeShot(), DIGIT::PART::RIGHT);
					gDigit::pick(_bindCharacter->getStatusBeShot(), DIGIT::PART::LEFT);
				}
			}
		}
		gDigit::pick(_bindCharacter->getStatusBeShot(), DIGIT::PART::BYSHOTGUN);
		gDigit::pick(_bindCharacter->getStatusBeShot(), DIGIT::PART::BYRIFLE);
	}
}
