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
	// ��Ʈ�ѷ� ���� �ʱ�ȭ
	resetAnimationController();

	//����� ���ߴ��� �Ǻ�
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

	// �޾ƿ� ������ �������� ��Ʈ�ѷ� ��������
	changeAnimationControll(acInfo);
	
	// ���� ����
	float deltaTimeA = MN_TIME->getDeltaTime() * acInfo.timeScale;
	float deltaTimeB = MN_TIME->getDeltaTime() * acInfo.nextTimeScale;
	float highDeltaTime = max(deltaTimeA, deltaTimeB);

	m_pAnimationController->AdvanceTime(highDeltaTime, NULL);

	// ������Ʈ
	// ���� ����� ���� ���
	if (acInfo.leftMixTime > FLT_EPSILON)
	{
		acInfo.leftMixTime -= highDeltaTime;
		acInfo.trackWeightA = acInfo.leftMixTime / acInfo.maxMixTime;
		acInfo.trackWeightB = 1.0f - acInfo.trackWeightA;

		// ��ȯ�� 0�� Ʈ�� ����
		acInfo.trackPositionB += highDeltaTime;
	}
	else
	{
		acInfo.trackPositionA += highDeltaTime;
	}

	_trackPersent = acInfo.trackPositionA / m_pAnimationSet->GetPeriod();

	// �˻�
	// �ִϸ��̼��� ������ ���(���� ��� �ݺ�)
	if (_trackPersent >= 0.95f && acInfo.leftMixTime <= FLT_EPSILON && acInfo.maxMixTime <= FLT_EPSILON)
	{
		acInfo.maxMixTime = 0.2f / acInfo.timeScale;
		acInfo.leftMixTime = acInfo.maxMixTime;
		acInfo.nextAniCount = min(acInfo.aniCount + 1, acInfo.motionVector.size() - 1);

		//ó������ ���ư��� ����Ǵ�
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
	//// �ִϸ��̼� �ͽ��� ������ ���
	if (acInfo.leftMixTime < FLT_EPSILON && acInfo.maxMixTime > FLT_EPSILON)
	{
		acInfo.aniCount = acInfo.nextAniCount;
		acInfo.maxMixTime = 0.0f;
		acInfo.trackPositionA = acInfo.trackPositionB;
		acInfo.trackPositionB = 0.0f;
		acInfo.trackWeightA = 1.0f;
		acInfo.trackWeightB = 0.0f;
		// ������ ��ȯ�Ǵ� ���
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
	//�ʱ⼳������ ����
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
	// ������ ������ ���� ���
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
		// ���� ���� ����
		m_pAnimationSet = findAnimationSet( m_oAnimationNameList[acInfo.motionVector[acInfo.aniCount]]);
		m_pAnimationController->SetTrackAnimationSet(0, m_pAnimationSet);
		m_pAnimationController->SetTrackWeight(0, acInfo.trackWeightA);
		m_pAnimationController->SetTrackPosition(0, acInfo.trackPositionA);
		// ���� ����� �ִ� ���
		if (acInfo.leftMixTime > 0.0f)
		{
			// ������ �ٲ�� ���
			if (acInfo.nextMotionVector.size() != 0)
			{
				m_pNextAnimationSet = findAnimationSet(m_oAnimationNameList[acInfo.nextMotionVector[0]]);
			}
			else // ���� ������ ���
			{
				m_pNextAnimationSet = findAnimationSet(m_oAnimationNameList[acInfo.motionVector[acInfo.nextAniCount]]);
			}
			// ����Ʈ���� ��� ����
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

			// �ͽ�Ÿ�� ����
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
