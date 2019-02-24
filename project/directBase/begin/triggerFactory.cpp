#include "triggerFactory.h"

#include "managerList.h"

#include "staticMesh.h"
#include "triggerBase.h"

#include "player.h"
#include "weaponBase.h"
#include "AnimationDef.h"
#include "soundManager.h"

#include "eventBase.h"

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
				CHANGE_BIT(SGT_GAME->getSet().player->getNextBit(),
					aniDefine::ANIBIT::WEAPON, own->refTriggerType() * 0x10);
				if (own->refTriggerType() == triggerBase::TYPE::MACHINE_GUN)
				{
					MN_SND->find("rDeploy")->play();
					MN_SND->find("takeRifle")->play();
				}
				else if (own->refTriggerType() == triggerBase::TYPE::SHOT_GUN)
				{
					MN_SND->find("sDeploy")->play();
					MN_SND->find("takeShotgun")->play();
				}
				else
				{
					MN_SND->find("takeHealkit")->play();
				}
			}
			else
				weapon->getInfoWeapon() = MN_WEAPON->getWeaponInfo(own->refTriggerType());
		};

	} break;

	case triggerBase::TYPE::RADIO : {

		result = new triggerBase(bindMesh);
		result->refTriggerType() = type;

		result->refActive() = [&](triggerBase* own)->void {

			MN_EVENT->add(new eventBase(nullptr, nullptr,
				EVENT::TYPE::TRIGGER |
				EVENT::KIND::TRIGGER::AIR_PLANE |
				EVENT::ACT::TRIGGER::ACTIVE));
		};

	} break;

	}

	return result;
}
