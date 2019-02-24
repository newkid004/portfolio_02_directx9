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

	//	�� ��
	// ����, �λ󿩺�, ���ε���, �ͽ�����, ���ε���
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

	// ���޻���, �λ�x, ������, �ͽ�x, ���ٵ�
	arr[0] = 42;

	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_FIRSTAIDKIT |
		ACONDITION_NORMAL |
		AMAIN_IDLE |
		AMIX_NONE |
		AIDLE_STANDING, arr, 1, 0.8f, true);

	// ����, �λ�x, ������, �ͽ�x, ���ٵ�
	arr[0] = 43;

	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_PUMPSHOTGUN |
		ACONDITION_NORMAL |
		AMAIN_IDLE |
		AMIX_NONE |
		AIDLE_STANDING, arr, 1, 0.8f, true);

	// ������, �λ�x, ������, �ͽ�x, ���ٵ�
	arr[0] = 44;

	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_RIFLE |
		ACONDITION_NORMAL |
		AMAIN_IDLE |
		AMIX_NONE |
		AIDLE_STANDING, arr, 1, 0.8f, true);

	// ���޻���, �λ�o, ������, �ͽ�x, ���ٵ�
	arr[0] = 37;

	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_FIRSTAIDKIT |
		ACONDITION_INJURED |
		AMAIN_IDLE |
		AMIX_NONE |
		AIDLE_STANDING, arr, 1, 0.8f, true);

	// ����, �λ�o, ������, �ͽ�x, ���ٵ�
	arr[0] = 38;

	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_PUMPSHOTGUN |
		ACONDITION_INJURED |
		AMAIN_IDLE |
		AMIX_NONE |
		AIDLE_STANDING, arr, 1, 0.8f, true);

	// ������, �λ�o, ������, �ͽ�x, ���ٵ�
	arr[0] = 39;

	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_RIFLE |
		ACONDITION_INJURED |
		AMAIN_IDLE |
		AMIX_NONE |
		AIDLE_STANDING, arr, 1, 0.8f, true);

	// ���޻���, --, ������, �ͽ�x, �ɾ�
	arr[0] = 31;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_FIRSTAIDKIT |
		AMAIN_IDLE |
		AMIX_NONE |
		AIDLE_SIT, arr, 1, 1.0f, true);

	// ����, --, ������, �ͽ�x, �ɾ�
	arr[0] = 32;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_PUMPSHOTGUN |
		AMAIN_IDLE |
		AMIX_NONE |
		AIDLE_SIT, arr, 1, 1.0f, true);

	// ������, --, ������, �ͽ�x, �ɾ�
	arr[0] = 33;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_RIFLE |
		AMAIN_IDLE |
		AMIX_NONE |
		AIDLE_SIT, arr, 1, 1.0f, true);

	// ���޻���, --, �ȱ�, �ͽ�x, ���ĵ�
	arr[0] = 90;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_FIRSTAIDKIT |
		AMAIN_WALK |
		AMIX_NONE |
		AWALK_STANDING, arr, 1, 0.8f, true);


	// ������, --, �ȱ�, �ͽ�x, ���ٵ�
	arr[0] = 2;
	arr[1] = 92;

	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_RIFLE |
		AMAIN_WALK |
		AMIX_NONE |
		ARUN_STANDING, arr, 2, 0.8f, true);

	// ����, --, �ȱ�, �ͽ�x, ���ٵ�
	arr[0] = 3;
	arr[1] = 91;

	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_PUMPSHOTGUN |
		AMAIN_WALK |
		AMIX_NONE |
		ARUN_STANDING, arr, 2, 0.8f, true);

	// ���޻���, --, �ȴ�, �ͽ�x, �ɾƼ�
	arr[0] = 7;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_FIRSTAIDKIT |
		AMAIN_WALK |
		AMIX_NONE |
		AWALK_SIT, arr, 1, 0.6f, true);

	// ����, --, �ȴ�, �ͽ�x, �ɾƼ�
	arr[0] = 8;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_PUMPSHOTGUN |
		AMAIN_WALK |
		AMIX_NONE |
		AWALK_SIT, arr, 1, 0.6f, true);

	// ������, --, �ȴ�, �ͽ�x, �ɾƼ�
	arr[0] = 9;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_RIFLE |
		AMAIN_WALK |
		AMIX_NONE |
		AWALK_SIT, arr, 1, 0.6f, true);

	// ���޻���, --, �޸���, �ͽ�x, ���ٵ�
	arr[0] = 77;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_FIRSTAIDKIT |
		AMAIN_RUN |
		AMIX_NONE |
		ARUN_STANDING, arr, 1, 0.8f, true);

	// ������, --, �޸���, �ͽ�x, ���ٵ�
	arr[0] = 0;
	arr[1] = 79;

	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_RIFLE |
		AMAIN_RUN |
		AMIX_NONE |
		ARUN_STANDING, arr, 2, 0.8f, true);

	// ����, --, �޸���, �ͽ�x, ���ٵ�
	arr[0] = 1;
	arr[1] = 78;

	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_PUMPSHOTGUN |
		AMAIN_RUN |
		AMIX_NONE |
		ARUN_STANDING, arr, 2, 0.8f, true);

	//{{�ӽ�
	// ���޻���, --, �޸���, �ͽ�x, �ɾƼ�
	arr[0] = 7;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_FIRSTAIDKIT |
		AMAIN_RUN |
		AMIX_NONE |
		ARUN_SIT, arr, 1, 0.8f, true);

	// ����, --, �޸���, �ͽ�x, �ɾƼ�
	arr[0] = 8;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_PUMPSHOTGUN |
		AMAIN_RUN |
		AMIX_NONE |
		ARUN_SIT, arr, 1, 0.8f, true);

	// ������, --, �޸���, �ͽ�x, �ɾƼ�
	arr[0] = 9;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_RIFLE |
		AMAIN_RUN |
		AMIX_NONE |
		ARUN_SIT, arr, 1, 0.8f, true);
	//}}

	// ���޻���, --, ����, �ͽ�x, ����
	arr[0] = 52;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_FIRSTAIDKIT |
		AMAIN_JUMP |
		AMIX_NONE |
		AJUMP_JUMP, arr, 1, 1.0f, false);

	// ������, --, ����, �ͽ�x, ����
	arr[0] = 54;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_RIFLE |
		AMAIN_JUMP |
		AMIX_NONE |
		AJUMP_JUMP, arr, 1, 1.0f, false);

	// ����, --, ����, �ͽ�x, ����
	arr[0] = 56;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_PUMPSHOTGUN |
		AMAIN_JUMP |
		AMIX_NONE |
		AJUMP_JUMP, arr, 1, 1.0f, false);

	//--, --, ����, �ͽ�x, ����
	arr[0] = 53;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AMAIN_JUMP |
		AMIX_NONE |
		AJUMP_LAND, arr, 1, 0.8f, false);

	// --, --, �Ѿ�����, �ͽ�x, �ڷ�
	arr[0] = 4;
	arr[1] = 5;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AMAIN_TRIP |
		AMIX_NONE |
		ATRIP_BACKWARD, arr, 2, 0.8f, false);

	// --, --, �Ѿ�����, �ͽ�x, ��������
	arr[0] = 4;
	arr[1] = 6;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AMAIN_TRIP |
		AMIX_NONE |
		ATRIP_LEFTWARD, arr, 2, 0.8f, false);

	// --, -- , �Ͼ��, �ͽ�x, �ڷ�
	arr[0] = 14;
	arr[1] = 17;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AMAIN_GETUP |
		AGETUP_BACKWARD,
		arr, 2, 0.8f, false);

	// --, -- , �Ͼ��, �ͽ�x, ������
	arr[0] = 13;
	arr[1] = 17;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AMAIN_GETUP |
		AGETUP_LEFTWARD,
		arr, 2, 0.8f, false);

	// --, -- , �Ͼ��, �ͽ�x, ��ũ��ġ
	arr[0] = 18;
	arr[1] = 17;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AMAIN_GETUP |
		AGETUP_TANKPUNCH,
		arr, 2, 0.8f, false);

	// --, -- , �Ͼ��, �ͽ�x, ��ũROCk
	arr[0] = 19;
	arr[1] = 17;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AMAIN_GETUP |
		AGETUP_TANKROCK,
		arr, 2, 0.8f, false);

	// --, --, ���ư���, �ͽ�x, ��ũ��ġ
	arr[0] = 34;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AMAIN_FLY |
		AMIX_NONE |
		AFLY_TANKPUNCH, arr, 1, 0.8f, true);

	// --, --, ���ư���, �ͽ�x, ��������
	arr[0] = 36;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AMAIN_FLY |
		AMIX_NONE |
		AFLY_FALLING, arr, 1, 0.8f, true);

	// --, --, ���ư���, �ͽ�x, ���ٴ�
	arr[0] = 35;
	//arr[1] = 36;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AMAIN_FLY |
		AMIX_NONE |
		AFLY_TONGUE, arr, 1, 0.8f, true);

	//--, --, �ݴ�, �ͽ�x, --
	arr[0] = 11;

	this->CreateMotion(
		ATYPE_SURVIVOR |
		AMAIN_DRAG |
		AMIX_NONE, arr, 1, 0.8f, false);

	// ���޻���, --, ġ��, �ͽ�x, ������|����
	//arr[0] = 23;
	arr[0] = 28;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_FIRSTAIDKIT |
		AMAIN_HEAL |
		AMIX_NONE |
		AHEAL_SELF_STANDING,
		arr, 1, 0.8f, false); //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	//���޻���, --, ġ��, �ͽ�x, ������|�ɾƼ�
	arr[0] = 27;
	arr[1] = 26;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_FIRSTAIDKIT |
		AMAIN_HEAL |
		AMIX_NONE |
		AHEAL_SELF_SIT,
		arr, 2, 0.8f, true);


	//���޻���, --, ġ��, �ͽ�x, ģ����|����
	arr[0] = 20;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AMAIN_HEAL |
		AMIX_NONE |
		AHEAL_FRIEND_STANDING,
		arr, 1, 0.6f, true);


	//���޻���, --, ġ��, �ͽ�x, ģ����|�����ִ�
	arr[0] = 23;
	arr[1] = 22;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AMAIN_HEAL |
		AMIX_NONE |
		AHEAL_FRIEND_LIE, arr, 2, 0.6f, true);

	// --, --, �״�, �ͽ�x, --
	arr[0] = 10;
	arr[1] = 6; // ��Ȯ�� ��� �ʿ� //DEAD_POS?
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AMAIN_DEAD |
		AMIX_NONE, arr, 2, 0.8f, false);

	// --, --, ����Ŀ, �ͽ�x, ����
	arr[0] = 45;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AMAIN_TONGUE |
		AMIX_NONE |
		ATONGUE_CATCH, arr, 1, 0.8f, false);

	// --, --, ����Ŀ, �ͽ�x, ��������
	arr[0] = 46;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AMAIN_TONGUE |
		AMIX_NONE |
		ATONGUE_DRAG, arr, 1, 0.8f, true);

	//// --, --, ����Ŀ, �ͽ�x, ����
	//arr[0] = 4;
	//this->CreateMotion(
	//	ATYPE_SURVIVOR |
	//	AMAIN_TRIP |
	//	AMIX_NONE |
	//	ATRIP_LEFTWARD, arr, 1);

	// ����, --, --, �߻�, --
	arr[0] = 80;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_PUMPSHOTGUN |
		AMIX_SHOOT, arr, 1, 0.6f, false);


	// ������, --, --, �߻�, --
	arr[0] = 81;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_RIFLE |
		AMIX_SHOOT, arr, 1, 1.2f, false);

	// --, --, --, ��������, --
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

	// ����, --, --, ����, --
	arr[0] = 72;
	//arr[1] = 73;
	//arr[2] = 74;
	//arr[3] = 75;
	//arr[4] = 71;3
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_PUMPSHOTGUN |
		AMIX_RELOAD, arr, 1, 0.8f, false);

	//������, --. --, ����, --
	arr[0] = 76;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_RIFLE |
		AMIX_RELOAD, arr, 1, 0.7f, false);

	//����, --, --, �ѻ̱�, --
	arr[0] = 88;
	this->CreateMotion(
		ATYPE_SURVIVOR |
		AWEAPON_PUMPSHOTGUN |
		AMIX_UNHOLSTER, arr, 1, 1.2f, false);

	//������, --, --, �ѻ̱�, --
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
	// ����, ����, ����

	// --, ������, ���
	arr[0] = 15;
	arr[1] = 16;
	arr[2] = 17;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		MALE_IDLE |
		MALE_IDLE_ALERT, arr, 3, 0.8f, true);

	// -- , ������, ���1
	arr[0] = 22;
	arr[1] = 28;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		MALE_IDLE |
		MALE_IDLE_NEUTRAL1, arr, 2, 0.4f, true);

	// --, ������, ���2
	//arr[0] = 27;
	arr[0] = 23;
	arr[1] = 28;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		MALE_IDLE |
		MALE_IDLE_NEUTRAL2, arr, 2, 0.4f, true);

	// --, ������, ���3
	arr[0] = 27;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		MALE_IDLE |
		MALE_IDLE_NEUTRAL3, arr, 1, 0.4f, true);

	// ����, �ǰ�, ����/��
	arr[0] = 4;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_PUMPSHOTGUN |
		MALE_DEAD |
		MALE_DEAD_LEFT_FRONT,
		arr, 1, 0.8f, false);

	// ����, �ǰ�, ������/��
	arr[0] = 1;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_PUMPSHOTGUN |
		MALE_DEAD |
		MALE_DEAD_RIGHT_FRONT,
		arr, 1, 0.8f, false);

	// ����, �ǰ�, �߰�/��
	arr[0] = 2;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_PUMPSHOTGUN |
		MALE_DEAD |
		MALE_DEAD_MIDDLE_FRONT,
		arr, 1, 1.0f, false);

	// ����, �ǰ�, �Ӹ�/��
	arr[0] = 5;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_PUMPSHOTGUN |
		MALE_DEAD |
		MALE_DEAD_HEAD_FRONT,
		arr, 1, 1.0f, false);

	//����, �ǰ�, ����/��
	arr[0] = 1;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_PUMPSHOTGUN |
		MALE_DEAD |
		MALE_DEAD_LEFT_BACK,
		arr, 1, 0.8f, false);

	//����, �ǰ�, ������/��
	arr[0] = 4;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_PUMPSHOTGUN |
		MALE_DEAD |
		MALE_DEAD_RIGHT_BACK,
		arr, 1, 0.8f, false);

	//����, �ǰ�, �߰�/��
	arr[0] = 2;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_PUMPSHOTGUN |
		MALE_DEAD |
		MALE_DEAD_MIDDLE_BACK,
		arr, 1, 1.0f, false);

	//����, �ǰ�, �Ӹ�/��
	arr[0] = 37;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_PUMPSHOTGUN |
		MALE_DEAD |
		MALE_DEAD_HEAD_BACK,
		arr, 1, 0.8f, false);

	//������, �ǰ�, ����/��
	arr[0] = 0;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_RIFLE |
		MALE_DEAD |
		MALE_DEAD_LEFT_FRONT,
		arr, 1, 1.0f, false);

	//������, �ǰ�, ������/��
	arr[0] = 3;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_RIFLE |
		MALE_DEAD |
		MALE_DEAD_RIGHT_FRONT,
		arr, 1, 1.0f, false);

	//������, �ǰ�, �߰�/��
	arr[0] = 0;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_RIFLE |
		MALE_DEAD |
		MALE_DEAD_MIDDLE_FRONT,
		arr, 1, 1.0f, false);

	//������, �ǰ�, �Ӹ�/��
	arr[0] = 5;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_RIFLE |
		MALE_DEAD |
		MALE_DEAD_HEAD_FRONT,
		arr, 1, 1.0f, false);

	//������, �ǰ�, ����/��
	arr[0] = 3;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_RIFLE |
		MALE_DEAD |
		MALE_DEAD_LEFT_BACK,
		arr, 1, 1.0f, false);

	//������, �ǰ�, ������/��
	arr[0] = 0;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_RIFLE |
		MALE_DEAD |
		MALE_DEAD_RIGHT_BACK,
		arr, 1, 1.0f, false);

	//������, �ǰ�, �߰�/��
	arr[0] = 0;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_RIFLE |
		MALE_DEAD |
		MALE_DEAD_MIDDLE_BACK,
		arr, 1, 1.0f, false);

	//������, �ǰ�, �Ӹ�/��
	arr[0] = 37;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_RIFLE |
		MALE_DEAD |
		MALE_DEAD_HEAD_BACK,
		arr, 1, 0.8f, false);

	//����, �޸����� �ǰ�, �Ӹ�
	arr[0] = 8;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_PUMPSHOTGUN |
		MALE_RUNNING_DEAD |
		MALE_RD_HEAD,
		arr, 1, 0.8f, false);

	//����, �޸����� �ǰ�, ����
	arr[0] = 7;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_PUMPSHOTGUN |
		MALE_RUNNING_DEAD |
		MALE_RD_MIDDLE,
		arr, 1, 1.0f, false);

	//����, �޸����� �ǰ�, ������ �κ�
	arr[0] = 9;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_PUMPSHOTGUN |
		MALE_RUNNING_DEAD |
		MALE_RD_ORDER,
		arr, 1, 1.0f, false);

	//������, �޸����� �ǰ�, �Ӹ�
	arr[0] = 8;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_RIFLE |
		MALE_RUNNING_DEAD |
		MALE_RD_HEAD,
		arr, 1, 0.8f, false);

	//������, �޸����� �ǰ�, ����
	arr[0] = 6;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_RIFLE |
		MALE_RUNNING_DEAD |
		MALE_RD_MIDDLE,
		arr, 1, 0.8f, false);

	//������, �޸����� �ǰ�, ������ �κ�
	arr[0] = 9;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		AWEAPON_RIFLE |
		MALE_RUNNING_DEAD |
		MALE_RD_ORDER,
		arr, 1, 1.0f, false);

	// --, �������� ���, NONE
	arr[0] = 10;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		MALE_FALL |
		MALE_FALL_NONE,
		arr, 1, 1.0f, true);

	// --, ȸ��, ������,
	arr[0] = 18;
	//arr[1] = 56;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		MALE_TURN |
		MALE_TURN_RIGHT,
		arr, 1, 0.8f, false);

	// --, ȸ��, ����
	arr[0] = 19;
	//arr[1] = 55;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		MALE_TURN |
		MALE_TURN_LEFT,
		arr, 1, 0.8f, false);

	// --, ����, �ڷ�
	arr[0] = 31;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		MALE_LYING |
		MALE_LYING_BACKWARD,
		arr, 1, 0.8f, false);

	// --, ����, ��������
	arr[0] = 30;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		MALE_LYING |
		MALE_LYING_LEFTWARD,
		arr, 1, 0.8f, false);

	// --, ����, ������
	arr[0] = 37;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		MALE_LYING |
		MALE_LYING_FRONTWARD,
		arr, 1, 0.8f, false);

	// --, �ȱ�, �Ϲ�
	arr[0] = 35;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		MALE_WALK |
		MALE_WALK_NORMAL,
		arr, 1, 0.6f, true);

	// --, �ȱ�, �Ӹ�����
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

	// --, �޸���, NONE
	arr[0] = 39;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		MALE_RUN |
		MALE_RUN_NONE,
		arr, 1, 1.2f, true);

	// --, ������, �ڿ���
	arr[0] = 42;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		MALE_SHOVED |
		MALE_SHOVED_BACKWARD,
		arr, 1, 0.8f, false);

	// --, ������, �տ���
	arr[0] = 44;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		MALE_SHOVED |
		MALE_SHOVED_FRONTWARD,
		arr, 1, 0.8f, false);

	// --, ������, �޸��� ���� �ڿ���
	arr[0] = 45;
	this->CreateMotion(
		ATYPE_ZOMBIE_MALE |
		MALE_SHOVED |
		MALE_SHOVED_BACK_RUN,
		arr, 1, 0.8f, false);

	// --, ������, �޸��� ���� �տ���
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
	// --, ������, ���
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

	// --, ������, ���1
	arr[0] = 48;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_IDLE |
		FEMALE_IDLE_NEUTRAL1,
		arr, 1, 0.6f, true);

	// --, ������, ���2
	arr[0] = 47;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_IDLE |
		FEMALE_IDLE_NEUTRAL2,
		arr, 1, 0.6f, true);

	// --, ������, ���3
	arr[0] = 49;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_IDLE |
		FEMALE_IDLE_NEUTRAL3,
		arr, 1, 0.6f, true);

	// DEAD

	// ����, �ǰ�, ����/��
	arr[0] = 9;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		AWEAPON_PUMPSHOTGUN |
		FEMALE_DEAD |
		FEMALE_DEAD_LEFT_FRONT,
		arr, 1, 0.8f, false);

	// ����, �ǰ�, ������/��
	arr[0] = 8;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		AWEAPON_PUMPSHOTGUN |
		FEMALE_DEAD |
		FEMALE_DEAD_RIGHT_FRONT,
		arr, 1, 0.8f, false);

	// ����, �ǰ�, �߰�/��
	arr[0] = 7;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		AWEAPON_PUMPSHOTGUN |
		FEMALE_DEAD |
		FEMALE_DEAD_MIDDLE_FRONT,
		arr, 1, 1.0f, false);

	// ����, �ǰ�, �Ӹ�/��
	arr[0] = 6;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		AWEAPON_PUMPSHOTGUN |
		FEMALE_DEAD |
		FEMALE_DEAD_HEAD_FRONT,
		arr, 1, 1.0f, false);

	// ����, �ǰ�, ����/��
	arr[0] = 8;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		AWEAPON_PUMPSHOTGUN |
		FEMALE_DEAD |
		FEMALE_DEAD_LEFT_BACK,
		arr, 1, 0.8f, false);

	// ����, �ǰ�, ������/��
	arr[0] = 9;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		AWEAPON_PUMPSHOTGUN |
		FEMALE_DEAD |
		FEMALE_DEAD_RIGHT_BACK,
		arr, 1, 1.0f, false);

	// ����, �ǰ�, �߰�/ ��
	arr[0] = 7;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		AWEAPON_PUMPSHOTGUN |
		FEMALE_DEAD |
		FEMALE_DEAD_MIDDLE_BACK,
		arr, 1, 1.0f, false);

	// ����, �ǰ�, �Ӹ�/��
	arr[0] = 25;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		AWEAPON_PUMPSHOTGUN |
		FEMALE_DEAD |
		FEMALE_DEAD_HEAD_BACK,
		arr, 1, 1.0f, false);

	// ������, �ǰ�, ����/��
	arr[0] = 5;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		AWEAPON_RIFLE |
		FEMALE_DEAD |
		FEMALE_DEAD_LEFT_FRONT,
		arr, 1, 1.0f, false);

	// ������, �ǰ�, ������/��
	arr[0] = 5;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		AWEAPON_RIFLE |
		FEMALE_DEAD |
		FEMALE_DEAD_RIGHT_FRONT,
		arr, 1, 1.0f, false);

	// ������, �ǰ�, �߰�/��
	arr[0] = 2;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		AWEAPON_RIFLE |
		FEMALE_DEAD |
		FEMALE_DEAD_MIDDLE_FRONT,
		arr, 1, 1.0f, false);

	// ������, �ǰ�, �Ӹ�/��
	arr[0] = 3;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		AWEAPON_RIFLE |
		FEMALE_DEAD |
		FEMALE_DEAD_HEAD_FRONT,
		arr, 1, 1.2f, false);

	// ������, �ǰ�, ����/��
	arr[0] = 5;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		AWEAPON_RIFLE |
		FEMALE_DEAD |
		FEMALE_DEAD_LEFT_BACK,
		arr, 1, 1.0f, false);

	// ������, �ǰ�, ������/��
	arr[0] = 5;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		AWEAPON_RIFLE |
		FEMALE_DEAD |
		FEMALE_DEAD_RIGHT_BACK,
		arr, 1, 1.0f, false);

	// ������, �ǰ�, �߰�/ ��
	arr[0] = 2;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		AWEAPON_RIFLE |
		FEMALE_DEAD |
		FEMALE_DEAD_MIDDLE_BACK,
		arr, 1, 1.0f, false);

	// ������, �ǰ�, �Ӹ�/��
	arr[0] = 25;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		AWEAPON_RIFLE |
		FEMALE_DEAD |
		FEMALE_DEAD_HEAD_BACK,
		arr, 1, 1.0f, false);


	// RUNNING_DEAD

	// --, �޸��� �� �ǰ�, �Ӹ�
	arr[0] = 19;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_RUNNING_DEAD |
		FEMALE_RD_HEAD,
		arr, 1, 1.0f, false);

	// --, �޸��� �� �ǰ�, �߰�
	arr[0] = 17;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_RUNNING_DEAD |
		FEMALE_RD_MIDDLE,
		arr, 1, 1.0f, false);

	// --, �޸��� �� �ǰ�, �ٸ�����
	arr[0] = 21;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_RUNNING_DEAD |
		FEMALE_RD_ORDER,
		arr, 1, 1.0f, false);

	// FALL
	// -- , �������� ���, NONE
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
	// --, ȸ��, ������
	arr[0] = 44;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_TURN |
		FEMALE_TURN_RIGHT,
		arr, 1, 0.8f, true);

	// -- ,ȸ��, ����
	arr[0] = 43;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_TURN |
		FEMALE_TURN_LEFT,
		arr, 1, 0.8f, false);

	// LYING
	// --, ���� ����, �ڷ�
	arr[0] = 34;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_LYING |
		FEMALE_LYING_BACKWARD,
		arr, 1, 0.8f, false);

	// --, ���� ����, ����
	arr[0] = 33;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_LYING |
		FEMALE_LYING_LEFTWARD,
		arr, 1, 0.8f, false);

	// --, ���� ����, ������
	arr[0] = 51;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_LYING |
		FEMALE_LYING_FRONTWARD,
		arr, 1, 0.8f, false);

	// --, ���� ����, ����������
	arr[0] = 37;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_LYING |
		FEMALE_LYING_RIGHTWARD,
		arr, 1, 0.8f, false);

	// WALK
	// --, �ȴ� ����, NONE
	arr[0] = 22;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_WALK |
		FEMALE_WALK_NORMAL,
		arr, 1, 0.8f, true);

	// ATTACK
	// --, ����, NONE
	arr[0] = 41;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_ATTACK |
		FEMALE_ATTACK_NONE,
		arr, 1, 1.0f, false);

	// RUN
	// --, �޸���, NONE
	arr[0] = 50;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_RUN |
		FEMALE_RUN_NONE,
		arr, 1, 1.5f, true);

	// SHOVED
	// --, �и� ����, �ڿ���
	arr[0] = 7;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_SHOVED |
		FEMALE_SHOVED_BACKWARD,
		arr, 1, 1.0f, false);

	// --, �и� ����, �տ���
	arr[0] = 12;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_SHOVED |
		FEMALE_SHOVED_FRONTWARD,
		arr, 1, 0.8f, false);

	// --, �и� ����, �޸��� ���� �ڿ���
	arr[0] = 21;
	this->CreateMotion(
		ATYPE_ZOMBIE_FEMALE |
		FEMALE_SHOVED |
		FEMALE_SHOVED_BACK_RUN,
		arr, 1, 1.0f, false);

	// --, �и� ����, �޸��� ���� �տ���
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
	// ����Ÿ���, ����
	arr[0] = 0;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_FLINCH |
		HULK_FLINCH_CHEST,
		arr, 1, 1.0f, false);

	// ����Ÿ���, ����
	arr[0] = 1;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_FLINCH |
		HULK_FLINCH_LEFT,
		arr, 1, 1.0f, false);

	// ����Ÿ���, ������
	arr[0] = 2;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_FLINCH |
		HULK_FLINCH_RIGHT,
		arr, 1, 1.0f, false);

	// ����Ÿ���, ����
	arr[0] = 3;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_FLINCH |
		HULK_FLINCH_STOMACH,
		arr, 1, 1.0f, false);

	// DEAD
	// ����, �븻
	arr[0] = 4;
	arr[1] = 31;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_DEAD |
		HULK_DEAD_NORMAL,
		arr, 2, 1.0f, false);

	// ����, ���
	arr[0] = 5;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_DEAD |
		HULK_DEAD_IDLE,
		arr, 1, 1.0f, false);

	// ����, �޸��� ��
	arr[0] = 6;
	arr[1] = 31;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_DEAD |
		HULK_DEAD_RUNNING,
		arr, 2, 1.0f, false);

	// IDLE
	// ���, �븻
	arr[0] = 18;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_IDLE |
		HULK_IDLE_NORMAL,
		arr, 1, 1.0f, true);

	// ���, �Ҹ�������
	arr[0] = 19;
	arr[1] = 20;
	arr[2] = 27;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_IDLE |
		HULK_IDLE_YELL,
		arr, 3, 0.8f, true);


	// ���, ���� ����ġ��
	arr[0] = 23;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_IDLE |
		HULK_IDLE_SMASH,
		arr, 1, 1.2f, true);


	// JUMP
	//����, �븻
	arr[0] = 22;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_JUMP |
		HULK_JUMP_NONE,
		arr, 1, 1.0f, false);

	// RUN
	// �޸���, �븻
	arr[0] = 36;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_RUN |
		HULK_RUN_NORMAL,
		arr, 1, 1.0f, true);

	// �޸���, ȭ��
	arr[0] = 30;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_RUN |
		HULK_RUN_RAGE,
		arr, 1, 1.0f, true);

	// WALK
	// �ȱ�, NONE
	arr[0] = 17;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_WALK |
		HULK_WALK_NONE,
		arr, 1, 1.0f, true);

	// TURN
	// ȸ��, ����
	arr[0] = 49;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_TURN |
		HULK_TURN_LEFT,
		arr, 1, 0.6f, true);

	// ȸ��, ������
	arr[0] = 50;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_TURN |
		HULK_TURN_RIGHT,
		arr, 1, 0.6f, true);

	// ATTACK
	// ����, �޸���
	arr[0] = 11;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_ATTACK |
		HULK_ATTACK_RUN,
		arr, 1, 1.0f, false);

	// ����, ������
	arr[0] = 38;
	arr[1] = 39;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_ATTACK |
		HULK_ATTACK_FLY,
		arr, 2, 1.0f, false);

	// ����, �⺻1
	arr[0] = 8;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_ATTACK |
		HULK_ATTACK_NORMAL1,
		arr, 1, 1.0f, false);

	// ����, �⺻2
	arr[0] = 48;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_ATTACK |
		HULK_ATTACK_NORMAL2,
		arr, 1, 1.0f, false);

	// VICTORY
	// �¸�, �¸�1
	arr[0] = 44;
	this->CreateMotion(
		ATYPE_ZOMBIE_HULK |
		HULK_VICTORY |
		HULK_VICTORY_1,
		arr, 1, 0.7f, true);

	// �¸�, �¸�2
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
	// ������, NONE
	arr[0] = 0;
	this->CreateMotion(
		ATYPE_ZOMBIE_SMOKER |
		SMOKER_IDLE |
		SMOKER_IDLE_NONE,
		arr, 1, 0.8f, true);

	// ���ٴ�, ����
	arr[0] = 1;
	this->CreateMotion(
		ATYPE_ZOMBIE_SMOKER |
		SMOKER_COUGH |
		SMOKER_COUGH_ATTACK,
		arr, 1, 1.0f, true);

	// ����, �⺻
	arr[0] = 4;
	arr[1] = 5;
	this->CreateMotion(
		ATYPE_ZOMBIE_SMOKER |
		SMOKER_ATTACK |
		SMOKER_ATTACK_NORMAL,
		arr, 2, 1.0f, false);

	// ��ó��, �ڿ���
	arr[0] = 7;
	this->CreateMotion(
		ATYPE_ZOMBIE_SMOKER |
		SMOKER_SHOVED |
		SMOKER_SHOVED_BACK,
		arr, 1, 1.0f, false);

	// ������, �տ���
	arr[0] = 8;
	this->CreateMotion(
		ATYPE_ZOMBIE_SMOKER |
		SMOKER_SHOVED |
		SMOKER_SHOVED_FOR,
		arr, 1, 1.0f, false);

	// ��ó��, ���ʿ���
	arr[0] = 9;
	this->CreateMotion(
		ATYPE_ZOMBIE_SMOKER |
		SMOKER_SHOVED |
		SMOKER_SHOVED_LEFT,
		arr, 1, 1.0f, false);

	// ��ó��, �����ʿ���
	arr[0] = 10;
	this->CreateMotion(
		ATYPE_ZOMBIE_SMOKER |
		SMOKER_SHOVED |
		SMOKER_SHOVED_RIGHT,
		arr, 1, 1.0f, false);

	// �����ϴ�, �ڿ���
	arr[0] = 11;
	this->CreateMotion(
		ATYPE_ZOMBIE_SMOKER |
		SMOKER_FLINCH |
		SMOKER_FLINCH_BACK,
		arr, 1, 0.8f, false);

	// �����ϴ�, ����
	arr[0] = 12;
	this->CreateMotion(
		ATYPE_ZOMBIE_SMOKER |
		SMOKER_FLINCH |
		SMOKER_FLINCH_CHEST,
		arr, 1, 0.8f, false);

	// �����ϴ�, �Ӹ�
	arr[0] = 13;
	this->CreateMotion(
		ATYPE_ZOMBIE_SMOKER |
		SMOKER_FLINCH |
		SMOKER_FLINCH_HEAD,
		arr, 1, 0.8f, false);

	// �����ϴ�, ����
	arr[0] = 14;
	this->CreateMotion(
		ATYPE_ZOMBIE_SMOKER |
		SMOKER_FLINCH |
		SMOKER_FLINCH_LEFT,
		arr, 1, 0.8f, false);

	// �����ϴ�, ���ʴٸ�
	arr[0] = 15;
	this->CreateMotion(
		ATYPE_ZOMBIE_SMOKER |
		SMOKER_FLINCH |
		SMOKER_FLINCH_LEFTLEG,
		arr, 1, 0.8f, false);

	// �����ϴ�, ������
	arr[0] = 16;
	this->CreateMotion(
		ATYPE_ZOMBIE_SMOKER |
		SMOKER_FLINCH |
		SMOKER_FLINCH_RIGHT,
		arr, 1, 0.8f, false);

	// �����ϴ�, �����ʴٸ�
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
	// ������, �õ�on
	arr[0] = 0;
	this->CreateMotion(
		ATYPE_AIRPLANE |
		AIRPLANE_IDLE |
		AIRPLANE_IDLE_ON,
		arr, 1, 1.0f, true);

	// ������, �õ�off
	arr[0] = 1;
	this->CreateMotion(
		ATYPE_AIRPLANE |
		AIRPLANE_IDLE |
		AIRPLANE_IDLE_OFF,
		arr, 1, 1.0f, true);

	// ��, ������ �ִ� ����
	arr[0] = 3;
	arr[1] = 2;
	this->CreateMotion(
		ATYPE_AIRPLANE |
		AIRPLANE_OPEN |
		AIRPLANE_OPEN_NONE,
		arr, 2, 2.0f, false);

	// ���
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
		//������ �� ã���� ���
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
