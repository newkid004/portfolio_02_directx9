#pragma once

class gDigit
{
public :
	static bool chk		(int L, int R)		{ return 0 < (L & R); }
	static bool mask	(int & L, int R)	{ return 0 < (L &= R);}
	static bool put		(int & L, int R)	{ return 0 < (L |= R); }
	static bool pick	(int & L, int R)	{ return 0 < (L &= (~R)); }
	static bool toggle	(int & L, int R)	{ return 0 < (L ^= R); }

private :
	gDigit() {};
	~gDigit() {};
};
