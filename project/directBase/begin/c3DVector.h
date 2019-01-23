#pragma once
#include "kGlobalDefine.h"

class c3DMatrix;

class c3DVector
{
public :
	NUM_REAL x = 0.0;
	NUM_REAL y = 0.0;
	NUM_REAL z = 0.0;

public :
	// ���� ��ȯ
	static NUM_REAL getLength(c3DVector & input);

	// ���� ���� ��ȯ
	static c3DVector getNormalize(c3DVector & input);

public :	// operator
	c3DVector operator*(NUM_REAL scalar);		// ��Į�� ���� ��ȯ

	c3DVector operator+(const c3DVector & input);	// ���� ��ȯ
	c3DVector operator-(const c3DVector & input);	// ���� ��ȯ
	NUM_REAL operator<<(const c3DVector & input);	// ���� ��ȯ
	c3DVector operator>>(const c3DVector & input);	// ���� ��ȯ

public :	// matrix
	c3DVector getTransform(const c3DMatrix & input);

public :
	static void* actXYZ(c3DVector & input, std::function<void*(NUM_REAL, NUM_REAL, NUM_REAL)> & act) { return act(input.x, input.y, input.z); }

public:
	c3DVector(NUM_REAL x = 0.f, NUM_REAL y = 0.f, NUM_REAL z = 0.f);
	~c3DVector() {};
};

