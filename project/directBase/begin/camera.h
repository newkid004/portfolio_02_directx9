#pragma once
#include "kGlobalDefine.h"
#include "baseObject.h"
#include "iRenderable.h"

class camera : public baseObject, public iRenderable
{
public :
	enum STATE_SWITCH	// bool Çü
	{
		HORIZONTAL = 0x1,
		NONE = 0
	};

protected:
	int _state = 0;

	D3DXMATRIXA16 _mView;
	D3DXMATRIXA16 _mProjection;
	D3DXPLANE _planeFrustum[6];	// near, far / left, right / top, bottom

public:
	virtual void update(void) override;
	virtual void update(const D3DXVECTOR3 & targetDirection);
	virtual void update(baseObject* targetObject);

	virtual void draw(void) override {};

private :
	virtual void updateCamera(void);

	virtual void updateAxis(void);
	virtual void updateRotate(void);
	virtual void updateTranslate(void);

public :
	bool isCullFrustum(const D3DXVECTOR3 & pos);
	bool isCullFrustum(const boundingSphere & bound);

public :
	void getState(STATE_SWITCH state, int* out) { *out = _state & state; }
	void setState(STATE_SWITCH state, bool input) { _state = input ? (_state | state) : (_state & (~state)); }

	virtual void setAspect(float aspect, float fov = 60.0f, float maxDistance = 1000.0f);

	constexpr D3DXMATRIXA16 & getMatrixView(void) { return _mView; }
	constexpr D3DXMATRIXA16 & getMatrixProjection(void) { return _mProjection; }

protected :
	void putFrustum(void);

public:
	camera(float aspect, float fov = 60.0f, float maxDistance = 1000.0f);
	virtual ~camera() { };
};