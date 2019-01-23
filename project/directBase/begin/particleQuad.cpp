#include "particleQuad.h"

#include "managerList.h"
#include "gFunc.h"

particleQuad::particleQuad(const particleSystem::mParams & param) :
	particleSystem(param, particleQuad::createVertexBuffer(param))
{
	_vertexDec = createVertexDec();
}

particleQuad::~particleQuad()
{
	SAFE_RELEASE(_vertexDec);
}

void particleQuad::drawPre(void)
{
	particleSystem::drawPre();

	MN_DEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
}

void particleQuad::drawDo(void)
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
			D3DXVECTOR3 pos[] = {
				// 좌
				D3DXVECTOR3(-1.0f, -1.0f,  0.0f),
				D3DXVECTOR3(-1.0f,  1.0f,  0.0f),
				D3DXVECTOR3(1.0f,  1.0f,  0.0f),

				// 우
				D3DXVECTOR3(-1.0f, -1.0f,  0.0f),
				D3DXVECTOR3(1.0f,  1.0f,  0.0f),
				D3DXVECTOR3(1.0f, -1.0f,  0.0f)
			};

			D3DXVECTOR2 uv[] = {
				D3DXVECTOR2(0.0f, 1.0f),
				D3DXVECTOR2(0.0f, 0.0f),
				D3DXVECTOR2(1.0f, 0.0f),
				D3DXVECTOR2(0.0f, 1.0f),
				D3DXVECTOR2(1.0f, 0.0f),
				D3DXVECTOR2(1.0f, 1.0f)
			};

			auto & target = pList[i];

			// 이동
			D3DXMATRIXA16 mTranslate;
			D3DXMatrixTranslation(&mTranslate,
				target.pos.x,
				target.pos.y,
				target.pos.z);

			// 척도
			D3DXMATRIXA16 mScale;
			D3DXMatrixScaling(&mScale,
				target.size,
				target.size,
				target.size);

			// 회전
			D3DXMATRIXA16 mRotate;
			D3DXMatrixRotationYawPitchRoll(&mRotate,
				D3DXToRadian(target.rotate.y),
				D3DXToRadian(target.rotate.x),
				D3DXToRadian(target.rotate.z));

			// 궤도
			D3DXMATRIXA16 mOrbit;
			D3DXMatrixRotationYawPitchRoll(&mOrbit,
				D3DXToRadian(target.orbit.y),
				D3DXToRadian(target.orbit.x),
				D3DXToRadian(target.orbit.z));

			// 변환
			D3DXMATRIXA16 mTotal = mScale * mRotate * mTranslate * mOrbit;

			D3DXVec3TransformCoordArray(pos,
				sizeof(D3DXVECTOR3), pos,
				sizeof(D3DXVECTOR3), &mTotal,
				sizeof(pos) / sizeof(pos[0]));

			int index = i * 6;

			for (int j = 0; j < 6; ++j)
			{
				v[index + j].position = pos[j];
				v[index + j].diffuse = pList[i].color;
				v[index + j].uv = uv[j];
			}
		}
		_vertexBuffer->Unlock();
	}

	// 출력
	MN_DEV->SetStreamSource(0, _vertexBuffer, 0, sizeof(vertex));
	MN_DEV->SetVertexDeclaration(_vertexDec);
	MN_DEV->SetTexture(0, _texture);

	MN_DEV->DrawPrimitive(D3DPT_TRIANGLELIST, 0, pList.size() * 2);
}

void particleQuad::drawPost(void)
{
	particleSystem::drawPost();

	MN_DEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

LPDIRECT3DVERTEXDECLARATION9 particleQuad::createVertexDec(void)
{
	D3DVERTEXELEMENT9 elements[MAX_FVF_DECL_SIZE];
	ZeroMemory(&elements, sizeof(elements));

	D3DXDeclaratorFromFVF(vertex::FVF, elements);

	LPDIRECT3DVERTEXDECLARATION9 result = nullptr;

	MN_DEV->CreateVertexDeclaration(elements, &result);

	return result;
}

LPDIRECT3DVERTEXBUFFER9 particleQuad::createVertexBuffer(const particleSystem::mParams & param)
{
	return gFunc::createVertexBuffer(
		sizeof(vertex) * param.emitterParam.maxNumParticle * 6,
		D3DUSAGE_WRITEONLY,
		vertex::FVF);
}