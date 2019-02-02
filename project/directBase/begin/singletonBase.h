#pragma once

#define SINGLE(singleton) (singleton::getInstance())

template<typename T>
class singletonBase
{
private :
	static T* _instance;

public :
	static T* getInstance(void)
	{
		if (!_instance)
			_instance = new T;

		return _instance;
	}

protected :
	singletonBase() {};
	~singletonBase() 
	{
		if (_instance)
			delete _instance;
	};
};

template<typename T>
T* singletonBase<T>::_instance = nullptr;
