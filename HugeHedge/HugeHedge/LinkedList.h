//	LinkedList.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-18

////////////////////////////////////////////////////////////////////////////////
/*	LinkedList class
	Basic implementation of a linked list, using a template.
	Works with any class that overloads the <, ==, and << operators.

	* Bool type conversion for whether the list contains any items.
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

template <class T>
class ListNode {
public:
	T data;
	ListNode<T>* next;
	ListNode(T& d) { data = d; next = nullptr; }
};

template <class T>
class LinkedList {
private:
	ListNode<T>* head;
	void clear();

public:
	LinkedList() { head = nullptr; }
	~LinkedList() { clear(); }
	bool empty() const { return !head; }
	bool contains(const T& data) const;
	void insert(T& data);
	void remove(T& data);
	void steal(LinkedList<T>& list);
	void print(std::ostream& os = std::cout);
	operator bool();
};

////////////////////////////////////////////////////////////////////////////////
/*	clear()
	Removes all nodes from the list.
*/
////////////////////////////////////////////////////////////////////////////////
template <class T>
void LinkedList<T>::clear() {
	ListNode<T>* curNode = head;
	ListNode<T>* nextNode = nullptr;

	// Until we reach the end of the list, delete the current node
	// and then move on to the next.
	while( curNode ) {
		nextNode = curNode->next;
		delete curNode;
		curNode = nextNode;
	}
	// List is empty, head points to nothing.
	head = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
/*	contains()
	Returns true if the list contains the item being checked.
*/
////////////////////////////////////////////////////////////////////////////////
template <class T>
bool LinkedList<T>::contains(const T& data) const {
	ListNode<T>* curNode = head;

	while( curNode ) {
		if( curNode->data == data )
			return true;
		curNode = curNode->next;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////
/*	insert()
	Adds a node with the given data into position in the list.
*/
////////////////////////////////////////////////////////////////////////////////
template <class T>
void LinkedList<T>::insert(T& data) {
	ListNode<T>* prevNode = nullptr;
	ListNode<T>* curNode = nullptr;
	ListNode<T>* newNode = new ListNode<T>(data);

	// Special case for if the list is currently empty.
	if( empty() ) {
		head = newNode;
		newNode->next = nullptr;
	}
	// Otherwise, we need to find where to insert the node.
	else {
		curNode = head;

		// Skip all nodes whose data is less than the search data.
		while( curNode && curNode->data < data ) {
			prevNode = curNode;
			curNode = curNode->next;
		}
		// Special case for if the new node is to be first in the list.
		if( !prevNode ) {
			head = newNode;
			newNode->next = nullptr;
		}
		// Otherwise, insert the data after the previous node.
		else {
			prevNode->next = newNode;
			newNode->next = curNode;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	remove()
	Removes a node with the given data from the list, if one is found.
*/
////////////////////////////////////////////////////////////////////////////////
template <class T>
void LinkedList<T>::remove(T& data) {
	ListNode<T>* prevNode = nullptr;
	ListNode<T>* curNode = nullptr;

	// If the list is empty, bail out.
	if( empty() )
		return;
	// Special case for if the search data is found in the first node.
	if( head->data == data ) {
		curNode = head->next;
		delete head;
		head = curNode;
	}
	// Otherwise, we need to find which node to delete.
	else {
		curNode = head;

		// Skip all nodes that don't match the search data.
		while( curNode && !(curNode->data == data) ) {
			prevNode = curNode;
			curNode = curNode->next;
		}
		// If we're not at the end of the list, we found the data.
		// Delete the node it's in.
		if( curNode ) {
			prevNode->next = curNode;
			delete curNode;
			curNode = nullptr;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	steal()
	Takes all the items from another linked list of the same type.
	Removes each item from the source list and adds it to this one.
*/
////////////////////////////////////////////////////////////////////////////////
template <class T>
void LinkedList<T>::steal(LinkedList<T>& list) {
	ListNode<T>* curNode = list.head;

	while( curNode ) {
		insert(curNode->data);
		list.remove(curNode->data);
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	print()
	Prints the contents of the list.
	- os: Any output stream
*/
////////////////////////////////////////////////////////////////////////////////
template <class T>
void LinkedList<T>::print(std::ostream& os) {
	ListNode<T>* curNode = head;

	while( curNode ) {
		os << '\t' << curNode->data << '\n';
		curNode = curNode->next;
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	bool type conversion
	Returns whether the list contains any items.
	(i.e. calls the empty() method)
*/
////////////////////////////////////////////////////////////////////////////////
template <class T>
LinkedList<T>::operator bool() {
	return empty();
}

#endif