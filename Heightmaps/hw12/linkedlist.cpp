#include <iostream>
#include <string>
#include "linkedlist.h"
using namespace std;

LinkedList::LinkedList() : head(nullptr), tail(nullptr) {
}

LinkedList::~LinkedList() {
	clear();
}

LinkedList::LinkedList(const LinkedList& source) {
	// Implement this function
}

LinkedList& LinkedList::operator=(const LinkedList& source) {
	// Implement this function
	LinkedList* list = new LinkedList();
	Node *temp = source.head;
	while (temp != source.tail)
	{
		list->insert(temp->location,temp->year,temp->month,temp->temper);
		temp = temp->next;
	}
	return *(list);
}

void LinkedList::insert(int location, int year, int month, double temperature) {
	Node* n = new Node(location, year, month, temperature);
	if (head = nullptr) {
		head = n;
		tail = n;
	}
	else {
		n->next = head;
		head = n;
	}
}

void LinkedList::clear() {
	Node* pDel = head;
	while (pDel != NULL) {
		head = head->next;
		delete pDel;
		pDel = head;
	}
	head = NULL;
	tail = NULL;
}

void LinkedList::print() const {
	/* Do not modify this function */
	print(cout);
}

void LinkedList::print(ostream& os) const {
	/* Do not modify this function */
	os << *this;
}

ostream& operator<<(ostream& os, const LinkedList& ll) {
	// Implement this function
	Node* temp = ll.head;
	while (temp != ll.tail) {
		os << temp->location << " " << temp->year << " " << temp->month << " " << temp->temper << '\n';
		temp = temp->next;
	}
	return os;
}