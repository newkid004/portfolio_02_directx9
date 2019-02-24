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
	if (!gDigit::chk(_bindCharacter->getInfoCharacter().status, DIGIT::CHAR::DEAD))
	{
		updatePlace();
		updateControl();
	}
	updateAnimation();
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

void playerController::updateAnimation(void)
{
	int status = _bindCharacter->getInfoMove().status;
	if (gDigit::chk(_bindCharacter->getInfoCharacter().status, DIGIT::CHAR::DEAD))
	{
		CHANGE_BIT(_bindCharacter->getNextBit(), aniDefine::ANIBIT::MAIN, AMAIN_TRIP);
		CHANGE_BIT(_bindCharacter->getNextBit(), aniDefine::ANIBIT::SUB, ATRIP_BACKWARD);
		if ((_bindCharacter->getAControllInfo().CurrentMotionBit & GET_ANIBITMASK(aniDefine::ANIBIT::MAIN)) == AMAIN_TRIP)
		{
			if (_bindCharacter->getAControllInfo().persent >= 0.8f)
			{
				MN_SND->getBGM()->stop();
				MN_SND->find("deathB")->play();
				MN_SCENE->change("deadScene");
			}
		}
		return;
	}

	if (gDigit::chk(status, DIGIT::MOVE::FLOAT))
	{
		CHANGE_BIT(_bindCharacter->getNextBit(), aniDefine::ANIBIT::MAIN, AMAIN_JUMP);
		CHANGE_BIT(_bindCharacter->getNextBit(), aniDefine::ANIBIT::SUB, AJUMP_JUMP);
		return;
	}
	else if (gDigit::chk(status, DIGIT::MOVE::MOVEING))
	{
		CHANGE_BIT(_bindCharacter->getNextBit(), aniDefine::ANIBIT::MAIN, AMAIN_RUN);
		CHANGE_BIT(_bindCharacter->getNextBit(), aniDefine::ANIBIT::SUB, ARUN_STANDING);
	}
	else
	{
		int index = _bindCharacter->getNextBit();
		CHANGE_BIT(_bindCharacter->getNextBit(), aniDefine::ANIBIT::MAIN, AMAIN_IDLE);
		CHANGE_BIT(_bindCharacter->getNextBit(), aniDefine::ANIBIT::SUB, AIDLE_STANDING);
	}

	int index = _bindCharacter->getNextBit();
	if (_bindCharacter->getInfoCharacter().maxHp > _bindCharacter->getInfoCharacter().nowHp)
	{
		CHANGE_BIT(_bindCharacter->getNextBit(), aniDefine::ANIBIT::CONDITION, ACONDITION_INJURED);
	}
	else CHANGE_BIT(_bindCharacter->getNextBit(), aniDefine::ANIBIT::CONDITION, ACONDITION_NORMAL);

}
