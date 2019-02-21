#pragma once
#include "kGlobalDefine.h"
#include "characterBase.h"

class enemyBase : public characterBase
{
protected :
	int _enemyType;
	D3DXVECTOR3	_nextPlacePos;			// ���� ��ǥ����

public :
	void update(void) override;

protected :
	void updateAdjacent(void);
	void updateApproach(void);

	void doResurrection(void);

public :
	int & refEnemyType(void) { return _enemyType; }
	D3DXVECTOR3 & refNextPlacePos(void) { return _nextPlacePos; }

public:
	enemyBase(patternMesh* duplicateTarget);
	~enemyBase();
};

