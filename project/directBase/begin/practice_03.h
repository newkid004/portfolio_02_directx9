#pragma once
#include "kGlobalDefine.h"
#include "direct3dApplication.h"

class practice_03 : public direct3dApplication
{
public :
	struct vertex
	{
		enum
		{
			FVF = D3DFVF_XYZ | D3DFVF_TEX1
		};

		D3DXVECTOR3 pos;
		D3DXVECTOR2 UV;
	};

private:
	LPDIRECT3DVERTEXBUFFER9 _vertexBuffer = NULL;
	LPDIRECT3DTEXTURE9 _texture = NULL;

	bool		_isTiled = false;
	int			_addressMode = 1;
	D3DXVECTOR2 _offsetUV = D3DXVECTOR2(0, 0);
	D3DXVECTOR2 _setUV = D3DXVECTOR2(1, 1);

public:
	void init(void) override;
	void update(void) override;
	void draw(void) override;

public :
	void updateUV(void);
	void updateControl(void);

private:
	LPDIRECT3DVERTEXBUFFER9 createVertexBuffer(void);
	LPDIRECT3DTEXTURE9 createTexture(void);

public:
	practice_03(HINSTANCE hInstance, const SIZE & windowSize, int option);
	~practice_03();
};

