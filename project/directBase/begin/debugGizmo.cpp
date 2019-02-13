#include "debugGizmo.h"

#include "gFunc.h"
#include "managerList.h"

debugGizmo::debugGizmo(int length) :
	_length(length)
{
	setScale(length);

	_vertexBuffer = createVertexBuffer();
}

debugGizmo::~debugGizmo()
{
	SAFE_RELEASE(_vertexBuffer);
}

#ifdef _DEBUG
void debugGizmo::update(void)
{
	renderObject::update();
	_isCull = false;
}

void debugGizmo::drawPre(void)
{
	renderObject::drawPre();
	MN_DEV->SetRenderState(D3DRS_LIGHTING, FALSE);
	MN_DEV->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	MN_DEV->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
}

void debugGizmo::drawDo(void)
{
	renderObject::drawDo();

	MN_DEV->SetTransform(D3DTS_WORLD, &getMatrixWorld());

	MN_DEV->SetStreamSource(0, _vertexBuffer, 0, sizeof(vertex));
	MN_DEV->SetFVF(vertex::FVF);
	MN_DEV->DrawPrimitive(D3DPT_LINELIST, 0, 9);
}

void debugGizmo::drawPost(void)
{
	renderObject::drawPost();
	MN_DEV->SetRenderState(D3DRS_LIGHTING, TRUE);
}

#endif // _DEBUG

LPDIRECT3DVERTEXBUFFER9 debugGizmo::createVertexBuffer(void)
{
	auto result = gFunc::createVertexBuffer(sizeof(vertex) * 18, D3DUSAGE_WRITEONLY, vertex::FVF);

	vertex* v = nullptr;
	if (SUCCEEDED(result->Lock(0, 0, (void**)&v, 0)))
	{
		int index = 0;
		// x
		v[index++].pos = D3DXVECTOR3(0, 0, 0);
		v[index++].pos = D3DXVECTOR3(_length, 0, 0);

		v[index++].pos = D3DXVECTOR3(_length * 0.9f, 0, _length * 0.1f);
		v[index++].pos = D3DXVECTOR3(_length, 0, 0);

		v[index++].pos = D3DXVECTOR3(_length * 0.9f, 0, -_length * 0.1f);
		v[index++].pos = D3DXVECTOR3(_length, 0, 0);

		// y
		v[index++].pos = D3DXVECTOR3(0, 0, 0);
		v[index++].pos = D3DXVECTOR3(0, _length, 0);

		v[index++].pos = D3DXVECTOR3(_length * 0.1f, _length * 0.9f, 0);
		v[index++].pos = D3DXVECTOR3(0, _length, 0);

		v[index++].pos = D3DXVECTOR3(-_length * 0.1f, _length * 0.9f, 0);
		v[index++].pos = D3DXVECTOR3(0, _length, 0);

		// z
		v[index++].pos = D3DXVECTOR3(0, 0, 0);
		v[index++].pos = D3DXVECTOR3(0, 0, _length);

		v[index++].pos = D3DXVECTOR3(0, _length * 0.1f, _length * 0.9f);
		v[index++].pos = D3DXVECTOR3(0, 0, _length);

		v[index++].pos = D3DXVECTOR3(0, -_length * 0.1f, _length * 0.9f);
		v[index++].pos = D3DXVECTOR3(0, 0, _length);

		for (int i = 0; i < 6; ++i)
			v[i].diffuse = COLOR_RED(255);
		for (int i = 6; i < 12; ++i)
			v[i].diffuse = COLOR_GREEN(255);
		for (int i = 12; i < 18; ++i)
			v[i].diffuse = COLOR_BLUE(255);

		result->Unlock();
	}

	return result;
}