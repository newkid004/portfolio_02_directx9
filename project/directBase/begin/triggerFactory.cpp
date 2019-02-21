#include "triggerFactory.h"

#include "managerList.h"

#include "staticMesh.h"
#include "triggerBase.h"

#include "player.h"
#include "weaponBase.h"
#include "AnimationDef.h"

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

		result->refActive() = [&](triggerBase* own)->void {
			auto & player = SGT_GAME->getSet().player;
			auto & weapon = own->refTriggerType() == triggerBase::TYPE::MEDKIT ?
				player->getWeaponSub() : player->getWeapon();

			if (weapon == nullptr || weapon->getInfoWeapon().type != own->refTriggerType())
			{
				SAFE_DELETE(weapon);
				weapon = MN_WEAPON->createWeapon(own->refTriggerType());
				//CHANGE_BIT(player->getNextBit(), aniDefine::ANIBIT::WEAPON, type*16);
			}
			else
				weapon->getInfoWeapon() = MN_WEAPON->getWeaponInfo(own->refTriggerType());
		};

	} break;

	case triggerBase::TYPE::AIR_PLANE : {

	} break;

	default: { SAFE_DELETE(result); }
	}

	return result;
}
