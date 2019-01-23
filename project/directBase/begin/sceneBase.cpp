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
	_camera = new cameraControlable(MN_WIN->getAspect(), 60.0f, 1000.0f);
	_camera->setPosition(D3DXVECTOR3(0, 0, -5));

	_grid = new debugGrid(50);
	_grid->setPosition(D3DXVECTOR3(0, 0, 0));
	_grid->addChild(new debugGizmo(12.0f));

	_light = new lightBase(0);
	_light->setPosition(D3DXVECTOR3(0.0f, 0.0f, -5.0f));
	_light->setRotation(D3DXVECTOR3(45.0f, 0.0f, 0.0f));
	_light->setLightable(true);

	_label = new labelBase("", 16.0f);
	_label->setPosition(D3DXVECTOR3(1, 1, 0));

	_sprite = createSprite();
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

