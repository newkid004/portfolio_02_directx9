#include "sceneUI.h"
#include "managerList.h"
#include "player.h"
#include "weaponBase.h"
#include "gFunc.h"

sceneUI::sceneUI()
{
	initResource();
	initUI();
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

	_hpBarBg->drawUI();
	_hpFont->drawUI();
	_profile->drawUI();

	//주무기의 현재/전체 탄환수
	D3DXVECTOR2 &winCen = D3DXVECTOR2(MN_WIN->getWindowSize().cx / 2.0f, MN_WIN->getWindowSize().cy / 2.0f);
	D3DXVECTOR2 position = D3DXVECTOR2(winCen.x+510.0f, winCen.y-50.0f);
	drawNumber(_number[0], SGT_GAME->getSet().player->getWeapon()->getInfoWeapon().current, position,D3DXVECTOR2(1.2f,1.2f));
	position.x += 60.0f;
	position.y += 10.0f;
	drawNumber(_number[1], SGT_GAME->getSet().player->getWeapon()->getInfoWeapon().maximum, position, D3DXVECTOR2(0.9f, 0.9f));

	//체력 퍼센트
	float persent = (float)SGT_GAME->getSet().player->getInfoCharacter().nowHp / (float)SGT_GAME->getSet().player->getInfoCharacter().maxHp;
	LPDIRECT3DTEXTURE9 hp;

	//체력 숫자
	if (persent < 0.3f)		hp = _number[4];
	else if (persent <0.6f)	hp = _number[3];
	else					hp = _number[2];
	position = D3DXVECTOR2(winCen.x + 420.0f, winCen.y + 280.0f);
	drawNumber(hp, SGT_GAME->getSet().player->getInfoCharacter().nowHp,position,D3DXVECTOR2(1.3f,1.3f));

	//체력 바
	D3DXVECTOR2 size;
	gFunc::getTextureSize(&size, _hpBar[0]);
	size.x = size.x * persent;
	D3DXVECTOR2 scale = D3DXVECTOR2(1.75f, 2.1f);
	size.x *= scale.x;
	size.y *= scale.y;
	if (persent < 0.3f)		hp	=	_hpBar[2];
	else if(persent <0.6f)	hp	=	_hpBar[1];
	else					hp	=	_hpBar[0];
	gFunc::drawSprite(hp,
		D3DXVECTOR2(winCen.x + 380, winCen.y + 326),
		size,
		scale);
}

void sceneUI::initResource(void)
{
	_itemSlot[0] = new spriteBase("resource/texture/UI/itemSlot_gun.png");
	_itemSlot[1] = new spriteBase("resource/texture/UI/itemSlot_healkit.png");
	_m16[0] = new spriteBase("resource/texture/UI/m16.png");
	_m16[1] = new spriteBase("resource/texture/UI/m16_off.png");
	_shotGun[0] = new spriteBase("resource/texture/UI/shotGun.png");
	_shotGun[1] = new spriteBase("resource/texture/UI/shotGun_off.png");
	_healKit[0] = new spriteBase("resource/texture/UI/healKit.png");
	_healKit[1] = new spriteBase("resource/texture/UI/healKit_off.png");
	_hpBarBg = new spriteBase("resource/texture/UI/hpBar.png");
	_hpFont = new spriteBase("resource/texture/UI/hp.png");
	_profile = new spriteBase("resource/texture/UI/survivor.tga");

	_number[0] = MN_SRC->getSpriteTexture("resource/texture/UI/number.png");
	_number[1] = MN_SRC->getSpriteTexture("resource/texture/UI/number2.png");
	_number[2] = MN_SRC->getSpriteTexture("resource/texture/UI/number3.png");
	_number[3] = MN_SRC->getSpriteTexture("resource/texture/UI/number4.png");
	_number[4] = MN_SRC->getSpriteTexture("resource/texture/UI/number5.png");

	_hpBar[0] = MN_SRC->getSpriteTexture("resource/texture/UI/hp_full.png");
	_hpBar[1] = MN_SRC->getSpriteTexture("resource/texture/UI/hp_full2.png");
	_hpBar[2] = MN_SRC->getSpriteTexture("resource/texture/UI/hp_full3.png");
}

void sceneUI::initUI(void)
{
	D3DXVECTOR2 winCen = D3DXVECTOR2(MN_WIN->getWindowSize().cx/2.0f, MN_WIN->getWindowSize().cy/2.0f);

	// INVENTORY
	_m16[0]->setScale(1.2f);
	_m16[1]->setScale(1.2f);
	_m16[0]->setPosition(D3DXVECTOR3(winCen.x  + 560,
		winCen.y  - 65, 0.0f));
	_m16[1]->setPosition(D3DXVECTOR3(winCen.x  + 560,
		winCen.y  - 65, 0.0f));

	_shotGun[0]->setScale(1.2f);
	_shotGun[1]->setScale(1.2f);
	_shotGun[0]->setPosition(D3DXVECTOR3(winCen.x  + 560,
		winCen.y  - 65, 0.0f));
	_shotGun[1]->setPosition(D3DXVECTOR3(winCen.x  + 560,
		winCen.y  - 65, 0.0f));

	_healKit[0]->setPosition(D3DXVECTOR3(winCen.x  + 605,
		winCen.y  + 50, 0.0f));
	_healKit[0]->setScale(1.3f);
	_healKit[1]->setPosition(D3DXVECTOR3(winCen.x  + 605,
		winCen.y  + 50, 0.0f));
	_healKit[1]->setScale(1.3f);

	// INVENSLOT
	_itemSlot[0]->setPosition(D3DXVECTOR3(winCen.x  + 560,
		winCen.y  - 35, 0.0f));
	_itemSlot[0]->setScale(1.3f);

	_itemSlot[1]->setPosition(D3DXVECTOR3(winCen.x  + 605,
		winCen.y  + 50, 0.0f));
	_itemSlot[1]->setScale(1.3f);

	// HP BAR
	_hpBarBg->setPosition(D3DXVECTOR3(winCen.x  + 500,
		winCen.y  + 336, 0.0f));
	_hpBarBg->setScale(1.7f);

	_hpFont->setPosition(D3DXVECTOR3(winCen.x  + 400,
		winCen.y  + 295, 0.0f));
	_hpFont->setScale(2.2f);

	_profile->setPosition(D3DXVECTOR3(winCen.x  + 335,
		winCen.y  + 310, 0.0f));
	_profile->setScale(1.1f);
}

void sceneUI::drawNumber(LPDIRECT3DTEXTURE9 texture, int num, D3DXVECTOR2 position, D3DXVECTOR2 scale)
{
	std::vector<int> numberSlot;
	for (int i = 0; ; i++)
	{
		int number;
		if (i == 0)
		{
			numberSlot.push_back(num % 10);
		}
		else
		{
			number = (num / (10 * (int)pow(10, (i - 1)))) % 10;
			int upNum = (num / (10 * (int)pow(10, (i)))) % 10;
			if (number == 0 && upNum == 0) break;
			numberSlot.push_back(number);
		}
	}

	D3DXVECTOR2 size;
	gFunc::getTextureSize(&size, texture);
	size.x /= 10.0f;


	for (int i = 0; i < numberSlot.size(); ++i)
	{
		gFunc::drawSprite(texture,
			D3DXVECTOR2(position.x + (size.x-5) * scale.x*i,position.y),
			size*scale.x,
			scale,
			1.0f,
			&D3DXVECTOR2(size.x*scale.x*numberSlot[numberSlot.size()-1-i], 0.0f));
	}
}

