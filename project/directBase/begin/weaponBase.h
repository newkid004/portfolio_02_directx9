#pragma once
#include "kGlobalDefine.h"

#include "inGame_data_status.h"

class viewDefBullet;

class weaponBase
{
public :
	using bulletBase = viewDefBullet;

protected :
	// info
	bulletBase*		_bindBullet = nullptr;
	weapon_set		_infoWeapon;
	D3DXMATRIXA16	_baseMatrix;

	// weapon
	bool			_isPressed = false;
	bool			_isReloading = false;

	float			_nextFireTime = 0.0f;
	float			_nextReloadTime = 0.0f;

public :
	void update(void);

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
	D3DXMATRIXA16 &	getBaseMatrix(void) { return _baseMatrix; }

public:
	weaponBase();
	virtual ~weaponBase();
};

