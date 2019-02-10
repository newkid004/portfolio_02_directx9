#include "animationControllerDigit.h"
#include "PatternManager.h"

animationControllerDigit::animationControllerDigit(LPD3DXANIMATIONCONTROLLER animationController)
	:
	m_pAnimationController(animationController)
{
	int nNumAnimationSets = animationController->GetNumAnimationSets();

	for (int i = 0; i < nNumAnimationSets; ++i)
	{
		LPD3DXANIMATIONSET pAnimationSet = nullptr;
		animationController->GetAnimationSet(i, &pAnimationSet);

		std::string oAnimationName = pAnimationSet->GetName();

		m_oAnimationNameList.push_back(oAnimationName);
		m_oAnimationSetList.insert(decltype(m_oAnimationSetList)::value_type(oAnimationName, pAnimationSet));
	}
}

animationControllerDigit::~animationControllerDigit()
{
	for (auto &rValuetype : m_oAnimationSetList)
	{
		SAFE_RELEASE(rValuetype.second);
	}

	SAFE_RELEASE(m_pAnimationController);
}

void animationControllerDigit::drawPre(ACInfo & acInfo)
{
	resetAnimationController();

	changeAnimationControll(acInfo);
	


	//모션이 변했는지 판별
	if (acInfo.CurrentMotionBit != acInfo.PreMotionBit)
	{
		acInfo.CurrentMotionBit = acInfo.PreMotionBit;

		if (_cancelAble)
		{

		}
	}
}

void animationControllerDigit::resetAnimationController(void)
{
	//초기설정으로 변경
	m_pAnimationSet = nullptr;
	m_pNextAnimationSet = nullptr;
	m_pAnimationController->SetTrackPosition(0, 0.0f);
	m_pAnimationController->SetTrackAnimationSet(0, NULL);

	m_pAnimationController->SetTrackEnable(1, FALSE);
	m_pAnimationController->SetTrackPosition(1, 0.0f);
	m_pAnimationController->SetTrackAnimationSet(1, NULL);
}

void animationControllerDigit::changeAnimationControll(ACInfo acInfo)
{
	// 기존의 정보가 없을 경우
	if (acInfo.currentAniSet == nullptr)
	{
		int animationIndex = checkAnimationIndex(acInfo.CurrentMotionBit, acInfo.aniCount);
		acInfo.trackWeightA = 1.0f;

		m_pAnimationSet = acInfo.currentAniSet = m_oAnimationSetList[m_oAnimationNameList[animationIndex]];
		m_pAnimationController->SetTrackWeight(0, acInfo.trackWeightA);
		m_pAnimationController->SetTrackAnimationSet(0, m_pAnimationSet);
	}
	else
	{
		//기존 정보 변경
		m_pAnimationSet = acInfo.currentAniSet;
		m_pAnimationController->SetTrackAnimationSet(0, m_pAnimationSet);
		m_pAnimationController->SetTrackWeight(0, acInfo.trackWeightA);
		if (acInfo.nextAniSet != nullptr)
		{
			m_pNextAnimationSet = acInfo.nextAniSet;
			m_pAnimationController->SetTrackEnable(1, TRUE);
			m_pAnimationController->SetTrackPosition(1, acInfo.trackPositionB);
			m_pAnimationController->SetTrackAnimationSet(1, m_pNextAnimationSet);
			m_pAnimationController->SetTrackWeight(1, acInfo.trackWeightB);
		}
	}
	_trackPersent = acInfo.trackPositionA / m_pAnimationSet->GetPeriod();
}

int animationControllerDigit::checkAnimationIndex(int motionBit, int animationIndex)
{
	int checkIndex;
	if ((motionBit & GET_ANIBITMASK(aniDefine::ANIBIT::MIX)) != 0)
	{
		int mixMask = motionBit & GET_ANIBITMASK(aniDefine::ANIBIT::MIX) |
			motionBit & GET_ANIBITMASK(aniDefine::ANIBIT::WEAPON);
		checkIndex = GET_PATTERN->getPattern(mixMask).motionArray[animationIndex];
	}
	else
	{
		checkIndex = GET_PATTERN->getPattern(motionBit).motionArray[animationIndex];
	}

	return checkIndex;
}

void animationControllerDigit::returnMotion(ANIMATION_TYPE type, ACInfo &acInfo)
{
	if ((acInfo.CurrentMotionBit & GET_ANIBITMASK(aniDefine::ANIBIT::TYPE)) == type)
	{
	}
}

void animationControllerDigit::stopMotion(ANIMATION_TYPE type, ACInfo &acInfo)
{
}

void animationControllerDigit::controllTrack(ANIMATION_TYPE type, ACInfo &acInfo)
{
}
