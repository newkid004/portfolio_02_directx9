#include "mainGame.h"

#include "managerList.h"

#include "sceneMapTool.h"
#include "sceneInGame.h"

#include "sceneTest1.h"
#include "sceneTest2.h"
#include "sceneTest3.h"
#include "sceneTest4.h"
#include "sceneCollisionTest.h"
#include "AnimationTester.h"
#include "wallCollision.h"
#include "weaponTest.h"
#include "menuScene.h"

void mainGame::init(void)
{
	direct3dApplication::init();
	_bindScene = &MN_SCENE->getCurrentScene();

	/*/	// current save
	MN_SCENE->add("menuScene", new menuScene());
	MN_SCENE->add("sceneInGame", new sceneInGame());

	/*/	// current
	MN_SCENE->add("sceneMapTool", new sceneMapTool());

	/*/ // test complete
	MN_SCENE->add("scene1", new sceneTest1);			// json
	MN_SCENE->add("scene2", new sceneTest2);			// a* node
	MN_SCENE->add("scene3", new sceneTest3);			// character
	MN_SCENE->add("scene4", new sceneTest4());			// particle

	/*/ // test current

	/*/ // test save
	MN_SCENE->add("sceneCollisionTest", new sceneCollisionTest);
	MN_SCENE->add("animation", new AnimationTester);
	MN_SCENE->add("wallC", new wallCollision);

	MN_SCENE->add("weaponT", new weaponTest);

	//*/

	MN_SCENE->change("sceneMapTool");
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
