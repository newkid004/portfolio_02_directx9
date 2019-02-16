#include "eventManager.h"
#include "eventBase.h"
#include "eventCatcher.h"

#include "gMng.h"

eventManager::~eventManager()
{
	this->deleteAll();
	this->releaseCatcher();
}

void eventManager::init(void)
{
	this->initCatcher();
	auto & i = getEventCatcherArray(0x0000);


}

void eventManager::update(void)
{
	for (auto iter = m_stEventList.begin(); iter != m_stEventList.end();)
	{
		V_EVENT_CALL & vCatcher = getEventCatcherArray((*iter)->getParamType());

		// catcherBefore -> event -> catcherAfter
		for (auto cIter : vCatcher)
		{
			if (cIter->getBeforeActive())
			{
				(cIter->getBeforeActive())(*iter);
			}
		}

		// event time update
		(*iter)->update();

		for (auto cIter : vCatcher)
		{
			if (cIter->getAfterActive())
			{
				(cIter->getAfterActive())(*iter);
			}
		}

		if ((*iter)->getTimeAlive() <= 0.0f)
		{
			SAFE_DELETE(*iter);
			iter = m_stEventList.erase(iter);
		}
		else ++iter;
	}
}

void eventManager::draw(void)
{
}

void eventManager::initCatcher(void)
{
}

void eventManager::releaseCatcher(void)
{
	auto iterType = m_stEventCatcher.begin();
	for (; iterType != m_stEventCatcher.end();)
	{
		auto iterKind = iterType->second.begin();
		for (; iterKind != iterType->second.end();)
		{
			auto iterAct = iterKind->second.begin();
			for (; iterAct != iterKind->second.end();)
			{
				auto iterCall = iterAct->second.begin();
				for (; iterCall != iterAct->second.end();)
				{
					auto & vCatcher = iterCall->second;
					for (int i = 0; i < vCatcher.size(); ++i)
					{
						vCatcher[i]->release();
						SAFE_DELETE(vCatcher[i]);
					}
					vCatcher.clear();

					iterCall = iterAct->second.erase(iterCall);
				}
				iterAct = iterKind->second.erase(iterAct);
			}
			iterKind = iterType->second.erase(iterKind);
		}
		iterType = m_stEventCatcher.erase(iterType);
	}
}

void eventManager::add(eventBase * a_rstEvent)
{
	m_stEventList.push_back(a_rstEvent);
}

void eventManager::add(unsigned long a_rstParam, std::function<void(eventBase*)> a_rBeforeActive, std::function<void(eventBase*)> a_rAfterActive)
{
	getEventCatcherArray(a_rstParam).push_back(new eventCatcher(a_rstParam, a_rBeforeActive, a_rAfterActive));
}

void eventManager::deleteAll(void)
{
	for (auto iter = m_stEventList.begin(); iter != m_stEventList.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}
}

V_EVENT_CALL & eventManager::getEventCatcherArray(int param)
{
	return m_stEventCatcher
		[param & 0x000f]
	[(param & 0x00f0) >> 4]
	[(param & 0x0f00) >> 8]
	[(param & 0xf000) >> 12];
}