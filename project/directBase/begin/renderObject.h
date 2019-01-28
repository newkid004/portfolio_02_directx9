#pragma once
#include "kGlobalDefine.h"
#include "baseObject.h"
#include "iRenderable.h"

class debugGizmo;
class debugDraw;

class renderObject : public baseObject, public iRenderable
{
protected:
	bool _isVisible = true;
	bool _isDebugEnable = false;

	boundingBox _bBox;
	boundingSphere _bSphere;

	objectBox _oBox;

	debugDraw* _debugDraw = nullptr;

public :	// iterface
	virtual void draw(void) final override;

protected:
	virtual void drawPre(void) {};
	virtual void drawDo(void) {};
	virtual void drawPost(void) {};

public:
	void ToggleVisible(void) { _isVisible = !_isVisible; }

	bool getVisible(void) { return _isVisible; }
	bool getDebugEnalbe(void) { return _isDebugEnable; }
	constexpr boundingBox & getBoundingBox(void) { return _bBox; }
	constexpr boundingSphere & getBoundingSphere(void) { return _bSphere; }
	void getBoundingBoxFinal(boundingBox * out);
	void getBoundingSphereFinal(boundingSphere * out);
	void getObjectBox(objectBox * out);
	debugDraw* getDebugDraw(void) { return _debugDraw; }

	void setVisible(bool input) { _isVisible = input; }
	void setDebugEnalbe(bool input, EDebugDrawType drawType = EDebugDrawType::BOX);
	void setBoundingBox(const boundingBox & input) { _bBox = input; };
	void setBoundingSphere(const boundingSphere & input) { _bSphere = input; };

protected :
	renderObject();

public:
	~renderObject();
};