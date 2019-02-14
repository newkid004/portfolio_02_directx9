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

void gFunc::runRenderTarget(LPDIRECT3DTEXTURE9 renderTarget, int clearOption, LPDIRECT3DSURFACE9 depthStensil, const std::function<void(void)>& callback, bool isAlpha, D3DCOLOR backColor)
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
	if (renderTarget)
	{
		if (SUCCEEDED(renderTarget->GetSurfaceLevel(0, &targetSurface)))
		{
			MN_DEV->SetRenderTarget(0, targetSurface);
			SAFE_RELEASE(targetSurface);
		}

		// 렌더타겟 초기화
		if (clearOption)
			MN_DEV->Clear(0, NULL, clearOption, backColor, 1, 0);
	}

	// 알파 사용 확인
	if (isAlpha)
	{
		// 알파 블렌딩
		MN_DEV->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		MN_DEV->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		MN_DEV->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		// 알파 테스팅
		MN_DEV->SetRenderState(D3DRS_ALPHATESTENABLE, true);
		MN_DEV->SetRenderState(D3DRS_ALPHAREF, 0x01);
		MN_DEV->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

	}

	// 구문 실행
	callback();

	// 알파 사용 복구
	if (isAlpha)
	{
		MN_DEV->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		MN_DEV->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	}

	// 원본 복구
	MN_DEV->SetRenderTarget(0, originRenderTarget);
	if (depthStensil)
		MN_DEV->SetDepthStencilSurface(originDepthStensil);

	SAFE_RELEASE(originRenderTarget);
	SAFE_RELEASE(originDepthStensil);
}

void gFunc::drawText(int x, int y, std::string & text, int DT_align, D3DCOLOR color)
{
	GET_LABEL()->setAlign(DT_align);
	GET_LABEL()->setText(text);
	GET_LABEL()->setPosition(D3DXVECTOR3(x, y, 0.0f));

	auto prevColor = GET_LABEL()->getColor();
	GET_LABEL()->setColor(color);

	GET_SPRITE()->SetTransform(getIdentity(true));
	GET_LABEL()->drawUI();

	GET_LABEL()->setColor(prevColor);
}

void gFunc::drawSprite(LPDIRECT3DTEXTURE9 texture, const D3DXVECTOR2 & pos, const D3DXVECTOR2 & size, const D3DXVECTOR2 & scale, float alpha, D3DXVECTOR2 * offset, RECT * clipSize, bool isClipPull)
{
	// 크기 설정
	D3DXVECTOR2 drawSize = gFunc::Vec2Dev(size, scale);
	RECT rcTexture = {
		0, 0,
		(LONG)drawSize.x,
		(LONG)drawSize.y };

	// 보간 설정
	if (offset)
	{
		D3DXVECTOR2 offsetValue = gFunc::Vec2Dev(*offset, scale);
		rcTexture.right += rcTexture.left = offsetValue.x;
		rcTexture.bottom += rcTexture.top = offsetValue.y;
	}

	// 클립 설정
	D3DXVECTOR4 clipValue;
	if (clipSize)
	{
		clipValue = D3DXVECTOR4(
			clipSize->left / scale.x,
			clipSize->top / scale.y,
			clipSize->right / scale.x,
			clipSize->bottom / scale.y);

		rcTexture.left += clipValue.x;
		rcTexture.top += clipValue.y;
		rcTexture.right -= clipValue.z;
		rcTexture.bottom -= clipValue.w;
	}

	// 행렬 설정
	D3DXMATRIXA16 mWorld;
	D3DXMatrixScaling(&mWorld, 
		scale.x,
		scale.y,
		1.0f);
	GET_SPRITE()->SetTransform(&mWorld);

	// 위치 설정
	D3DXVECTOR3 position = {
		pos.x * (1.0f / scale.x) + (isClipPull || clipSize == NULL ? 0 : clipValue.x),
		pos.y * (1.0f / scale.y) + (isClipPull || clipSize == NULL ? 0 : clipValue.y),
		0.0f };

	GET_SPRITE()->Draw(
		texture,
		&rcTexture,
		NULL,
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

pick::ray gFunc::createPickRay(const POINT & clickPos, const D3DXVECTOR3 & origin)
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

	ray.origin = origin;
	ray.direction = D3DXVECTOR3(
		normalizePos.x / mProjection._11,
		normalizePos.y / mProjection._22,
		1.0f);

	// 뷰 -> 월드 변환
	D3DXMATRIXA16 mView;
	MN_DEV->GetTransform(D3DTS_VIEW, &mView);

	D3DXMATRIXA16 miView;
	D3DXMatrixInverse(&miView, NULL, &mView);

	if (origin == D3DXVECTOR3(0, 0, 0))
	{
		D3DXVec3TransformCoord(&ray.origin, &ray.origin, &miView);
	}
	D3DXVec3TransformNormal(&ray.direction, &ray.direction, &miView);

	D3DXVec3Normalize(&ray.direction, &ray.direction);

	return ray;
}

LPDIRECT3DTEXTURE9 gFunc::createRenderTarget(D3DXVECTOR2 size)
{
	LPDIRECT3DTEXTURE9 result = nullptr;

	if (size == D3DXVECTOR2())
		size = D3DXVECTOR2(
			GET_WINDOW_SIZE().cx,
			GET_WINDOW_SIZE().cy);

	MN_DEV->CreateTexture(
		size.x,
		size.y,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&result,
		NULL);

	return result;
}

LPDIRECT3DTEXTURE9 gFunc::createRenderTargetShadowMap(D3DXVECTOR2 size)
{
	LPDIRECT3DTEXTURE9 result = nullptr;

	if (size == D3DXVECTOR2())
		size = D3DXVECTOR2(
			GET_WINDOW_SIZE().cx,
			GET_WINDOW_SIZE().cy);

	MN_DEV->CreateTexture(
		size.x,
		size.y,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_R32F,
		D3DPOOL_DEFAULT,
		&result,
		NULL);

	return result;
}

LPDIRECT3DSURFACE9 gFunc::createDepthStensil(D3DXVECTOR2 size)
{
	LPDIRECT3DSURFACE9 result = nullptr;

	if (size == D3DXVECTOR2())
		size = D3DXVECTOR2(
			GET_WINDOW_SIZE().cx,
			GET_WINDOW_SIZE().cy);

	MN_DEV->CreateDepthStencilSurface(
		size.x,
		size.y,
		D3DFMT_D24S8,
		D3DMULTISAMPLE_NONE,
		0,
		TRUE,
		&result,
		NULL);

	return result;
}

void gFunc::getTextureSize(D3DXVECTOR2 * out_size, LPDIRECT3DTEXTURE9 texture)
{
	// 출력
	D3DSURFACE_DESC sDesc;
	texture->GetLevelDesc(0, &sDesc);

	out_size->x = sDesc.Width;
	out_size->y = sDesc.Height;
}

void gFunc::getNormal(D3DXVECTOR3 * out, D3DXVECTOR3 * v0, D3DXVECTOR3 * v1, D3DXVECTOR3 * v2)
{
	D3DXVec3Cross(out, &(*v1 - *v0), &(*v2 - *v0));
	D3DXVec3Normalize(out, out);
}

float gFunc::getAngle(D3DXVECTOR3 v1, D3DXVECTOR3 v2)
{
	D3DXVec3Normalize(&v1, &v1);
	D3DXVec3Normalize(&v2, &v2);

	float angle = std::acosf(D3DXVec3Dot(&v1, &v2));

	if (v1.x * v2.y - v1.y * v2.x < 0.0f)
		angle = -angle;

	return angle;
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

boundingBox gFunc::createBoundingBox(D3DXVECTOR3 position, float width, float height, float depth)
{
	boundingBox result;

	// 경계 정보 설정
	result.min = D3DXVECTOR3(position.x - width / 2, position.y - height / 2, position.z - depth / 2);
	result.max = D3DXVECTOR3(position.x + width / 2, position.y + height / 2, position.z + depth / 2);
	
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

boundingSphere gFunc::createBoundingSphere(D3DXVECTOR3 position, float radius)
{
	boundingSphere result;

	// 경계 정보 설정
	result.center = position;
	result.radius = radius;

	return result;
}

bool gFunc::isIntersect(const objectBox & boundA, const objectBox & boundB)
{
	float cutoffValue = 0.99999f;
	bool isExistParallel = false;

	float cosValues[3][3] = { 0.0f, };
	float absCosValues[3][3] = { 0.0f, };

	float deltaDotValues[3] = { 0.0f, };
	D3DXVECTOR3 delta = boundB.center - boundA.center;

	float dotValueA = 0.0f;
	float dotValueB = 0.0f;
	float totalDotValue = 0.0f;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			cosValues[i][j] = D3DXVec3Dot(&boundA.direction[i], &boundB.direction[j]);
			absCosValues[i][j] = fabsf(cosValues[i][j]);

			// 평행한 축이 존재할 경우
			if (cutoffValue < absCosValues[i][j])
				isExistParallel = true;
		}
		deltaDotValues[i] = D3DXVec3Dot(&boundA.direction[i], &delta);
	}

	// ----- A기준 충돌 ----- //
	// X Y Z 순
	for (int i = 0; i < 3; ++i)
	{
		totalDotValue = fabsf(deltaDotValues[i]);
		dotValueA = boundA.halfLength[i];
		dotValueB =
			(absCosValues[i][0] * boundB.halfLength[0]) +
			(absCosValues[i][1] * boundB.halfLength[1]) +
			(absCosValues[i][2] * boundB.halfLength[2]);

		if (dotValueA + dotValueB < totalDotValue)
			return false;
	}

	// ----- B기준 충돌 ----- //
	// X Y Z 순
	for (int i = 0; i < 3; ++i)
	{
		totalDotValue = fabsf(D3DXVec3Dot(&boundA.direction[i], &delta));
		dotValueB = boundB.halfLength[i];
		dotValueA =
			(absCosValues[0][i] * boundA.halfLength[0]) +
			(absCosValues[1][i] * boundA.halfLength[1]) +
			(absCosValues[2][i] * boundA.halfLength[2]);

		if (dotValueA + dotValueB < totalDotValue)
			return false;
	}

	// ----- 평행축 존재 ----- //
	if (isExistParallel)
		return true;

	// ----- A x B 기준 충돌 ----- //
	// X x X ~ Z x Z
	for (int c = 0; c < 3; ++c)
	{
		for (int r = 0; r < 3; ++r)
		{
			int column1 = (c + 1) % 3;
			int column2 = (c + 2) % 3;

			int row1 = (r + 1) % 3;
			int row2 = (r + 2) % 3;

			totalDotValue = fabs(
				(deltaDotValues[column2] * cosValues[column1][r]) -
				(deltaDotValues[column1] * cosValues[column2][r]));
			dotValueA =
				absCosValues[column2][r] * boundA.halfLength[column1] +
				absCosValues[column1][r] * boundA.halfLength[column2];
			dotValueB =
				absCosValues[c][row2] * boundA.halfLength[row1] +
				absCosValues[c][row1] * boundA.halfLength[row2];

			if (dotValueA + dotValueB < totalDotValue)
				return false;
		}
	}

	return true;
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
