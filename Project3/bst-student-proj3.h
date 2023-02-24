#ifndef BST_STUDENT_PROJ3 
#define BST_STUDENT_PROJ3 

#include "bst-prof-proj3.h"

/* Place your implementation of the BSTNode, BST, and EncryptionTree classes
 * here.
 *
 * Your driver should #include this file, which (as you can see above) will also
 * #include the professor file.
 */

//BSTNode

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
    BSTNode<Base> *temp = new BSTNode<Base>(this->data, this->left, this->right);
    while (temp->left != NULL)
    {
        temp = temp->left;
    }
    return temp;
}

template <class Base>
const BSTNode<Base> *BSTNode<Base>::maxNode() const
{
    BSTNode<Base> *temp = new BSTNode<Base>(this->data, this->left, this->right);
    while (temp->right != NULL)
    {
        temp = temp->right;
    }
    return temp;
}

//BST

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
            BSTNode<Base> *child = NULL;
            if (toRemove->left != NULL)
            {
                child = toRemove;
                toRemove->left = NULL;
            }
            else
            {
                child = toRemove;
                toRemove->right = NULL;
            }
            if (parent->left == toRemove)
            {
                parent->left = child;
            }
            else
            {
                parent->right = child;
            }
            delete child;
        }
        //if the item has two children
        else
        {
            BSTNode<Base> *leftMost = toRemove->right;
            BSTNode<Base> *leftMostParent = toRemove;
            while (leftMost->left != NULL)
            {
                leftMostParent = leftMost;
                leftMost = leftMost->left;
            }
            leftMostParent->left = leftMost->right;
            leftMost->right = toRemove->right;
            leftMost->left = toRemove->left;
            if (parent->left == toRemove)
            {
                parent->left = leftMost;
            }
            else
            {
                parent->right = leftMost;
            }
            toRemove->left = toRemove->right = NULL;
            delete toRemove;
        }

        //delete pointers
        if (parent != NULL)
        {
            delete parent;
        }
        delete toRemove;
    }
}

/*template <class Base>
string EncryptionTree<Base>::encrypt(const Base &item) const
{
    
}

template <class Base>
const Base *EncryptionTree<Base>::decrypt(const string &path) const
{

}*/

#endif

