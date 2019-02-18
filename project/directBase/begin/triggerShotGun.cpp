#include "triggerShotGun.h"

#include "managerList.h"

#include "inGame_struct.h"

#include "weaponBase.h"

#include "player.h"

triggerShotGun::triggerShotGun(staticMesh * bindMesh) : 
	triggerBase(bindMesh)
{
	_active = [&](void)->void {
		auto & player = SGT_GAME->getSet().player;
		auto & weapon = player->getWeapon()->getInfoWeapon();

		weapon = ((weaponBase*)_bindMesh)->getInfoWeapon();
	};
}
