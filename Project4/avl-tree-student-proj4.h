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

}

template<class Base>
void AVLTree<Base>::rebalancePathToRoot(vector<AVLNode<Base> *> const &path)
{

}

#endif