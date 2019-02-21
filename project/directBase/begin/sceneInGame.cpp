#include "sceneInGame.h"

#include "managerList.h"

#include "sceneBase.h"
#include "debugGrid.h"

#include "inGameCamera.h"
#include "inGame_field.h"
#include "inGame_grape.h"

#include "eventDef.h"
#include "eventCatcher.h"
#include "eventBase.h"

#include "patternMesh.h"
#include "characterBase.h"
#include "player.h"

void sceneInGame::init(void)
{
	sceneBase::init();

	initResource();
	initSystem();
	initEvent();
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
}

void sceneInGame::initResource(void)
{
	// player
	patternMesh::mParam param;
	param.effectFilePath = "resource/effect/Survivor.fx";
	param.filePath = "resource/mesh/L4D1/Teenangst/teenangst.x";	MN_SRC->getPatternMesh("test", &param)->setScale(0.004f);

	// enemy
	param.filePath = "resource/mesh/L4D1/male/male.X";				MN_SRC->getPatternMesh("enemy_male_0", &param)->setScale(0.004f);
	param.filePath = "resource/mesh/L4D1/male/male1.X";				MN_SRC->getPatternMesh("enemy_male_1", &param)->setScale(0.004f);
	param.filePath = "resource/mesh/L4D1/female/female.X";			MN_SRC->getPatternMesh("enemy_female_0", &param)->setScale(0.004f);
}

void sceneInGame::initSystem(void)
{
	// player
	auto pCharacter = SGT_GAME->getSet().player = new player(MN_SRC->getPatternMesh("test"));
	
	pCharacter->getNextBit() =
		ATYPE_SURVIVOR |
		AWEAPON_RIFLE |
		ACONDITION_NORMAL |
		AMAIN_IDLE |
		AMIX_NONE |
		AIDLE_STANDING;

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


}
