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

	// _controller->update();

	updateLanding();
	updateMove();
}

void characterBase::updateLanding(void)
{
	float postPos = _position.y + _infoMove.velVertical;

	if (FLT_EPSILON < postPos)
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
	updateFriction();
	updateVelocity();
	// updateCollision();
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

void characterBase::updateCollision(void)
{
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
				moveByCollistion(wall);
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
	float charRange = _infoCharacter.colRadian;

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

void characterBase::moveByCollistion(staticMesh * wall)
{
	// box
	boundingBox & bBox = wall->getBoundingBox();
	D3DXVECTOR2 bMin(bBox.min.x, bBox.min.z);
	D3DXVECTOR2 bMax(bBox.max.x, bBox.max.z);
	D3DXVECTOR2 bCenter = (bMin + bMax) / 2.0f;
	float bRadius = gFunc::Vec2Distance(bCenter, bMax);

	// player
	D3DXVECTOR2 & velocity = _infoMove.velHorizon;
	D3DXVECTOR2 planePos(_position.x, _position.z);
	D3DXVECTOR2 deltaPos(planePos.x + velocity.x, planePos.y + velocity.y);
	float radius = _infoCharacter.colRadian;

	// compare
	float distance = gFunc::Vec2Distance(bCenter, deltaPos) - bRadius - radius;

	// �浹���� ��
	if (0.0f < distance)
		return;

	//����
	if (bMin.x <= deltaPos.x && deltaPos.x <= bMax.x)
	{
		//��
		if (bCenter.y < deltaPos.y)
			deltaPos.y -= bMax.y - (deltaPos.y + radius);

		//��
		else
			deltaPos.y += bMin.y - (deltaPos.y - radius);
	}
	//�¿�
	else if (bMin.y <= deltaPos.y && deltaPos.y <= bMax.y)
	{
		//��
		if (bCenter.x < deltaPos.x)
			deltaPos.x -= bMax.x - (deltaPos.x + radius);

		//��
		else
			deltaPos.x += bMin.x - (deltaPos.x - radius);
	}
	//������
	else
	{
		D3DXVECTOR2 edgePos;

		// ��
		if (deltaPos.x < bCenter.x)
		{
			edgePos.x = bMin.x;

			// ��
			if (bCenter.y < deltaPos.y)
				edgePos.y = bMax.y;

			// ��
			else
				edgePos.y = bMin.y;
		}
		// ��
		else
		{
			edgePos.x = bMax.x;

			// ��
			if (bCenter.y < deltaPos.y)
				edgePos.y = bMax.y;

			// ��
			else
				edgePos.y = bMin.y;
		}

		deltaPos = gFunc::Vec2Dir(edgePos, deltaPos) * radius;
	}

	// �ӵ� ������
	D3DXVECTOR2 direction(gFunc::Vec2Dir(planePos, deltaPos));
	_infoMove.currentSpeed = gFunc::Vec2Distance(direction, deltaPos);

	velocity = direction * _infoMove.currentSpeed;
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
	input->getBindCharacter() = this;
}