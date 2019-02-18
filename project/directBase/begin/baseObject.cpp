#include "baseObject.h"

#include "direct3dApplication.h"
#include "camera.h"

#include "sceneManager.h"
#include "sceneBase.h"

void baseObject::putOffsetPosition(void)
{
	D3DXMATRIXA16 mRotation = getMatrixRotate();
	D3DXVECTOR3 offset = getOffset();
	D3DXVec3TransformCoord(&offset, &offset, &mRotation);

	_offsetPosition = _position - offset;
}

baseObject::baseObject() :
	_position(0.0f, 0.0f, 0.0f),
	_scale(1.0f, 1.0f, 1.0f),
	_parent(NULL),
	_directionRight(WORLD_DIRECTION_RIGHT),
	_directionUp(WORLD_DIRECTION_UP),
	_directionForward(WORLD_DIRECTION_FORWARD)
{
	D3DXMatrixIdentity(&_mWorld);
	D3DXMatrixIdentity(&_mOffset);
}

baseObject::~baseObject()
{
	for (auto child : _vChildren) 
		SAFE_DELETE(child);
}

void baseObject::update(void)
{
	calMatrixFinal();

	// 자식 갱신
	for (auto childObject : _vChildren)
		childObject->update();
}

void baseObject::addChild(baseObject * input)
{
	auto iter = std::find(_vChildren.begin(), _vChildren.end(), input);
	if (iter == _vChildren.end())
	{
		input->setParent(this);
		_vChildren.push_back(input);
	}
}

void baseObject::removeChild(baseObject * input)
{
	auto iter = std::find(_vChildren.begin(), _vChildren.end(), input);
	if (iter != _vChildren.end())
	{
		input->setParent(NULL);
		_vChildren.erase(iter);
	}
}

void baseObject::moveX(float distance, bool isLocal)
{
	if (isLocal)	
		_position += _directionRight * distance;
	else
		_position += D3DXVECTOR3(_directionRight.x, 0.0f, _directionRight.z) * distance;
}

void baseObject::moveY(float distance, bool isLocal)
{
	if (isLocal)	
		_position += _directionUp * distance;
	else			
		_position.y	+= distance;
}

void baseObject::moveZ(float distance, bool isLocal)
{
	if (isLocal)	
		_position += _directionForward * distance;
	else
	{
		D3DXVECTOR3 dir;
		D3DXVec3Cross(&dir, &_directionRight, &WORLD_DIRECTION_UP); 
		dir.y = 0;
		_position += dir * distance;
	}
}

void baseObject::moveCameraX(float distance, bool isFixAxisY)
{
	D3DXVECTOR3 direction = GET_CAMERA()->getDirectRight();
	if (isFixAxisY) 
		direction.y = 0;

	_position += direction * distance;
}

void baseObject::moveCameraY(float distance)
{
	_position += GET_CAMERA()->getDirectUp() * distance;
}

void baseObject::moveCameraZ(float distance, bool isFixAxisY)
{
	D3DXVECTOR3 direction = GET_CAMERA()->getDirectForward();
	if (isFixAxisY)
		direction.y = 0;

	_position += direction * distance;
}

void baseObject::rotateX(float angle, bool isLocal)
{
	// x축 기준 회전 행렬 설정
	D3DXMATRIXA16 mRotation;
	if (isLocal)
		D3DXMatrixRotationAxis(&mRotation, &_directionRight, D3DXToRadian(angle));
	else
	{
		D3DXMatrixRotationX(&mRotation, D3DXToRadian(angle));
		D3DXVec3TransformNormal(&_directionRight, &_directionRight, &mRotation);
	}

	// x축을 제외한 나머지 기저 벡터 회전
	D3DXVec3TransformNormal(&_directionUp,		&_directionUp,		&mRotation);
	D3DXVec3TransformNormal(&_directionForward,	&_directionForward,	&mRotation);

	normalizeAxis();
}

void baseObject::rotateY(float angle, bool isLocal)
{
	// y축 기준 회전 행렬 설정
	D3DXMATRIXA16 mRotation;
	if (isLocal)
		D3DXMatrixRotationAxis(&mRotation, &_directionUp, D3DXToRadian(angle));
	else
	{
		D3DXMatrixRotationY(&mRotation, D3DXToRadian(angle));
		D3DXVec3TransformNormal(&_directionUp, &_directionUp, &mRotation);
	}

	// y축을 제외한 나머지 기저 벡터 회전
	D3DXVec3TransformNormal(&_directionRight,	&_directionRight,	&mRotation);
	D3DXVec3TransformNormal(&_directionForward,	&_directionForward,	&mRotation);

	normalizeAxis();
}

void baseObject::rotateZ(float angle, bool isLocal)
{
	// z축 기준 회전 행렬 설정
	D3DXMATRIXA16 mRotation;
	if (isLocal)
		D3DXMatrixRotationAxis(&mRotation, &_directionForward, D3DXToRadian(angle));
	else
	{
		D3DXMatrixRotationZ(&mRotation, D3DXToRadian(angle));
		D3DXVec3TransformNormal(&_directionForward, &_directionForward, &mRotation);
	}

	// z축을 제외한 나머지 기저 벡터 회전
	D3DXVec3TransformNormal(&_directionRight,	&_directionRight,	&mRotation);
	D3DXVec3TransformNormal(&_directionUp,		&_directionUp,		&mRotation);

	normalizeAxis();
}

void baseObject::rotateCameraX(float angle)
{
	// 카메라 y축 기준 회전 행렬 설정
	D3DXMATRIXA16 mRotation;
	D3DXMatrixRotationAxis(&mRotation, &GET_CAMERA()->getDirectRight(), D3DXToRadian(angle));

	// 기저 벡터 회전
	D3DXVec3TransformNormal(&_directionForward, &_directionForward, &mRotation);
	D3DXVec3TransformNormal(&_directionRight, &_directionRight, &mRotation);
	D3DXVec3TransformNormal(&_directionUp, &_directionUp, &mRotation);

	normalizeAxis();
}

void baseObject::rotateCameraY(float angle)
{
	// 카메라 y축 기준 회전 행렬 설정
	D3DXMATRIXA16 mRotation;
	D3DXMatrixRotationAxis(&mRotation, &GET_CAMERA()->getDirectUp(), D3DXToRadian(angle));

	// 기저 벡터 회전
	D3DXVec3TransformNormal(&_directionForward, &_directionForward, &mRotation);
	D3DXVec3TransformNormal(&_directionRight, &_directionRight, &mRotation);
	D3DXVec3TransformNormal(&_directionUp, &_directionUp, &mRotation);

	normalizeAxis();
}

void baseObject::rotateCameraZ(float angle)
{
	// 카메라 z축 기준 회전 행렬 설정
	D3DXMATRIXA16 mRotation;
	D3DXMatrixRotationAxis(&mRotation, &GET_CAMERA()->getDirectForward(), D3DXToRadian(angle));

	// 기저 벡터 회전
	D3DXVec3TransformNormal(&_directionForward, &_directionForward, &mRotation);
	D3DXVec3TransformNormal(&_directionRight, &_directionRight, &mRotation);
	D3DXVec3TransformNormal(&_directionUp, &_directionUp, &mRotation);

	normalizeAxis();
}

void baseObject::rotate2Pos(const D3DXVECTOR3 & pos, bool isSphere, bool isFixAxisX)
{
	D3DXVECTOR3 dir = pos - _position;
	D3DXVec3Normalize(&dir, &dir);

	rotate2Dir(dir, isSphere, isFixAxisX);
}

void baseObject::rotate2Dir(const D3DXVECTOR3 & dir, bool isSphere, bool isFixAxisX)
{
	_directionForward = dir;
	if (!isSphere) 
		_directionForward.y = 0;

	// 새로운 축 정보 계산
	_directionUp = WORLD_DIRECTION_UP;
	D3DXVec3Cross(&_directionRight,		&_directionUp,		&_directionForward);
	
	if (!isFixAxisX)
		D3DXVec3Cross(&_directionUp,	&_directionForward,	&_directionRight);

	D3DXVec3Cross(&_directionForward,	&_directionRight,	&_directionUp);

	normalizeAxis();
}

void baseObject::rotate2Mat(const D3DXMATRIXA16 & mat)
{
	D3DXVec3TransformNormal(&_directionRight,	&_directionRight,	&mat);
	D3DXVec3TransformNormal(&_directionUp,		&_directionUp,		&mat);
	D3DXVec3TransformNormal(&_directionForward,	&_directionForward,	&mat);

	normalizeAxis();
}

void baseObject::rotateBillboard(bool isFixAxisX, bool isFront)
{
	_directionForward = -GET_CAMERA()->getDirectForward();
	if (isFront) _directionForward = -_directionForward;

	_directionUp = WORLD_DIRECTION_UP;

	D3DXVec3Cross(&_directionRight, &_directionUp, &_directionForward);

	if (!isFixAxisX)
		D3DXVec3Cross(&_directionUp, &_directionRight, &_directionForward);

	D3DXVec3Cross(&_directionForward, &_directionRight, &_directionUp);

	normalizeAxis();
}

void baseObject::normalizeAxis(void)
{
	D3DXVec3Normalize(&_directionRight,		&_directionRight);
	D3DXVec3Normalize(&_directionUp,		&_directionUp);
	D3DXVec3Normalize(&_directionForward,	&_directionForward);
}

void baseObject::calMatrixFinal(void)
{
	// 이동
	D3DXMATRIXA16 mTranslation;
	D3DXMatrixTranslation(&mTranslation,
		_position.x,
		_position.y,
		_position.z);

	// 척도
	D3DXMATRIXA16 mScalse;
	D3DXMatrixScaling(&mScalse,
		_scale.x,
		_scale.y,
		_scale.z);

	// 회전
	D3DXMATRIXA16 mRotation;
	D3DXMatrixIdentity(&mRotation);

	CopyMemory(&mRotation(0, 0), &_directionRight, sizeof(D3DXVECTOR3));
	CopyMemory(&mRotation(1, 0), &_directionUp, sizeof(D3DXVECTOR3));
	CopyMemory(&mRotation(2, 0), &_directionForward, sizeof(D3DXVECTOR3));

	// world
	_mWorld = _mOffset * mScalse * mRotation * mTranslation;
}

D3DXMATRIXA16 baseObject::getMatrixFinal(void)
{
	if (_parent == NULL)
		return _mWorld;

	return _mWorld * _parent->getMatrixFinal();
}

D3DXMATRIXA16 baseObject::getMatrixRotate(void)
{
	D3DXMATRIXA16 mRotation;
	D3DXMatrixIdentity(&mRotation);

	CopyMemory(&mRotation(0, 0), &_directionRight, sizeof(D3DXVECTOR3));
	CopyMemory(&mRotation(1, 0), &_directionUp, sizeof(D3DXVECTOR3));
	CopyMemory(&mRotation(2, 0), &_directionForward, sizeof(D3DXVECTOR3));

	return mRotation;
}

void baseObject::setRotation(const D3DXVECTOR3 & input)
{
	D3DXMATRIXA16 mRotation;
	D3DXMatrixRotationYawPitchRoll(&mRotation,
		D3DXToRadian(input.y),
		D3DXToRadian(input.x),
		D3DXToRadian(input.z));

	// 회전 행렬로부터 기저 벡터에 해당하는 성분 추출
	CopyMemory(&_directionRight,	&mRotation(0, 0), sizeof(D3DXVECTOR3));
	CopyMemory(&_directionUp,		&mRotation(1, 0), sizeof(D3DXVECTOR3));
	CopyMemory(&_directionForward,	&mRotation(2, 0), sizeof(D3DXVECTOR3));
}

void baseObject::setParent(baseObject* input)
{
	assert(_parent == NULL);
	_parent = input;
}