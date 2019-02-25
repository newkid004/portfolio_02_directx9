#include "enemyBase.h"

#include "managerList.h"
#include "gFunc.h"
#include "gDigit.h"

#include "aStar_path.h"
#include "aStar_node.h"
#include "aStar_runner.h"

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

	// Á×À½
	if (gDigit::chk(charStatus, DIGIT_CHAR::DEAD))
		return;

	if (gDigit::chk(charStatus, DIGIT_CHAR::ATTACK))
		return;

	// Á¢±Ù
	if (gDigit::chk(charStatus, DIGIT_CHAR::APPROACH))
		updateApproach();
}

void enemyBase::updateApproach(void)
{
	int & charStatus = _infoCharacter.status;
	auto refPlayer = SGT_GAME->getSet().player;

	gDigit::put(charStatus, DIGIT_CHAR::APPROACH);

	float distance = gFunc::Vec3Distance(refPlayer->getPosition(), _position);
	if (distance < 10.0f)
		gDigit::put(charStatus, DIGIT_CHAR::ADJACENT);
	else
	{
		gDigit::pick(charStatus, DIGIT_CHAR::ADJACENT);
		rotate2Pos(_controller->getDestPos(), true, true);
		moveDo(DIGIT::KEY::W);
	}
}