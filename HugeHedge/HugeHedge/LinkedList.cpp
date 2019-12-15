//	LinkedList.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-14

#include "LinkedList.h"

////////////////////////////////////////////////////////////////////////////////
/*	Destructor
*/
////////////////////////////////////////////////////////////////////////////////
template <class T>
LinkedList<T>::~LinkedList() {
	clear();
}

////////////////////////////////////////////////////////////////////////////////
/*	insert()
	Adds a node with the given data into position in the list.
*/
////////////////////////////////////////////////////////////////////////////////
template <class T>
void LinkedList<T>::insert(const T& data) {
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
void LinkedList<T>::remove(const T& data) {
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
		while( curNode && curNode->data != data ) {
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