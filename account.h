/***************** Standard Account********************
This class represents a standard account. It has private
variables that store the balance of the account and the
account ID.
*******************************************************/
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <fstream>
#include <array>

using namespace std;

class Account {

	friend ifstream& operator >> (ifstream&, Account&);

public:

	Account(bool moneymarket = false, bool bond = false) : MoneyMarket(moneymarket), Bond(bond) {};

	// Returns the account balance
	int getAccountBalance() const;

	// Sets the account balance
	void setAccountBalance(const int amount);

	void setAccountID(const int ID);

	int getAccountID() const;

	// Deposits money into account
	void deposit(const int amount);

	// Removes funds from balance, returns true if account had enough
	//money to cover withdraw. Returns false if it has insuffient funds.
	bool withdraw(const int amount, array<Account, 10>& accounts);

private:

	bool transfer(const int accountID1, const int accountID2, int amount, array<Account, 10>& accounts);

	int balance; // Stores value of our balance
	int accountID; // Unique account ID's
	bool MoneyMarket = false;
	bool Bond = false;
};

#endif
