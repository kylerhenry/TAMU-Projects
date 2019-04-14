#ifndef NODE_H
#define NODE_H

using namespace std;

//defines the "node" data stucture for use ina doubly linked list
template <class Type>
struct node {
		Type data;
		node *next;
		node *prev;
};


#endif