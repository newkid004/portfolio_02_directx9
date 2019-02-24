#include "sceneUI.h"
#include "managerList.h"


sceneUI::sceneUI()
{
	_number[0] = new spriteBase("resource/texture/UI/number.png");
	_number[1] = new spriteBase("resource/texture/UI/number2.png");
	_itemSlot[0] = new spriteBase("resource/texture/UI/itemSlot_gun.png");
	_itemSlot[1] = new spriteBase("resource/texture/UI/itemSlot_healkit.png");
	_m16[0] = new spriteBase("resource/texture/UI/m16.png");
	_m16[1] = new spriteBase("resource/texture/UI/m16_off.png");
	_shotGun[0] = new spriteBase("resource/texture/UI/shotGun.png");
	_shotGun[1] = new spriteBase("resource/texture/UI/shotGun_off.png");
	_healKit[0] = new spriteBase("resource/texture/UI/healKit.png");
	_healKit[1] = new spriteBase("resource/texture/UI/healKit_off.png");
	_hpBarBg = new spriteBase("resource/texture/UI/hpBar.png");
	_hpBar = new spriteBase("resource/texture/UI/hp_full.png");
	_hpFont = new spriteBase("resource/texture/UI/hp.png");
	_profile = new spriteBase("resource/texture/UI/survivor.tga");
}

sceneUI::~sceneUI()
{
	SAFE_DELETE(_number[0]);
	SAFE_DELETE(_number[1]);
	SAFE_DELETE(_m16[0]);
	SAFE_DELETE(_m16[1]);
	SAFE_DELETE(_shotGun[0]);
	SAFE_DELETE(_shotGun[1]);
	SAFE_DELETE(_healKit[0]);
	SAFE_DELETE(_healKit[1]);
	SAFE_DELETE(_itemSlot[0]);
	SAFE_DELETE(_itemSlot[1]);
	SAFE_DELETE(_hpBarBg);
	SAFE_DELETE(_hpBar);
	SAFE_DELETE(_hpFont);
	SAFE_DELETE(_profile);
}

void sceneUI::update(void)
{
}

void sceneUI::draw(void)
{
	// Inventory

	_itemSlot[0]->drawUI();
	_itemSlot[1]->drawUI();

	switch (SGT_GAME->getSet().player->getWeapon()->getInfoWeapon().type)
	{
	case weapon_set::type::rifle:
	{
		_m16[0]->drawUI();
		_healKit[1]->drawUI();
	}
	case weapon_set::type::shotgun:
	{
		_shotGun[0]->drawUI();
		_healKit[1]->drawUI();
		break;
	}
	case weapon_set::type::healkit:
	{
		_m16[1]->drawUI();
		_healKit[0]->drawUI();
		break;
	}
	}
	_number[0]->drawUI();
	_number[1]->drawUI();

	_hpBarBg->drawUI();
	_hpBar->drawUI();
	_hpFont->drawUI();
	_profile->drawUI();
}

void sceneUI::initUI(void)
{
	// NUMBER
	_number[0]->setPosition(D3DXVECTOR3(MN_WIN->getWindowSize().cx / 2.0f + 560,
		MN_WIN->getWindowSize().cy / 2.0f - 55, 0.0f));
	_number[0]->setScale(1.5f);
	_number[1]->setPosition(D3DXVECTOR3(MN_WIN->getWindowSize().cx / 2.0f + 560,
		MN_WIN->getWindowSize().cy / 2.0f - 55, 0.0f));
	_number[1]->setScale(1.5f);

	// INVENTORY
	_m16[0]->setPosition(D3DXVECTOR3(MN_WIN->getWindowSize().cx / 2.0f + 560,
		MN_WIN->getWindowSize().cy / 2.0f - 55, 0.0f));
	_m16[1]->setPosition(D3DXVECTOR3(MN_WIN->getWindowSize().cx / 2.0f + 560,
		MN_WIN->getWindowSize().cy / 2.0f - 55, 0.0f));

	_shotGun[0]->setPosition(D3DXVECTOR3(MN_WIN->getWindowSize().cx / 2.0f + 560,
		MN_WIN->getWindowSize().cy / 2.0f - 55, 0.0f));
	_shotGun[1]->setPosition(D3DXVECTOR3(MN_WIN->getWindowSize().cx / 2.0f + 560,
		MN_WIN->getWindowSize().cy / 2.0f - 55, 0.0f));

	_healKit[0]->setPosition(D3DXVECTOR3(MN_WIN->getWindowSize().cx / 2.0f + 605,
		MN_WIN->getWindowSize().cy / 2.0f + 50, 0.0f));
	_healKit[0]->setScale(1.3f);
	_healKit[1]->setPosition(D3DXVECTOR3(MN_WIN->getWindowSize().cx / 2.0f + 605,
		MN_WIN->getWindowSize().cy / 2.0f + 50, 0.0f));
	_healKit[1]->setScale(1.3f);

	// INVENSLOT
	_itemSlot[0]->setPosition(D3DXVECTOR3(MN_WIN->getWindowSize().cx / 2.0f + 560,
		MN_WIN->getWindowSize().cy / 2.0f - 35, 0.0f));
	_itemSlot[0]->setScale(1.3f);

	_itemSlot[1]->setPosition(D3DXVECTOR3(MN_WIN->getWindowSize().cx / 2.0f + 605,
		MN_WIN->getWindowSize().cy / 2.0f + 50, 0.0f));
	_itemSlot[1]->setScale(1.3f);

	// HP BAR
	_hpBarBg->setPosition(D3DXVECTOR3(MN_WIN->getWindowSize().cx / 2.0f + 500,
		MN_WIN->getWindowSize().cy / 2.0f + 336, 0.0f));
	_hpBarBg->setScale(1.7f);
	_hpBar->setPosition(D3DXVECTOR3(MN_WIN->getWindowSize().cx / 2.0f + 500,
		MN_WIN->getWindowSize().cy / 2.0f + 336, 0.0f));
	_hpBar->setScale(1.7f);
	_hpFont->setPosition(D3DXVECTOR3(MN_WIN->getWindowSize().cx / 2.0f + 400,
		MN_WIN->getWindowSize().cy / 2.0f + 280, 0.0f));
	_hpFont->setScale(2.2f);

	_profile->setPosition(D3DXVECTOR3(MN_WIN->getWindowSize().cx / 2.0f + 335,
		MN_WIN->getWindowSize().cy / 2.0f + 310, 0.0f));
	_profile->setScale(1.1f);
}

