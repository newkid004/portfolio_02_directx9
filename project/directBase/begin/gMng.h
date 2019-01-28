#pragma once
#include "kGlobalDefine.h"
#include "dbList.h"

class gMng
{
public :
	enum class PLACE
	{
		FRONT,
		BACK
	};

public :	// add
	template<typename tKey, typename tValue>
	static tValue add(tKey & key, tValue value, std::unordered_map<tKey, tValue> & container);
	template<typename tValue> 
	static tValue add(tValue & value, std::list<tValue> & container, PLACE place = PLACE::BACK);
	template<typename tValue>
	static tValue add(tValue & value, std::vector<tValue> & container, PLACE place = PLACE::BACK);
	template<typename tValue>
	static tValue add(tValue & value, dbList<tValue> & container, PLACE place = PLACE::BACK);

public :	// find
	template<typename tKey, typename tValue>
	static tValue find(tKey & key, std::unordered_map<tKey, tValue> & container);
	template<typename tValue>
	static tValue find(tValue & key, std::list<tValue> & container, PLACE place = PLACE::FRONT);
	template<typename tValue>
	static tValue find(tValue & key, std::vector<tValue> & container, PLACE place = PLACE::FRONT);
	template<typename tValue>
	static tValue find(tValue & key, dbList<tValue> & container, PLACE place = PLACE::FRONT);

public :	// findIf
	template<typename tKey, typename tValue>
	static bool findif(tKey & key, std::unordered_map<tKey, tValue> & container, const std::function<void(tValue found)> & callback);
	template<typename tValue>
	static bool findif(tValue & key, std::list<tValue> & container, const std::function<void(tValue found)> & callback, PLACE place = PLACE::FRONT);
	template<typename tValue>
	static bool findif(tValue & key, std::vector<tValue> & container, const std::function<void(tValue found)> & callback, PLACE place = PLACE::FRONT);
	template<typename tValue>
	static bool findif(tValue & key, dbList<tValue> & container, const std::function<void(tValue found)> & callback, PLACE place = PLACE::FRONT);

private :
	gMng() {};
	~gMng() {};
};

#include "gMng.inl"
