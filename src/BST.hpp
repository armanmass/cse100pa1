//
// BST.hpp
// CSE 100 Project 1
//
// Last modified by Heitor Schueroff on 01/10/2019
//

#ifndef BST_HPP
#define BST_HPP

#include <iostream>

#include "BSTIterator.hpp"
#include "BSTNode.hpp"

using namespace std;

template <typename Data>
class BST {
protected:
    // Pointer to the root of this BST, or 0 if the BST is empty.
    BSTNode<Data> *root;

    // Number of elements stored in this BST.
    unsigned int isize;

    // Height of this BST.
    unsigned int iheight;

public:
    // Define iterator as an aliased typename for BSTIterator<Data>.
    typedef BSTIterator<Data> iterator;

    /** 
     * Default constructor. Initializes an empty BST.
     */
    BST() : root(0), isize(0), iheight(0) {}

    /** 
     * Default destructor. Frees all memory allocated by this BST.
     */
    // 
    virtual ~BST() {
		deleteAll(root); //call helper destructor
    }


    /** 
     * Inserts the given item into this BST.
     *
     * This function should use only the '<' operator when comparing
     * Data items. (do not use ==, >, <=, >=). For the reasoning
     * behind this, see the assignment writeup.
     *
     * Parameters:
     *     item Data item to insert into this BST
     *
     * Returns:
     *     true if the item was inserted as a consequence of calling
     *     this function, false otherwise (e.g. item is a duplicate).
     */
    // 
    virtual bool insert(const Data &item) {
		//create new BSTNode object on heap with n1 pointing to it
		BSTNode<Data>* n1 = new BSTNode<Data>(item);
		//if tree is empty make n1 the root
		if(root == nullptr){
			root = n1;
			isize++;
			iheight = 1;
			return true;
		}
		
		//make curr a pointer to the root and keep count of tree height
		BSTNode<Data>* curr = root;
		unsigned int count = 1;

		//while not fallen off the tree
		while(curr != nullptr){
			count++;
			//check for duplicate
			if(!(curr->data < item) && !(item < curr->data)){
				delete n1;
				return false;
			}
			//if lesser test the two possibles cases
			else if (curr->data < item){
				if(curr->right == nullptr){
					curr->right = n1;
					n1->parent = curr;
					isize++;
                    if(iheight < count)
					    iheight = count;
					return true;
				}
				else{
					curr = curr->right;
				}
			}
			//if greater test two possible cases
			else{
				if(curr->left == nullptr){
					curr->left = n1;
					n1->parent = curr;
					isize++;
                    if(iheight < count)
					    iheight = count;
					return true;
				}
				else{
					curr = curr->left;
				}
			}
		}
		delete n1;
		return false;
	}

    /**
     * Searches for the given item in this BST.
     *
     * This function should use only the '<' operator when comparing
     * Data items. (should not use ==, >, <=, >=). For the reasoning
     * behind this, see the assignment writeup.
     *
     * Parameters:
     *     item Data item to search for in this BST.
     *
     * Returns:
     *     An iterator pointing to the item if found, or pointing 
     *     past the last node in this BST if item is not found.
     */
    // 
    virtual iterator find(const Data &item) const {
	//set pointer to root
	BSTNode<Data>* curr = root;

	//while not fallen off tree compare elements and climb down tree to find element
	//once found return iterator object containing curr pointer to found node
	//if not found return iterator object with null pointer
	while(curr != nullptr){
		if(!(curr->data < item) &&!(item < curr->data)){
			return typename BST<Data>::iterator(curr);
		}
		else if(curr->data < item){
			curr = curr->right;
		}
		else{
			curr = curr->left;
		}
	}
	
        return typename BST<Data>::iterator(0); 
    }

    /** 
     * Returns the number of items currently in the BST.
     */
    // 
    unsigned int size() const {
	return isize;
    }

    /** 
     * Returns the height of this BST.
     */
    // 
    unsigned int height() const {
	return iheight;
    }

    /** 
     * Returns true if this BST is empty, false otherwise.
     */
    // 
    bool empty() const {
	if(isize == 0)
		return true;
	return false;
    }

    /** 
     * Returns an iterator pointing to the first item in the BST (not the root).
     */
    // 
    iterator begin() const {
	//find the left most leaf of the BST which is the first item
	if(root == nullptr)
		return end();
	
	BSTNode<Data>* curr = root;
	while(curr->left != nullptr){
		curr = curr->left;}
	
	return typename BST<Data>::iterator(curr);
    }

    /** 
     * Returns an iterator pointing past the last item in the BST.
     */
    iterator end() const { 
        return typename BST<Data>::iterator(0); 
    }

    /** 
     * Prints the elements in this BST in ascending order.
     */
    void inorder() const { 
        inorder(root); 
    }

private:
    /*
ECTION("adding elements in random order") {
(gdb) next
     * Find the first node in the given subtree with root curr.
     */
    static BSTNode<Data>* first(BSTNode<Data> *curr) {
        if (!curr) return 0;
        while (curr->left) {
            curr = curr->left;
        }
        return curr;
    }

    /* 
     * Do an inorder traversal, printing the data in ascending order.
     *
     * You can achieve an inorder traversal recursively by following 
     * the order below.
     *
     *     recurse left - print node data - recurse right
     */
    // 
    static void inorder(BSTNode<Data> *n) {
	if(n != nullptr){

		if(n->left != nullptr)
			inorder(n->left);

		cout << n->data << endl;

		if(n->right != nullptr)
			inorder(n->right);
	}
    }

    /* 
     * Do a postorder traversal, deleting nodes.
     *
     * You can achieve a postorder traversal recursively by following 
     * the order below.
     *
     *     recurse left - recurse right - delete node
     */
    // 
    static void deleteAll(BSTNode<Data> *n) {
	if(n != nullptr){
		if(n->left != nullptr)
			deleteAll(n->left);
		if(n->right != nullptr)
			deleteAll(n->right);
		
		delete n;
	}
    }

};

#endif  // BST_HPP
