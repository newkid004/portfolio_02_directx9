#pragma once
#include "camera.h"

class cameraControlable : public camera
{
private :
	struct vertex
	{
		enum
		{
			FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE
		};
		D3DXVECTOR3 pos;
		D3DCOLOR diffuse;
	};

protected :
	bool _isMoveable = true;

	POINT _mousePrevPosition;
	float _velocity;

	bool _isVisible = true;
	baseObject* _defObject = nullptr;
	LPDIRECT3DVERTEXBUFFER9 _defVertexBuffer = nullptr;

public :
	void update(void) override;
	void draw(void) override;

protected:
	void updateControl(void);

private :
	LPDIRECT3DVERTEXBUFFER9 createDefVertex(void);

public :
	bool getMoveable(void) { return _isMoveable; }
	void setMoveable(bool input) { _isMoveable = input; }

	float getVelocity(void) { return _velocity; }
	void setVelocity(float input) { _velocity = input; }

	void setVisible(bool input) { _isVisible = input; }

public:
	cameraControlable(float aspect, float fov, float maxDistance);
	virtual ~cameraControlable();
};

