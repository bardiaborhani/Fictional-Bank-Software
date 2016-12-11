/*------------------------------------------------------------------------------------------------------

Program created by:
Kevin Ulrich
Bardia Borhani

December 11th, 2016

PURPOSE: 

	Write software to handle transactions for a local financial firm called Lots of Savings Earned (LOSE)
	LOSE wishes to be able to display the contents of the firm at any time and allow clients to perfom transactions 
	on their various accounts.

ASSUMPTIONS: 

	It is assumed that all data text files are formatted correctly. All text files, if this program is being run
	on the Windows OS, must contain a line after the data for EOF purposes.

	For data files, the clients should be formatted as follows: 

		* lastName firstName account1 account2 account3 account4 account5 account6 account7 account8 account9 account10

		where all 10 accounts are accounted for, are integers and no chars occur after the client's first name and last name.
		The accounts should be in correct order as specified in the design document (i.e. account1 is Money Market, account2
		is Prime Money Market, etc). All data for a single client should be one one line of the text file.

	For command files, the transactions should be formatted in one of the four ways:
	NOTE that clientID and accountID are concatenated, such as 12341, where 1234 is the client ID, and 1 is the account ID.

		* D clientIDaccountID amount
	
		* W clientIDaccountID amount

		* M clientIDaccountID amount clientIDaccountID

		* H clientIDaccountID


	any ints used in the data files must not exceed 2147483647, which is the max of an integer. over this amount, erroneous behaviour
	will occur.

DESCRIPTION:

	Main for Homework 5. Creates new BankManager object and passes two file streams to this object.
	Then displays the clients built by the BankManager as well as the transactions that have been
	completed.

------------------------------------------------------------------------------------------------------*/


#include <iostream>
#include <fstream>

#include "bankManager.h"

using namespace std;

int main() {

	//instantiates BankManager object, which oversees all high level operations
	//regarding Clients and the transactions that occur between/to them.
	BankManager bankManager;

	//create an ifstream and open the data text file to read into
	//the BankManager object.
	ifstream clientFile;
	clientFile.open("testdata2.txt");

	//passes the client data file to bankManger
	//to construct the BST
	bankManager.readClients(clientFile);

	//create an ifstream and open the commands text file to read into
	//the BankManager object.
	ifstream transactionFile;
	transactionFile.open("testcommand2.txt");

	//passes the transaction data file stream
	//to the bankManager to carry out transactions
	bankManager.readTransactions(transactionFile);

	//prints out the output of the displayClients method in our BankManager object.
	//this prints all the clients that have been stored in the BankManager, which
	//were read in when we called readClients.
	cout << "Clients:" << endl << endl;
	bankManager.displayClients();

	cout << endl;

	//prints out the output of the displayTransactions method in our BankManager object.
	//this will print out all transactions that were completed during readTransactions.
	cout << "Transactions:" << endl;
	bankManager.displayTransactions();

	// Again we are out printing out all the clients - to show the ending balances of the clients
	//prints out the output of the displayClients method in our BankManager object.
	//this prints all the clients that have been stored in the BankManager, which
	//were read in when we called readClients.
	cout << "Clients:" << endl << endl;
	bankManager.displayClients();

	//closes the ifstreams
	clientFile.close();
	transactionFile.close();

	return 0;
};
