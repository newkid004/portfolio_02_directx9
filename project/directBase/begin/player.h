#pragma once
#include "kGlobalDefine.h"
#include "survivorBase.h"

class player : public survivorBase
{
protected :
	bool _isFixCamera = false;

public :
	bool & refIsFixCamera(void) { return _isFixCamera; }

public:
	player(patternMesh* duplicateTarget);
	~player();
};

