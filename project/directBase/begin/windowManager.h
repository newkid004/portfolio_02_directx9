#pragma once
#include "kGlobalDefine.h"
#include "windowMessageHandler.h"

class windowManager : public windowMessageHandler
{
private :
	SIZE _windowSize;

	HWND _hWnd = NULL;
	HINSTANCE _hInstance = NULL;

	TCHAR* _className = NULL;
	windowMessageHandler* _winMessageHandler = NULL;

public :	// ----- �̱��� ----- //
	DECLARE_SINGLETON(windowManager);

public :	// ----- FW ----- //
	void init(
		HINSTANCE hInstance,
		const SIZE & windowSize,
		windowMessageHandler* winMessageHandler);

private :
	HWND createWindow(HINSTANCE hInstance, const SIZE & windowSize);

public :
	float getAspect(void) { return _windowSize.cx / (float)_windowSize.cy; }

public :	// ---- ����, ������ ----- //
	HWND getHWnd(void) { return _hWnd; }
	HINSTANCE getHInstance(void) { return _hInstance; }
	SIZE getWindowSize(void) { return _windowSize; }

public :	// ----- �������̽� ----- //
	virtual LRESULT handleWindowMessage(
		HWND hWnd,
		UINT message,
		WPARAM wParam,
		LPARAM lParam) override;

private :
	windowManager() :
		_className(TEXT(WINNAME)) 
	{
		ZeroMemory(&_windowSize, sizeof(_windowSize)); 
	};
	virtual ~windowManager() 
	{
		UnregisterClass(_className, _hInstance); 
	};
};

