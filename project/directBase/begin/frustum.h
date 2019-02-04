#pragma once
#include "kGlobalDefine.h"
#include "iUpdateble.h"

class frustum : public iUpdateble
{
public :
	enum CULL
	{
		NEAR_FAR = 1,
		LEFT_RIGHT = 2,
		TOP_BOT = 4,

		ALL = 7,

		NONE = 0
	};

private :
	D3DXPLANE _plane[6];	// near, far / left, right / top, bottom

public :
	void update(void) override;

protected :
	void updatePlane(void);

public :
	bool isCull(const D3DXVECTOR3 & pos, int c = CULL::ALL);
	bool isCull(const boundingSphere & bound, int c = CULL::ALL);
	bool chkCull(const D3DXVECTOR3 & dotPos, float interval, int c);

public :
	void getPlane(D3DXPLANE * outPlane[]);

public:
	frustum();
	~frustum();
};

