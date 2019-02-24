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
	//����
	if (gDigit::chk(_bindCharacter->getInfoCharacter().status, DIGIT::CHAR::DEAD))
	{
		changeBindBit(aniDefine::ANIBIT::MAIN, HULK_DEAD);
		if (gDigit::chk(_bindCharacter->getInfoCharacter().status, DIGIT::CHAR::APPROACH))
		{
			//����, �޸��� ��
			changeBindBit(aniDefine::ANIBIT::SUB, HULK_DEAD_RUNNING);
		}
		else
		{

			//����, �븻
			changeBindBit(aniDefine::ANIBIT::SUB, HULK_DEAD_NORMAL);
			//����, ���
			changeBindBit(aniDefine::ANIBIT::SUB, HULK_DEAD_IDLE);
		}
		
		_delay = VALUE::delayHangOut;
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
			if ((_bindCharacter->getAControllInfo().CurrentMotionBit & GET_ANIBITMASK(aniDefine::ANIBIT::MAIN))
				== HULK_RUN)
			{
				//����, �޸���
				changeBindBit(aniDefine::ANIBIT::SUB, HULK_ATTACK_RUN);
			}
			else
			{
				changeBindBit(aniDefine::ANIBIT::MAIN, HULK_ATTACK);
				switch (gFunc::rndInt(0, 3))
				{
				case 0:
					//����, ������
					changeBindBit(aniDefine::ANIBIT::SUB, HULK_ATTACK_FLY);
					break;
				case 1:
					//����, �⺻1
					changeBindBit(aniDefine::ANIBIT::SUB, HULK_ATTACK_NORMAL1);
					break;
				case 2:
					//����, �⺻2
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
	// �⺻ ����
	else if (getDistance2player() > VALUE::aletyDistance)
	{
		baseBit();
		_delay = VALUE::delayHangOut;
		_bindCharacter->getInfoCharacter().status = DIGIT::CHAR::IDLE;
	}
	// ��� ����
	else if (getDistance2player() <= VALUE::aletyDistance &&
		getDistance2player() >= VALUE::findSomthingDistance)
	{
		/*D3DXVECTOR3 direction = ((enemyBase*)_bindCharacter)->refNextPlacePos() - _bindCharacter->getPosition();
		float cosValue = D3DXVec2Dot(&D3DXVECTOR2(_bindCharacter->getDirectForward().x, _bindCharacter->getDirectForward().z),
			&D3DXVECTOR2(direction.x, direction.z));*/
		//if (cosValue <= FLT_EPSILON)
		{
			//�Ҹ�ġ��
			changeBindBit(aniDefine::ANIBIT::MAIN, HULK_IDLE);
			changeBindBit(aniDefine::ANIBIT::SUB, HULK_IDLE_YELL);

			_bindCharacter->getInfoCharacter().status = DIGIT::CHAR::ALERT;
		}
		// ȸ���ϰ�
		//else
		//{
		//	//���� ��带 ���ؼ� �������� ȸ��
		//	if (cosValue > 0.0f)
		//	{
		//		changeBindBit(aniDefine::ANIBIT::MAIN, HULK_TURN);
		//		changeBindBit(aniDefine::ANIBIT::SUB, HULK_TURN_LEFT);
		//		_bindCharacter->getInfoCharacter().status = DIGIT::CHAR::LROTATE;
		//	}
		//	//���� ��带 ���ؼ� ���������� ȸ��
		//	else
		//	{
		//		changeBindBit(aniDefine::ANIBIT::MAIN, HULK_TURN);
		//		changeBindBit(aniDefine::ANIBIT::SUB, HULK_TURN_RIGHT);
		//		_bindCharacter->getInfoCharacter().status = DIGIT::CHAR::RROTATE;
		//	}

			_delay = VALUE::delayAlert;
		//}
	}
	// �޸���
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
