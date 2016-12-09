#include "account.h"

using namespace std;


Account::Account()
{
	accountType = "uninitialized";
}

//----------------------------------------------------
// Returns the account balance
int Account::getAccountBalance() const {
	return balance;
}

//----------------------------------------------------
// Sets the account balance
void Account::setAccountBalance(const int amount) {
	balance = amount;
}

//----------------------------------------------------
// Deposits money into account
void Account::deposit(const int amount) {
	balance += amount;
}

//----------------------------------------------------
// Removes funds from balance, returns true if account had enough
// money to cover withdraw. Returns false if it has insuffient funds.
bool Account::withdraw(const int amount, array<Account, 10>& accounts) {
	if ((balance - amount) >= 0) { //if we can just withdraw, do so
		balance -= amount;
		return true;
	}
	else {

		if (MoneyMarket) { //if we're a moneymarket

			return transfer(0, 1, amount, accounts);

		}
		else if (Bond) { //if we're a bond

			return transfer(2, 3, amount, accounts);

		}
		else {
			return false; //if we're a normal account we can't go negative and we can't borrow from other accounts
		}
	}
}

bool Account::transfer(const int accountID1, const int accountID2, int amount, array<Account, 10>& accounts) {
	if (accountID == accountID1) { //we are either accountID1 or accountID2

		if (balance + accounts[accountID2].balance >= amount) {
			accounts[accountID2].withdraw(amount - balance, accounts);
			balance = 0;
			return true;
		}
		else {
			return false;
		}

	}
	else { //we are not accountID1, we must be accountID2

		if (balance + accounts[accountID1].balance >= amount) {
			accounts[accountID1].withdraw(amount - balance, accounts);
			balance = 0;
			return true;
		}
		else {
			return false;
		}
	}
}

ifstream& operator >> (ifstream& input, Account& obj) {
	int i;
	input >> i;
	obj.setAccountBalance(i);
	return input;
}

int Account::getAccountID() const {
	return accountID;
}

void Account::setAccountType(const string type)
{
	accountType = type;
}

string Account::getAccountType() const
{
	return accountType;
}

void Account::setAccountID(const int ID) {
	accountID = ID;
}
