#pragma once
#include "kGlobalDefine.h"
#include "sceneBase.h"

class patternMesh;
class characterBase;

class staticMesh;

class inGame_node;
class inGame_grape;

class sceneTest3 : public sceneBase
{
private :
	patternMesh* _origin = nullptr;
	characterBase* _char = nullptr;

	inGame_grape * _grape = nullptr;
	
	staticMesh* _bump = nullptr;

public:
	virtual void init(void) override;
	virtual void update(void) override;
	virtual void draw(void) override;

private :
	patternMesh* createCharacter(void);

public:
	sceneTest3() {};
	~sceneTest3() {};
};

