#pragma once
#include "kGlobalDefine.h"
#include "staticMesh.h"

class triggerMesh : public staticMesh
{
protected :
	int _triggerType = 0;

public :
	int & refTriggerType(void) { return _triggerType; }

public:
	triggerMesh(const staticMesh::mParam & param) : staticMesh(param) {};
	~triggerMesh() {};
};

