#pragma once
#include "KGlobalDefine.h"
#include "eventDef.h"

class eventBase;
// 각 event의 destParam(type, kind, act, call)에 반응하는 요소
// 해당 event가 실행되기 전, 후에 각자의 active를 실행

typedef std::function<void(eventBase*)> eventCatcherActive;

class eventCatcher
{
private:

	unsigned long m_stParam;

	eventCatcherActive m_stBeforeActive;
	eventCatcherActive m_stAfterActive;

public:

	unsigned long & getParam(void) { return m_stParam; }
	eventCatcherActive & getBeforeActive(void) { return m_stBeforeActive; };
	eventCatcherActive & getAfterActive(void) { return m_stAfterActive; };

public:

	void release(void);

public:
	eventCatcher(void);
	eventCatcher(unsigned long param, eventCatcherActive & beforeActive, eventCatcherActive & afterActive);
	~eventCatcher(void) {};
};

