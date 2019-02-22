#pragma once

struct EVENT
{
#define DEF_TYPE constexpr static int
#define MAKE_EV(index, identity) DEF_TYPE identity = index << shiftCount

	DEF_TYPE shift_TYPE	= 0;
	DEF_TYPE shift_KIND	= 4;
	DEF_TYPE shift_ACT	= 8;
	DEF_TYPE shift_CALL	= 12;

	DEF_TYPE NONE = 0;

	// ----- type : 0x000f ----- //
	// 이벤트로 전달되는 인자의 형태
	// 각 sour, destParam의 0x000f번째(0x000f 000f)의 형태로 전달
	// 예) enemy -> player에게 전달(param = 0x0009 0008)
	struct TYPE
	{
		DEF_TYPE shiftCount = shift_TYPE;

		MAKE_EV(0x1, EVENT);
		MAKE_EV(0x2, OBJECT);
		MAKE_EV(0x3, TERRAIN);
		MAKE_EV(0x4, EFFECT);
		MAKE_EV(0x5, ITEM);
		MAKE_EV(0x6, WINDOW);
		MAKE_EV(0x7, SYSTEM);
		MAKE_EV(0x8, CHARACTER);
		MAKE_EV(0x9, ENEMY);
		MAKE_EV(0xA, TRIGGER);
		MAKE_EV(0xB, WEAPON);
	};

	// ----- kind : 0x00f0 ----- //
	// 이벤트로 전달되는 인자의 세부형태
	// 각 sour, destParam의 0x00f0번째(0x00f0 00f0)의 형태로 전달
	// 세부형태가 딱히 없으면 비워둠(0)
	struct KIND
	{
		DEF_TYPE shiftCount = shift_KIND;

		struct OBJECT
		{
			MAKE_EV(0x1, BASE);
			MAKE_EV(0x2, BULLET);
			MAKE_EV(0x3, VEHICLE);
		};

		struct TERRAIN
		{
			DEF_TYPE BASE		= 0x1 << shiftCount;
			DEF_TYPE WALL		= 0x2 << shiftCount;
			DEF_TYPE STAIRS		= 0x3 << shiftCount;
		};

		struct EFFECT
		{
			DEF_TYPE BLOOD		= 0x1 << shiftCount;
			DEF_TYPE SHADE		= 0x2 << shiftCount;
			DEF_TYPE LIGHT		= 0x3 << shiftCount;
			DEF_TYPE SHOTFIRE	= 0x4 << shiftCount;
		};

		struct ITEM
		{
			DEF_TYPE RIFLE		= 0x1 << shiftCount;
			DEF_TYPE SHOTGUN	= 0x2 << shiftCount;
			DEF_TYPE HEALKIT	= 0x3 << shiftCount;
			DEF_TYPE BULLET		= 0x4 << shiftCount;
			DEF_TYPE ETC		= 0x5 << shiftCount;
		};

		struct WINDOW
		{
			DEF_TYPE BASE		= 0x1 << shiftCount;
			DEF_TYPE MAPTOOL	= 0x2 << shiftCount;
			DEF_TYPE OPTION		= 0x3 << shiftCount;
			DEF_TYPE EXIT		= 0x4 << shiftCount;
		};

		struct SYSTEM
		{
			DEF_TYPE MAPSAVE	= 0x1 << shiftCount;
			DEF_TYPE MAPLOAD	= 0x2 << shiftCount;
			DEF_TYPE SOUND		= 0x3 << shiftCount;
		};

		struct CHARACTER
		{
			DEF_TYPE PLAYER		= 0x1 << shiftCount;
			DEF_TYPE NAMVET		= 0x2 << shiftCount;
			DEF_TYPE TEENANGST	= 0x3 << shiftCount;
			DEF_TYPE MANAGER	= 0x4 << shiftCount;
		};

		struct ENEMY
		{
			DEF_TYPE BASE		= 0x1 << shiftCount;
			DEF_TYPE TANKER		= 0x2 << shiftCount;
			DEF_TYPE SMOKER		= 0x3 << shiftCount;
		};

		struct TRIGGER
		{
			MAKE_EV(0x1, AIR_PLANE);
			MAKE_EV(0x2, MOVE_FAR);
			MAKE_EV(0x3, ZOMBIE_WAVE);
		};

		struct WEAPON
		{
			MAKE_EV(0x1, SHOTGUN);
			MAKE_EV(0x1, RIFLE);
		};
	};

	// ----- act : 0x0f00 ----- //
	// 인자 간 이벤트의 실행 형태
	// 각 sour, destParam의 0x0f00번째(0x0f00 0f00)의 형태로 전달
	// 각 enum에 원하는 구분요소가 없을때마다 임의로 추가
	struct ACT
	{
		DEF_TYPE shiftCount = shift_ACT;

		struct CHARACTER
		{
			DEF_TYPE WALK		= 0x1 << shiftCount;
			DEF_TYPE RUN		= 0x2 << shiftCount;
			DEF_TYPE JUMP		= 0x3 << shiftCount;
			DEF_TYPE SHOOT		= 0x4 << shiftCount;
			DEF_TYPE ATTACK		= 0x5 << shiftCount;
			DEF_TYPE HEAL		= 0x6 << shiftCount;
			DEF_TYPE ONHIT		= 0x7 << shiftCount;
			DEF_TYPE STUN		= 0x8 << shiftCount;
			DEF_TYPE DEATH		= 0x9 << shiftCount;
		};

		struct ENEMY
		{
			MAKE_EV(0x1, WALK);
			MAKE_EV(0x2, RUN);
			MAKE_EV(0x3, ATTACK);
			MAKE_EV(0x4, FALL);
			MAKE_EV(0x5, ONHIT);
			MAKE_EV(0x6, DEATH);
			MAKE_EV(0x7, RESURRECTION);
			MAKE_EV(0x8, ADDED);
		};

		struct ITEM
		{
			DEF_TYPE GET		= 0x1 << shiftCount;
			DEF_TYPE USE		= 0x2 << shiftCount;
			DEF_TYPE EQUIPMENT	= 0x3 << shiftCount;
		};

		struct TRIGGER
		{
			MAKE_EV(0x1, ACTIVE);
			MAKE_EV(0x2, CONTINUE);
			MAKE_EV(0x3, COMPLETE);
		};

		struct WEAPON
		{
			MAKE_EV(0x1, SHOOT);
		};
	};

	// ----- call : 0xf000 ---- //
	// 위 사항의 형태에 따른 캐쳐 호출형태(index)
	// 각 sour, destParam의 0xf000번째(0xf000 f000)의 형태로 전달
	// 세부형태가 딱히 없으면 비워둠(0)
	struct CALL
	{
		DEF_TYPE shiftCount = shift_CALL;

		struct PLAYER_STATE_CHANGE
		{
			DEF_TYPE INCREASE	= 0x1 << shiftCount;
			DEF_TYPE DECREASE	= 0x2 << shiftCount;
		};
	};
};

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
	EA_ITEM_GET		  = 0x100,		// 획득
	EA_ITEM_USE		  = 0x200,		// 사용
	EA_ITEM_EQUIPMENT = 0x300,		// 장비 착용

	EA_ITEM_NONE = 0
};


// call : player - status - change
enum e_EVENT_CALL_PLAYER_STATE_CHANGE
{
	EC_PLAYER_STATE_CHANGE_INCREASE = 0x1000,
	EC_PLAYER_STATE_CHANGE_DECREASE = 0x2000,

	EC_PLAYER_STATE_CHANGE_NONE = 0
};