#pragma once
#include "kGlobalDefine.h"
#include "iUpdateble.h"

#include "pickRay.h"

class inputManager : public iUpdateble
{
private:
	// device
	LPDIRECTINPUT8 _directInput = NULL;
	LPDIRECTINPUTDEVICE8 _keyDevice = NULL;
	LPDIRECTINPUTDEVICE8 _mouseDevice = NULL;

	// key
	BYTE _keyStates[UCHAR_MAX + 1];
	BYTE _keyPrevStates[UCHAR_MAX + 1];

	// mouse
	DIMOUSESTATE	_mouseState;
	DIMOUSESTATE	_mousePrevState;
	POINT			_mousePos;

	// double click
	float			_mouseClickTime = 0.0f;
	float			_mouseClickTimePrev = 0.0f;
	float			_mouseDbClickTime = 0.0f;
	float			_mouseDbClickTurm = 0.5f;

	bool			_clickIgnore = false;

	// pick
	pick::ray		_pickRay;

private:
	LPDIRECTINPUT8 createDirectInput(void);
	LPDIRECTINPUTDEVICE8 createKeyDevice(void);
	LPDIRECTINPUTDEVICE8 createMouseDevice(void);

public :
	void init(void);
	void update(void);

public :
	bool keyDown(int keyCode);
	bool keyPress(int keyCode);
	bool keyUp(int keyCode);

	bool mouseDown(EMouseInput input = EMouseInput::LEFT);
	bool mousePress(EMouseInput input = EMouseInput::LEFT);
	bool mouseUp(EMouseInput input = EMouseInput::LEFT);

	// 좌클릭만 확인
	bool mousePressDb(void);

	bool wheelUp(void);
	bool wheelDown(void);
	LONG wheel(void);

public :
	void resetMousePressDb(void);

public :
	constexpr pick::ray & getPickRay(void) { return _pickRay; }
	constexpr POINT & getMousePos(void) { return _mousePos; }
	float getDbClickTurm(void) { return _mouseDbClickTurm; }
	bool getClickIgnore(void) { return _clickIgnore; }

	void setMousePos(POINT input);
	void setDbClickTurm(float input) { _mouseDbClickTurm = input; }
	void setClickIgnore(bool isIgnore = true) { _clickIgnore = isIgnore; }

private :
	void updateMousePos(void);
	void updateMouseDbClick(void);

public :
	DECLARE_SINGLETON(inputManager);

private :
	inputManager(void);
	virtual ~inputManager(void);
};

