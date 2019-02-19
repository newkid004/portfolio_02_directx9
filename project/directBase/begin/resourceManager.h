#pragma once
#include "kGlobalDefine.h"

using namespace std;

class sound;
class skinnedMesh;

class resourceManager
{
private :
	unordered_map<string, LPD3DXEFFECT> _mEffect;
	unordered_map<string, LPDIRECT3DTEXTURE9> _mTexture;
	unordered_map<string, meshSet*> _mStaticMesh;
	unordered_map<string, skinnedMesh*> _mSkinnedMesh;
	unordered_map<string, sound*> _mSound;
	unordered_map<string, LPDIRECT3DCUBETEXTURE9> _mTextureCube;

public :
	// ----- create ----- //
	meshSet*				createStaticMesh(const string & filePath);
	skinnedMesh*			createSkinnedMesh(const string & filePath, void* makeParam);
	LPD3DXEFFECT			createEffect(const string & key);
	LPDIRECT3DTEXTURE9		createTexture(const string & key);
	LPDIRECT3DTEXTURE9		createSpriteTexture(const string & key);
	sound*					createSound(const string & key, bool isBGM = true);
	LPDIRECT3DCUBETEXTURE9	createTextureCube(const string & key);

public :
	// ----- add ----- //
	meshSet*				addStaticMesh(const string & key, meshSet* value)					{ return addSomthing(key, value, _mStaticMesh); }
	skinnedMesh*			addSkinnedMesh(const string & key, skinnedMesh* value)				{ return addSomthing(key, value, _mSkinnedMesh); }
	LPD3DXEFFECT			addEffect(const string & key, LPD3DXEFFECT value)					{ return addSomthing(key, value, _mEffect); }
	LPDIRECT3DTEXTURE9		addTexture(const string & key, LPDIRECT3DTEXTURE9 value)			{ return addSomthing(key, value, _mTexture); }
	LPDIRECT3DTEXTURE9		addSpriteTexture(const string & key, LPDIRECT3DTEXTURE9 value)		{ return addSomthing(key, value, _mTexture); }
	sound*					addSound(const string & key, sound* value)							{ return addSomthing(key, value, _mSound); }
	LPDIRECT3DCUBETEXTURE9	addTextureCube(const string & key, LPDIRECT3DCUBETEXTURE9 value)	{ return addSomthing(key, value, _mTextureCube); }

	template<typename T> T	addSomthing(const string & key, T value, unordered_map<string, T> & table);

public :
	// ----- get ----- //
	meshSet*				getStaticMesh(const string & key, bool isAutoCreate = true);
	skinnedMesh*			getSkinnedMesh(const string & key, void* makeParam, bool isAutoCreate = true);
	skinnedMesh*			getSkinnedMesh(const string & key);
	LPD3DXEFFECT			getEffect(const string & key, bool isAutoCreate = true);
	LPDIRECT3DTEXTURE9		getTexture(const string & key, bool isAutoCreate = true);
	LPDIRECT3DTEXTURE9		getSpriteTexture(const string & key, bool isAutoCreate = true);
	sound*					getSoundBGM(const string & key, bool isAutoCreate = true);
	sound*					getSoundSE(const string & key, bool isAutoCreate = true);
	LPDIRECT3DCUBETEXTURE9	getTextureCube(const string & key, bool isAutoCreate = true);

	template<typename T> T	getSomthing(const string & key, unordered_map<string, T> & table, bool isAutoCreate, function<T(void)> creater);

public :	// ----- ΩÃ±€≈Ê ----- //
	DECLARE_SINGLETON(resourceManager);

private :
	resourceManager();
	virtual ~resourceManager();
};

