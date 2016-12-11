#include <sstream>

#include "client.h"

using namespace std;


//--------------------------------------------------------------------------------------------
/*
This default constructor indicates, in order, all the types of accounts the client has
The index of the array indicates which account is looked at
The accounts array will be looked at when transactions are directed depost or withdraw an amount from the balance of an account

Pre-condition: When an object of this class is created, the default constructor is called if the object created passes in no parameters
Post-condition: The accounts array is initialzied with ten types of accounts
*/
Client::Client() {

	// the client's ten types of accounts are ordered in a specific type of way where the first two accounts in the array are 
	// money market accounts and the two following are the two types of bond accounts. 
	// The other six accounts are normal types of accounts
	// We order it in this way so we know where the money market and bond accounts are in the array so we can later call them
	accounts = { moneyMarket, primeMoneyMarket, longTerm, shortTerm,
				indexFund, capitalValueFund, growthEquityFund, growthIndexFund,
				valueFund, valueStockIndex };	

}

//--------------------------------------------------------------------------------------------
/*
This constructor intakes two strings and an int
the first parameter indicates what the first name of the client should be
the second parameter indicates what the last name of the client should be
the third parameter indicates what the clientID of the client should be

Pre-condition: this constructor is called when three parameters are passed into the parameter when a new client object is made
The parameters must properly intake the information about the client - which is found in the client data file

Post-condition: The firstName, lastName, and clientID variables now have a value
*/
Client::Client(string first, string last, int ID) {

	Client();	// calls the default constructor to initiliaze the accounts array

	firstName = first; // set the first name of the client according to the first parameter passed into the function
	lastName = last;	// set the last name of the client according to the second parameter passed into the function
	clientID = ID;	// set the clientID of the client according to the third parameter passed into the function
}

//--------------------------------------------------------------------------------------------
/*
The overloaded output stream operator function tells the client what to display when the bankManager wants to display a client using <<
The driver calls the displayClients function within the bankManager and that function calls the inorderWalk function within the BST
the inorderWalk function outputs all the clients objects located in the BST (which contains all the clients in the bank)
This function inputs the information about the client int a stringstream then the stringstream is inputted into the ostream variable
which at the end of the function is returned

Pre-condition: Two parameters are passed into the function - the ostream variable to store and return what needs to be outputted 
and the client whose information is sought to be outputted

Post-condition: the ostream variable is returned containing the client's first name, last name, clientID and account balances 
*/
ostream& operator<<(ostream& stream, const Client& client) {

	//create a stringstream
	stringstream ss;

	//stream the client name and ID
	ss << "CLIENT NAME: " << client.firstName << " " << client.lastName << " " << "CLIENT ID: " << client.clientID;


	//stream all the accounts' starting balances
	ss << endl << "STARTING ACCOUNTS:" << endl;
	for (int i = 0; i < 10; i++) ss << " " << client.startingAccounts[i].getAccountBalance();

	//stream all the accounts' ending balances
	ss << endl << "ENDING ACCOUNTS:" << endl;
	for (int i = 0; i < 10; i++) ss << " " << client.accounts[i].getAccountBalance();

	ss << endl;

	//stream the string representation of the ss stringstream to the passed ostream and return the
	//ostream to the calling function for further use.
	stream << ss.str();
	return stream;
}

//--------------------------------------------------------------------------------------------
/*
The setData function intakes a ifstream that reads a line from the client data file
the information from the ifstream is inputted into the variables in the client object
The first parameter contains the last name of the client - so that is set as the client object's lastName variable
Then individually (using the input stream) each string is gives a value to a variable of the client
After the last name, the second thing the in the line of the client data file is the first name of the client
knowing the format of the client data file, we individually give value to the client according to what is stated about the client in the client data file

Pre-condition: a string and ifstream are passed in as parameters - the ifstream reads the client data file and the string contains the last name of the client

Post-condition: The client object now has all the information about the client
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

	// in the line read in the client data file, the next word in the string represents the first name of client
	// and after the first name comes the clientID of the client
	inFile >> firstName >> clientID;	
	
	// after the clientID, the balance of the ten accounts owned by the client are displayed int the client data file
	// we make a for loop to look at each balance and set the balance of each account for the client
	for (int i = 0; i<10; i++) {

		inFile >> accountBalance;

		//if the balance of an account is read as below 0 then there is something wrong about the client data file.
		//accounts should never be below 0
		if (accountBalance < 0) success = false;

		accounts[i].setAccountBalance(accountBalance); // Set the balance of this type of account by passing in the amount that is written in the client data file
		accounts[i].setAccountID(i);	// number 0-9 representing the client's type of account- ex. 0 = Money Market account
	}

	//if we successfully created all 10 accounts, then copy those values into the starting
	//accounts array to keep track of the starting values of all the accounts - used when printing this Client.
	if (success) {
		startingAccounts = accounts;
	}

	return clientID >= 0 && success;
}

//--------------------------------------------------------------------------------------------
/*
This function deposists money into one of the client's accounts
In addition, the transaction description is added to the client's transactionHistory queue

Pre-condition: Three parameters are passed into the function. The first is an int representing the clients clientID
the second int represents the amount that must be despoited intothe clientID
the third parameter is a string that represents the transaction that was read from the command data file 

Post-condition: the transactionHistory queue now holds another transaction done by the client
and one of the client's accounts (indicated by the first parameter) has a new balance (according to how much was deposited into the account by the variable "amount")
*/
void Client::deposit(const int clientID, const int amount, const string transaction) {

	// money is depoisted into one of the client's accounts (indiciated by the clientID variable) 
	// the value of the variable is between 0-9 -> it searches for the account in the accounts array that the client has
	accounts[clientID].deposit(amount);

	// the transaction (that indicates that money should be deposited into one the accounts of this client)
	// is added to the client's transactionHistory queue - this is done to keep track of what transactions the client has completed
	transactionHistory.push(transaction); 
}

//--------------------------------------------------------------------------------------------
/*
Money is withdrawen from one of the client's accounts - the balance of one of the client's accounts will drop
The account that money is withdrawed from is indicated by the value of the first parameter "const int clientID"
A bool variable named "success" indicates where the withdraw was able to be processed
Within this function, the account class' withdraw function is called and money is subtracted from the balance of that account

Pre-condition: Three parameters are passed into the function- the first one is a value between 0-9 indiciating which account money 
must be withdrawed fmo - the second one is an int amount (0 or above) that indicates how much money to be subtracted from the balance
and the third parameter is a string that represents the transaction that was read from the command data file  

Post-condition: The function returns a true or false indicating whether the amount sought to be withdraw from an account 
was able to covered by the balance of the account
*/
bool Client::withdraw(const int clientID, const int amount, const string transaction) {
	bool success;

	// if the amount sought to be withdrawed from the account is more money than than the balance contains, then the withdraw is unable
	// to be processed - so success is set to false and returned
	success = accounts[clientID].withdraw(amount, accounts);

	// the transaction (that indicates that money should be withdrawed into one the accounts of this client)
	// is added to the client's transactionHistory queue - this is done to keep track of what transactions the client has completed
	// it is only pushed into the queue if the withdrawel was successful - the balance of the account was enought to cover the amount sought to be withdrawed
	if (success) transactionHistory.push(transaction);

	return success;
}

//--------------------------------------------------------------------------------------------
/*
The transactions completed by the client are displayed in order of when they were completed - the lastest transaction is displayed last
A copy of the transactionHistory is made so transactinos can be popped out of the copied queue and displayed without
changing the original displayHistory queue

Pre-condition: One parameter is passed into the function and it contains the command that was read from the command data file
which told the program to display the client's history
Post-condition: The transactions completed by the client are outputted onto the console
*/
void Client::displayHistory(const string transaction) {

	// a copy of the transactionHistory queue is made for the purpose of popping the transactions (string form) out of the queue 
	// and displaying them one by one without changing the structure of the transactionHistory queue
	queue<string> copy = transactionHistory;	

	// we output the first name and last name of the client whose transaction history is sought to be displayed
	cout << firstName << " " << lastName << "'s history:" << endl;

	//if this client's history is empty to begin
	//with, simply display a statement to that effect.
	if (copy.empty()) {
		cout << firstName << " " << lastName << " has no transaction history" << endl;
	}

	// one by one display the transactions in the copied transaction history queue
	// then pop off the transaction to reveal the next transaction
	// this is done until all the transactions are outputted and the copy queue is empty
	while (!copy.empty()) {
		cout << copy.front() << endl;
		copy.pop();
	}
	 
	// displaying the transaction itself is a transaction - so it is also pushed into the transa
	transactionHistory.push(transaction);	
}

//--------------------------------------------------------------------------------------------
/*
the toString() function returns this client's information
by dereferencing this object

Pre-condition: none
Post-condition: returns a string that shows the client's information
*/
string Client::toString()
{
	stringstream ss;	// create a stringstream variable to contiain the client's info
	ss << *this;	// dereferences the client and puts it into the string stream
	return ss.str();
}

//--------------------------------------------------------------------------------------------
/*
returns the last name of the client

Pre-condition: none
Post-condition: a string is returned containg the client's last name
*/
string Client::getLastName() const {
	return lastName;
}

//--------------------------------------------------------------------------------------------
/*
returns the first name of the client

Pre-condition: none
Post-condition: a string is returned containg the client's first name
*/
string Client::getFirstName() const {
	return firstName;
}

//--------------------------------------------------------------------------------------------
/*
returns the clientID of the client

Pre-condition: none 
Post-condition: an int is returned containing the client's clientID
*/
int Client::getClientID() const {
	return clientID;
}

//--------------------------------------------------------------------------------------------
/*
The function takes in a int parameter and uses that to find one of the client's account
The number is used to look up an account using an index value
returns the type of account that is looked at

Pre-condition: the function takes in an int valued between 0-9 that is used to look up a account in the accounts array
Post-condition: the type of account is returned
*/
string Client::getAccountName(int ID) const
{
	return accounts[ID].getAccountType();
}

//--------------------------------------------------------------------------------------------
/*
returns the overallBalance of all the client's accounts

Pre-condition: none
Post-condition: returns an int with the value of the client's overallBalance
*/
/*
int Client::getOverallBalance() const {
	return overallBalance;
}
*/

//--------------------------------------------------------------------------------------------
/*
Assigns the private data member "lastName" to the value of the string parameter passed through

Pre-condition: a string that is used to be assigned to the client's last name
Post-condition: none
*/
void Client::setLastName(string input) {
	lastName = input;
}

//--------------------------------------------------------------------------------------------
/*
Assigns the private data member "firstName" to the value of the string parameter passed through 

Pre-condition: a string that is used to be assigned to the client's first name
Post-condition: none
*/
void Client::setFirstName(string input) {
	firstName = input;
}

//--------------------------------------------------------------------------------------------
/* 
Assigns the private data member "clientID" to the value of the int parameter passed through

Pre-condition: a int that is used to be assigned to the client's clientID
Post-condition: none
*/
void Client::setClientID(int input) {
	clientID = input;
}

//--------------------------------------------------------------------------------------------
/*
Compares two client objects' account numbers
returns true if the object to the left of the > operator has an clientID that is a larger number
than the clientID of the account object to the right of the operator - false if otherwise

Pre-condition: Passes in the client that is compared to - the client object that is passed through is one
placed to the right side of the operator
Post-condition: Returns true if left object's clientID is larger than the right one's clientID
*/
bool Client::operator>(const Client& toCompare) const {
	return clientID > toCompare.getClientID();
}

//--------------------------------------------------------------------------------------------
/*
Compares two client objects' account numbers
returns true if the object to the left of the < operator has an clientID that is a smaller number
than the clientID of the account object to the right of the operator - false if otherwise

Pre-condition: Passes in the client that is compared to - the client object that is passed through is one
placed to the right side of the operator
Post-condition: Returns true if left object's clientID is smaller than the right one's clientID
*/
bool Client::operator<(const Client& toCompare) const {
	return clientID < toCompare.getClientID();
}

//--------------------------------------------------------------------------------------------
/*
Compares two client objects to see if they have the same clientID
if they have the same clientID then they are the same client

Pre-condition: Passes in the client that is compared to - the client object that is passed through is one
placed to the right side of the operator

Post-condition: returns true if the clients have the same clientID
*/
bool Client::operator==(const Client& toCompare) const {
	return clientID == toCompare.getClientID();
}

//--------------------------------------------------------------------------------------------
/*
Compares two client objects to see if they do not have the same clientID

Pre-condition: Passes in the client that is compared to - the client object that is passed through is one
placed to the right side of the operator

Post-condition: returns true if the clients do not the same clientID
*/
bool Client::operator!=(const Client& toCompare) const {
	return clientID != toCompare.getClientID();
}
