/*------------------------------------------------------------------------------------------------

	The BankManager class is a high level class that manages the interactions between 
	Binary Search Tree of Clients and a queue of Transactions. This class will also log
	the Transactions that have been completed so that they can be undone if necessary.
	Note that this class manages interactions, and relies on the BinarySearchTree, Client,
	and Transaction classes to throw any errors pertaining to the suitability of data.

------------------------------------------------------------------------------------------------*/

#pragma once
#ifndef bankmanager_h
#define bankmanager_h

#include "client.h"
#include "transaction.h"
#include "bst.h"
#include "bankqueue.h"
#include <stack>
#include <queue>
#include <iostream>
#include <string>

class BankManager {

	private: 

	BankQueue<Transaction> pending;			//queue to hold Transactions that are pending
	stack<Transaction> completed;			//stack to hold transactions that have been completed 
	BST<Client> clients;		//Binary Search Tree to hold Clients

	public:

	void readClients(ifstream& inFile);
	void readTransactions(ifstream& inFile);
	void transact(void);	
	void displayClients(void);
	void displayTransactions(void);
};

#endif
