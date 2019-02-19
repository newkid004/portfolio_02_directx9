#include "characterBase.h"

#include "managerList.h"
#include "gFunc.h"
#include "gMng.h"
#include "gDigit.h"

#include "inGame_value.h"
#include "inGame_digit.h"
#include "inGame_node.h"
#include "inGame_grape.h"
#include "inGame_field.h"

#include "aStar_node.h"

#include "controllerBase.h"
#include "player.h"
#include "staticMesh.h"

#include "heap.h"

using DIGIT = inGame_digit;
using VALUE = inGame_value;

bool characterBase::heapCompare::operator()(aStar_node * n1, aStar_node * n2)
{
	auto & vBindList = SGT_GAME->getSet().field->getMember().grape->getBindList();
	inGame_node* infoA = vBindList[n1->getIndex()];
	inGame_node* infoB = vBindList[n1->getIndex()];

	D3DXVECTOR3 & playerPos = SGT_GAME->getSet().player->getPosition();
	D3DXVECTOR2 player2D = D3DXVECTOR2(playerPos.x, playerPos.z);

	float distanceA = gFunc::Vec2Distance(D3DXVECTOR2(infoA->getPosition().x, infoA->getPosition().z), player2D);
	float distanceB = gFunc::Vec2Distance(D3DXVECTOR2(infoB->getPosition().x, infoB->getPosition().z), player2D);

	return distanceA < distanceB;
}

characterBase::characterBase(patternMesh* duplicateTarget) :
	patternMeshDup(duplicateTarget)
{
}

characterBase::~characterBase()
{
	SAFE_DELETE(_controller);
}

void characterBase::update(void)
{
	patternMeshDup::update();

	_controller->update();

	updateLanding();
	updateMove();
	if (_weapon != nullptr)
	{
		_weapon->updateWeapon(_finalHandMatrix, _isCull);
	}
}

void characterBase::drawDo(void)
{
	patternMeshDup::drawDo();
	if (_weapon != nullptr)
	{
		_weapon->draw();
	}
}

void characterBase::updateLanding(void)
{
	if (0.0f < _infoMove.velVertical)
	{
		gDigit::pick(_infoMove.status, DIGIT::MOVE::LAND);
		gDigit::put(_infoMove.status, DIGIT::MOVE::FLOAT);
	}
	else if (_infoMove.velVertical < 0.0f)
	{
		float deltaHeight = _position.y + _infoMove.velVertical;

		if (deltaHeight < 0.0f)
		{
			gDigit::put(_infoMove.status, DIGIT::MOVE::LAND);
			gDigit::pick(_infoMove.status, DIGIT::MOVE::FLOAT);

			_position.y = 0.0f;
			_infoMove.velVertical = 0.0f;
		}
	}
}

void characterBase::updateMove(void)
{
	updateGravity();
	updateFriction();
	updateCollision();
	updateVelocity();
}

void characterBase::updateGravity(void)
{
	if (!gDigit::chk(_infoMove.status, DIGIT::MOVE::LAND))
		_infoMove.velVertical -= VALUE::gravity * MN_TIME->getDeltaTime();
}

void characterBase::updateFriction(void)
{
	// 부유 중
	if (!gDigit::chk(_infoMove.status, DIGIT::MOVE::LAND))
		return;

	// 마찰 적용
	float frictionValue = VALUE::friction * MN_TIME->getDeltaTime();
	_infoMove.currentSpeed = std::fmaxf(0.0f, _infoMove.currentSpeed - frictionValue);

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

void characterBase::updateCollision(void)
{
	// horizon
	vector<aStar_node*> vColNodeList;
	createCollisionNode(&vColNodeList);

	auto & vBindList = *SGT_GAME->getSet().field->getMember().grape;
	vector<staticMesh*> closeList(vColNodeList.size() * 2);
	for (auto i : vColNodeList)
	{
		auto & wallList = vBindList[i]->getListSet().wall;
		for (auto wall : wallList)
		{
			if (!gMng::find(wall, closeList))
			{
				moveByCollision(wall);
				closeList.push_back(wall);
			}
		}
	}
}

void characterBase::updateVelocity(void)
{
	_position.x += _infoMove.velHorizon.x;
	_position.y += _infoMove.velVertical;
	_position.z += _infoMove.velHorizon.y;
}

void characterBase::createCollisionNode(std::vector<aStar_node*>* out_list)
{
	D3DXVECTOR2 charPos(_position.x, _position.z);
	float charRange = _infoCharacter.colRadius;

	auto & vBindList = *SGT_GAME->getSet().field->getMember().grape;

	heap<aStar_node*, heapCompare> openList;
	vector<aStar_node*> closeList;

	openList.push(_placedNode);
	while (!openList.empty())
	{
		aStar_node* currentNode = openList.top();

		openList.pop();
		out_list->push_back(currentNode);
		closeList.push_back(currentNode);

		for (auto & i : currentNode->getLinkedNodeList())
		{
			auto linkedNode = i.connector;

			auto bindData = vBindList[linkedNode];
			D3DXVECTOR2 bindPosition(bindData->getPosition().x, bindData->getPosition().z);
			float distance = gFunc::Vec2Distance(bindPosition, charPos);
			if (charRange + bindData->getRadius() < distance)
				continue;

			if (gMng::find(linkedNode, closeList))
				continue;

			if (!gMng::find(linkedNode, openList.getContainer()))
				openList.push(linkedNode);
		}
	}
}

void characterBase::moveByCollision(staticMesh * wall)
{
	// player
	D3DXVECTOR2 & velocity = _infoMove.velHorizon;
	D3DXVECTOR2 planePos(_position.x, _position.z);
	D3DXVECTOR2 deltaPos(planePos.x + velocity.x, planePos.y + velocity.y);
	float radius = _infoCharacter.colRadius;

	// box
	boundingBox bBox = wall->getBoundingBoxList()[0];
	wall->getBoundingBoxFinal(&bBox);
	D3DXVECTOR2 bMin(bBox.min.x, bBox.min.z);
	D3DXVECTOR2 bMax(bBox.max.x, bBox.max.z);
	D3DXVECTOR2 bCenter = (bMin + bMax) / 2.0f;
	float bRadius = std::fminf(gFunc::Vec2Distance(bCenter, bMin), gFunc::Vec2Distance(bCenter, bMax));

	bMin.x -= radius;	bMax.x += radius;
	bMin.y -= radius;	bMax.y += radius;

	bool isCollision = false;

	//상하
	float interval[2];
	if (bMin.x < deltaPos.x && deltaPos.x < bMax.x)
	{
		interval[0] = (deltaPos.y - radius) - bMax.y;	// 상
		interval[1] = (deltaPos.y + radius) - bMin.y;	// 하

		if (bCenter.y < deltaPos.y && interval[0] < 0.0f)
		{
			deltaPos.y -= interval[0];
			isCollision = true;
		}

		else if (deltaPos.y < bCenter.y && 0.0f < interval[1])
		{
			deltaPos.y -= interval[1];
			isCollision = true;
		}
	}
	//좌우
	else if (bMin.y < deltaPos.y && deltaPos.y < bMax.y)
	{
		interval[0] = (deltaPos.x - radius) - bMax.x;	// 우
		interval[1] = (deltaPos.x + radius) - bMin.x;	// 좌

		if (bCenter.x < deltaPos.x && interval[0] < 0.0f)
		{
			deltaPos.x -= interval[0];
			isCollision = true;
		}

		else if (deltaPos.x < bCenter.x && 0.0f < interval[1])
		{
			deltaPos.x -= interval[1];
			isCollision = true;
		}
	}
	//꼭지점
	else
	{
		D3DXVECTOR2 edgePos;

		if (bCenter.y < deltaPos.y)		edgePos.y = bMax.y;		// 상
		else							edgePos.y = bMin.y;		// 하
		if (deltaPos.x < bCenter.x)		edgePos.x = bMin.x;		// 좌
		else							edgePos.x = bMax.x;		// 우
	
		interval[0] = gFunc::Vec2Distance(edgePos, deltaPos) - radius;
		if (interval[0] < 0.0f)
		{
			deltaPos -= gFunc::Vec2Dir(edgePos, deltaPos) * interval[0];
			isCollision = true;
		}
	}

	// 속도 재지정
	if (isCollision)
	{
		D3DXVECTOR2 direction(gFunc::Vec2Dir(planePos, deltaPos));
		_infoMove.currentSpeed = gFunc::Vec2Distance(planePos, deltaPos);

		velocity = direction * _infoMove.currentSpeed;
	}
}

void characterBase::moveDo(int direction)
{
	if (direction == 0) return;

	gDigit::put(_infoMove.status, DIGIT::MOVE::MOVEING);

	float nowSpeed = _infoMove.getSpeedXZ();

	D3DXVECTOR3 moveDirection(0.0f, 0.0f, 0.0f);
	if (gDigit::chk(direction, DIGIT::KEY::W))	moveDirection += _directionForward;
	if (gDigit::chk(direction, DIGIT::KEY::S))	moveDirection -= _directionForward;
	if (gDigit::chk(direction, DIGIT::KEY::A))	moveDirection -= _directionRight;
	if (gDigit::chk(direction, DIGIT::KEY::D))	moveDirection += _directionRight;

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

			moveDirection = currentVelocity + compareValue * interval * MN_TIME->getDeltaTime();
		}
		// 감속
		else if (VALUE::P2I <= std::fabsf(angle))
		{
			moveDirection += currentVelocity;
			_infoMove.currentSpeed = D3DXVec2Length(&D3DXVECTOR2(moveDirection.x, moveDirection.z)) * MN_TIME->getDeltaTime();
		}
	}
	// 일반
	else
	{
		_infoMove.currentSpeed = std::fminf(_infoMove.maximumSpeed, _infoMove.currentSpeed + _infoMove.accelSpeed * MN_TIME->getDeltaTime());
		moveDirection *= _infoMove.currentSpeed;
	}

	// 속력 적용
	_infoMove.velHorizon.x	= moveDirection.x;
	_infoMove.velHorizon.y	= moveDirection.z;
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

void characterBase::jump(void)
{
	if (gDigit::chk(_infoMove.status, DIGIT::MOVE::FLOAT))
		return;

	gDigit::put(_infoMove.status, DIGIT::MOVE::FLOAT);
	gDigit::pick(_infoMove.status, DIGIT::MOVE::LAND);

	_infoMove.velVertical = 1.0f;
}

void characterBase::setController(controllerBase * input)
{
	_controller = input;
	input->getBindCharacter() = this;
}
