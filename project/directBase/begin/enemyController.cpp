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
	// �Ѿ����� ����(����)
	if (gDigit::chk(_bindCharacter->getInfoCharacter().status, DIGIT::CHAR::DEAD))
	{
		if (_isFemale)
		{
			changeBindBit(aniDefine::ANIBIT::MAIN, FEMALE_LYING);
			//�ڷ�
			changeBindBit(aniDefine::ANIBIT::SUB, FEMALE_LYING_BACKWARD);
			//����
			//changeBindBit(aniDefine::ANIBIT::SUB, FEMALE_LYING_LEFTWARD);
			//������
			//changeBindBit(aniDefine::ANIBIT::SUB, FEMALE_LYING_RIGHTWARD);
			//������
			//changeBindBit(aniDefine::ANIBIT::SUB, FEMALE_LYING_FRONTWARD);
		}
		else
		{
			//�ڷ�
			changeBindBit(aniDefine::ANIBIT::MAIN, MALE_LYING);
			changeBindBit(aniDefine::ANIBIT::SUB, MALE_LYING_BACKWARD);

			//��������
			//changeBindBit(aniDefine::ANIBIT::SUB, MALE_LYING_LEFTWARD);
			//������
			//changeBindBit(aniDefine::ANIBIT::SUB, MALE_LYING_FRONTWARD);
		}
		_delay = VALUE::delayHangOut;
		// 3�ʵ� �����
		_infoTimeEnemy.timeNextDisappear = MN_TIME->getRunningTime() + 3.0f;
		return;
	}
	
	// �ǰ� ����(��)
	else if (gDigit::chk(_bindCharacter->getInfoCharacter().status, DIGIT::CHAR::BESHOT))
	{
		updateBeShot();
		return;
	}
	
	// �ǰ� ����(������)
	else if (gDigit::chk(_bindCharacter->getInfoCharacter().status, DIGIT::CHAR::SHOVED))
	{
		//������ �ִϸ��̼��� ������ ���
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
			�̰����� �����̴�  ���� üũ �����Ѱ�?
			*/
			D3DXVECTOR3 playerToEnemyDirection = _bindCharacter->getPosition() - SGT_GAME->getSet().player->getPosition();
			float angle = D3DXVec2Dot(&D3DXVECTOR2(_bindCharacter->getDirectForward().x,_bindCharacter->getDirectForward().z),
				&D3DXVECTOR2(playerToEnemyDirection.x, playerToEnemyDirection.z));
			if (gDigit::chk(_bindCharacter->getInfoMove().status, DIGIT::MOVE::MOVEING))
			{
				if (angle < 0)
				{
					//�޸��� ���� �ڿ���
					changeBindBit(aniDefine::ANIBIT::SUB, FEMALE_SHOVED_BACK_RUN);
				}
				else
				{
					//�޸��� ���� �տ���
					changeBindBit(aniDefine::ANIBIT::SUB, FEMALE_SHOVED_FRONT_RUN);
				}
			}
			else
			{
				if (angle < 0)
				{
					//�ڿ���
					changeBindBit(aniDefine::ANIBIT::SUB, FEMALE_SHOVED_BACKWARD);
				}
				else
				{
					//�տ���
					changeBindBit(aniDefine::ANIBIT::SUB, FEMALE_SHOVED_FRONTWARD);
				}

			}
		}
		_delay = VALUE::findSomthingDistance;
		return;
	}

	// ����
	else if (gDigit::chk(_bindCharacter->getInfoCharacter().status, DIGIT::CHAR::ADJACENT))
		//���� �������߰�?
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


	// �⺻ ����
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
	// ��� ����
	else if (_path->getDistance() <= VALUE::aletyDistance &&
		_path->getDistance() >= VALUE::findSomthingDistance)
	{
		//D3DXVECTOR3 direction =  ((enemyBase*)_bindCharacter)->refNextPlacePos() - _bindCharacter->getPosition();
		//float cosValue = D3DXVec2Dot(&D3DXVECTOR2(_bindCharacter->getDirectForward().x, _bindCharacter->getDirectForward().z),
		//	&D3DXVECTOR2(direction.x, direction.z));
		//if (cosValue <= FLT_EPSILON)
		{
			// �ѷ�����
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
		//// ȸ���ϰ�
		//else
		//{
		//	//������带 ���ؼ� �������� ȸ��
		//	if (cosValue > 0.0f)
		//	{
		//		changeBindBit(aniDefine::ANIBIT::MAIN, MALE_TURN);
		//		changeBindBit(aniDefine::ANIBIT::SUB, MALE_TURN_LEFT);
		//		_bindCharacter->getInfoCharacter().status = DIGIT::CHAR::LROTATE;
		//	}
		//	//���� ��带 ���ؼ� ���������� ȸ��
		//	else
		//	{
		//		changeBindBit(aniDefine::ANIBIT::MAIN, MALE_TURN);
		//		changeBindBit(aniDefine::ANIBIT::SUB, MALE_TURN_RIGHT);
		//		_bindCharacter->getInfoCharacter().status = DIGIT::CHAR::RROTATE;
		//	}
		//}
		_delay = VALUE::delayAlert;
	}
	// �޸���
	else if (_path->getDistance() < VALUE::findSomthingDistance)
	{
		changeBindBit(aniDefine::ANIBIT::MAIN, MALE_RUN);
		changeBindBit(aniDefine::ANIBIT::SUB, MALE_RUN_NONE);
		_delay = VALUE::delayMove;
		_bindCharacter->getInfoCharacter().status = DIGIT::CHAR::APPROACH;
	}

	// ����
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
	//�ǰ� ����� ������ ���
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
				//����, �ǰ�, �Ӹ�/��
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
				//����, �ǰ�, ����/��
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
				//����, �ǰ�, ������/��
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
				//����, �ǰ�, �߰�/��
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


				//����, �ǰ�, ����/��
				//����, �ǰ�, ������/��
				//����, �ǰ�, �߰�/��
				//����, �ǰ�, �Ӹ�/��
			}
			else
			{
				//������, �ǰ�, �Ӹ�/��
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
				//������, �ǰ�, ����/��
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
				//������, �ǰ�, ������/��
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
				//������, �ǰ�, �߰�/��
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

				//������, �ǰ�, ����/��
				//������, �ǰ�, ������/��
				//������, �ǰ�, �߰�/��
				//������, �ǰ�, �Ӹ�/��
			}
		}
		else if (_isFemale)
		{
			//--, �޸��� �� �ǰ�, �Ӹ�
			if (gDigit::chk(_bindCharacter->getStatusBeShot(), DIGIT::PART::HEAD))
			{

				gDigit::pick(_bindCharacter->getStatusBeShot(), DIGIT::PART::HEAD);
			}
			//--, �޸��� �� �ǰ�, �߰�
			else if (gDigit::chk(_bindCharacter->getStatusBeShot(), DIGIT::PART::MIDDLE))
			{

				gDigit::pick(_bindCharacter->getStatusBeShot(), DIGIT::PART::MIDDLE);
			}
			//--, �޸��� �� �ǰ�, �ٸ�����
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
				//����, �޸��� �� �ǰ�, �Ӹ�
				if (gDigit::chk(_bindCharacter->getStatusBeShot(), DIGIT::PART::HEAD))
				{
					changeBindBit(ANIBIT::WEAPON, AWEAPON_PUMPSHOTGUN);
					changeBindBit(ANIBIT::MAIN, MALE_RUNNING_DEAD);
					changeBindBit(ANIBIT::SUB, MALE_RD_HEAD);
					gDigit::pick(_bindCharacter->getStatusBeShot(), DIGIT::PART::HEAD);
				}
				//����, �޸��� �� �ǰ�, ����
				else if (gDigit::chk(_bindCharacter->getStatusBeShot(), DIGIT::PART::MIDDLE))
				{
					changeBindBit(ANIBIT::WEAPON, AWEAPON_PUMPSHOTGUN);
					changeBindBit(ANIBIT::MAIN, MALE_RUNNING_DEAD);
					changeBindBit(ANIBIT::SUB, MALE_RD_MIDDLE);
					gDigit::pick(_bindCharacter->getStatusBeShot(), DIGIT::PART::MIDDLE);
				}
				//����, �޸��� �� �ǰ�, ������ �κ�
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
				//������, �޸��� �� �ǰ�, �Ӹ�
				if (gDigit::chk(_bindCharacter->getStatusBeShot(), DIGIT::PART::HEAD))
				{
					changeBindBit(ANIBIT::WEAPON, AWEAPON_RIFLE);
					changeBindBit(ANIBIT::MAIN, MALE_RUNNING_DEAD);
					changeBindBit(ANIBIT::SUB, MALE_RD_HEAD);
					gDigit::pick(_bindCharacter->getStatusBeShot(), DIGIT::PART::HEAD);
				}
				//������, �޸��� �� �ǰ�, ����
				else if (gDigit::chk(_bindCharacter->getStatusBeShot(), DIGIT::PART::MIDDLE))
				{
					changeBindBit(ANIBIT::WEAPON, AWEAPON_RIFLE);
					changeBindBit(ANIBIT::MAIN, MALE_RUNNING_DEAD);
					changeBindBit(ANIBIT::SUB, MALE_RD_MIDDLE);
					gDigit::pick(_bindCharacter->getStatusBeShot(), DIGIT::PART::MIDDLE);
				}
				//������, �޸��� �� �ǰ�, ������ �κ�
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
