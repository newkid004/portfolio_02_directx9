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
	// ±æÀÌ ¹ÝÈ¯
	static NUM_REAL getLength(c3DVector & input);

	// Á¤±Ô º¤ÅÍ ¹ÝÈ¯
	static c3DVector getNormalize(c3DVector & input);

public :	// operator
	c3DVector operator*(NUM_REAL scalar);		// ½ºÄ®¶ó °ö¼À ¹ÝÈ¯

	c3DVector operator+(const c3DVector & input);	// µ¡¼À ¹ÝÈ¯
	c3DVector operator-(const c3DVector & input);	// »¬¼À ¹ÝÈ¯
	NUM_REAL operator<<(const c3DVector & input);	// ³»Àû ¹ÝÈ¯
	c3DVector operator>>(const c3DVector & input);	// ¿ÜÀû ¹ÝÈ¯

public :	// matrix
	c3DVector getTransform(const c3DMatrix & input);

public :
	static void* actXYZ(c3DVector & input, std::function<void*(NUM_REAL, NUM_REAL, NUM_REAL)> & act) { return act(input.x, input.y, input.z); }

public:
	c3DVector(NUM_REAL x = 0.f, NUM_REAL y = 0.f, NUM_REAL z = 0.f);
	~c3DVector() {};
};

