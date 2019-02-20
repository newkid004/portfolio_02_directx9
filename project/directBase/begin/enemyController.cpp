#include "enemyController.h"

#include "managerList.h"
#include "gDigit.h"
#include "gFunc.h"

#include "inGame_digit.h"
#include "inGame_value.h"

#include "aStar_node.h"
#include "inGame_node.h"

#include "enemyBase.h"

enemyController::enemyController(characterBase * bindCharacter) :
	controllerBase(bindCharacter)
{
}

enemyController::~enemyController()
{
}

void enemyController::update(void)
{
}

void enemyController::update2bit(void)
{

}

void enemyController::updateFootPrint(void)
{
	auto & placedNode = _bindCharacter->getPlacedNode();
	auto beforeNode = placedNode;

	controllerBase::updateFootPrint();

	if (beforeNode != placedNode)
	{
		auto & nextPlacePos = static_cast<enemyBase*>(_bindCharacter)->refNextPlacePos();
		auto nodeData = inGame_node::getData(placedNode);
		nextPlacePos = nodeData->getPosition();

		float interval = nodeData->getRadius() * 0.875f;
		nextPlacePos.x += gFunc::rndFloat(-interval, interval);
		nextPlacePos.y += gFunc::rndFloat(-interval, interval);
	}
}
