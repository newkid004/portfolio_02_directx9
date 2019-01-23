#pragma once
#include "kGlobalDefine.h"
#include "renderObject.h"

class defaulteCube : public renderObject
{
private :
	LPD3DXMESH _cube = nullptr;

protected :
	void drawPre(void) override;
	void drawDo(void) override;
	void drawPost(void) override;

private :
	LPD3DXMESH createCube(void);

public:
	defaulteCube();
	~defaulteCube();
};

