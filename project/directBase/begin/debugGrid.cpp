#include "debugGrid.h"
#include "managerList.h"
#include "gFunc.h"

debugGrid::debugGrid(int size) :
	_size(size)
{
	_vertexBuffer = createVertexBuffer();
}

debugGrid::~debugGrid()
{
	SAFE_RELEASE(_vertexBuffer);
}

void debugGrid::drawPre(void)
{
	MN_DEV->SetRenderState(D3DRS_LIGHTING, false);
	MN_DEV->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	MN_DEV->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
}

void debugGrid::drawDo(void)
{
	// 행렬
	D3DXMATRIXA16 mWorld = getMatrixFinal();
	MN_DEV->SetTransform(D3DTS_WORLD, &mWorld);

	// 출력
	MN_DEV->SetStreamSource(0, _vertexBuffer, 0, sizeof(vertex));
	MN_DEV->SetFVF(vertex::FVF);

	MN_DEV->DrawPrimitive(D3DPT_LINELIST, 0, (_size + 1) * 2);
}

void debugGrid::drawPost(void)
{
	MN_DEV->SetRenderState(D3DRS_LIGHTING, true);
}

LPDIRECT3DVERTEXBUFFER9 debugGrid::createVertexBuffer(void)
{
	LPDIRECT3DVERTEXBUFFER9 result = gFunc::createVertexBuffer(
		sizeof(vertex) * (_size + 1) * 4,
		D3DUSAGE_WRITEONLY,
		vertex::FVF);

	vertex* v = nullptr;
	if (SUCCEEDED(result->Lock(0, 0, (void**)&v, 0)))
	{
		D3DXVECTOR3 posBase = {
			_size / -2.0f,
			0.0f,
			_size / 2.0f
		};

		for (int i = 0; i < _size; ++i)
		{
			int index = i * 4;
			D3DXCOLOR dif = D3DCOLOR_XRGB(180, 180, 180);
			if (i % 5 == 0)
				dif = D3DCOLOR_XRGB(255, 255, 255);

			// 가로
			v[index + 0].pos = posBase + D3DXVECTOR3(0.0f, 0.0f, -i);
			v[index + 1].pos = posBase + D3DXVECTOR3(_size, 0.0f, -i);

			// 세로
			v[index + 2].pos = posBase + D3DXVECTOR3(i, 0.0f, 0.0f);
			v[index + 3].pos = posBase + D3DXVECTOR3(i, 0.0f, -_size);

			for (int j = 0; j < 4; ++j)
				v[index + j].diffuse = dif;
		}

		result->Unlock();
	}

	return result;
}
