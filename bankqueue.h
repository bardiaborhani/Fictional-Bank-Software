/*
This a a linked-queue that functions in a first in, first out manner.

*/
#pragma once
#ifndef bankqueue_h
#define bankqueue_h

#include <exception>
#include <stdexcept>

using namespace std;

template<typename Object>
class BankQueue {

private:

	struct Node {        	// the node in a linked list
		Object* data;          	// pointer to actual data
		Node* next;
	};

	Node* head;

public:

	BankQueue(void);
	~BankQueue(void);
	Node* pop(void);
	void push(Object* toAdd);
	bool isEmpty(void) const;
	void makeEmpty(void);
	void buildQueue(ifstream& inFile);
};

#endif // !bankqueue_h

/****************************
Default no args constructor
*****************************/
template<typename Object>
BankQueue<Object>::BankQueue(void)
{
	head = NULL;
};
/*****************************
Destructor. Calls makeEmpty()
*****************************/
template<typename Object>
BankQueue<Object>::~BankQueue(void)
{
	makeEmpty();
};

/********************************************
Adds a transaction object to the queue. Adds
all new nodes to the end of the list.
*********************************************/
template<typename Object>
void BankQueue<Object>::push(Object* toAdd)
{
	if (toAdd == NULL) { // Error check if object is null
		return;
	}
	if (head == NULL) { // First condition, empty list
		head = new Node(toAdd, NULL);
	}
	else {
		Node* current = head; // Second condition, list of size one

		while (current->next != NULL) { // Traverse to end of list
			current = current->next;
		}
		current->next = new Node(toAdd, NULL); // Add to end of list
	}
};

/**************************************************
Removes a object from the list. Preforms this in a 
first in, first out manner.
**************************************************/
template<typename Object>
BankQueue<Object>::Node* BankQueue<Object>::pop(void)
{
	if (head == NULL) { // Error check, list is empty
		throw new runtime_error("Empty List!"); // Throw exception
		return;
	}
	Node* retNode = head; // Return value
	head = head->next; // Move pointer
	return retNode; // Returns first node on the list
};

/*******************************************
Deletes everything within the list. Clears
all data.
*******************************************/
template<typename Object>
void BankQueue<Object>::makeEmpty(void)
{
	Node* toDelete; // Temp node for deletion

	while (head != NULL) { // Traverse the list
		toDelete = head; // Prepares to delete head
		head = head->next; // Moves the pointer
		delete toDelete; // Deletes head
	}
	head = NULL; // Removes head's pointer
};

/**********************************
Returns true if our list is empty
***********************************/
template<typename Object>
bool BankQueue<Object>::isEmpty(void) const
{
	// If our head is null, then the list is empty
	// Returns true if head is null
	return head == NULL; 
};

/************************************************************************
Preconditions: Assumes that the filestream data is properly 
formatted.
Note: It is the responsibility of the object to properly handle 
the filestream.
Takes in a filestream as a parameter. Creates a new object type.
Passes the filesteam to the object if the object can succesfully 
set the data. Then the object is push on to the queue.  If the read is 
successful then the data is added to the queue by calling
setData().
************************************************************************/
template<typename Object>
void BankQueue<Object>::buildQueue(ifstream& inFile)
{
	Object* ptr; 
	bool successfulRead;
	bool success;
	for (;;) { // Infite loop
		ptr = new Object;
		successfulRead = ptr->setData(inFile); // If succuess, set data
		if (inFile.eof()) { // If end of file, delte ptr, break out of loop
			delete ptr;
			break;
		}

		if (successfulRead) { // If good read, push ptr
			success = push(ptr);
		}
		else {
			delete ptr; // Not successfull, delete ptr
		}
		if (!success) break; // If not success, break out.
	}
};
