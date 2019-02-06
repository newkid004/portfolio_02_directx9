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

	bool wheelUp(void);
	bool wheelDown(void);
	LONG wheel(void);

public :
	constexpr pick::ray & getPickRay(void) { return _pickRay; }
	constexpr POINT & getMousePos(void) { return _mousePos; }
	bool getClickIgnore(void) { return _clickIgnore; }

	void setMousePos(POINT input);
	void setClickIgnore(bool isIgnore = true) { _clickIgnore = isIgnore; }

private :
	void updateMousePos(void);

public :
	DECLARE_SINGLETON(inputManager);

private :
	inputManager(void);
	virtual ~inputManager(void);
};

