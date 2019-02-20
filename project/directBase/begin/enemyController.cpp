#include "enemyController.h"

#include "managerList.h"
#include "gDigit.h"

#include "inGame_digit.h"
#include "inGame_value.h"
#include "aStar_node.h"
#include "aStar_path.h"
#include "characterBase.h"
#include "AnimationDef.h"
#include "patternMesh.h"
#include "gFunc.h"

using DIGIT = inGame_digit;
using VALUE = inGame_value;

enemyController::enemyController(characterBase * bindCharacter) :
	controllerBase(bindCharacter)
{
	gDigit::put(_bindCharacter->getInfoCharacter().status, DIGIT::CHAR::IDLE);
	baseBit();
	_infoTimeEnemy.timeNextActive = MN_TIME->getRunningTime();
	_delay = VALUE::enemy::delayHangOut;
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
	/*
	�ʿ� ����
	�÷��̾������ �Ÿ�
	���� ������ ���� ����
	*/

	// �⺻ ����
	if (_path->getDistance());

	// ��� ����
		//�ѷ�����
		//ȸ���ϰ�
		//�Ȱ�

	// �޸���
	// ����
	// ����
	// �Ѿ����� ����(����)
	// �ǰ� ����
}

void enemyController::baseBit(void)
{
	int random = gFunc::rndInt(0, 3);

	std::string basePath = _bindCharacter->getOriginMesh()->getBasePath();
	if (basePath.find("female") != std::string::npos)
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

void enemyController::changeBindBit(aniDefine::ANIBIT minusBit, int plusBit)
{
	CHANGE_BIT(_bindCharacter->getNextBit(), minusBit, plusBit);
}
