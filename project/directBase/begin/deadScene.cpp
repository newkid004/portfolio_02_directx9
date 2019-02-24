#include "deadScene.h"
#include "spriteBase.h"
#include "managerList.h"
#include "gFunc.h"

deadScene::~deadScene()
{
	SAFE_DELETE(_backGround);
}

void deadScene::init(void)
{
	sceneBase::init();
	initResource();
	initSetting();
	MN_SND->find("deathB")->play();
}

void deadScene::update(void)
{
}

void deadScene::draw(void)
{
}

void deadScene::drawUI(void)
{
	_backGround->drawUI();
}

void deadScene::initResource(void)
{
	_backGround = new spriteBase("resource/texture/scene/menu2.jpg");
}

void deadScene::initSetting(void)
{
	D3DXVECTOR2 windowCenter = D3DXVECTOR2(MN_WIN->getWindowSize().cx / 2.0f,
		MN_WIN->getWindowSize().cy / 2.0f);

	LPDIRECT3DTEXTURE9 texture = MN_SRC->getSpriteTexture("resource/texture/scene/menu2.jpg");
	D3DXVECTOR2 backSize;
	gFunc::getTextureSize(&backSize, texture);
	_backGround->setPosition(D3DXVECTOR3(windowCenter.x,
		windowCenter.y,0.0f));
	_backGround->setScale(D3DXVECTOR3(MN_WIN->getWindowSize().cx/backSize.x,
		MN_WIN->getWindowSize().cy / backSize.y, 0.0f));
}
