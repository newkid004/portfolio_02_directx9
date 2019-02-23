#pragma once
#include "kGlobalDefine.h"

#include "inGame_struct.h"
#include "weaponBase.h"

class weaponHealkit :public weaponBase
{
private:
	D3DXVECTOR3 _originR;
	D3DXVECTOR3 _originU;
	D3DXVECTOR3 _originF;

public:
	virtual void updateWeapon(D3DXMATRIXA16 combineMatrix[], bool isCull) override;

protected:

	virtual void firePre(void) override;
	virtual void fireDo(void) override;
	virtual void firePost(void) override {};
public:
	weaponHealkit(staticMesh::mParam param, characterBase* linkPatternDup);
	virtual ~weaponHealkit();
};