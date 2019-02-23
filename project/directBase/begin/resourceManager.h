#pragma once
#include "kGlobalDefine.h"

using namespace std;

class skinnedMesh;
class patternMesh;

class resourceManager
{
private :
	template<typename T>
	using strMap = std::unordered_map<std::string, T>;

private :
	strMap<LPD3DXEFFECT>			_mEffect;
	strMap<LPDIRECT3DTEXTURE9>		_mTexture;
	strMap<meshSet*>				_mStaticMesh;
	strMap<skinnedMesh*>			_mSkinnedMesh;
	strMap<LPDIRECT3DCUBETEXTURE9>	_mTextureCube;
	strMap<patternMesh*>			_mPatternMesh;

public :
	// ----- create ----- //
	meshSet*				createStaticMesh(const string & filePath);
	skinnedMesh*			createSkinnedMesh(const string & filePath, void* makeParam);
	LPD3DXEFFECT			createEffect(const string & key);
	LPDIRECT3DTEXTURE9		createTexture(const string & key);
	LPDIRECT3DTEXTURE9		createSpriteTexture(const string & key);
	LPDIRECT3DCUBETEXTURE9	createTextureCube(const string & key);
	patternMesh*			createPatternMesh(const string & key, void* makeParam);

public :
	// ----- add ----- //
	meshSet*				addStaticMesh(const string & key, meshSet* value)					{ return addSomthing(key, value, _mStaticMesh); }
	skinnedMesh*			addSkinnedMesh(const string & key, skinnedMesh* value)				{ return addSomthing(key, value, _mSkinnedMesh); }
	LPD3DXEFFECT			addEffect(const string & key, LPD3DXEFFECT value)					{ return addSomthing(key, value, _mEffect); }
	LPDIRECT3DTEXTURE9		addTexture(const string & key, LPDIRECT3DTEXTURE9 value)			{ return addSomthing(key, value, _mTexture); }
	LPDIRECT3DTEXTURE9		addSpriteTexture(const string & key, LPDIRECT3DTEXTURE9 value)		{ return addSomthing(key, value, _mTexture); }
	LPDIRECT3DCUBETEXTURE9	addTextureCube(const string & key, LPDIRECT3DCUBETEXTURE9 value)	{ return addSomthing(key, value, _mTextureCube); }
	patternMesh*			addPatternMesh(const string & key, patternMesh* value)				{ return addSomthing(key, value, _mPatternMesh); }

private :
	template<typename T> T	addSomthing(const string & key, T value, unordered_map<string, T> & table);

public :
	// ----- get ----- //
	meshSet*				getStaticMesh(const string & key, bool isAutoCreate = true);
	skinnedMesh*			getSkinnedMesh(const string & key, void* makeParam, bool isAutoCreate = true);
	skinnedMesh*			getSkinnedMesh(const string & key);
	LPD3DXEFFECT			getEffect(const string & key, bool isAutoCreate = true);
	LPDIRECT3DTEXTURE9		getTexture(const string & key, bool isAutoCreate = true);
	LPDIRECT3DTEXTURE9		getSpriteTexture(const string & key, bool isAutoCreate = true);
	LPDIRECT3DCUBETEXTURE9	getTextureCube(const string & key, bool isAutoCreate = true);
	patternMesh*			getPatternMesh(const string & key, void* makeParam, bool isAutoCreate = true);
	patternMesh*			getPatternMesh(const string & key);

private :
	template<typename T> T	getSomething(const string & key, unordered_map<string, T> & table, bool isAutoCreate, function<T(void)> creater);

public :	// ----- ΩÃ±€≈Ê ----- //
	DECLARE_SINGLETON(resourceManager);

private :
	resourceManager();
	virtual ~resourceManager();
};

