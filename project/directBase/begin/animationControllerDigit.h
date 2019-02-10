#pragma once
#include "kGlobalDefine.h"
#include "AnimationDef.h"

class animationControllerDigit
{
public:
	struct ACInfo
	{
		int CurrentMotionBit;
		int PreMotionBit;
		int aniCount;
		float trackPositionA;
		float trackPositionB;
		float trackWeightA;
		float trackWeightB;
		float leftMixTime;
		bool isCancel;
		LPD3DXANIMATIONSET currentAniSet;
		LPD3DXANIMATIONSET nextAniSet;
	};

	struct checkOut
	{
		int nameCount;
		float timeScale;
		bool isCancel;
	};

public:
	void drawPre(ACInfo &acInfo);

private:
	// 컨트롤러의 설정을 초기화한다.
	void resetAnimationController(void);

	// 전달받은 구조체로 정보를 변경한다.
	void changeAnimationControll(ACInfo acInfo);

	// 비트의 종류 체크
	int checkAnimationIndex(int motionBit, int animationIndex);

	// 처음으로 돌아가는 모션 체크
	void returnMotion(ANIMATION_TYPE type, ACInfo& acInfo);

	// 정지할 모션 체크
	void stopMotion(ANIMATION_TYPE type, ACInfo& acInfo);

	// 다음 모션의 시작지점 설정
	void controllTrack(ANIMATION_TYPE type, ACInfo& acInfo);

private:
	int _trackPersent;
	bool _cancelAble;

	LPD3DXANIMATIONSET m_pAnimationSet = nullptr;
	LPD3DXANIMATIONSET m_pNextAnimationSet = nullptr;
	LPD3DXANIMATIONCONTROLLER m_pAnimationController = nullptr;

	std::vector<std::string> m_oAnimationNameList;
	std::unordered_map<std::string, LPD3DXANIMATIONSET> m_oAnimationSetList;

public:
	animationControllerDigit(LPD3DXANIMATIONCONTROLLER animationController);
	~animationControllerDigit();
};