#include "camera.h"
#include "managerList.h"

camera::camera(float aspect, float fov, float maxDistance)
{
	D3DXMatrixIdentity(&_mView);
	D3DXMatrixIdentity(&_mProjection);

	setAspect(aspect, fov, maxDistance);
}

void camera::update(void)
{
	baseObject::update();
	updateCamera();

	MN_DEV->SetTransform(D3DTS_VIEW, &_mView);
}
void camera::update(const D3DXVECTOR3 & targetDirection)
{
	_directionForward = targetDirection;
	update();
}
void camera::update(baseObject* targetObject)
{
	_directionForward	= targetObject->getDirectForward();
	_directionRight		= targetObject->getDirectRight();
	_directionUp		= targetObject->getDirectUp();

	update();
}

void camera::updateCamera(void)
{
	updateAxis();		// 축 정렬
	updateRotate();		// 회전 정렬
	updateTranslate();	// 이동 정렬
}

void camera::updateAxis(void)
{
	// 0 - 0. y축 상단으로 고정
	if (_state & STATE_SWITCH::HORIZONTAL)
		_directionUp = WORLD_DIRECTION_UP;

	D3DXVec3Normalize(&_directionForward, &_directionForward);

	D3DXVec3Cross(&_directionRight, &_directionUp, &_directionForward);
	D3DXVec3Normalize(&_directionRight, &_directionRight);

	D3DXVec3Cross(&_directionUp, &_directionForward, &_directionRight);
	D3DXVec3Normalize(&_directionUp, &_directionUp);
}

void camera::updateRotate(void)
{
	_mView(0, 0) = _directionRight.x;
	_mView(1, 0) = _directionRight.y;
	_mView(2, 0) = _directionRight.z;

	_mView(0, 1) = _directionUp.x;
	_mView(1, 1) = _directionUp.y;
	_mView(2, 1) = _directionUp.z;

	_mView(0, 2) = _directionForward.x;
	_mView(1, 2) = _directionForward.y;
	_mView(2, 2) = _directionForward.z;
}

void camera::updateTranslate(void)
{
	_mView(3, 0) = -D3DXVec3Dot(&_directionRight,	&_position) + _mOffset(3, 0);
	_mView(3, 1) = -D3DXVec3Dot(&_directionUp,		&_position) + _mOffset(3, 1);
	_mView(3, 2) = -D3DXVec3Dot(&_directionForward,	&_position) + _mOffset(3, 2);
}

void camera::setAspect(float aspect, float fov, float maxDistance)
{
	D3DXMatrixPerspectiveFovLH(
		&_mProjection,
		D3DXToRadian(fov),
		aspect,
		0.1f,
		maxDistance);

	// 투영 행렬을 설정한다
	MN_DEV->SetTransform(D3DTS_PROJECTION, &_mProjection);
}
