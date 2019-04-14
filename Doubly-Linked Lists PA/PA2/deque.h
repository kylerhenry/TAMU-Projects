#ifndef DEQUE_H
#define DEQUE_H

#include <exception>
#include "node.h"

using namespace std;

//implements a deque 
template <class Type>
class Deque
{
private:
	node<Type> *Head;
	node<Type> *Tail;
	int currentSize;

public:
	Deque() {
		//constructor
		Head = NULL;
		Tail = NULL;
		currentSize = 0;
	}

	~Deque() {
		//destructor
		node<Type> *badNode = Head;
		while (badNode != NULL) {
			node<Type> *temp = badNode;
			badNode = badNode->next;
			temp->next = NULL;
			delete temp;
			Head = badNode;
		}
	}

	bool isEmpty() {
		//determines if deque is empty
		if (currentSize == 0) {
			return(1);
		}
		return(0);
	}

	int size() {
		//returns current size of deque
		return currentSize;
	}

	Type first() {
		//returns first (head) element in deque
		//throw exception if empty
		if (Head != NULL) {
			return Head->data;
		}
		throw std::out_of_range("No elements in deque!");
		return 1;
	}

	Type last() {
		//returns the last (tail) element of deque
		//throw exception if empty
		if (Tail != NULL) {
			return Tail->data;
		}
		throw std::out_of_range("No elements in deque!");
		return 1;
	}

	void insertFirst(Type o) {
		//inserts new element at head with appropriate pointers
		node<Type> *newNode;
		newNode = new node<Type>;
		newNode->data = o;
		newNode->next = Head;
		newNode->prev = NULL;
		if (size() == 0) {
			//if there is the first element to be added, head and tail must both point to that element
			Head = newNode;
			Tail = newNode;
			currentSize++;
		}
		else {
			Head->prev = newNode;
			Head = newNode;
			currentSize++;
		}
	}

	void insertLast(Type o) {
		//inserts new element at tail with appropriate pointers
		node<Type> *newNode;
		newNode = new node<Type>;
		newNode->data = o;
		newNode->next = NULL;
		newNode->prev = Tail;
		if (size() == 0) {
			//if there is the first element to be added, head and tail must both point to that element
			Tail = newNode;
			Head = newNode;
			currentSize++;
		}
		else {
			Tail->next = newNode;
			Tail = newNode;
			currentSize++;
		}
	}

	Type removeFirst() {
		//remove first element (value at head) and return it, and move the head pointer to the next element in the deque
		//throw exception if empty
		if (size() == 0) {
			throw std::out_of_range("No elements in deque!");
			return 1;
		}
		node<Type> *temp = Head;
		Type returnData = temp->data;
		Head = Head->next;
		delete temp;
		if (size() == 1) {
			//have to add this to ensure tail is equal to NULL in the case there are no elements left in the deque
			//otherwiese tail would be left pointing to an de-allocated memory location
			Tail = NULL;
			currentSize--;
			return returnData;
		}
		Head->prev = NULL;
		currentSize--;
		return returnData;
	}

	Type removeLast() {
		//remove last element (value at tail) and return it, and move tail pointed to previous element in deque
		//thow excpetion if empty
		if (size() == 0) {
			throw std::out_of_range("No elements in deque!");
			return 1;
		}
		node<Type> *temp = Tail;
		Type returnData = temp->data;
		Tail = Tail->prev;
		delete temp;
		if (size() == 1) {
			//have to add this to ensure head is equal to NULL in the case there are no elements left in the deque
			//otherwiese head would be left pointing to an de-allocated memory location
			Head = NULL;
			currentSize--;
			return returnData;
		}
		Tail->next = NULL;
		currentSize--;
		return returnData;
	}
};

#endif