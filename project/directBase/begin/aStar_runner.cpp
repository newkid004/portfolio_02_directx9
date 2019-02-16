#include "aStar_runner.h"
#include "aStar_grape.h"
#include "aStar_node.h"

bool aStar_runner::comparer::operator()(aStar_runner* & p1, aStar_runner* & p2)
{
	return	p1->_member.distance.F < p2->_member.distance.F;
}

void aStar_runner::setPrevRunner(aStar_runner * prevRunner)
{
	_member.prevRunner = prevRunner;
	_member.prevNode = prevRunner->getMember().placedNode;

	_member.prevRunner->_member.nextRunner = this;
	_member.prevRunner->_member.nextNode = _member.placedNode;

	aStar_node* dest = ((aStar_grape*)_member.prevNode->getBindGrape())->getDestNode();

	_member.distance.G = aStar_grape::calDistance(_member.prevNode, _member.placedNode) + _member.prevRunner->_member.distance.G;
	_member.distance.H = aStar_grape::calDistance(_member.placedNode, dest);
	_member.distance.F = _member.distance.G + _member.distance.H;
}

// start
aStar_runner::aStar_runner(aStar_node * startNode)
{
	_member.placedNode = startNode;
}

// run
aStar_runner::aStar_runner(aStar_runner* prevRunner, aStar_node * placedNode)
{
	_member.placedNode = placedNode;
	setPrevRunner(prevRunner);
}

// duplicate
aStar_runner::aStar_runner(member & member) :
	_member(member)
{
}