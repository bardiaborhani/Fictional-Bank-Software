/*------------------------------------------------------------------------------------------------

  The BankManager class is a high level class that manages the interactions between 
  Binary Search Tree of Clients and a queue of Transactions. This class will also log
  the Transactions that have been completed so that they can be undone if necessary.
  Note that this class manages interactions, and relies on the BinarySearchTree, Client,
  and Transaction classes to throw any errors pertaining to the suitability of data.

------------------------------------------------------------------------------------------------*/


#include "bankmanager.h"

using namespace std;



/*------------------------------------------------------------------------------------------------

This function will take in a file stream and use it to build a binary search tree
of Clients. The file stream will be passed off to the BinarySearchTree to build the
tree.

Flow of Program:
  - readClients(ifstream&) takes in a file stream.
  - clients.buildTree(ifstream&) is called and the file stream is passed to it
  - buildTree(ifstream&) creates new Client objects, passing the file stream
    to each new Client and inserting the Client in to the clients BinarySearchTree
    until the end-of-file is reached

PRECONDITIONS:
  - file must contain data formatted for Client objects

POSTCONDITIONS:
  - reads from file to fill the clients BinarySearchTree

------------------------------------------------------------------------------------------------*/

void BankManager::readClients(ifstream& inFile){
  
}



/*------------------------------------------------------------------------------------------------

This function takes in a file stream and uses it to build a queue of Transactions.
The STL queue class is used. The file stream is parsed by line and passed to new Transaction
objects which are then added to the queue.

Flow of Program:
  - readTransactions(ifstream&) takes in a file stream
  - file stream is parsed in to strings which are passed to new Transaction objects
  - Transaction objects are added to pending

PRECONDITIONS:
  - file must contain data formatted for Transaction objects

POSTCONDITIONS:
  - fills pending Transaction queue

------------------------------------------------------------------------------------------------*/

void BankManager::readTransactions(ifstream& inFile){
  
}

/*------------------------------------------------------------------------------------------------

This function completes all Transactions in the transaction queue. The function pops a
transaction off of the transaction queue, finds the appropriate clients, and passes
the information to the clients to carry out the transaction. The transaction is then moved
to the Transaction stack to log that it has been completed and allow for transactions
to be undone.

Flow of Program:
  - transact(void) pops a Transaction object off of pending
  - program searches clients by account number via the retrieve method call on clients
  - program has both Client objects perform the appropriate transaction
  - data is handed to both Clients for them to log necessary transaction data
  - Transaction is moved to the completed

NOTE:
  - this class is not responsible for handling errors pertaining to Transactions

------------------------------------------------------------------------------------------------*/

void BankManager::transact(void){
  
}

/*------------------------------------------------------------------------------------------------

This function will print all Clients with beginning and ending account balances of each of
the Client's accounts. Clients will be printed in order by accountID.

------------------------------------------------------------------------------------------------*/

void BankManager::displayClients(void){
  
}

/*------------------------------------------------------------------------------------------------

This function will print out all of the Transactions that have been completed.

------------------------------------------------------------------------------------------------*/

void BankManager::displayTransactions(void){
  
}
