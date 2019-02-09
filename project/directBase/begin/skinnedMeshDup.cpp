#include "skinnedMeshDup.h"

#include "skinnedMesh.h"

skinnedMeshDup::skinnedMeshDup(skinnedMesh * duplicateTarget) :
	_bindObject(duplicateTarget)
{


}

skinnedMeshDup::~skinnedMeshDup()
{
}


skinnedMesh * skinnedMeshDup::getBindObject(void)
{
	return _bindObject;
}

void skinnedMeshDup::update(void)
{
}

void skinnedMeshDup::drawPre(void)
{
}

void skinnedMeshDup::drawDo(void)
{
}

void skinnedMeshDup::drawPost(void)
{
}

void skinnedMeshDup::updateBoneMatrix(LPD3DXFRAME frame, const D3DXMATRIXA16 & mUpdate)
{
}

void skinnedMeshDup::drawBone(LPD3DXFRAME frame)
{
}

void skinnedMeshDup::drawMeshContainer(LPD3DXFRAME frame, LPD3DXMESHCONTAINER meshContainer)
{
}
