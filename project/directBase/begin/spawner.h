#pragma once
#include "kGlobalDefine.h"
#include "nodeMesh.h"

class spawner : public nodeMesh
{
public :
	void drawDo(void) override;

public:
	spawner(const staticMesh::mParam & param);
	~spawner();
};

