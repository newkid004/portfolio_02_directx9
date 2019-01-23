#pragma once

#include "kGlobalDefine.h"
#include "renderObject.h"

using namespace std;

class staticMesh : public renderObject
{
public :
	struct mParam
	{
		string meshFilePath;
		string effectFilePath;
	};


private :
	LPD3DXEFFECT _effect = nullptr;
	meshSet* _info = nullptr;
	mParam _param;

protected :
	virtual void drawDo(void) override;

public :


public:
	staticMesh();
	staticMesh(mParam & param);

	~staticMesh();
};

