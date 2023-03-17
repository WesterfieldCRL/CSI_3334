#ifndef AVL_TREE_STUDENT_PROJ4 
#define AVL_TREE_STUDENT_PROJ4 

#include "avl-tree-prof-proj4.h"
#include <queue>

/* Place your implementation of the AVLNode, AVLNode, and EncryptionTree classes
 * here.
 *
 * Your driver should #include this file, which (as you can see above) will also
 * #include the professor file.
 */

template<class Base>
AVLNode<Base>::~AVLNode()
{
    if (this->left != NULL) {
        delete this->left;
    }
    if (this->right != NULL) {
        delete this->right;
    }
}


template<class Base>
void AVLNode<Base>::printPreorder(ostream &os, string indent) const
{
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

template<class Base>
const AVLNode<Base> *AVLNode<Base>::minNode() const
{
    if (this->left == NULL) {
        return this;
    }
    else {
        return this->left->minNode();
    }
}

template<class Base>
const AVLNode<Base> *AVLNode<Base>::maxNode() const
{
    if (this->right == NULL) {
        return this;
    }
    else {
        return this->right->maxNode();
    }
}

template<class Base>
AVLNode<Base> *AVLNode<Base>::singleRotateLeft()
{
    AVLNode<Base> *rightChild = this->right;
    this->right = rightChild->left;
    rightChild->left = this;
    this->updateHeight();
    rightChild->updateHeight();
    return rightChild;
}

template<class Base>
AVLNode<Base> *AVLNode<Base>::singleRotateRight()
{
    AVLNode<Base> *leftChild = this->left;
    this->left = leftChild->right;
    leftChild->right = this;
    this->updateHeight();
    leftChild->updateHeight();
    return leftChild;
}

template<class Base>
AVLNode<Base> *AVLNode<Base>::doubleRotateLeftRight()
{
    AVLNode<Base> *returnValue = this->left->right;
    this->left->singleRotateLeft();
    this->singleRotateRight();
    return returnValue;
}

template<class Base>
AVLNode<Base> *AVLNode<Base>::doubleRotateRightLeft()
{
    AVLNode<Base> *returnValue = this->right->left;
    this->right->singleRotateRight();
    this->singleRotateLeft();
    return returnValue;
}

template<class Base>
void AVLTree<Base>::insert(const Base &item)
{
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

template<class Base>
void AVLTree<Base>::rebalancePathToRoot(vector<AVLNode<Base> *> const &path)
{   
    for (int i = path.size() - 1; i >= 0; i--) {
        path[i]->updateHeight();
        if (this->root->getHeight(path[i]->left) - this->root->getHeight(path[i]->right) >= 2) {
            if (this->root->getHeight(path[i]->left) >= 1 && this->root->getHeight(path[i]->left->right) < 1) {
                if (i == 0)
                {
                    this->root = path[i]->singleRotateRight();
                }
                else
                {
                    if (path[i-1]->left == path[i])
                    {
                        path[i-1]->left = path[i]->singleRotateRight();
                    }
                    else
                    {
                        path[i-1]->right = path[i]->singleRotateRight();
                    }
                }
            }
            else {
                if (i == 0)
                {
                    this->root = path[i]->doubleRotateLeftRight();
                }
                else
                {
                    if (path[i-1]->left == path[i])
                    {
                        path[i-1]->left = path[i]->doubleRotateLeftRight();
                    }
                    else
                    {
                        path[i-1]->right = path[i]->doubleRotateLeftRight();
                    }
                }
            }
        }
        else if (this->root->getHeight(path[i]->left) - this->root->getHeight(path[i]->right) <= -2) {
            if (this->root->getHeight(path[i]->right) >= 1 && this->root->getHeight(path[i]->right->left) < 1) {
                if (i == 0)
                {
                    this->root = path[i]->singleRotateLeft();
                }
                else
                {
                    if (path[i-1]->left == path[i])
                    {
                        path[i-1]->left = path[i]->singleRotateLeft();
                    }
                    else
                    {
                        path[i-1]->right = path[i]->singleRotateLeft();
                    }
                }
            }
            else {
                if (i == 0)
                {
                    this->root = path[i]->doubleRotateRightLeft();
                }
                else
                {
                    if (path[i-1]->left == path[i])
                    {
                        path[i-1]->left = path[i]->doubleRotateRightLeft();
                    }
                    else
                    {
                        path[i-1]->right = path[i]->doubleRotateRightLeft();
                    }
                }
            }
        }
    }
}

#endif