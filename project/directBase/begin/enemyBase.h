#pragma once
#include "kGlobalDefine.h"
#include "characterBase.h"

class enemyBase : public characterBase
{
protected :
	D3DXVECTOR3	_nextPlacePos;			// 다음 목표지점

public :
	void update(void) override;

protected :
	void updateAdjacent(void);
	void updateApproach(void);

public :
	D3DXVECTOR3 & refNextPlacePos(void) { return _nextPlacePos; }

public:
	enemyBase(patternMesh* duplicateTarget);
	~enemyBase();
};

