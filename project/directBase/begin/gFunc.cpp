#include "gFunc.h"
#include "managerList.h"

#include "direct3dApplication.h"
#include "camera.h"
#include "labelBase.h"

#include "sceneBase.h"

using namespace std;

void gFunc::runEffectLoop(LPD3DXEFFECT effect, const string & technique, const function<void(int)> & callback)
{
	effect->SetTechnique(technique.c_str());

	UINT numPass = 0;
	effect->Begin(&numPass, 0);

	for (int i = 0; i < numPass; ++i)
	{
		effect->BeginPass(i);
		callback(i);
		effect->EndPass();
	}

	effect->End();
}

void gFunc::runRenderTarget(LPDIRECT3DTEXTURE9 renderTarget, int clearOption, LPDIRECT3DSURFACE9 depthStensil, const std::function<void(void)>& callback, D3DCOLOR backColor)
{
	LPDIRECT3DSURFACE9 originRenderTarget = nullptr;
	LPDIRECT3DSURFACE9 originDepthStensil = nullptr;

	// ���� ����
	MN_DEV->GetRenderTarget(0, &originRenderTarget);
	if (depthStensil)
	{
		MN_DEV->GetDepthStencilSurface(&originDepthStensil);
		MN_DEV->SetDepthStencilSurface(depthStensil);
	}

	// ����Ÿ�� ����
	LPDIRECT3DSURFACE9 targetSurface = nullptr;
	if (SUCCEEDED(renderTarget->GetSurfaceLevel(0, &targetSurface)))
	{
		MN_DEV->SetRenderTarget(0, targetSurface);
		SAFE_RELEASE(targetSurface);
	}

	// ����Ÿ�� �ʱ�ȭ
	if (clearOption)
		MN_DEV->Clear(0, NULL, clearOption, backColor, 1, 0);

	// ���� ����
	callback();

	// ���� ����
	MN_DEV->SetRenderTarget(0, originRenderTarget);
	if (depthStensil)
		MN_DEV->SetDepthStencilSurface(originDepthStensil);

	SAFE_RELEASE(originRenderTarget);
	SAFE_RELEASE(originDepthStensil);
}

void gFunc::drawText(int x, int y, const std::string & text, int DT_align)
{
	GET_LABEL()->setAlign(DT_align);
	GET_LABEL()->setText(text);
	GET_LABEL()->setPosition(D3DXVECTOR3(x, y, 1.0f));

	GET_LABEL()->drawUI();
}

LPDIRECT3DVERTEXBUFFER9 gFunc::createVertexBuffer(int size, DWORD options, DWORD FVF)
{
	LPDIRECT3DVERTEXBUFFER9 result = nullptr;

	MN_DEV->CreateVertexBuffer(
		size,
		options,
		FVF,
		D3DPOOL_MANAGED,
		&result,
		NULL);

	return result;
}

LPDIRECT3DINDEXBUFFER9 gFunc::createIndexBuffer(int size, DWORD options, DWORD format)
{
	LPDIRECT3DINDEXBUFFER9 result = nullptr;

	MN_DEV->CreateIndexBuffer(
		size,
		options,
		(D3DFORMAT)format,
		D3DPOOL_MANAGED,
		&result,
		NULL);

	return result;
}

LPD3DXMESH gFunc::createMesh(int faceSize, int vertexSize, DWORD options, DWORD FVF)
{
	D3DVERTEXELEMENT9 elements[MAX_FVF_DECL_SIZE];
	ZeroMemory(&elements, sizeof(elements));

	D3DXDeclaratorFromFVF(FVF, elements);

	return createMesh(faceSize, vertexSize, options, elements);
}
LPD3DXMESH gFunc::createMesh(int faceSize, int vertexSize, DWORD options, D3DVERTEXELEMENT9* elements)
{
	LPD3DXMESH result = nullptr;

	D3DXCreateMesh(
		faceSize,
		vertexSize,
		options,
		elements,
		MN_DEV,
		&result);

	return result;
}

pRay gFunc::createPickRay(const POINT & clickPos)
{
	// �� -> ���� ��ȯ
	D3DVIEWPORT9 viewPort;
	MN_DEV->GetViewport(&viewPort);

	D3DXVECTOR2 normalizePos(
		((clickPos.x * 2.0f) / viewPort.Width) - 1.0f,
		((clickPos.y * -2.0f) / viewPort.Height) + 1.0f);

	// ���� -> �� ��ȯ
	D3DXMATRIXA16 & mProjection = GET_CAMERA()->getMatrixProjection();

	pRay ray;
	ZeroMemory(&ray, sizeof(ray));

	ray.direction = D3DXVECTOR3(
		normalizePos.x / mProjection._11,
		normalizePos.y / mProjection._22,
		1.0f);

	// �� -> ���� ��ȯ
	D3DXMATRIXA16 mView;
	MN_DEV->GetTransform(D3DTS_VIEW, &mView);

	D3DXMATRIXA16 miView;
	D3DXMatrixInverse(&miView, NULL, &mView);

	D3DXVec3TransformCoord(&ray.origin, &ray.origin, &miView);
	D3DXVec3TransformNormal(&ray.direction, &ray.direction, &miView);

	D3DXVec3Normalize(&ray.direction, &ray.direction);

	return ray;
}

int gFunc::rndInt(int min, int max)
{
	random_device rDevice;
	uniform_int_distribution<int> uRandom(min, max);

	return uRandom(rDevice);
}

float gFunc::rndFloat(float min, float max)
{
	random_device rDevice;
	uniform_real_distribution<float> uRandom(min, max);

	return uRandom(rDevice);
}
