/*------------------------------------------------------------------------------------------------
The Account class represents an account owned by a client. The class identifies if it is a normal, moneymarket, or bond account.
The type of account affects the accounts ability for withdrawel in the withdraw function.
The account also has a balance and accountID variable to keep track of the balance of the account and the number of the account (0-9)
Each client has 10 accounts
This class keeps track of all the information for each of the ten accounts (one object of account represents one of the client's account)
------------------------------------------------------------------------------------------------*/

#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <iostream>
#include <fstream> 
#include <array>

using namespace std;

class Account {

	friend ifstream& operator >> (ifstream&, Account&); // The inputs stream operator allows program to set the balance of this account

public:

	Account(); // Constructor used when creating an account object

			   // If the account created is a money market or bond account, then the account constructor that is used to create the object has
			   // at least two parameters which indicates which of the two types of account they are
	Account(string type, bool moneymarket = false, bool bond = false) : MoneyMarket(moneymarket), Bond(bond), accountType(type) {};

	// Setters
	void setAccountBalance(const int amount);	// sets the balance of this account
	void setAccountID(const int ID);	// sets the accountID of this account
	void setAccountType(const string type);	// sets the type of this account

											// Getters
	int getAccountBalance() const;	// returns the balance of this account
	int getAccountID() const;	// returns the accountID of this account
	string getAccountType() const;	// returns the type of this account

									// Deposits money into account
	void deposit(const int amount);

	// Removes funds from balance, returns true if account had enough
	//money to cover withdraw. Returns false if it has insuffient funds.
	bool withdraw(const int amount, array<Account, 10>& accounts);

private:

	string accountType;	// identifies which of the ten type of accounts this account is

						// if this object is a money market or bond class, money is able to be transferred inbetween accounts to make
						// up for money that needs to be withdrawen if the money sought to be withdrawn is more than the balance of this account
	bool transfer(const int accountID1, const int accountID2, int amount, array<Account, 10>& accounts);

	int balance; // Stores value of our balance
	int accountID; // Unique account ID's
	bool MoneyMarket = false;	// set to true if this account is a money market account
	bool Bond = false; // set to true if this account is a bond account
};

#endif
