#pragma once

#include "kGlobalDefine.h"
#include "AnimationDef.h"
#include "singletonBase.h"

class PatternManager: public singletonBase<PatternManager>
{
public:
	struct AniInfo
	{
		std::vector<int> motionArray;
		float timeScale;
		bool cancel;
	};

private:
	typedef std::map<int, AniInfo> BOOK;
	BOOK _motionBook[(int)ATYPE_SIZE];

	BOOK _cashingPattern;
private:
	void CreateMotion(int conditionCode, int* arr, int size, float timeScale, bool cancel);

private:
	void initMotionSurvivor(void);
	void initMaleZombie(void);
	void initFemaleZombie(void);
	void initHulkZombie(void);
	void initSmokerZombie(void);
	void initMotionAirplane(void);

public:
	AniInfo & getPattern(int conditionCode);

public:
	PatternManager(void);
	~PatternManager(void);
};
#define GET_PATTERN			(PatternManager::getInstance())