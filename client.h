#ifndef CLIENT_H
#define CLIENT_H

#include <cstring>
#include <queue>
#include <array>

#include "account.h"

using namespace std;

class Client {

	friend ostream& operator<<(ostream& stream, const Client& client);

public:

	Client();
	Client(string first, string last, int ID);


	bool operator>(const Client& toCompare) const;
	bool operator<(const Client& toCompare) const;
	bool operator==(const Client& toCompare) const;

	string getLastName() const;
	string getFirstName() const;

	int getAccountNumber() const;
	string getAccountName(int ID) const;

	int getOverallBalance() const;

	bool setData(const string last, ifstream& inFile);

	void deposit(const int accountID, const int amount, const string transaction);
	bool withdraw(const int accountID, const int amount, const string transaction);
	void displayHistory(const string transaction);

	string toString();

private:

	string firstName = "undeclared";
	string lastName = "undeclared";

	int accountID = 0;
	int overallBalance = 0;

	queue<string> transactionHistory;
	array<Account, 10> accounts;

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

	void setLastName(string input);
	void setFirstName(string input);
	void setAccountNumber(int input);
	void setOverallBalance(int input);
};

#endif //CLIENT_H
