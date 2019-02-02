#pragma once
#include "kGlobalDefine.h"
#include "iWindowApplication.h"

#include "iUpdateble.h"
#include "iRenderable.h"

class camera;
class debugGrid;
class lightBase;
class labelBase;
class frustum;

class direct3dApplication : 
	public iWindowApplication,
	public iUpdateble,
	public iRenderable
{
protected :
	camera* _camera = nullptr;
	frustum* _frustum = nullptr;

	debugGrid* _grid = nullptr;
	lightBase* _light = nullptr;
	labelBase* _label = nullptr;
	LPD3DXSPRITE _sprite = nullptr;

public:	// ----- �������̽� ----- //
	LRESULT handleWindowMessage(
		HWND hWnd,
		UINT message,
		WPARAM wParam,
		LPARAM lParam) override;

protected:
	// ���ø����̼� �ʱ�ȭ
	virtual void init(void) override;
	virtual void update(void) override;
	virtual void draw(void) override;
	virtual void drawUI(void) override;

	// �޼��� ���� ����
	virtual int msgLoop(void) final override;

protected :
	LPD3DXSPRITE createSprite(void);
	virtual void createMember(void);

public :
	camera* getCamera(void) { return _camera; }
	frustum* getFrustum(void) { return _frustum; }
	void setCamera(camera* input) { _camera = input; }

	lightBase* getLight(void) { return _light; }
	labelBase* getLabel(void) { return _label; }
	LPD3DXSPRITE getSprite(void) { return _sprite; }

	void setWindowSize(const SIZE & input) override;

public:		// ----- ����, �Ҹ��� ----- //
	direct3dApplication(HINSTANCE hInstance, const SIZE & windowSize, int option)
		: iWindowApplication(hInstance, windowSize, option) {};
	virtual ~direct3dApplication();
};

