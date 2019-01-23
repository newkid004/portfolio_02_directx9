#pragma once
#include "kGlobalDefine.h"

class c3DMatrix
{
public :
	enum
	{
		SIZE = 3
	};
private :
	NUM_REAL _matrix[SIZE][SIZE];

public :
	// ´ÜÀ§ Çà·Ä
	static c3DMatrix getIdentity(void);

	// ÀÌµ¿ Çà·Ä
	static c3DMatrix getTranslate(NUM_REAL* input);
	static c3DMatrix getTranslate(NUM_REAL x = 0, NUM_REAL y = 0, NUM_REAL z = 0);

	// Ã´µµ Çà·Ä
	static c3DMatrix getScale(NUM_REAL* input);
	static c3DMatrix getScale(NUM_REAL x = 0, NUM_REAL y = 0, NUM_REAL z = 0);

	// È¸Àü Çà·Ä
	static c3DMatrix getRotate(NUM_REAL roll);

	// ÀüÄ¡ Çà·Ä
	c3DMatrix getTranspose(void);

public :		// operator
	NUM_REAL & operator()(int row, int col) { return _matrix[row][col]; };		// ¼ÒÀç °¡Á®¿È 
	NUM_REAL operator()(int row, int col) const { return _matrix[row][col]; };

	c3DMatrix operator+(const c3DMatrix & input);	// Çà·Ä µ¡¼À
	c3DMatrix operator-(const c3DMatrix & input);	// Çà·Ä »¬¼À
	c3DMatrix operator*(const c3DMatrix & input);	// Çà·Ä °ö¼À

	c3DMatrix operator*(const NUM_REAL & input);	// ´ÜÀ§ °ö¼À

public:
	c3DMatrix(void) { memset(_matrix, 0, sizeof(_matrix)); };
	~c3DMatrix(void) {};
};