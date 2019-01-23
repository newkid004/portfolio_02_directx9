#pragma once
#include "kGlobalDefine.h"

#include "windowMessageHandler.h"

// ������ ���ø����̼�
class iWindowApplication : public windowMessageHandler
{
protected :
	HINSTANCE _hInstance;
	SIZE _windowSize;
	UINT _option;

public :
	// ���ø����̼� ����
	int run(void);

public :	// ----- ����, ������ ----- //
	static iWindowApplication* getInstance(void);
	virtual void setWindowSize(const SIZE & winSize) { _windowSize = winSize; };

public :	// ----- �������̽� ----- //
	LRESULT handleWindowMessage(
		HWND hWnd,
		UINT message,
		WPARAM wParam,
		LPARAM lParam) override;

protected :
	// ���ø����̼� �ʱ�ȭ
	virtual void init(void);

	// ���� �޼��� ó��
	virtual void handleDestroyMsg(WPARAM wParam, LPARAM lParam);

	// �޼��� ���� ����
	virtual int msgLoop(void);

protected :	// ----- ����, �Ҹ��� ----- //
	iWindowApplication(HINSTANCE hInstance, const SIZE & windowSize, int option);

	virtual ~iWindowApplication();
};

