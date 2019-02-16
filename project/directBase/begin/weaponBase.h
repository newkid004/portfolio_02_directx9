#pragma once
#include "kGlobalDefine.h"
#include "staticMesh.h"
#include "inGame_struct.h"

class viewDefBullet;
class patternMeshDup;

class weaponBase:public staticMesh
{
public :
	using bulletBase = viewDefBullet;

protected :
	bulletBase*					_bindBullet = nullptr;	// delete : disable (bulletManager)
	patternMeshDup*				_bindPMesh = nullptr;

	D3DXMATRIXA16	_baseMatrix[2];

	
	weapon_set		_infoWeapon;

	bool _isLeft = true;
public :
	void updateWeapon(D3DXMATRIXA16 combineMatrix[], bool isCull);

private :
	void updateFire(void);
	void updateReload(void);

protected :
	virtual void firePre(void);
	virtual void fireDo(void);
	virtual void firePost(void);

	virtual void reloadPre(void);
	virtual void reloadDo(void);
	virtual void reloadPost(void);

public :
	bool isShotPossible(void);
	bool isReloadPossible(void);
	bool isStillFire(void);
	bool needReload(void);

public :
	bulletBase* &	getBindBullet(void) { return _bindBullet; }
	weapon_set &	getInfoWeapon(void) { return _infoWeapon; }

public:
	weaponBase(patternMeshDup* linkPatternDup);
	virtual ~weaponBase();
};

