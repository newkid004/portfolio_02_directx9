#include "resourceManager.h"
#include "managerList.h"

#include "skinnedMesh.h"
#include "patternMesh.h"
#include "patternMeshDup.h"
#include "animationController.h"

resourceManager::resourceManager()
{
}

resourceManager::~resourceManager()
{
	for (auto iter : _mEffect)		{ SAFE_RELEASE(iter.second); }
	for (auto iter : _mTexture)		{ SAFE_RELEASE(iter.second); }
	for (auto iter : _mStaticMesh)	{ SAFE_DELETE(iter.second); }
	for (auto iter : _mSkinnedMesh) { SAFE_DELETE(iter.second); }
	for (auto iter : _mTextureCube)	{ SAFE_RELEASE(iter.second); }
	for (auto iter : _mPatternMesh) { SAFE_DELETE(iter.second); }
}

meshSet* resourceManager::createStaticMesh(const string & filePath)
{
	meshSet* meshSt = new meshSet;

	LPD3DXBUFFER bufAdjacency = nullptr;
	LPD3DXBUFFER bufXMaterial = nullptr;

	// 메쉬 생성 : X파일, 모델링으올 부터
	D3DXLoadMeshFromXA(
		filePath.c_str(),
		D3DXMESH_MANAGED,
		MN_DEV,
		&bufAdjacency,			// 인자 정보
		&bufXMaterial,			// 재질 정보
		NULL,
		&meshSt->numMaterial,	// 재질의 개수
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

	// 사본 생성
	auto originMesh = meshSt->mesh;
	originMesh->CloneMesh(originMesh->GetOptions(),
		element,
		MN_DEV,
		&meshSt->mesh);

	D3DXComputeNormals(meshSt->mesh, (DWORD*)bufAdjacency->GetBufferPointer());					// 인접 정보 계산
	D3DXComputeTangent(meshSt->mesh, 0, 0, 0, TRUE, (DWORD*)bufAdjacency->GetBufferPointer());	// 접선, 종법선 계산

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

LPDIRECT3DCUBETEXTURE9 resourceManager::createTextureCube(const string & key)
{
	LPDIRECT3DCUBETEXTURE9 result = nullptr;

	D3DXCreateCubeTextureFromFileA(MN_DEV,
		key.c_str(),
		&result);

	return result;
}

patternMesh * resourceManager::createPatternMesh(const string & key, void * makeParam)
{
	auto mParam = (patternMesh::mParam*)makeParam;
	return new patternMesh(*mParam);
}

// ----- add ----- //
template<typename T> 
T resourceManager::addSomthing(const string & key, T value, unordered_map<string, T> & table)
{
	auto iter = table.find(key);

	if (iter != table.end())
		return iter->second;

	// std::make_pair 함수에 의한 값의 추가는 내부적으로 임시 객체가 복사되기 때문에
	// value_type에 의한 값의 추가가 좀 더 효율적
	table.insert(unordered_map<string, T>::value_type(key, value));

	return value;
}

// ----- get ----- //
meshSet * resourceManager::getStaticMesh(const string & key, bool isAutoCreate)
{
	return getSomething(key, _mStaticMesh, isAutoCreate, (function<meshSet*(void)>)[&]()->auto { return createStaticMesh(key); });
}

skinnedMesh * resourceManager::getSkinnedMesh(const string & key, void * makeParam, bool isAutoCreate)
{
	return getSomething(key, _mSkinnedMesh, isAutoCreate, (function<skinnedMesh*(void)>)[&]()->auto { return createSkinnedMesh(key, makeParam); });
}

skinnedMesh * resourceManager::getSkinnedMesh(const string & key)
{
	return getSomething(key, _mSkinnedMesh, false, (function<skinnedMesh*(void)>)nullptr);
}

LPD3DXEFFECT resourceManager::getEffect(const string & key, bool isAutoCreate)
{
	return getSomething(key, _mEffect, isAutoCreate, (function<LPD3DXEFFECT(void)>)[&]()->auto { return createEffect(key); });
}

LPDIRECT3DTEXTURE9 resourceManager::getTexture(const string & key, bool isAutoCreate)
{
	return getSomething(key, _mTexture, isAutoCreate, (function<LPDIRECT3DTEXTURE9(void)>)[&]()->auto { return createTexture(key); });
}

LPDIRECT3DTEXTURE9 resourceManager::getSpriteTexture(const string & key, bool isAutoCreate)
{
	return getSomething(key, _mTexture, isAutoCreate, (function<LPDIRECT3DTEXTURE9(void)>)[&]()->auto { return createSpriteTexture(key); });
}

LPDIRECT3DCUBETEXTURE9 resourceManager::getTextureCube(const string & key, bool isAutoCreate)
{
	return getSomething(key, _mTextureCube, isAutoCreate, (function<LPDIRECT3DCUBETEXTURE9(void)>)[&]()->auto { return createTextureCube(key); });
}

patternMesh * resourceManager::getPatternMesh(const string & key, void * makeParam, bool isAutoCreate)
{
	return getSomething(key, _mPatternMesh, isAutoCreate, (function<patternMesh*(void)>)[&]()->auto { return createPatternMesh(key, makeParam); });
}

patternMesh * resourceManager::getPatternMesh(const string & key)
{
	return getSomething(key, _mPatternMesh, false, (function<patternMesh*(void)>)nullptr);
}

template<typename T> 
T resourceManager::getSomething(const string & key, unordered_map<string, T> & table, bool isAutoCreate, function<T(void)> creater)
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