#pragma once
#include "kGlobalDefine.h"
#include "iUpdateble.h"

using namespace std::chrono;

class timeManager : public iUpdateble
{
private :
	typedef system_clock::time_point TimePoint;

private :
	float _fpsElipse = 0.0f;
	unsigned int _fpsCount = 0U;
	unsigned int _fps = 0U;

	float _deltaTime = 0.f;
	float _runningTime = 0.f;

	TimePoint _prevTimePoint;
	TimePoint _startTimePoint;

public :
	void init(void);
	void update(void) override;

public :
	float getDeltaTime(void) const { return _deltaTime; }
	float getRunningTime(void) const { return _runningTime; }
	unsigned int getFPS(void) const { return _fps; }

private :
	// Ω√∞£ ∞£∞› ∞ËªÍ
	float calDeltaTime(const TimePoint & start, const TimePoint end);

public :	// ----- ΩÃ±€≈Ê ----- //
	DECLARE_SINGLETON(timeManager);

public:
	timeManager() {};
	~timeManager() {};
};

