#pragma once
#include "KGlobalDefine.h"
#include "singletonBase.h"
#include "eventDef.h"

class eventBase;
class eventCatcher;

typedef std::vector<eventCatcher*>				V_EVENT_CALL;
typedef std::unordered_map<int, V_EVENT_CALL>	M_EVENT_ACT;
typedef std::unordered_map<int, M_EVENT_ACT>	M_EVENT_KIND;
typedef std::unordered_map<int, M_EVENT_KIND>	M_EVENT_TYPE;
typedef std::unordered_map<int, M_EVENT_TYPE>	M_EVENT_CATCHER;

class eventManager : public singletonBase<eventManager>
{
private:

	M_EVENT_CATCHER			m_stEventCatcher;
	std::vector<eventBase*>	m_stEventList;

public:

	//! �ʱ�ȭ
	void init(void);

	//! ������Ʈ
	void update(void);
	void draw(void);

public:

	void initCatcher(void);
	void releaseCatcher(void);

public:

	// �̺�Ʈ�� �߰��Ѵ�
	void add(eventBase* a_rstEvent);

	// �̺�Ʈ ĳ�ĸ� �߰��Ѵ�
	void add(eventCatcher* a_rstEventCatcher);
	void add(unsigned long a_rstParam,
		const std::function<void(eventBase*)> & a_rBeforeActive,
		const std::function<void(eventBase*)> & a_rAfterActive);

	// ��� �̺�Ʈ�� �����
	void deleteAll(void);

public:	// ----- catcher ----- //
	M_EVENT_TYPE & getEventCatcherType(int type) { return m_stEventCatcher[type & 0xf]; };
	M_EVENT_KIND & getEventCatcherKind(M_EVENT_TYPE & mType, int kind) { return mType[(kind & 0x00f0) >> 4]; };
	M_EVENT_ACT & getEventCatcherKind(M_EVENT_KIND & mKind, int act) { return mKind[(act & 0x0f00) >> 8]; }
	V_EVENT_CALL & getEventCatcherCall(M_EVENT_ACT & mAct, int call) { return mAct[(call & 0xf000) >> 12]; };
	V_EVENT_CALL & getEventCatcherArray(int param);
	eventCatcher* & getEventCatcher(V_EVENT_CALL & vCall, int index) { return vCall[index]; };
	eventCatcher* & getEventCatcher(int param, int index) { return getEventCatcherArray(param)[index]; };

public:
	eventManager() {};
	virtual ~eventManager();
};

#define MN_EVENT (eventManager::getInstance())