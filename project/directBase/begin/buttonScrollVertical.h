#pragma once
#include "kGlobalDefine.h"
#include "buttonStatic.h"

constexpr float BTN_SCROLL_SIZE_X = 18.0f;

class buttonStatic;

class buttonScrollVerticalHead : public buttonBase
{
public :
	// * 아래의 클래스에만 필요 * //
	friend class buttonScrollVertical;

private :
	bool _isClicked = false;
	LONG _beforePosY;

	buttonBase* _body = nullptr;
	buttonBase* _armTop = nullptr;
	buttonBase* _armBot = nullptr;

public :
	UI_LIST_NODE updateAlways(void) override;
	UI_LIST_NODE updateActive(void) override;

public :
	void moveScroll(LONG interval);

private :
	buttonScrollVerticalHead(windowBase* bind);
	~buttonScrollVerticalHead() {};
};

// ----- scroll arm ----- //
class buttonScrollVerticalArm : public buttonStatic
{
public:
	// * 아래의 클래스에만 필요 * //
	friend class buttonScrollVertical;

public :


private:
	buttonScrollVerticalArm(windowBase* bind);
	~buttonScrollVerticalArm() {};
};

// ----- scroll body ----- //
class buttonScrollVertical : public buttonBase
{
protected :
	buttonScrollVerticalHead* _head = nullptr;
	buttonScrollVerticalArm* _armTop = nullptr;
	buttonScrollVerticalArm* _armBot = nullptr;

	float _viewHeight = 1.0f;
	float _listHeight = 1.0f;
	float _value = 0.0f;
	activeScrollSet _activeScrollSet;

public :
	UI_LIST_NODE updateAlways(void) override;
	UI_LIST_NODE updateActive(void) override;

public :
	void putListHeight(int ListHeight, float viewHeight = 1.0f);

public :
	float & getValue(void) { return _value; }

public:
	buttonScrollVertical(windowBase* bind, int listHeight = 1.0f, float viewHeight = 1.0f);
	~buttonScrollVertical();
};

// ----- scroll func ----- //
class btnScrollFunc
{
public :
	static buttonScrollVerticalHead* b2Head(buttonBase* btn);
	static buttonScrollVerticalArm* b2Arm(buttonBase* btn);
	static buttonScrollVertical* b2Body(buttonBase* btn);

private :
	btnScrollFunc() {}
	~btnScrollFunc() {}
};