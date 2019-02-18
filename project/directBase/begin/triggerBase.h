#pragma once
#include "kGlobalDefine.h"

class staticMesh;

class triggerBase
{
	struct TYPE
	{
		constexpr static int NONE			= 0;
		constexpr static int SHOT_GUN		= 1;
		constexpr static int MACHINE_GUN	= 2;
		constexpr static int MEDKIT			= 3;
		constexpr static int AIR_PLANE		= 4;
	};

protected :
	int _type = TYPE::NONE;

	staticMesh* _bindMesh = nullptr;
	bool _isPick = false;
	std::function<void(void)> _active;

public :
	void update(void);
	virtual void draw(void);

protected :
	virtual bool pickCheck(void);

public :
	std::function<void(void)> & refActive(void) { return _active; }

public:
	triggerBase(staticMesh* bindMesh) : _bindMesh(bindMesh) {};
	~triggerBase() {};
};

