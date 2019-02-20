#pragma once
#include "kGlobalDefine.h"
#include "staticMesh.h"

class triggerMesh : public staticMesh
{
public:
	triggerMesh(const staticMesh::mParam & param) : staticMesh(param) {};
	~triggerMesh() {};
};

