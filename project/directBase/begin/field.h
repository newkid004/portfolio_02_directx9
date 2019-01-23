#pragma once
#include "kGlobalDefine.h"
#include "renderObject.h"

#include "pickRay.h"

class terrain;

class field : public renderObject
{
private :
	terrain* _bindTerrain = nullptr;

public :
	bool getPickInfo(pick::info * out_info);

public :
	terrain* getTerrain(void) { return _bindTerrain; }

public:
	field(terrain* fieldTerrain);
	~field();
};

