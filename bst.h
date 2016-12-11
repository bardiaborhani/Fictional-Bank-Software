/*
A binary search tree (BST) is created to contain all the clients in the bank. The nodes in the tree each have a pointer to a client object
The tree is ordered from smallest to largest according to the number of the clientID
The BankManager contains the BST 
The driver (main.cpp) passes in an ifstream (that reads the client data file) to the BankManager
The BankManager passes the ifstream to this class' buildTree function 
The function reads the client data file and creates new nodes - creating the tree
The BankManager transact function then uses the tree's retreive functionto find a client  
and the tree's inorderWalk function to display the Client's clientID
*/

#ifndef BST_H
#define BST_H

#include <string>
#include <stdio.h>

#include "client.h"

using namespace std;

class BST {

	struct Node {
		Client* data; // every node contains a pointer to a client containing an clientID of type int
		Node* right = nullptr; // every node has a pointer to two nodes
		Node* left = nullptr;  // each node represents a child node of this node (one for left side and one for right side)

							   // constructor for the node struct- assigns all the members of the struct to what is passed through in the paraeter
		Node(Client* d, Node* l, Node* r) : data(d), left(l), right(r) {};
	};

public:

	//BST(); the class already has a constructor - no need to explicitly create one - noting to initialize
	~BST();

	void insert(Client* client); //inserts a new node into the tree using a pointer to a client to set as the data of the new node
	int height(); // finds the height of the tree - length from bottom-most node to the root
	int size(); // finds number of nodes in tree
	void clear(); // deletes all the nodes in the tree
	void inorderWalk(); // does an inorder walk through the tree displaying all the clients
	bool search(int target) const;  //you MUST search before you retrieve in order to know if the tree is empty or not
									//as well as whether or not the target Client is in the tree
	Client* retrieve(int target) const; // returns a reference to a client that is in the tree
	bool buildTree(ifstream& inFile);   // creates the tree using the txt file that contains all of the clients and their information

private:
	//facade functions for functions above
	// each facade, when first called, passes in the root of the tree
	// then the facades use recursion to traveres through the tree
	int height(BST::Node* subtree);
	int size(BST::Node* subtree);
	void clear(BST::Node* subtree);
	Node* insert(Client* client, BST::Node* subtree);
	bool search(BST::Node* subtree, int target) const;
	Client* retrieve(BST::Node* subtree, int target) const;
	string inorderWalk(BST::Node* subtree);

	Node* root = nullptr;
};

#endif //BST_H
