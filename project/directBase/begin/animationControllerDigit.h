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
	// ��Ʈ�ѷ��� ������ �ʱ�ȭ�Ѵ�.
	void resetAnimationController(void);

	// ���޹��� ����ü�� ������ �����Ѵ�.
	void changeAnimationControll(ACInfo acInfo);

	// ��Ʈ�� ���� üũ
	int checkAnimationIndex(int motionBit, int animationIndex);

	// ó������ ���ư��� ��� üũ
	void returnMotion(ANIMATION_TYPE type, ACInfo& acInfo);

	// ������ ��� üũ
	void stopMotion(ANIMATION_TYPE type, ACInfo& acInfo);

	// ���� ����� �������� ����
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