#include "triggerFactory.h"

#include "managerList.h"

#include "staticMesh.h"
#include "triggerBase.h"

#include "player.h"
#include "weaponBase.h"

triggerBase * triggerFactory::createTrigger2type(int type, staticMesh* bindMesh)
{
	triggerBase* result = nullptr;

	switch (type)
	{
	case triggerBase::TYPE::SHOT_GUN : 
	case triggerBase::TYPE::MACHINE_GUN :
	case triggerBase::TYPE::MEDKIT : {

		result = new triggerBase(bindMesh);
		result->refTriggerType() = type;

		result->refActive() = [&](void)->void {
			auto & player = SGT_GAME->getSet().player;
			auto & weapon = type == triggerBase::TYPE::MEDKIT ?
				player->getWeaponSub() : player->getWeapon();

			if (weapon == nullptr)
				weapon = MN_WEAPON->createWeapon(type);
			else
				weapon->getInfoWeapon() = MN_WEAPON->getWeaponInfo(type);
		};

	} break;

	case triggerBase::TYPE::AIR_PLANE : {

	} break;

	default: { SAFE_DELETE(result); }
	}

	return result;
}
