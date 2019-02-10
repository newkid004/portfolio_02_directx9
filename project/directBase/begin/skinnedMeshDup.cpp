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

		// 블렌드 제어
		if (0.0f < _blendSet.currentBlendTime)
		{
			_blendSet.currentBlendTime -= MN_TIME->getDeltaTime();

			float switchWeight = _blendSet.currentBlendTime / _blendSet.timeBlend;
			_bindAnimation->SetTrackWeight(1, switchWeight);
			_bindAnimation->SetTrackWeight(0, 1.0f - switchWeight);
		}
		else
			_bindAnimation->SetTrackEnable(1, false);

		// 재생 제어
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
	// 	// 기존 애니메이션 보존 : 트랙 1번
	// 	D3DXTRACK_DESC trackDesc;
	// 	double trackPos;
	// 	_bindAnimation->GetTrackAnimationSet(0, &_blendSetPrev.aniCurrent);
	// 	_bindAnimation->GetTrackDesc(0, &trackDesc);
	// 	trackPos = trackDesc.Position;
	// 
	// 	_bindAnimation->SetTrackEnable(1, true);				// 트랙 활성화
	// 	_bindAnimation->SetTrackAnimationSet(1, _blendSetPrev.aniCurrent);		// 트랙 애니메이션 설정
	// 	_bindAnimation->SetTrackPosition(1, trackPos);			// 위치 보존
	// 
	// 	// 상대적인 재생시간
	// 	if (_blendSet.currentBlendTime < 0.0f)
	// 		_blendSet.currentBlendTime = _blendSet.timeBlend;
	// 	else
	// 		_blendSet.currentBlendTime = _blendSet.timeBlend - _blendSet.currentBlendTime;
	// }
	// 
	// // 새 애니메이션 보존 : 트랙 0번
	// _bindAnimation->SetTrackAnimationSet(0, aniSet);
	// 
	// _blendSet.aniCurrent = aniSet;
}
