#include "weaponManager.h"
#include "weaponHealkit.h"
#include "weaponRifle.h"
#include "weaponShotgun.h"
#include "weaponNormal.h"

#include "managerList.h"
#include "player.h"

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
	weapon_set zombie;
	weapon_set tank;

	normalSet.type = weapon_set::type::none;
	normalSet.current = 1;
	normalSet.damage = 5;
	normalSet.shotDelay = 0.8f;

	rifleSet.type = weapon_set::type::rifle;
	rifleSet.current = 30;
	rifleSet.reload = 30;
	rifleSet.maximum = 180;
	rifleSet.damage = 1;
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

	zombie.type = weapon_set::type::zombie;
	zombie.current = 1;
	zombie.damage = 5;
	zombie.shotDelay = 0.0f;

	tank.type = weapon_set::type::tank;
	tank.current = 1;
	tank.damage = 5;
	tank.shotDelay = 0.0f;

	_vWeaponInfo.resize(6);

	_vWeaponInfo[weapon_set::type::none] = normalSet;
	_vWeaponInfo[weapon_set::type::rifle] = rifleSet;
	_vWeaponInfo[weapon_set::type::shotgun] = shotgunSet;
	_vWeaponInfo[weapon_set::type::healkit] = healkitSet;
	_vWeaponInfo[weapon_set::type::zombie] = zombie;
	_vWeaponInfo[weapon_set::type::tank] = tank;
}

weaponBase * weaponManager::createWeapon(int weaponType)
{
	weaponBase* result = nullptr;

	auto & weaponParam = _vWeaponParam[weaponType];
	auto player = SGT_GAME->getSet().player;

	switch (weaponType)
	{
	case weapon_set::type::rifle	: result = new weaponRifle(weaponParam, player); break;
	case weapon_set::type::shotgun	: result = new weaponShotgun(weaponParam, player, 1); break;
	case weapon_set::type::healkit	: result = new weaponHealkit(weaponParam, player); break;
	}

	result->getInfoWeapon() = _vWeaponInfo[weaponType];
	return result;
}
