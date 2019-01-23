#pragma once
#include "kGlobalDefine.h"

class deviceManager
{
private :
	LPDIRECT3D9 _direct3d = NULL;
	LPDIRECT3DDEVICE9 _device = NULL;

public :	// ----- FW ----- //
	void init(void);

public :	// ----- 立辟, 瘤沥磊 ----- //
	LPDIRECT3D9 getDirect3D(void) const { return _direct3d; };
	LPDIRECT3DDEVICE9 getDevice(void) const { return _device; };

public:		// ----- 教臂沛 ----- //
	DECLARE_SINGLETON(deviceManager);

private :	// ----- private ----- //
	// direct3d 积己
	LPDIRECT3D9 createDirect3D(void);

	// divice 积己
	LPDIRECT3DDEVICE9 createDevice(void);

private :
	deviceManager() {};

public :
	virtual ~deviceManager();
};

