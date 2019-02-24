#include "menuScene.h"
#include "managerList.h"
#include "spriteBase.h"

#include "uiManager.h"
#include "gFunc.h"

menuScene::~menuScene()
{
	SAFE_DELETE(backGround);
}

void menuScene::init(void)
{
	sceneBase::init();

	initInfomation();
	
	MN_SND->find("gamestartup1")->play();
}

void menuScene::update(void)
{
	backGround->setColor(D3DCOLOR_ARGB((int)_colorA, (int)_colorA, 255- (int)(_colorA/3.0f), 255- (int)(_colorA / 3.0f)));
	
	(_isIncrease) ? _colorA += 40.0f * MN_TIME->getDeltaTime() : _colorA -= 40.0f* MN_TIME->getDeltaTime();
	if (_colorA > 255) _isIncrease = false;
	else if (_colorA < 150) _isIncrease = true;

	updateBlood();

	if (MN_KEY->mouseUp() && intersectMouseToRect(mainGameButton.rc))
	{
		// 메인게임으로 scene 전환
		printf("mainGame\n");
		ShowCursor(FALSE);
		MN_SCENE->change("sceneInGame");
		MN_SND->find("menu_accept")->play();
	}
	else if (MN_KEY->mouseUp() && intersectMouseToRect(mapToolButton.rc))
	{
		// 맵툴로 scene 전환
		printf("mapTool\n");
		ShowCursor(TRUE);
		MN_SCENE->change("sceneMapTool");
		MN_SND->find("menu_accept")->play();
	}
	else if (MN_KEY->mouseUp() && intersectMouseToRect(exitButton.rc))
	{
		// 나가기
		printf("exit\n");
		ShowCursor(TRUE);
		PostMessage(MN_WIN->getHWnd(), WM_DESTROY, 0, 0);
		MN_SND->find("menu_accept")->play();
	}
}

void menuScene::draw(void)
{
}

void menuScene::drawUI(void)
{
	backGround->drawUI();

	if (MN_KEY->mouseDown() && intersectMouseToRect(mainGameButton.rc))
	{
		gFunc::drawSprite(mainGameButton.texture[1],
			D3DXVECTOR2(mainGameButton.rc.left, mainGameButton.rc.top),
			D3DXVECTOR2(1000.0f, 1000.0f),
			D3DXVECTOR2(0.8f, 0.8f));
	}
	else
	{
		gFunc::drawSprite(mainGameButton.texture[0],
			D3DXVECTOR2(mainGameButton.rc.left, mainGameButton.rc.top),
			D3DXVECTOR2(1000.0f, 1000.0f),
			D3DXVECTOR2(0.8f, 0.8f));
	}
	if (MN_KEY->mouseDown() && intersectMouseToRect(mapToolButton.rc))
	{
		gFunc::drawSprite(mapToolButton.texture[1],
			D3DXVECTOR2(mapToolButton.rc.left, mapToolButton.rc.top),
			D3DXVECTOR2(1000.0f, 1000.0f),
			D3DXVECTOR2(0.8f, 0.8f));
	}
	else
	{
		gFunc::drawSprite(mapToolButton.texture[0],
			D3DXVECTOR2(mapToolButton.rc.left, mapToolButton.rc.top),
			D3DXVECTOR2(1000.0f, 1000.0f),
			D3DXVECTOR2(0.8f, 0.8f));
	}
	if (MN_KEY->mouseDown() && intersectMouseToRect(exitButton.rc))
	{
		gFunc::drawSprite(exitButton.texture[1],
			D3DXVECTOR2(exitButton.rc.left, exitButton.rc.top),
			D3DXVECTOR2(1000.0f, 1000.0f),
			D3DXVECTOR2(0.8f, 0.8f));
	}
	else
	{
		gFunc::drawSprite(exitButton.texture[0],
			D3DXVECTOR2(exitButton.rc.left, exitButton.rc.top),
			D3DXVECTOR2(1000.0f, 1000.0f),
			D3DXVECTOR2(0.8f, 0.8f));
	}
	
	for (int i = 0; i < 4; ++i)
	{
		if (blood[i].alpha > FLT_EPSILON)
		{
			gFunc::drawSprite(blood[i].texture,
				blood[i].pos,
				blood[i].size,
				blood[i].scale,
				blood[i].alpha);
		}
	}
}

void menuScene::initInfomation(void)
{
	backGround = new spriteBase("resource/texture/scene/menuT.png");
	LPDIRECT3DTEXTURE9 texture = MN_SRC->getSpriteTexture("resource/texture/scene/menuT.png");
	D3DXVECTOR2 backSize;
	gFunc::getTextureSize(&backSize, texture);
	backGround->setPosition(D3DXVECTOR3(MN_WIN->getWindowSize().cx / 2.0f,
		MN_WIN->getWindowSize().cy / 2.0f - 50.0f, 0.0f));
	backGround->setScale(D3DXVECTOR3(MN_WIN->getWindowSize().cx / backSize.x,
		MN_WIN->getWindowSize().cy / backSize.y + 0.1f, 0.0f));
	for (int i = 0; i < 4; ++i)
	{
		blood[i].alpha = 0.0f;
		if (i < 1)
		{
			blood[i].type = 0;
			blood[i].texture = MN_SRC->getSpriteTexture("resource/texture/scene/hand.png");
			blood[i].updateTime = MN_TIME->getRunningTime() + gFunc::rndFloat(2.0f, 4.0f);
		}
		else
		{
			blood[i].type = 1;
			blood[i].texture = MN_SRC->getSpriteTexture("resource/texture/scene/blood.png");
			blood[i].updateTime = MN_TIME->getRunningTime() + gFunc::rndFloat(3.0f, 6.0f);
		}
	}

	int middleX = MN_WIN->getWindowSize().cx / 2;
	int middleY = MN_WIN->getWindowSize().cy / 2;

	// 버튼 초기화
	mainGameButton.rc = { middleX - 200, middleY + 110, middleX + 200, middleY + 170 };
	mainGameButton.texture[0] = MN_SRC->getSpriteTexture("resource/texture/scene/mainGameGreen.png");
	mainGameButton.texture[1] = MN_SRC->getSpriteTexture("resource/texture/scene/mainGame.png");

	mapToolButton.rc = { middleX - 200, middleY + 185, middleX + 200, middleY + 245 };
	mapToolButton.texture[0] = MN_SRC->getSpriteTexture("resource/texture/scene/maptoolGreen.png");
	mapToolButton.texture[1] = MN_SRC->getSpriteTexture("resource/texture/scene/maptool.png");

	exitButton.rc = { middleX - 200, middleY + 260, middleX + 200, middleY + 320 };
	exitButton.texture[0] = MN_SRC->getSpriteTexture("resource/texture/scene/exitGreen.png");
	exitButton.texture[1] = MN_SRC->getSpriteTexture("resource/texture/scene/exit.png");

	//사운드 추가
	MN_SND->addSound("gamestartup1", "resource/sound/menu/gamestartup1.mp3", true, true);
	MN_SND->addSound("menu_accept", "resource/sound/menu/menu_accept.wav", false, false);
	MN_SND->addSound("menu_countdown", "resource/sound/menu/menu_countdown.wav", false, false);

}

void menuScene::updateBlood(void)
{
	for (int i = 0; i < 4; ++i)
	{
		if (blood[i].alpha <= FLT_EPSILON &&
			blood[i].updateTime <= MN_TIME->getRunningTime())
		{
			blood[i].size = D3DXVECTOR2(3000.0f, 3000.0f);
			blood[i].scale = D3DXVECTOR2(0.2f, 0.2f);
			D3DXVECTOR2 centerPos;
			if (blood[i].type == 0)
			{
				centerPos = D3DXVECTOR2(MN_WIN->getWindowSize().cx / 2.0f, MN_WIN->getWindowSize().cy / 2.0f);
				blood[i].pos = D3DXVECTOR2(gFunc::rndInt(centerPos.x - (MN_WIN->getWindowSize().cx / 3), centerPos.x + (MN_WIN->getWindowSize().cx / 3)),
					gFunc::rndInt(centerPos.y - (MN_WIN->getWindowSize().cy / 3), centerPos.y + (MN_WIN->getWindowSize().cy / 3)));
			}
			else if (blood[i].type == 1)
			{
				centerPos = D3DXVECTOR2(i % 3 * MN_WIN->getWindowSize().cx / 3 + MN_WIN->getWindowSize().cx / 6,
					MN_WIN->getWindowSize().cy / 2);
				blood[i].pos = D3DXVECTOR2(gFunc::rndInt(centerPos.x - MN_WIN->getWindowSize().cx / 7, centerPos.x + MN_WIN->getWindowSize().cx / 7),
					gFunc::rndInt(centerPos.y - MN_WIN->getWindowSize().cy / 3, centerPos.y + MN_WIN->getWindowSize().cy / 3));
			}
			blood[i].alpha = 1.0f;

		}
		else if(blood[i].updateTime <= MN_TIME->getRunningTime())
		{
			if (blood[i].type == 0)
			{
				blood[i].alpha = max(0.0f, blood[i].alpha - 0.15f * MN_TIME->getDeltaTime());
				if (blood[i].alpha < FLT_EPSILON)
				{
					blood[i].updateTime = MN_TIME->getRunningTime() + gFunc::rndFloat(1.0f, 3.0f);
				}
				blood[i].updateTime = MN_TIME->getRunningTime();
			}
			else 
			{
				blood[i].pos.y += 1.0f* MN_TIME->getDeltaTime();
				blood[i].size.y += 800.0f* MN_TIME->getDeltaTime();
				blood[i].scale.y += 0.15f* MN_TIME->getDeltaTime();
				blood[i].alpha = max(0.0f, blood[i].alpha - 0.3f * MN_TIME->getDeltaTime());
				blood[i].updateTime = MN_TIME->getRunningTime();
			}
		}
	}
}

bool menuScene::intersectMouseToRect(RECT rc)
{
	if (rc.left <= MN_KEY->getMousePos().x &&
		rc.right >= MN_KEY->getMousePos().x &&
		rc.top <= MN_KEY->getMousePos().y &&
		rc.bottom >= MN_KEY->getMousePos().y)
	{
		return true;
	}
	else
	{
		if(!MN_SND->find("menu_countdown")->isPlaySound())
		MN_SND->find("menu_countdown")->play();
		
		return false;
	}
}
