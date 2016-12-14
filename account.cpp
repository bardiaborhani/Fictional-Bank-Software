#include "account.h"

using namespace std;

// Constructor used when creating an account object
// Initializes accountType variable to "unitialized"
// Pre-condition: Object for class has to be made
// Post-condition: accountType variable is set to "uninitialized"
Account::Account()
{
	accountType = "uninitialized";
}

//----------------------------------------------------
/*
Returns the balance of the account
Only way for another class to get the account's balance
Const is set to make sure the function does not change the balance
Pre-condition: Object for class has to be made
Post-condition: the variable balance of the account object is returned
*/
int Account::getAccountBalance() const {
	return balance;
}

//----------------------------------------------------
/*
Sets the account's balance variable to the value of the int variable passed in the parameter
the parameter variable is set to const to make sure it is not changed within the function
this sets the balance of a type of account owned by client
this function is called within the setData() function in the client.cpp file
Pre-condition: An int parameter is passed into the function
Post-condition: the balance variable of the account object is set to value of the variable passed into the parameter
*/
void Account::setAccountBalance(const int amount) {
	balance = amount;
}

//----------------------------------------------------
/*
Deposits money into account
the value of the balance variable is increased or stays the same - the amount cannot be less than 0- already handeled before
Pre-condition: An int is passed into the function - the value of the int is 0 or higher
Post-condition: Balance has a new balance (0 or more is added to the balance)
*/
void Account::deposit(const int amount) {
	balance += amount;	// the amount is added on top of the value of the balance
}

//----------------------------------------------------
/*
Removes funds from balance, returns true if account had enough
money to cover withdraw. Returns false if it has insuffient funds.
First tries to withdraw amount from the balance of the account
If the amount withdrawn causes the balance to go below zero, money from the moneymarket or bond accounts are transferred IF the account is a
moneymarket or bond account
If the account is not a money market or bond account, you cannot borrow money from other accounts
The function will return false if the amount sought to be withdrawn is more than the balance
The function will return true if the amount sought to be withdrawn doesnt bring the balance lower than 0
Pre-condition: a const int variable is passed into the account indicating the amount to subtract from the balance
Post-condition: a bool is returned indicating whether or not the withdraw was successful
*/
bool Account::withdraw(const int amount, array<Account, 10>& accounts) {
	if ((balance - amount) >= 0) { //if we can just withdraw, do so
		balance -= amount; // subtract the desired amount from the balance
		return true;	//return true since the withdraw was successful
	}
	else {

		if (MoneyMarket) { //if this account is a moneymarket (if the MoneyMarket variable is set to true)

			return transfer(0, 1, amount, accounts); // call the transfer function to transfer funds between bonds

		}
		else if (Bond) {  //if this account is a bond (if the Bond variable is set to true)

			return transfer(2, 3, amount, accounts); // call the transfer function to transfer funds between bonds

		}
		else {
			return false; //if we're a normal account we can't go negative and we can't borrow from other accounts
		}
	}
}

/*
If the account is a money market account:
transfer money from the other money market account
we check to see if the account we are dealing with is a money market (Account Number 0)
OR if it is a Prime Money Market (Account Number 1)

If the account is a bond account:
transfer money from the other bond account
we check to see if the account we are dealing with is a Long-term Bond account (Account Number 2)
OR if it is a Short-term Bond account (Account Number 3)

We identify which exact account this object is by comparing it to the first two parameters of the function
By identifying the account, we can transfer money from the other account, of the same type (money market or bond),
into this account to be withdrawn (as directed by the withdraw function which calls this function

Pre-condition: The function passes in two const ints (value between 0-3), an int representing the amount to be withdrawen, and a reference of an array of accounts
Post-condition: If the other account has enough money to cover the amount sought to be withdrawen, then function will return a true (if not, then it will return false)
*/
bool Account::transfer(const int accountID1, const int accountID2, int amount, array<Account, 10>& accounts) {
	//we are either accountID1 or accountID2
	if (accountID == accountID1) {	// This account is accountID1

		if (balance + accounts[accountID2].balance >= amount) {	// if the amount in the account is enough to pay the amount asked to be withdrawn...
			accounts[accountID2].withdraw(amount - balance, accounts);	// then withdraw the amount to cover the balance of the other money market/bond
			balance = 0; // the amount was covered by all the balance in this account and some in the other account of the same type - so we need to set the balance of this account to 0 
			return true;	// return true since the balance of both accounts was enough to cover the amount sought to be withdrawen
		}
		else {
			return false;	// the balance of both accounts of the same type are not enough to cover the amount sought to be withdrawen from the account
		}

	}
	else { //we are not accountID1, we must be accountID2

		if (balance + accounts[accountID1].balance >= amount) { // if the amount in the account is enough to pay the amount asked to be withdrawn...
			accounts[accountID1].withdraw(amount - balance, accounts);	// then withdraw the amount to cover the balance of the other money market/bond
			balance = 0;	// the amount was covered by all the balance in this account and some in the other account of the same type - so we need to set the balance of this account to 0 
			return true;	// return true since the balance of both accounts was enough to cover the amount sought to be withdrawen
		}
		else {
			return false;	// the balance of both accounts of the same type are not enough to cover the amount sought to be withdrawen from the account
		}

	}
}
/*
The inputs stream operator allows program to set the balance of this account
Pre-condition: Two parameters - the first one is a reference of an ifstream variable which allows input operator to be used
to set a balance to the account - a reference the account is also passed in to indicate which object to set the balance for
Post-condition: The ifstream variable is returned  to enable the functionality of the input stream operator
*/
ifstream& operator>>(ifstream& input, Account& obj) {
	int i;	// new variable is declared to later store the value of what is inputted by the ifstream
	input >> i;	// the input variable stores the value in "i"
	obj.setAccountBalance(i);	// the account balance of the object is set according to the value that was given to "i"
	return input;
}

/*
The function sets the accountType of the account object according to the value of the string
that is passed through the parameter
Pre-condition: A const string is passed in the parameter representing the accountType to be set to the object
Post-condition: The accountType is changed/set
*/
void Account::setAccountType(const string type)
{
	accountType = type;
}

/*
The function sets the accountID of the account object according the the value of the int
that is passed through the parameter
Pre-condition: A const int is passed in the parameter representing the accountID value to be set to the object
Post-condition: The accountID is changed/set
*/
void Account::setAccountID(const int ID) {
	accountID = ID;
}

/*
This function is used by another class to get access to the accountType of the account object
The account type is one of the ten types of accounts the client can have
Pre-condition: The object has to me made
Post-condition: the accountType is returned
*/
string Account::getAccountType() const
{
	return accountType;
}

/*
This function is used by another class to get access to the accountID of the account object
Pre-condition: The object has to me made
Post-condition: the accountID is returned
*/
int Account::getAccountID() const {
	return accountID;
}
