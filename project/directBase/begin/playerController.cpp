#include "playerController.h"

#include "managerList.h"
#include "gDigit.h"

#include "inGame_digit.h"

#include "characterBase.h"


using DIGIT = inGame_digit;

playerController::playerController(characterBase * bindCharacter) :
	controllerBase(bindCharacter)
{
}

playerController::~playerController()
{
}

void playerController::update(void)
{
	updatePlace();
	updateControl();
}

void playerController::updateControl(void)
{
	int dirMove = 0;

	if (MN_KEY->keyDown(DIK_W))		gDigit::put(dirMove, DIGIT::KEY::W);
	if (MN_KEY->keyDown(DIK_S))		gDigit::put(dirMove, DIGIT::KEY::S);
	if (MN_KEY->keyDown(DIK_A))		gDigit::put(dirMove, DIGIT::KEY::A);
	if (MN_KEY->keyDown(DIK_D))		gDigit::put(dirMove, DIGIT::KEY::D);
	if (MN_KEY->keyPress(DIK_SPACE)) _bindCharacter->jump();

	if (_bindCharacter->getWeapon())
	{
		int & weaponStatus = _bindCharacter->getWeapon()->getInfoWeapon().status;
		if (MN_KEY->mouseDown())		gDigit::put(weaponStatus, DIGIT::WEAPON::DO_FIRE);
		else							gDigit::pick(weaponStatus, DIGIT::WEAPON::DO_FIRE);
	}

	_bindCharacter->moveDo(dirMove);
}
