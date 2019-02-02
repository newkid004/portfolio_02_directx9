#include "sceneBase.h"

#include "managerList.h"

#include "cameraControlable.h"
#include "debugGrid.h"
#include "debugGizmo.h"
#include "lightBase.h"
#include "labelBase.h"
#include "spriteBase.h"

sceneBase::sceneBase() :
	direct3dApplication(
		MN_WIN->getHInstance(),
		MN_WIN->getWindowSize(),
		0)
{
}

void sceneBase::init(void)
{
	createMember();
}

void sceneBase::update(void)
{
	direct3dApplication::update();
}

void sceneBase::draw(void)
{
	direct3dApplication::draw();
}

void sceneBase::drawUI(void)
{
	direct3dApplication::drawUI();
}

