#include "customMesh.h"

#include "managerList.h"

customMesh::customMesh()
{
	_meshSphere = createMeshSphere();
	_meshPlane = createMeshPlane();
}

customMesh::~customMesh()
{
	SAFE_RELEASE(_meshSphere);
	SAFE_RELEASE(_meshPlane);
}

void customMesh::drawPre(void)
{
}

void customMesh::drawDo(void)
{
}

void customMesh::drawPost(void)
{
}

LPD3DXMESH customMesh::createMeshSphere(void)
{
	LPD3DXMESH result = nullptr;

	return LPD3DXMESH();
}

LPD3DXMESH customMesh::createMeshPlane(void)
{
	return LPD3DXMESH();
}
