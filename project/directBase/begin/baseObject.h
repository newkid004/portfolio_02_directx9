#pragma once
#include "kGlobalDefine.h"
#include "iUpdateble.h"

class baseObject : public iUpdateble
{
protected :
	baseObject* _parent;
	std::vector<baseObject*> _vChildren;

	D3DXVECTOR3 _position;
	D3DXVECTOR3 _scale;
	D3DXVECTOR3 _directionRight;
	D3DXVECTOR3 _directionUp;
	D3DXVECTOR3 _directionForward;

	D3DXMATRIXA16 _mWorld;
	D3DXMATRIXA16 _mOffset;

	D3DXVECTOR3 _offsetPosition;

public :	// interface
	virtual void update(void) override;

public :
	void addChild(baseObject* input);
	void removeChild(baseObject* input);

public :
	// 해당 축을 기준으로 이동
	void moveX(float distance, bool isLocal = true);
	void moveY(float distance, bool isLocal = true);
	void moveZ(float distance, bool isLocal = true);

	// 해당 축을 기준으로 회전
	void rotateX(float angle, bool isLocal = true);
	void rotateY(float angle, bool isLocal = true);
	void rotateZ(float angle, bool isLocal = true);

	// 특정 기준으로 회전
	void rotate2Pos(const D3DXVECTOR3 & pos, bool isSphere = true, bool isFixAxisX = false);
	void rotate2Dir(const D3DXVECTOR3 & dir, bool isSphere = true, bool isFixAxisX = false);
	void rotate2Mat(const D3DXMATRIXA16 & mat);
	void rotateBillboard(bool isFixAxisX = false, bool isFront = false);

	void normalizeAxis(void);

public :	// 접근, 지정자
	D3DXMATRIXA16* getMatrixWorldPoint(void) { return &_mWorld; }
	D3DXMATRIXA16 getMatrixWorld(void) { return _mWorld; }
	D3DXMATRIXA16 getMatrixFinal(void);
	D3DXMATRIXA16 getMatrixRotate(void);

	constexpr D3DXVECTOR3 & getPosition			(void) { return _position; }
	constexpr D3DXVECTOR3 & getScale			(void) { return _scale; }
	constexpr D3DXVECTOR3 & getDirectRight		(void) { return _directionRight; }
	constexpr D3DXVECTOR3 & getDirectUp			(void) { return _directionUp; }
	constexpr D3DXVECTOR3 & getDirectForward	(void) { return _directionForward; }

	D3DXVECTOR3 getOffset(void) { return D3DXVECTOR3(_mOffset(3, 0), _mOffset(3, 1), _mOffset(3, 2)); }
	constexpr D3DXVECTOR3 & getOffsetPosition(void) { return _offsetPosition; }
	
	// 지정자
	void setParent					(baseObject* input);
	void setRotation				(const D3DXVECTOR3 & input);

	void setPosition				(const D3DXVECTOR3 & input)	{ _position = input; }
	void setScale					(const D3DXVECTOR3 & input)	{ _scale = input; }
	void setScale					(float input)				{ setScale(D3DXVECTOR3(input, input, input)); }
	void setDirectionRight			(const D3DXVECTOR3 & input)	{ _directionRight = input; }
	void setDirectionUp				(const D3DXVECTOR3 & input)	{ _directionUp = input; }
	void setDirectionForward		(const D3DXVECTOR3 & input) { _directionForward = input; }

	void setMatrixOffset			(const D3DXMATRIXA16 & input) { _mOffset = input; }

private:
	void putOffsetPosition(void);

public:
	baseObject();
	virtual ~baseObject();
};

