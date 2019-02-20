#include "wallMesh.h"

#include "camera.h"
#include "lightBase.h"
#include "managerList.h"
#include "gFunc.h"

#include "sceneBase.h"

wallMesh::wallMesh()
{
	ZeroMemory(&_wallParam, sizeof(_wallParam));
}

wallMesh::wallMesh(const staticMesh::mParam & param, std::string textureFilePath, std::string normalTextureFilePath)
:
staticMesh(param),
_texturePath(textureFilePath),
_normalTexturePath(normalTextureFilePath)
{
	_texture = MN_SRC->getTexture(textureFilePath);
	_normalTexture = MN_SRC->getTexture(normalTextureFilePath);
}

wallMesh::~wallMesh(void)
{
}

void wallMesh::drawPre(void)
{
	renderObject::drawPre();
	//MN_DEV->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	//MN_DEV->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);
}

void wallMesh::drawDo(void)
{
	// ����� �����Ѵ�
	// {
	D3DXMATRIXA16 mWorld = this->getMatrixFinal();

	D3DXMATRIXA16 mView = GET_CAMERA()->getMatrixView();
	D3DXMATRIXA16 mProjection = GET_CAMERA()->getMatrixProjection();

	_effect->SetMatrix("g_stWorldMatrix", &mWorld);
	_effect->SetMatrix("g_stViewMatrix", &mView);
	_effect->SetMatrix("g_stProjectionMatrix", &mProjection);
	// }

	// ī�޶�, ������ �����Ѵ�
	// {
	D3DXVECTOR4 viewPosition(GET_CAMERA()->getPosition(), 1.0f);
	D3DXVECTOR4 lightDirection(GET_LIGHT()->getDirectForward(), 0.0f);

	_effect->SetVector("g_stViewPosition", &viewPosition);
	_effect->SetVector("g_stLightDirection", &lightDirection);
	// }

	// �ؽ�ó�� �����Ѵ�
	// {
	_effect->SetTexture("g_pTexture", _texture);
	_effect->SetTexture("g_pNormalTexture", _normalTexture);
	//_effect->SetTexture("g_pBumpTexture", _bumpTexture);
	// }
	//_parallax = 0.02f;
	// ���� ������ �����Ѵ�
//	_effect->SetFloat("g_fParallax", _parallax);

	// ��ü�� �׸���
	for (int i = 0; i < _meshSet->numMaterial; ++i)
	{
		gFunc::runEffectLoop(_effect, "MyTechnique", [=](int a_nPassNumber) -> void {
			_meshSet->mesh->DrawSubset(i);
		});
	}
}

void wallMesh::drawPost(void)
{
	renderObject::drawPost();
}