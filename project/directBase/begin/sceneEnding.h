#pragma once
#include "kGlobalDefine.h"
#include "sceneBase.h"

class sceneInGame;

class sceneEnding : public sceneBase
{
private :
	bool _isEnd = false;
	float _percent = 0.0f;

	bool _isInit = false;

	D3DXVECTOR2 _sourPos;

public :
	virtual void init(void)		override;
	virtual void update(void)	override;
	virtual void draw(void)		override;
	virtual void drawUI(void)	override;

public:
	sceneEnding();
	~sceneEnding();
};

