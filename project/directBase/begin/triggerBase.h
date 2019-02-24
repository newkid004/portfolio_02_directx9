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
		static constexpr int MACHINE_GUN	= 0x1;
		static constexpr int SHOT_GUN		= 0x2;
		static constexpr int MEDKIT			= 0x3;
		static constexpr int NORMAL			= 0x4;

		static constexpr int RADIO			= 0x1 << 4;
	};

protected :
	int _triggerType = 0;

	staticMesh* _bindMesh = nullptr;
	bool _isPick = false;
	std::function<void(triggerBase*)> _active;

public :
	void update(void) override;
	virtual void draw(void) override;

protected :
	virtual bool pickCheck(void);

public :
	int & refTriggerType(void) { return _triggerType; }
	std::function<void(triggerBase*)> & refActive(void) { return _active; }

public:
	triggerBase(staticMesh* bindMesh);
	~triggerBase() {};
};

