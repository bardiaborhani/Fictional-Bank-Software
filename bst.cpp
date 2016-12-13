

#include <sstream>

#include "bst.h"




// This destructor calls the clear function which deletes all the nodes in the graph
// The destructor is called when the delete operator is applied to a pointer to the object (delete *p where p is a pointer to this tree)
// OR when the object goes out of scope

//Pre-condition: Constructor has to already have been called (object has to have been made)
//Post-condition: deletes the tree (deletes all the nodes in the tree) -- deletes all the clients
BST::~BST() {
	clear(root);
	root = nullptr;
}

// The clear function deletes all the nodes in the tree
// It calls a facade (that passes in the root of the tree) so it can use recursion to traverse the tree and delete all the nodes

// Pre-condition: the object has to already have been made
// Post-condition: the tree is empty - there are no more nodes
void BST::clear() {
	return clear(root); // facade is created so recursion is able to happen (the function with a parameter can be used for recursion)
}

// This is the facade of the clear function - it passes in a node as a parameter and it uses recursion to traverse the tree and delete all the nodes
// The root is passed in as the parameter when the function is first called - if the root isn't empty then the left and right side of the tree are deleted as well as the root
// The pointer to the data and the node are what is deleted -- all the clients are deleted
// If the root is null (has no data as well as no left and right nodes) then nothing happens - the if loop is skipped and the end of the function is reached

// Pre-condition: The root of the tree is passed in as a parameter - it can have a value or it can be null - either way it is okay
// Post-condition: All the pointers to data and nodes are deleted -- all the clients are deleted from the tree
void BST::clear(BST::Node* subtree) {
	if (subtree != nullptr) {	// if the subtree isn't empty then go through the tree and delete what is there
		clear(subtree->right);	// traverse the right side of the tree
		clear(subtree->left);	// traverse the left side of the tree
		delete subtree;		// delete all the nodes
		subtree = nullptr;
	}
}

// This finds the height of the tree and returns a number representing the height of the tree
// This function uses a facade to be able to use recursion to traverse through the list

// Pre-condition: The object has to be already made
// Post-condition: The facade is called and a int is returned representing the height of the tree
int BST::height() {
	return height(root);
}

// This facade takes in a node - starting with the root- and traverses the tree using recursion
// The tree steps through the nodes of the tree down until it reaches the leaf node
// As it goes down, it counts the number of times it goes down - keeping track of the height of the tree

// Pre-condition: A pointer to a node is passed into the parameter - doesn't have to have any value - can be set to null
// Post-condition: An int is returned representing the height of the tree
int BST::height(BST::Node* subtree) {
	// The height of a tree is the length of the path from the root to the deepest node in the tree. 
	// A (rooted) tree with only a node (the root) has a height of zero
	// The height of a binary search tree is equal to number of layers - 1

	// the base case returns a 0 and is called when the node being looked at is null (has no data and left and right nodes)
	// this happens when the traversal reaches the bottom of the tree (tries to go further down from a leaf)
	// the else statement traverses through the tree an adds 1 to what is returned indicating how far (height) the node is down the tree
	// the max function indicates which height of which side of the parent node is longer - the longest one is returned
	return subtree == nullptr ? 0 : 1 + max(height(subtree->left), height(subtree->right));

	// Alternative way of writing the code above	
	/* if(subtree == nullptr){
	return 0;
	} else {
	return 1 + max(height(subtree->left), height(subtree->right));
	}
	*/
}

// This function calls a facade that returns an int indicating the number of nodes in the tree
// The facade function passes in the root of the tree so it can start there before traversing through the tree

// Pre-condition: A object has to be created for this class
// Post-condition: An int is returned indicating the number of nodes in the tree
int BST::size() {
	return size(root);
}

// This facade for the size function passes in a node pointer (starting with the root node) and traverses the tree
// A base case is created to stop the traversal once a subtree represents a pointer to a node that is set to null (has no data and child nodes)
// As the tree is traversed - int 1 is returned as every node is reached - this indicates how many nodes are in the tree
// After the tree is tranversed, an int is returned indicating the number of nodes in the tree
// In this case, it indicates the number of clients in our bankman manager

// Pre-condition: Object for class has to be made - root of the tree is passed through as the parameter
// Post-condition: An int is retuned indicating the number of nodes (clients) in the tree
int BST::size(BST::Node* subtree) {
	// the base case returns a 0 and is called when the node being looked at is null (has no data and left and right nodes)
	// this happens when the traversal reaches the past a leaf node
	// the else statement traverses through the tree an adds 1 every time it touches a new node
	// the number of nodes on the left side and right side of the tree are added together with the root to find the number of nodes (clients) in the tree
	return subtree == nullptr ? 0 : 1 + size(subtree->left) + size(subtree->right);

	// Alternative way of writing the code above	
	/* if(subtree == nullptr){
	return 0;
	} else {
	return 1 + size(subtree->left) + size(subtree->right);
	}
	*/
}


// This insert function inserts a new node (new client) into the tree 
// This function calls a facade that passes in the client (information for the new node) and the root of the tree
// These are passed through so the facade can traverse recursively through the tree

// Pre-condition: A pointer to a client object must be passed through this function
// Post-condition: The pointer to the client object is inserted into the tree and the root of the tree is set to what the facade returns
// indicating if there is a new root or if the root is the same
void BST::insert(Client client) {
	root = insert(client, root);	// the facade returns a pointer to a node representing the root of the tree
};
 
// The insert function facade passes in a pointer to a clident object and the root of the tree
// The function uses recursion to traverse through the tree and insert the client pointer into the tree
// Once the leaf of the binary search tree is reached, a new node is created as a child to that leaf node and it contains the data of the client pointer

// Pre-condition: A pointer to a client object and a pointer to the root of the tree is passed into the function when it is first called
// Post-condition: The pointer to the client object is inserted into the tree and the root of the tree is returned
BST::Node* BST::insert(Client client, BST::Node* subtree) {
	if (subtree == nullptr) { // base case - a new node object is allocated and set as the subtree
		subtree = new Node(client, nullptr, nullptr);
	}
	else if (client < subtree->data) {
		// if the client's account number is less than the account number of the client node being looked at, 
		// then traverse through the left side of the parent node until you reach a leaf node to then reach the base case
		// the left child of the subtree is assigned to what the recursive call returns - this keeps the tree intact
		// and when the node is inserted - this makes sure that the parent node is contected to this child node (the new node that is inserted) 
		subtree->left = insert(client, subtree->left);
	}
	else {
		// if the client's account number is more than the account number of the client node being looked at, 
		// then traverse through the right side of the parent node until you reach a leaf node to then reach the base case
		subtree->right = insert(client, subtree->right);
	}
	return subtree;
}

// Searches through the tree to find a node that contains data that matches the int passed into the function
// this function calls a facade that, in addition to the int parameter, takes in another parameter of type node 
// That parameter represents the root of the function - the facade is created to be able to use recursion to search the tree

// Pre-condition: A int, named "target", is passed into the parameter representing the clientID for the client trying to be found
// Post-condition: A bool is returned (true or false) indicating whether or not the node was found in the tree
// Search is created to be used in the retrieve function to see if the client wanting to be retreived is in the tree
bool BST::search(int target) const {
	return search(root, target);	// facade is called passing in the clientID and the root of the tree
}

// The search function traverses through the tree trying to find a node whose client data matches the clientID represented by the int "target"
// once a node is found whose data matches "target" then true is returned - if not then false is returned
// If the end of the tree is reached and no matches have been found then false is returned

// Pre-condition:A int, named "target", is passed into the parameter representing the clientID for the client trying to be found
// and the root of the tree is passed into the parameter - the root and the tree do not need to have any information
// the object for the tree does however need to be made before this function is called
// Post-condition: A bool is returned (true or false) indicating whether or not the node was found in the tree
bool BST::search(BST::Node* subtree, int target) const {
	if (subtree == nullptr) { // base case - if the pointer is pointing to a node that doesn't have any information - go back up the list
		return false;
	}
	if (subtree->data.getClientID() == target) {
		return true;	// if the node has the account id that matches the node then it has been found and true is returned
	}
	else if (target > subtree->data.getClientID()) {
		return search(subtree->right, target);
		// look at the right side of the parent node for the node if the target number is
		// bigger than the account id of the parent node (parent client node)
	}
	else {
		return search(subtree->left, target); // otherwise, look at the left side of the parent node for the node
	}
}

// The retreive function traverses through the tree
// and finds a client node whose clientID matches int target that is passed through the parameter
// This function calls the facade that allows the function to use recursion to traverse through the tree

// Pre-condition: Passes in an int target that represents the clientID of a client (data of one of the nodes)
// Post-condition: returns a reference to the data of the node that matches the value of the int target
Client BST::retrieve(int target) const {
	Client client = retrieve(root, target);
	if (client.getClientID() == -1) cerr << "/////////// ERROR: Unable to find the specified client with the ID of: " << target << "   ///////////" << endl << endl;
	return client;
}

// The function traverses the tree and finds the client node that has the clientID that matches the number held by "int target"
// If it is found then the reference of the client that has the clientID that matches int target is returned

// Pre-condition: Passes in a node, representing the root of the tree, 
// and a int called target that contains a number matching the value of the accountId of a client
// Post-condition: A reference to the client that contains the clientID matching the int target is returned
Client BST::retrieve(BST::Node* subtree, int target) const {

	if (subtree == nullptr) {	// if we find an empty leaf
		Client ret;
		return ret;	// then return nullptr
	}
	else if (subtree->data.getClientID() == target) {	// if we found the node that contains the client whose clientID matches that int specfied by the parameter...
		return subtree->data;	//.. then we need to return a pointer to that client (we are "retriving" the client)
	}
	else if (target > subtree->data.getClientID()) {	// traverse the right side of the parent node if the node's client clientID is smaller than the number indicated by "target"
		return retrieve(subtree->right, target);	
	}
	else if (target < subtree->data.getClientID()) { // traverse the left side of the parent node if the node's client clientID is bigger than the number indicated by "target"
		return retrieve(subtree->left, target);
	}
}

// Walks through the list in the style of an inorderWalk
// Displays the left child then the parent node then the right child - starting with the root node

// Pre-condition: The object for the BST needs to be made
// Post-condition: Returns the data of the nodes (the client clientID)
void BST::inorderWalk() {
	cout << inorderWalk(root);	// call the facade down below
}

// Uses a stringstream to store all of the data of the nodes (the client clientID) as it does an inorder walk though the tree
// The facade uses recursion to walk through the tree
// Does an in-order walk through the tree

// Pre-condition: Takes in a pointer to the root node (the top client in the tree)
// Post-condition: Returns a string containting the clientID of all the clients displaying the left child node then the parent node then the right child node
string BST::inorderWalk(BST::Node* subtree) {
	string retVal = "";
	stringstream ss;
	if (subtree != nullptr) {
		ss << inorderWalk(subtree->left);	// traverse through left side of tree
		// the client pointer contained by the node in the tree is dereferenced 
		// and the stringstream intakes the clientID of the client
		ss << subtree->data << endl;	
		ss << inorderWalk(subtree->right);	// traverse through right side of tree
	}
	return ss.str();
}

// this function is called by the readClients function inside the BankManager class in BankManager.cpp
// It intakes the file stream that reads the text file that contains information about clients and their information
// The information from every line in the text is information to store in a Client class (information about each client)
// Memory is allocated for a Client and information from the file is passed into the Client class using the client pointer
//
// Pre-condition: File stream is passed through parameter that reads the text file that contains information about clients and their information
// Post-condition: bool is returned indicating if the tree was successfully built or not
bool BST::buildTree(ifstream& inFile) {   // creates the tree using the txt file that contains all of the clients and their information
	Client tempClient;	// decalre a pointer to a new Client but do not initialize yet

	string store;

	if (inFile.is_open()) {	// check if the file that the ifstream is reading is opened
		while (inFile >> store) { // store the last name of the client into the variable store - later passed onto the Client's setData function
			if (tempClient.setData(store, inFile)) {  //if we successfully create a Client, i.e. there was no bad data
				if (!search(tempClient.getClientID())) {
					insert(tempClient); //insert the Client, whom we are assured is composed of good data
				}
				else {
					cerr << "//////////////////// " << endl << "duplicate client ID: " << tempClient.getClientID()
						<< endl << "//////////////////" << endl << endl;
				}
			}
			else {
				cerr << "//////////////////// " << endl << "did not insert \"" << store << "\""
					<< endl << "//////////////////" << endl << endl;
			}

			if (inFile.eof()) break; //if we reach the eof finish the while
		}
	}
	else {
		// end the program if the file that is meant to be read cannot be opened
		// If the file can't be opened then we cannot make new clients
		cerr << "unable to open the clients file" << endl;
		return false;
	}

	return true;
}
