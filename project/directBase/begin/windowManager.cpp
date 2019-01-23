#include "windowManager.h"
#include "iWindowApplication.h"

static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static windowMessageHandler* msgHandler = NULL;

	switch (message)
	{
	case WM_CREATE: {
		CREATESTRUCT* cStruct = (CREATESTRUCT*)lParam;
		
		// CreateWindow시, lpParam에 전달한 내용을 가져옴
		msgHandler = (windowMessageHandler*)cStruct->lpCreateParams;

	} break;

	default:
		break;
	}

	if (msgHandler != NULL)
		return msgHandler->handleWindowMessage(hWnd, message, wParam, lParam);

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void windowManager::init(HINSTANCE hInstance, const SIZE & windowSize, windowMessageHandler * winMessageHandler)
{
	_hInstance = hInstance;
	_windowSize = windowSize;
	_winMessageHandler = winMessageHandler;

	_hWnd = this->createWindow(hInstance, windowSize);
}

HWND windowManager::createWindow(HINSTANCE hInstance, const SIZE & windowSize)
{
	// 클래스 생성
	WNDCLASS winClass = {
		CS_VREDRAW | CS_HREDRAW,
		WndProc,
		0, 0,
		hInstance,
		LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)GetStockObject(COLOR_WINDOW + 1),
		NULL,
		_className
	};

	// 클래스 등록
	RegisterClass(&winClass);
	RECT winRect = { 0, 0, _windowSize.cx, _windowSize.cy };

	// 윈도우 크기 계산
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, false);

	// 윈도우 생성
	return CreateWindow(winClass.lpszClassName, winClass.lpszClassName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		winRect.right - winRect.left,
		winRect.bottom - winRect.top,
		GetDesktopWindow(),
		NULL,
		winClass.hInstance,
		this);
}

LRESULT windowManager::handleWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_SIZE: {
		_windowSize.cx = LOWORD(lParam);
		_windowSize.cy = HIWORD(lParam);

		GET_WINDOW_APPLICATION()->setWindowSize(_windowSize);
	} break;

	}

	return _winMessageHandler->handleWindowMessage(hWnd, message, wParam, lParam);
}
