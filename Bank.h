#ifndef BANK_H
#define BANK_H

#include <fstream>
#include <iostream>
#include <queue>
#include "BST.h"

class Bank {
public:

	bool readClients(ifstream& inFile);
	bool readTransactions(ifstream& inFile);

    string output(); //todo: remove before submitting

private:

	BST tree;
	queue<string> transactions;
	bool parseTransactions();
	bool depositOrWithdraw(const vector<string> parsedTransactions, const string transaction);
	bool move(const vector<string> parsedTransactions, const string transaction);
	bool history(const string transaction);
};

#endif //BANK_H
