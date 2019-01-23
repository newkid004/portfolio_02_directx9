#pragma once

#include "kGlobalDefine.h"
#include "direct3dApplication.h"

class skinnedMesh;

class practice_09 : public direct3dApplication
{
private:
	skinnedMesh* _skinnedMesh = nullptr;

public:
	void init(void) override;
	void update(void) override;
	void draw(void) override;

private :
	void updateControl(void);

private:
	skinnedMesh* createSkinnedMesh(void);

public:
	practice_09(HINSTANCE hInstance, const SIZE & windowSize, int option);
	~practice_09();
};

