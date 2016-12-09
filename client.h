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
	int getOverallBalance() const;
	bool setData(const string last, ifstream& inFile);
	void deposit(const int accountID, const int amount, const string transaction);
	bool withdraw(const int accountID, const int amount, const string transaction);
	void displayHistory(const string transaction);

private:

	string firstName = "undeclared";
	string lastName = "undeclared";
	int accountID = 0;
	int overallBalance = 0;
	queue<string> transactionHistory;
	array<Account, 10> accounts;

private:

	void setLastName(string input);
	void setFirstName(string input);
	void setAccountNumber(int input);
	void setOverallBalance(int input);
};

#endif //CLIENT_H
