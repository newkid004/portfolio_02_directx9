#pragma once
#include "kGlobalDefine.h"

// ������ �޼��� ó����
class windowMessageHandler
{
public :	// ----- interface ----- //
	virtual LRESULT handleWindowMessage(
		HWND hWnd,
		UINT message,
		WPARAM wParam,
		LPARAM lParam) = 0;
};

