#pragma once
#include "kGlobalDefine.h"

class deviceManager
{
private :
	LPDIRECT3D9 _direct3d = NULL;
	LPDIRECT3DDEVICE9 _device = NULL;

public :	// ----- FW ----- //
	void init(void);

public :	// ----- ����, ������ ----- //
	LPDIRECT3D9 getDirect3D(void) const { return _direct3d; };
	LPDIRECT3DDEVICE9 getDevice(void) const { return _device; };

public:		// ----- �̱��� ----- //
	DECLARE_SINGLETON(deviceManager);

private :	// ----- private ----- //
	// direct3d ����
	LPDIRECT3D9 createDirect3D(void);

	// divice ����
	LPDIRECT3DDEVICE9 createDevice(void);

private :
	deviceManager() {};

public :
	virtual ~deviceManager();
};

