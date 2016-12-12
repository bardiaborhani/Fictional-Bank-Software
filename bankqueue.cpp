

#include "bankqueue.h"


/*****************************
Destructor. Calls makeEmpty()

Pre-condition: The object needs to have already been made
Post-condition: the BankQueue object now holds no Nodes and Transactions
*****************************/
BankQueue::~BankQueue(void)
{
	makeEmpty();
};

/********************************************
Adds a Transaction to the queue. Adds
all new nodes to the end of the list.
New node is created for every transaction that is pushed
The function iterates though to the end of the bankQueue - looks at the last node and creates a new node to place after the last node

Pre-condition: Intakes a pointer to a Transaction object through the parameter which is pushed into the BankQueue
Post-condition: A new node is created at the end of the BankQueue containing a pointer to the lastest transaction read
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
			current = current->next; //iterate onto the next node
		}
		current->next = new Node(toAdd, nullptr); // Add to end of list
	}
};

/**************************************************
Removes a Transaction from the list. Preforms this in a
first in, first out manner.

Pre-condition: The object has to have already been made
Post-condition: the last node is deleted
**************************************************/
void BankQueue::pop()
{
	Node* store = head;	// store is used to point to the last node and delete it

	if (store != nullptr) { // while the store pointer has not reached pointing to the last node
		head = head->next; // iterate through the bankQueue
		delete store;	// the last node is deleted
	}
};

/*
The top function returns the Transaction that is held by the Transaction pointer in the first node in the BankQueue

Pre-condition: The object has to have already been made
Post-condition:	returns the transaction that is first in the BankQueue
*/
Transaction BankQueue::top() const
{
	Transaction store; // to temporarly store the Transaction
	if (head != nullptr) {
		store = *head->data;	// dereferences the Transaction pointer in the head node and stores it in the variable "store" 
	}
	return store; // return the transaction object
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

Precondition: the object has to have already been made
Post-condition: returns a bool indicating whethere or not the bankQueue is empty - true if it is empty and false if it is not empty
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
 		while (inFile >> store) { //getline() from STL reads characters from an input stream and places them into a the store 

			if (store.length() != 1) {
				
				// print out an message stating that the transaction type was not correct
				cout << "/////////////////////" << endl << "ERROR: misformatted transaction data:" << endl << endl 
					<< "\"" << store << " is not a correct type of transaction" <<  "\"" <<
					endl << endl << "please try again with correct data" << endl << "/////////////////////" << endl << endl;

				// skips the inFile stream to look at the next line in the command data file
				inFile.ignore(numeric_limits<streamsize>::max(), '\n'); 

				if (inFile.eof()) {
					break; //if we reach the eof finish the while
				}
			}
			else {
				newTransaction = new Transaction();	// a new Transaction object is made

													// the command that is stored by "store" is passed through to the setData function in the Transaction class
													// the function reads the string store and sets information about the command in the newly created transaction object
				if (newTransaction->setData(store, inFile)) {
					push(newTransaction);	// if the data was properly read and set into the new transaction object, then push the object into the BankQueue
				}

				if (inFile.eof()) {
					break; //if we reach the eof finish the while
				}
			}
		}
	}
	else {

		// If unable to open the transaction to read the commands then we cannot read any commands
		cerr << "/////// ERROR: unable to open the transactions file    ///////" << endl;
		return false;
	}

	return true;
};