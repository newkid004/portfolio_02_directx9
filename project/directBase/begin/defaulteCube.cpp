#include "defaulteCube.h"
#include "gFunc.h"
#include "managerList.h"

defaulteCube::defaulteCube()
{
	_cube = createCube();
}


defaulteCube::~defaulteCube()
{
	SAFE_RELEASE(_cube);
}

void defaulteCube::drawPre(void)
{
	MN_DEV->SetRenderState(D3DRS_LIGHTING, false);
}

void defaulteCube::drawDo(void)
{
	MN_DEV->SetTransform(D3DTS_WORLD, &getMatrixFinal());
	_cube->DrawSubset(NULL);
}

void defaulteCube::drawPost(void)
{
	MN_DEV->SetRenderState(D3DRS_LIGHTING, true);
}

LPD3DXMESH defaulteCube::createCube(void)
{
	LPD3DXMESH result = nullptr;

	D3DXCreateBox(
		MN_DEV,
		1.0f, 1.0f, 1.0f,
		&result,
		NULL);

	return result;
}
