#pragma once
#include "kGlobalDefine.h"
#include "eventBase.h"

class eventAirPlane : public eventBase
{
public :
	void update(void) override;

public:
	eventAirPlane();
	~eventAirPlane();
};

