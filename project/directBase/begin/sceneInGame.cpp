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
}

void sceneInGame::draw(void)
{
	sceneBase::draw();

	SGT_GAME->draw();
}

void sceneInGame::drawUI(void)
{
	sceneBase::drawUI();
}

void sceneInGame::initResource(void)
{
	patternMesh::mParam param;
	param.effectFilePath = "resource/effect/Survivor.fx";
	param.filePath = "resource/mesh/L4D1/Teenangst/teenangst.x";

	MN_SRC->getPatternMesh("test", &param);
}

void sceneInGame::initSystem(void)
{
	// player
	auto pCharacter = SGT_GAME->getSet().player = new player(MN_SRC->getPatternMesh("test"));

	SAFE_DELETE(_camera);
	SAFE_DELETE(_grid);

	SGT_GAME->getSet().field->getMember().grape->putData(pCharacter, 3, pCharacter->getPosition(), pCharacter->getInfoCharacter().colRadius);

	// camera
	_camera = new inGameCamera(pCharacter);

	// cursur
	ShowCursor(NULL);
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
