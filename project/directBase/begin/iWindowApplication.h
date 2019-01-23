#pragma once
#include "kGlobalDefine.h"

#include "windowMessageHandler.h"

// 윈도우 어플리케이션
class iWindowApplication : public windowMessageHandler
{
protected :
	HINSTANCE _hInstance;
	SIZE _windowSize;
	UINT _option;

public :
	// 어플리케이션 실행
	int run(void);

public :	// ----- 접근, 지정자 ----- //
	static iWindowApplication* getInstance(void);
	virtual void setWindowSize(const SIZE & winSize) { _windowSize = winSize; };

public :	// ----- 인터페이스 ----- //
	LRESULT handleWindowMessage(
		HWND hWnd,
		UINT message,
		WPARAM wParam,
		LPARAM lParam) override;

protected :
	// 어플리케이션 초기화
	virtual void init(void);

	// 제거 메세지 처리
	virtual void handleDestroyMsg(WPARAM wParam, LPARAM lParam);

	// 메세지 루프 실행
	virtual int msgLoop(void);

protected :	// ----- 생성, 소멸자 ----- //
	iWindowApplication(HINSTANCE hInstance, const SIZE & windowSize, int option);

	virtual ~iWindowApplication();
};

