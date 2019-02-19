#include "player.h"

#include "managerList.h"

#include "sceneBase.h"
#include "camera.h"

#include "playerController.h"

player::player(patternMesh* duplicateTarget) :
	survivorBase(duplicateTarget)
{
	setController(new playerController(this));

}

player::~player()
{
}