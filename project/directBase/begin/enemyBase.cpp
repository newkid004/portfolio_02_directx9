#include "enemyBase.h"

#include "managerList.h"
#include "gFunc.h"
#include "gDigit.h"

#include "inGame_digit.h"
#include "inGame_value.h"

#include "enemyController.h"

#include "player.h"

#include "eventDef.h"
#include "patternMesh.h"
#include "weaponNormal.h"

using DIGIT = inGame_digit;
using DIGIT_WEAPON = DIGIT::WEAPON;
using DIGIT_CHAR = DIGIT::CHAR;

enemyBase::enemyBase(patternMesh* duplicateTarget) :
	characterBase(duplicateTarget)
{
	_infoCharacter.maxHp = 10;
	_infoCharacter.nowHp = 10;

	_controller = new enemyController(this);

	duplicateTarget->init();

	_weapon = new weaponNormal(this, 3);
}

enemyBase::~enemyBase()
{
	SAFE_DELETE(_weapon);
}

void enemyBase::update(void)
{
	characterBase::update();

	int & charStatus = _infoCharacter.status;
	int & weaponStatus = _weapon->getInfoWeapon().status;

	// ����
	if (gDigit::chk(charStatus, DIGIT_CHAR::DEAD))
	{
		// ���ȯ ����
		doResurrection();
		return;
	}

	// ����
	if (gDigit::chk(charStatus, DIGIT_CHAR::APPROACH))
		updateApproach();

	// �Ÿ� Ȯ��
	//else
	//	updateAlert();
}

void enemyBase::updateApproach(void)
{
	int & charStatus = _infoCharacter.status;
	auto refPlayer = SGT_GAME->getSet().player;

	gDigit::put(charStatus, DIGIT_CHAR::APPROACH);

	float distance = gFunc::Vec3Distance(refPlayer->getPosition(), _position);
	if (distance < 5.0f)
		gDigit::put(charStatus, DIGIT_CHAR::ADJACENT);
	else
	{
		gDigit::pick(charStatus, DIGIT_CHAR::ADJACENT);
		rotate2Pos(refPlayer->getPosition(), true, true);
		moveDo(DIGIT::KEY::W);
	}
}

void enemyBase::updateAlert(void)
{
	int & charStatus = _infoCharacter.status;
	auto refPlayer = SGT_GAME->getSet().player;

	float distance = gFunc::Vec3Distance(refPlayer->getPosition(), _position);
	if (distance < inGame_value::enemy::aletyDistance)
		gDigit::put(charStatus, DIGIT_CHAR::ALERT);
}

void enemyBase::doResurrection(void)
{
	// ��Ȱ�ð� Ȯ��
	enemyController* con = static_cast<enemyController*>(_controller);
	if (MN_TIME->getRunningTime() < con->refInfoTimeEnemy().timeNextAlive)
		return;


}