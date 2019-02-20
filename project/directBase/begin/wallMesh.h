#pragma once
#include "KGlobalDefine.h"
#include "staticMesh.h"

class wallMesh : public staticMesh
{
protected:			// protected �Լ�

	//! ��ü�� �׸��� ��
	virtual void drawPre(void) override final;

	//! ��ü�� �׸���
	virtual void drawDo(void) override final;

	//! ��ü�� �׸� ��
	virtual void drawPost(void) override final;

public:

	wallMesh();
	wallMesh(const staticMesh::mParam & param, std::string textureFilePath, std::string normalTextureFilePath);

	virtual ~wallMesh(void);

	string getTexturePath(void) { return _texturePath; }
	string getNormalTexturePath(void) { return _normalTexturePath; }

private:

	float _parallax = 0.0f;

	mParam _wallParam;

	string _texturePath = "";
	string _normalTexturePath = "";

	LPDIRECT3DTEXTURE9 _texture = nullptr;
	LPDIRECT3DTEXTURE9 _normalTexture = nullptr;
};