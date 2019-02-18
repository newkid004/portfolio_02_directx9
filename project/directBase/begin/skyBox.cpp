#include "skyBox.h"

#include "managerList.h"

#include "direct3dApplication.h"
#include "gFunc.h"

#include "sceneBase.h"
#include "camera.h"

skyBox::skyBox(const mParam & param) :
	_param(param)
{
	_mesh = createMesh();
	_effect = MN_SRC->getEffect(param.pathEffect);
	_textureCube = MN_SRC->getTextureCube(param.pathTextureCube);
}

skyBox::~skyBox()
{
	SAFE_RELEASE(_mesh);
}

void skyBox::drawPre(void)
{
	renderObject::drawPre();

	MN_DEV->SetRenderState(D3DRS_LIGHTING, FALSE);
	MN_DEV->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
}

void skyBox::drawDo(void)
{
	renderObject::drawDo();

	// 행렬
	D3DXVECTOR3 cameraPos = GET_CAMERA()->getOffsetPosition() / 10.0f;
	D3DXMATRIXA16 mScale, mTranslate, mWorld;
	D3DXMatrixScaling(&mScale, 10.0f, 10.0f, 10.0f);
	D3DXMatrixTranslation(&mTranslate, cameraPos.x, cameraPos.y, cameraPos.z);
	mWorld = mScale * mTranslate;

	_effect->SetMatrix("_mWorld", &mWorld);
	_effect->SetMatrix("_mView", GET_CAMERA()->getMatrixViewPoint());
	_effect->SetMatrix("_mProjection", GET_CAMERA()->getMatrixProjectionPoint());

	// 텍스쳐
	_effect->SetTexture("_textureCube", _textureCube);

	gFunc::runEffectLoop(_effect, "skyboxTechnique", [&](int numPass)->void {
		_mesh->DrawSubset(0);
	});
}

void skyBox::drawPost(void)
{
	renderObject::drawPost();
	MN_DEV->SetTexture(0, NULL);

	MN_DEV->SetRenderState(D3DRS_LIGHTING, TRUE);
	MN_DEV->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

LPD3DXMESH skyBox::createMesh(void)
{
	LPD3DXMESH result = nullptr;
	LPD3DXBUFFER bufAdjacency = nullptr;

	D3DXCreateSphere(
		MN_DEV,
		0.5f,
		50, 50,
		&result,
		&bufAdjacency);

	D3DXComputeNormals(result, (DWORD*)bufAdjacency->GetBufferPointer());

	SAFE_RELEASE(bufAdjacency);

	return result;
}
