/*
This a a linked-queue that functions in a first in, first out manner.

*/
#ifndef BANKQUEUE_H
#define BANKQUEUE_H

#include <exception>
#include <stdexcept>

#include "transaction.h"

using namespace std;

class BankQueue {

	struct Node {        	// the node in a linked list
		Transaction* data;          	// pointer to actual data
		Node* next;

		Node(Transaction* d, Node* n) : data(d), next(n) {}

		Node() {
			data = nullptr;
			next = nullptr;
		}
	};

private:

	Node* head = nullptr;

public:

	~BankQueue();

	void pop();
	Transaction top() const;

	void push(Transaction* toAdd);

	bool isEmpty() const;
	void makeEmpty();

	bool buildQueue(ifstream& inFile);
};

#endif // !BANKQUEUE
