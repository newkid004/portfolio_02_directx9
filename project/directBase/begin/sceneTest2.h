#pragma once
#include "kGlobalDefine.h"
#include "mainGame.h"

class staticMesh;
class aStar_node;
class aStar_grape;
class aStar_runner;
class aStar_path;

class sceneTest2 : public sceneBase
{
public :
	struct vertex
	{
		enum { FVF = D3DFVF_XYZ };

		D3DXVECTOR3 pos;
	};
	
private:
	staticMesh* _staticMesh = nullptr;
	aStar_grape* _grape = nullptr;
	
	aStar_path* _pathResult = nullptr;
	std::vector<aStar_node*> _vSelectionNode;

public:
	virtual void init(void) override;
	virtual void update(void) override;
	virtual void draw(void) override;
	virtual void drawUI(void) override;

public :
	void updateMouse(void);
	void updateKey(void);

	void drawMesh(void);
	void drawConnect(void);

public :
	aStar_grape* createGrape(void);
	staticMesh* createStaticMesh(void);

public:
	sceneTest2() {};
	~sceneTest2();
};

