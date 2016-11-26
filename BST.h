//
// Created by Kevin on 11/9/2016.
//

#ifndef BST_H
#define BST_H

#include <string>
#include <stdio.h>
#include "Client.h"

using namespace std;

class BST{

    struct Node{
        Client* data;
        Node* right = nullptr;
        Node* left = nullptr;

        Node(Client* d, Node* l, Node* r) : data(d), left(l), right(r){};
    };

public:
    void insert(Client* client);
    int height();
    int size();
    void clear();
    string inorderWalk();
    bool search(int target) const;  //you MUST search before you retrieve in order to know if the tree is empty or not
                                    //as well as whether or not the target Client is in the tree
    Client& retrieve(int target) const;
    ~BST();

private:
    int height(BST::Node* subtree);
    int size(BST::Node* subtree);
    void clear(BST::Node* subtree);
    Node* insert(Client* client, BST::Node* subtree);
    bool search(BST::Node* subtree, int target) const;
    Client& retrieve(BST::Node* subtree, int target) const;
    string inorderWalk(BST::Node* subtree);

    Node* root = nullptr;
};

#endif //BST_H
