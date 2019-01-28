#include "gMng.h"

using namespace std;

template<typename tKey, typename tValue>
inline tValue gMng::add(tKey & key, tValue value, std::unordered_map<tKey, tValue>& container)
{
	auto iter = container.find(key);
	if (iter != container.end()) return iter->second;

	container.insert(unordered_map<tKey, tValue>::value_type(key, value));

	return value;
}

template<typename tValue>
inline tValue gMng::add(tValue & value, list<tValue>& container, PLACE place)
{
	auto iter = std::find(container.begin(), container.end(), value);
	if (iter != container.end()) return iter->second;

	switch (place)
	{
	case gMng::PLACE::FRONT: container.push_front(value); break;
	case gMng::PLACE::BACK:  container.push_back(value); break;
	}

	return value;
}

template<typename tValue>
inline tValue gMng::add(tValue & value, std::vector<tValue>& container, PLACE place)
{
	auto iter = std::find(container.begin(), container.end(), value);
	if (iter != container.end()) return iter->second;

	switch (place)
	{
	case gMng::PLACE::FRONT: container.push_front(value); break;
	case gMng::PLACE::BACK:  container.push_back(value); break;
	}

	return value;
}

template<typename tValue>
inline tValue gMng::add(tValue & value, dbList<tValue>& container, PLACE place)
{
	auto iter = container.find(value);
	if (iter != NULL) return iter->value;

	switch (place)
	{
	case gMng::PLACE::FRONT: container.push_front(value); break;
	case gMng::PLACE::BACK:  container.push_back(value); break;
	}

	return value;
}

template<typename tKey, typename tValue>
inline tValue gMng::find(tKey & key, std::unordered_map<tKey, tValue>& container)
{
	auto iter = container.find(key);
	if (iter == container.end()) return NULL;

	return iter->second;
}

template<typename tValue>
inline tValue gMng::find(tValue & key, std::list<tValue>& container, PLACE place)
{
	list<tValue>::iterator iter;
	switch (place)
	{
	case gMng::PLACE::FRONT: iter = std::find(container.begin(), container.end(), key); break;
	case gMng::PLACE::BACK: iter = std::find_end(container.begin(), container.end(), key); break;
	}
	if (iter == container.end()) return NULL;

	return *iter;
}

template<typename tValue>
inline tValue gMng::find(tValue & key, std::vector<tValue>& container, PLACE place)
{
	vector<tValue>::iterator iter;
	switch (place)
	{
	case gMng::PLACE::FRONT: iter = std::find(container.begin(), container.end(), key); break;
	case gMng::PLACE::BACK: iter = std::find_end(container.begin(), container.end(), key); break;
	}
	if (iter == container.end()) return NULL;

	return *iter;
}

template<typename tValue>
inline tValue gMng::find(tValue & key, dbList<tValue>& container, PLACE place)
{
	dbList<tValue>::node iter;
	switch (place)
	{
	case gMng::PLACE::FRONT: iter = container.find(key, dbList<tValue>::runDirection::FORWARD); break;
	case gMng::PLACE::BACK: iter = container.find(key, dbList<tValue>::runDirection::REVERSE); break;
	}
	if (iter == NULL) return NULL;

	return iter->value;
}

template<typename tKey, typename tValue>
inline bool gMng::findif(tKey & key, std::unordered_map<tKey, tValue>& container, const std::function<void(tValue found)>& callback)
{
	auto foundValue = find(key, container);
	if (foundValue != NULL)
	{
		callback(foundValue);
		return true;
	}
	return false;
}

template<typename tValue>
inline bool gMng::findif(tValue & key, std::list<tValue>& container, const std::function<void(tValue found)>& callback, PLACE place)
{
	auto foundValue = find(key, container, place);
	if (foundValue != NULL)
	{
		callback(foundValue);
		return true;
	}
	return false;
}

template<typename tValue>
inline bool gMng::findif(tValue & key, std::vector<tValue>& container, const std::function<void(tValue found)>& callback, PLACE place)
{
	auto foundValue = find(key, container, place);
	if (foundValue != NULL)
	{
		callback(foundValue);
		return true;
	}
	return false;
}

template<typename tValue>
inline bool gMng::findif(tValue & key, dbList<tValue>& container, const std::function<void(tValue found)>& callback, PLACE place)
{
	auto foundValue = find(key, container, place);
	if (foundValue != NULL)
	{
		callback(foundValue);
		return true;
	}
	return false;
}
