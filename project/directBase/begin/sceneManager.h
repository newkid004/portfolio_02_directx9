#pragma once
#include "kGlobalDefine.h"

class sceneBase;

class sceneManager
{
private :
	typedef sceneBase* SCENE;
	typedef std::unordered_map<std::string, SCENE> SCENE_CONTAINER;

private :
	SCENE_CONTAINER _mSceneList;
	SCENE _mainGame = nullptr;
	SCENE _currentScene = nullptr;

public:
	void update(void);
	void draw(void);
	void drawUI(void);

public :
	SCENE add(const std::string & key, SCENE input);
	SCENE get(const std::string & key);
	SCENE change(SCENE scene);
	SCENE change(const std::string & key);

public :
	SCENE & getCurrentScene(void) { return _currentScene; }

public :
	DECLARE_SINGLETON(sceneManager);

public:
	sceneManager() {};
	virtual ~sceneManager();
};

