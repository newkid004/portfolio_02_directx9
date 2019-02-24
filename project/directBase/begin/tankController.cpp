#include "tankController.h"
#include "characterBase.h"
#include "gDigit.h"
#include "gFunc.h"
#include "inGame_digit.h"
#include "inGame_value.h"
#include "AnimationDef.h"
#include "managerList.h"
#include "aStar_node.h"
#include "aStar_path.h"
#include "inGame_node.h"
#include "enemyBase.h"

using DIGIT = inGame_digit;
using VALUE = inGame_value::enemy;

tankController::tankController(characterBase * bindCharacter)
	:enemyController::enemyController(bindCharacter)
{
}

tankController::~tankController()
{
}

void tankController::update2bit(void)
{
	//죽음
	if (gDigit::chk(_bindCharacter->getInfoCharacter().status, DIGIT::CHAR::DEAD))
	{
		changeBindBit(aniDefine::ANIBIT::MAIN, HULK_DEAD);
		if (gDigit::chk(_bindCharacter->getInfoCharacter().status, DIGIT::CHAR::APPROACH))
		{
			//죽음, 달리는 중
			changeBindBit(aniDefine::ANIBIT::SUB, HULK_DEAD_RUNNING);
		}
		else
		{

			//죽음, 노말
			changeBindBit(aniDefine::ANIBIT::SUB, HULK_DEAD_NORMAL);
			//죽음, 대기
			changeBindBit(aniDefine::ANIBIT::SUB, HULK_DEAD_IDLE);
		}
		
		_delay = VALUE::delayHangOut;
		return;
	}
	// 피격 상태
	else if (gDigit::chk(_bindCharacter->getInfoCharacter().status, DIGIT::CHAR::BESHOT))
	{
		if ((_bindCharacter->getAControllInfo().CurrentMotionBit & GET_ANIBITMASK(aniDefine::ANIBIT::MAIN))
			== HULK_FLINCH)
		{
			if (_bindCharacter->getAControllInfo().persent >= 0.8f)
			{
				gDigit::pick(_bindCharacter->getInfoCharacter().status, DIGIT::CHAR::BESHOT);
			}
		}
		else
		{
			changeBindBit(aniDefine::ANIBIT::MAIN, HULK_FLINCH);
			//움찔거리는, 가슴
			changeBindBit(aniDefine::ANIBIT::SUB, HULK_FLINCH_CHEST);
			//움찔거리는, 왼쪽
			changeBindBit(aniDefine::ANIBIT::SUB, HULK_FLINCH_LEFT);
			//움찔거리는, 오른쪽
			changeBindBit(aniDefine::ANIBIT::SUB, HULK_FLINCH_RIGHT);
			//움찔거리는, 복부
			changeBindBit(aniDefine::ANIBIT::SUB, HULK_FLINCH_STOMACH);
		}

		return;
	}
	else if (gDigit::chk(_bindCharacter->getInfoCharacter().status, DIGIT::CHAR::ADJACENT))
	{
		if ((_bindCharacter->getAControllInfo().CurrentMotionBit & GET_ANIBITMASK(aniDefine::ANIBIT::MAIN))
			== HULK_ATTACK)
		{
			if (_bindCharacter->getAControllInfo().persent >= 0.8f)
			{
				gDigit::pick(_bindCharacter->getInfoCharacter().status, DIGIT::CHAR::ATTACK);
			}
		}
		else
		{
			if ((_bindCharacter->getAControllInfo().CurrentMotionBit & GET_ANIBITMASK(aniDefine::ANIBIT::MAIN))
				== HULK_RUN)
			{
				//공격, 달리기
				changeBindBit(aniDefine::ANIBIT::SUB, HULK_ATTACK_RUN);
			}
			else
			{
				changeBindBit(aniDefine::ANIBIT::MAIN, HULK_ATTACK);
				switch (gFunc::rndInt(0, 3))
				{
				case 0:
					//공격, 날리기
					changeBindBit(aniDefine::ANIBIT::SUB, HULK_ATTACK_FLY);
					break;
				case 1:
					//공격, 기본1
					changeBindBit(aniDefine::ANIBIT::SUB, HULK_ATTACK_NORMAL1);
					break;
				case 2:
					//공격, 기본2
					changeBindBit(aniDefine::ANIBIT::SUB, HULK_ATTACK_NORMAL2);
					break;
				default:
					break;
				}
			}

			gDigit::put(_bindCharacter->getInfoCharacter().status, DIGIT::CHAR::ATTACK);
		}
		_delay = VALUE::delayMove;
		return;
	}
	// 기본 상태
	else if (getDistance2player() > VALUE::aletyDistance)
	{
		baseBit();
		_delay = VALUE::delayHangOut;
		_bindCharacter->getInfoCharacter().status = DIGIT::CHAR::IDLE;
	}
	// 경계 상태
	else if (getDistance2player() <= VALUE::aletyDistance &&
		getDistance2player() >= VALUE::findSomthingDistance)
	{
		/*D3DXVECTOR3 direction = ((enemyBase*)_bindCharacter)->refNextPlacePos() - _bindCharacter->getPosition();
		float cosValue = D3DXVec2Dot(&D3DXVECTOR2(_bindCharacter->getDirectForward().x, _bindCharacter->getDirectForward().z),
			&D3DXVECTOR2(direction.x, direction.z));*/
		//if (cosValue <= FLT_EPSILON)
		{
			//소리치고
			changeBindBit(aniDefine::ANIBIT::MAIN, HULK_IDLE);
			changeBindBit(aniDefine::ANIBIT::SUB, HULK_IDLE_YELL);

			_bindCharacter->getInfoCharacter().status = DIGIT::CHAR::ALERT;
		}
		// 회전하고
		//else
		//{
		//	//다음 노드를 향해서 왼쪽으로 회전
		//	if (cosValue > 0.0f)
		//	{
		//		changeBindBit(aniDefine::ANIBIT::MAIN, HULK_TURN);
		//		changeBindBit(aniDefine::ANIBIT::SUB, HULK_TURN_LEFT);
		//		_bindCharacter->getInfoCharacter().status = DIGIT::CHAR::LROTATE;
		//	}
		//	//다음 노드를 향해서 오른쪽으로 회전
		//	else
		//	{
		//		changeBindBit(aniDefine::ANIBIT::MAIN, HULK_TURN);
		//		changeBindBit(aniDefine::ANIBIT::SUB, HULK_TURN_RIGHT);
		//		_bindCharacter->getInfoCharacter().status = DIGIT::CHAR::RROTATE;
		//	}

			_delay = VALUE::delayAlert;
		//}
	}
	// 달리기
	else if (_path->getDistance() < VALUE::findSomthingDistance)
	{
		changeBindBit(aniDefine::ANIBIT::MAIN, HULK_RUN);
		changeBindBit(aniDefine::ANIBIT::SUB, HULK_RUN_NORMAL);
		_delay = VALUE::delayMove;
		_bindCharacter->getInfoCharacter().status = DIGIT::CHAR::APPROACH;
	}
}

void tankController::baseBit(void)
{
	_bindCharacter->getNextBit() =
		ATYPE_ZOMBIE_HULK |
		HULK_IDLE |
		HULK_IDLE_NORMAL;
}
