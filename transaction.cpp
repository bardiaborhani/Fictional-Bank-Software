#include <sstream>

#include "transaction.h"

using namespace std;

Transaction::Transaction()
{
	description = "";

	transactionType = 'N';

	amount = NULL;

	firstClientID = NULL;
	firstAccountID = NULL;

	secondClientID = NULL;
	secondAccountID = NULL;
}

/*


Pre-condition:
Post-condition:
*/
bool Transaction::setData(string transaction) { // Sets the transaction data from reading a filestream
	transactionType = transaction[0]; //get the first char of the transaction

	istringstream iss(transaction);
	parsedTransaction = { istream_iterator<string>{iss}, istream_iterator<string>{} };

	if (parsedTransaction.size() != 0) {

		//this is always a given to exist, so it is independent of the cases
		firstClientID = stoi(parsedTransaction[1].substr(0, 4));
		firstAccountID = (parsedTransaction[1][4] - '0');

		switch (parsedTransaction[0][0]) {
		case 'D':
			//continue on to W, they're the same
		case 'W':
			amount = stoi(parsedTransaction[2]);
			break;
		case 'M':
			amount = stoi(parsedTransaction[2]);

			secondClientID = stoi(parsedTransaction[3].substr(0, 4));
			secondAccountID = (parsedTransaction[3][4] - '0');
			break;
		}

		return true;

	}
	else {
		return false;
	}
}

char Transaction::getTransactionType() const
{
	return transactionType;
}

/*


Pre-condition:
Post-condition:
*/
string Transaction::getDescription(void) const { // Returns a string of transaction description
	return description;
}

/*


Pre-condition:
Post-condition:
*/
int Transaction::getAmount(void) const { // Returns an int with transaction amount
	return amount;
}


void Transaction::setFirstClient(Client* client)
{
	firstClient = client;
}

void Transaction::setSecondClient(Client* client)
{
	secondClient = client;
}

bool Transaction::transact()
{
	stringstream ss;
	ss << *this;
	description = ss.str();

	switch (transactionType) { //perform the appropriate action based on the char
	case 'D':
		return depositOrWithdraw();
	case 'W':
		return depositOrWithdraw();
	case 'M':
		return move();
	case 'H':
		history();
		return true;
	default:
		cerr << "an error occurred"; //todo: yeah change this, actual exception here.
		return false;
	}

}

/*


Pre-condition:
Post-condition:
*/
int Transaction::getFirstClientID(void) const { // Returns firstClientID
	return firstClientID;
}

/*


Pre-condition:
Post-condition:
*/
int Transaction::getSecondClientID(void) const { // Returns secondClientID
	return secondClientID;
}

/*


Pre-condition:
Post-condition:
*/
bool Transaction::depositOrWithdraw() {
	//assume that the operation will be a success, which will be true if we
	//deposit, but not necessarily true if we withdraw.
	bool success = true;

	if (transactionType == 'D') {
		firstClient->deposit(firstAccountID, amount, description);
	}
	else if (transactionType == 'W') { //must be withdraw
		success = firstClient->withdraw(firstAccountID, amount, description);
	}
	else {
		//something went very very wrong
		success = false;
	}

	return success;
}

/*


Pre-condition:
Post-condition:
*/
bool Transaction::move() {

	bool success = firstClient->withdraw(firstAccountID, amount, description);
	if (success) secondClient->deposit(secondAccountID, amount, description);

	return success;
}

/*


Pre-condition:
Post-condition:
*/
void Transaction::history() {
	firstClient->displayHistory(description);
	cout << endl;
}

