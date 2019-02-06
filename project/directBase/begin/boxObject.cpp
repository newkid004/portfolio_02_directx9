#include "boxObject.h"
#include "Direct3DApplication.h"
#include "deviceManager.h"
#include "camera.h"
#include "sceneBase.h"
#include "sceneManager.h"


boxObject::boxObject(void)
{
	m_pWallMesh = createWallMesh();
}

boxObject::~boxObject(void)
{
	SAFE_RELEASE(m_pWallMesh);
}

void boxObject::update(void)
{
	renderObject::update();
}

void boxObject::drawPre(void)
{
	renderObject::drawPre();

	GET_DEVICE_MANAGER()->getDevice()->SetRenderState(D3DRS_LIGHTING, false);
}

void boxObject::drawDo(void)
{
	renderObject::drawDo();

	D3DXMATRIXA16 stWorldMatrix = this->getMatrixFinal();
	D3DXMATRIXA16 stViewMatrix = GET_CAMERA()->getMatrixView();
	D3DXMATRIXA16 stProjectionMatrix = GET_CAMERA()->getMatrixProjection();

	GET_DEVICE_MANAGER()->getDevice()->SetTransform(D3DTS_WORLD, &stWorldMatrix);
	GET_DEVICE_MANAGER()->getDevice()->SetTransform(D3DTS_VIEW, &stViewMatrix);
	GET_DEVICE_MANAGER()->getDevice()->SetTransform(D3DTS_PROJECTION, &stProjectionMatrix);

	m_pWallMesh->DrawSubset(0);
}

void boxObject::drawPost(void)
{
	renderObject::drawPost();

	GET_DEVICE_MANAGER()->getDevice()->SetRenderState(D3DRS_LIGHTING, true);
}

LPD3DXMESH boxObject::createWallMesh(void)
{
	LPD3DXMESH pMesh = nullptr;

	D3DXCreateBox(GET_DEVICE_MANAGER()->getDevice(), 10, 8, 1, &pMesh, NULL);

	return pMesh;
}
