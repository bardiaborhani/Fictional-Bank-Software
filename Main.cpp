//
// Created by Kevin on 11/20/2016.
//
#include "Bank.h"

using namespace std;

int main() {
//    BST bst;
//    Client client1("mickey", "mouse", 1234);
//    Client client2("donald", "duck", 1338);
//    Client client3("minnie", "mouse", 1110);
//
//    bst.insert(client1);
//    bst.insert(client2);
//    bst.insert(client3);
//
//    cout << bst.inorderWalk();

    //BEGIN CORE MAIN - SHOULD NOT BE CHANGED
    Bank bank;
    ifstream clientStream("testdata2.txt");

    bank.readClients(clientStream);

    ifstream transactionStream("testcommand2.txt");
    bank.readTransactions(transactionStream);
    //END CORE MAIN

    cout << bank.output();

}