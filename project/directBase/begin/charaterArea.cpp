#include "charaterArea.h"

#include "gFunc.h"
#include "managerList.h"

charaterArea::charaterArea(int length)
	:_length(length)
{
	_vertexBuffer = createVertexBuffer();
	_texture = MN_SRC->getTexture("resource/texture/maptool/nodeRange.png");
}

charaterArea::~charaterArea()
{
	SAFE_RELEASE(_vertexBuffer);
}

#ifdef _DEBUG
void charaterArea::update(void)
{
	renderObject::update();
}

void charaterArea::drawPre(void)
{
	renderObject::drawPre();

	MN_DEV->SetRenderState(D3DRS_LIGHTING, FALSE);
	MN_DEV->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	MN_DEV->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	MN_DEV->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	MN_DEV->SetTexture(0, _texture);
}

void charaterArea::drawDo(void)
{
	renderObject::drawDo();
	D3DXMATRIXA16 finalMatrix;
	D3DXMatrixTranslation(&finalMatrix, getParentPosition().x, getParentPosition().y, getParentPosition().z);
	finalMatrix = finalMatrix * getMatrixWorld();
	MN_DEV->SetStreamSource(0, _vertexBuffer, 0, sizeof(vertex));
	MN_DEV->SetTransform(D3DTS_WORLD, &finalMatrix);
	MN_DEV->SetFVF(vertex::FVF);
	gFunc::runRenderTarget(NULL, NULL, NULL, [&](void)->void
	{
		MN_DEV->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
	},true);
}

void charaterArea::drawPost(void)
{
	renderObject::drawPost();
	MN_DEV->SetRenderState(D3DRS_LIGHTING, TRUE);
	MN_DEV->SetTexture(0, NULL);
}

#endif
LPDIRECT3DVERTEXBUFFER9 charaterArea::createVertexBuffer(void)
{
	auto result = gFunc::createVertexBuffer(sizeof(vertex) * 6, D3DUSAGE_WRITEONLY, vertex::FVF);

	vertex* vertex = nullptr;
	if (SUCCEEDED(result->Lock(0, 0, (void**)&vertex, 0)))
	{
		vertex[0].m_stPosition = D3DXVECTOR3(-_length, 1, -_length);
		vertex[0].m_stUV = D3DXVECTOR2(0.0f, 1.0f);
		vertex[1].m_stPosition = D3DXVECTOR3(-_length, 1, _length);
		vertex[1].m_stUV = D3DXVECTOR2(0.0f, 0.0f);
		vertex[2].m_stPosition = D3DXVECTOR3(_length, 1, _length);
		vertex[2].m_stUV = D3DXVECTOR2(1.0f, 0.0f);
		vertex[3].m_stPosition = D3DXVECTOR3(_length, 1, _length);
		vertex[3].m_stUV = D3DXVECTOR2(1.0f, 0.0f);
		vertex[4].m_stPosition = D3DXVECTOR3(_length, 1, -_length);
		vertex[4].m_stUV = D3DXVECTOR2(1.0f, 1.0f);
		vertex[5].m_stPosition = D3DXVECTOR3(-_length, 1, -_length);
		vertex[5].m_stUV = D3DXVECTOR2(0.0f, 1.0f);

		result->Unlock();
	}

	return result;
}
