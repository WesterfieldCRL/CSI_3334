#ifndef BST_STUDENT_PROJ3 
#define BST_STUDENT_PROJ3 

#include "bst-prof-proj3.h"

/* Place your implementation of the BSTNode, BST, and EncryptionTree classes
 * here.
 *
 * Your driver should #include this file, which (as you can see above) will also
 * #include the professor file.
 */

template <class Base>
BSTNode<Base>::~BSTNode()
{
    if (this->left != NULL)
    {
        delete this->left;
    }
    if (this->right != NULL)
    {
        delete this->right;
    }
}

template <class Base>
void BSTNode<Base>::printPreorder(ostream &os, string indent) const
{
    os << indent << this->data << endl;
    if (this->left != NULL)
    {
        this->left->printPreorder(os, indent + "  ");
    }
    if (this->right != NULL)
    {
        this->right->printPreorder(os, indent + "  ");
    }
}

template <class Base>
const BSTNode<Base> *BSTNode<Base>::minNode() const
{
    BSTNode *temp = this;
    while (temp->left != NULL)
    {
        temp = temp->left;
    }
    return temp;
}

template <class Base>
const BSTNode<Base> *BSTNode<Base>::maxNode() const
{
    BSTNode *temp = this;
    while (temp->right != NULL)
    {
        temp = temp->right;
    }
    return temp;
}

template <class Base>
void BST<Base>::insert(const Base &item)
{

    if (this->root == NULL)
    {
        this->root = new BSTNode<Base>(item);
    }
    else
    {
        BSTNode<Base> temp = this->root;
        while (temp != NULL)
        {
            if (item < temp->data)
            {
                if (temp->left != NULL)
                {
                    temp = temp->left;
                }
                else
                {
                    temp->left = new BSTNode<Base>(item);
                    temp = NULL;
                }
            }
            else
            {
                if (temp->right != NULL)
                {
                    temp = temp->right;
                }
                else
                {
                    temp->right = new BSTNode<Base>(item);
                    temp = NULL;
                }
            }
        }
        delete temp;
    }
}

template <class Base>
void BST<Base>::remove(const Base &item)
{
    //find the item
    BSTNode<Base> *toRemove = this->root;
    BSTNode<Base> *parent = NULL;
    while (toRemove != NULL || toRemove->data != item)
    {
        parent = toRemove;
        if (item < toRemove->data)
        {
            toRemove = toRemove->left;
        }
        else
        {
            toRemove = toRemove->right;
        }
    }
    
    if (toRemove != NULL)
    {
        //if the item is a leaf
        if (toRemove->left == NULL && toRemove->right == NULL)
        {
            if (parent == NULL)
            {
                this->root = NULL;
            }
            else
            {
                if (parent->left == toRemove)
                {
                    parent->left = NULL;
                }
                else
                {
                    parent->right = NULL;
                }
            }
        }
        //if the item has one child
        else if (toRemove->left == NULL || toRemove->right == NULL)
        {

        }
        //if the item has two children
        else
        {

        }

        //delete pointers
        if (parent != NULL)
        {
            delete parent;
        }
        delete toRemove;
    }
}

#endif

