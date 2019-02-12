#include "AnimationTester.h"
#include "managerList.h"
#include "gFunc.h"
#include "patternMesh.h"
//#include "skinnedMesh.h"

void AnimationTester::init(void)
{
	sceneBase::init();

	_skinnedMesh = this->createSkinnedMesh();
	_skinnedMesh->setScale(D3DXVECTOR3(0.1f, 0.1f, 0.1f));

	int middle = MAX_ZOMBIE / 2;
	for (int i = 0; i < MAX_ZOMBIE; ++i)
	{
		ZeroMemory(&_cloneACInfo[i], sizeof(_cloneACInfo[i]));
		
		int random = gFunc::rndInt(1, 3);

		switch (random)
		{
		case 1:
			_cloneACInfo[i].NextMotionBit = ATYPE_ZOMBIE_MALE |
				MALE_IDLE |
				MALE_IDLE_NEUTRAL1;
			break;
		case 2:
			_cloneACInfo[i].NextMotionBit = ATYPE_ZOMBIE_MALE |
				MALE_IDLE |
				MALE_IDLE_NEUTRAL2;
			break;
		case 3:
			_cloneACInfo[i].NextMotionBit = ATYPE_ZOMBIE_MALE |
				MALE_IDLE |
				MALE_IDLE_NEUTRAL3;
			break;
		}
		m_stRotation[i] = D3DXVECTOR3(0.0f, gFunc::rndFloat(0.0f,360.0f), 0.0f);
	}

	for (int j = 0; j < 세로; ++j)
	{
		for (int i = 0; i < 가로; ++i)
		{
			m_stPosition[j*가로 + i] = D3DXVECTOR3(i * 20.0f,0.0f,j*20.0f);
		}
	}

	//
	m_stRotation[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_cloneACInfo[0].NextMotionBit = ATYPE_ZOMBIE_MALE |
		MALE_IDLE |
		MALE_IDLE_NEUTRAL2;
	

}

void AnimationTester::update(void)
{
	sceneBase::update();

	updateControl();
}

void AnimationTester::draw(void)
{
	D3DXVECTOR3 baseR = D3DXVECTOR3(-90.0f, 180.0f, 180.0f);

	sceneBase::draw();
	for (int i = 0; i < MAX_ZOMBIE; ++i)
	{
		_skinnedMesh->setPosition(m_stPosition[i]);
		_skinnedMesh->setRotation(baseR + m_stRotation[i]);
		_skinnedMesh->update();
		_skinnedMesh->drawpreMesh(_cloneACInfo[i]);
		_skinnedMesh->draw();
	}

}

void AnimationTester::drawUI(void)
{
	sceneBase::drawUI();
}

void AnimationTester::updateControl(void)
{
	if (MN_KEY->keyDown(DIK_1))
	{
		for (int i = 0; i < MAX_ZOMBIE; ++i)
		{
			_cloneACInfo[i].NextMotionBit = ATYPE_ZOMBIE_MALE |
				MALE_ATTACK |
				MALE_ATTACK_NONE;
		}
	}
	else if (MN_KEY->keyDown(DIK_2))
	{
		for (int i = 0; i < MAX_ZOMBIE; ++i)
		{
			_cloneACInfo[i].NextMotionBit = ATYPE_ZOMBIE_MALE |
				MALE_IDLE |
				MALE_IDLE_NEUTRAL3;
		}
	}


	if (MN_KEY->keyDown(DIK_SPACE))
	{
		printf("CurrentMotionBit : %d\n", _cloneACInfo[0].CurrentMotionBit);
		printf("NextMotionBit : %d\n", _cloneACInfo[0].NextMotionBit);
		printf("AniCount : %d\n", _cloneACInfo[0].aniCount);
		printf("LeftMixTime : %f\n", _cloneACInfo[0].leftMixTime);
		printf("MaxMixTime : %f\n", _cloneACInfo[0].maxMixTime);
		printf("TrackPositionA : %f\n", _cloneACInfo[0].trackPositionA);
		printf("TrackPositionB : %f\n", _cloneACInfo[0].trackPositionB);
		printf("timeScale : %f\n", _cloneACInfo[0].timeScale);
		printf("NextTimeScale : %f\n\n", _cloneACInfo[0].nextTimeScale);
	}
}

patternMesh * AnimationTester::createSkinnedMesh(void)
{
	patternMesh::mParam param = {

	"resource/mesh/L4D1/male/male1.x",
		"resource/effect/skinnedMesh.fx"
	};

	return new patternMesh(param);
}
