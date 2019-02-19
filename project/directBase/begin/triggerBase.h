#pragma once
#include "kGlobalDefine.h"
#include "iUpdateble.h"
#include "iRenderable.h"

class staticMesh;

class triggerBase : public iUpdateble, public iRenderable
{
public :
	struct TYPE
	{
		constexpr static int MACHINE_GUN	= 0;
		constexpr static int SHOT_GUN		= 1;
		constexpr static int MEDKIT			= 2;
		constexpr static int AIR_PLANE		= 3;
	};

protected :
	int _triggerType = 0;

	staticMesh* _bindMesh = nullptr;
	bool _isPick = false;
	std::function<void(void)> _active;

public :
	void update(void) override;
	virtual void draw(void) override;

protected :
	virtual bool pickCheck(void);

public :
	int & refTriggerType(void) { return _triggerType; }
	std::function<void(void)> & refActive(void) { return _active; }

public:
	triggerBase(staticMesh* bindMesh);
	~triggerBase() {};
};

