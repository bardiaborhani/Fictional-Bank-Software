/*------------------------------------------------------------------------------------------------

The BankQueue class is a linked list styled object (in the way it has nodes and each node connects to the next node)
that stores all the transaction objects. This class relies on the bankmanager class to call the 
readTransactions function that intakes a file stream and passes it onto the buildQueue function in this class - this creates the BankQueue
This class is used to organize and store the transactions in order so that they can be popped off in FIFO order
so that they can be read by the transact function the in the bankManager class

------------------------------------------------------------------------------------------------*/

#ifndef BANKQUEUE_H
#define BANKQUEUE_H

#include <exception> 
#include <stdexcept>

#include "transaction.h"

using namespace std;

class BankQueue {

	struct Node {        	// the node in a linked list
		Transaction* data;          	// pointer to actual data
		Node* next;	// pointer to the next node (the node that holds the next transaction)

		Node(Transaction* d, Node* n) : data(d), next(n) {}

		Node() {
			data = nullptr;
			next = nullptr;
		}
	};

private:

	Node* head = nullptr;

public:

	~BankQueue();	// deletes the bankQueue

	void pop();	// takes off the newest node in the list
	Transaction top() const;	// looks at the top most node in the list

	void push(Transaction* toAdd); //adds a Transaction to the BankQueue

	bool isEmpty() const;	//checks if the BankQueue is empty (if therre are no transactions)
	void makeEmpty();	// empties the BankQueue

	bool buildQueue(ifstream& inFile);	// Builds the BankQueue using the ifstream that reads the command data file
};

#endif // !BANKQUEUE
