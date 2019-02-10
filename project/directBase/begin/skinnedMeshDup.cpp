#include "skinnedMeshDup.h"

#include "managerList.h"

#include "skinnedMesh.h"

skinnedMeshDup::skinnedMeshDup(skinnedMesh * duplicateTarget) :
	_bindObject(duplicateTarget),
	_bindAnimation(duplicateTarget->getAniController()->getAniController())
{

}

skinnedMeshDup::~skinnedMeshDup()
{
}



void skinnedMeshDup::update(void)
{
	renderObject::update();

}

void skinnedMeshDup::applyAnimation(void)
{
	if (_playSet.isPlay)
	{
		float deltaTime = _playSet.timeScale * MN_TIME->getDeltaTime();

		// ���� ����
		if (0.0f < _blendSet.currentBlendTime)
		{
			_blendSet.currentBlendTime -= MN_TIME->getDeltaTime();

			float switchWeight = _blendSet.currentBlendTime / _blendSet.timeBlend;
			_bindAnimation->SetTrackWeight(1, switchWeight);
			_bindAnimation->SetTrackWeight(0, 1.0f - switchWeight);
		}
		else
			_bindAnimation->SetTrackEnable(1, false);

		// ��� ����
		D3DXTRACK_DESC trackDesc;
		_bindAnimation->GetTrackDesc(0, &trackDesc);

		double percent = trackDesc.Position / _blendSet.aniCurrent->GetPeriod();

		if (1.0f < percent)
		{
			auto curAnimation = _blendSet.aniCurrent;
			bool isLoop = _playSet.isPlay;

			//stop();
			//if (isLoop)
			//	play(curAnimation, isLoop);
		}

		_bindAnimation->AdvanceTime(deltaTime, NULL);
	}
}

void skinnedMeshDup::drawPre(void)
{
	applyAnimation();
	_bindObject->getAniController()->update();
	_bindObject->updateBoneMatrix();
}

void skinnedMeshDup::drawDo(void)
{
}

void skinnedMeshDup::drawPost(void)
{
}

void skinnedMeshDup::updateBoneMatrix(LPD3DXFRAME frame, const D3DXMATRIXA16 & mUpdate)
{
}

void skinnedMeshDup::drawBone(LPD3DXFRAME frame)
{
}

void skinnedMeshDup::drawMeshContainer(LPD3DXFRAME frame, LPD3DXMESHCONTAINER meshContainer)
{
}

void skinnedMeshDup::play(LPD3DXANIMATIONSET aniSet)
{
	// _playSet.isPlay = true;
	// 
	// if (aniSet != _blendSet.aniCurrent && _blendSet.aniCurrent != nullptr)
	// {
	// 	// ���� �ִϸ��̼� ���� : Ʈ�� 1��
	// 	D3DXTRACK_DESC trackDesc;
	// 	double trackPos;
	// 	_bindAnimation->GetTrackAnimationSet(0, &_blendSetPrev.aniCurrent);
	// 	_bindAnimation->GetTrackDesc(0, &trackDesc);
	// 	trackPos = trackDesc.Position;
	// 
	// 	_bindAnimation->SetTrackEnable(1, true);				// Ʈ�� Ȱ��ȭ
	// 	_bindAnimation->SetTrackAnimationSet(1, _blendSetPrev.aniCurrent);		// Ʈ�� �ִϸ��̼� ����
	// 	_bindAnimation->SetTrackPosition(1, trackPos);			// ��ġ ����
	// 
	// 	// ������� ����ð�
	// 	if (_blendSet.currentBlendTime < 0.0f)
	// 		_blendSet.currentBlendTime = _blendSet.timeBlend;
	// 	else
	// 		_blendSet.currentBlendTime = _blendSet.timeBlend - _blendSet.currentBlendTime;
	// }
	// 
	// // �� �ִϸ��̼� ���� : Ʈ�� 0��
	// _bindAnimation->SetTrackAnimationSet(0, aniSet);
	// 
	// _blendSet.aniCurrent = aniSet;
}
