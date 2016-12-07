#pragma once
/******************************************************************************************
Transactions class will read in a filestream of transactions. Assumptions are that 
the data in the filestream will be correctly formatted. Transactions will
be added to a transactions queue in the BankManager class. They will be executed in the
order that they are read. Based on the transaction information, it will store the info in 
the correct variables and execute the transaction. 
******************************************************************************************/


#ifndef transaction_h
#define transaction_h


#include "client.h"
#include <string>


using namespace std;


class Transaction {


private:


	string description; // Decription of the transaction
	const char transactionType; // Char representing the type of transaction
	const int amount; // Amount to be transacted
	const int firstClient; // Integer represents firstClients account number
	const int firstAccountID; //Integer representing the account ID of the first client
	const int secondClient; // Integer represents secondClients account number
	const int secondAccountID; //Integer representing the account ID of the second client


	void setDescription(string); // Sets the transaction decription
	void setAmount(const int); // Sets the transaction amount
	void setFirstClient(int*); // Sets the account number for client one
	void setSecondClient(int*); // Sets the account number for client two




public:


	Transaction(); // Default no args constructor
	~Transaction(); // Destructor


	bool setData(ifstream&); // Sets the transactin data from reading a filestream
	string getDescription(void) const; // Returns a string of transaction description
	int getAmount(void) const; // Returns an int with transaction amount
	int getFirstClient(void) const; // Returns firstClient
	int getSecondClient(void) const; // Returns secondClient
	int getFirstClientID(void) const; // Returns firstClientID
	int getSecondClientID(void) const; // Returns secondClientID
	
	void deposit();
	bool withdraw();
	bool move();
	string history();


};


#endif // !transaction.h


