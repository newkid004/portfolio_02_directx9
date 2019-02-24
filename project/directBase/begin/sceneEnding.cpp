#include "sceneEnding.h"

#include "managerList.h"
#include "gFunc.h"

#include "camera.h"

#include "patternMeshDup.h"
#include "player.h"

sceneEnding::sceneEnding()
{
}

sceneEnding::~sceneEnding()
{
}

void sceneEnding::init(void)
{
	sceneBase::init();

	MN_EVENT->add(
		EVENT::TYPE::TRIGGER |
		EVENT::KIND::TRIGGER::AIR_PLANE |
		EVENT::ACT::TRIGGER::GAME_END,
		[](eventBase*)->void {},
		[this](eventBase*)->void {

		_isEnd = true;
	});
}

void sceneEnding::update(void)
{
	sceneBase::update();

	if (!_isInit)
	{
		_camera->setAspect(MN_WIN->getAspect(), 60.0f, 3000.0f);

		GET_CAMERA()->setPosition(D3DXVECTOR3(-200, 150, -150));

		_sourPos.x = MN_WIN->getWindowSize().cx * 0.85f;
		_sourPos.y = MN_WIN->getWindowSize().cy * 0.15f;

		SGT_GAME->getSet().player->setVisible(false);

		MN_SND->getBGM()->stop();
		MN_SND->find("clear")->play();

		_isInit = true;
	}

	if (!_isEnd)
	{
		SGT_GAME->update();

		GET_CAMERA()->rotate2Pos(SGT_GAME->getSet().airPlane->getPosition());
		GET_CAMERA()->moveZ(-10.0f * MN_TIME->getDeltaTime());
		GET_CAMERA()->moveY(-10.0f * MN_TIME->getDeltaTime());
		GET_CAMERA()->moveX(-20.0f * MN_TIME->getDeltaTime());
	}
	else
	{
		_percent = min(1.0f, _percent + 0.2f * MN_TIME->getDeltaTime());
	}

	MN_EVENT->update();
}

void sceneEnding::draw(void)
{
	sceneBase::draw();

	SGT_GAME->draw();
	MN_EVENT->draw();
}

void sceneEnding::drawUI(void)
{
	if (_isEnd)
	{
		static auto poster = MN_SRC->getSpriteTexture("resource/texture/scene/menu.jpg");
		static D3DXVECTOR2 winSize = {
			(float)MN_WIN->getWindowSize().cx,
			(float)MN_WIN->getWindowSize().cy
		};

		D3DXVECTOR2 pos = gFunc::lerp(
			_sourPos, 
			D3DXVECTOR2(0.0f, 0.0f), 
			_percent);
		
		D3DXVECTOR2 size = gFunc::lerp(
			D3DXVECTOR2(0.0f, 0.0f),
			winSize,
			_percent
		);

		D3DXVECTOR2 texSize; gFunc::getTextureSize(&texSize, poster);
		D3DXVECTOR2 scale = gFunc::lerp(
			D3DXVECTOR2(0.0f, 0.0f),
			D3DXVECTOR2(winSize.x / texSize.x, winSize.y / texSize.y),
			_percent);

		gFunc::drawSprite(
			poster,
			pos,
			size,
			scale,
			max(0.3f, _percent));
	}
}

