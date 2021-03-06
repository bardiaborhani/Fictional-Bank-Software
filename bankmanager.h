/*------------------------------------------------------------------------------------------------

The BankManager class is a high level class that manages the interactions between
Binary Search Tree of Clients and a queue of Transactions. This class will also log
the Transactions that have been completed so that they can be undone if necessary.
Note that this class manages interactions, and relies on the BinarySearchTree, Client,
and Transaction classes to throw any errors pertaining to the suitability of data.

------------------------------------------------------------------------------------------------*/

#ifndef BANKMANAGER_H
#define BANKMANAGER_H

#include <stack>
#include <queue>
#include <iostream>
#include <string>

#include "bst.h"
#include "bankqueue.h"

class BankManager {

private:

	BankQueue pending;			//queue to hold Transactions that are pending
	stack<Transaction> completed;			//stack to hold transactions that have been completed 
	BST clients;		//Binary Search Tree to hold Clients

public:

	void readClients(ifstream& inFile); //passes in an ifstream that reads the client data file to and creates a BST of clients
	void readTransactions(ifstream& inFile); // passes in an ifstream that reads the command data file and puts each transaction in the pending BankQueue
	void transact(void); // reads the transaction and completes the command
	void displayClients(void); //displays all the clients in the bank
	void displayTransactions(void); // displays all the transactions that were read in the command data file
};

#endif //BANKMANAGER_H
