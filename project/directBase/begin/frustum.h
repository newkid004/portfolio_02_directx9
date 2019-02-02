#pragma once
#include "kGlobalDefine.h"
#include "iUpdateble.h"

class frustum : public iUpdateble
{
private :
	D3DXPLANE _plane[6];	// near, far / left, right / top, bottom

public :
	void update(void) override;

protected :
	void updatePlane(void);

public :
	bool isCull(const D3DXVECTOR3 & pos);
	bool isCull(const boundingSphere & bound);

public :
	void getPlane(D3DXPLANE * outPlane[]);

public:
	frustum();
	~frustum();
};

