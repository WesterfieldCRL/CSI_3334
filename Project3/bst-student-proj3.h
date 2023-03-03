/* CSI 3334
 * Project 3 -- Tree-Based Encryption
 * Filename: bst-student-proj3.h
 * Student name: Wesley Anastasi
 * version: 1.0
 * 
 * This file contains all the functions for the BSTNode, BST and EncryptionTree classes.
 * The functions implemented in BSTNode are the destructor, printPreorder, minNode, and maxNode.
 * The functions implemented in BST are the insert and remove functions.
 * The functions implemented in EncryptionTree are the encrypt and decrypt functions.
 * BST uses BSTNode for its functions and EncryptionTree inherits from BST.
 * 
 */

#ifndef BST_STUDENT_PROJ3 
#define BST_STUDENT_PROJ3 

#include "bst-prof-proj3.h"

//BSTNode

/**
 * ~BSTNode
 * 
 * Destructor for BSTNode. Deletes the left and right nodes recursively.
 * 
 * Parameters:
 *   none
 * 
 * Return value: none
 */

template <class Base>
BSTNode<Base>::~BSTNode() {
    if (this->left != NULL) {
        delete this->left;
    }
    if (this->right != NULL) {
        delete this->right;
    }
}

/**
 * printPreorder
 * 
 * Prints the tree in preorder. Prints the data of the node, then recursively
 * calls printPreorder on the left node and then the right node with an indent added.
 * 
 * Parameters:
 *   os - output stream to print to
 *   indent - string to indent the tree
 * 
 * Return value: none
 */

template <class Base>
void BSTNode<Base>::printPreorder(ostream &os, string indent) const {
    os << indent << this->data << endl;
    if (this->left != NULL) {
        this->left->printPreorder(os, indent + "  ");
    }
    else {
        os << indent << "  " << "NULL" << endl;
    }
    if (this->right != NULL) {
        this->right->printPreorder(os, indent + "  ");
    }
    else {
        os << indent << "  " << "NULL" << endl;
    }
}

/**
 * minNode
 * 
 * Finds the minimum node in the tree. If the left node is NULL, the current node
 * is the minimum node. If the left node is not NULL, recursively calls minNode
 * on the left node.
 * 
 * Parameters:
 *   none
 * 
 * Return value: pointer to the minimum node
 */

template <class Base>
const BSTNode<Base> *BSTNode<Base>::minNode() const {
    if (this->left == NULL) {
        return this;
    }
    else {
        return this->left->minNode();
    }
}

/**
 * maxNode
 * 
 * Finds the maximum node in the tree. If the right node is NULL, the current node
 * is the maximum node. If the right node is not NULL, recursively calls maxNode
 * on the right node.
 * 
 * Parameters:
 *   none
 * 
 * Return value: pointer to the maximum node
 */

template <class Base>
const BSTNode<Base> *BSTNode<Base>::maxNode() const {
    if (this->right == NULL) {
        return this;
    }
    else {
        return this->right->maxNode();
    }
}

//BST

/**
 * insert
 * 
 * Inserts an item into the tree. If the root is NULL, the item is inserted
 * as the root. If the root is not NULL, a temporary node is created and
 * traverses the tree until it finds a NULL node. The item is then inserted
 * as the left or right node of the temporary node depending on if it is
 * less than or greater than the temporary node.
 * 
 * 
 * Parameters:
 *   item - item to be inserted
 * 
 * Return value: none
 */

template <class Base>
void BST<Base>::insert(const Base &item) {
    bool inserted = false;
    if (this->root == NULL) {
        this->root = new BSTNode<Base>(item);
    }
    else {
        BSTNode<Base> *temp = this->root;
        while (!inserted) {
            if (item < temp->data) {
                if (temp->left != NULL) {
                    temp = temp->left;
                }
                else {
                    temp->left = new BSTNode<Base>(item);
                    inserted = true;
                }
            }
            else {
                if (temp->right != NULL) {
                    temp = temp->right;
                }
                else {
                    temp->right = new BSTNode<Base>(item);
                    inserted = true;
                }
            }
        }
    }
}

/**
 * remove
 * 
 * Removes an item from the tree. First, the item is found in the tree.
 * and then then the item is removed based on the following cases:
 * 1. The item is a leaf
 *    If the parent is NULL, the root is set to NULL.
 *    If the parent is not NULL, then whichever child of the parent is the item
 *    is set to NULL.
 * 2. The item has one child
 *    If the node to be removed is set to its child.
 * 3. The item has two children
 *    The minimum node of the right subtree is found and set to the node to be removed.
 * 
 * Parameters:
 *   item - item to be removed
 * 
 * Return value: none
 */

template <class Base>
void BST<Base>::remove(const Base &item) {
    //find the item
    BSTNode<Base> *toRemove = this->root;
    BSTNode<Base> *parent = NULL;
    while (toRemove != NULL && (toRemove->data < item || item < toRemove->data)) {
        parent = toRemove;
        if (item < toRemove->data) {
            toRemove = toRemove->left;
        }
        else if (toRemove->data < item) {
            toRemove = toRemove->right;
        }
    }
    
    if (toRemove != NULL) {
        //if the item is a leaf
        if (toRemove->left == NULL && toRemove->right == NULL) {
            if (parent == NULL) {
                this->root = NULL;
            }
            else {
                if (parent->left == toRemove) {
                    parent->left = NULL;
                }
                else {
                    parent->right = NULL;
                }
            }
        }
        //if the item has one child
        else if (toRemove->left == NULL || toRemove->right == NULL) {
            BSTNode<Base> *child = NULL;
            if (toRemove->left != NULL) {
                child = toRemove->left;
                toRemove->left = NULL;
            }
            else {
                child = toRemove->right;
                toRemove->right = NULL;
            }
            if (parent->left == toRemove) {
                parent->left = child;
            }
            else {
                parent->right = child;
            }
            child = NULL;
            delete child;
        }
        //if the item has two children
        else {
            BSTNode<Base> *leftMost = toRemove->right;
            BSTNode<Base> *leftMostParent = toRemove;
            while (leftMost->left != NULL) {
                leftMostParent = leftMost;
                leftMost = leftMost->left;
            }
            //if the leftmost node is the right child of the node to be removed
            if (leftMost == toRemove->right) { 
                leftMost->left = toRemove->left;
            }
            //if the leftmost node is not the right child of the node to be removed
            else {
                leftMostParent->left = leftMost->right;
                leftMost->right = toRemove->right;
                leftMost->left = toRemove->left;
            }
            if (parent->left == toRemove) {
                parent->left = leftMost;
            }
            else {
                parent->right = leftMost;
            }
            toRemove->left = toRemove->right = NULL;
            leftMost = NULL;
            leftMostParent = NULL;
            delete leftMost;
            delete leftMostParent;
        }

        //delete pointers

        toRemove = NULL;
        parent = NULL;

        delete parent;
        delete toRemove;
    }
}

/**
 * encrypt
 * 
 * Encrypts an item by finding the item in the tree and returning the path
 * to the item. If the item is not found, the path is set to "?".
 * 
 * Parameters:
 *   item - item to be found
 * 
 * Return value: the path to the item in the form r01 (r is the root, 0 is left, 1 is right)
 */


template <class Base>
string EncryptionTree<Base>::encrypt(const Base &item) const {
    string result = "r";
    bool found = false;
    const BSTNode<Base> *temp = this->root;
    while (temp != NULL) {
        if (item < temp->getData()) {
            result += "0";
            temp = temp->getLeft();
        }
        else if (temp->getData() < item) {
            result += "1";
            temp = temp->getRight();
        }
        else {
            found = true;
            temp = NULL;
        }
    }

    delete temp;

    if (!found) {
        result = "?";
    }

    return result;
}

/**
 * decrypt
 * 
 * Decrypts an item by following the provided path.
 * If the path is invalid, NULL is returned.
 * 
 * Parameters:
 *   path - path to the item in the form r01 (r is the root, 0 is left, 1 is right)
 * 
 * Return value: pointer to the item
 */

template <class Base>
const Base *EncryptionTree<Base>::decrypt(const string &path) const {
    const BSTNode<Base> *temp = this->root;
    int length = path.length();
    for (int i = 1; i < length && temp != NULL; i++) {
        if (path[i] == '0') {
            temp = temp->getLeft();
        }
        else {
            temp = temp->getRight();
        }
    }

    if (temp == NULL) {
        return NULL;
    }
    else {
        return &temp->getData();
    }
}

#endif

