#include <sstream>

#include "client.h"

using namespace std;


Client::Client() {

	moneyMarket = Account(true, false);
 	primeMoneyMarket = Account(true, false);
 	shortTerm = Account(false, true);
 	longTerm = Account(false, true);

	accounts = { moneyMarket, primeMoneyMarket, longTerm, shortTerm,
		indexFund, capitalValueFund, growthEquityFund,
		growthIndexFund, valueFund, valueStockIndex };


}

//--------------------------------------------------------------------------------------------
/*


Pre-condition:
Post-condition:
*/
Client::Client(string first, string last, int ID) {

	Client();

	firstName = first;
	lastName = last;
	accountID = ID;
}

//--------------------------------------------------------------------------------------------
/*



Pre-condition:
Post-condition:
*/
ostream& operator<<(ostream& stream, const Client& client) {
	stringstream ss;
	ss << "CLIENT NAME: " << client.firstName << " " << client.lastName << " " << "CLIENT ID: " << client.accountID << " ACCOUNTS:";
	for (int i = 0; i < 10; i++) ss << " " << client.accounts[i].getAccountBalance();
	stream << ss.str();
	return stream;
}

//--------------------------------------------------------------------------------------------
/*



Pre-condition:
Post-condition:
*/
bool Client::setData(const string last, ifstream& inFile) {

	// create a bool to keep track that everything in the line we are reading in client data file is read properly
	// if something is not read properly then success is set to false and returned by the function
	// if false is returned then the program will finish executing 
	bool success = true;	
	int accountBalance;

	// the first string read in a line in the client data file represents the last name of the client
	// set the last name of this client to the first string read in the client data file
	lastName = last;	

	inFile >> firstName >> accountID;
	for (int i = 0; i<10; i++) {
		inFile >> accountBalance;
		if (accountBalance < 0) success = false;	// if the balance of an account is read as below 0 then there is something wrong about the client data file - should never be below 0 - an account does start below 0
		accounts[i].setAccountBalance(accountBalance); // Set the balance of this type of account by passing in the amount that is written in the client data file
		accounts[i].setAccountID(i);	// number 0-9 representing the client's type of account- ex. 0 = Money Market account
	}

	return accountID >= 0 && success;
}

//--------------------------------------------------------------------------------------------
/*



Pre-condition:
Post-condition:
*/
void Client::deposit(const int accountID, const int amount, const string transaction) {
	accounts[accountID].deposit(amount);
	transactionHistory.push(transaction);
}

//--------------------------------------------------------------------------------------------
/*



Pre-condition:
Post-condition:
*/
bool Client::withdraw(const int accountID, const int amount, const string transaction) {
	bool success;

	success = accounts[accountID].withdraw(amount, accounts);
	if (success) transactionHistory.push(transaction);

	return success;
}

//--------------------------------------------------------------------------------------------
/*



Pre-condition:
Post-condition:
*/
void Client::displayHistory(const string transaction) {

	queue<string> copy = transactionHistory;

	cout << firstName << " " << lastName << "'s history:" << endl;

	//if this client's history is empty to begin
	//with, simply display a statement to that effect.
	if (copy.empty()) {
		cout << firstName << " " << lastName << " has no transaction history" << endl;
	}

	while (!copy.empty()) {
		cout << copy.front() << endl;
		copy.pop();
	}
	transactionHistory.push(transaction);
}

//--------------------------------------------------------------------------------------------
/*



Pre-condition:
Post-condition:
*/
string Client::toString()
{
	stringstream ss;
	ss << *this;
	return ss.str();
}

//--------------------------------------------------------------------------------------------
/*



Pre-condition:
Post-condition:
*/
bool Client::operator>(const Client& toCompare) const {
	return accountID > toCompare.getAccountNumber();
}

//--------------------------------------------------------------------------------------------
/*



Pre-condition:
Post-condition:
*/
bool Client::operator<(const Client& toCompare) const {
	return accountID < toCompare.getAccountNumber();
}

//--------------------------------------------------------------------------------------------
/*



Pre-condition:
Post-condition:
*/
bool Client::operator==(const Client& toCompare) const {
	return accountID == toCompare.getAccountNumber();
}

//--------------------------------------------------------------------------------------------
/*



Pre-condition:
Post-condition:
*/
string Client::getLastName() const {
	return lastName;
}

//--------------------------------------------------------------------------------------------
/*



Pre-condition:
Post-condition:
*/
string Client::getFirstName() const {
	return firstName;
}

//--------------------------------------------------------------------------------------------
/*



Pre-condition:
Post-condition:
*/
int Client::getAccountNumber() const {
	return accountID;
}

//--------------------------------------------------------------------------------------------
/*



Pre-condition:
Post-condition:
*/
int Client::getOverallBalance() const {
	return overallBalance;
}

//--------------------------------------------------------------------------------------------
/*
Assigns the private data member "lastName" to the value of the string parameter passed through


Pre-condition:
Post-condition:
*/
void Client::setLastName(string input) {
	lastName = input;
}

//--------------------------------------------------------------------------------------------
/*Assigns the private data member "firstName" to the value of the string parameter passed through 


Pre-condition:
Post-condition:
*/
void Client::setFirstName(string input) {
	firstName = input;
}

//--------------------------------------------------------------------------------------------
/* Assigns the private data member "accountID" to the value of the int parameter passed through


Pre-condition:
Post-condition:
*/
void Client::setAccountNumber(int input) {
	accountID = input;
}

//--------------------------------------------------------------------------------------------
/* Assigns the private data member "overallBalance" to the value of the int parameter passed through 

Pre-condition:
Post-condition:
*/
void Client::setOverallBalance(int input) {
	overallBalance = input;
}
