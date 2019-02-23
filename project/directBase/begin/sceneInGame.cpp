#include "sceneInGame.h"

#include "managerList.h"

#include "sceneBase.h"
#include "debugGrid.h"

#include "inGameCamera.h"
#include "inGame_field.h"
#include "inGame_grape.h"

#include "weaponBase.h"

#include "eventDef.h"
#include "eventCatcher.h"
#include "eventBase.h"
#include "eShootWeapon.h"

#include "patternMesh.h"
#include "player.h"

#include "mapObject.h"
#include "wallMesh.h"

sceneInGame::~sceneInGame()
{
	for (int i = 0; i < 2; ++i)
	{
		SAFE_DELETE(_crosshair[i]);
	}
}

void sceneInGame::init(void)
{
	sceneBase::init();

	initResource();
	initSystem();
	initField();
	initEvent();
	initUI();
}

void sceneInGame::update(void)
{
	sceneBase::update();

	SGT_GAME->update();
	GET_BULLET_MANAGER()->update();

	MN_EVENT->update();
}

void sceneInGame::draw(void)
{
	sceneBase::draw();

	SGT_GAME->draw();
	GET_BULLET_MANAGER()->draw();

	MN_EVENT->draw();
}

void sceneInGame::drawUI(void)
{
	sceneBase::drawUI();

	//crosshair
	switch (SGT_GAME->getSet().player->getWeapon()->getInfoWeapon().type)
	{
	case weapon_set::type::rifle:
	case weapon_set::type::shotgun:
		_crosshair[SGT_GAME->getSet().player->getWeapon()->getInfoWeapon().type - 1]->drawUI();
		break;
	}
}

void sceneInGame::initResource(void)
{
	// player
	patternMesh::mParam param;
	param.effectFilePath = "resource/effect/Survivor.fx";
	param.filePath = "resource/mesh/L4D1/Teenangst/teenangst.x";	MN_SRC->getPatternMesh("test", &param)->setScale(0.004f);

	// enemy
	param.effectFilePath = "resource/effect/zombie.fx";
	param.filePath = "resource/mesh/L4D1/male/male.X";				MN_SRC->getPatternMesh("enemy_male_0", &param)->setScale(0.004f);
	param.filePath = "resource/mesh/L4D1/female/female.X";			MN_SRC->getPatternMesh("enemy_female_0", &param)->setScale(0.004f);

	//UI
	_crosshair[0] = new spriteBase("resource/texture/UI/crosshair.png");
	_crosshair[1] = new spriteBase("resource/texture/UI/crosshairShotgun.png");
}

void sceneInGame::initSystem(void)
{
	// player
	auto pCharacter = SGT_GAME->getSet().player = new player(MN_SRC->getPatternMesh("test"));
	MN_BULLET->setBindPlayer(pCharacter);
	pCharacter->getOriginMesh()->init();
	pCharacter->getOriginMesh()->setDebugEnable(true, EDebugDrawType::SPHERE);

	pCharacter->getNextBit() =
		ATYPE_SURVIVOR |
		AWEAPON_RIFLE |
		ACONDITION_NORMAL |
		AMAIN_IDLE |
		AMIX_NONE |
		AIDLE_STANDING;


	pCharacter->getWeapon() = MN_WEAPON->createWeapon(weapon_set::type::rifle);

	SAFE_DELETE(_camera);
	SAFE_DELETE(_grid);

	SGT_GAME->getSet().field->getMember().grape->putData(pCharacter, 3, pCharacter->getPosition(), pCharacter->getInfoCharacter().colRadius);

	// camera
	_camera = new inGameCamera(pCharacter);

	// cursur
	// ShowCursor(NULL);

	//
	SGT_GAME->addEnemy();
}

void sceneInGame::initField(void)
{
	auto field = SGT_GAME->getSet().field;

	// make obj
	auto & mapObj = field->getMember().mapObject;
	mapObj = new mapObject();
	mapObj->init();

	// put obj
	
}

void sceneInGame::initEvent(void)
{
	eventCatcher* eC[10];
	eC[0] = new eventCatcher();
	eC[0]->getParam() = makeDestParam(
		ET_CHARACTER |
		EK_CHARACTER_PLAYER |
		EA_CHARACTER_WALK |
		EC_PLAYER_STATE_CHANGE_INCREASE);

	//eC[0]->getAfterActive() = [this](eventBase* e)->void {
	//	((characterBase*)e->getDest())->moveX(((characterBase*)e->getDest())->스피드);
	//};

	MN_EVENT->getEventCatcherArray(eC[0]->getParam()).push_back(eC[0]);

	eC[1] = new eventCatcher();
	eC[1]->getParam() = makeDestParam(
		ET_CHARACTER |
		EK_CHARACTER_PLAYER |
		EA_CHARACTER_WALK |
		EC_PLAYER_STATE_CHANGE_DECREASE);

	// < trigger >
	// 비행기 시간 완료
	MN_EVENT->add(
		EVENT::TYPE::TRIGGER |
		EVENT::KIND::TRIGGER::AIR_PLANE |
		EVENT::ACT::TRIGGER::COMPLETE,
		[](eventBase*)->void {},
		[](eventBase*)->void {

		// do shomthing
	} );

	initEventWeapon();
}

void sceneInGame::initEventWeapon(void)
{
	// 무기 발사 시
	MN_EVENT->add(
		EVENT::TYPE::WEAPON |
		EVENT::ACT::WEAPON::SHOOT,
		[](eventBase*)->void {},
		[](eventBase* e)->void {

		int eParam =
			EVENT::TYPE::WEAPON |
			EVENT::ACT::WEAPON::SHOOT;

		auto own = static_cast<characterBase*>(e->getSour());
		int weaponType = own->getWeapon()->getInfoWeapon().type;

		switch (weaponType)
		{
		case weapon_set::type::shotgun:	eParam |= EVENT::KIND::WEAPON::SHOTGUN;	break;
		case weapon_set::type::rifle:	eParam |= EVENT::KIND::WEAPON::RIFLE;	break;
		}

		MN_EVENT->add(new eShootWeapon(e->getSour(), eParam));

	});
}

void sceneInGame::initUI(void)
{
	for (int i = 0; i < 2; ++i)
	{
		_crosshair[i]->setPosition(D3DXVECTOR3(MN_WIN->getWindowSize().cx / 2.0f,
			MN_WIN->getWindowSize().cy / 2.0f, 0.0f));
	}
	_crosshair[0]->setScale(0.5f);
	_crosshair[1]->setScale(0.5f);
}

void sceneInGame::initSound(void)
{

}
