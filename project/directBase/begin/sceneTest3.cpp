#include "sceneTest3.h"

#include "managerList.h"

#include "inGame_grape.h"
#include "inGame_field.h"

#include "patternMesh.h"
#include "characterBase.h"
#include "controllerBase.h"

#include "player.h"

void sceneTest3::init(void)
{
	sceneBase::init();

	// char
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

	SGT_GAME->getSet().player = (player*)_char;
	_char->getPlacedNode() = SGT_GAME->getSet().field->getMember().grape->getNodeList()[0];
}

void sceneTest3::update(void)
{
	sceneBase::update();
	
	D3DXVECTOR3 dirMove(0, 0, 0);

	if (MN_KEY->keyDown(DIK_UP))		dirMove.z += 1.0f;
	if (MN_KEY->keyDown(DIK_DOWN))		dirMove.z -= 1.0f;
	if (MN_KEY->keyDown(DIK_LEFT))		dirMove.x -= 1.0f;
	if (MN_KEY->keyDown(DIK_RIGHT))		dirMove.x += 1.0f;

	if (dirMove.x || dirMove.z)
		_char->moveDo(dirMove);

	_char->update();
	SGT_GAME->update();
}

void sceneTest3::draw(void)
{
	sceneBase::draw();

	queue<int> a;
	a.back

	_char->draw();
	SGT_GAME->draw();
}

patternMesh * sceneTest3::createCharacter(void)
{
	patternMesh::mParam param;
	param.effectFilePath = "resource/effect/Survivor.fx";
	param.filePath = "resource/mesh/L4D1/Teenangst/teenangst.x";

	return new patternMesh(param);
}
