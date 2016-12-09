/*------------------------------------------------------------------------------------------------------

Main for Homework 5. Creates new BankManager object and passes two file streams to this object.
Then displays the clients built by the BankManager as well as the transactions that have been
completed.

------------------------------------------------------------------------------------------------------*/


#include <iostream>
#include <fstream>

#include "bankManager.h"
#include "client.h"
#include "transaction.h"
#include "bankqueue.h"


using namespace std;

int main() {

	BankManager bankManager;						//instantiates BankManager object
	ifstream clientFile;							//creates new ifstream
	clientFile.open("testdata2.txt");					//opens the data file

	bankManager.readClients(clientFile);			//passes the client data file to bankManger
													//to construct the BST

	ifstream transactionFile;						//creates new ifstream
	transactionFile.open("testcommand2.txt");			//opens the data file

	bankManager.readTransactions(transactionFile);	//passes the transaction data file stream
													//to the bankManager to carry out transactions
	cout << "Clients:" << endl;
	bankManager.displayClients();					//displays the clients in the bankManager

	cout << endl;

	cout << "Transactions:" << endl;
	bankManager.displayTransactions();				//displays the transactions in the bankManager


													//closes the ifstreams
	clientFile.close();
	transactionFile.close();
	return 0;
};
