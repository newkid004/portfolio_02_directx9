#include "inGame_node.h"

#include "aStar_node.h"

void inGame_node::setBindNode(aStar_node* input)
{
	_bindNode = input;
	input->getBindData() = this;
}

inGame_node * inGame_node::getData(aStar_node * node)
{
	return (inGame_node*)node->getBindData();
}
