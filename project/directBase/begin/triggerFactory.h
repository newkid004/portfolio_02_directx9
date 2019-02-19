#pragma once
#include "kGlobalDefine.h"

class staticMesh;
class triggerBase;

class triggerFactory
{
public :
	static triggerBase* createTrigger2type(int type, staticMesh* bindMesh = nullptr);

private :
	triggerFactory() {};
	~triggerFactory() {};
};

