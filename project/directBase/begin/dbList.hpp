#pragma once
#include "kGlobalDefine.h"
#include "dbList.h"

#define SAFE_DELETE(TARGET)				if((TARGET) != nullptr) { delete (TARGET); (TARGET) = NULL; }

template<typename T>
inline dbList<T>::dbList(void)
{
	node* beginNode = nullptr;

	beginNode = new node();
	_head = &beginNode;

	beginNode = new node();
	_tail = &beginNode;

	head()->next = *_tail;
	tail()->prev = *_head;
}

template<typename T>
inline dbList<T>::~dbList(void)
{
	this->clear();

	SAFE_DELETE(head());
	SAFE_DELETE(tail());
}

template<typename T>
inline T dbList<T>::front(void)
{
	return head()->next->value;
}

template<typename T>
inline T dbList<T>::back(void)
{
	return tail()->prev->value;
}

template<typename T>
inline typename dbList<T>::node * dbList<T>::begin(void)
{
	return head()->next;
}

template<typename T>
inline typename dbList<T>::node * dbList<T>::end(void)
{
	return tail()->prev;
}

template<typename T>
inline void dbList<T>::push_front(T input)
{
	node* inNode = new node;

	this->insert(head(), begin(), inNode);
	inNode->value = input;

	++_size;
}

template<typename T>
inline void dbList<T>::push_back(T input)
{
	node* inNode = new node;

	this->insert(end(), tail(), inNode);
	inNode->value = input;

	++_size;
}

template<typename T>
inline void dbList<T>::run(bool * runner, const std::function<void(T found, node *& curNode)>& callback, runDirection runDir)
{
	node* endNode;
	node* ownNode;

	switch (runDir)
	{
		case runDirection::FORWARD : { ownNode = begin();	endNode = tail(); }; break;
		case runDirection::REVERSE : { ownNode = end();		endNode = head(); }; break;
	}

	while (ownNode != endNode)
	{
		callback(ownNode->value, ownNode);

		if (!(*runner))
			break;

		switch (runDir)
		{
			case runDirection::FORWARD : ownNode = ownNode->next; break;
			case runDirection::REVERSE : ownNode = ownNode->prev; break;
		}
	}
}

template<typename T>
inline typename dbList<T>::node * dbList<T>::find(T input, runDirection runDir)
{
	node* fNode = NULL;

	this->findif(input, [&](T found, node *& curNode)->void {
		fNode = curNode;
	}, runDir);

	return fNode;
}

template<typename T>
inline bool dbList<T>::findif(T input, const std::function<void(T found, node *& curNode)>& callback, runDirection runDir)
{
	bool isFound = false;
	bool runner = true;

	this->run(&runner, [&](T found, node*& curNode)->void {
		if (input == found)
		{
			callback(found, curNode);
			runner = false;
			isFound = true;
		}
	}, runDir);

	return isFound;
}

template<typename T>
inline typename dbList<T>::node * dbList<T>::erase(node * input)
{
	node* nextNode = input->prev->next = input->next;
	input->next->prev = input->prev;

	SAFE_DELETE(input);
	--_size;

	return nextNode;
}

template<typename T>
inline typename dbList<T>::node * dbList<T>::erase(T input)
{
	node* next = nullptr;

	findif(input, [&](T found, node* curNode)->void {
		next = erase(curNode);
	});

	return next;
}

template<typename T>
inline void dbList<T>::clear(void)
{
	node* ownNode = head();

	while (ownNode->next != nullptr)
	{
		ownNode = ownNode->next;
		SAFE_DELETE(ownNode->prev);
	}
}

template<typename T>
void dbList<T>::insert(node * prev, node * next, node * input)
{
	prev->next = input;

	input->prev = prev;
	input->next = next;

	next->prev = input;
}
