#pragma once

#include "kGlobalDefine.h"
#include "singletonBase.h"
#include "inGame_struct.h"
#include "staticMesh.h"

class weaponBase;

class weaponManager : public singletonBase<weaponManager>
{
public:
	struct Type
	{
		constexpr static int rifle = 0;
		constexpr static int shotgun = 1;
		constexpr static int healkit = 2;
		constexpr static int normal = 3;
	};

private:

	std::vector<staticMesh::mParam> _vWeaponParam;
	std::vector<weapon_set> _vWeaponInfo;

private:
	void CreateParam(void);
	void CreateWeaponInfo(void);

public:
	staticMesh::mParam getParam(int index) { return _vWeaponParam[index]; }
	weapon_set getWeaponInfo(int index) { return _vWeaponInfo[index]; }
	
	weaponBase* createWeapon(int weaponType);

public:
	weaponManager(void);
	~weaponManager(void);
};
#define MN_WEAPON			(weaponManager::getInstance())