#include "characterBase.h"

#include "managerList.h"
#include "gFunc.h"
#include "gDigit.h"

#include "inGame_value.h"
#include "inGame_digit.h"

#include "controllerBase.h"

using DIGIT = inGame_digit;
using VALUE = inGame_value;

characterBase::characterBase(const patternMesh::mParam & param) :
	patternMesh(param)
{
}

characterBase::~characterBase()
{
	SAFE_DELETE(_controller);
}

void characterBase::update(void)
{
	updateLanding();
	updateMove();

	_controller->update();
}

void characterBase::updateLanding(void)
{
	float postPos = _position.y + _infoMove.velVertical;

	if (0.0f <= postPos)
	{
		gDigit::put(_infoMove.status, DIGIT::MOVE::FLOAT);
		gDigit::pick(_infoMove.status, DIGIT::MOVE::LAND);
		return;
	}

	_infoMove.velVertical = -_position.y;
	gDigit::put(_infoMove.status, DIGIT::MOVE::LAND);
}

void characterBase::updateMove(void)
{
	updateGravity();
	updateVelocity();
	updateFriction();
}

void characterBase::updateGravity(void)
{
	if (!gDigit::chk(_infoMove.status, DIGIT::MOVE::LAND))
		_infoMove.velVertical += VALUE::gravity * MN_TIME->getDeltaTime();
}

void characterBase::updateFriction(void)
{
	// ���� ��
	if (!gDigit::chk(_infoMove.status, DIGIT::MOVE::LAND))
		return;

	// ���� ����
	float frictionValue = VALUE::friction * MN_TIME->getDeltaTime();
	_infoMove.currentSpeed = std::fmaxf(0.0f, (_infoMove.currentSpeed - frictionValue) * (1.0f - frictionValue));

	// ���� Ȯ��
	if (_infoMove.currentSpeed <= FLT_EPSILON)
	{
		_infoMove.currentSpeed = 0.0f;
		gDigit::pick(_infoMove.status, DIGIT::MOVE::MOVEING);

		ZeroMemory(&_infoMove.velHorizon, sizeof(D3DXVECTOR2));
	}
	// �ӵ� ����
	else
	{
		D3DXVec2Normalize(&_infoMove.velHorizon, &_infoMove.velHorizon);
		_infoMove.velHorizon *= _infoMove.currentSpeed;
	}
}

void characterBase::updateVelocity(void)
{
	// ***** ��ӵ� �ڽ�, AI���� �� �浹 �ʿ� ***** //

	_position.x += _infoMove.velHorizon.x;
	_position.y += _infoMove.velVertical;
	_position.z += _infoMove.velHorizon.y;
}

void characterBase::moveDo(D3DXVECTOR3 & direction)
{
	gDigit::put(_infoMove.status, DIGIT::MOVE::MOVEING);
	if (direction.y < 0.0f)
	{
		gDigit::put(_infoMove.status, DIGIT::MOVE::FLOAT);
		gDigit::pick(_infoMove.status, DIGIT::MOVE::LAND);
	}

	float nowSpeed = _infoMove.getSpeedXZ();

	D3DXVECTOR3 moveDirection;
	moveDirection += _directionRight	* direction.x;
	moveDirection += _directionUp		* direction.y;
	moveDirection += _directionForward	* direction.z;
	D3DXVec3Normalize(&moveDirection, &moveDirection);

	// �ִ�ӵ� �ѱ�
	if (_infoMove.maximumSpeed < nowSpeed)
	{
		moveDirection *= _infoMove.maximumSpeed;

		D3DXVECTOR3 currentVelocity = _infoMove.getVelocityXYZ();
		float angle = gFunc::getAngle(currentVelocity, moveDirection);

		// ���õǴ� ���� ����
		if (std::fabsf(angle) < VALUE::P2I)
		{
			D3DXVECTOR3 compareValue;
			D3DXVec3Cross(&compareValue, &WORLD_DIRECTION_UP, &currentVelocity);
			D3DXVec3Normalize(&compareValue, &compareValue);
			
			float interval = D3DXVec3Dot(&compareValue, &moveDirection);

			if (angle < 0.0f)
				compareValue = -compareValue;

			moveDirection = currentVelocity + compareValue * interval;
		}
		// ����
		else if (VALUE::P2I <= std::fabsf(angle))
		{
			moveDirection += currentVelocity;
			_infoMove.currentSpeed = D3DXVec2Length(&D3DXVECTOR2(moveDirection.x, moveDirection.z));
		}
	}
	// �Ϲ�
	else
	{
		_infoMove.currentSpeed = std::fminf(_infoMove.maximumSpeed, _infoMove.currentSpeed + _infoMove.accelSpeed * MN_TIME->getDeltaTime());
		moveDirection *= _infoMove.currentSpeed;
	}

	// �ӷ� ����
	_infoMove.velHorizon.x	= moveDirection.x * MN_TIME->getDeltaTime();
	_infoMove.velVertical	= moveDirection.y * MN_TIME->getDeltaTime();
	_infoMove.velHorizon.y	= moveDirection.z * MN_TIME->getDeltaTime();
}

void characterBase::moveBe(D3DXVECTOR3 & direction)
{
	gDigit::put(_infoMove.status, DIGIT::MOVE::MOVEING);
	if (direction.y < 0.0f)
	{
		gDigit::put(_infoMove.status, DIGIT::MOVE::FLOAT);
		gDigit::pick(_infoMove.status, DIGIT::MOVE::LAND);
	}

	// delta time ������
	_infoMove.velHorizon.x	+= direction.x;
	_infoMove.velVertical	+= direction.y;
	_infoMove.velHorizon.y	+= direction.z;
}

void characterBase::setController(controllerBase * input)
{
	_controller = input;
}
