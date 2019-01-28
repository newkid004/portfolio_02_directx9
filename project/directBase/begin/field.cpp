#include "field.h"

#include "managerList.h"

#include "terrain.h"

field::field(terrain* fieldTerrain) :
	_bindTerrain(fieldTerrain)
{
	if (fieldTerrain)
		this->addChild(fieldTerrain);
}

field::~field()
{
}

bool field::getPickInfo(pick::info * out_info)
{
	return pick::chkPick(out_info, &MN_KEY->getPickRay(), _bindTerrain->getMesh());
}