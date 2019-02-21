#include "tankController.h"
#include "characterBase.h"
#include "gDigit.h"
#include "gFunc.h"
#include "inGame_digit.h"
#include "inGame_value.h"
#include "AnimationDef.h"
#include "managerList.h"

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
		//죽음, 노말
		changeBindBit(aniDefine::ANIBIT::SUB, HULK_DEAD_NORMAL);
		//죽음, 대기
		changeBindBit(aniDefine::ANIBIT::SUB, HULK_DEAD_IDLE);
		//죽음, 달리는 중
		changeBindBit(aniDefine::ANIBIT::SUB, HULK_DEAD_RUNNING);
		_delay = VALUE::delayHangOut;
		_infoTimeEnemy.timeNextDisappear = MN_TIME->getRunningTime() + 3.0f;
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
			changeBindBit(aniDefine::ANIBIT::MAIN, HULK_ATTACK);
			//공격, 달리기
			changeBindBit(aniDefine::ANIBIT::SUB, HULK_ATTACK_RUN);
			//공격, 날리기
			changeBindBit(aniDefine::ANIBIT::SUB, HULK_ATTACK_FLY);
			//공격, 기본1
			changeBindBit(aniDefine::ANIBIT::SUB, HULK_ATTACK_NORMAL1);
			//공격, 기본2
			changeBindBit(aniDefine::ANIBIT::SUB, HULK_ATTACK_NORMAL2);

			_bindCharacter->getInfoCharacter().status = DIGIT::CHAR::ATTACK;
		}
		_delay = VALUE::delayMove;
		return;
	}
	// 기본 상태
	// 경계 상태
	// 달리기
}

void tankController::baseBit(void)
{
	_bindCharacter->getNextBit() =
		ATYPE_ZOMBIE_HULK |
		HULK_IDLE |
		HULK_IDLE_NORMAL;
}
