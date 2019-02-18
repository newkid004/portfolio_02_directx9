#pragma once
#include "kGlobalDefine.h"

class aStar_node;
class aStar_path;
class characterBase;

class controllerBase
{
protected :
	characterBase*	_bindCharacter = nullptr;	// delete : disable (characterManager - enemy / playerable)
	aStar_path*		_path = nullptr;			// delete : enable

protected :
	D3DXVECTOR3		_destPos;

public :
	virtual void update(void);

private :
	void updatePlace(void);
	void updatePath(void);
	void updateFootPrint(void);

private :
	void createPath2Player(void);
	void findPath2Player(void);

public :
	characterBase* & getBindCharacter(void) { return _bindCharacter; }
	aStar_path* & getPath(void) { return _path; }

public:
	controllerBase(characterBase* bindCharacter);
	~controllerBase();
};

