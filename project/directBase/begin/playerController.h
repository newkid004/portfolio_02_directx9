#pragma once
#include "kGlobalDefine.h"
#include "controllerBase.h"

class playerController : public controllerBase
{
public:
	virtual void update(void) override;

protected :
	void updateControl(void);
	void updateAnimation(void);
public:
	playerController(characterBase* bindCharacter);
	~playerController();
};

