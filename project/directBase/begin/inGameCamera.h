#pragma once
#include "kGlobalDefine.h"
#include "camera.h"

class characterBase;

class inGameCamera : public camera
{
protected :
	characterBase* _bindCharacter = nullptr;

	POINT _posCenter;

	bool _isFixMouse = true;
	
public :
	void update(void) override;

protected :
	void updateBind(void);
	void updateControl(void);

public:
	inGameCamera(characterBase* bindCharacter);
	~inGameCamera();
};

