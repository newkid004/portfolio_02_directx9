#include "inputManager.h"
#include "windowManager.h"

inputManager::inputManager(void)
{
	ZeroMemory(_keyStates, sizeof(_keyStates));
	ZeroMemory(_keyPrevStates, sizeof(_keyPrevStates));
	ZeroMemory(&_mouseState, sizeof(_mouseState));
	ZeroMemory(&_mousePrevState, sizeof(_mousePrevState));
}

inputManager::~inputManager(void)
{
	_keyDevice->Unacquire();

	SAFE_RELEASE(_keyDevice);
	SAFE_RELEASE(_mouseDevice);
	SAFE_RELEASE(_directInput);
}

void inputManager::init(void)
{
	_directInput = createDirectInput();
	_keyDevice = createKeyDevice();
	_mouseDevice = createMouseDevice();
}

void inputManager::update(void)
{
	CopyMemory(&_mousePrevState, &_mouseState, sizeof(_mouseState));
	CopyMemory(_keyPrevStates, _keyStates, sizeof(_keyStates));

	_mouseDevice->GetDeviceState(sizeof(_mouseState), &_mouseState);
	_keyDevice->GetDeviceState(sizeof(_keyStates), _keyStates);

	if (mouseDown(EMouseInput::LEFT) ||
		mouseDown(EMouseInput::RIGHT) || 
		mouseDown(EMouseInput::MIDDLE))
	{
		pick::createPickRay(&_pickRay);
	}

	updateMousePos();
	_clickIgnore = false;
}

LPDIRECTINPUT8 inputManager::createDirectInput(void)
{
	LPDIRECTINPUT8 directInput = NULL;
	DirectInput8Create(GET_WINDOW_MANAGER()->getHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, NULL);

	return directInput;
}

LPDIRECTINPUTDEVICE8 inputManager::createKeyDevice(void)
{
	LPDIRECTINPUTDEVICE8 directDevice = NULL;
	_directInput->CreateDevice(GUID_SysKeyboard, &directDevice, NULL);

	// ����̽� ��ġ�� ó���ϱ� ���� ������ ������ ����
	directDevice->SetDataFormat(&c_dfDIKeyboard);

	// ���� ���� ���� : Ÿ ���ø����̼ǰ� ��ȣ�ۿ�
	directDevice->SetCooperativeLevel(GET_WINDOW_MANAGER()->getHWnd(), 
		DISCL_BACKGROUND |		// ��Ȱ��ȭ �ÿ��� ����
		DISCL_NONEXCLUSIVE);	// �������� ����

	// ����̽� ���� ȹ��
	directDevice->Acquire();

	return directDevice;
}

LPDIRECTINPUTDEVICE8 inputManager::createMouseDevice(void)
{
	LPDIRECTINPUTDEVICE8 directDevice = NULL;

	_directInput->CreateDevice(GUID_SysMouse, &directDevice, NULL);

	directDevice->SetDataFormat(&c_dfDIMouse);
	directDevice->SetCooperativeLevel(GET_WINDOW_HANDLE(), DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
	directDevice->Acquire();

	return directDevice;
}

bool inputManager::keyDown(int keyCode)
{
	return _keyStates[keyCode] & 0x80;
}

bool inputManager::keyPress(int keyCode)
{
	return (_keyStates[keyCode] & 0x80) && !(_keyPrevStates[keyCode] & 0x80);
}

bool inputManager::keyUp(int keyCode)
{
	return !(_keyStates[keyCode] & 0x80) && (_keyPrevStates[keyCode] & 0x80);
}

bool inputManager::mouseDown(EMouseInput input)
{
	return _mouseState.rgbButtons[input] & 0x80;
}

bool inputManager::mousePress(EMouseInput input)
{
	return (_mouseState.rgbButtons[input] & 0x80) &&
		!(_mousePrevState.rgbButtons[input] & 0x80);
}

bool inputManager::mouseUp(EMouseInput input)
{
	return !(_mouseState.rgbButtons[input] & 0x80) &&
		(_mousePrevState.rgbButtons[input] & 0x80);
}

bool inputManager::wheelUp(void)
{
	return 0 < _mouseState.lZ;
}

bool inputManager::wheelDown(void)
{
	return _mouseState.lZ < 0;
}

LONG inputManager::wheel(void)
{
	return _mouseState.lZ;
}

void inputManager::setMousePos(POINT input)
{
	ClientToScreen(GET_WINDOW_MANAGER()->getHWnd(), &input);
	SetCursorPos(input.x, input.y);
}

void inputManager::updateMousePos(void)
{
	GetCursorPos(&_mousePos);
	ScreenToClient(GET_WINDOW_MANAGER()->getHWnd(), &_mousePos);
}
