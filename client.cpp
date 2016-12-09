#include <sstream>

#include "client.h"

using namespace std;


Client::Client() {

	Account indexFund;
	Account capitalValueFund;
	Account growthEquityFund;
	Account growthIndexFund;
	Account valueFund;
	Account valueStockIndex;

	Account moneyMarket(true, false);
	Account primeMoneyMarket(true, false);

	Account shortTerm(false, true);
	Account longTerm(false, true);

	accounts = { indexFund, capitalValueFund, growthEquityFund,
		growthIndexFund, valueFund, valueStockIndex,
		moneyMarket, primeMoneyMarket, shortTerm, longTerm };


}

//--------------------------------------------------------------------------------------------
Client::Client(string first, string last, int ID) {

	Client();

	firstName = first;
	lastName = last;
	accountID = ID;
}

//--------------------------------------------------------------------------------------------
ostream& operator<<(ostream& stream, const Client& client) {
	stringstream ss;
	ss << "CLIENT NAME: " << client.firstName << " " << client.lastName << " " << "CLIENT ID: " << client.accountID << " ACCOUNTS:";
	for (int i = 0; i < 10; i++) ss << " " << client.accounts[i].getAccountBalance();
	stream << ss.str();
	return stream;
}

//--------------------------------------------------------------------------------------------
bool Client::setData(const string last, ifstream& inFile) {

	bool success = true;
	int accountBalance;

	lastName = last;

	inFile >> firstName >> accountID;
	for (int i = 0; i<10; i++) {
		inFile >> accountBalance;
		if (accountBalance < 0) success = false;
		accounts[i].setAccountBalance(accountBalance);
		accounts[i].setAccountID(i);
	}

	return accountID >= 0 && success;
}

//--------------------------------------------------------------------------------------------
void Client::deposit(const int accountID, const int amount, const string transaction) {
	accounts[accountID].deposit(amount);
	transactionHistory.push(transaction);
}

//--------------------------------------------------------------------------------------------
bool Client::withdraw(const int accountID, const int amount, const string transaction) {
	bool success;

	success = accounts[accountID].withdraw(amount, accounts);
	if (success) transactionHistory.push(transaction);

	return success;
}

//--------------------------------------------------------------------------------------------
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
bool Client::operator>(const Client& toCompare) const {
	return accountID > toCompare.getAccountNumber();
}

//--------------------------------------------------------------------------------------------
bool Client::operator<(const Client& toCompare) const {
	return accountID < toCompare.getAccountNumber();
}

//--------------------------------------------------------------------------------------------
bool Client::operator==(const Client& toCompare) const {
	return accountID == toCompare.getAccountNumber();
}

//--------------------------------------------------------------------------------------------
string Client::getLastName() const {
	return lastName;
}

//--------------------------------------------------------------------------------------------
string Client::getFirstName() const {
	return firstName;
}

//--------------------------------------------------------------------------------------------
int Client::getAccountNumber() const {
	return accountID;
}

//--------------------------------------------------------------------------------------------
int Client::getOverallBalance() const {
	return overallBalance;
}

//--------------------------------------------------------------------------------------------
// Assigns the private data member "lastName" to the value of the string parameter passed through 
void Client::setLastName(string input) {
	lastName = input;
}

//--------------------------------------------------------------------------------------------
// Assigns the private data member "firstName" to the value of the string parameter passed through 
void Client::setFirstName(string input) {
	firstName = input;
}

//--------------------------------------------------------------------------------------------
// Assigns the private data member "accountID" to the value of the int parameter passed through
void Client::setAccountNumber(int input) {
	accountID = input;
}

//--------------------------------------------------------------------------------------------
// Assigns the private data member "overallBalance" to the value of the int parameter passed through 
void Client::setOverallBalance(int input) {
	overallBalance = input;
}
