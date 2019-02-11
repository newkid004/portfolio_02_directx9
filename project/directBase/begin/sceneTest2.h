#pragma once
#include "kGlobalDefine.h"
#include "mainGame.h"

class staticMesh;
class aStar_node;
class aStar_grape;
class aStar_runner;

class sceneTest2 : public sceneBase
{
private:
	staticMesh* _staticMesh = nullptr;
	aStar_grape* _grape = nullptr;
	
	std::stack<aStar_runner> _pathResult;
	std::vector<aStar_node*> _vSelectionNode;

public:
	virtual void init(void) override;
	virtual void update(void) override;
	virtual void draw(void) override;
	virtual void drawUI(void) override;

public :
	void updateControl(void);

public :
	aStar_grape* createGrape(void);
	staticMesh* createStaticMesh(void);

public:
	sceneTest2() {};
	~sceneTest2();
};

