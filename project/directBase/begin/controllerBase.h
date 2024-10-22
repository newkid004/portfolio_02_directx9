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

protected :
	virtual void updatePlace(void);

public :
	virtual void updatePath(void);

protected :
	virtual void updateFootPrint(void);

private :
	void findPath2Player(void);

public :
	void createPath2Player(void);


public :
	characterBase* & getBindCharacter(void) { return _bindCharacter; }
	aStar_path* & getPath(void) { return _path; }
	constexpr D3DXVECTOR3 & getDestPos(void) { return _destPos; }

public:
	controllerBase(characterBase* bindCharacter);
	~controllerBase();
};

