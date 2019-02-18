#include "resourceManager.h"
#include "managerList.h"

#include "sound.h"

#include "skinnedMesh.h"
#include "skinnedMeshDup.h"
#include "animationController.h"

resourceManager::resourceManager()
{
}

resourceManager::~resourceManager()
{
	for (auto iter : _mStaticMesh)	{ SAFE_DELETE(iter.second); }
	for (auto iter : _mEffect)		{ SAFE_RELEASE(iter.second); }
	for (auto iter : _mTexture)		{ SAFE_RELEASE(iter.second); }
	for (auto iter : _mSound)		{ SAFE_DELETE(iter.second); }
	for (auto iter : _mTextureCube)	{ SAFE_DELETE(iter.second); }
}

meshSet* resourceManager::createStaticMesh(const string & filePath)
{
	meshSet* meshSt = new meshSet;

	LPD3DXBUFFER bufAdjacency = nullptr;
	LPD3DXBUFFER bufXMaterial = nullptr;

	// �޽� ���� : X����, �𵨸����� ����
	D3DXLoadMeshFromXA(
		filePath.c_str(),
		D3DXMESH_MANAGED,
		MN_DEV,
		&bufAdjacency,			// ���� ����
		&bufXMaterial,			// ���� ����
		NULL,
		&meshSt->numMaterial,	// ������ ����
		&meshSt->mesh);

	for (int i = 0; i < meshSt->numMaterial; ++i)
	{
		auto xMaterial = (LPD3DXMATERIAL)bufXMaterial->GetBufferPointer();
		LPDIRECT3DTEXTURE9 texture = nullptr;

		if (xMaterial[i].pTextureFilename)
		{
			string basePath = "";
			if (filePath.rfind("/") != string::npos)
				basePath = filePath.substr(0, filePath.rfind("/") + 1);

			char texturePath[MAX_PATH] = "";
			sprintf(texturePath, "%s%s", basePath.c_str(), xMaterial[i].pTextureFilename);

			texture = MN_SRC->getTexture(texturePath);
		}
		meshSt->vTextureList.push_back(texture);
		meshSt->vMaterialList.push_back(xMaterial[i].MatD3D);
	}

	D3DVERTEXELEMENT9 element[] = {
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
		{ 0, 24, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0 },
		{ 0, 36, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0 },
		{ 0, 48, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};

	// �纻 ����
	auto originMesh = meshSt->mesh;
	originMesh->CloneMesh(originMesh->GetOptions(),
		element,
		MN_DEV,
		&meshSt->mesh);

	D3DXComputeNormals(meshSt->mesh, (DWORD*)bufAdjacency->GetBufferPointer());					// ���� ���� ���
	D3DXComputeTangent(meshSt->mesh, 0, 0, 0, TRUE, (DWORD*)bufAdjacency->GetBufferPointer());	// ����, ������ ���

	SAFE_RELEASE(bufAdjacency);
	SAFE_RELEASE(bufXMaterial);
	SAFE_RELEASE(originMesh);

	return meshSt;
}

skinnedMesh* resourceManager::createSkinnedMesh(const string & filePath, void * makeParam)
{
	auto mParam = (skinnedMesh::mParam*)makeParam;

	return new skinnedMesh(*mParam);
}

LPD3DXEFFECT resourceManager::createEffect(const string & key)
{
	LPD3DXEFFECT result = nullptr;
	LPD3DXBUFFER bufError = nullptr;

	D3DXCreateEffectFromFileA(
		MN_DEV,
		key.c_str(),
		NULL,
		NULL,
		D3DXSHADER_DEBUG,
		NULL,
		&result,
		&bufError);

	if (bufError != nullptr)
	{
		char * msgError = (char*)bufError->GetBufferPointer();
		printf("resourceManager.createEffect : %s\n", msgError);

		SAFE_RELEASE(bufError);
	}
	return result;
}

LPDIRECT3DTEXTURE9 resourceManager::createTexture(const string & key)
{
	LPDIRECT3DTEXTURE9 result = nullptr;

	D3DXCreateTextureFromFileA(
		MN_DEV,
		key.c_str(),
		&result);

	return result;
}

LPDIRECT3DTEXTURE9 resourceManager::createSpriteTexture(const string & key)
{
	LPDIRECT3DTEXTURE9 result = nullptr;

	D3DXCreateTextureFromFileExA(
		MN_DEV,
		key.c_str(),
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		1,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(0, 0, 0),
		NULL,
		NULL,
		&result);

	return result;
}

sound * resourceManager::createSound(const string & key, bool isBGM)
{
	sound* result = nullptr;

	/*
	< �޸� �� >
	- ���� �ý����� �����ϱ� ���� �����Ǵ� ���
	�޸𸮿� �����ϴ� ��ó�� ���� �����͸� ���� ����
	�޸� �� �̿� ��, ���� �������� ������ ���������� �̷������ ������
	������� ���ϰ� ����
	*/
	HMMIO wavFile = mmioOpenA(	// memory map
		(char*)key.c_str(),
		NULL,
		MMIO_READ);

	if (wavFile != NULL)
	{
		MMCKINFO chunkInfo;
		ZeroMemory(&chunkInfo, sizeof(chunkInfo));

		chunkInfo.fccType = mmioFOURCC('W', 'A', 'V', 'E');
		mmioDescend(wavFile, &chunkInfo, NULL, MMIO_FINDRIFF);				// find resource format

		MMCKINFO subChunkInfo;
		ZeroMemory(&subChunkInfo, sizeof(subChunkInfo));
		subChunkInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
		mmioDescend(wavFile, &subChunkInfo, &chunkInfo, MMIO_FINDCHUNK);	// find chunk

		// ���� ���� ����
		sound::wavInfo* wavInfo = new sound::wavInfo();
		mmioRead(wavFile,
			(char*)(&wavInfo->format),
			sizeof(wavInfo->format));

		mmioAscend(wavFile, &subChunkInfo, 0);

		// ���� ���� ����
		subChunkInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
		mmioDescend(wavFile, &subChunkInfo, &chunkInfo, MMIO_FINDCHUNK);

		wavInfo->numByte = subChunkInfo.cksize;
		wavInfo->nBytes = (BYTE*)malloc(sizeof(BYTE) * subChunkInfo.cksize);

		mmioRead(wavFile,
			(char*)(wavInfo->nBytes),
			subChunkInfo.cksize);

		mmioClose(wavFile, 0);

		return new sound(wavInfo, isBGM);
	}

	return result;
}

LPDIRECT3DCUBETEXTURE9 resourceManager::createTextureCube(const string & key)
{
	LPDIRECT3DCUBETEXTURE9 result = nullptr;

	D3DXCreateCubeTextureFromFileA(MN_DEV,
		key.c_str(),
		&result);

	return result;
}

// ----- add ----- //
template<typename T> 
T resourceManager::addSomthing(const string & key, T value, unordered_map<string, T> & table)
{
	auto iter = table.find(key);

	if (iter != table.end())
		return iter->second;

	// std::make_pair �Լ��� ���� ���� �߰��� ���������� �ӽ� ��ü�� ����Ǳ� ������
	// value_type�� ���� ���� �߰��� �� �� ȿ����
	table.insert(unordered_map<string, T>::value_type(key, value));

	return value;
}

// ----- get ----- //
meshSet * resourceManager::getStaticMesh(const string & key, bool isAutoCreate)
{
	return getSomthing(key, _mStaticMesh, isAutoCreate, (function<meshSet*(void)>)[&]()->auto { return createStaticMesh(key); });
}

skinnedMesh * resourceManager::getSkinnedMesh(const string & key, void * makeParam, bool isAutoCreate)
{
	return getSomthing(key, _mSkinnedMesh, isAutoCreate, (function<skinnedMesh*(void)>)[&]()->auto { return createSkinnedMesh(key, makeParam); });
}

skinnedMesh * resourceManager::getSkinnedMesh(const string & key)
{
	return getSomthing(key, _mSkinnedMesh, false, (function<skinnedMesh*(void)>)nullptr);
}

LPD3DXEFFECT resourceManager::getEffect(const string & key, bool isAutoCreate)
{
	return getSomthing(key, _mEffect, isAutoCreate, (function<LPD3DXEFFECT(void)>)[&]()->auto { return createEffect(key); });
}

LPDIRECT3DTEXTURE9 resourceManager::getTexture(const string & key, bool isAutoCreate)
{
	return getSomthing(key, _mTexture, isAutoCreate, (function<LPDIRECT3DTEXTURE9(void)>)[&]()->auto { return createTexture(key); });
}

LPDIRECT3DTEXTURE9 resourceManager::getSpriteTexture(const string & key, bool isAutoCreate)
{
	return getSomthing(key, _mTexture, isAutoCreate, (function<LPDIRECT3DTEXTURE9(void)>)[&]()->auto { return createSpriteTexture(key); });
}

sound * resourceManager::getSoundBGM(const string & key, bool isAutoCreate)
{
	return getSomthing(key, _mSound, isAutoCreate, (function<sound*(void)>)[&]()->auto { sound* c = createSound(key, true); return c; });
}

sound * resourceManager::getSoundSE(const string & key, bool isAutoCreate)
{
	return getSomthing(key, _mSound, isAutoCreate, (function<sound*(void)>)[&]()->auto { sound* c = createSound(key, false); return c; });
}

LPDIRECT3DCUBETEXTURE9 resourceManager::getTextureCube(const string & key, bool isAutoCreate)
{
	return getSomthing(key, _mTextureCube, isAutoCreate, (function<LPDIRECT3DCUBETEXTURE9(void)>)[&]()->auto { return createTextureCube(key); });
}

template<typename T> 
T resourceManager::getSomthing(const string & key, unordered_map<string, T> & table, bool isAutoCreate, function<T(void)> creater)
{
	auto iter = table.find(key);

	if (iter == table.end())
	{
		T val = nullptr;

		if (isAutoCreate)
		{
			val = creater();
			return addSomthing(key, val, table);
		}
	}

	return iter->second;
}