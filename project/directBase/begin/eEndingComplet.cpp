#include "eEndingComplet.h"

#include "eventManager.h"

eEndingComplet::eEndingComplet() :
	eventBase(nullptr, nullptr,
		EVENT::TYPE::TRIGGER |
		EVENT::KIND::TRIGGER::AIR_PLANE |
		EVENT::ACT::TRIGGER::CONTINUE,
		25.0f)
{
}


eEndingComplet::~eEndingComplet()
{
	MN_EVENT->add(new eventBase(nullptr, nullptr,
		EVENT::TYPE::TRIGGER |
		EVENT::KIND::TRIGGER::AIR_PLANE |
		EVENT::ACT::TRIGGER::GAME_END));
}
