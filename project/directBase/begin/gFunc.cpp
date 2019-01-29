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

	// 원본 보존
	MN_DEV->GetRenderTarget(0, &originRenderTarget);
	if (depthStensil)
	{
		MN_DEV->GetDepthStencilSurface(&originDepthStensil);
		MN_DEV->SetDepthStencilSurface(depthStensil);
	}

	// 렌더타겟 설정
	LPDIRECT3DSURFACE9 targetSurface = nullptr;
	if (SUCCEEDED(renderTarget->GetSurfaceLevel(0, &targetSurface)))
	{
		MN_DEV->SetRenderTarget(0, targetSurface);
		SAFE_RELEASE(targetSurface);
	}

	// 렌더타겟 초기화
	if (clearOption)
		MN_DEV->Clear(0, NULL, clearOption, backColor, 1, 0);

	// 구문 실행
	callback();

	// 원본 복구
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

void gFunc::drawSprite(LPDIRECT3DTEXTURE9 texture, const D3DXVECTOR2 & pos, const D3DXVECTOR2 & size, const D3DXVECTOR2 & scale, float alpha)
{
	// 행렬 설정
	D3DXMATRIXA16 mWorld;
	D3DXMatrixScaling(&mWorld, scale.x, scale.y, 1.0f);

	GET_SPRITE()->SetTransform(&mWorld);

	// 출력
	D3DSURFACE_DESC sDesc;
	texture->GetLevelDesc(0, &sDesc);

	RECT rcTexture = { 0, 0, (LONG)sDesc.Width, (LONG)sDesc.Height };

	D3DXVECTOR3 position = {
		pos.x * (1.0f / scale.x),
		pos.y * (1.0f / scale.y),
		1.0f };

	GET_SPRITE()->Draw(
		texture,
		&rcTexture,
		&D3DXVECTOR3(rcTexture.right / 2.0f, rcTexture.bottom / 2.0f, 0.0f),
		&position,
		COLOR_WHITE((int)(255 * alpha)));
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

pick::ray gFunc::createPickRay(const POINT & clickPos)
{
	// 뷰 -> 투영 변환
	D3DVIEWPORT9 viewPort;
	MN_DEV->GetViewport(&viewPort);

	D3DXVECTOR2 normalizePos(
		((clickPos.x * 2.0f) / viewPort.Width) - 1.0f,
		((clickPos.y * -2.0f) / viewPort.Height) + 1.0f);

	// 투영 -> 뷰 변환
	D3DXMATRIXA16 & mProjection = GET_CAMERA()->getMatrixProjection();

	pick::ray ray;
	ZeroMemory(&ray, sizeof(ray));

	ray.direction = D3DXVECTOR3(
		normalizePos.x / mProjection._11,
		normalizePos.y / mProjection._22,
		1.0f);

	// 뷰 -> 월드 변환
	D3DXMATRIXA16 mView;
	MN_DEV->GetTransform(D3DTS_VIEW, &mView);

	D3DXMATRIXA16 miView;
	D3DXMatrixInverse(&miView, NULL, &mView);

	D3DXVec3TransformCoord(&ray.origin, &ray.origin, &miView);
	D3DXVec3TransformNormal(&ray.direction, &ray.direction, &miView);

	D3DXVec3Normalize(&ray.direction, &ray.direction);

	return ray;
}

LPDIRECT3DTEXTURE9 gFunc::createRenderTarget(void)
{
	LPDIRECT3DTEXTURE9 result = nullptr;

	MN_DEV->CreateTexture(
		GET_WINDOW_SIZE().cx,
		GET_WINDOW_SIZE().cy,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_R32F,
		D3DPOOL_DEFAULT,
		&result,
		NULL);

	return result;
}

LPDIRECT3DSURFACE9 gFunc::createDepthStensil(void)
{
	LPDIRECT3DSURFACE9 result = nullptr;

	MN_DEV->CreateDepthStencilSurface(
		GET_WINDOW_SIZE().cx,
		GET_WINDOW_SIZE().cy,
		D3DFMT_D24S8,
		D3DMULTISAMPLE_NONE,
		0,
		TRUE,
		&result,
		NULL);

	return result;
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

bool gFunc::isMouseInRange(const D3DXVECTOR2 & pos, const D3DXVECTOR2 & size)
{
	return
		pos.x < MN_KEY->getMousePos().x && MN_KEY->getMousePos().x < pos.x + size.x &&
		pos.y < MN_KEY->getMousePos().y && MN_KEY->getMousePos().y < pos.y + size.y;
}

boundingBox gFunc::createBoundingBox(LPD3DXMESH mesh)
{
	boundingBox result;

	// 경계 정보 설정
	void* vertex = nullptr;

	if (SUCCEEDED(mesh->LockVertexBuffer(0, &vertex)))
	{
		D3DXComputeBoundingBox(
			(D3DXVECTOR3*)vertex,
			mesh->GetNumVertices(),
			mesh->GetNumBytesPerVertex(),
			&result.min,
			&result.max);

		mesh->UnlockVertexBuffer();
	}

	return result;
}

boundingSphere gFunc::createBoundingSphere(LPD3DXMESH mesh)
{
	boundingSphere result;

	// 경계 정보 설정
	void* vertex = nullptr;

	if (SUCCEEDED(mesh->LockVertexBuffer(0, &vertex)))
	{
		D3DXComputeBoundingSphere(
			(D3DXVECTOR3*)vertex,
			mesh->GetNumVertices(),
			mesh->GetNumBytesPerVertex(),
			&result.center,
			&result.radius);

		mesh->UnlockVertexBuffer();
	}

	return result;
}

bool gFunc::isIntersect(const boundingBox & boundA, const boundingBox & boundB)
{
	if (boundB.max.x < boundA.min.x || boundA.max.x < boundB.min.x ||
		boundB.max.y < boundA.min.y || boundA.max.y < boundB.min.y ||
		boundB.max.z < boundA.min.z || boundA.max.z < boundB.min.z)
		return false;

	return true;
}

bool gFunc::isIntersect(const boundingSphere & boundA, const boundingSphere & boundB)
{
	auto distance = boundA.center - boundB.center;
	return D3DXVec3Length(&distance) <= boundA.radius + boundB.radius;
}

void gFunc::obj2bound(boundingBox * outBoundingBox, objectBox * inObjectBox)
{
	ZeroMemory(outBoundingBox, sizeof(boundingBox));

	D3DXVECTOR3 & center = inObjectBox->center;
	D3DXVECTOR3 direction[] = {
		inObjectBox->direction[0] * inObjectBox->halfLength[0],
		inObjectBox->direction[1] * inObjectBox->halfLength[1],
		inObjectBox->direction[2] * inObjectBox->halfLength[2]
	};

	// 경계 볼륨
	D3DXVECTOR3 vertices[] = {
		center + direction[0] + direction[1] + direction[2],
		center + direction[0] - direction[1] + direction[2],
		center - direction[0] + direction[1] + direction[2],
		center - direction[0] - direction[1] + direction[2],

		center + direction[0] + direction[1] - direction[2],
		center + direction[0] - direction[1] - direction[2],
		center - direction[0] + direction[1] - direction[2],
		center - direction[0] - direction[1] - direction[2]
	};

	outBoundingBox->min = center;
	outBoundingBox->max = center;

	// 위치 계산
	for (int i = 0; i < sizeof(vertices) / sizeof(vertices[0]); ++i)
	{
		D3DXVECTOR3 & v = vertices[i];

		if (v.x < outBoundingBox->min.x)	outBoundingBox->min.x = v.x;
		if (v.x >= outBoundingBox->max.x)	outBoundingBox->max.x = v.x;

		if (v.y < outBoundingBox->min.y)	outBoundingBox->min.y = v.y;
		if (v.y >= outBoundingBox->max.y)	outBoundingBox->max.y = v.y;

		if (v.z < outBoundingBox->min.z)	outBoundingBox->min.z = v.z;
		if (v.z >= outBoundingBox->max.z)	outBoundingBox->max.z = v.z;
	}
}
