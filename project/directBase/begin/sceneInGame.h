#pragma once
#include "kGlobalDefine.h"
#include "sceneBase.h"

class sceneInGame : public sceneBase
{
public:
	virtual void init(void)		override;
	virtual void update(void)	override;
	virtual void draw(void)		override;
	virtual void drawUI(void)	override;

private :
	void initResource(void);
	void initSystem(void);
	void initField(void);

	void initEvent(void);
	void initEventWeapon(void);

	void initSound(void);
	

public:
	sceneInGame() {};
	~sceneInGame() {};
};

