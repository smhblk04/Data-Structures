#ifndef BST_H
#define BST_H
#include <string>
#include <iostream>
#include <vector>
using namespace std;

template<class S, class I>
class  BSTNode
{
public:
    S element;
    I location;
    BSTNode<S, I>* left;
    BSTNode<S, I>* right;

    BSTNode(const S & s, const I & x, BSTNode<S, I>* lt, BSTNode<S, I>* rt):
            element(s), location(x), left(lt), right(rt)//Holding the strings with the ordered values
    {}
};


template<class S, class I>
class BST
{
public:
    explicit BST(const I & notFound);
    ~BST();
    const I & find (const S & s) const;
    void makeEmpty();
    void insert(const S & s, const I & x);
    void remove(const S & s);
    void printTree() const;//-------

private:
    BSTNode<S, I>* root;
    const I ITEM_NOT_FOUND;
    const I & elementAt(BSTNode<S, I>* t) const;
    void insert(const S & s, const I & x, BSTNode<S, I>* & t);
    void printTree(BSTNode<S, I> *t) const;//-------
    void remove(const S & s, BSTNode<S, I>* & t) const;
    BSTNode<S, I>* find(const S & s, BSTNode<S, I>* t) const;
    BSTNode<S, I>* findMin(BSTNode<S, I>* t) const;
    void makeEmpty(BSTNode<S, I>* & t) const;
};

template<class S, class I>
BST<S, I>::BST(const I & notFound): ITEM_NOT_FOUND(notFound), root(NULL) {}

template<class S, class I>
const I & BST<S, I>::elementAt (BSTNode<S, I>* t) const
{
    return t == NULL ? ITEM_NOT_FOUND : t->location;
}

template<class S, class I>
const I & BST<S, I>::find(const S & s) const
{
    return elementAt(find(s, root));
}

template<class S, class I>
BSTNode<S, I>* BST<S, I>::find(const S & s, BSTNode<S, I>* t) const
{
    while(t != NULL)
    {
        if(s < t->element)
        {
            t = t->left;
        }
        else if(s > t->element)
        {
            t = t->right;
        }
        else
        {
            return t;
        }
    }
    return NULL;
}

template<class S, class I>
BSTNode<S, I>* BST<S, I>::findMin(BSTNode<S, I>* t) const
{
    if(t == NULL)
    {
        return NULL; //not found
    }
    while(t != NULL)
    {
        if(t -> left != NULL)
        {
            t = t->left; //has left subtree so iterate to the left
        }
        else
        {
            return t; //no left subtree, so it is the minimum element in BST
        }
    }
}

template<class S, class I>
void BST<S, I>::printTree() const
{
    printTree(root);
}

template<class S, class I>
void BST<S, I>::printTree(BSTNode<S, I> *t) const
{
    if( t != NULL )
    {
        printTree( t->left );
        cout << t->element << " ";
        printTree( t->right );
    }
}

template<class S, class I>
void BST<S, I>::insert(const S & s, const I & x)
{
    insert(s, x, root);
}

template<class S, class I>
void BST<S, I>::insert(const S & s, const I & x, BSTNode<S, I>* & t)
{
    if (t == NULL)					// insert
        t = new BSTNode<S, I>(s, x, NULL, NULL);
    else if (s < t->element)			// continue with left
        insert(s, x, t->left);
    else if (s > t->element)			// continue with right
        insert(s, x, t->right);
    else
        ;						// duplicate
}

template<class S, class I>
void BST<S, I>::remove(const S & s)
{
    remove(s, root);
}

template<class S, class I>
void BST<S, I>::remove(const S & s, BSTNode<S, I>* & t) const
{
    if (t == NULL)
        return;

    if (s < t->element)
        remove(s, t->left);

    else if (s > t->element)
        remove(s, t->right);

    else if (t->left != NULL && t->right != NULL)		// two child
    {
        t->element = findMin(t->right)->element;
        t->location = findMin(t->right)->location;
        remove(t->element, t->right);
    }

    else							// one child
    {
        BSTNode<S, I>* oldNode = t;
        t = (t->left != NULL) ? t->left : t->right;
        delete oldNode;
    }
}

template<class S, class I>
void BST<S, I>::makeEmpty()
{
    makeEmpty(root);
}

template<class S, class I>
void BST<S, I>::makeEmpty(BSTNode<S, I> * & t) const
{//Deleting the tree using post-order traversal
    if (t != NULL)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }

    t = NULL;
}

template<class S, class I>
BST<S, I>::~BST()
{
    makeEmpty();
}
#endif
