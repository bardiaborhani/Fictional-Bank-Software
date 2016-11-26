#include "BST.h"
#include <sstream>

BST::~BST(){
    clear(root);
}

void BST::clear(){ return clear(root);}

void BST::clear(BST::Node* subtree){
    if(subtree!= nullptr){
        clear(subtree->right);
        clear(subtree->left);
		delete subtree->data;
        delete subtree;
    }
}

int BST::height(){return height(root);}

int BST::height(BST::Node* subtree){
    return subtree == nullptr ? 0 : 1 + max(height(subtree->left), height(subtree->right));
}

int BST::size(){ return size(root);}

int BST::size(BST::Node* subtree){
    return subtree == nullptr ? 0 : 1 + size(subtree->left) + size(subtree->right);
}

void BST::insert(Client* client){
    root = insert(client, root);
};

BST::Node* BST::insert(Client* client, BST::Node* subtree) {
    if(subtree == nullptr) subtree = new Node(client, nullptr, nullptr);
    else if(*client < *subtree->data) subtree->left = insert(client, subtree->left);
    else subtree->right = insert(client, subtree->right);
    return subtree;
}

bool BST::search(int target) const {
    return search(root, target);
}

bool BST::search(BST::Node* subtree, int target) const {
    if (subtree == nullptr) {
        return false;
    }

    if (subtree->data->getAccountNumber() == target) {
        return true;
    } else if (target > subtree->data->getAccountNumber()) {
        return search(subtree->right, target);
    } else {
        return search(subtree->left, target);
    }
}

Client& BST::retrieve(int target) const {
    return retrieve(root, target);
}

Client& BST::retrieve(BST::Node* subtree, int target) const {
    if (subtree->data->getAccountNumber() == target) {
        return *subtree->data;
    } else if (target > subtree->data->getAccountNumber()) {
        return retrieve(subtree->right, target);
    } else {
        return retrieve(subtree->left, target);
    }
}

string BST::inorderWalk(){
    return inorderWalk(root);
}

string BST::inorderWalk(BST::Node* subtree) {
    string retVal = "";
    stringstream ss;
    if(subtree != nullptr){
        ss << inorderWalk(subtree->left);
        ss << *subtree->data;
        ss << inorderWalk(subtree->right);
    }
    return ss.str();
}
