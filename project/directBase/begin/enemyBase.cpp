#include "enemyBase.h"

#include "managerList.h"
#include "gDigit.h"

#include "inGame_digit.h"
#include "inGame_value.h"

using DIGIT = inGame_digit::CHAR;

enemyBase::enemyBase(patternMesh* duplicateTarget) :
	characterBase(duplicateTarget)
{

}

enemyBase::~enemyBase()
{
}

void enemyBase::update(void)
{
	characterBase::update();

	int status = _infoCharacter.status;
	if (gDigit::chk(status, DIGIT::APPROACH))
		updateApproach();
}

void enemyBase::updateApproach(void)
{
	// rotate2Pos();
}
