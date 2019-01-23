#include "animationController.h"

#include "managerList.h"

animationController::animationController(LPD3DXANIMATIONCONTROLLER aniController) :
	_timeScale(1.0f),
	_aniController(aniController)
{
	int numAniSet = aniController->GetNumAnimationSets();

	for (int i = 0; i < numAniSet; ++i)
	{
		LPD3DXANIMATIONSET aniSet = nullptr;
		aniController->GetAnimationSet(i, &aniSet);

		string aniName = aniSet->GetName();

		_vAniNameList.push_back(aniName);
		_mAniSetList.insert(decltype(_mAniSetList)::value_type(aniName, aniSet));
	}
}

animationController::~animationController()
{
	for (auto & val : _mAniSetList) 
		SAFE_RELEASE(val.second);

	SAFE_RELEASE(_aniController);
}

void animationController::update(void)
{
	if (_isPlay)
	{
		float deltaTime = _timeScale * MN_TIME->getDeltaTime();

		// ���� ����
		if (0.0f < _currentBlendTime)
		{
			_currentBlendTime -= MN_TIME->getDeltaTime();

			float switchWeight = _currentBlendTime / _timeBlend;
			_aniController->SetTrackWeight(1, switchWeight);
			_aniController->SetTrackWeight(0, 1.0f - switchWeight);
		}
		else
			_aniController->SetTrackEnable(1, false);

		// ��� ����
		D3DXTRACK_DESC trackDesc;
		_aniController->GetTrackDesc(0, &trackDesc);

		double percent = trackDesc.Position / _aniCurrent->GetPeriod();

		if (1.0f < percent)
		{
			auto curAnimation = _aniCurrent;
			bool isLoop = _isLoop;

			stop();
			if (isLoop)
				play(curAnimation, isLoop);
		}

		_aniController->AdvanceTime(deltaTime, NULL);
	}
}

void animationController::play(const string & aniName, double pos)
{
	if (0.0 < pos)
		setPlayPosition(pos);
	else if (0.0 == pos && _aniCurrent != nullptr)
	{
		LPD3DXANIMATIONSET aniSet = nullptr;
		_aniController->GetAnimationSet(0, &aniSet);

		if (aniSet != _aniCurrent)
			setPlayPosition(pos);
	}

	play(aniName);
}

void animationController::play(LPD3DXANIMATIONSET aniSet, double pos)
{
	/*
		�ִϸ��̼� ��Ʈ�ѷ��� ���������� Ʈ���� �������� �ִϸ��̼��� ������
		�⺻������ Ʈ���� �������� ���������� 0�� Ʈ���� �����ϰ�� ��Ȱ��ȭ : �� �ϳ��� �ִϸ��̼� ����� ��Ģ
	*/
	if (0.0 < pos)
		setPlayPosition(pos);
	else if (0.0 == pos && _aniCurrent != nullptr)
	{
		LPD3DXANIMATIONSET aniSet = nullptr;
		_aniController->GetAnimationSet(0, &aniSet);

		if (aniSet != _aniCurrent)
			setPlayPosition(pos);
	}

	play(aniSet);
}

void animationController::play(const string & aniName, bool isLoop)
{
	_isLoop = isLoop;
	play(aniName);
}

void animationController::play(LPD3DXANIMATIONSET aniSet, bool isLoop)
{
	_isLoop = isLoop;
	play(aniSet);
}

void animationController::play(const string & aniName)
{
	auto iter = _mAniSetList.find(aniName);
	if (iter != _mAniSetList.end())
		play(iter->second);
}

void animationController::play(LPD3DXANIMATIONSET aniSet)
{
	_isPlay = true;

	if (aniSet != _aniCurrent && _aniCurrent != nullptr)
	{
		// ���� �ִϸ��̼� ���� : Ʈ�� 1��
		LPD3DXANIMATIONSET preAniSet = nullptr;
		D3DXTRACK_DESC trackDesc;
		double trackPos;
		_aniController->GetTrackAnimationSet(0, &preAniSet);
		_aniController->GetTrackDesc(0, &trackDesc);
		trackPos = trackDesc.Position;

		_aniController->SetTrackEnable(1, true);				// Ʈ�� Ȱ��ȭ
		_aniController->SetTrackAnimationSet(1, preAniSet);		// Ʈ�� �ִϸ��̼� ����
		_aniController->SetTrackPosition(1, trackPos);			// ��ġ ����

		// ������� ����ð�
		if (_currentBlendTime < 0.0f)
			_currentBlendTime = _timeBlend;
		else
			_currentBlendTime = _timeBlend - _currentBlendTime;
	}

	// �� �ִϸ��̼� ���� : Ʈ�� 0��
	_aniController->SetTrackAnimationSet(0, aniSet);

	_aniCurrent = aniSet;
}

void animationController::stop(void)
{
	_isLoop = false;
	_isPlay = false;
	_aniCurrent = nullptr;

	setPlayPosition(0.0);
	_aniController->SetTrackAnimationSet(0, NULL);
}