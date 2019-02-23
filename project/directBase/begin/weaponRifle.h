#pragma once
#include "kGlobalDefine.h"

#include "inGame_struct.h"
#include "weaponBase.h"

class weaponRifle :public weaponBase
{
protected:
	virtual void firePre(void) override;
	virtual void fireDo(void) override;
	virtual void firePost(void) override;

	virtual void reloadBullet();
	virtual void updateHandMatrix(D3DXMATRIXA16 combineMatrix[]) override;
public:
	weaponRifle(staticMesh::mParam param , characterBase* linkPatternDup, int damage = 3);
	virtual ~weaponRifle();
};