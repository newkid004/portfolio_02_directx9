#include "playerController.h"

playerController::playerController(characterBase * bindCharacter) :
	controllerBase(bindCharacter)
{
}

playerController::~playerController()
{
}

void playerController::update(void)
{
	controllerBase::update();

	updateControl();
}

void playerController::updateControl(void)
{
}
