#include "c3DMatrix.h"

c3DMatrix c3DMatrix::getIdentity(void)
{
	c3DMatrix m;
	for (int i = 0; i < SIZE; ++i)
		m(i, i) = 1.f;

	return m;
}

c3DMatrix c3DMatrix::getTranspose(void)
{
	c3DMatrix m;
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
			m(j, i) = _matrix[i][j];
	}

	return m;
}

c3DMatrix c3DMatrix::getTranslate(NUM_REAL* input)
{
	/* 이동 행렬 
		1	0	0
		0	1	0
		x	y	1
	*/
	c3DMatrix m = c3DMatrix::getIdentity();

	int count = SIZE - 1;
	for (int i = 0; i < count; ++i)
		m(count, i) = *(input + i);

	return m;
}

c3DMatrix c3DMatrix::getTranslate(NUM_REAL x, NUM_REAL y, NUM_REAL z)
{
	NUM_REAL input[] = { x, y, z };
	return getTranslate(input);
}

c3DMatrix c3DMatrix::getScale(NUM_REAL* input)
{
	/* 척도 행렬
		x	0	0
		0	y	0
		0	0	1
	*/
	c3DMatrix m = c3DMatrix::getIdentity();

	int count = SIZE - 1;
	for (int i = 0; i < count; ++i)
		m(i, i) = *(input + i);

	return m;
}

c3DMatrix c3DMatrix::getScale(NUM_REAL x, NUM_REAL y, NUM_REAL z)
{
	NUM_REAL input[] = { x, y, z };
	return getScale(input);
}

c3DMatrix c3DMatrix::getRotate(NUM_REAL roll)
{
	/* 회전 행렬(Roll)
	 cosΘ	sinΘ	0
	-sinΘ	cosΘ	0
	 0		0		1
	*/
	c3DMatrix m = c3DMatrix::getIdentity();

	m(0, 0) = cos(roll);
	m(1, 1) = cos(roll);
	m(0, 1) = sin(roll);
	m(1, 0) = -sin(roll);

	return m;
}

c3DMatrix c3DMatrix::operator+(const c3DMatrix & input)
{
	c3DMatrix m;
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
			m(i, j) = _matrix[i][j] + input(i, j);
	}
	return m;
}

c3DMatrix c3DMatrix::operator-(const c3DMatrix & input)
{
	c3DMatrix m;
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
			m(i, j) = _matrix[i][j] - input(i, j);
	}
	return m;
}

c3DMatrix c3DMatrix::operator*(const c3DMatrix & input)
{
	c3DMatrix m;
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			for (int k = 0; k < SIZE; ++k)
				m(i, j) += _matrix[i][k] * input(k, j);
		}
	}
	return m;
}
c3DMatrix c3DMatrix::operator*(const NUM_REAL & input)
{
	c3DMatrix m;
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
			m(i, j) = _matrix[i][j] * input;
	}
	return m;
}