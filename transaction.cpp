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

	//we must have at least a transaction type and a first client,
	//otherwise there's nothing to do and we categorize this as 'bad data'
	if (parsedTransaction.size() > 1) {

		//this is always a given to exist, so it is independent of the cases.
		//we do check for the correct size of the array and make sure that
		//the Client ID + Account ID is not negative.
		if (parsedTransaction[1].size() == 5 && stoi(parsedTransaction[1]) >= 0) {
			firstClientID = stoi(parsedTransaction[1].substr(0, 4));
			firstAccountID = (parsedTransaction[1][4] - '0');
		}
		else return false;


		switch (parsedTransaction[0][0]) {
		case 'D':

			//continue on to W, they're the same

		case 'W':

			//we don't allow negative amounts to be deposited or withdrawn, cause
			//then customers might scam our bank. that would be bad
			if (stoi(parsedTransaction[2]) >= 0) {
				amount = abs(stoi(parsedTransaction[2]));
			}
			else return false;

			break;

		case 'M':

			//as stated in case 'W'
			if (stoi(parsedTransaction[2]) >= 0) {
				amount = abs(stoi(parsedTransaction[2]));
			}
			else return false;

			//check for the correct size of the array and make sure that
			//the Client ID + Account ID is not negative.
			if (parsedTransaction[3].size() == 5 && stoi(parsedTransaction[3]) >= 0) {
				secondClientID = abs(stoi(parsedTransaction[3].substr(0, 4)));
				secondAccountID = abs((parsedTransaction[3][4] - '0'));
			}
			else return false;

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
	if (firstClient != nullptr) {
		stringstream ss;
		ss << *this;
		description = ss.str();
	}
	else {
		description = "clients not loaded into transaction properly";
	}

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
		cerr << "The transaction type '" << transactionType << "' was not recognized" << endl;
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

