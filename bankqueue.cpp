

#include "bankqueue.h"


/*****************************
Destructor. Calls makeEmpty()
*****************************/
BankQueue::~BankQueue(void)
{
	makeEmpty();
};

/********************************************
Adds a Transaction to the queue. Adds
all new nodes to the end of the list.
*********************************************/
void BankQueue::push(Transaction* toAdd)
{
	if (toAdd == nullptr) { // Error check if Transaction is null
		return;
	}
	if (head == nullptr) { // First condition, empty list
		head = new Node(toAdd, nullptr);
	}
	else {
		Node* current = head; // Second condition, list of size one

		while (current->next != nullptr) { // Traverse to end of list
			current = current->next;
		}
		current->next = new Node(toAdd, nullptr); // Add to end of list
	}
};

/**************************************************
Removes a Transaction from the list. Preforms this in a
first in, first out manner.
**************************************************/
void BankQueue::pop()
{
	Node* store = head;

	if (store != nullptr) {
		head = head->next;
		delete store;
	}
};


Transaction BankQueue::top() const
{
	Transaction store;
	if (head != nullptr) {
		store = *head->data;
	}
	return store;
};

/*******************************************
Deletes everything within the list. Clears
all data.
*******************************************/
void BankQueue::makeEmpty(void)
{
	Node* store; // Temp node for deletion

	while (head != nullptr) { // Traverse the list
		store = head; // Prepares to delete head
		head = head->next; // Moves the pointer
		delete store->data;
		delete store; // Deletes head
	}
	head = nullptr; // Removes head's pointer
};

/**********************************
Returns true if our list is empty
***********************************/
bool BankQueue::isEmpty(void) const
{
	// If our head is null, then the list is empty
	// Returns true if head is null
	return head == nullptr;
};

/************************************************************************
Preconditions: Assumes that the filestream data is properly
formatted.
Note: It is the responsibility of the Transaction to properly handle
the filestream.
Takes in a filestream as a parameter. Creates a new Transaction type.
Passes the filesteam to the Transaction if the Transaction can succesfully
set the data. Then the Transaction is push on to the queue.  If the read is
successful then the data is added to the queue by calling
setData().
************************************************************************/
bool BankQueue::buildQueue(ifstream& inFile)
{
	Transaction* newTransaction;  // make it a pointer or not a pointer?

	string store;

	if (inFile.is_open()) { //make sure the file is open
		while (getline(inFile, store)) { //getline() from STL reads characters from an input stream and places them into a the store 
			newTransaction = new Transaction();
			if (newTransaction->setData(store)) {
				push(newTransaction);
			}
			else {
				return false;
			}

			if (inFile.eof()) {
				break; //if we reach the eof finish the while
			}
		}
	}
	else {
		cerr << "unable to open the transactions file" << endl;
		exit(-1);
	}

	return true;
};