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
		if(!gDigit::chk(_bindCharacter->getInfoCharacter().status, DIGIT::CHAR::DEAD))	controllerBase::update();
		_infoTimeEnemy.timeNextActive = MN_TIME->getRunningTime() + _delay;
	}
	update2bit();
}

void enemyController::update2bit(void)
{
	float distance = getDistance2player();
	bool isWave = gDigit::chk(SGT_GAME->getStatus().digitActive, sysDigit::wave);

	// �Ѿ����� ����(����)
	if (gDigit::chk(_bindCharacter->getInfoCharacter().status, DIGIT::CHAR::DEAD))
	{
		changeBindBit(ANIBIT::WEAPON, AWEAPON_NONE);
		if (_isFemale)
		{
			if (_soundT.mouse.find("death_f") == std::string::npos)
			{
				_soundT.mouseSoundDelay = 2.5f;
				MN_SND->find(_soundT.mouse)->stop();
				_soundT.mouse = "death_f";
				_soundT.mouseSoundStart = MN_TIME->getRunningTime() + _soundT.mouseSoundDelay;
				MN_SND->find("death_f")->play(gFunc::getSoundVolumeToPlayer(_bindCharacter->getPosition()));
			}
			changeBindBit(aniDefine::ANIBIT::MAIN, FEMALE_LYING);
			//�ڷ�
			changeBindBit(aniDefine::ANIBIT::SUB, FEMALE_LYING_BACKWARD);
		}
		else
		{
			if (_soundT.mouse.find("death_m") == std::string::npos)
			{
				_soundT.mouseSoundDelay = 2.5f;
				MN_SND->find(_soundT.mouse)->stop();
				_soundT.mouse = "death_m";
				_soundT.mouseSoundStart = MN_TIME->getRunningTime() + _soundT.mouseSoundDelay;
				MN_SND->find("death_m")->play(gFunc::getSoundVolumeToPlayer(_bindCharacter->getPosition()));
			}
			//�ڷ�
			changeBindBit(aniDefine::ANIBIT::MAIN, MALE_LYING);
			changeBindBit(aniDefine::ANIBIT::SUB, MALE_LYING_BACKWARD);
		}
		_delay = VALUE::delayHangOut;
		return;
	}
	
	// �ǰ� ����(��)
	else if (gDigit::chk(_bindCharacter->getInfoCharacter().status, DIGIT::CHAR::BESHOT))
	{
		if (_soundT.effectSoundStart < MN_TIME->getRunningTime())
		{
			_soundT.effectSoundStart = MN_TIME->getRunningTime() + _soundT.effectSoundDelay;
			MN_SND->find("bullet_gib")->play(gFunc::getSoundVolumeToPlayer(_bindCharacter->getPosition()),
				gFunc::rndFloat(0.6f, 0.8f));
		}
		if (gDigit::chk(_bindCharacter->getStatusBeShot(), DIGIT::PART::HEAD))
		{
			if (_soundT.mouse.find("headless") == std::string::npos)
			{
				_soundT.mouseSoundDelay = 2.5f;
				MN_SND->find(_soundT.mouse)->stop();
				_soundT.mouse = "headless";
				_soundT.mouseSoundStart = MN_TIME->getRunningTime() + _soundT.mouseSoundDelay;
				MN_SND->find("headless")->play(gFunc::getSoundVolumeToPlayer(_bindCharacter->getPosition()));
			}
			else
			{
				if (_soundT.mouseSoundStart < MN_TIME->getRunningTime())
				{
					MN_SND->find("headless")->play(gFunc::getSoundVolumeToPlayer(_bindCharacter->getPosition()),
						gFunc::rndFloat(0.6f, 1.0f));
					_soundT.mouseSoundStart = MN_TIME->getRunningTime() + _soundT.mouseSoundDelay;
				}
			}
		}
		else
		{
			if (_isFemale)
			{
				if (_soundT.mouse.find("been_shot_f") == std::string::npos)
				{
					_soundT.mouseSoundDelay = 2.5f;
					MN_SND->find(_soundT.mouse)->stop();
					_soundT.mouse = "been_shot_f";
					_soundT.mouseSoundStart = MN_TIME->getRunningTime() + _soundT.mouseSoundDelay;
					MN_SND->find("been_shot_f")->play(gFunc::getSoundVolumeToPlayer(_bindCharacter->getPosition()));
				}
				else
				{
					if (_soundT.mouseSoundStart < MN_TIME->getRunningTime())
					{
						MN_SND->find("been_shot_f")->play(gFunc::getSoundVolumeToPlayer(_bindCharacter->getPosition()),
							gFunc::rndFloat(0.6f, 1.0f));
						_soundT.mouseSoundStart = MN_TIME->getRunningTime() + _soundT.mouseSoundDelay;
					}
				}
			}
			else
			{
				if (_soundT.mouse.find("been_shot_m") == std::string::npos)
				{
					_soundT.mouseSoundDelay = 2.5f;
					MN_SND->find(_soundT.mouse)->stop();
					_soundT.mouse = "been_shot_m";
					_soundT.mouseSoundStart = MN_TIME->getRunningTime() + _soundT.mouseSoundDelay;
					MN_SND->find("been_shot_m")->play(gFunc::getSoundVolumeToPlayer(_bindCharacter->getPosition()));
				}
				else
				{
					if (_soundT.mouseSoundStart < MN_TIME->getRunningTime())
					{
						MN_SND->find("been_shot_m")->play(gFunc::getSoundVolumeToPlayer(_bindCharacter->getPosition()),
							gFunc::rndFloat(0.6f, 1.0f));
						_soundT.mouseSoundStart = MN_TIME->getRunningTime() + _soundT.mouseSoundDelay;
					}
				}

			}
		}

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
				return;
			}
		}
		else
		{
			changeBindBit(aniDefine::ANIBIT::MAIN, FEMALE_SHOVED);

			/*
			�̰����� �����̴�  ���� üũ �����Ѱ�?
			*/
			if (gDigit::chk(_bindCharacter->getInfoMove().status, DIGIT::MOVE::MOVEING))
			{
				//�޸��� ���� �տ���
				changeBindBit(aniDefine::ANIBIT::SUB, FEMALE_SHOVED_FRONT_RUN);
			}
			else
			{
				//�տ���
				changeBindBit(aniDefine::ANIBIT::SUB, FEMALE_SHOVED_FRONTWARD);
			}
		}
		_delay = VALUE::findSomthingDistance;
		return;
	}

	// ����
	else if (gDigit::chk(_bindCharacter->getInfoCharacter().status, DIGIT::CHAR::ADJACENT))
	{
		_delay = VALUE::delayMove;
		return;
	}


	// �⺻ ����
	else if (distance > (isWave ? VALUE::aletyDistance : VALUE::aletyDistance * 100))
	{
		
		if (_isFemale)
		{
			changeBindBit(aniDefine::ANIBIT::MAIN, FEMALE_IDLE);
			changeBindBit(aniDefine::ANIBIT::SUB, FEMALE_IDLE_NEUTRAL1);
			if (_soundT.mouse.find("idle_breath") == std::string::npos)
			{
				_soundT.mouseSoundDelay = 2.5f;
				MN_SND->find(_soundT.mouse)->stop();
				_soundT.mouse = "idle_breath";
				_soundT.mouseSoundStart = MN_TIME->getRunningTime() + _soundT.mouseSoundDelay;
				MN_SND->find("idle_breath")->play(gFunc::getSoundVolumeToPlayer(_bindCharacter->getPosition()));
			}
			else
			{
				if (_soundT.mouseSoundStart < MN_TIME->getRunningTime())
				{
					MN_SND->find("idle_breath")->play(gFunc::getSoundVolumeToPlayer(_bindCharacter->getPosition()),
						gFunc::rndFloat(0.6f, 1.0f));
					_soundT.mouseSoundStart = MN_TIME->getRunningTime() + _soundT.mouseSoundDelay;
				}
			}
		}
		else
		{
			if (_soundT.mouse.find("breathing") == std::string::npos)
			{
				_soundT.mouseSoundDelay = 2.5f;
				MN_SND->find(_soundT.mouse)->stop();
				_soundT.mouse = "breathing";
				_soundT.mouseSoundStart = MN_TIME->getRunningTime() + _soundT.mouseSoundDelay;
				MN_SND->find("breathing")->play(gFunc::getSoundVolumeToPlayer(_bindCharacter->getPosition()));
			}
			else
			{
				if (_soundT.mouseSoundStart < MN_TIME->getRunningTime())
				{
					MN_SND->find("breathing")->play(gFunc::getSoundVolumeToPlayer(_bindCharacter->getPosition()),
						gFunc::rndFloat(0.6f, 1.0f));
					_soundT.mouseSoundStart = MN_TIME->getRunningTime() + _soundT.mouseSoundDelay;
				}
			}
			changeBindBit(aniDefine::ANIBIT::MAIN, MALE_IDLE);
			changeBindBit(aniDefine::ANIBIT::SUB, MALE_IDLE_NEUTRAL1);
		}
		_delay = VALUE::delayHangOut;
		_bindCharacter->getInfoCharacter().status =  DIGIT::CHAR::IDLE;
	}
	// ��� ����
	else if (	distance <= (isWave ? VALUE::aletyDistance : VALUE::aletyDistance * 10) &&
				distance >= (isWave ? VALUE::findSomthingDistance : VALUE::findSomthingDistance * 10))
	{
		// �ѷ�����
		if (_isFemale)
		{
			if (_soundT.mouse.find("alert_f") == std::string::npos)
			{
				_soundT.mouseSoundDelay = 3.0f;
				MN_SND->find(_soundT.mouse)->stop();
				_soundT.mouse = "alert_f";
				_soundT.mouseSoundStart = MN_TIME->getRunningTime() + _soundT.mouseSoundDelay;
				MN_SND->find("alert_f")->play(gFunc::getSoundVolumeToPlayer(_bindCharacter->getPosition()));
			}
			else
			{
				if (_soundT.mouseSoundStart < MN_TIME->getRunningTime())
				{
					MN_SND->find("alert_f")->play(gFunc::getSoundVolumeToPlayer(_bindCharacter->getPosition()));
					_soundT.mouseSoundStart = MN_TIME->getRunningTime() + _soundT.mouseSoundDelay;
				}
			}
			changeBindBit(aniDefine::ANIBIT::MAIN, FEMALE_IDLE);
			changeBindBit(aniDefine::ANIBIT::SUB, FEMALE_IDLE_ALERT);
		}
		else
		{
			if (_soundT.mouse.find("alert_m") == std::string::npos)
			{
				_soundT.mouseSoundDelay = 3.0f;
				MN_SND->find(_soundT.mouse)->stop();
				_soundT.mouse = "alert_m";
				_soundT.mouseSoundStart = MN_TIME->getRunningTime() + _soundT.mouseSoundDelay;
				MN_SND->find("alert_m")->play(gFunc::getSoundVolumeToPlayer(_bindCharacter->getPosition()));
			}
			else
			{
				if (_soundT.mouseSoundStart < MN_TIME->getRunningTime())
				{
					MN_SND->find("alert_m")->play(gFunc::getSoundVolumeToPlayer(_bindCharacter->getPosition()));
					_soundT.mouseSoundStart = MN_TIME->getRunningTime() + _soundT.mouseSoundDelay;
				}
			}
			changeBindBit(aniDefine::ANIBIT::MAIN, MALE_IDLE);
			changeBindBit(aniDefine::ANIBIT::SUB, MALE_IDLE_ALERT);
		}
		_bindCharacter->getInfoCharacter().status = DIGIT::CHAR::ALERT;
		
		_delay = VALUE::delayAlert;
	}
	// �޸���
	else if (distance < (isWave ? VALUE::findSomthingDistance : 10 * VALUE::findSomthingDistance))
	{
		if(_soundT.footSoundStart < MN_TIME->getRunningTime())
		{ 
			_soundT.footSoundStart = MN_TIME->getRunningTime() + _soundT.footSoundDelay;
			MN_SND->find("commonF")->play(gFunc::getSoundVolumeToPlayer(_bindCharacter->getPosition()));
		}
		if (_isFemale)
		{
			if (_soundT.mouse.find("rage_run_f") == std::string::npos)
			{
				_soundT.mouseSoundDelay = 1.5f;
				MN_SND->find(_soundT.mouse)->stop();
				_soundT.mouse = "rage_run_f";
				_soundT.mouseSoundStart = MN_TIME->getRunningTime() + _soundT.mouseSoundDelay;
				MN_SND->find("rage_run_f")->play(gFunc::getSoundVolumeToPlayer(_bindCharacter->getPosition()),
					gFunc::rndFloat(0.5f,1.0f));
			}
			else
			{
				if (_soundT.mouseSoundStart < MN_TIME->getRunningTime())
				{
					MN_SND->find("rage_run_f")->play(gFunc::getSoundVolumeToPlayer(_bindCharacter->getPosition()),
						gFunc::rndFloat(0.5f, 1.0f));
					_soundT.mouseSoundStart = MN_TIME->getRunningTime() + _soundT.mouseSoundDelay;
				}
			}

		}
		else
		{
			if (_soundT.mouse.find("rage_run_m") == std::string::npos)
			{
				_soundT.mouseSoundDelay = 3.0f;
				MN_SND->find(_soundT.mouse)->stop();
				_soundT.mouse = "rage_run_m";
				_soundT.mouseSoundStart = MN_TIME->getRunningTime() + _soundT.mouseSoundDelay;
				MN_SND->find("rage_run_m")->play(gFunc::getSoundVolumeToPlayer(_bindCharacter->getPosition()),
					gFunc::rndFloat(0.5f, 1.0f));
			}
			else
			{
				if (_soundT.mouseSoundStart < MN_TIME->getRunningTime())
				{
					MN_SND->find("rage_run_m")->play(gFunc::getSoundVolumeToPlayer(_bindCharacter->getPosition()),
						gFunc::rndFloat(0.5f, 1.0f));
					_soundT.mouseSoundStart = MN_TIME->getRunningTime() + _soundT.mouseSoundDelay;
				}
			}
		}

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
		float intervalPlayer = aStar_node::getInterval(viewPlayer->getPlacedNode(), prevPathPlayer->getMember().placedNode);

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
	if (((_bindCharacter->getAControllInfo().CurrentMotionBit & GET_ANIBITMASK(aniDefine::ANIBIT::MAIN))== MALE_DEAD)||
		((_bindCharacter->getAControllInfo().CurrentMotionBit & GET_ANIBITMASK(aniDefine::ANIBIT::MAIN)) == MALE_RUNNING_DEAD))
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
						changeBindBit(ANIBIT::WEAPON, AWEAPON_PUMPSHOTGUN);
						changeBindBit(ANIBIT::MAIN, FEMALE_DEAD);
						changeBindBit(ANIBIT::SUB, FEMALE_DEAD_HEAD_FRONT);
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
						changeBindBit(ANIBIT::WEAPON, AWEAPON_PUMPSHOTGUN);
						changeBindBit(ANIBIT::MAIN, FEMALE_DEAD);
						changeBindBit(ANIBIT::SUB, FEMALE_DEAD_LEFT_FRONT);
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
						changeBindBit(ANIBIT::WEAPON, AWEAPON_PUMPSHOTGUN);
						changeBindBit(ANIBIT::MAIN, FEMALE_DEAD);
						changeBindBit(ANIBIT::SUB, FEMALE_DEAD_RIGHT_FRONT);
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
						changeBindBit(ANIBIT::WEAPON, AWEAPON_PUMPSHOTGUN);
						changeBindBit(ANIBIT::MAIN, FEMALE_DEAD);
						changeBindBit(ANIBIT::SUB, FEMALE_DEAD_MIDDLE_FRONT);
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
						changeBindBit(ANIBIT::WEAPON, AWEAPON_RIFLE);
						changeBindBit(ANIBIT::MAIN, FEMALE_DEAD);
						changeBindBit(ANIBIT::SUB, FEMALE_DEAD_HEAD_FRONT);
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
						changeBindBit(ANIBIT::WEAPON, AWEAPON_RIFLE);
						changeBindBit(ANIBIT::MAIN, FEMALE_DEAD);
						changeBindBit(ANIBIT::SUB, FEMALE_DEAD_LEFT_FRONT);
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
						changeBindBit(ANIBIT::WEAPON, AWEAPON_RIFLE);
						changeBindBit(ANIBIT::MAIN, FEMALE_DEAD);
						changeBindBit(ANIBIT::SUB, FEMALE_DEAD_RIGHT_FRONT);
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
						changeBindBit(ANIBIT::WEAPON, AWEAPON_RIFLE);
						changeBindBit(ANIBIT::MAIN, FEMALE_DEAD);
						changeBindBit(ANIBIT::SUB, FEMALE_DEAD_MIDDLE_FRONT);
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
				changeBindBit(ANIBIT::WEAPON, AWEAPON_RIFLE);
				changeBindBit(ANIBIT::MAIN, FEMALE_RUNNING_DEAD);
				changeBindBit(ANIBIT::SUB, FEMALE_RD_HEAD);
				gDigit::pick(_bindCharacter->getStatusBeShot(), DIGIT::PART::HEAD);
			}
			//--, �޸��� �� �ǰ�, �߰�
			else if (gDigit::chk(_bindCharacter->getStatusBeShot(), DIGIT::PART::MIDDLE))
			{
				changeBindBit(ANIBIT::WEAPON, AWEAPON_RIFLE);
				changeBindBit(ANIBIT::MAIN, FEMALE_RUNNING_DEAD);
				changeBindBit(ANIBIT::SUB, FEMALE_RD_MIDDLE);
				gDigit::pick(_bindCharacter->getStatusBeShot(), DIGIT::PART::MIDDLE);
			}
			//--, �޸��� �� �ǰ�, �ٸ�����
			else if (gDigit::chk(_bindCharacter->getStatusBeShot(), DIGIT::PART::ORDER) ||
				gDigit::chk(_bindCharacter->getStatusBeShot(), DIGIT::PART::RIGHT) ||
				gDigit::chk(_bindCharacter->getStatusBeShot(), DIGIT::PART::LEFT))
			{
				changeBindBit(ANIBIT::WEAPON, AWEAPON_RIFLE);
				changeBindBit(ANIBIT::MAIN, FEMALE_RUNNING_DEAD);
				changeBindBit(ANIBIT::SUB, FEMALE_RD_ORDER);
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
