#include "sceneTest3.h"

#include "managerList.h"

#include "patternMesh.h"
#include "characterBase.h"
#include "controllerBase.h"


void sceneTest3::init(void)
{
	sceneBase::init();

	_origin = createCharacter();
	_origin->setScale(0.02f);
	_origin->rotateX(180.0f);

	_char = new characterBase(_origin);
	_char->setController(new controllerBase(_char));
	_char->getNextBit() = ATYPE_SURVIVOR |
		AWEAPON_RIFLE |
		ACONDITION_NORMAL |
		AMAIN_IDLE |
		AMIX_NONE |
		AIDLE_STANDING;
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

patternMesh * sceneTest3::createCharacter(void)
{
	patternMesh::mParam param;
	param.effectFilePath = "resource/effect/Survivor.fx";
	param.filePath = "resource/mesh/L4D1/Teenangst/teenangst.x";

	return new patternMesh(param);
}
