#ifndef CLIENT_H
#define CLIENT_H

#include <cstring>
#include <queue>
#include <array>

#include "account.h"

using namespace std;

class Client {

	//operator<< for outputing the client, with its accounts, both starting and ending values.
	friend ostream& operator<<(ostream& stream, const Client& client);

public:

	//default constructor, used to initialize the array of accounts
	Client();

	//constructor with a given first and last name, as well as an ID to assign to the Client.
	Client(string first, string last, int ID);

	//comparison operators
	bool operator>(const Client& toCompare) const;
	bool operator<(const Client& toCompare) const;
	bool operator==(const Client& toCompare) const;
	bool operator!=(const Client& toCompare) const;

	//getters, to get the first and last name of the client, respectively
	string getFirstName() const;
	string getLastName() const;

	//getters, to retrive information about a specific account
	//that the client owns
	int getClientID() const;
	string getAccountName(int ID) const;

	//setter for all data contained in client, using an ifstream
	//and a string containing the last name of the client.
	bool setData(const string last, ifstream& inFile);

	//the three action methods, deposit to put money into a given account, withdraw,
	//to take money out of a given account, and displayHistory, to display
	//the transaction history of this client object
	void deposit(const int clientID, const int amount, const string transaction);
	bool withdraw(const int clientID, const int amount, const string transaction);
	void displayHistory(const string transaction);

	//toString method
	string toString();

private:

	//first and last name
	string firstName = "undeclared";
	string lastName = "undeclared";

	//the ID of this client, specific to each client or not depending on how
	//smart you are with your data initialization. the bst that is used underlying
	//the client section of this program does not mind duplicates -- but if you search
	//it you will only find the first occurence of that ID.
	int clientID = 0;

	//the transaction history of this client, stored in a queue
	queue<string> transactionHistory;

	//two arrays, the first to store the starting balances of all accounts associated with this client,
	//the second to store the balance of each account as transactions occur and they change.
	array<Account, 10> startingAccounts;
	array<Account, 10> accounts;

	//all accounts associated with this client
	Account indexFund = Account("500 Index Fund", false, false);
	Account capitalValueFund = Account("Capital Value Fund", false, false);
	Account growthEquityFund = Account("Growth Equity Fund", false, false);
	Account growthIndexFund = Account("Growth Index Fund", false, false);
	Account valueFund = Account("Value Fund", false, false);
	Account valueStockIndex = Account("Value Stock Index", false, false);

	Account moneyMarket = Account("Money Market", true, false);
	Account primeMoneyMarket = Account("Prime Money Market", true, false);

	Account shortTerm = Account("Long-Term Bond", false, true);
	Account longTerm = Account("Short-Term Bond", false, true);

private:

	//private setters for first and last name, as well as
	//setting the client ID
	void setLastName(string input);
	void setFirstName(string input);
	void setClientID(int input);

};

#endif //CLIENT_H
