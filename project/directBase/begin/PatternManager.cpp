#include "PatternManager.h"

PatternManager::PatternManager(void)
{
	initMotionSurvivor();
	initMaleZombie();
	initFemaleZombie();
	initHulkZombie();
	initSmokerZombie();
	initMotionAirplane();
}

PatternManager::~PatternManager(void)
{
}

void PatternManager::CreateMotion(int conditionCode, int * arr, int size, float timeScale, bool cancel)
{
	AniInfo motion;
	ZeroMemory(&motion, sizeof(motion));

	for (int i = 0; i < size; ++i)
	{
		motion.motionArray.push_back(arr[i]);
	}

	motion.timeScale = timeScale;
	motion.cancel = cancel;

	int type = conditionCode & GET_ANIBITMASK(aniDefine::ANIBIT::TYPE);

	_motionBook[type].insert(BOOK::value_type(conditionCode, motion));
}

void PatternManager::initMotionSurvivor(void)
{

	//	샘 플
	// 무기, 부상여부, 메인동작, 믹스여부, 세부동작
	//arr[0] = ;
	//this->CreateMotion(
	//	ATYPE_SURVIVOR |
	//	AWEAPON_NONE |
	//	ACONDITION_NONE |
	//	AMAIN_IDLE |
	//	AMIX_NONE |
	//	ASUB, arr, _count);

	int arr[10];
	//Survivor

	// 구급상자, 부상x, 가만히, 믹스x, 스텐딩
	arr[0] = 42;

	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_FIRSTAIDKIT |
		ACONDITION_NORMAL |
		AMAIN_IDLE |
		AMIX_NONE |
		AIDLE_STANDING, arr, 1, 0.8f, true);

	// 샷건, 부상x, 가만히, 믹스x, 스텐딩
	arr[0] = 43;

	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_PUMPSHOTGUN |
		ACONDITION_NORMAL |
		AMAIN_IDLE |
		AMIX_NONE |
		AIDLE_STANDING, arr, 1, 0.8f, true);

	// 라이플, 부상x, 가만히, 믹스x, 스텐딩
	arr[0] = 44;

	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_RIFLE |
		ACONDITION_NORMAL |
		AMAIN_IDLE |
		AMIX_NONE |
		AIDLE_STANDING, arr, 1, 0.8f, true);

	// 구급상자, 부상o, 가만히, 믹스x, 스텐딩
	arr[0] = 37;

	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_FIRSTAIDKIT |
		ACONDITION_INJURED |
		AMAIN_IDLE |
		AMIX_NONE |
		AIDLE_STANDING, arr, 1, 0.8f, true);

	// 샷건, 부상o, 가만히, 믹스x, 스텐딩
	arr[0] = 38;

	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_PUMPSHOTGUN |
		ACONDITION_INJURED |
		AMAIN_IDLE |
		AMIX_NONE |
		AIDLE_STANDING, arr, 1, 0.8f, true);

	// 라이플, 부상o, 가만히, 믹스x, 스텐딩
	arr[0] = 39;

	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_RIFLE |
		ACONDITION_INJURED |
		AMAIN_IDLE |
		AMIX_NONE |
		AIDLE_STANDING, arr, 1, 0.8f, true);

	// 구급상자, --, 가만히, 믹스x, 앉아
	arr[0] = 31;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_FIRSTAIDKIT |
		AMAIN_IDLE |
		AMIX_NONE |
		AIDLE_SIT, arr, 1, 1.0f, true);

	// 샷건, --, 가만히, 믹스x, 앉아
	arr[0] = 32;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_PUMPSHOTGUN |
		AMAIN_IDLE |
		AMIX_NONE |
		AIDLE_SIT, arr, 1, 1.0f, true);

	// 라이플, --, 가만히, 믹스x, 앉아
	arr[0] = 33;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_RIFLE |
		AMAIN_IDLE |
		AMIX_NONE |
		AIDLE_SIT, arr, 1, 1.0f, true);

	// 구급상자, --, 걷기, 믹스x, 스탠딩
	arr[0] = 90;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_FIRSTAIDKIT |
		AMAIN_WALK |
		AMIX_NONE |
		AWALK_STANDING, arr, 1, 0.8f, true);


	// 라이플, --, 걷기, 믹스x, 스텐딩
	arr[0] = 2;
	arr[1] = 92;

	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_RIFLE |
		AMAIN_WALK |
		AMIX_NONE |
		ARUN_STANDING, arr, 2, 0.8f, true);

	// 샷건, --, 걷기, 믹스x, 스텐딩
	arr[0] = 3;
	arr[1] = 91;

	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_PUMPSHOTGUN |
		AMAIN_WALK |
		AMIX_NONE |
		ARUN_STANDING, arr, 2, 0.8f, true);

	// 구급상자, --, 걷다, 믹스x, 앉아서
	arr[0] = 7;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_FIRSTAIDKIT |
		AMAIN_WALK |
		AMIX_NONE |
		AWALK_SIT, arr, 1, 0.6f, true);

	// 샷건, --, 걷다, 믹스x, 앉아서
	arr[0] = 8;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_PUMPSHOTGUN |
		AMAIN_WALK |
		AMIX_NONE |
		AWALK_SIT, arr, 1, 0.6f, true);

	// 라이플, --, 걷다, 믹스x, 앉아서
	arr[0] = 9;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_RIFLE |
		AMAIN_WALK |
		AMIX_NONE |
		AWALK_SIT, arr, 1, 0.6f, true);

	// 구급상자, --, 달리기, 믹스x, 스텐딩
	arr[0] = 77;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_FIRSTAIDKIT |
		AMAIN_RUN |
		AMIX_NONE |
		ARUN_STANDING, arr, 1, 0.8f, true);

	// 라이플, --, 달리기, 믹스x, 스텐딩
	arr[0] = 0;
	arr[1] = 79;

	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_RIFLE |
		AMAIN_RUN |
		AMIX_NONE |
		ARUN_STANDING, arr, 2, 0.8f, true);

	// 샷건, --, 달리기, 믹스x, 스텐딩
	arr[0] = 1;
	arr[1] = 78;

	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_PUMPSHOTGUN |
		AMAIN_RUN |
		AMIX_NONE |
		ARUN_STANDING, arr, 2, 0.8f, true);

	//{{임시
	// 구급상자, --, 달리기, 믹스x, 앉아서
	arr[0] = 7;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_FIRSTAIDKIT |
		AMAIN_RUN |
		AMIX_NONE |
		ARUN_SIT, arr, 1, 0.8f, true);

	// 샷건, --, 달리기, 믹스x, 앉아서
	arr[0] = 8;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_PUMPSHOTGUN |
		AMAIN_RUN |
		AMIX_NONE |
		ARUN_SIT, arr, 1, 0.8f, true);

	// 라이플, --, 달리기, 믹스x, 앉아서
	arr[0] = 9;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_RIFLE |
		AMAIN_RUN |
		AMIX_NONE |
		ARUN_SIT, arr, 1, 0.8f, true);
	//}}

	// 구급상자, --, 점프, 믹스x, 점프
	arr[0] = 52;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_FIRSTAIDKIT |
		AMAIN_JUMP |
		AMIX_NONE |
		AJUMP_JUMP, arr, 1, 1.0f, false);

	// 라이플, --, 점프, 믹스x, 점프
	arr[0] = 54;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_RIFLE |
		AMAIN_JUMP |
		AMIX_NONE |
		AJUMP_JUMP, arr, 1, 1.0f, false);

	// 샷건, --, 점프, 믹스x, 점프
	arr[0] = 56;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_PUMPSHOTGUN |
		AMAIN_JUMP |
		AMIX_NONE |
		AJUMP_JUMP, arr, 1, 1.0f, false);

	//--, --, 점프, 믹스x, 착지
	arr[0] = 53;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AMAIN_JUMP |
		AMIX_NONE |
		AJUMP_LAND, arr, 1, 0.8f, false);

	// --, --, 넘어지다, 믹스x, 뒤로
	arr[0] = 4;
	arr[1] = 5;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AMAIN_TRIP |
		AMIX_NONE |
		ATRIP_BACKWARD, arr, 2, 0.8f, false);

	// --, --, 넘어지다, 믹스x, 왼쪽으로
	arr[0] = 4;
	arr[1] = 6;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AMAIN_TRIP |
		AMIX_NONE |
		ATRIP_LEFTWARD, arr, 2, 0.8f, false);

	// --, -- , 일어나기, 믹스x, 뒤로
	arr[0] = 14;
	arr[1] = 17;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AMAIN_GETUP |
		AGETUP_BACKWARD,
		arr, 2, 0.8f, false);

	// --, -- , 일어나기, 믹스x, 옆으로
	arr[0] = 13;
	arr[1] = 17;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AMAIN_GETUP |
		AGETUP_LEFTWARD,
		arr, 2, 0.8f, false);

	// --, -- , 일어나기, 믹스x, 탱크펀치
	arr[0] = 18;
	arr[1] = 17;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AMAIN_GETUP |
		AGETUP_TANKPUNCH,
		arr, 2, 0.8f, false);

	// --, -- , 일어나기, 믹스x, 탱크ROCk
	arr[0] = 19;
	arr[1] = 17;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AMAIN_GETUP |
		AGETUP_TANKROCK,
		arr, 2, 0.8f, false);

	// --, --, 날아가는, 믹스x, 탱크펀치
	arr[0] = 34;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AMAIN_FLY |
		AMIX_NONE |
		AFLY_TANKPUNCH, arr, 1, 0.8f, true);

	// --, --, 날아가는, 믹스x, 떨어지는
	arr[0] = 36;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AMAIN_FLY |
		AMIX_NONE |
		AFLY_FALLING, arr, 1, 0.8f, true);

	// --, --, 날아가는, 믹스x, 혓바닥
	arr[0] = 35;
	//arr[1] = 36;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AMAIN_FLY |
		AMIX_NONE |
		AFLY_TONGUE, arr, 1, 0.8f, true);

	//--, --, 줍다, 믹스x, --
	arr[0] = 11;

	this->CreateMotion(
		ATYPE_SURVIVOR |
		AMAIN_DRAG |
		AMIX_NONE, arr, 1, 0.8f, false);

	// 구급상자, --, 치료, 믹스x, 스스로|서서
	//arr[0] = 23;
	arr[0] = 28;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_FIRSTAIDKIT |
		AMAIN_HEAL |
		AMIX_NONE |
		AHEAL_SELF_STANDING,
		arr, 1, 0.8f, false); //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	//구급상자, --, 치료, 믹스x, 스스로|앉아서
	arr[0] = 27;
	arr[1] = 26;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_FIRSTAIDKIT |
		AMAIN_HEAL |
		AMIX_NONE |
		AHEAL_SELF_SIT,
		arr, 2, 0.8f, true);


	//구급상자, --, 치료, 믹스x, 친구를|서서
	arr[0] = 20;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AMAIN_HEAL |
		AMIX_NONE |
		AHEAL_FRIEND_STANDING,
		arr, 1, 0.6f, true);


	//구급상자, --, 치료, 믹스x, 친구를|누워있는
	arr[0] = 23;
	arr[1] = 22;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AMAIN_HEAL |
		AMIX_NONE |
		AHEAL_FRIEND_LIE, arr, 2, 0.6f, true);

	// --, --, 죽다, 믹스x, --
	arr[0] = 10;
	arr[1] = 6; // 정확한 모션 필요 //DEAD_POS?
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AMAIN_DEAD |
		AMIX_NONE, arr, 2, 0.8f, false);

	// --, --, 스토커, 믹스x, 잡힌
	arr[0] = 45;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AMAIN_TONGUE |
		AMIX_NONE |
		ATONGUE_CATCH, arr, 1, 0.8f, false);

	// --, --, 스토커, 믹스x, 끌려가는
	arr[0] = 46;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AMAIN_TONGUE |
		AMIX_NONE |
		ATONGUE_DRAG, arr, 1, 0.8f, true);

	//// --, --, 스토커, 믹스x, 묶인
	//arr[0] = 4;
	//this->CreateMotion(
	//	ATYPE_SURVIVOR |
	//	AMAIN_TRIP |
	//	AMIX_NONE |
	//	ATRIP_LEFTWARD, arr, 1);

	// 샷건, --, --, 발사, --
	arr[0] = 80;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_PUMPSHOTGUN |
		AMIX_SHOOT, arr, 1, 0.6f, false);


	// 라이플, --, --, 발사, --
	arr[0] = 81;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_RIFLE |
		AMIX_SHOOT, arr, 1, 1.2f, false);

	// --, --, --, 근접공격, --
	//{
	arr[0] = 64;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_PUMPSHOTGUN |
		AMIX_ATTACK, arr, 1, 1.5f, false);

	arr[0] = 64;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_RIFLE |
		AMIX_ATTACK, arr, 1, 1.5f, false);
	//}

	// 샷건, --, --, 장전, --
	arr[0] = 72;
	//arr[1] = 73;
	//arr[2] = 74;
	//arr[3] = 75;
	//arr[4] = 71;3
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_PUMPSHOTGUN |
		AMIX_RELOAD, arr, 1, 0.8f, false);

	//라이플, --. --, 장전, --
	arr[0] = 76;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_RIFLE |
		AMIX_RELOAD, arr, 1, 0.7f, false);

	//샷건, --, --, 총뽑기, --
	arr[0] = 88;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_PUMPSHOTGUN |
		AMIX_UNHOLSTER, arr, 1, 1.2f, false);

	//라이플, --, --, 총뽑기, --
	arr[0] = 89;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_RIFLE |
		AMIX_UNHOLSTER, arr, 1, 1.2f, false);

	arr[0] = 89;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_FIRSTAIDKIT |
		AMIX_UNHOLSTER, arr, 1, 1.2f, false);
}

void PatternManager::initMaleZombie(void)
{
	//Male Zombie
	int arr[10];
	// 무기, 메인, 서브

	// --, 가만히, 경계
	arr[0] = 15;
	arr[1] = 16;
	arr[2] = 17;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		MALE_IDLE |
		MALE_IDLE_ALERT, arr, 3, 0.8f, true);

	// -- , 가만히, 대기1
	arr[0] = 22;
	arr[1] = 28;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		MALE_IDLE |
		MALE_IDLE_NEUTRAL1, arr, 2, 0.4f, true);

	// --, 가만히, 대기2
	//arr[0] = 27;
	arr[0] = 23;
	arr[1] = 28;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		MALE_IDLE |
		MALE_IDLE_NEUTRAL2, arr, 2, 0.4f, true);

	// --, 가만히, 대기3
	arr[0] = 27;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		MALE_IDLE |
		MALE_IDLE_NEUTRAL3, arr, 1, 0.4f, true);

	// 샷건, 피격, 왼쪽/앞
	arr[0] = 4;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_PUMPSHOTGUN |
		MALE_DEAD |
		MALE_DEAD_LEFT_FRONT,
		arr, 1, 0.8f, false);

	// 샷건, 피격, 오른쪽/앞
	arr[0] = 1;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_PUMPSHOTGUN |
		MALE_DEAD |
		MALE_DEAD_RIGHT_FRONT,
		arr, 1, 0.8f, false);

	// 샷건, 피격, 중간/앞
	arr[0] = 2;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_PUMPSHOTGUN |
		MALE_DEAD |
		MALE_DEAD_MIDDLE_FRONT,
		arr, 1, 1.0f, false);

	// 샷건, 피격, 머리/앞
	arr[0] = 5;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_PUMPSHOTGUN |
		MALE_DEAD |
		MALE_DEAD_HEAD_FRONT,
		arr, 1, 1.0f, false);

	//샷건, 피격, 왼쪽/뒤
	arr[0] = 1;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_PUMPSHOTGUN |
		MALE_DEAD |
		MALE_DEAD_LEFT_BACK,
		arr, 1, 0.8f, false);

	//샷건, 피격, 오른쪽/뒤
	arr[0] = 4;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_PUMPSHOTGUN |
		MALE_DEAD |
		MALE_DEAD_RIGHT_BACK,
		arr, 1, 0.8f, false);

	//샷건, 피격, 중간/뒤
	arr[0] = 2;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_PUMPSHOTGUN |
		MALE_DEAD |
		MALE_DEAD_MIDDLE_BACK,
		arr, 1, 1.0f, false);

	//샷건, 피격, 머리/뒤
	arr[0] = 37;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_PUMPSHOTGUN |
		MALE_DEAD |
		MALE_DEAD_HEAD_BACK,
		arr, 1, 0.8f, false);

	//라이플, 피격, 왼쪽/앞
	arr[0] = 0;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_RIFLE |
		MALE_DEAD |
		MALE_DEAD_LEFT_FRONT,
		arr, 1, 1.0f, false);

	//라이플, 피격, 오른쪽/앞
	arr[0] = 3;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_RIFLE |
		MALE_DEAD |
		MALE_DEAD_RIGHT_FRONT,
		arr, 1, 1.0f, false);

	//라이플, 피격, 중간/앞
	arr[0] = 0;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_RIFLE |
		MALE_DEAD |
		MALE_DEAD_MIDDLE_FRONT,
		arr, 1, 1.0f, false);

	//라이플, 피격, 머리/앞
	arr[0] = 5;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_RIFLE |
		MALE_DEAD |
		MALE_DEAD_HEAD_FRONT,
		arr, 1, 1.0f, false);

	//라이플, 피격, 왼쪽/뒤
	arr[0] = 3;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_RIFLE |
		MALE_DEAD |
		MALE_DEAD_LEFT_BACK,
		arr, 1, 1.0f, false);

	//라이플, 피격, 오른쪽/뒤
	arr[0] = 0;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_RIFLE |
		MALE_DEAD |
		MALE_DEAD_RIGHT_BACK,
		arr, 1, 1.0f, false);

	//라이플, 피격, 중간/뒤
	arr[0] = 0;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_RIFLE |
		MALE_DEAD |
		MALE_DEAD_MIDDLE_BACK,
		arr, 1, 1.0f, false);

	//라이플, 피격, 머리/뒤
	arr[0] = 37;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_RIFLE |
		MALE_DEAD |
		MALE_DEAD_HEAD_BACK,
		arr, 1, 0.8f, false);

	//샷건, 달리는중 피격, 머리
	arr[0] = 8;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_PUMPSHOTGUN |
		MALE_RUNNING_DEAD |
		MALE_RD_HEAD,
		arr, 1, 0.8f, false);

	//샷건, 달리는중 피격, 몸통
	arr[0] = 7;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_PUMPSHOTGUN |
		MALE_RUNNING_DEAD |
		MALE_RD_MIDDLE,
		arr, 1, 1.0f, false);

	//샷건, 달리는중 피격, 나머지 부분
	arr[0] = 9;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_PUMPSHOTGUN |
		MALE_RUNNING_DEAD |
		MALE_RD_ORDER,
		arr, 1, 1.0f, false);

	//라이플, 달리는중 피격, 머리
	arr[0] = 8;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_RIFLE |
		MALE_RUNNING_DEAD |
		MALE_RD_HEAD,
		arr, 1, 0.8f, false);

	//라이플, 달리는중 피격, 몸통
	arr[0] = 6;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_RIFLE |
		MALE_RUNNING_DEAD |
		MALE_RD_MIDDLE,
		arr, 1, 0.8f, false);

	//라이플, 달리는중 피격, 나머지 부분
	arr[0] = 9;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_RIFLE |
		MALE_RUNNING_DEAD |
		MALE_RD_ORDER,
		arr, 1, 1.0f, false);

	// --, 떨어지는 모션, NONE
	arr[0] = 10;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		MALE_FALL |
		MALE_FALL_NONE,
		arr, 1, 1.0f, true);

	// --, 회전, 오른쪽,
	arr[0] = 18;
	//arr[1] = 56;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		MALE_TURN |
		MALE_TURN_RIGHT,
		arr, 1, 0.8f, false);

	// --, 회전, 왼쪽
	arr[0] = 19;
	//arr[1] = 55;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		MALE_TURN |
		MALE_TURN_LEFT,
		arr, 1, 0.8f, false);

	// --, 눕기, 뒤로
	arr[0] = 31;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		MALE_LYING |
		MALE_LYING_BACKWARD,
		arr, 1, 0.8f, false);

	// --, 눕기, 왼쪽으로
	arr[0] = 30;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		MALE_LYING |
		MALE_LYING_LEFTWARD,
		arr, 1, 0.8f, false);

	// --, 눕기, 앞으로
	arr[0] = 37;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		MALE_LYING |
		MALE_LYING_FRONTWARD,
		arr, 1, 0.8f, false);

	// --, 걷기, 일반
	arr[0] = 35;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		MALE_WALK |
		MALE_WALK_NORMAL,
		arr, 1, 0.6f, true);

	// --, 걷기, 머리위로
	arr[0] = 36;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		MALE_WALK |
		MALE_WALK_HEADUP,
		arr, 1, 0.6f, true);

	// --, ATTACK, NONE
	arr[0] = 33;
	arr[1] = 34;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		MALE_ATTACK |
		MALE_ATTACK_NONE,
		arr, 2, 1.0f, true);

	// --, 달리기, NONE
	arr[0] = 39;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		MALE_RUN |
		MALE_RUN_NONE,
		arr, 1, 1.2f, true);

	// --, 밀쳐진, 뒤에서
	arr[0] = 42;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		MALE_SHOVED |
		MALE_SHOVED_BACKWARD,
		arr, 1, 0.8f, false);

	// --, 밀쳐진, 앞에서
	arr[0] = 44;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		MALE_SHOVED |
		MALE_SHOVED_FRONTWARD,
		arr, 1, 0.8f, false);

	// --, 밀쳐진, 달리는 도중 뒤에서
	arr[0] = 45;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		MALE_SHOVED |
		MALE_SHOVED_BACK_RUN,
		arr, 1, 0.8f, false);

	// --, 밀쳐진, 달리는 도중 앞에서
	arr[0] = 46;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		MALE_SHOVED |
		MALE_SHOVED_FRONT_RUN,
		arr, 1, 0.8f, false);
}

void PatternManager::initFemaleZombie(void)
{
	//Female Zombie
	int arr[10];

	// IDLE
	// --, 가만히, 경계
	//arr[0] = 27;
	//arr[0] = 28;
	arr[0] = 29;
	arr[1] = 30;
	arr[2] = 31;
	arr[3] = 32;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_IDLE |
		FEMALE_IDLE_ALERT,
		arr, 4, 0.6f, true);

	// --, 가만히, 대기1
	arr[0] = 48;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_IDLE |
		FEMALE_IDLE_NEUTRAL1,
		arr, 1, 0.6f, true);

	// --, 가만히, 대기2
	arr[0] = 47;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_IDLE |
		FEMALE_IDLE_NEUTRAL2,
		arr, 1, 0.6f, true);

	// --, 가만히, 대기3
	arr[0] = 49;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_IDLE |
		FEMALE_IDLE_NEUTRAL3,
		arr, 1, 0.6f, true);

	// DEAD

	// 샷건, 피격, 왼쪽/앞
	arr[0] = 9;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		AWEAPON_PUMPSHOTGUN |
		FEMALE_DEAD |
		FEMALE_DEAD_LEFT_FRONT,
		arr, 1, 0.8f, false);

	// 샷건, 피격, 오른쪽/앞
	arr[0] = 8;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		AWEAPON_PUMPSHOTGUN |
		FEMALE_DEAD |
		FEMALE_DEAD_RIGHT_FRONT,
		arr, 1, 0.8f, false);

	// 샷건, 피격, 중간/앞
	arr[0] = 7;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		AWEAPON_PUMPSHOTGUN |
		FEMALE_DEAD |
		FEMALE_DEAD_MIDDLE_FRONT,
		arr, 1, 1.0f, false);

	// 샷건, 피격, 머리/앞
	arr[0] = 6;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		AWEAPON_PUMPSHOTGUN |
		FEMALE_DEAD |
		FEMALE_DEAD_HEAD_FRONT,
		arr, 1, 1.0f, false);

	// 샷건, 피격, 왼쪽/뒤
	arr[0] = 8;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		AWEAPON_PUMPSHOTGUN |
		FEMALE_DEAD |
		FEMALE_DEAD_LEFT_BACK,
		arr, 1, 0.8f, false);

	// 샷건, 피격, 오른쪽/뒤
	arr[0] = 9;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		AWEAPON_PUMPSHOTGUN |
		FEMALE_DEAD |
		FEMALE_DEAD_RIGHT_BACK,
		arr, 1, 1.0f, false);

	// 샷건, 피격, 중간/ 뒤
	arr[0] = 7;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		AWEAPON_PUMPSHOTGUN |
		FEMALE_DEAD |
		FEMALE_DEAD_MIDDLE_BACK,
		arr, 1, 1.0f, false);

	// 샷건, 피격, 머리/뒤
	arr[0] = 25;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		AWEAPON_PUMPSHOTGUN |
		FEMALE_DEAD |
		FEMALE_DEAD_HEAD_BACK,
		arr, 1, 1.0f, false);

	// 라이플, 피격, 왼쪽/앞
	arr[0] = 5;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		AWEAPON_RIFLE |
		FEMALE_DEAD |
		FEMALE_DEAD_LEFT_FRONT,
		arr, 1, 1.0f, false);

	// 라이플, 피격, 오른쪽/앞
	arr[0] = 5;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		AWEAPON_RIFLE |
		FEMALE_DEAD |
		FEMALE_DEAD_RIGHT_FRONT,
		arr, 1, 1.0f, false);

	// 라이플, 피격, 중간/앞
	arr[0] = 2;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		AWEAPON_RIFLE |
		FEMALE_DEAD |
		FEMALE_DEAD_MIDDLE_FRONT,
		arr, 1, 1.0f, false);

	// 라이플, 피격, 머리/앞
	arr[0] = 3;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		AWEAPON_RIFLE |
		FEMALE_DEAD |
		FEMALE_DEAD_HEAD_FRONT,
		arr, 1, 1.2f, false);

	// 라이플, 피격, 왼쪽/뒤
	arr[0] = 5;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		AWEAPON_RIFLE |
		FEMALE_DEAD |
		FEMALE_DEAD_LEFT_BACK,
		arr, 1, 1.0f, false);

	// 라이플, 피격, 오른쪽/뒤
	arr[0] = 5;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		AWEAPON_RIFLE |
		FEMALE_DEAD |
		FEMALE_DEAD_RIGHT_BACK,
		arr, 1, 1.0f, false);

	// 라이플, 피격, 중간/ 뒤
	arr[0] = 2;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		AWEAPON_RIFLE |
		FEMALE_DEAD |
		FEMALE_DEAD_MIDDLE_BACK,
		arr, 1, 1.0f, false);

	// 라이플, 피격, 머리/뒤
	arr[0] = 25;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		AWEAPON_RIFLE |
		FEMALE_DEAD |
		FEMALE_DEAD_HEAD_BACK,
		arr, 1, 1.0f, false);


	// RUNNING_DEAD

	// --, 달리는 중 피격, 머리
	arr[0] = 19;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_RUNNING_DEAD |
		FEMALE_RD_HEAD,
		arr, 1, 1.0f, false);

	// --, 달리는 중 피격, 중간
	arr[0] = 17;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_RUNNING_DEAD |
		FEMALE_RD_MIDDLE,
		arr, 1, 1.0f, false);

	// --, 달리는 중 피격, 다른부위
	arr[0] = 21;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_RUNNING_DEAD |
		FEMALE_RD_ORDER,
		arr, 1, 1.0f, false);

	// FALL
	// -- , 떨어지는 모션, NONE
	arr[0] = 23;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_FALL |
		FEMALE_FALL_FALLING,
		arr, 1, 1.0f, false);

	arr[0] = 24;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_FALL |
		FEMALE_FALL_LANDING,
		arr, 1, 0.8f, false);

	// TURN
	// --, 회전, 오른쪽
	arr[0] = 44;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_TURN |
		FEMALE_TURN_RIGHT,
		arr, 1, 0.8f, true);

	// -- ,회전, 왼쪽
	arr[0] = 43;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_TURN |
		FEMALE_TURN_LEFT,
		arr, 1, 0.8f, false);

	// LYING
	// --, 눕는 동작, 뒤로
	arr[0] = 34;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_LYING |
		FEMALE_LYING_BACKWARD,
		arr, 1, 0.8f, false);

	// --, 눕는 동작, 왼쪽
	arr[0] = 33;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_LYING |
		FEMALE_LYING_LEFTWARD,
		arr, 1, 0.8f, false);

	// --, 눕는 동작, 앞으로
	arr[0] = 51;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_LYING |
		FEMALE_LYING_FRONTWARD,
		arr, 1, 0.8f, false);

	// --, 눕는 동작, 오른쪽으로
	arr[0] = 37;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_LYING |
		FEMALE_LYING_RIGHTWARD,
		arr, 1, 0.8f, false);

	// WALK
	// --, 걷는 동작, NONE
	arr[0] = 22;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_WALK |
		FEMALE_WALK_NORMAL,
		arr, 1, 0.8f, true);

	// ATTACK
	// --, 공격, NONE
	arr[0] = 41;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_ATTACK |
		FEMALE_ATTACK_NONE,
		arr, 1, 1.0f, false);

	// RUN
	// --, 달리기, NONE
	arr[0] = 50;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_RUN |
		FEMALE_RUN_NONE,
		arr, 1, 1.5f, true);

	// SHOVED
	// --, 밀린 동작, 뒤에서
	arr[0] = 7;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_SHOVED |
		FEMALE_SHOVED_BACKWARD,
		arr, 1, 1.0f, false);

	// --, 밀린 동작, 앞에서
	arr[0] = 12;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_SHOVED |
		FEMALE_SHOVED_FRONTWARD,
		arr, 1, 0.8f, false);

	// --, 밀린 동작, 달리는 도중 뒤에서
	arr[0] = 21;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_SHOVED |
		FEMALE_SHOVED_BACK_RUN,
		arr, 1, 1.0f, false);

	// --, 밀린 동작, 달리는 도중 앞에서
	arr[0] = 19;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_SHOVED |
		FEMALE_SHOVED_FRONT_RUN,
		arr, 1, 1.0f, false);
}

void PatternManager::initHulkZombie(void)
{
	int arr[10];
	//Hulk Zombie
	// FLINCH
	// 움찔거리는, 가슴
	arr[0] = 0;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_FLINCH |
		HULK_FLINCH_CHEST,
		arr, 1, 1.0f, false);

	// 움찔거리는, 왼쪽
	arr[0] = 1;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_FLINCH |
		HULK_FLINCH_LEFT,
		arr, 1, 1.0f, false);

	// 움찔거리는, 오른쪽
	arr[0] = 2;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_FLINCH |
		HULK_FLINCH_RIGHT,
		arr, 1, 1.0f, false);

	// 움찔거리는, 복부
	arr[0] = 3;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_FLINCH |
		HULK_FLINCH_STOMACH,
		arr, 1, 1.0f, false);

	// DEAD
	// 죽음, 노말
	arr[0] = 4;
	arr[1] = 31;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_DEAD |
		HULK_DEAD_NORMAL,
		arr, 2, 1.0f, false);

	// 죽음, 대기
	arr[0] = 5;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_DEAD |
		HULK_DEAD_IDLE,
		arr, 1, 1.0f, false);

	// 죽음, 달리는 중
	arr[0] = 6;
	arr[1] = 31;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_DEAD |
		HULK_DEAD_RUNNING,
		arr, 2, 1.0f, false);

	// IDLE
	// 대기, 노말
	arr[0] = 18;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_IDLE |
		HULK_IDLE_NORMAL,
		arr, 1, 1.0f, true);

	// 대기, 소리지르는
	arr[0] = 19;
	arr[1] = 20;
	arr[2] = 27;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_IDLE |
		HULK_IDLE_YELL,
		arr, 3, 0.8f, true);


	// 대기, 땅을 내려치는
	arr[0] = 23;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_IDLE |
		HULK_IDLE_SMASH,
		arr, 1, 1.2f, true);


	// JUMP
	//점프, 노말
	arr[0] = 22;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_JUMP |
		HULK_JUMP_NONE,
		arr, 1, 1.0f, false);

	// RUN
	// 달리기, 노말
	arr[0] = 36;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_RUN |
		HULK_RUN_NORMAL,
		arr, 1, 1.0f, true);

	// 달리기, 화난
	arr[0] = 30;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_RUN |
		HULK_RUN_RAGE,
		arr, 1, 1.0f, true);

	// WALK
	// 걷기, NONE
	arr[0] = 17;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_WALK |
		HULK_WALK_NONE,
		arr, 1, 1.0f, true);

	// TURN
	// 회전, 왼쪽
	arr[0] = 49;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_TURN |
		HULK_TURN_LEFT,
		arr, 1, 0.6f, true);

	// 회전, 오른쪽
	arr[0] = 50;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_TURN |
		HULK_TURN_RIGHT,
		arr, 1, 0.6f, true);

	// ATTACK
	// 공격, 달리기
	arr[0] = 11;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_ATTACK |
		HULK_ATTACK_RUN,
		arr, 1, 1.0f, false);

	// 공격, 날리기
	arr[0] = 38;
	arr[1] = 39;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_ATTACK |
		HULK_ATTACK_FLY,
		arr, 2, 1.0f, false);

	// 공격, 기본1
	arr[0] = 8;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_ATTACK |
		HULK_ATTACK_NORMAL1,
		arr, 1, 1.0f, false);

	// 공격, 기본2
	arr[0] = 48;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_ATTACK |
		HULK_ATTACK_NORMAL2,
		arr, 1, 1.0f, false);

	// VICTORY
	// 승리, 승리1
	arr[0] = 44;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_VICTORY |
		HULK_VICTORY_1,
		arr, 1, 0.7f, true);

	// 승리, 승리2
	arr[0] = 45;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_VICTORY |
		HULK_VICTORY_2,
		arr, 1, 0.6f, true);
}

void PatternManager::initSmokerZombie(void)
{
	int arr[10];
	//Smoker Zombie
	// 가만히, NONE
	arr[0] = 0;
	this->CreateMotion(
		ATYPE_ZOMBIE_SMOKER |
		SMOKER_IDLE |
		SMOKER_IDLE_NONE,
		arr, 1, 0.8f, true);

	// 혓바닥, 공격
	arr[0] = 1;
	this->CreateMotion(
		ATYPE_ZOMBIE_SMOKER |
		SMOKER_COUGH |
		SMOKER_COUGH_ATTACK,
		arr, 1, 1.0f, true);

	// 공격, 기본
	arr[0] = 4;
	arr[1] = 5;
	this->CreateMotion(
		ATYPE_ZOMBIE_SMOKER |
		SMOKER_ATTACK |
		SMOKER_ATTACK_NORMAL,
		arr, 2, 1.0f, false);

	// 밀처진, 뒤에서
	arr[0] = 7;
	this->CreateMotion(
		ATYPE_ZOMBIE_SMOKER |
		SMOKER_SHOVED |
		SMOKER_SHOVED_BACK,
		arr, 1, 1.0f, false);

	// 밀쳐진, 앞에서
	arr[0] = 8;
	this->CreateMotion(
		ATYPE_ZOMBIE_SMOKER |
		SMOKER_SHOVED |
		SMOKER_SHOVED_FOR,
		arr, 1, 1.0f, false);

	// 밀처진, 왼쪽에서
	arr[0] = 9;
	this->CreateMotion(
		ATYPE_ZOMBIE_SMOKER |
		SMOKER_SHOVED |
		SMOKER_SHOVED_LEFT,
		arr, 1, 1.0f, false);

	// 밀처진, 오른쪽에서
	arr[0] = 10;
	this->CreateMotion(
		ATYPE_ZOMBIE_SMOKER |
		SMOKER_SHOVED |
		SMOKER_SHOVED_RIGHT,
		arr, 1, 1.0f, false);

	// 움찔하는, 뒤에서
	arr[0] = 11;
	this->CreateMotion(
		ATYPE_ZOMBIE_SMOKER |
		SMOKER_FLINCH |
		SMOKER_FLINCH_BACK,
		arr, 1, 0.8f, false);

	// 움찔하는, 가슴
	arr[0] = 12;
	this->CreateMotion(
		ATYPE_ZOMBIE_SMOKER |
		SMOKER_FLINCH |
		SMOKER_FLINCH_CHEST,
		arr, 1, 0.8f, false);

	// 움찔하는, 머리
	arr[0] = 13;
	this->CreateMotion(
		ATYPE_ZOMBIE_SMOKER |
		SMOKER_FLINCH |
		SMOKER_FLINCH_HEAD,
		arr, 1, 0.8f, false);

	// 움찔하는, 왼쪽
	arr[0] = 14;
	this->CreateMotion(
		ATYPE_ZOMBIE_SMOKER |
		SMOKER_FLINCH |
		SMOKER_FLINCH_LEFT,
		arr, 1, 0.8f, false);

	// 움찔하는, 왼쪽다리
	arr[0] = 15;
	this->CreateMotion(
		ATYPE_ZOMBIE_SMOKER |
		SMOKER_FLINCH |
		SMOKER_FLINCH_LEFTLEG,
		arr, 1, 0.8f, false);

	// 움찔하는, 오른쪽
	arr[0] = 16;
	this->CreateMotion(
		ATYPE_ZOMBIE_SMOKER |
		SMOKER_FLINCH |
		SMOKER_FLINCH_RIGHT,
		arr, 1, 0.8f, false);

	// 움찔하는, 오른쪽다리
	arr[0] = 17;
	this->CreateMotion(
		ATYPE_ZOMBIE_SMOKER |
		SMOKER_FLINCH |
		SMOKER_FLINCH_RIGHTLEG,
		arr, 1, 0.8f, false);
}

void PatternManager::initMotionAirplane(void)
{
	//Air plane
	int arr[10];
	// 가만히, 시동on
	arr[0] = 0;
	this->CreateMotion(
		ATYPE_AIRPLANE |
		AIRPLANE_IDLE |
		AIRPLANE_IDLE_ON,
		arr, 1, 1.0f, true);

	// 가만히, 시동off
	arr[0] = 1;
	this->CreateMotion(
		ATYPE_AIRPLANE |
		AIRPLANE_IDLE |
		AIRPLANE_IDLE_OFF,
		arr, 1, 1.0f, true);

	// 문, 열리고 있는 상태
	arr[0] = 3;
	arr[1] = 2;
	this->CreateMotion(
		ATYPE_AIRPLANE |
		AIRPLANE_OPEN |
		AIRPLANE_OPEN_NONE,
		arr, 2, 2.0f, false);

	// 출발
	arr[0] = 4;
	this->CreateMotion(
		ATYPE_AIRPLANE |
		AIRPLANE_OUTRO |
		AIRPLANE_OUTRO_NONE,
		arr, 1, 1.0f, false);
}

PatternManager::AniInfo & PatternManager::getPattern(int conditionCode)
{
	auto cashIterator = _cashingPattern.find(conditionCode);
	if (cashIterator != _cashingPattern.end())
	{
		return cashIterator->second;
	}

	int type = conditionCode & GET_ANIBITMASK(aniDefine::ANIBIT::TYPE);
	auto iterator = (_motionBook[type].find(conditionCode));

	if (iterator != _motionBook[type].end())
	{
		_cashingPattern.insert(BOOK::value_type(conditionCode, iterator->second));
		return iterator->second;
	}
	else
	{
		//동작을 못 찾았을 경우
		if ((conditionCode & GET_ANIBITMASK(aniDefine::ANIBIT::CONDITION)) != 0)
		{
			int findCode = conditionCode - (conditionCode & GET_ANIBITMASK(aniDefine::ANIBIT::CONDITION));
			PatternManager::AniInfo &check = getPattern(findCode);
			if (_motionBook[type].begin()->second != check) return check;
		}

		if ((conditionCode & GET_ANIBITMASK(aniDefine::ANIBIT::WEAPON)) != 0)
		{
			int findCode = conditionCode - (conditionCode & GET_ANIBITMASK(aniDefine::ANIBIT::WEAPON));
			PatternManager::AniInfo &check = getPattern(findCode);
			if (_motionBook[type].begin()->second != check) return check;
		}

		if ((conditionCode & GET_ANIBITMASK(aniDefine::ANIBIT::SUB)) != 0)
		{
			int findCode = conditionCode - (conditionCode & GET_ANIBITMASK(aniDefine::ANIBIT::SUB));
			PatternManager::AniInfo &check = getPattern(findCode);
			if (_motionBook[type].begin()->second != check) return check;
		}
	}

	return _motionBook[type].begin()->second;
}
