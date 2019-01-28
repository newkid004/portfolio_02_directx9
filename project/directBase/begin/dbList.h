#pragma once
#include "kGlobalDefine.h"

template<typename T>
class dbList
{
public :
	enum class runDirection
	{
		FORWARD,
		REVERSE
	};

	struct node
	{
		node* prev = nullptr;
		node* next = nullptr;

		T value;
	};

private:
	int _size = 0;
	node** _head = nullptr;
	node** _tail = nullptr;

public :
	T front(void);
	T back(void);
	node* begin(void);
	node* end(void);
	void push_front(T input);
	void push_back(T input);

	void run(bool* runner, const std::function<void(T found, node *& curNode)> & callback, runDirection runDir = runDirection::FORWARD);
	node* find(T input, runDirection runDir = runDirection::FORWARD);
	bool findif(T input, const std::function<void(T found, node *& curNode)> & callback, runDirection runDir = runDirection::FORWARD);

	node* erase(node* input);
	node* erase(T input);
	void clear(void);

	int size(void) { return _size; }
	bool empty(void) { return _size == 0; };

private :
	node*& head(void) { return *_head; }
	node*& tail(void) { return *_tail; }
	void insert(node* prev, node* next, node* input);

public:
	dbList(void);
	virtual ~dbList(void);
};

#include "dbList.hpp"