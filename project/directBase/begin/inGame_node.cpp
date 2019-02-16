#include "inGame_node.h"

#include "aStar_node.h"

inGame_node * inGame_node::getData(aStar_node * node)
{
	return (inGame_node*)node->getBindData();
}
