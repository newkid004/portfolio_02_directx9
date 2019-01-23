#include "timeManager.h"

void timeManager::init(void)
{
	_prevTimePoint = system_clock::now();
	_startTimePoint = system_clock::now();
}

void timeManager::update(void)
{
	auto currentTimePoint = system_clock::now();

	_deltaTime = calDeltaTime(_prevTimePoint, currentTimePoint);
	_runningTime = calDeltaTime(_startTimePoint, currentTimePoint);

	_prevTimePoint = currentTimePoint;

	// fps
	++_fpsCount;
	if (1.0f < (_fpsElipse += _deltaTime))
	{
		_fps = _fpsCount;
		_fpsCount = 0U;
		_fpsElipse = 0.0f;
	}
}

float timeManager::calDeltaTime(const TimePoint & start, const TimePoint end)
{
	return duration<float>(end - start).count();
}
