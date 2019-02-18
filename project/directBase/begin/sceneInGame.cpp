#include "sceneInGame.h"
#include "eventCatcher.h"
#include "eventBase.h"
#include "characterBase.h"
#include "managerList.h"

sceneInGame::sceneInGame()
{
}

sceneInGame::~sceneInGame()
{
}

void sceneInGame::init(void)
{
	sceneBase::init();
	initEvent();
}

void sceneInGame::update(void)
{
	sceneBase::update();
}

void sceneInGame::draw(void)
{
	sceneBase::draw();
}

void sceneInGame::drawUI(void)
{
	sceneBase::drawUI();
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
	//	((characterBase*)e->getDest())->moveX(((characterBase*)e->getDest())->½ºÇÇµå);
	//};

	MN_EVENT->getEventCatcherArray(eC[0]->getParam()).push_back(eC[0]);

	eC[1] = new eventCatcher();
	eC[1]->getParam() = makeDestParam(
		ET_CHARACTER |
		EK_CHARACTER_PLAYER |
		EA_CHARACTER_WALK |
		EC_PLAYER_STATE_CHANGE_DECREASE);

}
