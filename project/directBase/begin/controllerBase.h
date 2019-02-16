#pragma once
#include "kGlobalDefine.h"

class aStar_node;
class aStar_path;
class characterBase;

class controllerBase
{
public :
	struct heapCompare	{ bool operator()(aStar_node* n1, aStar_node* n2); };

protected :
	characterBase*	_bindCharacter = nullptr;	// delete : disable (characterManager - enemy / playerable)
	aStar_path*		_path = nullptr;			// delete : enable

protected :
	D3DXVECTOR3		_destPos;

public :
	virtual void update(void);

private :
	void updatePath(void);
	void updateFootPrint(void);
	void updateCollision(void);

private :
	void createPath2Player(void);
	void findPath2Player(void);
	
	void createCollisionNode(std::vector<aStar_node*> * out_list);

public :
	characterBase* & getBindCharacter(void) { return _bindCharacter; }
	aStar_path* & getPath(void) { return _path; }

public:
	controllerBase(characterBase* bindCharacter);
	~controllerBase();
};

