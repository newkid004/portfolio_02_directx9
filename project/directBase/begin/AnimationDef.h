#pragma once
#include "singletonBase.h"

struct ACInfo
{
	int CurrentMotionBit;
	int NextMotionBit;
	int aniCount;
	int nextAniCount;
	float leftMixTime;
	float maxMixTime;
	float trackPositionA;
	float trackPositionB;
	float trackWeightA;
	float trackWeightB;
	float timeScale;
	float nextTimeScale;
	bool isCancel;
	bool isNextCancel;
	std::vector<int> motionVector;
	std::vector<int> nextMotionVector;
};

class aniDefine : public singletonBase<aniDefine>
{
public:
	
	enum class ANIBIT
	{
		TYPE = 0,
		WEAPON,
		CONDITION,
		MAIN,
		MIX,
		SUB,
		_COUNT
	};

	enum class SHIFTBIT
	{
		TYPE		= 0,
		WEAPON		= 1 << (4 * (((int)ANIBIT::WEAPON))),
		CONDITION	= 1 << (4 * (((int)ANIBIT::CONDITION))),
		MAIN		= 1 << (4 * (((int)ANIBIT::MAIN))),
		MIX			= 1 << (4 * (((int)ANIBIT::MIX))),
		SUB			= 1 << (4 * (((int)ANIBIT::SUB))),
	};

public:
	aniDefine(void)
	{
		for (int i = 0; i < (int)ANIBIT::_COUNT; ++i)
		{
			_value[i] = i ? (0x1 << ((i) * 4)) : 0;
		}
	}
	~aniDefine() {}

private:
	int _value[(int)ANIBIT::_COUNT];

public:
	
	int getMask(ANIBIT bit)
	{
		if (bit == ANIBIT::TYPE)return 0xf;
		else return _value[(int)bit] * 0xf;
	}

	// 비트를 변환한다.
	void changeBit(int &output, ANIBIT minusBit,int motion)
	{
		output -= (output& getMask(minusBit));
		output += motion;
	}

};
#define DEF_ANI									aniDefine::getInstance()
#define GET_ANIBITMASK(TYPE)					DEF_ANI->getMask(TYPE)
#define CHANGE_BIT(OUTPUT, MINUSBIT, MOTION)	DEF_ANI->changeBit(OUTPUT, MINUSBIT, MOTION)

enum ANIMATION_TYPE
{
	ATYPE_SURVIVOR			= 0x0 ,
	ATYPE_ZOMBIE_MALE		= 0x1 ,
	ATYPE_ZOMBIE_FEMALE		= 0x2 ,
	ATYPE_ZOMBIE_HULK		= 0x3 ,
	ATYPE_ZOMBIE_SMOKER		= 0x4 ,
	ATYPE_AIRPLANE			= 0x5 ,
	ATYPE_SIZE				= 0x6
};

// SURVIVOR
enum ANIMATION_CWEAPON
{
	AWEAPON_FIRSTAIDKIT		= 0x1 * (int)aniDefine::SHIFTBIT::WEAPON,
	AWEAPON_PUMPSHOTGUN		= 0x2 * (int)aniDefine::SHIFTBIT::WEAPON,
	AWEAPON_RIFLE			= 0x3 * (int)aniDefine::SHIFTBIT::WEAPON,
	AWEAPON_NONE			= 0	  * (int)aniDefine::SHIFTBIT::WEAPON
};

enum ANIMATION_CCONDITION
{
	ACONDITION_INJURED		= 0x1 * (int)aniDefine::SHIFTBIT::CONDITION,
	ACONDITION_NORMAL		= 0x2 * (int)aniDefine::SHIFTBIT::CONDITION,
	ACONDITION_NONE			=	0 * (int)aniDefine::SHIFTBIT::CONDITION
};

enum ANIMATION_CMAINMOTION
{
	AMAIN_IDLE				= 0	  * (int)aniDefine::SHIFTBIT::MAIN,
	AMAIN_WALK				= 0x1 * (int)aniDefine::SHIFTBIT::MAIN,
	AMAIN_RUN				= 0x2 * (int)aniDefine::SHIFTBIT::MAIN,
	AMAIN_JUMP				= 0x3 * (int)aniDefine::SHIFTBIT::MAIN,
	AMAIN_TRIP				= 0x4 * (int)aniDefine::SHIFTBIT::MAIN, // 넘어지다.
	AMAIN_GETUP				= 0x5 * (int)aniDefine::SHIFTBIT::MAIN, // 일어나다
	AMAIN_FLY				= 0x6 * (int)aniDefine::SHIFTBIT::MAIN,
	AMAIN_DRAG				= 0x7 * (int)aniDefine::SHIFTBIT::MAIN,
	AMAIN_HEAL				= 0x8 * (int)aniDefine::SHIFTBIT::MAIN,
	AMAIN_BE_ATTACKED		= 0x9 * (int)aniDefine::SHIFTBIT::MAIN, // 피격
	AMAIN_DEAD				= 0xA * (int)aniDefine::SHIFTBIT::MAIN,
	AMAIN_TONGUE			= 0xB * (int)aniDefine::SHIFTBIT::MAIN
	//AMAIN_TURN				= 0xC * (int)aniDefine::SHIFTBIT::MAIN
};

enum ANIMATION_CMIXMOTION
{
	AMIX_RELOAD				= 0x1 * (int)aniDefine::SHIFTBIT::MIX,
	AMIX_SHOOT				= 0x2 * (int)aniDefine::SHIFTBIT::MIX,
	AMIX_UNHOLSTER			= 0x3 * (int)aniDefine::SHIFTBIT::MIX, // 총 꺼내는 모션
	AMIX_ATTACK				= 0x4 * (int)aniDefine::SHIFTBIT::MIX,
	AMIX_NONE				= 0	  * (int)aniDefine::SHIFTBIT::MIX
};

//enum ANIMATINO_TONGUE_DIRECTION
//{
//	ADIRECTION_FORWARD		= 0x0 * (int)aniDefine::SHIFTBIT::MIX,
//	ADIRECTION_BACKWARD		= 0x1 * (int)aniDefine::SHIFTBIT::MIX,
//	ADIRECTION_LEFT			= 0x2 * (int)aniDefine::SHIFTBIT::MIX,
//	ADIRECTION_RIGHT		= 0x3 * (int)aniDefine::SHIFTBIT::MIX
//};

enum ANIMATION_IDLE
{
	AIDLE_STANDING			= 0x1 * (int)aniDefine::SHIFTBIT::SUB,
	AIDLE_SIT				= 0x2 * (int)aniDefine::SHIFTBIT::SUB,
	AIDLE_NONE				= 0	  * (int)aniDefine::SHIFTBIT::SUB
};

enum ANIMTION_WALK
{
	AWALK_STANDING			= 0x1 * (int)aniDefine::SHIFTBIT::SUB,
	AWALK_SIT				= 0x2 * (int)aniDefine::SHIFTBIT::SUB, // 앉다
	AWALK_NONE				= 0	  * (int)aniDefine::SHIFTBIT::SUB
};

enum ANIMATION_RUN
{
	ARUN_STANDING			= 0x1 * (int)aniDefine::SHIFTBIT::SUB,
	ARUN_SIT				= 0x2 * (int)aniDefine::SHIFTBIT::SUB,
	ARUN_NONE				= 0	  * (int)aniDefine::SHIFTBIT::SUB
};

enum ANIMATION_JUMP
{
	AJUMP_JUMP				= 0x1 * (int)aniDefine::SHIFTBIT::SUB,
	AJUMP_LAND				= 0x2 * (int)aniDefine::SHIFTBIT::SUB,
	AJUMP_NONE				= 0	  * (int)aniDefine::SHIFTBIT::SUB
};

enum ANIMATION_TRIP
{
	ATRIP_BACKWARD			= 0x1 * (int)aniDefine::SHIFTBIT::SUB,
	ATRIP_LEFTWARD			= 0x2 * (int)aniDefine::SHIFTBIT::SUB,
	ATRIP_NONE				= 0	  * (int)aniDefine::SHIFTBIT::SUB
}; 

enum ANIMATION_GETUP
{
	AGETUP_BACKWARD			= 0x1 * (int)aniDefine::SHIFTBIT::SUB,
	AGETUP_LEFTWARD			= 0x2 * (int)aniDefine::SHIFTBIT::SUB,
	AGETUP_TANKPUNCH		= 0x3 * (int)aniDefine::SHIFTBIT::SUB,
	AGETUP_TANKROCK			= 0x4 * (int)aniDefine::SHIFTBIT::SUB,
	AGETUP_NONE				= 0	  * (int)aniDefine::SHIFTBIT::SUB
};

enum ANIMATION_FLY
{
	AFLY_TANKPUNCH			= 0x1 * (int)aniDefine::SHIFTBIT::SUB,
	AFLY_FALLING			= 0x2 * (int)aniDefine::SHIFTBIT::SUB,
	AFLY_TONGUE				= 0x3 * (int)aniDefine::SHIFTBIT::SUB,
	AFLY_NONE				= 0	  * (int)aniDefine::SHIFTBIT::SUB
};

enum ANIMATION_DRAG
{
	ADRAG_NONE				= 0   * (int)aniDefine::SHIFTBIT::SUB
};

enum ANIMATION_HEAL
{
	AHEAL_SELF_STANDING		= 0x1 * (int)aniDefine::SHIFTBIT::SUB,
	AHEAL_SELF_SIT			= 0x2 * (int)aniDefine::SHIFTBIT::SUB,
	AHEAL_FRIEND_STANDING	= 0x3 * (int)aniDefine::SHIFTBIT::SUB,
	AHEAL_FRIEND_LIE		= 0x4 * (int)aniDefine::SHIFTBIT::SUB,
	AHEAL_NONE				= 0	  * (int)aniDefine::SHIFTBIT::SUB
};

enum ANIMATION_BE_ATTACKED
{
	ABEATTACKED_NONE		= 0 * (int)aniDefine::SHIFTBIT::SUB
};

enum ANIMATION_DEAD
{
	ADEAD_NONE				= 0 * (int)aniDefine::SHIFTBIT::SUB
};

enum ANIMATION_TONGUE
{
	ATONGUE_CATCH			= 0x0 * (int)aniDefine::SHIFTBIT::SUB,
	ATONGUE_DRAG			= 0x1 * (int)aniDefine::SHIFTBIT::SUB,
	ATONGUE_BIND			= 0x2 * (int)aniDefine::SHIFTBIT::SUB
};

//MALE

enum MALE_MAIN
{
	MALE_IDLE				= 0x0 * (int)aniDefine::SHIFTBIT::MAIN,
	MALE_DEAD				= 0x1 * (int)aniDefine::SHIFTBIT::MAIN,
	MALE_RUNNING_DEAD		= 0x2 * (int)aniDefine::SHIFTBIT::MAIN,
	MALE_FALL				= 0x3 * (int)aniDefine::SHIFTBIT::MAIN,
	MALE_TURN				= 0x4 * (int)aniDefine::SHIFTBIT::MAIN,
	MALE_LYING				= 0x5 * (int)aniDefine::SHIFTBIT::MAIN,
	MALE_WALK				= 0x6 * (int)aniDefine::SHIFTBIT::MAIN,
	MALE_ATTACK				= 0x7 * (int)aniDefine::SHIFTBIT::MAIN,
	MALE_RUN				= 0x8 * (int)aniDefine::SHIFTBIT::MAIN,
	MALE_SHOVED				= 0x9 * (int)aniDefine::SHIFTBIT::MAIN
};

enum MALE_ATTACKED_BY
{
	MALE_ATTACKED_NORAML	= 0x0 * (int)aniDefine::SHIFTBIT::WEAPON,
	MALE_ATTACKED_SHOTGUN	= 0x1 * (int)aniDefine::SHIFTBIT::WEAPON,
	MALE_ATTACKED_RIFLE		= 0x2 * (int)aniDefine::SHIFTBIT::WEAPON
};

enum MALE_IDLE
{
	MALE_IDLE_NONE			= 0x0 * (int)aniDefine::SHIFTBIT::SUB,
	MALE_IDLE_ALERT			= 0x1 * (int)aniDefine::SHIFTBIT::SUB,	// 경계
	MALE_IDLE_NEUTRAL1		= 0x2 * (int)aniDefine::SHIFTBIT::SUB,	// 대기모션
	MALE_IDLE_NEUTRAL2		= 0x3 * (int)aniDefine::SHIFTBIT::SUB,
	MALE_IDLE_NEUTRAL3		= 0x4 * (int)aniDefine::SHIFTBIT::SUB
};


enum MALE_DEAD
{
	MALE_DEAD_LEFT_FRONT	= 0x0 * (int)aniDefine::SHIFTBIT::SUB,
	MALE_DEAD_RIGHT_FRONT	= 0x1 * (int)aniDefine::SHIFTBIT::SUB,
	MALE_DEAD_MIDDLE_FRONT	= 0x2 * (int)aniDefine::SHIFTBIT::SUB,
	MALE_DEAD_HEAD_FRONT	= 0x3 * (int)aniDefine::SHIFTBIT::SUB,
	MALE_DEAD_LEFT_BACK		= 0x4 * (int)aniDefine::SHIFTBIT::SUB,
	MALE_DEAD_RIGHT_BACK	= 0x5 * (int)aniDefine::SHIFTBIT::SUB,
	MALE_DEAD_MIDDLE_BACK	= 0x6 * (int)aniDefine::SHIFTBIT::SUB,
	MALE_DEAD_HEAD_BACK		= 0x7 * (int)aniDefine::SHIFTBIT::SUB
};

enum MALE_RUNNING_DEAD
{
	MALE_RD_HEAD			= 0x0 * (int)aniDefine::SHIFTBIT::SUB,
	MALE_RD_MIDDLE			= 0x1 * (int)aniDefine::SHIFTBIT::SUB,
	MALE_RD_ORDER			= 0x2 * (int)aniDefine::SHIFTBIT::SUB
};

enum MALE_FALL
{
	MALE_FALL_NONE			= 0x0 * (int)aniDefine::SHIFTBIT::SUB
};

enum MALE_TURN
{
	MALE_TURN_NONE			= 0x0 * (int)aniDefine::SHIFTBIT::SUB,
	MALE_TURN_RIGHT			= 0x1 * (int)aniDefine::SHIFTBIT::SUB,
	MALE_TURN_LEFT			= 0x2 * (int)aniDefine::SHIFTBIT::SUB
};

enum MALE_LYING
{
	MALE_LYING_BACKWARD		= 0x0 * (int)aniDefine::SHIFTBIT::SUB,
	MALE_LYING_LEFTWARD		= 0x1 * (int)aniDefine::SHIFTBIT::SUB,
	MALE_LYING_FRONTWARD	= 0x2 * (int)aniDefine::SHIFTBIT::SUB	
};

enum MALE_WALK
{
	MALE_WALK_NORMAL		= 0x0 * (int)aniDefine::SHIFTBIT::SUB,
	MALE_WALK_HEADUP		= 0x1 * (int)aniDefine::SHIFTBIT::SUB
};

enum MALE_ATTACK
{
	MALE_ATTACK_NONE		= 0x0 * (int)aniDefine::SHIFTBIT::SUB
};

enum MALE_RUN
{
	MALE_RUN_NONE			= 0x0 * (int)aniDefine::SHIFTBIT::SUB
};

enum MALE_SHOVED
{
	MALE_SHOVED_BACKWARD	= 0x0 * (int)aniDefine::SHIFTBIT::SUB,
	MALE_SHOVED_FRONTWARD	= 0x1 * (int)aniDefine::SHIFTBIT::SUB,
	MALE_SHOVED_BACK_RUN	= 0x2 * (int)aniDefine::SHIFTBIT::SUB,
	MALE_SHOVED_FRONT_RUN	= 0x3 * (int)aniDefine::SHIFTBIT::SUB
};

// Female
enum FEMALE_MAIN
{
	FEMALE_IDLE				= 0x0 * (int)aniDefine::SHIFTBIT::MAIN,
	FEMALE_DEAD				= 0x1 * (int)aniDefine::SHIFTBIT::MAIN,
	FEMALE_RUNNING_DEAD		= 0x2 * (int)aniDefine::SHIFTBIT::MAIN,
	FEMALE_FALL				= 0x3 * (int)aniDefine::SHIFTBIT::MAIN,
	FEMALE_TURN				= 0x4 * (int)aniDefine::SHIFTBIT::MAIN,
	FEMALE_LYING			= 0x5 * (int)aniDefine::SHIFTBIT::MAIN,
	FEMALE_WALK				= 0x6 * (int)aniDefine::SHIFTBIT::MAIN,
	FEMALE_ATTACK			= 0x7 * (int)aniDefine::SHIFTBIT::MAIN,
	FEMALE_RUN				= 0x8 * (int)aniDefine::SHIFTBIT::MAIN,
	FEMALE_SHOVED			= 0x9 * (int)aniDefine::SHIFTBIT::MAIN
};

enum FEMALE_IDLE
{
	FEMALE_IDLE_NEUTRAL1	= 0x0 * (int)aniDefine::SHIFTBIT::SUB,
	FEMALE_IDLE_NEUTRAL2	= 0x1 * (int)aniDefine::SHIFTBIT::SUB,
	FEMALE_IDLE_NEUTRAL3	= 0x2 * (int)aniDefine::SHIFTBIT::SUB,
	FEMALE_IDLE_ALERT		= 0x3 * (int)aniDefine::SHIFTBIT::SUB
};

enum FEMALE_DEAD
{
	FEMALE_DEAD_LEFT_FRONT	= 0x0 * (int)aniDefine::SHIFTBIT::SUB,
	FEMALE_DEAD_RIGHT_FRONT	= 0x1 * (int)aniDefine::SHIFTBIT::SUB,
	FEMALE_DEAD_MIDDLE_FRONT= 0x2 * (int)aniDefine::SHIFTBIT::SUB,
	FEMALE_DEAD_HEAD_FRONT	= 0x3 * (int)aniDefine::SHIFTBIT::SUB,
	FEMALE_DEAD_LEFT_BACK	= 0x4 * (int)aniDefine::SHIFTBIT::SUB,
	FEMALE_DEAD_RIGHT_BACK	= 0x5 * (int)aniDefine::SHIFTBIT::SUB,
	FEMALE_DEAD_MIDDLE_BACK	= 0x6 * (int)aniDefine::SHIFTBIT::SUB,
	FEMALE_DEAD_HEAD_BACK	= 0x7 * (int)aniDefine::SHIFTBIT::SUB
};

enum FEMALE_RUNNING_DEAD
{
	FEMALE_RD_HEAD			= 0x0 * (int)aniDefine::SHIFTBIT::SUB,
	FEMALE_RD_MIDDLE		= 0x1 * (int)aniDefine::SHIFTBIT::SUB,
	FEMALE_RD_ORDER			= 0x2 * (int)aniDefine::SHIFTBIT::SUB,
	FEMALE_RD_LEFT			= 0x3 * (int)aniDefine::SHIFTBIT::SUB,
	FEMALE_RD_RIGHT			= 0x4 * (int)aniDefine::SHIFTBIT::SUB
};

enum FEMALE_FALL
{
	FEMALE_FALL_FALLING		= 0x0 * (int)aniDefine::SHIFTBIT::SUB,
	FEMALE_FALL_LANDING		= 0x1 * (int)aniDefine::SHIFTBIT::SUB
};

enum FEMALE_TURN
{
	FEMALE_TURN_NONE		= 0x0 * (int)aniDefine::SHIFTBIT::SUB, 
	FEMALE_TURN_RIGHT		= 0x1 * (int)aniDefine::SHIFTBIT::SUB,
	FEMALE_TURN_LEFT		= 0x2 * (int)aniDefine::SHIFTBIT::SUB 

};

enum FEMALE_LYING
{
	FEMALE_LYING_BACKWARD	= 0x0 * (int)aniDefine::SHIFTBIT::SUB,
	FEMALE_LYING_LEFTWARD	= 0x1 * (int)aniDefine::SHIFTBIT::SUB,
	FEMALE_LYING_FRONTWARD	= 0x2 * (int)aniDefine::SHIFTBIT::SUB,
	FEMALE_LYING_RIGHTWARD	= 0x3 * (int)aniDefine::SHIFTBIT::SUB
};

enum FEMALE_WALK
{
	FEMALE_WALK_NORMAL		= 0x0 * (int)aniDefine::SHIFTBIT::SUB
};

enum FEMALE_ATTACK
{
	FEMALE_ATTACK_NONE		= 0x0 * (int)aniDefine::SHIFTBIT::SUB
};
	
enum FEMALE_RUN
{
	FEMALE_RUN_NONE			= 0x0 * (int)aniDefine::SHIFTBIT::SUB
};

enum FEMALE_SHOVED
{
	FEMALE_SHOVED_BACKWARD	= 0x0 * (int)aniDefine::SHIFTBIT::SUB,
	FEMALE_SHOVED_FRONTWARD	= 0x1 * (int)aniDefine::SHIFTBIT::SUB,
	FEMALE_SHOVED_BACK_RUN	= 0x2 * (int)aniDefine::SHIFTBIT::SUB,
	FEMALE_SHOVED_FRONT_RUN	= 0x3 * (int)aniDefine::SHIFTBIT::SUB
};

// HULK
enum HULK_MAIN
{
	HULK_FLINCH				= 0x0 * (int)aniDefine::SHIFTBIT::MAIN,
	HULK_DEAD				= 0x1 * (int)aniDefine::SHIFTBIT::MAIN,
	HULK_IDLE				= 0x2 * (int)aniDefine::SHIFTBIT::MAIN,
	HULK_JUMP				= 0x3 * (int)aniDefine::SHIFTBIT::MAIN,
	HULK_RUN				= 0x4 * (int)aniDefine::SHIFTBIT::MAIN,
	HULK_WALK				= 0x5 * (int)aniDefine::SHIFTBIT::MAIN,
	HULK_TURN				= 0x6 * (int)aniDefine::SHIFTBIT::MAIN,
	HULK_ATTACK				= 0x7 * (int)aniDefine::SHIFTBIT::MAIN,
	HULK_VICTORY			= 0x8 * (int)aniDefine::SHIFTBIT::MAIN
};

enum HULK_FLINCH
{
	HULK_FLINCH_CHEST		= 0x0 * (int)aniDefine::SHIFTBIT::SUB,
	HULK_FLINCH_LEFT		= 0x1 * (int)aniDefine::SHIFTBIT::SUB,
	HULK_FLINCH_RIGHT		= 0x2 * (int)aniDefine::SHIFTBIT::SUB,
	HULK_FLINCH_STOMACH		= 0x3 * (int)aniDefine::SHIFTBIT::SUB
};

enum HULK_DEAD
{
	HULK_DEAD_NORMAL		= 0x0 * (int)aniDefine::SHIFTBIT::SUB,
	HULK_DEAD_IDLE			= 0x1 * (int)aniDefine::SHIFTBIT::SUB,
	HULK_DEAD_RUNNING		= 0x2 * (int)aniDefine::SHIFTBIT::SUB
};

enum HULK_IDLE
{
	HULK_IDLE_NORMAL		= 0x0 * (int)aniDefine::SHIFTBIT::SUB,
	HULK_IDLE_YELL			= 0x1 * (int)aniDefine::SHIFTBIT::SUB,
	HULK_IDLE_SMASH			= 0x2 * (int)aniDefine::SHIFTBIT::SUB
};

enum HULK_JUMP
{
	HULK_JUMP_NONE			= 0x0 * (int)aniDefine::SHIFTBIT::SUB
};

enum HULK_RUN
{
	HULK_RUN_NORMAL			= 0x0 * (int)aniDefine::SHIFTBIT::SUB,
	HULK_RUN_RAGE			= 0x1 * (int)aniDefine::SHIFTBIT::SUB
};

enum HULK_WALK
{
	HULK_WALK_NONE			= 0x0 * (int)aniDefine::SHIFTBIT::SUB
};

enum HULK_TURN
{
	HULK_TURN_NONE			= 0x0 * (int)aniDefine::SHIFTBIT::SUB,
	HULK_TURN_LEFT			= 0x1 * (int)aniDefine::SHIFTBIT::SUB,
	HULK_TURN_RIGHT			= 0x2 * (int)aniDefine::SHIFTBIT::SUB
};

enum HULK_ATTACK
{
	HULK_ATTACK_RUN			= 0x0 * (int)aniDefine::SHIFTBIT::SUB,
	HULK_ATTACK_FLY			= 0x1 * (int)aniDefine::SHIFTBIT::SUB,
	HULK_ATTACK_NORMAL1		= 0x2 * (int)aniDefine::SHIFTBIT::SUB,
	HULK_ATTACK_NORMAL2		= 0x3 * (int)aniDefine::SHIFTBIT::SUB
};

enum HULK_VICTORY
{
	HULK_VICTORY_1			= 0x0 * (int)aniDefine::SHIFTBIT::SUB,
	HULK_VICTORY_2			= 0x1 * (int)aniDefine::SHIFTBIT::SUB
};

// SMOKER
enum SMOKER_MAIN
{
	SMOKER_IDLE				= 0x0 * (int)aniDefine::SHIFTBIT::MAIN,
	SMOKER_COUGH			= 0x1 * (int)aniDefine::SHIFTBIT::MAIN,
	SMOKER_ATTACK			= 0x2 * (int)aniDefine::SHIFTBIT::MAIN,
	SMOKER_SHOVED			= 0x3 * (int)aniDefine::SHIFTBIT::MAIN,
	SMOKER_FLINCH			= 0x4 * (int)aniDefine::SHIFTBIT::MAIN
};

enum SMOKER_IDLE
{
	SMOKER_IDLE_NONE		= 0x0 * (int)aniDefine::SHIFTBIT::SUB
};

enum SMOKER_COUGH
{
	SMOKER_COUGH_ATTACK		= 0x0 * (int)aniDefine::SHIFTBIT::SUB
};

enum SMOKER_ATTACK
{
	SMOKER_ATTACK_NORMAL	= 0x0 * (int)aniDefine::SHIFTBIT::SUB
};

enum SMOKER_SHOVED
{
	SMOKER_SHOVED_BACK		= 0x0 * (int)aniDefine::SHIFTBIT::SUB,
	SMOKER_SHOVED_FOR		= 0x1 * (int)aniDefine::SHIFTBIT::SUB,
	SMOKER_SHOVED_LEFT		= 0x2 * (int)aniDefine::SHIFTBIT::SUB,
	SMOKER_SHOVED_RIGHT		= 0x3 * (int)aniDefine::SHIFTBIT::SUB
};

enum SMOKER_FLINCH
{
	SMOKER_FLINCH_BACK		= 0x0 * (int)aniDefine::SHIFTBIT::SUB,
	SMOKER_FLINCH_CHEST		= 0x1 * (int)aniDefine::SHIFTBIT::SUB,
	SMOKER_FLINCH_HEAD		= 0x2 * (int)aniDefine::SHIFTBIT::SUB,
	SMOKER_FLINCH_LEFT		= 0x3 * (int)aniDefine::SHIFTBIT::SUB,
	SMOKER_FLINCH_LEFTLEG	= 0x4 * (int)aniDefine::SHIFTBIT::SUB,
	SMOKER_FLINCH_RIGHT		= 0x5 * (int)aniDefine::SHIFTBIT::SUB,
	SMOKER_FLINCH_RIGHTLEG	= 0x6 * (int)aniDefine::SHIFTBIT::SUB
};


// AIRPLANE
enum AIRPLANE_MAIN
{
	AIRPLANE_IDLE			= 0x0 * (int)aniDefine::SHIFTBIT::MAIN,
	AIRPLANE_OPEN			= 0x1 * (int)aniDefine::SHIFTBIT::MAIN,
	AIRPLANE_OUTRO			= 0x2 * (int)aniDefine::SHIFTBIT::MAIN
};

enum AIRPLANE_IDLE
{
	AIRPLANE_IDLE_ON		= 0x0 * (int)aniDefine::SHIFTBIT::SUB,
	AIRPLANE_IDLE_OFF		= 0x1 * (int)aniDefine::SHIFTBIT::SUB
};

enum AIRPLANE_OPEN
{
	AIRPLANE_OPEN_NONE		= 0x0 * (int)aniDefine::SHIFTBIT::SUB
};

enum AIRPLANE_OUTRO
{
	AIRPLANE_OUTRO_NONE		= 0x0 * (int)aniDefine::SHIFTBIT::SUB
};