#include "animationControllerDigit.h"
#include "PatternManager.h"
#include "managerList.h"

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
	// 컨트롤러 설정 초기화
	resetAnimationController();

	//모션이 변했는지 판별
	if (acInfo.CurrentMotionBit != acInfo.NextMotionBit)
	{
		acInfo.CurrentMotionBit = acInfo.NextMotionBit;

		if (acInfo.motionVector.size() != 0)
		{
			PatternManager::AniInfo check = checkAnimationOut(acInfo.CurrentMotionBit);
			acInfo.nextMotionVector = check.motionArray;
			acInfo.nextTimeScale = check.timeScale;
			acInfo.isNextCancel = check.cancel;
			acInfo.maxMixTime = 0.2f / max(acInfo.timeScale, acInfo.nextTimeScale);
			acInfo.leftMixTime = acInfo.maxMixTime;

			
		}
	}

	// 받아온 정보를 기준으로 컨트롤러 설정변경
	changeAnimationControll(acInfo);
	
	// 본에 적용
	float deltaTimeA = MN_TIME->getDeltaTime() * acInfo.timeScale;
	float deltaTimeB = MN_TIME->getDeltaTime() * acInfo.nextTimeScale;
	float highDeltaTime = max(deltaTimeA, deltaTimeB);

	m_pAnimationController->AdvanceTime(highDeltaTime, NULL);

	// 업데이트
	// 다음 모션이 있을 경우
	if (acInfo.leftMixTime > FLT_EPSILON)
	{
		acInfo.leftMixTime -= highDeltaTime;
		acInfo.trackWeightA = acInfo.leftMixTime / acInfo.maxMixTime;
		acInfo.trackWeightB = 1.0f - acInfo.trackWeightA;

		// 전환중 0번 트랙 고정
		acInfo.trackPositionB += highDeltaTime;
	}
	else
	{
		acInfo.trackPositionA += highDeltaTime;
	}

	_trackPersent = acInfo.trackPositionA / m_pAnimationSet->GetPeriod();

	// 검사
	// 애니메이션이 끝나갈 경우(같은 모션 반복)
	if (_trackPersent >= 0.95f && acInfo.leftMixTime <= FLT_EPSILON && acInfo.maxMixTime <= FLT_EPSILON)
	{
		acInfo.maxMixTime = 0.2f / acInfo.timeScale;
		acInfo.leftMixTime = acInfo.maxMixTime;
		acInfo.nextAniCount = min(acInfo.aniCount + 1, acInfo.motionVector.size() - 1);

		//처음으로 돌아가는 모션판단
		if ((acInfo.CurrentMotionBit & GET_ANIBITMASK(aniDefine::ANIBIT::TYPE)) == ATYPE_ZOMBIE_MALE)
		{
			returnMotion(34, acInfo.nextAniCount);
			returnMotion(28, acInfo.nextAniCount);
		}
		else if ((acInfo.CurrentMotionBit & GET_ANIBITMASK(aniDefine::ANIBIT::TYPE)) == ATYPE_ZOMBIE_FEMALE)
		{
			returnMotion(32, acInfo.nextAniCount);
		}
		else if ((acInfo.CurrentMotionBit & GET_ANIBITMASK(aniDefine::ANIBIT::TYPE)) == ATYPE_ZOMBIE_SMOKER)
		{
			returnMotion(5, acInfo.nextAniCount);
		}

	}
	//// 애니메이션 믹스이 끝났을 경우
	if (acInfo.leftMixTime < FLT_EPSILON && acInfo.maxMixTime > FLT_EPSILON)
	{
		acInfo.aniCount = acInfo.nextAniCount;
		acInfo.maxMixTime = 0.0f;
		acInfo.trackPositionA = acInfo.trackPositionB;
		acInfo.trackPositionB = 0.0f;
		acInfo.trackWeightA = 1.0f;
		acInfo.trackWeightB = 0.0f;
		// 동작이 전환되는 경우
		if (acInfo.nextMotionVector.size() != 0)
		{
			acInfo.aniCount = 0;
			acInfo.timeScale = acInfo.nextTimeScale;
			acInfo.nextTimeScale = 0.0f;
			acInfo.isCancel = acInfo.isNextCancel;
			acInfo.motionVector = acInfo.nextMotionVector;
			acInfo.nextMotionVector.clear();
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
	_trackPersent = 0.0f;
}

void animationControllerDigit::changeAnimationControll(ACInfo& acInfo)
{
	// 기존의 정보가 없을 경우
	if (acInfo.motionVector.size() == 0)
	{
		PatternManager::AniInfo check = checkAnimationOut(acInfo.CurrentMotionBit);
		acInfo.motionVector = check.motionArray;
		acInfo.timeScale = check.timeScale;
		acInfo.isCancel = check.cancel;
		acInfo.trackWeightA = 1.0f;

		m_pAnimationSet = findAnimationSet(m_oAnimationNameList[acInfo.motionVector[acInfo.aniCount]]);
		m_pAnimationController->SetTrackWeight(0, acInfo.trackWeightA);
		m_pAnimationController->SetTrackAnimationSet(0, m_pAnimationSet);
		m_pAnimationController->SetTrackPosition(0, acInfo.trackPositionA);
	}
	else
	{
		// 기존 정보 변경
		m_pAnimationSet = findAnimationSet( m_oAnimationNameList[acInfo.motionVector[acInfo.aniCount]]);
		m_pAnimationController->SetTrackAnimationSet(0, m_pAnimationSet);
		m_pAnimationController->SetTrackWeight(0, acInfo.trackWeightA);
		m_pAnimationController->SetTrackPosition(0, acInfo.trackPositionA);
		// 다음 모션이 있는 경우
		if (acInfo.leftMixTime > 0.0f)
		{
			// 동작이 바뀌는 경우
			if (acInfo.nextMotionVector.size() != 0)
			{
				m_pNextAnimationSet = findAnimationSet(m_oAnimationNameList[acInfo.nextMotionVector[0]]);
			}
			else // 같은 동작일 경우
			{
				m_pNextAnimationSet = findAnimationSet(m_oAnimationNameList[acInfo.motionVector[acInfo.nextAniCount]]);
			}
			// 다음트랙의 모션 조정
			if ((acInfo.CurrentMotionBit & GET_ANIBITMASK(aniDefine::ANIBIT::TYPE)) == ATYPE_SURVIVOR)
			{
				controllTrack(20, acInfo.trackPositionB, 0.8f);
				controllTrack(20, acInfo.trackPositionB, 0.8f);
				controllTrack(20, acInfo.trackPositionB, 0.8f);
				controllTrack(20, acInfo.trackPositionB, 0.8f);
			}
			else if ((acInfo.CurrentMotionBit & GET_ANIBITMASK(aniDefine::ANIBIT::TYPE)) == ATYPE_ZOMBIE_MALE)
			{

			}
			else if ((acInfo.CurrentMotionBit & GET_ANIBITMASK(aniDefine::ANIBIT::TYPE)) == ATYPE_ZOMBIE_FEMALE)
			{

			}
			else if ((acInfo.CurrentMotionBit & GET_ANIBITMASK(aniDefine::ANIBIT::TYPE)) == ATYPE_ZOMBIE_HULK)
			{

			}

			m_pAnimationController->SetTrackEnable(1, TRUE);
			m_pAnimationController->SetTrackPosition(1, acInfo.trackPositionB);
			m_pAnimationController->SetTrackAnimationSet(1, m_pNextAnimationSet);
			m_pAnimationController->SetTrackWeight(1, acInfo.trackWeightB);

			// 믹스타임 제거
			if ((acInfo.CurrentMotionBit & GET_ANIBITMASK(aniDefine::ANIBIT::TYPE)) == ATYPE_SURVIVOR)
			{
				stopMotion(28, acInfo);
			}
		}
	}
}

PatternManager::AniInfo animationControllerDigit::checkAnimationOut(const int motionBit)
{
	PatternManager::AniInfo cOInfo;

	if ((motionBit & GET_ANIBITMASK(aniDefine::ANIBIT::MIX)) != 0)
	{
		int mixMask = motionBit & GET_ANIBITMASK(aniDefine::ANIBIT::MIX) |
			motionBit & GET_ANIBITMASK(aniDefine::ANIBIT::WEAPON);
		cOInfo = GET_PATTERN->getPattern(mixMask);
	}
	else
	{
		cOInfo = GET_PATTERN->getPattern(motionBit);
	}

	return cOInfo;
}

void animationControllerDigit::returnMotion(int motionName, int &count)
{
	if ((m_pAnimationSet->GetName() == m_oAnimationNameList[motionName]))
	{
		count = 0;
	}
}

void animationControllerDigit::stopMotion(int motionName, ACInfo &acInfo)
{
	if ((m_pNextAnimationSet->GetName() == m_oAnimationNameList[motionName]))
	{
		acInfo.leftMixTime = 0.0f;
	}
}

void animationControllerDigit::controllTrack(int motionName, float& nextPosition, const float customPosition)
{
	if ((m_pNextAnimationSet->GetName() == m_oAnimationNameList[motionName]))
	{
		nextPosition = customPosition;
	}
}

LPD3DXANIMATIONSET animationControllerDigit::findAnimationSet(const std::string & animationName)
{
	decltype(m_oAnimationSetList)::iterator oIterator = m_oAnimationSetList.find(animationName);

	if (oIterator != m_oAnimationSetList.end())
	{
		return oIterator->second;
	}
	return m_oAnimationSetList.begin()->second;
}
