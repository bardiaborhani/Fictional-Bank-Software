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


	friend ostream& operator<<(ostream& stream, const Transaction& transaction) { //<< operator overload

		switch (transaction.transactionType) {
		case 'D':
			stream << "Deposited $" << transaction.amount << " in acccount " << transaction.firstAccountID << ", which is owned by "
				<< transaction.firstClient.getFirstName() << " " << transaction.firstClient.getLastName() << endl;
			break;
		case 'W':
			stream << "Withdrew " << transaction.amount << " from account " << transaction.firstAccountID << ", which is owned by "
				<< transaction.firstClient.getFirstName() << " " << transaction.firstClient.getLastName() << endl;
			break;
		case 'M':
			stream << "Moved " << transaction.amount << " from account " << transaction.firstAccountID << ", which is owned by "
				<< transaction.firstClient.getFirstName() << " " << transaction.firstClient.getLastName() << " and placed it in account "
				<< transaction.secondAccountID << ", which is owned by " << transaction.secondClient.getFirstName() << " "
				<< transaction.secondClient.getLastName() << endl;
			break;
		default:
			cerr << "an error occurred"; //todo: yeah change this, actual exception here.
		}

		return stream;
	}


private:


	string description; // Decription of the transaction //todo: remove this, we print instead of storing an english translation

	char transactionType; // Char representing the type of transaction

	int amount; // Amount to be transacted

	Client firstClient; // Integer represents firstClients account number
	int firstClientID;
	int firstAccountID; //Integer representing the account ID of the first client

	Client secondClient; // Integer represents secondClients account number
	int secondClientID;
	int secondAccountID; //Integer representing the account ID of the second client

	vector<string> parsedTransaction;

	//unnecessary
	//void setDescription(string); // Sets the transaction decription
	//void setAmount(const int); // Sets the transaction amount


public:

	Transaction();

	bool setData(string transaction); // Sets the transaction data from reading a filestream

	string getDescription(void) const; // Returns a string of transaction description

	int getAmount(void) const; // Returns an int with transaction amount

	int getFirstClientID(void) const; // Returns firstClient
	int getSecondClientID(void) const; // Returns secondClient

	void setFirstClient(Client& client); // Sets the account number for client one
	void setSecondClient(Client& client); // Sets the account number for client two

	bool transact();

	bool depositOrWithdraw();
	bool move();
	void history();


};


#endif // !TRANSACTION_H


