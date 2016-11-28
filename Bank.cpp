// ASSUMPTION: The data read in the ifstream that is passed through the readTransactions() function is assumed to be formate correctly (numbers and types of input)

#include <sstream>
#include <iterator>
#include "Bank.h"

using namespace std;

bool Bank::readClients(ifstream& inFile){
    Client* tempClient;
    string store;

    int timesRun = 0;

    if (inFile.is_open()) { //make sure the file is open
        while (inFile >> store) {
            tempClient = new Client;
            timesRun++;
            if(tempClient->setData(store, inFile)) {  //if we successfully create a Client, i.e. there was no bad data

                tree.insert(tempClient); //insert the Client, whom we are assured is composed of good data
            }else{
                return false;
            }

            if (inFile.eof()) break; //if we reach the eof finish the while
        }
    }
    inFile.close(); //close the file - good practice
    return true;
}

bool Bank::readTransactions(ifstream& inFile){
    string store;
    if (inFile.is_open()) { //make sure the file is open
        while (getline(inFile, store)) {
            transactions.push(store);
            if (inFile.eof()) break; //if we reach the eof finish the while
        }
    }
    inFile.close(); //close the file - good practice
    return parseTransactions();
}

bool Bank::parseTransactions(){
    string transaction;
    char transactionType;
    while(!transactions.empty()){ //while we still have transactions to process

        transaction = transactions.front(); //get the next transaction

        transactionType = transaction[0]; //get the first char of the transaction

        istringstream iss(transaction);
        vector<string> parsedTransaction{istream_iterator<string>{iss}, istream_iterator<string>{}}; //todo: error handling, in helper method?

        switch (transactionType) { //perform the appropriate action based on the char
            case 'D' :
                depositOrWithdraw(parsedTransaction, transaction);
                break;
            case 'W' :
                depositOrWithdraw(parsedTransaction, transaction);
                break;
            case 'M' :
                move(parsedTransaction, transaction);
                break;
            case 'H' :
                history(transaction);
                break;
            default :
                cerr << "an error occurred"; //todo: yeah change this, actual exception here.
        }

        transactions.pop(); //todo: should there be error handling here? if so we should pop and not process in whatever case that is
    }
    return true; //todo: do actual returns
}

bool Bank::depositOrWithdraw(const vector<string> parsedTransactions, const string transaction){
    int clientID = stoi(parsedTransactions[1].substr(0, 4)); //todo: do we want to change this to using the parsedTransactions vector for consistency or nah?
    int accountID = (parsedTransactions[1][4] - '0'); //todo: error handling

    int amount = stoi(parsedTransactions[2]);

    bool success;
    success = tree.search(clientID);

    if(success) {
        Client& client = tree.retrieve(clientID);
        if(parsedTransactions[0][0] == 'D'){
            client.deposit(accountID, amount, transaction);
        }else{ //must be withdraw
            client.withdraw(accountID, amount, transaction);
        }
    }
    return success;
}

bool Bank::move(const vector<string> parsedTransactions, const string transaction){
    int clientID1 = stoi(parsedTransactions[1].substr(0, 4));
    int accountID1 = (parsedTransactions[1][4] - '0'); //todo: error handling - should have been done in parseTransactions?

    int amount = stoi(parsedTransactions[2]);

    int clientID2 = stoi(parsedTransactions[3].substr(0, 4));
    int accountID2 = (parsedTransactions[3][4] - '0');

    bool success;
    success = tree.search(clientID1) && tree.search(clientID2);

    if(success) {
        Client& client1 = tree.retrieve(clientID1);
        Client& client2 = tree.retrieve(clientID2);

        success = client1.withdraw(accountID1, amount, transaction);
        if(success) client2.deposit(accountID2, amount, transaction);
    }
    return success;
}

bool Bank::history(const string transaction){
    int clientID = stoi(transaction.substr(2,4));

    bool success;
    success = tree.search(clientID);

    if(success) {
        Client& client = tree.retrieve(clientID);
        client.displayHistory(transaction);
    }
    return success;
}

string Bank::output() {
    return tree.inorderWalk();
}
