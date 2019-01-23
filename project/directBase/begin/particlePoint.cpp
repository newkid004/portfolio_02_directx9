#include "particlePoint.h"

#include "gFunc.h"
#include "managerList.h"

particlePoint::particlePoint(const particleSystem::mParams & param) :
	particleSystem(param, particlePoint::createVertexBuffer(param))
{
}

particlePoint::~particlePoint()
{
}

void particlePoint::drawPre(void)
{
	particleSystem::drawPre();

	MN_DEV->SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);	// 카메라 거리에 따라 입자의 크기 자동 조절
	MN_DEV->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);	// 점 출력 시, 텍스쳐 사용여부
	MN_DEV->SetRenderState(D3DRS_POINTSIZE_MIN, gFunc::float2DWORD(0.0f));
	MN_DEV->SetRenderState(D3DRS_POINTSIZE_MAX, gFunc::float2DWORD(300.0f));

	// 포인트 크기 계산 공식
	// viewPort * pointSize * sprt(1 / (A + B * Distance) + C * (Distacne ^ 2)))
	MN_DEV->SetRenderState(D3DRS_POINTSCALE_A, gFunc::float2DWORD(0.0f));
	MN_DEV->SetRenderState(D3DRS_POINTSCALE_B, gFunc::float2DWORD(0.0f));
	MN_DEV->SetRenderState(D3DRS_POINTSCALE_C, gFunc::float2DWORD(1.0f));
}

void particlePoint::drawDo(void)
{
	particleSystem::drawDo();

	// 행렬
	auto mWorld = getMatrixFinal();
	MN_DEV->SetTransform(D3DTS_WORLD, &mWorld);

	// 정점
	auto & pList = _emitter->getParticleList();
	vertex* v = nullptr;
	if (SUCCEEDED(_vertexBuffer->Lock(0, 0, (void**)&v, 0)))
	{

		for (int i = 0; i < pList.size(); ++i)
		{
			v[i].position = pList[i].pos;
			v[i].pSize = pList[i].size;
			v[i].diffuse = pList[i].color;
		}

		_vertexBuffer->Unlock();
	}

	// 출력
	MN_DEV->SetStreamSource(0, _vertexBuffer, 0, sizeof(vertex));
	MN_DEV->SetFVF(vertex::FVF);
	MN_DEV->SetTexture(0, _texture);

	MN_DEV->DrawPrimitive(D3DPT_POINTLIST, 0, pList.size());
}

void particlePoint::drawPost(void)
{
	particleSystem::drawPost();

	MN_DEV->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);
	MN_DEV->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
}

LPDIRECT3DVERTEXBUFFER9 particlePoint::createVertexBuffer(const particleSystem::mParams & param)
{
	return gFunc::createVertexBuffer(
		sizeof(vertex) * param.emitterParam.maxNumParticle,
		D3DUSAGE_WRITEONLY,
		vertex::FVF);
}