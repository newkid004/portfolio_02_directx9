#pragma once
#include "kGlobalDefine.h"
#include "sceneBase.h"

class characterBase;

class sceneTest3 : public sceneBase
{
private :
	characterBase* _char = nullptr;

public:
	virtual void init(void) override;
	virtual void update(void) override;
	virtual void draw(void) override;

private :
	characterBase* createCharacter(void);

public:
	sceneTest3() {};
	~sceneTest3() {};
};

