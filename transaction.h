/******************************************************************************************
Transactions class will read in a filestream of transactions. Assumptions are that
the data in the filestream will be correctly formatted. Transactions will
be added to a transactions queue in the BankManager class. They will be executed in the
order that they are read. Based on the transaction information, it will store the info in
the correct variables and execute the transaction.
******************************************************************************************/


#ifndef TRANSACTION_H
#define TRANSACTION_H


#include <string>
#include <iostream>
#include <stdio.h>

#include "client.h"


using namespace std;


class Transaction {


	friend ostream& operator<<(ostream& stream, const Transaction& transaction); //operator<<


private:


	string description; // Decription of the transaction

	char transactionType; // Char representing the type of transaction

	int amount; // Amount to be transacted

	Client firstClient; // Integer represents firstClients account number
	int firstClientID;
	int firstAccountID; //Integer representing the account ID of the first client

	Client secondClient; // Integer represents secondClients account number
	int secondClientID;
	int secondAccountID; //Integer representing the account ID of the second client

	vector<string> parsedTransaction; //vector to hold a parsed, segmented version of the string transaction that setData receives.



public:

	Transaction();

	bool setData(const string type, ifstream& inFile); // Sets the transaction data from reading a filestream

	char getTransactionType() const; //retrieve the type of transaction that this is

	string getDescription(void) const; // Returns a string of transaction description

	int getAmount(void) const; // Returns an int with transaction amount

	int getFirstClientID(void) const; // Returns firstClient
	int getSecondClientID(void) const; // Returns secondClient

	void setFirstClient(const Client& client); // Sets the account number for client one
	void setSecondClient(const Client& client); // Sets the account number for client two

	Client getFirstClient() const;
	Client getSecondClient() const;

	bool transact(); //perform the specified transaction based on this Transaction's data members


	/*
		the three horsemen:

		depositOrWithdraw is a composite of both deposit and withdraw, with the
		case specified within.

		move moves money between two clients or between a singular client's accounts. perhaps it might
		find itself even moving money from the same account to itself.

		history prints out a client's transaction history.
	*/
	bool depositOrWithdraw();
	bool move();
	void history();


};


#endif // !TRANSACTION_H


