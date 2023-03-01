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
    else
    {
        os << indent << "  " << "NULL" << endl;
    }
    if (this->right != NULL)
    {
        this->right->printPreorder(os, indent + "  ");
    }
    else
    {
        os << indent << "  " << "NULL" << endl;
    }
}

template <class Base>
const BSTNode<Base> *BSTNode<Base>::minNode() const
{
    if (this->left == NULL)
    {
        return this;
    }
    else
    {
        return this->left->minNode();
    }
}

template <class Base>
const BSTNode<Base> *BSTNode<Base>::maxNode() const
{
    if (this->right == NULL)
    {
        return this;
    }
    else
    {
        return this->right->maxNode();
    }
}

//BST

template <class Base>
void BST<Base>::insert(const Base &item)
{
    cout << "DEBUG: inserting word \'" << item << "\'" << endl;
    if (this->root == NULL)
    {
        this->root = new BSTNode<Base>(item);
    }
    else
    {
        BSTNode<Base> temp(this->root->data, this->root->left, this->root->right);
        do
        {
            if (item < temp.data)
            {
                if (temp.left != NULL)
                {
                    temp = BSTNode<Base>(temp.left->data, temp.left->left, temp.left->right);
                }
                else
                {
                    temp.left = new BSTNode<Base>(item);
                }
            }
            else
            {
                if (temp.right != NULL)
                {
                    cout << "vibe check" << endl;
                    temp = BSTNode<Base>(temp.right->data, temp.right->left, temp.right->right);
                }
                else
                {
                    temp.right = new BSTNode<Base>(item);
                }
            }
        } while (temp.left != NULL && temp.right != NULL);
    }
}

template <class Base>
void BST<Base>::remove(const Base &item)
{
    //find the item
    BSTNode<Base> *toRemove = new BSTNode<Base>(this->root->data, this->root->left, this->root->right);
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

template <class Base>
string EncryptionTree<Base>::encrypt(const Base &item) const
{
    string result = "r";
    bool found = false;
    const BSTNode<Base> *temp = this->root;
    while (temp != NULL)
    {
        if (item < temp->getData())
        {
            result += "0";
            temp = temp->getLeft();
        }
        else if (item > temp->getData())
        {
            result += "1";
            temp = temp->getRight();
        }
        else
        {
            found = true;
            temp = NULL;
        }
    }

    delete temp;

    if (!found)
    {
        result = "?";
    }

    return result;
}

template <class Base>
const Base *EncryptionTree<Base>::decrypt(const string &path) const
{
    Base data;
    const BSTNode<Base> *temp = this->root;
    for (int i = 1; i < path.length() || temp != NULL; i++)
    {
        if (path[i] == '0')
        {
            temp = temp->getLeft();
        }
        else
        {
            temp = temp->getRight();
        }
    }

    if (temp == NULL)
    {
        return NULL;
    }
    else
    {
        return &temp->getData();
    }
}

#endif

