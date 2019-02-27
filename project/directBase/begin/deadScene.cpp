#include "deadScene.h"
#include "spriteBase.h"
#include "managerList.h"
#include "gFunc.h"

deadScene::~deadScene()
{
	SAFE_DELETE(_backGround);
	SAFE_DELETE(_died);
}

void deadScene::init(void)
{
	sceneBase::init();
	initResource();
	initSetting();
	_type = 0;
	_downColor = 255;
}

void deadScene::update(void)
{
	if (_type == 0)
	{
		for (int i = 0; i < 2; ++i)
		{
			_hand[i].position.y -= 70.0f*MN_TIME->getDeltaTime();
		}
		if (_hand[0].position.y < 0) _type = 1;
	}
	else
	{
		_hand[1].position.y += 30.0f*MN_TIME->getDeltaTime();
		_hand[0].scale.y += 0.04f*MN_TIME->getDeltaTime();
		
		_downColor = max(0, _downColor - 10.0f*MN_TIME->getDeltaTime());

		_backGround->setColor(D3DCOLOR_ARGB(255, 255, (int)_downColor, (int)_downColor));
		_died->setColor(D3DCOLOR_ARGB(300 - (int)_downColor, 270 - (int)_downColor, 270 - (int)_downColor, 270 - (int)_downColor));
	}
}

void deadScene::draw(void)
{

}

void deadScene::drawUI(void)
{
	_backGround->drawUI();

	for (int i = 0; i < 2; ++i)
	{
		if (_type == 0 && i == 0) continue;
		D3DXVECTOR2 scale = D3DXVECTOR2(_hand[i].size.x*_hand[i].scale.x, _hand[i].size.y * _hand[i].scale.y);
		gFunc::drawSprite(_hand[i].texture,
			_hand[i].position,
			scale,
			_hand[i].scale);
	}

	if (_type == 1)
	{
		_died->drawUI();
	}
}

void deadScene::initResource(void)
{
	_backGround = new spriteBase("resource/texture/scene/menu2.jpg");
	_died = new spriteBase("resource/texture/scene/youdie.png");
	_hand[0].texture = MN_SRC->getSpriteTexture("resource/texture/scene/endHandBlood.png");
	_hand[1].texture = MN_SRC->getSpriteTexture("resource/texture/scene/endHand.png");
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
	 _backGround->setColor(D3DCOLOR_ARGB(255, 255, 255, 255));

	 texture = MN_SRC->getSpriteTexture("resource/texture/scene/youdie.png");
	 gFunc::getTextureSize(&backSize, texture);
	 _died->setPosition(D3DXVECTOR3(windowCenter.x,
		 windowCenter.y, 0.0f));

	for (int i = 0; i < 2; ++i)
	{
		gFunc::getTextureSize(&_hand[i].size, _hand[i].texture);
		_hand[i].scale = D3DXVECTOR2(1.0f, 1.0f);
		_hand[i].position = D3DXVECTOR2(MN_WIN->getWindowSize().cx / 2.0f-100, MN_WIN->getWindowSize().cy);
	}
}
