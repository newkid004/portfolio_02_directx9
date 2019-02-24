#include "sceneInGame.h"

#include "managerList.h"
#include "gDigit.h"

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
#include "eEnemySpawner.h"
#include "eEndingComplet.h"

#include "patternMesh.h"
#include "player.h"
#include "enemyBase.h"

#include "mapObject.h"
#include "wallMesh.h"
#include "soundManager.h"


sceneInGame::~sceneInGame()
{
	for (int i = 0; i < 2; ++i)
	{
		SAFE_DELETE(_crosshair[i]);
	}
	SAFE_DELETE(_ui);
}

void sceneInGame::init(void)
{
	sceneBase::init();

	initResource();
	initSystem();
	initField();
	initEvent();
	initSound();
	initUI();

	MN_SND->find("inGameB")->play();
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
	// sceneBase::drawUI();

	_ui->draw();

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
	_crosshair[0]	= new spriteBase("resource/texture/UI/crosshair.png");
	_crosshair[1]	= new spriteBase("resource/texture/UI/crosshairShotgun.png");

	

}

void sceneInGame::initSystem(void)
{
	// player
	auto pCharacter = SGT_GAME->getSet().player = new player(MN_SRC->getPatternMesh("test"));
	MN_BULLET->setBindPlayer(pCharacter);
	pCharacter->getOriginMesh()->init();
	pCharacter->getOriginMesh()->setDebugEnable(true, EDebugDrawType::NONE);

	pCharacter->getNextBit() =
		ATYPE_SURVIVOR |
		AWEAPON_RIFLE |
		ACONDITION_NORMAL |
		AMAIN_IDLE |
		AMIX_NONE |
		AIDLE_STANDING;


	pCharacter->getWeapon() = MN_WEAPON->createWeapon(weapon_set::type::rifle);
	pCharacter->getInfoCharacter().maxHp = 100;
	pCharacter->getInfoCharacter().nowHp = 100;

	SAFE_DELETE(_camera);
	SAFE_DELETE(_grid);

	SGT_GAME->getSet().field->getMember().grape->putData(pCharacter, 3, pCharacter->getPosition(), pCharacter->getInfoCharacter().colRadius);

	// camera
	_camera = new inGameCamera(pCharacter);

	// status
	auto & sysStatus = SGT_GAME->getStatus();

}

void sceneInGame::initField(void)
{
	auto field = SGT_GAME->getSet().field;

	// make obj
	auto & mapObj = field->getMember().mapObject;
	mapObj = new mapObject();
	mapObj->init();

	// put enemy
	for (int i = 0; i < 5; ++i)
	{
		auto e = SGT_GAME->addEnemy();
		e->setPosition( D3DXVECTOR3(
			gFunc::rndFloat(-80.0f, 80.0f),
			0.0f,
			gFunc::rndFloat(-80.0f, 80.0f)));
	}
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

	eC[2] = new eventCatcher(
		EVENT::TYPE::CHARACTER |
		EVENT::KIND::CHARACTER::PLAYER |
		EVENT::ACT::CHARACTER::DEATH,
		[](eventBase* e)->void {

	},
		[](eventBase*)->void {}
	);

	initEventTrigger();
	initEventWeapon();
}

void sceneInGame::initEventTrigger(void)
{
	// wave 시작
	MN_EVENT->add(
		EVENT::TYPE::TRIGGER |
		EVENT::KIND::TRIGGER::AIR_PLANE |
		EVENT::ACT::TRIGGER::ACTIVE,
		[](eventBase*)->void {},
		[](eventBase*)->void {

		int & digitActive = SGT_GAME->getStatus().digitActive;
		if (!gDigit::chk(digitActive, sysDigit::wave))
		{
			gDigit::put(SGT_GAME->getStatus().digitActive, sysDigit::wave | sysDigit::enemySpawn);
			MN_EVENT->add(new eEnemySpawner());

			MN_SND->getBGM()->stop();
			MN_SND->find("waveStart")->play();
			MN_SND->find("buttonOn")->play();
		}
		else
		{
			MN_SND->find("buttonAlready")->play();
		}
	});

	// wave 끝
	MN_EVENT->add(
		EVENT::TYPE::TRIGGER |
		EVENT::KIND::TRIGGER::AIR_PLANE |
		EVENT::ACT::TRIGGER::COMPLETE,
		[](eventBase*)->void {},
		[](eventBase*)->void {

		MN_SCENE->change("sceneEnding");
		MN_EVENT->add(new eEndingComplet());

		SGT_GAME->getSet().player->getPosition() = SGT_GAME->getSet().airPlane->getPosition();
		SGT_GAME->getSet().airPlane->getNextBit() =
			ATYPE_AIRPLANE |
			AIRPLANE_OUTRO |
			AIRPLANE_OUTRO_NONE;

		MN_SND->find("Cfly")->play();
	});
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
		_crosshair[i]->setScale(0.3f);
	}

	_ui = new sceneUI();

}

void sceneInGame::initSound(void)
{
	//weapon
	MN_SND->addSound("rifleShoot", "resource/sound/weapon/rifle_fire.wav",false,false);//
	MN_SND->addSound("emptyClip", "resource/sound/weapon/clipempty.wav", false, false);//
	MN_SND->addSound("rClipIn", "resource/sound/weapon/rifle_clip_in_1.wav", false, false);//
	MN_SND->addSound("rClipOut", "resource/sound/weapon/rifle_clip_out_1.wav", false, false);//
	MN_SND->addSound("rDeploy", "resource/sound/weapon/rifle_deploy_1.wav", false, false);//
	MN_SND->addSound("rReady", "resource/sound/weapon/rifle_ready_1.wav", false, false);//
	MN_SND->addSound("shotgunShoot", "resource/sound/weapon/shotgun_fire.wav", false, false);//
	MN_SND->addSound("sDeploy", "resource/sound/weapon/shotgun_deploy_1.wav", false, false);//
	MN_SND->addSound("sLoadShell", "resource/sound/weapon/shotgun_load_shell_2.wav", false, false);//
	MN_SND->addSound("sPump", "resource/sound/weapon/shotgun_pump_1.wav", false, false);//


	//background
	MN_SND->addSound("clear", "resource/sound/background/clear.wav", true, false);
	MN_SND->addSound("deathB", "resource/sound/background/deathS.wav", true, true);
	MN_SND->addSound("inGameB", "resource/sound/background/inGameB.wav", true, true);//
	//MN_SND->addSound("tankB", "resource/sound/background/tank.wav", true, false);
	MN_SND->addSound("waveStart", "resource/sound/background/waveStart.wav", true, false);

	//footSound
	MN_SND->addSound("survivorF", "resource/sound/footSound/survivor/concrete1.wav",false,false); //
	MN_SND->addSound("commonF", "resource/sound/footSound/common/concrete3.wav",false,false); //?

	//survivor
	MN_SND->addSound("bandaging", "resource/sound/survivor/bandaging_1.wav", false, false);
	MN_SND->addSound("survivorDamage", "resource/sound/survivor/damage1.wav", false, false);//새거요망
	MN_SND->addSound("hitbyEnemey", "resource/sound/survivor/hordattack05.wav", false, false);//
	//MN_SND->addSound("incomingVoice", "resource/sound/survivor/incoming02.wav", false, false);
	MN_SND->addSound("hitEnemy", "resource/sound/survivor/rifle_swing_hit_infected9.wav", false, false);//
	MN_SND->addSound("hitWall", "resource/sound/survivor/rifle_swing_hit_world.wav", false, false);
	//MN_SND->addSound("survivorShoved", "resource/sound/survivor/shoved01.wav", false, false);
	MN_SND->addSound("swingWeapon", "resource/sound/survivor/swish_weaponswing_swipe3.wav", false, false);//
	MN_SND->addSound("takeRifle", "resource/sound/survivor/takeassaultrifle01.wav", false, false);//
	MN_SND->addSound("takeHealkit", "resource/sound/survivor/takefirstaid01.wav", false, false);//
	MN_SND->addSound("takeShotgun", "resource/sound/survivor/takeshotgun01.wav", false, false);//

	//terrainCollision
	MN_SND->addSound("shootWall", "resource/sound/terrain/concrete_impact_bullet1.wav", false, false);

	//airplane
	MN_SND->addSound("buttonAlready", "resource/airplane/terrain/alreadyOn.wav", false, false);
	MN_SND->addSound("buttonOn", "resource/sound/airplane/buttonOn.wav", false, false);
	MN_SND->addSound("CdoorOpen", "resource/sound/airplane/c130_door_open.wav", false, false);
	MN_SND->addSound("Cfly", "resource/sound/airplane/c130_flyby.wav", false, false);
	MN_SND->addSound("Cidle", "resource/sound/airplane/c130_idle.wav", false, true);

	//zombie
	MN_SND->addSound("alert_f", "resource/sound/zombie/alert_f.wav", false, false);//
	MN_SND->addSound("alert_m", "resource/sound/zombie/alert_m.wav", false, false);//
	MN_SND->addSound("been_shot_f", "resource/sound/zombie/been_shot_f.wav", false, false);//
	MN_SND->addSound("been_shot_m", "resource/sound/zombie/been_shot_m.wav", false, false);//
	MN_SND->addSound("breathing", "resource/sound/zombie/breathing08.wav", false, false);// 여자필요
	MN_SND->addSound("bullet_gib", "resource/sound/zombie/bullet_gib_06.wav", false, false);//
	MN_SND->addSound("claw_miss", "resource/sound/zombie/claw_miss_1.wav", false, false);//
	//MN_SND->addSound("claw_scrape", "resource/sound/zombie/claw_scrape_3.wav", false, false);
	MN_SND->addSound("death_f", "resource/sound/zombie/death_f.wav", false, false);//
	MN_SND->addSound("death_m", "resource/sound/zombie/death_m.wav", false, false);//
	MN_SND->addSound("headless", "resource/sound/zombie/headless_1.wav", false, false);//
	MN_SND->addSound("hit_punch", "resource/sound/zombie/hit_punch_05.wav", false, false);
	MN_SND->addSound("idle_breath", "resource/sound/zombie/idle_breath_02.wav", false, false);
	MN_SND->addSound("rage_run_f", "resource/sound/zombie/rage_run_f.wav", false, false);//
	MN_SND->addSound("rage_run_m", "resource/sound/zombie/rage_run_m.wav", false, false);//

}