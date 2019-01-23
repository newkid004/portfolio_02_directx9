#pragma once
#include "kGlobalDefine.h"

// 윈도우 메세지 처리자
class windowMessageHandler
{
public :	// ----- interface ----- //
	virtual LRESULT handleWindowMessage(
		HWND hWnd,
		UINT message,
		WPARAM wParam,
		LPARAM lParam) = 0;
};

