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
	// 부유 중
	if (!gDigit::chk(_infoMove.status, DIGIT::MOVE::LAND))
		return;

	// 마찰 적용
	float frictionValue = VALUE::friction * MN_TIME->getDeltaTime();
	_infoMove.currentSpeed = std::fmaxf(0.0f, (_infoMove.currentSpeed - frictionValue) * (1.0f - frictionValue));

	// 정지 확인
	if (_infoMove.currentSpeed <= FLT_EPSILON)
	{
		_infoMove.currentSpeed = 0.0f;
		gDigit::pick(_infoMove.status, DIGIT::MOVE::MOVEING);

		ZeroMemory(&_infoMove.velHorizon, sizeof(D3DXVECTOR2));
	}
	// 속도 적용
	else
	{
		D3DXVec2Normalize(&_infoMove.velHorizon, &_infoMove.velHorizon);
		_infoMove.velHorizon *= _infoMove.currentSpeed;
	}
}

void characterBase::updateVelocity(void)
{
	// ***** 상속된 자식, AI에서 벽 충돌 필요 ***** //

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

	// 최대속도 넘김
	if (_infoMove.maximumSpeed < nowSpeed)
	{
		moveDirection *= _infoMove.maximumSpeed;

		D3DXVECTOR3 currentVelocity = _infoMove.getVelocityXYZ();
		float angle = gFunc::getAngle(currentVelocity, moveDirection);

		// 무시되는 방향 제외
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
		// 감속
		else if (VALUE::P2I <= std::fabsf(angle))
		{
			moveDirection += currentVelocity;
			_infoMove.currentSpeed = D3DXVec2Length(&D3DXVECTOR2(moveDirection.x, moveDirection.z));
		}
	}
	// 일반
	else
	{
		_infoMove.currentSpeed = std::fminf(_infoMove.maximumSpeed, _infoMove.currentSpeed + _infoMove.accelSpeed * MN_TIME->getDeltaTime());
		moveDirection *= _infoMove.currentSpeed;
	}

	// 속력 적용
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

	// delta time 미적용
	_infoMove.velHorizon.x	+= direction.x;
	_infoMove.velVertical	+= direction.y;
	_infoMove.velHorizon.y	+= direction.z;
}

void characterBase::setController(controllerBase * input)
{
	_controller = input;
}
