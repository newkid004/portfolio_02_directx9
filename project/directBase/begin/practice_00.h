#pragma once
#include "kGlobalDefine.h"
#include "direct3dApplication.h"

using namespace std::chrono;

class practice_00 : public direct3dApplication
{
public:
	struct vertex
	{
		enum
		{
			FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE
		};

		D3DXVECTOR3 pos;
		D3DCOLOR diffuse;
	};
	float _deg;
	system_clock::time_point _tPoint;

private:
	LPDIRECT3DVERTEXBUFFER9 _vertexBuffer = NULL;

public:
	void init(void) override;
	LRESULT handleWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

	void update(void) override;
	void draw(void) override;

private :
	LPDIRECT3DVERTEXBUFFER9 createVertexBuffer(void);
	void initMatrix(void);

public:
	practice_00(HINSTANCE hInstance, const SIZE & windowSize, int option);
	~practice_00();
};

