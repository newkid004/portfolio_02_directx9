#pragma once
#include "kGlobalDefine.h"
#include "AnimationDef.h"
#include "PatternManager.h"

class animationControllerDigit
{
public:
	void drawPre(ACInfo &acInfo);

private:

	// ��Ʈ�ѷ��� ������ �ʱ�ȭ�Ѵ�.
	void resetAnimationController(void);

	// ���޹��� ����ü�� ������ �����Ѵ�.
	void changeAnimationControll(ACInfo& acInfo);

	// ��Ʈ�� ���� üũ
	PatternManager::AniInfo checkAnimationOut(const int motionBit);

	// ó������ ���ư��� ��� üũ
	void returnMotion(int motionName, int& count);

	// ������ ��� üũ
	void stopMotion(int motionName, ACInfo& acInfo);

	// ���� ����� �������� ����
	void controllTrack(int motionName, float& nextPosition, const float customPosition);

	// ����� ã�ƿ´�.
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