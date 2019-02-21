#include "enemyBase.h"

#include "managerList.h"
#include "gFunc.h"
#include "gDigit.h"

#include "inGame_digit.h"
#include "inGame_value.h"

#include "enemyController.h"

#include "player.h"

#include "eventDef.h"

using DIGIT = inGame_digit;
using DIGIT_WEAPON = DIGIT::WEAPON;
using DIGIT_CHAR = DIGIT::CHAR;

enemyBase::enemyBase(patternMesh* duplicateTarget) :
	characterBase(duplicateTarget)
{
	_infoCharacter.maxHp = 10;
	_infoCharacter.nowHp = 10;

	_controller = new enemyController(this);
}

enemyBase::~enemyBase()
{
}

void enemyBase::update(void)
{
	characterBase::update();

	int charStatus = _infoCharacter.status;
	int & weaponStatus = _weapon->getInfoWeapon().status;

	// 죽음
	if (gDigit::chk(charStatus, DIGIT_CHAR::DEAD))
	{
		// 재소환 갱신
		doResurrection();
		return;
	}

	// 공격
	if (_weapon)
	{
		gDigit::pick(weaponStatus, DIGIT_WEAPON::DO_FIRE);
		if (gDigit::chk(charStatus, DIGIT_CHAR::ADJACENT))
			updateAdjacent();
	}

	// 접근
	if (gDigit::chk(charStatus, DIGIT_CHAR::APPROACH))
		updateApproach();
}

void enemyBase::updateAdjacent(void)
{
	int & weaponStatus = _weapon->getInfoWeapon().status;
	gDigit::put(weaponStatus, DIGIT_WEAPON::DO_FIRE);
}

void enemyBase::updateApproach(void)
{
	int & charStatus = _infoCharacter.status;
	auto refPlayer = SGT_GAME->getSet().player;

	float distance = gFunc::Vec3Distance(refPlayer->getPosition(), _position);
	if (distance < 25.0f)
		gDigit::put(charStatus, DIGIT_CHAR::ADJACENT);
	else
	{
		gDigit::pick(charStatus, DIGIT_CHAR::ADJACENT);
		rotate2Dir(refPlayer->getPosition(), true, true);
		moveDo(DIGIT::KEY::W);
	}
}

void enemyBase::doResurrection(void)
{
	// 부활시간 확인
	enemyController* con = static_cast<enemyController*>(_controller);
	if (MN_TIME->getRunningTime() < con->refInfoTimeEnemy().timeNextAlive)
		return;


}
