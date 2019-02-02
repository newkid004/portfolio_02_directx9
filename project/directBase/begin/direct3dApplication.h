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

public:	// ----- 인터페이스 ----- //
	LRESULT handleWindowMessage(
		HWND hWnd,
		UINT message,
		WPARAM wParam,
		LPARAM lParam) override;

protected:
	// 어플리케이션 초기화
	virtual void init(void) override;
	virtual void update(void) override;
	virtual void draw(void) override;
	virtual void drawUI(void) override;

	// 메세지 루프 실행
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

public:		// ----- 생성, 소멸자 ----- //
	direct3dApplication(HINSTANCE hInstance, const SIZE & windowSize, int option)
		: iWindowApplication(hInstance, windowSize, option) {};
	virtual ~direct3dApplication();
};

