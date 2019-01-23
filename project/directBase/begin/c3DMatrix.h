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
	// ���� ���
	static c3DMatrix getIdentity(void);

	// �̵� ���
	static c3DMatrix getTranslate(NUM_REAL* input);
	static c3DMatrix getTranslate(NUM_REAL x = 0, NUM_REAL y = 0, NUM_REAL z = 0);

	// ô�� ���
	static c3DMatrix getScale(NUM_REAL* input);
	static c3DMatrix getScale(NUM_REAL x = 0, NUM_REAL y = 0, NUM_REAL z = 0);

	// ȸ�� ���
	static c3DMatrix getRotate(NUM_REAL roll);

	// ��ġ ���
	c3DMatrix getTranspose(void);

public :		// operator
	NUM_REAL & operator()(int row, int col) { return _matrix[row][col]; };		// ���� ������ 
	NUM_REAL operator()(int row, int col) const { return _matrix[row][col]; };

	c3DMatrix operator+(const c3DMatrix & input);	// ��� ����
	c3DMatrix operator-(const c3DMatrix & input);	// ��� ����
	c3DMatrix operator*(const c3DMatrix & input);	// ��� ����

	c3DMatrix operator*(const NUM_REAL & input);	// ���� ����

public:
	c3DMatrix(void) { memset(_matrix, 0, sizeof(_matrix)); };
	~c3DMatrix(void) {};
};