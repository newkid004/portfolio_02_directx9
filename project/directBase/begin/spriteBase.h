#pragma once
#include "kGlobalDefine.h"
#include "UIBase.h"

using namespace std;

class spriteBase :  public UIBase
{
private :
	LPDIRECT3DTEXTURE9 _texture = nullptr;

protected :
	virtual void drawDoUI(void);

public :
	void setTexture(const string & filePath);

public:
	spriteBase(const string & filePath);
	~spriteBase() {};
};

