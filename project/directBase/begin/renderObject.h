#pragma once
#include "kGlobalDefine.h"
#include "baseObject.h"
#include "iRenderable.h"

class debugGizmo;
class debugDraw;

class renderObject : public baseObject, public iRenderable
{
public:
	struct BOUNDBOXSET
	{
		boundingBox box;
		D3DXMATRIXA16 matrix;
	};

	struct BOUNDSPHERESET
	{
		boundingSphere sphere;
		D3DXMATRIXA16 matrix;
	};

	typedef std::unordered_map<std::string, BOUNDBOXSET> BOUNDBOXMATRIXSET;
	typedef std::unordered_map<std::string, BOUNDSPHERESET> BOUNDSPHEREMATRIXSET;

protected:
	bool _isCull = false;
	bool _isVisible = true;
	bool _isDebugEnable = false;

	boundingBox _bBox;
	boundingSphere _bSphere;

	objectBox _oBox;

	debugDraw* _debugDraw = nullptr;

	std::vector<boundingBox> _vbBox;
	std::vector<boundingSphere> _vbSphere;

	BOUNDBOXMATRIXSET _mbBoxSet;
	BOUNDSPHEREMATRIXSET _mbSphereSet;


public :	// iterface
	virtual void update(void) override;
	virtual void draw(void) final override;

protected:
	virtual bool cullFrustum(void);

	virtual void drawPre(void) {};
	virtual void drawDo(void) {};
	virtual void drawPost(void) {};

public:
	void ToggleVisible(void) { _isVisible = !_isVisible; }

	bool isCull(void) { return _isCull; }
	bool getVisible(void) { return _isVisible; }
	bool getDebugEnalbe(void) { return _isDebugEnable; }

	std::vector<boundingBox> & getBoundingBoxList(void) { return _vbBox; }
	std::vector<boundingSphere> & getBoundingSphereList(void) { return _vbSphere; }
	BOUNDBOXMATRIXSET & getBoundingBoxSetList(void) { return _mbBoxSet; }
	BOUNDSPHEREMATRIXSET & getBoundingSphereSetList(void) { return _mbSphereSet; }

	constexpr boundingBox & getBoundingBox(void) { return _bBox; }
	constexpr boundingSphere & getBoundingSphere(void) { return _bSphere; }

	void getBoundingBoxFinal(boundingBox * out);
	void getBoundingSphereFinal(boundingSphere * out);
	void getObjectBox(objectBox * out);

	debugDraw* getDebugDraw(void) { return _debugDraw; }

	void setVisible(bool input) { _isVisible = input; }
	void setDebugEnable(bool input, EDebugDrawType drawType = EDebugDrawType::BOX);
	void setBoundingBox(const boundingBox & input) { _vbBox.push_back(input); }
	void setBoundingBox(std::string name, BOUNDBOXSET & input) { _mbBoxSet.insert(BOUNDBOXMATRIXSET::value_type(name, input)); }
	void setBoundingSphere(const boundingSphere & input) { _bSphere = input; }
	void setBoundingSphere(std::string name, BOUNDSPHERESET & input) { _mbSphereSet.insert(BOUNDSPHEREMATRIXSET::value_type(name, input)); }

	void setBoundingBoxMatrix(std::string name, D3DXMATRIXA16 & mat) { _mbBoxSet.find(name)->second.matrix = mat; }

protected :
	renderObject();

public:
	~renderObject();
};