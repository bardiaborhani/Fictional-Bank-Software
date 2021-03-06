#include <sstream>

#include "transaction.h"

using namespace std;


//--------------------------------------------------------------------------------------------
/*

DEFAULT CONSTRUCTOR


Description:

creates a Transaction object with everything defaulted. this method intends that following the creation
of the Transaction object, you then call setData(). otherwise, if you want to work with
a Transaction object with these defaulted values you must handle all exceptions related to NULL ints and empty
strings. if a transaction object is encountered with a non-standard transactionType, such as 'N', it will not be
processed. so if you do not call setData this Transaction will not be processed.


Pre-condition: a Transaction object is needed.

Post-condition: a Transaction object has been created with all member variables defaulted.
*/
Transaction::Transaction()
{
	description = "";

	transactionType = 'N';	// N is not a real transaction type - it is just here to be initialized before reassigned

							// Setting all of these variables to NULL so that they do not contain another value until they are reassigned
	amount = NULL;
	firstClientID = NULL;
	firstAccountID = NULL;
	secondClientID = NULL;
	secondAccountID = NULL;
}

//--------------------------------------------------------------------------------------------
/*

SETDATA


Program Flow:

the first char of the passed string transaction is copied into transactionType as an uppercase char.

a store string is created in order to separate Client IDs and account IDs, which are combined
initially when read in from the ifstream.

the first case that occurs is if the transactionType we just read in is 'H', signalling that it
is a history display operation. in this case all we receive is a Client ID, minus an account ID, as
it prints out all accounts. if this is not the case then we read in the basics of all three other
operations ('D', 'W', 'M'), which is a Client ID, account ID, and an amount. then, if we find that
we have 'M' as the transactionType, which simply means we have a second Client, which we read in.

if all data is good and within bounds, both upper and lower, then we return true to indicate
that all data was set without a problem.

Pre-condition: the passed string transaction contains the data that we want to insert into this Transaction,
properly formatted.

Post-condition: all data member fields that pertain to the transactionType, as well as the transactionType char
itself, have been set.
*/
bool Transaction::setData(const string type, ifstream& inFile) { // Sets the transaction data from reading a filestream

																 //get the first char of the transaction
	transactionType = toupper(type[0]);

	//create a string to temporarily store the 5 digit Client ID + account ID,
	//as we need to separate it into the two.
	string store;

	//first case is if we have a display history operation
	//on our hands
	if (transactionType == 'H') {

		//if we just need to display the history of a client,
		//then all we need to read in is the the client's ID
		inFile >> firstClientID;
	}
	else {

		//read in the first client
		inFile >> store;
		firstClientID = stoi(store.substr(0, store.size() - 1));
		firstAccountID = store[store.size() - 1] - '0';

		//read in the amount
		inFile >> amount;
	}

	if (transactionType == 'M') {

		//if our operation is to move money, we need a second client
		inFile >> store;
		secondClientID = stoi(store.substr(0, store.size() - 1));
		secondAccountID = store[store.size() - 1] - '0';

	}

	//success depends on the correctness and formatting of all the data
	//fields. check all and store in success bool
	bool success = firstClientID < 10000 && firstClientID >= 0 && secondClientID < 10000 &&
		secondClientID >= 0 && amount < 2147483648 && amount >= 0;

	//print an error message if we received any bad data, which
	//will cause us to not store this transaction in BankManager.
	if (!success) cerr << "/////////////////////" << endl << "ERROR: misformatted transaction data:" << endl << endl
		<< "\"" << transactionType << " " << firstClientID << " " << firstAccountID << " " <<
		amount << " " << secondClientID << " " << secondAccountID << "\"" <<
		endl << endl << "please try again with correct data" << endl << "/////////////////////" << endl << endl;

	//return the boolean success of setting the data fields
	//of this object.
	return success;
}

//--------------------------------------------------------------------------------------------
/*
TRANSACT

the overall goal of this function is to perform whatever transaction we are between the
specified clients stored in firstClient and secondClient or on the firstClient alone, depending
on the transactionType char.

the first thing this function does is create an English description of this Transaction for later use
when printing out the completed or pending transactions in BankManager, or displaying the transactions
performed upon a certain Client. this description is created through the use of a stringstream which we
then pipe ourselves into using the operator<< function.

the second part of this function is to switch based on the transactionType char. there are five cases that
can occur. We either deposit, withdraw, or move money, or we display the history of the specified client (stored
in firstClient), or we have not been given a valid transactionType char, and we print that error to the cerr
stream.

Pre-condition: setData should be run before this function.

Post-condition: the char contained in transactionType, or the lack
thereof, has been returned to the user
*/
bool Transaction::transact()
{
	if (firstClient.getClientID() != -1) {
		stringstream ss;
		ss << *this;
		description = ss.str();
	}
	else {
		// if the client has not been read properly in the command data file - cannot identify which client to work on
		description = "clients not loaded into transaction properly";
	}

	switch (transactionType) { //perform the appropriate action based on the char
	case 'D':	// if the transaction type indicates that we need to do a deposit
		return depositOrWithdraw(); // call the depositOrWithdraw function to deposit money
	case 'W': // if the transaction type indicates that we need to do a withdrawal
		return depositOrWithdraw();
	case 'M': // if the transaction type indicates that we need to do a move money from one account to another
		return move();
	case 'H':	// if the transaction type indicates that we need to do display the history of a client
		history();
		return true;
	default:
		// An error is printed if the transaction type is not one of the above - command cannot be completed if transaction
		// type doesnt represent any action
		cerr << "/////////// ERROR: The transaction type '" << transactionType << "' was not recognized   ///////////" << endl << endl;
		return false;
	}

}

//--------------------------------------------------------------------------------------------
/*
DEPOSITORWITHDRAW

this function handles two separate but similar cases, withdraw and deposit. the reason
this function can handle and should handle both cases is due to the fact that their structure
is exactly the same. both deposit and withdraw depend on a Client and an amount, and nothing
more. this method uses the transactionType char to decide which operation to perform.

Pre-condition: none

Post-condition: we either deposited or withdrew, or if we couldn't withdraw, we didn't.
*/
bool Transaction::depositOrWithdraw() {

	//check the transaction type to see if we should withdraw or deposit
	//the given amount.
	if (transactionType == 'D') {

		if (firstClient.getClientID() != -1) {
			//the type of this transaction is deposit, so do that.
			firstClient.deposit(firstAccountID, amount, description);
			return true;
		}
		else return false;

	}

	//the other case is withdraw.
	else if (transactionType == 'W') {

		//otherwise, though we still check, the transaction type must be withdraw.
		bool success = firstClient.withdraw(firstAccountID, amount, description);

		//win or lose, tell the coach what happened.
		return success;
	}
}

//--------------------------------------------------------------------------------------------
/*
MOVE

moves the int amount specified in the data member amount variable from one Client to another.
this is accomplished by attempting to withdraw from the first Client's account and, if successful,
depositing it in the second Client's account. both accounts are specified in firstAccountID and
secondAccountID, respectively. additionally, the description of this Transaction is passed as
the third parameter of the withdraw and deposit methods.

Pre-condition: none

Post-condition: if possible, the correct amount determined by our private amount variable has been moved
from the first Client to the second Client.
*/
bool Transaction::move() {
	bool success = false;

	//check to make sure that we have valid clients on our hands
	if (firstClient.getClientID() != -1 && secondClient.getClientID() != -1) {

		// in order to move money, money from one account must be withdrawed
		// and then deposited into the account the money needs to move intop
		success = firstClient.withdraw(firstAccountID, amount, description);
		if (success) {

			//if the second client is the exact same client as the first
			//one, we're just moving among accounts, not clients.
			//in that case we deposit via firstClient.
			if (firstClient == secondClient) {
				firstClient.deposit(secondAccountID, amount, "-1");

				//for the sake of managing the BST correctly, we update the secondClient
				//so they both share the same account values
				secondClient = firstClient;
			}

			//otherwise we're moving between clients, so deposit into the
			//secondClient's account.
			else {
				secondClient.deposit(secondAccountID, amount, description);
			}

		}
	}

	return success;
}

//--------------------------------------------------------------------------------------------
/*
HISTORY

displays the history of the firstClient data member. this is done by calling the
displayHistory function of firstClient. this action is only carried out if the firstClient
pointer is not == nullptr.

Pre-condition: none

Post-condition: the history of the firstClient has been printed out via the displayHistory method
of that Client.
*/
void Transaction::history() {
	if (firstClient.getClientID() != -1) {
		// displays the clients transaction history
		// by calling the displayHistory function in the client class
		// the functino displays the client's first and last name then prints all the 
		// transactions that were succesfully completed by the client
		firstClient.displayHistory(description);
		cout << endl;
	}
}


//--------------------------------------------------------------------------------------------
/*
GETRANSACTIONTYPE

a simple getter function to return the transactionType char

Pre-condition: none

Post-condition: the char contained in transactionType, or the lack
thereof, has been returned to the user
*/
char Transaction::getTransactionType() const
{
	return transactionType;
}

//--------------------------------------------------------------------------------------------
/*
GETDESCRIPTION

a simple getter function to return the description string

Pre-condition: none

Post-condition: the string stored in description has been returned to the user
*/
string Transaction::getDescription(void) const {

	// Returns a string of transaction description
	return description;

}

//--------------------------------------------------------------------------------------------
/*
GETAMOUNT

a simple getter function to return the amount int

Pre-condition: none

Post-condition: the int contained in the amount data member has been returned to the user
*/
int Transaction::getAmount(void) const {

	// Returns an int with transaction amount
	return amount;

}

//--------------------------------------------------------------------------------------------
/*
SETFIRSTCLIENT

a simple setter function to set the firstClient Client.

Pre-condition: none

Post-condition: the firstClient Client object now points to
a client, or is nullptr, i.e. has been "unpointed"
*/
void Transaction::setFirstClient(const Client& client)
{
	firstClient = client;
}

//--------------------------------------------------------------------------------------------
/*
SETSECONDCLIENT

a simple setter function to set the secondClient Client.

Pre-condition: none

Post-condition: the secondClient Client object now points to
a client, or is nullptr, i.e. has been "unpointed"
*/
void Transaction::setSecondClient(const Client& client)
{
	secondClient = client;
}

Client Transaction::getFirstClient() const
{
	return firstClient;
}

Client Transaction::getSecondClient() const
{
	return secondClient;
}

//--------------------------------------------------------------------------------------------
/*
GETFIRSTCLIENTID

a simple getter function to return the firstClientID int.

Pre-condition: none

Post-condition: the int stored in firstClientID has been returned to the user.
*/
int Transaction::getFirstClientID(void) const { // Returns firstClientID
	return firstClientID;
}

//--------------------------------------------------------------------------------------------
/*
GETSECONDCLIENTID

a simple getter function to return the secondClientID int.

Pre-condition: none

Post-condition: the int stored in secondClientID has been returned to the user.
*/
int Transaction::getSecondClientID(void) const { // Returns secondClientID
	return secondClientID;
}


//--------------------------------------------------------------------------------------------
/*
OPERATOR<<

streams an English translation of a Transaction's function.

Program Flow:

A switch statement based on the transactionType char of transaction decides how this
Transaction should be represented. Then, based on the passed reference to the Transaction
that needs to be displayed, a translation of the operation performed when doing this
Transaction is created and streamed to the referenced ostream stream.

Pre-condition: the passed transaction should have data members that have been filled by setData,
otherwise this method may not print a correct representation of the Transaction,
and formatting errors may occur.

Post-condition: the English representation of transaction has been streamed to the provided
ostream.
*/
ostream & operator<<(ostream & stream, const Transaction& transaction)
{
	switch (transaction.transactionType) {
	case 'D':
		// Prints out a sentence that describes how much money was deposited
		// into a client's account - specifying the account name
		stream << "Deposited $" << transaction.amount << " into " << transaction.firstClient.getFirstName() << " " << transaction.firstClient.getLastName()
			<< "'s " << transaction.firstClient.getAccountName(transaction.firstAccountID) << " account";
		break;
	case 'W':
		// Prints out a sentence that describes how much money was successfully
		// subtracted from the balance of an account (withdrawen)
		// also specifying the accouunt name
		stream << "Withdrew $" << transaction.amount << " from " << transaction.firstClient.getFirstName() << " " << transaction.firstClient.getLastName()
			<< "'s " << transaction.firstClient.getAccountName(transaction.firstAccountID) << " account";
		break;
	case 'M':
		// Prints out a sentence that describes how much money was successfully 
		// moved from one account to another specifying both accounts
		stream << "Moved $" << transaction.amount << " from " << transaction.firstClient.getFirstName() << " " << transaction.firstClient.getLastName()
			<< "'s " << transaction.firstClient.getAccountName(transaction.firstAccountID) << " account and placed it in " << transaction.secondClient.getFirstName() << " "
			<< transaction.secondClient.getLastName() << "'s " << transaction.secondClient.getAccountName(transaction.secondAccountID) << " account";
		break;
	case 'H':
		// Prints out a sentence that describes that the client's transaction history was displayed
		// indicating the client by first and last name
		stream << "Displayed " << transaction.firstClient.getFirstName() << " " << transaction.firstClient.getLastName() << "'s transaction history";
		break;
	default:
		break;
	}

	return stream;
}
