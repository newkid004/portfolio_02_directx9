#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define DIRECTINPUT_VERSION 0x0800

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput8.lib")	// direct input
#pragma comment(lib, "dsound.lib")	// direct sound
#pragma comment(lib, "dxguid.lib")	// direct gui
#pragma comment(lib, "winmm.lib")	// window multi-media

// 공용 헤더파일
#include <iostream>
#include <cassert>
#include <Windows.h>
#include <tchar.h>
#include <chrono>
#include <memory>
#include <random>

// 기타 헤더파일
#include <algorithm>
#include <numeric>
#include <functional>
#include <mmsystem.h>	// 멀티미디어

// STL
#include <string>
#include <vector>
#include <unordered_map>

// d3d 헤더파일
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <dsound.h>

// 유틸리티 파일
typedef double NUM_REAL;
#include "c3DMatrix.h"
#include "c3DVector.h"

// ----- 매크로 ------ //
// 싱글톤
#define DECLARE_SINGLETON(CLASS_NAME)	\
public:									\
static CLASS_NAME* getInstance(void) {	\
static CLASS_NAME _instance;			\
return &_instance;						\
}

#define GET_WINDOW_MANAGER()			(windowManager::getInstance())
#define GET_DEVICE_MANAGER()			(deviceManager::getInstance())
#define GET_TIME_MANAGER()				(timeManager::getInstance())
#define GET_INPUT_MANAGER()				(inputManager::getInstance())
#define GET_RESOURCE_MANAGER()			(resourceManager::getInstance())
#define GET_SOUND_MANAGER()				(soundManager::getInstance())

#define GET_SCENE_MANAGER()				(sceneManager::getInstance())

// D3D
#define WORLD_DIRECTION_RIGHT			(D3DXVECTOR3(1.0f, 0.0f, 0.0f))
#define WORLD_DIRECTION_UP				(D3DXVECTOR3(0.0f, 1.0f, 0.0f))
#define WORLD_DIRECTION_FORWARD			(D3DXVECTOR3(0.0f, 0.0f, 1.0f))

// 윈도우
#define GET_WINDOW_APPLICATION()		(iWindowApplication::getInstance())
#define GET_DIRECT3D_APPLICATION()		((direct3dApplication*)GET_WINDOW_APPLICATION())

#define GET_WINDOW_SIZE()				(GET_WINDOW_MANAGER()->getWindowSize())
#define GET_WINDOW_HANDLE()				(GET_WINDOW_MANAGER()->getHWnd())
#define GET_INSTANCE_HANDLE()			(GET_WINDOW_MANAGER()->getHInstance())

#define GET_CAMERA()					(GET_SCENE_MANAGER()->getCurrentScene()->getCamera())
#define GET_LIGHT()						(GET_SCENE_MANAGER()->getCurrentScene()->getLight())
#define GET_LABEL()						(GET_SCENE_MANAGER()->getCurrentScene()->getLabel())
#define GET_SPRITE()					(GET_SCENE_MANAGER()->getCurrentScene()->getSprite())

// Deleter
#define SAFE_FREE(TARGET)				if((TARGET) != nullptr) { free(TARGET); (TARGET) = NULL; }
#define SAFE_DELETE(TARGET)				if((TARGET) != nullptr) { delete (TARGET); (TARGET) = NULL; }
#define SAFE_DELETE_ARRAY(TARGET)		if((TARGET) != nullptr) { delete[] (TARGET); (TARGET) = NULL; }
#define SAFE_RELEASE(TARGET)			if((TARGET) != nullptr) { (TARGET)->Release(); (TARGET) = NULL; }

// ----- color ----- //
#define COLOR_BLACK(alpha)		D3DCOLOR_ARGB(alpha, 0, 0, 0)
#define COLOR_GRAY(alpha)		D3DCOLOR_ARGB(alpha, 128, 128, 128)
#define COLOR_WHITE(alpha)		D3DCOLOR_ARGB(alpha, 255, 255, 255)
#define COLOR_RED(alpha)		D3DCOLOR_ARGB(alpha, 255, 0, 0)
#define COLOR_GREEN(alpha)		D3DCOLOR_ARGB(alpha, 0, 255, 0)
#define COLOR_BLUE(alpha)		D3DCOLOR_ARGB(alpha, 0, 0, 255)
#define COLOR_MAGENTA(alpha)	D3DCOLOR_ARGB(alpha, 255, 0, 255)
#define COLOR_YELLOW(alpha)		D3DCOLOR_ARGB(alpha, 255, 255, 0)
#define COLOR_CYAN(alpha)		D3DCOLOR_ARGB(alpha, 0, 255, 255)

// ----- 창 설정 ----- //
#define WINNAME				"winDirect"
#define WINSIZEX			640
#define WINSIZEY			360
#define BACK_COLOR			COLOR_GRAY

// ----- enum ----- //

// 마우스 입력
enum EMouseInput
{
	LEFT,
	RIGHT,
	MIDDLE,
	NONE
};

// 파티클 타입
enum class EParticleType
{
	EXPLOSION,
	EXPLOSION_OUTLINE,
	SINK,
	ORBIT,
	NONE
};

// ----- struct ----- //

// 정적 메쉬
struct meshSet
{
	DWORD numMaterial;
	LPD3DXMESH mesh;

	std::vector<D3DMATERIAL9> vMaterialList;
	std::vector<LPDIRECT3DTEXTURE9> vTextureList;
};

// 광선
struct pRay
{
	D3DXVECTOR3 origin;
	D3DXVECTOR3 direction;
};

// 웨이브 사운드
