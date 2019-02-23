#pragma once
#include "windowManager.h"
#include "deviceManager.h"
#include "timeManager.h"
#include "inputManager.h"
#include "resourceManager.h"
#include "soundManager.h"

#include "sceneManager.h"
#include "uiManager.h"
#include "eventManager.h"
#include "textManager.h"
#include "bulletManager.h"
#include "weaponManager.h"

#include "gameSystem.h"

// ----- def ----- //
#define MN_WIN		GET_WINDOW_MANAGER()
#define MN_DEV		GET_DEVICE_MANAGER()->getDevice()
#define MN_KEY		GET_INPUT_MANAGER()
#define MN_TIME		GET_TIME_MANAGER()
#define MN_SRC		GET_RESOURCE_MANAGER()
#define MN_BULLET	GET_BULLET_MANAGER()