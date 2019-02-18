#include "AnimationTester.h"
#include "managerList.h"
#include "gFunc.h"
#include "patternMesh.h"
#include "staticMesh.h"
#include "debugGizmo.h"
#include "charaterArea.h"

void AnimationTester::init(void)
{
	sceneBase::init();

	_rifle = this->createRifle();
	_rifle->setScale(0.03f);
	_shotgun = this->createShotgun();
	_shotgun->setScale(0.03f);
	_healKit = this->createHealKit();
	_healKit->setScale(0.03f);
	_skinnedMesh = this->createSkinnedMesh();
	//_skinnedMesh->setWeapon(_shotgun);
#if		CURRENT_MESH ==	SURVIVOR
	_skinnedMesh->setScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));
#elif	CURRENT_MESH == ZOMBIE_MALE
	_skinnedMesh->setScale(D3DXVECTOR3(0.1f, 0.1f, 0.1f));
#elif	CURRENT_MESH == ZOMBIE_FEMALE
	_skinnedMesh->setScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));
#elif	CURRENT_MESH == ZOMBIE_HULK
	_skinnedMesh->setScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));
#elif	CURRENT_MESH == ZOMBIE_SMOKER
	_skinnedMesh->setScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));
#else
	_skinnedMesh->setScale(D3DXVECTOR3(0.007f, 0.007f, 0.007f));
#endif
	_skinnedMesh->addChild(new charaterArea(10));
	for (int i = 0; i < MAX_NUM; ++i)
	{
		ZeroMemory(&_cloneACInfo[i], sizeof(_cloneACInfo[i]));
		
		int random = gFunc::rndInt(1, 3);

		switch (random)
		{
#if		CURRENT_MESH ==	SURVIVOR
		case 1:
			_cloneACInfo[i].NextMotionBit = ATYPE_SURVIVOR |
				AWEAPON_FIRSTAIDKIT |
				ACONDITION_NORMAL |
				AMAIN_IDLE |
				AMIX_NONE |
				AIDLE_STANDING;
			break;
		case 2:
			_cloneACInfo[i].NextMotionBit = ATYPE_SURVIVOR |
				AWEAPON_PUMPSHOTGUN |
				ACONDITION_NORMAL |
				AMAIN_IDLE |
				AMIX_NONE |
				AIDLE_STANDING;
			break;
		case 3:
			_cloneACInfo[i].NextMotionBit = ATYPE_SURVIVOR |
				AWEAPON_RIFLE |
				ACONDITION_NORMAL |
				AMAIN_IDLE |
				AMIX_NONE |
				AIDLE_STANDING;
			break;

#elif	CURRENT_MESH == ZOMBIE_MALE
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
#elif	CURRENT_MESH == ZOMBIE_FEMALE
		case 1:
			_cloneACInfo[i].NextMotionBit = ATYPE_ZOMBIE_FEMALE |
				FEMALE_IDLE |
				FEMALE_IDLE_ALERT;
			break;
		case 2:
			_cloneACInfo[i].NextMotionBit = ATYPE_ZOMBIE_FEMALE |
				FEMALE_IDLE |
				FEMALE_IDLE_NEUTRAL1;
			break;
		case 3:
			_cloneACInfo[i].NextMotionBit = ATYPE_ZOMBIE_FEMALE |
				FEMALE_IDLE |
				FEMALE_IDLE_NEUTRAL2;
			break;
#elif	CURRENT_MESH == ZOMBIE_HULK
		case 1:
			_cloneACInfo[i].NextMotionBit = ATYPE_ZOMBIE_HULK |
				HULK_FLINCH |
				HULK_FLINCH_CHEST;
			break;
		case 2:
			_cloneACInfo[i].NextMotionBit = ATYPE_ZOMBIE_HULK |
				HULK_FLINCH |
				HULK_FLINCH_LEFT;
			break;
		case 3:
			_cloneACInfo[i].NextMotionBit = ATYPE_ZOMBIE_HULK |
				HULK_FLINCH |
				HULK_FLINCH_RIGHT;
			break;
#elif	CURRENT_MESH == ZOMBIE_SMOKER
		case 1:
			_cloneACInfo[i].NextMotionBit = ATYPE_ZOMBIE_SMOKER |
				SMOKER_IDLE |
				SMOKER_IDLE_NONE;
			break;
		case 2:
			_cloneACInfo[i].NextMotionBit = ATYPE_ZOMBIE_SMOKER |
				SMOKER_COUGH |
				SMOKER_COUGH_ATTACK;
			break;
		case 3:
			_cloneACInfo[i].NextMotionBit = ATYPE_ZOMBIE_SMOKER |
				SMOKER_ATTACK |
				SMOKER_ATTACK_NORMAL;
			break;
#else
		case 1:
			_cloneACInfo[i].NextMotionBit = ATYPE_AIRPLANE |
				AIRPLANE_IDLE |
				AIRPLANE_IDLE_ON;
			break;
		case 2:
			_cloneACInfo[i].NextMotionBit = ATYPE_AIRPLANE |
				AIRPLANE_IDLE |
				AIRPLANE_IDLE_OFF;
			break;
		case 3:
			_cloneACInfo[i].NextMotionBit = ATYPE_AIRPLANE |
				AIRPLANE_OPEN |
				AIRPLANE_OPEN_NONE;
			break;
#endif
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
#if		CURRENT_MESH ==	SURVIVOR
	_cloneACInfo[0].NextMotionBit = ATYPE_SURVIVOR |
		AWEAPON_FIRSTAIDKIT |
		ACONDITION_NORMAL |
		AMAIN_IDLE |
		AMIX_NONE |
		AIDLE_STANDING;

#elif	CURRENT_MESH == ZOMBIE_MALE
	_cloneACInfo[0].NextMotionBit = ATYPE_ZOMBIE_MALE |
		MALE_IDLE |
		MALE_IDLE_ALERT;

#elif	CURRENT_MESH == ZOMBIE_FEMALE
	_cloneACInfo[0].NextMotionBit = ATYPE_ZOMBIE_FEMALE |
		FEMALE_IDLE |
		FEMALE_IDLE_ALERT;
#elif	CURRENT_MESH == ZOMBIE_HULK
	_cloneACInfo[0].NextMotionBit = ATYPE_ZOMBIE_HULK |
		HULK_FLINCH |
		HULK_FLINCH_CHEST;
#elif	CURRENT_MESH == ZOMBIE_SMOKER
	_cloneACInfo[0].NextMotionBit = ATYPE_ZOMBIE_SMOKER |
		SMOKER_IDLE |
		SMOKER_IDLE_NONE;
#else
	_cloneACInfo[0].NextMotionBit = ATYPE_AIRPLANE |
		AIRPLANE_IDLE |
		AIRPLANE_IDLE_ON;
#endif

	m_stRotation[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

void AnimationTester::update(void)
{
	sceneBase::update();

	updateControl();
}

void AnimationTester::draw(void)
{
	D3DXVECTOR3 baseR ;
#if		CURRENT_MESH ==	SURVIVOR
	baseR = D3DXVECTOR3(0.0f, 180.0f, 180.0f);
#elif	CURRENT_MESH == ZOMBIE_MALE
	baseR = D3DXVECTOR3(-90.0f, 180.0f, 180.0f);
#elif	CURRENT_MESH == ZOMBIE_FEMALE
	baseR = D3DXVECTOR3(-90.0f, 180.0f, 180.0f);
#elif	CURRENT_MESH == ZOMBIE_HULK
	baseR = D3DXVECTOR3(-90.0f, 180.0f, 180.0f);
#elif	CURRNET_MESH == ZOMBIE_SMOKER
	baseR = D3DXVECTOR3(0.0f, 180.0f, 180.0f);
#else
	baseR = D3DXVECTOR3(0.0f, 180.0f, 180.0f);
#endif

	sceneBase::draw();
	for (int i = 0; i < MAX_NUM; ++i)
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
#if		CURRENT_MESH ==	SURVIVOR
	if (MN_KEY->keyPress(DIK_1))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit =
				ATYPE_SURVIVOR |
				AWEAPON_PUMPSHOTGUN |
				ACONDITION_NORMAL |
				AMAIN_IDLE |
				AMIX_NONE |
				AIDLE_STANDING;
		}
	}
	else if (MN_KEY->keyPress(DIK_2))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit = 
				ATYPE_SURVIVOR |
				AWEAPON_PUMPSHOTGUN |
				ACONDITION_INJURED |
				AMAIN_IDLE |
				AMIX_NONE |
				AIDLE_STANDING;
		}
	}
	else if (MN_KEY->keyPress(DIK_3))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit =
				ATYPE_SURVIVOR |
				AWEAPON_PUMPSHOTGUN |
				AMAIN_IDLE |
				AMIX_NONE |
				AIDLE_SIT;
		}
	}
	else if (MN_KEY->keyPress(DIK_4))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit = 
				ATYPE_SURVIVOR |
				AWEAPON_PUMPSHOTGUN |
				AMAIN_WALK |
				AMIX_NONE |
				ARUN_STANDING;
		}
	}
	else if (MN_KEY->keyPress(DIK_5))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit =
				ATYPE_SURVIVOR |
				AWEAPON_PUMPSHOTGUN |
				AMIX_UNHOLSTER;
		}
	}
	else if (MN_KEY->keyPress(DIK_6))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit = 
				ATYPE_SURVIVOR |
				AWEAPON_PUMPSHOTGUN |
				AMIX_RELOAD;
		}
	}
	else if (MN_KEY->keyPress(DIK_7))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit =
				ATYPE_SURVIVOR |
				AWEAPON_PUMPSHOTGUN |
				AMIX_SHOOT;
		}
	}
	else if (MN_KEY->keyPress(DIK_8))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit = 
				ATYPE_SURVIVOR |
				AWEAPON_PUMPSHOTGUN |
				AMAIN_RUN |
				AMIX_NONE |
				ARUN_STANDING;
		}
	}
	else if (MN_KEY->keyPress(DIK_9))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit = 
				ATYPE_SURVIVOR |
				AWEAPON_PUMPSHOTGUN |
				AMAIN_WALK |
				AMIX_NONE |
				AWALK_SIT;
		}
	}

#elif	CURRENT_MESH == ZOMBIE_MALE
	if (MN_KEY->keyDown(DIK_1))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit = 
				ATYPE_ZOMBIE_MALE |
				MALE_LYING |
				MALE_LYING_BACKWARD;
		}
	}
	else if (MN_KEY->keyDown(DIK_2))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit =
				ATYPE_ZOMBIE_MALE |
				MALE_LYING |
				MALE_LYING_LEFTWARD;
		}
	}
	else if (MN_KEY->keyDown(DIK_3))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit = 
				ATYPE_ZOMBIE_MALE |
				MALE_LYING |
				MALE_LYING_FRONTWARD;
		}
	}
	else if (MN_KEY->keyDown(DIK_4))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit =
				ATYPE_ZOMBIE_MALE |
				MALE_WALK |
				MALE_WALK_NORMAL;
		}
	}
	else if (MN_KEY->keyDown(DIK_5))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit =
				ATYPE_ZOMBIE_MALE |
				MALE_WALK |
				MALE_WALK_HEADUP;
		}
	}
	else if (MN_KEY->keyDown(DIK_6))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit = 
				ATYPE_ZOMBIE_MALE |
				MALE_ATTACK |
				MALE_ATTACK_NONE;
		}
	}
	else if (MN_KEY->keyDown(DIK_7))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit =
				ATYPE_ZOMBIE_MALE |
				MALE_RUN |
				MALE_RUN_NONE;
		}
	}
	else if (MN_KEY->keyDown(DIK_8))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit = 
				ATYPE_ZOMBIE_MALE |
				MALE_SHOVED |
				MALE_SHOVED_BACK_RUN;
		}
	}
	else if (MN_KEY->keyDown(DIK_9))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit = 
				ATYPE_ZOMBIE_MALE |
				MALE_SHOVED |
				MALE_SHOVED_FRONT_RUN;
		}
	}
#elif	CURRENT_MESH == ZOMBIE_FEMALE
	if (MN_KEY->keyDown(DIK_1))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit = 
				ATYPE_ZOMBIE_FEMALE |
				FEMALE_LYING |
				FEMALE_LYING_BACKWARD;
		}
	}
	else if (MN_KEY->keyDown(DIK_2))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit =
				ATYPE_ZOMBIE_FEMALE |
				FEMALE_LYING |
				FEMALE_LYING_LEFTWARD;
		}
	}
	else if (MN_KEY->keyDown(DIK_3))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit =
				ATYPE_ZOMBIE_FEMALE |
				FEMALE_LYING |
				FEMALE_LYING_FRONTWARD;
		}
	}
	else if (MN_KEY->keyDown(DIK_4))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit =
				ATYPE_ZOMBIE_FEMALE |
				FEMALE_LYING |
				FEMALE_LYING_RIGHTWARD;
		}
	}
	else if (MN_KEY->keyDown(DIK_5))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit =
				ATYPE_ZOMBIE_FEMALE |
				FEMALE_WALK |
				FEMALE_WALK_NORMAL;
		}
	}
	else if (MN_KEY->keyDown(DIK_6))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit =
				ATYPE_ZOMBIE_FEMALE |
				FEMALE_ATTACK |
				FEMALE_ATTACK_NONE;
		}
	}
	else if (MN_KEY->keyDown(DIK_7))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit =
				ATYPE_ZOMBIE_FEMALE |
				FEMALE_RUN |
				FEMALE_RUN_NONE;
		}
	}
	else if (MN_KEY->keyDown(DIK_8))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit =
				ATYPE_ZOMBIE_FEMALE |
				FEMALE_SHOVED |
				FEMALE_SHOVED_FRONT_RUN;
		}
	}
	else if (MN_KEY->keyDown(DIK_9))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit =
				ATYPE_ZOMBIE_FEMALE |
				FEMALE_SHOVED |
				FEMALE_SHOVED_BACK_RUN;
		}
	}
#elif	CURRENT_MESH == ZOMBIE_HULK
	if (MN_KEY->keyDown(DIK_1))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit =
				ATYPE_ZOMBIE_HULK |
				HULK_ATTACK |
				HULK_ATTACK_NORMAL1;
		}
	}
	else if (MN_KEY->keyDown(DIK_2))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit =
				ATYPE_ZOMBIE_HULK |
				HULK_ATTACK |
				HULK_ATTACK_NORMAL2;
		}
	}
	else if (MN_KEY->keyDown(DIK_3))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit =
				ATYPE_ZOMBIE_HULK |
				HULK_VICTORY |
				HULK_VICTORY_1;
		}
	}
	else if (MN_KEY->keyDown(DIK_4))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit =
				ATYPE_ZOMBIE_HULK |
				HULK_VICTORY |
				HULK_VICTORY_2;
		}
	}
	else if (MN_KEY->keyDown(DIK_5))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit =
				ATYPE_ZOMBIE_HULK |
				HULK_WALK |
				HULK_WALK_NONE;
		}
	}
	else if (MN_KEY->keyDown(DIK_6))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit =
				ATYPE_ZOMBIE_HULK |
				HULK_TURN |
				HULK_TURN_LEFT;
		}
	}
	else if (MN_KEY->keyDown(DIK_7))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit =
				ATYPE_ZOMBIE_HULK |
				HULK_TURN |
				HULK_TURN_RIGHT;
		}
	}
	else if (MN_KEY->keyDown(DIK_8))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit =
				ATYPE_ZOMBIE_HULK |
				HULK_ATTACK |
				HULK_ATTACK_RUN;
		}
	}
	else if (MN_KEY->keyDown(DIK_9))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit =
				ATYPE_ZOMBIE_HULK |
				HULK_ATTACK |
				HULK_ATTACK_FLY;
		}
	}
#elif	CURRENT_MESH == ZOMBIE_SMOKER
if (MN_KEY->keyDown(DIK_1))
{
	for (int i = 0; i < MAX_NUM; ++i)
	{
		_cloneACInfo[i].NextMotionBit =
			ATYPE_ZOMBIE_SMOKER |
			SMOKER_IDLE |
			SMOKER_IDLE_NONE;
	}
}
else if (MN_KEY->keyDown(DIK_2))
{
	for (int i = 0; i < MAX_NUM; ++i)
	{
		_cloneACInfo[i].NextMotionBit =
			ATYPE_ZOMBIE_SMOKER |
			SMOKER_COUGH |
			SMOKER_COUGH_ATTACK;
	}
}
else if (MN_KEY->keyDown(DIK_3))
{
	for (int i = 0; i < MAX_NUM; ++i)
	{
		_cloneACInfo[i].NextMotionBit =
			ATYPE_ZOMBIE_SMOKER |
			SMOKER_ATTACK |
			SMOKER_ATTACK_NORMAL;
	}
}
else if (MN_KEY->keyDown(DIK_4))
{
	for (int i = 0; i < MAX_NUM; ++i)
	{
		_cloneACInfo[i].NextMotionBit =
			ATYPE_ZOMBIE_SMOKER |
			SMOKER_FLINCH |
			SMOKER_FLINCH_RIGHTLEG;
	}
}
else if (MN_KEY->keyDown(DIK_5))
{
	for (int i = 0; i < MAX_NUM; ++i)
	{
		_cloneACInfo[i].NextMotionBit =
			ATYPE_ZOMBIE_SMOKER |
			SMOKER_FLINCH |
			SMOKER_FLINCH_RIGHT;
	}
}
else if (MN_KEY->keyDown(DIK_6))
{
	for (int i = 0; i < MAX_NUM; ++i)
	{
		_cloneACInfo[i].NextMotionBit =
			ATYPE_ZOMBIE_SMOKER |
			SMOKER_FLINCH |
			SMOKER_FLINCH_LEFTLEG;
	}
}
else if (MN_KEY->keyDown(DIK_7))
{
	for (int i = 0; i < MAX_NUM; ++i)
	{
		_cloneACInfo[i].NextMotionBit =
			ATYPE_ZOMBIE_SMOKER |
			SMOKER_FLINCH |
			SMOKER_FLINCH_LEFT;
	}
}
else if (MN_KEY->keyDown(DIK_8))
{
	for (int i = 0; i < MAX_NUM; ++i)
	{
		_cloneACInfo[i].NextMotionBit =
			ATYPE_ZOMBIE_SMOKER |
			SMOKER_FLINCH |
			SMOKER_FLINCH_HEAD;
	}
}
else if (MN_KEY->keyDown(DIK_9))
{
	for (int i = 0; i < MAX_NUM; ++i)
	{
		_cloneACInfo[i].NextMotionBit =
			ATYPE_ZOMBIE_SMOKER |
			SMOKER_FLINCH |
			SMOKER_FLINCH_CHEST;
	}
}
#else

	if (MN_KEY->keyDown(DIK_1))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit =
				ATYPE_AIRPLANE |
				AIRPLANE_IDLE |
				AIRPLANE_IDLE_ON;
		}
	}
	else if (MN_KEY->keyDown(DIK_2))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit =
				ATYPE_AIRPLANE |
				AIRPLANE_IDLE |
				AIRPLANE_IDLE_OFF;
		}
	}
	else if (MN_KEY->keyDown(DIK_3))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit =
				ATYPE_AIRPLANE |
				AIRPLANE_OPEN |
				AIRPLANE_OPEN_NONE;
		}
	}
	else if (MN_KEY->keyDown(DIK_4))
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			_cloneACInfo[i].NextMotionBit =
				ATYPE_AIRPLANE |
				AIRPLANE_OUTRO |
				AIRPLANE_OUTRO_NONE;
		}
	}
#endif
	


	if (MN_KEY->keyDown(DIK_SPACE))
	{
		/*printf("CurrentMotionBit : %d\n", _cloneACInfo[0].CurrentMotionBit);
		printf("NextMotionBit : %d\n", _cloneACInfo[0].NextMotionBit);
		printf("AniCount : %d\n", _cloneACInfo[0].aniCount);
		printf("LeftMixTime : %f\n", _cloneACInfo[0].leftMixTime);
		printf("MaxMixTime : %f\n", _cloneACInfo[0].maxMixTime);
		printf("TrackPositionA : %f\n", _cloneACInfo[0].trackPositionA);
		printf("TrackPositionB : %f\n", _cloneACInfo[0].trackPositionB);
		printf("timeScale : %f\n", _cloneACInfo[0].timeScale);
		printf("NextTimeScale : %f\n\n", _cloneACInfo[0].nextTimeScale);*/
		printf("persent: %f\n", _cloneACInfo[0].persent);
	}
}

patternMesh * AnimationTester::createSkinnedMesh(void)
{
	patternMesh::mParam param;
#if		CURRENT_MESH ==	SURVIVOR

	int rndValue = 3;// gFunc::rndInt(0, 3);
		switch (rndValue)
		{
		case 0:
			param.filePath = "resource/mesh/L4D1/Biker/biker.x";
			break;
		case 1:
			param.filePath = "resource/mesh/L4D1/Manager/manager.x";
			break;
		case 2:
			param.filePath = "resource/mesh/L4D1/Namvet/namvet.x";
			break;
		case 3:
			param.filePath = "resource/mesh/L4D1/Teenangst/teenangst.x";
			break;
		}

#elif	CURRENT_MESH == ZOMBIE_MALE
	param.filePath = "resource/mesh/L4D1/male/male1.x";

#elif	CURRENT_MESH == ZOMBIE_FEMALE
	param.filePath = "resource/mesh/L4D1/female/female.x";

#elif	CURRENT_MESH == ZOMBIE_HULK
	param.filePath = "resource/mesh/L4D1/hulk/hulk.x";

#elif	CURRENT_MESH == ZOMBIE_SMOKER
	param.filePath = "resource/mesh/L4D1/smoker/smoker.x";
#else
	param.filePath = "resource/mesh/L4D1/c130/c130.x";
#endif
	param.effectFilePath = "resource/effect/Survivor.fx";

	return new patternMesh(param);
}

staticMesh * AnimationTester::createRifle(void)
{
	staticMesh::mParam stParam =
	{
		"resource/mesh/L4D1/items/rifle.x",
		"resource/effect/example_15.fx"
	};

	return new staticMesh(stParam);
}

staticMesh * AnimationTester::createHealKit(void)
{
	staticMesh::mParam stParam =
	{
		"resource/mesh/L4D1/items/medikit.x",
		"resource/effect/example_15.fx"
	};

	return new staticMesh(stParam);
}

staticMesh * AnimationTester::createShotgun(void)
{
	staticMesh::mParam stParam =
	{
		"resource/mesh/L4D1/items/shotgun.x",
		"resource/effect/example_15.fx"
	};

	return new staticMesh(stParam);
}
