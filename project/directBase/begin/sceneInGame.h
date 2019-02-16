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
	void initEvent(void);

public:
	sceneInGame();
	~sceneInGame();
};

