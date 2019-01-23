#pragma once
#include "kGlobalDefine.h"
#include "sceneBase.h"

class mainGame : public sceneBase
{
private :
	sceneBase** _bindScene = nullptr;

public :
	virtual void init(void) override;
	virtual void update(void) override;
	virtual void draw(void) override;
	virtual void drawUI(void) override;

public:
	mainGame(HINSTANCE hInstance, const SIZE & windowSize, int option) :
		sceneBase(hInstance, windowSize, option) {};
	virtual ~mainGame() {};
};

