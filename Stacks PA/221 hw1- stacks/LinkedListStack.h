#ifndef LINKED_LIST_STACK_H
#define LINKED_LIST_STACK_H
#include "Node.h"


template <class Type>
class LinkedListStack
{
private:
	node<Type> *top;

public:
	//constuctor
	LinkedListStack() {
		top = NULL;
	}
	//checks if stack is empty
	bool isEmpty() const {
		return top == NULL;
	}
	//finds current size of stack (number of elements)
	int size() {
		if (isEmpty) {
			cout << "Stack empty." << endl;
		}
		else {
			return(++top);
		}
	}
	//pops element off stack
	Type pop() {
		if (isEmpty()) {
			cout << "Nothing to pop; stack empty." << endl;
		}
		else {
			node<Type> *current = top;
			Type element = current->data;
			top = top->link;
			delete current;

			return element;
			}
	}
	//pushes element onto stack
	void push(Type e) {
		node<Type> *newNode;
		newNode = new node<Type>;
		newNode->data = e;
		newNode->link = top;
		top = newNode;
	}
};

#endif