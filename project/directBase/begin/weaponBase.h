#pragma once
#include "kGlobalDefine.h"

#include "inGame_struct.h"

class viewDefBullet;

class weaponBase
{
public :
	using bulletBase = viewDefBullet;

protected :
	bulletBase*					_bindBullet = nullptr;	// delete : disable (bulletManager)
	std::list<D3DXMATRIXA16>	_baseMatrixList;
	
	weapon_set		_infoWeapon;

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
	std::list<D3DXMATRIXA16> &	getBaseMatrixList(void) { return _baseMatrixList; }

public:
	weaponBase();
	virtual ~weaponBase();
};

