#pragma once
#include "kGlobalDefine.h"
#include "staticMesh.h"
#include "inGame_struct.h"
#include "bulletManager.h"


class characterBase;

class weaponBase:public staticMesh
{
protected :
	characterBase*				_bindPMesh = nullptr;

	D3DXMATRIXA16	_baseMatrix[2];
	D3DXMATRIXA16   _localMatrix;
	D3DXVECTOR3 _handPosition;
	D3DXVECTOR3 _pickPosition = D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXVECTOR3 _targetDirection;

	weapon_set		_infoWeapon;

	bool _isLeft = true;

public :
	virtual void updateWeapon(D3DXMATRIXA16 combineMatrix[], bool isCull);

private :
	void updateFire(void);
	void updateReload(void);
	void updateNormal(void);

protected :
	virtual void firePre(void);
	virtual void fireDo(void);
	virtual void firePost(void);

	virtual void reloadPre(void);
	virtual void reloadDo(void);
	virtual void reloadPost(void);

	virtual void normalPre(void);
	virtual void normalDo(void);
	virtual void normalPost(void);

	virtual void reloadBullet() {};
	virtual void updateHandMatrix(D3DXMATRIXA16 combineMatrix[]);

public :
	bool isShotPossible(void);
	bool isReloadPossible(void);
	bool isStillFire(void);
	bool isNormalPossible(void);
	bool needReload(void);

public :
	weapon_set &	getInfoWeapon(void) { return _infoWeapon; }
	void chanegePickPosition(D3DXVECTOR3 picking) { _pickPosition = picking; }

	D3DXVECTOR3 & refHandPosition(void) { return _handPosition; }

public:
	weaponBase(staticMesh::mParam param , characterBase* linkPatternDup);
	weaponBase(characterBase* linkPatternDup);
	virtual ~weaponBase();
};

