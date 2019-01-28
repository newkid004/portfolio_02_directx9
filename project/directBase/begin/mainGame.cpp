#include "mainGame.h"

#include "managerList.h"

#include "sceneTest1.h"
#include "sceneTest2.h"
#include "sceneMapTool.h"

void mainGame::init(void)
{
	direct3dApplication::init();
	_bindScene = &MN_SCENE->getCurrentScene();

	MN_SCENE->add("scene1", new sceneTest1);
	MN_SCENE->add("scene2", new sceneTest2);
	MN_SCENE->add("sceneMapTool", new sceneMapTool);

	MN_SCENE->change("scene1");
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
