#pragma once
#include "kGlobalDefine.h"
#include "survivorBase.h"

class player : public survivorBase
{
public:
	player(patternMesh* duplicateTarget);
	~player();
};

