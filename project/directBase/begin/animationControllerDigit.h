#pragma once
#include "kGlobalDefine.h"
#include "AnimationDef.h"
#include "PatternManager.h"

class animationControllerDigit
{
public:
	void drawPre(ACInfo &acInfo);

private:

	// 컨트롤러의 설정을 초기화한다.
	void resetAnimationController(void);

	// 전달받은 구조체로 정보를 변경한다.
	void changeAnimationControll(ACInfo& acInfo);

	// 비트의 종류 체크
	PatternManager::AniInfo checkAnimationOut(const int motionBit);

	// 처음으로 돌아가는 모션 체크
	void returnMotion(int motionName, int& count);

	// 정지할 모션 체크
	void stopMotion(int motionName, ACInfo& acInfo);

	// 다음 모션의 시작지점 설정
	void controllTrack(int motionName, float& nextPosition, const float customPosition);

	// 모션을 찾아온다.
	LPD3DXANIMATIONSET findAnimationSet(const std::string& animationName);

private:
	float _trackPersent;

	LPD3DXANIMATIONSET m_pAnimationSet = nullptr;
	LPD3DXANIMATIONSET m_pNextAnimationSet = nullptr;
	LPD3DXANIMATIONCONTROLLER m_pAnimationController = nullptr;

	std::vector<std::string> m_oAnimationNameList;
	std::unordered_map<std::string, LPD3DXANIMATIONSET> m_oAnimationSetList;

public:
	animationControllerDigit(LPD3DXANIMATIONCONTROLLER animationController);
	~animationControllerDigit();
};