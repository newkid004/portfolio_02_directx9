#include "eventAirPlane.h"

#include "managerList.h"

#include "eventDef.h"

eventAirPlane::eventAirPlane() :
	eventBase(nullptr, nullptr, 
		
		EVENT::TYPE::TRIGGER |
		EVENT::KIND::TRIGGER::AIR_PLANE |
		EVENT::ACT::TRIGGER::ACTIVE,
		
		180.0f)
{

}

eventAirPlane::~eventAirPlane()
{
	eventBase* addition = 
		new eventBase(nullptr, nullptr,
			EVENT::TYPE::TRIGGER |
			EVENT::KIND::TRIGGER::AIR_PLANE |
			EVENT::ACT::TRIGGER::COMPLETE);

	MN_EVENT->add(addition);
}

void eventAirPlane::update(void)
{
	eventBase::update();
}