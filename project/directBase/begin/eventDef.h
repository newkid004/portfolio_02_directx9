#pragma once

// ----- type : 0x000f ----- //
// �̺�Ʈ�� ���޵Ǵ� ������ ����
// �� sour, destParam�� 0x000f��°(0x000f 000f)�� ���·� ����
// ��) enemy -> player���� ����(param = 0x0009 0008)
enum e_EVENT_TYPE
{
	ET_EVENT			= 0x1,
	ET_OBJECT			= 0x2,
	ET_TERRAIN			= 0x3,
	ET_EFFECT			= 0x4,
	ET_ITEM				= 0x5,
	ET_WINDOW			= 0x6,
	ET_SYSTEM			= 0x7,
	ET_CHARACTER		= 0x8,
	ET_ENEMY			= 0x9,

	ET_NONE = 0
};

// ----- kind : 0x00f0 ----- //
// �̺�Ʈ�� ���޵Ǵ� ������ ��������
// �� sour, destParam�� 0x00f0��°(0x00f0 00f0)�� ���·� ����
// �������°� ���� ������ �����(0)

// kind : object
enum e_EVENT_KIND_OBJECT
{
	EK_OBJECT_BASE		= 0x10,
	EK_OBJECT_BULLET	= 0x20,
	EK_OBJECT_VEHICLE	= 0x30,

	EK_OBJECT_NONE = 0
};

// kind : terrain
enum e_EVENT_KIND_TERRAIN
{
	EK_TERRAIN_BASE		= 0x10,
	EK_TERRAIN_WALL		= 0x20,
	EK_TERRAIN_STAIRS	= 0x30,

	EK_TERRAIN_NONE	= 0
};

// kind : effect
enum e_EVENT_KIND_EFFECT
{
	EK_EFFECT_BLOOD		= 0x10,
	EK_EFFECT_SHADE		= 0x20,
	EK_EFFECT_LIGHT		= 0x30,
	EK_EFFECT_SHOTFIRE	= 0x40,

	EK_EFFECT_NONE = 0
};

// kind : item
enum e_EVENT_KIND_ITEM
{
	EK_ITEM_RIFLE		= 0x10,
	EK_ITEM_SHOTGUN		= 0x20,
	EK_ITEM_HEALKIT		= 0x30,
	EK_ITEM_BULLET		= 0x40,
	EK_ITEM_ETC			= 0x50,

	EK_ITEM_NONE = 0
};

// kind : window
enum e_EVENT_KIND_WINDOW
{
	EK_WINDOW_BASE		= 0x10,
	EK_WINDOW_MAPTOOL	= 0x20,
	EK_WINDOW_OPTION	= 0x30,
	EK_WINDOW_EXIT		= 0x40,

	EK_WINDOW_NONE = 0
};

// kind : system
enum e_EVENT_KIND_SYSTEM
{
	EK_SYSTEM_MAPSAVE	= 0x10,
	EK_SYSTEM_MAPLOAD	= 0x20,
	EK_SYSTEM_SOUND		= 0x30,

	EK_SYSTEM_NONE = 0
};

// kind : character
enum e_EVENT_KIND_CHARACTER
{
	EK_CHARACTER_PLAYER		= 0x10,
	EK_CHARACTER_NAMVET		= 0x20,
	EK_CHARACTER_TEENANGST	= 0x30,
	EK_CHARACTER_MANAGER	= 0x40,

	EK_PARTNER_NONE	= 0
};

// kind : enemy
enum e_EVENT_KIND_ENEMY
{
	EK_ENEMY_BASE		= 0x10,
	EK_ENEMY_TANKER		= 0x20,
	EK_ENEMY_SMOKER		= 0x30,

	EK_ENEMY_NONE = 0
};

// ----- act : 0x0f00 ----- //
// ���� �� �̺�Ʈ�� ���� ����
// �� sour, destParam�� 0x0f00��°(0x0f00 0f00)�� ���·� ����
// �� enum�� ���ϴ� ���п�Ұ� ���������� ���Ƿ� �߰�

// act : character
enum e_EVENT_ACT_CHARACTER
{
	EA_CHARACTER_WALK	 = 0x100,
	EA_CHARACTER_RUN	 = 0x200,
	EA_CHARACTER_JUMP	 = 0x300,
	EA_CHARACTER_SHOOT   = 0x400,
	EA_CHARACTER_ATTACK  = 0x500,
	EA_CHARACTER_HEAL	 = 0x600,
	EA_CHARACTER_ONHIT	 = 0x700,
	EA_CHARACTER_STUN	 = 0x800,
	EA_CHARACTER_DEATH	 = 0x900,

	EA_CHARACTER_NONE = 0
};

// act : enemy
enum e_EVENT_ACT_ENEMY
{
	EA_ENEMY_WALK		= 0x100,
	EA_ENEMY_RUN		= 0x200,
	EA_ENEMY_ATTACK		= 0x300,
	EA_ENEMY_FALL		= 0x400,
	EA_ENEMY_ONHIT		= 0x500,
	EA_ENEMY_DEATH		= 0x600,

	EA_ENEMY_NONE = 0
};

// act : item
enum e_EVENT_ACT_ITEM
{
	EA_ITEM_GET		  = 0x100,		// ȹ��
	EA_ITEM_USE		  = 0x200,		// ���
	EA_ITEM_EQUIPMENT = 0x300,		// ��� ����

	EA_ITEM_NONE = 0
};

// ----- call : 0xf000 ---- //
// �� ������ ���¿� ���� ĳ�� ȣ������(index)
// �� sour, destParam�� 0xf000��°(0xf000 f000)�� ���·� ����
// �������°� ���� ������ �����(0)

// call : player - status - change
enum e_EVENT_CALL_PLAYER_STATE_CHANGE
{
	EC_PLAYER_STATE_CHANGE_INCREASE = 0x1000,
	EC_PLAYER_STATE_CHANGE_DECREASE = 0x2000,

	EC_PLAYER_STATE_CHANGE_NONE = 0
};