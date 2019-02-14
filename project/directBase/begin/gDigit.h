#pragma once

class gDigit
{
public :
	static int chk		(int L, int R)		{ return L & R; }
	static int mask		(int & L, int R)	{ return L &= R;}
	static int put		(int & L, int R)	{ return L |= R; }
	static int pick		(int & L, int R)	{ return L &= (~R); }
	static int toggle	(int & L, int R)	{ return L ^= R; }

private :
	gDigit() {};
	~gDigit() {};
};
