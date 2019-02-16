#include "sceneTest3.h"

#include "managerList.h"

#include "characterBase.h"
#include "controllerBase.h"

void sceneTest3::init(void)
{
	sceneBase::init();

	_char = createCharacter();
	_char->setController(new controllerBase(_char));
}

void sceneTest3::update(void)
{
	sceneBase::update();

	_char->update();
}

void sceneTest3::draw(void)
{
	sceneBase::draw();

	_char->draw();
}

characterBase * sceneTest3::createCharacter(void)
{
	characterBase::mParam param;
	param.effectFilePath = "resource/effect/Survivor.fx";
	param.filePath = "resource/mesh/L4D1/Teenangst/teenangst.x";

	return new characterBase(param);
}
