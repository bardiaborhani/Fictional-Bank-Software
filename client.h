/*
This class contains all the information about a client in the bank. There can be many clients in the bank (the BST) and a object 
of this class contains everything that a client has. A client has a last name, first name, accountID, balance, transactionHistory, and 10 accounts
Each node in the BankManager's BST contains a pointer to a client node. When the BankManager wants to parse through the transaction commands,
it looks at the BST for clients specified by the command - then information from client is retrieve or modified according to the transaction command
*/

#ifndef CLIENT_H
#define CLIENT_H

#include <cstring>
#include <queue>
#include <array>

#include "account.h"

using namespace std;

class Client {

	//The overloaded output stream operator function tells the client what to display when the bankManager wants to display a client using <<
	friend ostream& operator<<(ostream& stream, const Client& client);

public:

	//This default constructor indicates, in order, all the types of accounts the client has
	Client();

	//this constructor is called when three parameters are passed into the parameter when a new client object is made
	// Sets the client's first name, last name, and accountID
	Client(string first, string last, int ID);

	//Compares two client objects' account numbers
	bool operator>(const Client& toCompare) const;
	bool operator<(const Client& toCompare) const;

	//Compares two client objects to see if they have the same accountID
	bool operator==(const Client& toCompare) const;

	// returns the clients last name
	string getLastName() const;

	// returns the clients first name
	string getFirstName() const;

	// returns the clients accountNumber
	int getAccountNumber() const;

	// returns the clients the type of account for one of the client's accounts - indicated by the value of the parameter
	string getAccountName(int ID) const;

	// returns the client's overall balance
	//int getOverallBalance() const;

	//the information from the parameters is inputted into the variables in the client object
	//the client's last name is set to the value of the first parameter
	bool setData(const string last, ifstream& inFile);

	//This function deposists money into one of the client's accounts
	void deposit(const int accountID, const int amount, const string transaction);

	//Money is withdrawen from one of the client's accounts - the balance of one of the client's accounts will drop
	bool withdraw(const int accountID, const int amount, const string transaction);
	
	//The transactions completed by the client are displayed in order of when they were completed - the lastest transaction is displayed last
	void displayHistory(const string transaction);

	//the toString() function returns this client's information
	string toString();

private:

	string firstName = "undeclared"; // contains the client's first name
	string lastName = "undeclared"; //  contains the client's last name

	int accountID = 0; // contains a unique 4-digit account number that belongs to the client - used to look up the client in the bank
	//int overallBalance = 0;	// the balance of all of the client's accounts

	queue<string> transactionHistory;	// keeps track of all the transactions the client has completed
	array<Account, 10> accounts;	// holds all ten of the client's accounts

	// All ten types of accounts
	// The first parameter indicates the name of the account (the type of account)

	// These accounts are accounts that are not money market or bond accounts
	Account indexFund = Account("500 Index Fund", false, false);
	Account capitalValueFund = Account("Capital Value Fund", false, false);
	Account growthEquityFund = Account("Growth Equity Fund", false, false);
	Account growthIndexFund = Account("Growth Index Fund", false, false);
	Account valueFund = Account("Value Fund", false, false);
	Account valueStockIndex = Account("Value Stock Index", false, false);

	// Money Maket Accounts
	// the second parameter is set to true indicating that it is a money market type of account
	Account moneyMarket = Account("Money Market", true, false);
	Account primeMoneyMarket = Account("Prime Money Market", true, false);

	// Bond Accounts
	// the third parameter is set to true indicating that it is a bond type of account
	Account shortTerm = Account("Long-Term Bond", false, true);
	Account longTerm = Account("Short-Term Bond", false, true);

private:

	//Assigns the private data member "lastName" to the value of the string parameter passed through the parameter
	void setLastName(string input); 

	//Assigns the private data member "firstName" to the value of the string parameter passed through 
	void setFirstName(string input);
	
	//Assigns the private data member "accountID" to the value of the int parameter passed through
	void setAccountNumber(int input);
	
	//Assigns the private data member "overallBalance" to the value of the int parameter passed through  
	//void setOverallBalance(int input);
};

#endif //CLIENT_H
