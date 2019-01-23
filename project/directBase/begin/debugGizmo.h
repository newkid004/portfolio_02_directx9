#pragma once
#include "kGlobalDefine.h"
#include "renderObject.h"

class debugGizmo : public renderObject
{
public :
	struct vertex
	{
		enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
		D3DXVECTOR3 pos;
		D3DCOLOR diffuse;
	};

private :
	int _length = 0;
	LPDIRECT3DVERTEXBUFFER9 _vertexBuffer = nullptr;

#ifdef _DEBUG
protected:
	virtual void update(void) override;

	virtual void drawPre(void) override;
	virtual void drawDo(void) override;
	virtual void drawPost(void) override;

#endif	// _DEBUG

private :
	LPDIRECT3DVERTEXBUFFER9 createVertexBuffer(void);

public :
	void setLength(int input) { _length = input; }

public:
	debugGizmo(int length);
	virtual ~debugGizmo();
};

