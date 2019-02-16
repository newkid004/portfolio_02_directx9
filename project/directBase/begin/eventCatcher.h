#pragma once
#include "KGlobalDefine.h"
#include "eventDef.h"

class eventBase;
// �� event�� destParam(type, kind, act, call)�� �����ϴ� ���
// �ش� event�� ����Ǳ� ��, �Ŀ� ������ active�� ����

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

