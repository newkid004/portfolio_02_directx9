#include "weaponManager.h"
#include "weaponHealkit.h"
#include "weaponRifle.h"
#include "weaponShotgun.h"
#include "weaponNormal.h"

weaponManager::weaponManager(void)
{
	this->CreateParam();
	this->CreateWeaponInfo();
}

weaponManager::~weaponManager(void)
{
}

void weaponManager::CreateParam(void)
{
	staticMesh::mParam stParam =
	{
		"resource/mesh/L4D1/items/rifle.x",
		"resource/effect/example_15.fx"
	};
	_vWeaponParam.push_back(stParam);

	stParam.meshFilePath = "resource/mesh/L4D1/items/shotgun.x";
	_vWeaponParam.push_back(stParam);

	stParam.meshFilePath = "resource/mesh/L4D1/items/medikit.x";
	_vWeaponParam.push_back(stParam);
}

void weaponManager::CreateWeaponInfo(void)
{
	weapon_set rifleSet;
	weapon_set shotgunSet;
	weapon_set healkitSet;
	weapon_set normalSet;

	rifleSet.type = weapon_set::type::rifle;
	rifleSet.current = 30;
	rifleSet.reload = 30;
	rifleSet.maximum = 180;
	rifleSet.damage = 3;
	rifleSet.shotDelay = 0.1f;
	rifleSet.reloadDelay = 2.0f;

	shotgunSet.type = weapon_set::type::shotgun;
	shotgunSet.current = 5;
	shotgunSet.reload = 5;
	shotgunSet.maximum = 30;
	shotgunSet.damage = 1;
	shotgunSet.shotDelay = 0.5f;
	shotgunSet.reloadDelay = 2.0f;

	healkitSet.type = weapon_set::type::healkit;
	healkitSet.current = 1;
	healkitSet.reload = 1;
	healkitSet.maximum = 0;

	normalSet.type = weapon_set::type::none;
	normalSet.current = 1;
	normalSet.damage = 5;
	normalSet.shotDelay = 1.0f;

	_vWeaponInfo.push_back(rifleSet);
	_vWeaponInfo.push_back(shotgunSet);
	_vWeaponInfo.push_back(healkitSet);
	_vWeaponInfo.push_back(normalSet);
}
