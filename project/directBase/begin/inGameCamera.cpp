#include "inGameCamera.h"

#include "managerList.h"

#include "characterBase.h"

inGameCamera::inGameCamera(characterBase * bindCharacter) : 
	camera(MN_WIN->getAspect()),
	_bindCharacter(bindCharacter)
{
	_posCenter = POINT{ WINSIZEX / 2.0f , WINSIZEY / 2.0f };

	MN_KEY->setMousePos(_posCenter);
}

inGameCamera::~inGameCamera()
{
}

void inGameCamera::update(void)
{
	updateBind();
	updateControl();

	camera::update();
}

void inGameCamera::updateBind(void)
{
	if (_bindCharacter == nullptr) return;

	_position = _bindCharacter->getPosition();

	D3DXVECTOR3 lookForward(_directionForward.x, 0.0f, _directionForward.z);
	D3DXVECTOR3 lookRight(_directionRight.x, 0.0f, _directionRight.z);

	D3DXVec3Normalize(&_bindCharacter->getDirectForward(), &lookForward);
	D3DXVec3Normalize(&_bindCharacter->getDirectRight(), &lookRight);
	_bindCharacter->getDirectUp() = WORLD_DIRECTION_UP;
}

void inGameCamera::updateControl(void)
{
	POINT mousePos = MN_KEY->getMousePos();

	POINT mouseMove = {
		mousePos.x - _posCenter.x,
		mousePos.y - _posCenter.y };

	rotateX(mouseMove.y / 8.0f);
	rotateY(mouseMove.x / 8.0f, false);

	MN_KEY->setMousePos(_posCenter);
}
