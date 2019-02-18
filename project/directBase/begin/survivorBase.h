#pragma once
#include "kGlobalDefine.h"
#include "characterBase.h"

class survivorBase : public characterBase
{
public:
	survivorBase(patternMesh* duplicateTarget);
	~survivorBase();
};

