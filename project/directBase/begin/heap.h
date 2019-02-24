#pragma once
#include "kGlobalDefine.h"

template<typename T, typename st_COMP = std::less<T>>
class heap
{
public :
	using container = std::vector<T>;

protected :
	container _vData;

public :
	T & top(void) { return _vData[1]; }
	typename container::iterator begin(void) { return _vData.begin() + 1; }
	typename container::iterator end(void) { return _vData.end(); }

	void push(T input);
	void pop(void);

	bool empty(void) { return _vData.size() <= 1; }

public :
	container & getContainer(void) { return _vData; }

protected :
	int parentIndex(int childIndex) { return childIndex / 2; }
	int childIndex(int parent, bool isLeft) { return (parent * 2) + (isLeft ? 0 : 1); }

	bool compare(T & value1, T & value2) { return st_COMP()(value1, value2); };

public:
	heap() { _vData.push_back(T()); };
	~heap() {};
};

template<typename T, typename st_COMP>
inline void heap<T, st_COMP>::push(T input)
{
	int index = _vData.size();
	_vData.push_back(input);

	bool comp = true;
	while (comp)
	{
		int indexParent = parentIndex(index);
		if (indexParent < 1)
			return;

		comp = compare(_vData[index], _vData[indexParent]);
		if (comp)
			std::swap(_vData[index], _vData[indexParent]);

		index = indexParent;
	}
}

template<typename T, typename st_COMP>
inline void heap<T, st_COMP>::pop(void)
{
	int maxIndex = _vData.size() - 1;

	std::swap(_vData[1], _vData[maxIndex]);
	_vData.pop_back();

	int index = 1;

	bool compL;
	bool compR;

	do
	{
		int preIndex = index;

		compL = false;
		compR = false;

		int indexL = childIndex(index, true);
		int indexR = childIndex(index, false);

		if (indexL < maxIndex) compL = compare(_vData[indexL], _vData[index]);
		if (indexR < maxIndex) compR = compare(_vData[indexR], _vData[index]);

		if (compL && compR)
			index = compare(_vData[indexL], _vData[indexR]) ? indexR : indexL;

		else if (compL)
			index = indexL;

		else if (compR)
			index = indexR;

		if (compL || compR)
			std::swap(_vData[index], _vData[preIndex]);

	} while (compL || compR);
}