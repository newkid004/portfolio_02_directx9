#include "aStar_runner.h"

#include "aStar_grape.h"
#include "aStar_node.h"

bool aStar_runner::comparer::operator()(aStar_runner & p1, aStar_runner & p2)
{
	aStar_node* nodeCur = ((aStar_grape*)p1.getMember().placedNode->getBindGrape())->getCurrentNode();

	aStar_runner::info_distance distA, distB;
	nodeCur->calcDistance(&distA, p1.getMember().placedNode);
	nodeCur->calcDistance(&distB, p2.getMember().placedNode);

	return	distA.F < distB.F;
}

aStar_runner::aStar_runner(aStar_runner & prevRunner, aStar_node * placedNode)
{
	_member.prevRunner = &prevRunner;

	_member.placedNode = placedNode;
	_member.prevNode = _member.prevRunner->getMember().placedNode;

	_member.prevNode->calcDistance(&_member.distance, _member.placedNode);
}
