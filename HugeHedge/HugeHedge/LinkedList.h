//	LinkedList.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-14

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

////////////////////////////////////////////////////////////////////////////////
/*	LinkedList class
	Basic implementation of a linked list, using a template.
	Works with any class that overloads the <, !=, and << operators.
*/
////////////////////////////////////////////////////////////////////////////////

template <class T>
class ListNode {
public:
	T data;
	ListNode<T>* next;
	ListNode(T d) { data = d; next = nullptr; }
};

template <class T>
class LinkedList {
private:
	ListNode<T>* head;
public:
	LinkedList() { head = nullptr; }
	~LinkedList();
	bool empty() const { return !head; }
	void insert(const T& data);
	void remove(const T& data);
	void clear();
	void print(std::ostream& os = std::cout);
};

#endif