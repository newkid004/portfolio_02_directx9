#pragma once
#include "kGlobalDefine.h"
#include "direct3dApplication.h"

class sceneBase : public direct3dApplication
{
public:
	virtual void init(void)		override;
	virtual void update(void)	override;
	virtual void draw(void)		override;
	virtual void drawUI(void)	override;

public:
	sceneBase();
	sceneBase(HINSTANCE hInstance, const SIZE & windowSize, int option) :
		direct3dApplication(hInstance, windowSize, option) {};
	virtual ~sceneBase() {};
};