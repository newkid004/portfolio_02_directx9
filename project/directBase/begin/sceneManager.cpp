#include "sceneManager.h"

#include "mainGame.h"

sceneManager::~sceneManager()
{
	for (auto iter : _mSceneList)
		SAFE_DELETE(iter.second);
}

void sceneManager::update(void)
{
	if (_currentScene != nullptr) _currentScene->update();
}

void sceneManager::draw(void)
{
	if (_currentScene != nullptr) _currentScene->draw();
}

void sceneManager::drawUI(void)
{
	if (_currentScene != nullptr) _currentScene->drawUI();
}

sceneManager::SCENE sceneManager::add(const std::string & key, SCENE input)
{
	auto s = get(key);
	if (s != nullptr) return s;

	input->init();
	_mSceneList.insert(SCENE_CONTAINER::value_type(key, input));

	return input;
}

sceneManager::SCENE sceneManager::get(const std::string & key)
{
	auto iter = _mSceneList.find(key);
	if (iter != _mSceneList.end()) return iter->second;

	return nullptr;
}

sceneManager::SCENE sceneManager::change(SCENE scene)
{
	if (scene == nullptr) 
		return nullptr;

	return _currentScene = scene;;
}

sceneManager::SCENE sceneManager::change(const std::string & key)
{
	return change(get(key));
}
