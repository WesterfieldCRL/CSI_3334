#ifndef AVL_TREE_STUDENT_PROJ4 
#define AVL_TREE_STUDENT_PROJ4 

#include "avl-tree-prof-proj4.h"
#include <queue>

//AVLNode

/**
 * ~AVLNode
 * 
 * Destructor for AVLNode. Deletes the left and right nodes recursively.
 * 
 * Parameters:
 *   none
 * 
 * Return value: none
 */

template<class Base>
AVLNode<Base>::~AVLNode() {
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

template<class Base>
void AVLNode<Base>::printPreorder(ostream &os, string indent) const {
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
 * Returns the node with the minimum value in the tree.
 * 
 * Parameters:
 *   none
 * 
 * Return value: none
 */

template<class Base>
const AVLNode<Base> *AVLNode<Base>::minNode() const {
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
 * Returns the node with the maximum value in the tree.
 * 
 * Parameters:
 *   none
 * 
 * Return value: none
 */

template<class Base>
const AVLNode<Base> *AVLNode<Base>::maxNode() const {
    if (this->right == NULL) {
        return this;
    }
    else {
        return this->right->maxNode();
    }
}

/**
 * singleRotateLeft
 * 
 * Performs a single rotation to the left.
 * 
 * Parameters:
 *   none
 * 
 * Return value: none
 */

template<class Base>
AVLNode<Base> *AVLNode<Base>::singleRotateLeft() {
    AVLNode<Base> *rightChild = this->right;
    this->right = rightChild->left;
    rightChild->left = this;
    this->updateHeight();
    rightChild->updateHeight();
    return rightChild;
}

/**
 * singleRotateRight
 * 
 * Performs a single rotation to the right.
 * 
 * Parameters:
 *   none
 * 
 * Return value: none
 */

template<class Base>
AVLNode<Base> *AVLNode<Base>::singleRotateRight() {
    AVLNode<Base> *leftChild = this->left;
    this->left = leftChild->right;
    leftChild->right = this;
    this->updateHeight();
    leftChild->updateHeight();
    return leftChild;
}

/**
 * doubleRotateLeftRight
 * 
 * Performs a double rotation to the left and then to the right.
 * 
 * Parameters:
 *   none
 * 
 * Return value: none
 */

template<class Base>
AVLNode<Base> *AVLNode<Base>::doubleRotateLeftRight() {
    this->left = this->left->singleRotateLeft();
    return this->singleRotateRight();
}

//AVLTree

/**
 * doubleRotateRightLeft
 * 
 * Performs a double rotation to the right and then to the left.
 * 
 * Parameters:
 *   none
 * 
 * Return value: none
 */

template<class Base>
AVLNode<Base> *AVLNode<Base>::doubleRotateRightLeft() {
    this->right = this->right->singleRotateRight();
    return this->singleRotateLeft();
}

/**
 * insert
 * 
 * Insertes a node into the tree using the provided item as data.
 * Stores the path to the inserted node in a vector and then calls
 * rebalancePathToRoot to rebalance the tree.
 * 
 * Parameters:
 *   item - data to insert into the tree
 * 
 * Return value: none
 */

template<class Base>
void AVLTree<Base>::insert(const Base &item) {
    //insert
    vector<AVLNode<Base> *> path;
    bool inserted = false;
    if (this->root == NULL) {
        this->root = new AVLNode<Base>(item);
    }
    else {
        AVLNode<Base> *temp = this->root;
        path.push_back(temp);
        while (!inserted) {
            if (item < temp->data) {
                if (temp->left != NULL) {
                    temp = temp->left;
                    path.push_back(temp);
                }
                else {
                    temp->left = new AVLNode<Base>(item);
                    inserted = true;
                }
            }
            else if (temp->data < item){
                if (temp->right != NULL) {
                    temp = temp->right;
                    path.push_back(temp);
                }
                else {
                    temp->right = new AVLNode<Base>(item);
                    inserted = true;
                }
            }
            else {
                inserted = true;
            }
        }
        temp = NULL;
        delete temp;
    }

    //rebalance
    this->rebalancePathToRoot(path);
    
}

/**
 * rebalancePathToRoot
 * 
 * Rebalances the tree using the path to the inserted node by calling
 * the appropriate rotation functions.
 * 
 * Parameters:
 *   path - vector containing a path to the root of the tree
 * 
 * Return value: none
 */

template<class Base>
void AVLTree<Base>::rebalancePathToRoot(vector<AVLNode<Base> *> const &path) {   
    for (int i = path.size() - 1; i >= 0; i--) {
        path[i]->updateHeight();
        if (this->root->getHeight(path[i]->left) - 
        this->root->getHeight(path[i]->right) >= 2) {
            if (this->root->getHeight(path[i]->left->left) - 
            this->root->getHeight(path[i]->left->right) >= 0) {
                if (i == 0) {
                    this->root = path[i]->singleRotateRight();
                }
                else {
                    if (path[i-1]->left == path[i]) {
                        path[i-1]->left = path[i]->singleRotateRight();
                    }
                    else {
                        path[i-1]->right = path[i]->singleRotateRight();
                    }
                }
            }
            else {
                if (i == 0) {
                    this->root = path[i]->doubleRotateLeftRight();
                }
                else {
                    if (path[i-1]->left == path[i]) {
                        path[i-1]->left = path[i]->doubleRotateLeftRight();
                    }
                    else {
                        path[i-1]->right = path[i]->doubleRotateLeftRight();
                    }
                }
            }
        }
        else if (this->root->getHeight(path[i]->left) - 
        this->root->getHeight(path[i]->right) <= -2) {
            if (this->root->getHeight(path[i]->right->left) - 
            this->root->getHeight(path[i]->right->right) <= 0) {
                if (i == 0) {
                    this->root = path[i]->singleRotateLeft();
                }
                else {
                    if (path[i-1]->left == path[i]) {
                        path[i-1]->left = path[i]->singleRotateLeft();
                    }
                    else {
                        path[i-1]->right = path[i]->singleRotateLeft();
                    }
                }
            }
            else {
                if (i == 0) {
                    this->root = path[i]->doubleRotateRightLeft();
                }
                else {
                    if (path[i-1]->left == path[i]) {
                        path[i-1]->left = path[i]->doubleRotateRightLeft();
                    }
                    else {
                        path[i-1]->right = path[i]->doubleRotateRightLeft();
                    }
                }
            }
        }
    }
}

/**
 * remove
 * 
 * Removes a node from the tree using the provided item as data.
 * Stores the path to the removed node in a vector and then calls
 * rebalancePathToRoot to rebalance the tree.
 * 
 * Parameters:
 *   item - data to remove from the tree
 * 
 * Return value: none
 */

template<class Base>
void AVLTree<Base>::remove(const Base &item) {
    vector<AVLNode<Base> *> path;
    bool twoChildren = false;
    //find the item
    AVLNode<Base> *toRemove = this->root;
    AVLNode<Base> *parent = NULL;

    while (toRemove != NULL && (toRemove->data < item || item < toRemove->data)) {
        parent = toRemove;
        if (item < toRemove->data) {
            path.push_back(toRemove);
            toRemove = toRemove->left;
        }
        else if (toRemove->data < item) {
            path.push_back(toRemove);
            toRemove = toRemove->right;
        }
    }
    
    if (toRemove != NULL) {
        //if the item is a leaf
        if (toRemove->left == NULL && toRemove->right == NULL) {
            if (parent == NULL) {
                delete this->root;
                this->root = NULL;
            }
            else {
                if (parent->left == toRemove) {
                    delete parent->left;
                    parent->left = NULL;
                }
                else {
                    delete parent->right;
                    parent->right = NULL;
                }
            }
            toRemove = NULL;
            delete toRemove;
        }
        //if the item has one child
        else if (toRemove->left == NULL || toRemove->right == NULL) {
            AVLNode<Base> *child = NULL;
            if (toRemove->left != NULL) {
                child = toRemove->left;
                toRemove->left = NULL;
            }
            else {
                child = toRemove->right;
                toRemove->right = NULL;
            }
            if (parent == NULL) {
                this->root = child;
            }
            else {
                if (parent->left == toRemove) {
                    parent->left = child;
                }
                else {
                    parent->right = child;
                }
            }
            delete toRemove;
        }
        //if the item has two children
        else {
            twoChildren = true;
            AVLNode<Base> *leftMost = toRemove->right;
            AVLNode<Base> *leftMostParent = toRemove;
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
            if (parent == NULL) {
                this->root = leftMost;
            }
            else {
                if (parent->left == toRemove) {
                    parent->left = leftMost;
                }
                else {
                    parent->right = leftMost;
                }
            }
            path.push_back(leftMost);
            if (twoChildren) {
                if (leftMost->right != NULL) {
                    leftMost = leftMost->right;
                    while (leftMost != NULL) {
                        path.push_back(leftMost);
                        leftMost = leftMost->left;
                    }
                }
            }
            toRemove->left = toRemove->right = NULL;
            leftMost = NULL;
            leftMostParent = NULL;
            delete leftMost;
            delete leftMostParent;
            delete toRemove;
        }
    }

    this->rebalancePathToRoot(path);

}

/**
 * printLevelOrder
 * 
 * Prints the tree in level order, outputing NULL for empty nodes.
 * 
 * Parameters:
 *   os - output stream to print to
 * 
 * Return value: none
 */

template<class Base>
void AVLTree<Base>::printLevelOrder(ostream &os) const {
    if (this->root != NULL) {
        queue<AVLNode<Base> *> q;
        int nodesPerLine = 0;
        q.push(this->root);
        while (!q.empty()) {
            AVLNode<Base> *node = q.front();
            q.pop();
            if (node == NULL) {
                os << "NULL";
                if (q.empty()) {
                    break;
                }
            }
            else {
                os << node->data;

                q.push(node->left);
                q.push(node->right);
            }
            nodesPerLine++;
            if (nodesPerLine >= 20) {
                os << endl;
                nodesPerLine = 0;
            }
            else {
                os << " ";
            }
        }
        os << endl;
    }
    else {
        os << "NULL" << endl;
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
    const AVLNode<Base> *temp = this->root;
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
    const AVLNode<Base> *temp = this->root;
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