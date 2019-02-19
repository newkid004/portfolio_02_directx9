#include "eventCatcher.h"

eventCatcher::eventCatcher(void)
:
m_stParam(0)
{
}

eventCatcher::eventCatcher(unsigned long param, const eventCatcherActive & beforeActive, const eventCatcherActive & afterActive) :
	m_stParam(param),
	m_stBeforeActive(beforeActive),
	m_stAfterActive(afterActive)
{
}

void eventCatcher::release(void)
{
}
