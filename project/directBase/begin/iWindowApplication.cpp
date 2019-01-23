#include "iWindowApplication.h"
#include "windowManager.h"

static iWindowApplication* _instance = NULL;

iWindowApplication::iWindowApplication(HINSTANCE hInstance, const SIZE & windowSize, int option)
	:
	_windowSize(windowSize),
	_hInstance(hInstance),
	_option(option)
{
	_instance = this;

	if (AllocConsole())
	{
		freopen("CONIN$", "rb", stdin);
		freopen("CONOUT$", "wb", stdout);
		freopen("CONOUT$", "wb", stderr);
	}
}

iWindowApplication::~iWindowApplication()
{
	FreeConsole();
}

void iWindowApplication::init(void)
{
	GET_WINDOW_MANAGER()->init(_hInstance, _windowSize, this);
}

int iWindowApplication::run(void)
{
	this->init();

	// 윈도우 출력
	ShowWindow(GET_WINDOW_HANDLE(), _option);
	UpdateWindow(GET_WINDOW_HANDLE());

	return msgLoop();
}

iWindowApplication * iWindowApplication::getInstance(void)
{
	return _instance;
}

LRESULT iWindowApplication::handleWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY: {
		this->handleDestroyMsg(wParam, lParam);
	} break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void iWindowApplication::handleDestroyMsg(WPARAM wParam, LPARAM lParam)
{
	PostQuitMessage(0);
}

int iWindowApplication::msgLoop(void)
{
	MSG message;
	ZeroMemory(&message, sizeof(message));

	while (GetMessage(&message, NULL, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return (int)message.wParam;
}
