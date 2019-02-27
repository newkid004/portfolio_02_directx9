#include "mainGame.h"

#include "managerList.h"

#include "sceneMapTool.h"
#include "sceneInGame.h"
#include "sceneEnding.h"

#include "sceneTest1.h"
#include "sceneTest2.h"
#include "sceneTest3.h"
#include "sceneTest4.h"
#include "sceneCollisionTest.h"
#include "AnimationTester.h"
#include "wallCollision.h"
#include "weaponTest.h"
#include "menuScene.h"
#include "deadScene.h"

void mainGame::init(void)
{
	direct3dApplication::init();
	_bindScene = &MN_SCENE->getCurrentScene();

	/*/	// current save

	/*/	// current
	MN_SCENE->add("menuScene", new menuScene());
	MN_SCENE->add("sceneInGame", new sceneInGame());
	MN_SCENE->add("sceneMapTool", new sceneMapTool());
	MN_SCENE->add("deadScene", new deadScene());
	MN_SCENE->add("sceneEnding", new sceneEnding());

	MN_SCENE->change("menuScene");
}

void mainGame::update(void)
{
	if (*_bindScene != nullptr) (*_bindScene)->update();
}

void mainGame::draw(void)
{
	if (*_bindScene != nullptr) (*_bindScene)->draw();
}

void mainGame::drawUI(void)
{
	if (*_bindScene != nullptr) (*_bindScene)->drawUI();
}
