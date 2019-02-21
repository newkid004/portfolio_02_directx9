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
	//����
	if (gDigit::chk(_bindCharacter->getInfoCharacter().status, DIGIT::CHAR::DEAD))
	{
		changeBindBit(aniDefine::ANIBIT::MAIN, HULK_DEAD);
		//����, �븻
		changeBindBit(aniDefine::ANIBIT::SUB, HULK_DEAD_NORMAL);
		//����, ���
		changeBindBit(aniDefine::ANIBIT::SUB, HULK_DEAD_IDLE);
		//����, �޸��� ��
		changeBindBit(aniDefine::ANIBIT::SUB, HULK_DEAD_RUNNING);
		_delay = VALUE::delayHangOut;
		_infoTimeEnemy.timeNextDisappear = MN_TIME->getRunningTime() + 3.0f;
		return;
	}
	// �ǰ� ����
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
			//����Ÿ���, ����
			changeBindBit(aniDefine::ANIBIT::SUB, HULK_FLINCH_CHEST);
			//����Ÿ���, ����
			changeBindBit(aniDefine::ANIBIT::SUB, HULK_FLINCH_LEFT);
			//����Ÿ���, ������
			changeBindBit(aniDefine::ANIBIT::SUB, HULK_FLINCH_RIGHT);
			//����Ÿ���, ����
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
			//����, �޸���
			changeBindBit(aniDefine::ANIBIT::SUB, HULK_ATTACK_RUN);
			//����, ������
			changeBindBit(aniDefine::ANIBIT::SUB, HULK_ATTACK_FLY);
			//����, �⺻1
			changeBindBit(aniDefine::ANIBIT::SUB, HULK_ATTACK_NORMAL1);
			//����, �⺻2
			changeBindBit(aniDefine::ANIBIT::SUB, HULK_ATTACK_NORMAL2);

			_bindCharacter->getInfoCharacter().status = DIGIT::CHAR::ATTACK;
		}
		_delay = VALUE::delayMove;
		return;
	}
	// �⺻ ����
	// ��� ����
	// �޸���
}

void tankController::baseBit(void)
{
	_bindCharacter->getNextBit() =
		ATYPE_ZOMBIE_HULK |
		HULK_IDLE |
		HULK_IDLE_NORMAL;
}
