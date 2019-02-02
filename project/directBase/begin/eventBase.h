#pragma once
#include "eventDef.h"
#include "timeManager.h"

#define eventBaseCreate2Writter (void* sour, void* dest, unsigned long paramType = 0UL, float timeAlive = 0.f) : eventBase(sour, dest, paramType, timeAlive) {}

#define makeSourParam(param) ((param & 0xffffUL) << 16)
#define makeDestParam(param) (param & 0xffffUL)
#define makeParamType(sour, dest) (makeSourParam(sour) | makeDestParam(dest))
#define sourParam(param) ((param & 0xffff0000UL) >> 16)
#define destParam(param) (param & 0xffffUL)
#define makeEventParam(type, kind, act, call) ((type & 0x000f) | (kind & 0x00f0) | (act & 0x0f00) | (call & 0xf000))


class eventBase
{
public:			// public ÇÔ¼ö

	virtual void update() { m_stTimeAlive -= GET_TIME_MANAGER()->getDeltaTime(); };
	virtual void draw() {}

public:			// getter
	void* getSour(void) { return m_stSour; };
	void* getDest(void) { return m_stDest; };
	unsigned long getParamType(void) { return m_stParamType; };
	float getTimeAlive(void) { return m_stTimeAlive; }

protected:

	eventBase() {};

public:

	eventBase(void* sour, void* dest, unsigned long paramType = 0UL, float timeAlive = 0.f)
	{
		m_stSour = sour;
		m_stDest = dest;
		m_stParamType = paramType;
		m_stTimeAlive = timeAlive;
	}
	virtual ~eventBase() {}

protected:

	void*			m_stSour;
	void*			m_stDest;

	unsigned long	m_stParamType;

	float			m_stTimeAlive;

};
