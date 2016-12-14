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

void BankManager::readClients(ifstream& inFile) {
	bool success = clients.buildTree(inFile);  // calls the buildTree function in the BST class in bst.h

	if (!success) exit(-1);	// if the client had an account whose balance was less than 0 then there was something wrong with the client data- end program
}



/*------------------------------------------------------------------------------------------------

This function takes in a file stream and uses it to build a queue of Transactions.

Flow of Program:
- readTransactions(ifstream&) takes in a file stream

PRECONDITIONS:
- file must contain data formatted for Transaction objects

POSTCONDITIONS:
- fills pending Transaction queue

------------------------------------------------------------------------------------------------*/

void BankManager::readTransactions(ifstream& inFile) {

	// transactions are read from the file stream that reads the transaction (command) data file
	// True is returned if the commands were properly formatted and read
	// false is returned if commands were not properly formatted - if there was something wrong with the command
	// For example, if would return a false if the command, that is being read, did not state account number of the client 
	bool success = pending.buildQueue(inFile);

	if (!success) exit(-1); // if the command was not read properly then exit the program

							// the transactions were properly read and the bankmanager object now has a BankQueue filled with Transactions that are pending
							// the transact function is called to complete all the Transactions in the transaction queue ("pending")
	transact();
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

PRECONDITION: The transactinos were read from the command data file

POSTCONDITION: The transactions were read and action was taken according to what was stated by the command

------------------------------------------------------------------------------------------------*/

void BankManager::transact(void) {
	// All the transactions in the pending BankQueue are read (all the commands that were stated in the command data file)
	while (!pending.isEmpty()) {
		Transaction transaction = pending.top();	// completes the transactions one by one in order that they were read from the command data file

													//get all necessary information from the transaction
													//class so we can do our job
		int client1 = transaction.getFirstClientID();
		int client2 = transaction.getSecondClientID();

		bool success = false;
		bool secondSuccess = false;
		//find the clients involved in the operation, give them to the transaction
		//so it can do its job
		success = clients.search(client1);
		if (success && transaction.getTransactionType() == 'M') {	// If the command is a Move command then it requires information about two accounts
			secondSuccess = clients.search(client2);
		}

		//take the transaction off the pending queue and throw it away
		pending.pop();

		if (success) {
			transaction.setFirstClient(clients.retrieve(client1));
			if (secondSuccess) transaction.setSecondClient(clients.retrieve(client2));

			// only push transaction into the completed stack of transactions if the transaction was able to be completed
			bool successfulTransaction;

			//tell the transaction to do its business (outside please, 
			//goodness gracious)
			successfulTransaction = transaction.transact();

			//if the transaction was completed successfully
			if (successfulTransaction) {

				//put the transaction on the completed pile
				completed.push(transaction);

				//insert whichever clients we affected back into the
				//clients BST
				clients.insert(transaction.getFirstClient());
				if (secondSuccess) clients.insert(transaction.getSecondClient());
			}
			else {

				//if the transaction was unsuccessful, print out an error message to
				//indicate that fact.
				cerr << "/////////////////////" << endl << "ERROR: The transaction:"
					<< endl << "\"" << transaction.getDescription() << "\"" << endl
					<< "was not able to be completed due to insufficient funds"
					<< endl << "//////////////////" << endl << endl;
			}
		}
	}
}

/*------------------------------------------------------------------------------------------------

This function will print all Clients with beginning and ending account balances of each of
the Client's accounts. Clients will be printed in order by clientID.

PRECONDITION: The object has to already be made

POSTCONDITION: The clients are displayed in the console

------------------------------------------------------------------------------------------------*/

void BankManager::displayClients(void) {
	clients.inorderWalk();	// the inorderWalk function in the BST class is called
}

/*------------------------------------------------------------------------------------------------

This function will print out all of the Transactions that have been completed.
A stack is created to be used to bring the transaction objects out of the completed stack to be displayed one by one
After they are displayed, the transaction are put back into the completed stack so the completed stack is the same as it was before this
function was called
PRECONDITION: Object has to already be made

POSTCONDITION: The transactions are displayed in the console

------------------------------------------------------------------------------------------------*/

void BankManager::displayTransactions(void) {
	cout << "Displayed by most recent:" << endl;

	// stack created to be used to bring the transaction objects out of the completed stack to be displayed one by one
	// after they are displayed, the transaction are put back into the completed stack
	stack<Transaction> displayStack;
	while (!completed.empty()) {
		Transaction store = completed.top();	// looks at the most recently completed transaction
		cout << store << endl;	// that transaction is outputted to the console
		displayStack.push(store); // the new stack now inserts the transaction that was just displayed	
		completed.pop(); // the transaction is popped off so the next transaction can be seen in the completed stack
	}
	while (!displayStack.empty()) {	// now the transactions are put back into the "completed" stack
		completed.push(displayStack.top());
		displayStack.pop();	// the transaction is popped off so the next transaction can be seen in the stack used to display the transactions
	}
	cout << endl;
}
