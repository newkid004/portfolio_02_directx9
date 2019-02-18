#pragma once

#include "kGlobalDefine.h"
#include "singletonBase.h"
#include "inGame_struct.h"
#include "staticMesh.h"

class weaponManager : public singletonBase<weaponManager>
{
public:
	static enum class weaponType
	{
		rifle = 0,
		shotgun = 1,
		healkit = 2,
		normal = 3
	};

private:

	std::vector<staticMesh::mParam> _vWeaponParam;
	std::vector<weapon_set> _vWeaponInfo;

private:
	void CreateParam(void);
	void CreateWeaponInfo(void);

public:
	staticMesh::mParam getParam(weaponManager::weaponType index) { return _vWeaponParam[(int)index]; }
	weapon_set getWeaponInfo(weaponManager::weaponType index) { return _vWeaponInfo[(int)index]; }

public:
	weaponManager(void);
	~weaponManager(void);
};
#define MN_WEAPON			(weaponManager::getInstance())