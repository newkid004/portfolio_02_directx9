#include "aStar_grape_bind.h"

#include "aStar_node.h"

template<typename T>
inline void aStar_grape_bind<T>::addNode(aStar_node * input, BIND ** out_bind)
{
	aStar_grape::addNode(input);
	_vBindList.push_back(nullptr);

	*out_bind = _vBindList.back();
}

template<typename T>
inline bool aStar_grape_bind<T>::deleteNode(aStar_node * input)
{
	int index = input->getIndex();

	if (aStar_grape::deleteNode(input))
	{
		_vBindList.erase(_vBindList.begin() + index);
		return true;
	}
	return false;
}

template<typename T>
inline bool aStar_grape_bind<T>::deleteNode(int index)
{
	if (aStar_grape::deleteNode(index))
	{
		_vBindList.erase(_vBindList.begin() + index);
		return true;
	}
	return false;
}
