#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "RSTNode.hpp"
#include "RST.hpp"
#include "BSTIterator.hpp"
#include <utility> // for std::pair
#include "countint.hpp"
#include <cstdlib>
#include <string>

template<typename Data>

class BST {

protected:

  /** Pointer to the root of this BST, or nullptr if the BST is empty */
  BSTNode<Data>* root;

  /** Number of Data items stored in this BST. */
  unsigned int isize;

private:

  /**
   * Private helper function that is called in clear() and ~BST() destructor.
   * Uses post-order recursive algorithm.
   * @param reference of the root node
   */ 
   void postOrderDes(BSTNode<Data>* & p)  {

     if(p != nullptr)  {
       // recursive call to traverse left and right
       postOrderDes(p -> left);
       postOrderDes(p -> right);
       delete p; 
       //set current pointer to null
       p = nullptr;
     }
   }

public:

  /** iterator is an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
   */
  BST() : root(nullptr), isize(0)  {
  }


  /** Default destructor.
   *  It is virtual, to allow appropriate destruction of subclass objects.
   *  Delete every node in this BST.
   * @author Mariya Shilova
   * login: cs100vax
   */ 
  virtual ~BST() {
    // calling clear
    clear();
  }

  /** Insert a Data item in the BST.
   *  Return a pair, with the pair's first member set to an
   *  iterator pointing to either the newly inserted element
   *  or to the equivalent element already in the set.
   *  The pair's second element is set to true
   *  if a new element was inserted or false if an
   *  equivalent element already existed.
   */ 
  virtual std::pair<iterator,bool> insert(const Data& item) {

    bool inserted = true;   // flag if the item is already in the tree
    BSTNode<Data>* node = root; // pointer to the root
    BSTNode<Data>* prevNode = nullptr; // helper pointer
    //BSTIterator<Data>* iter; // iterator for the pair to return
    // locating a place where to put the new node
    // compare item and data in nodes
    while(node != nullptr)  {
      prevNode = node;
      if(item < node->data)
        node = node->left;
      else if(node->data < item) 
        node = node->right;
      else  {
        inserted = false;  // if item is already present, set flag
        //  need to make iterator pointing to this node
        //iter = new BSTIterator<Data>(node);
        BSTIterator<Data> iter(node);
        return std:: make_pair(iter, inserted);
      }
    }
    // if item is not in the tree, insert the new node
    if(inserted)  {
      // if tree is empty, new node is the root
      if(root == nullptr)  {
        root = new BSTNode<Data>(item);
        BSTIterator<Data> iter(root);
        isize++;
        return std:: make_pair(iter, inserted);
      }
      else if(item < prevNode->data)  {
        // make it to be left node
        prevNode->left = new BSTNode<Data>(item);
         // set the parent pointer of new node
        (prevNode->left)->parent = prevNode;
        BSTIterator<Data> iter(prevNode->left);
        isize++;
        return std:: make_pair(iter, inserted);
      }
      else  {
         // make it the right node
        prevNode->right = new BSTNode<Data>(item);
         // set the parent pointer of new node
        (prevNode->right)->parent = prevNode;
        BSTIterator<Data> iter(prevNode->right);
        isize++;
        return std:: make_pair(iter, inserted);
      }
    }
    // if insert did not work, return empty iter and false
    BSTIterator<Data> iter = end();
    return  std:: make_pair(iter, false);
  }


  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or the end
   *  iterator if the item is not in the BST.
   */ 
  iterator find(const Data& item) const {
    BSTNode<Data>* node = root;
    
    while(node != nullptr)  {
      if(!(item < node->data || node->data < item))  {
     // std::cout<<"INCREMENTED COMPARISONS BY 2"<<std::endl;
      //if(item==node->data) {
        // make iterator pointing to this node
        BSTIterator<Data> iter(node);
        return iter;
      }
      else if(item < node->data)  {
    //  std::cout<<"INCREMENTED COMPARISONS BY 1"<<std::endl;
        node = node->left;
      }
      else   {
        node = node->right;
      }
    }
    return end();
  }

  
  /** Return the number of items currently in the BST.
   */ 
  unsigned int size() const {
   return this->isize;
  }

  /** Remove all elements from this BST, and destroy them,
   *  leaving this BST with a size of 0.
   * @author Mariya Shilova
   * login: cs100vax
   */ 
  void clear() {
    if(this->isize>0)  {
      // calls private postOrderDes()
      postOrderDes(root); 
      // set size back to 0
      this->isize = 0;
    }
  }

  /** Return true if the BST is empty, else false.
   */ 
  bool empty() const {
   return isize==0;
  }

  /** Return an iterator pointing to the first item in the BST.
   */ 
  iterator begin() const {

   // start first node at the root
   BSTNode<Data> *first = root;
   // if the tree is empty, iter points to null
   if(first == nullptr)
    return typename BST<Data>::iterator(nullptr);
   // advance first to the left most node  
   // which is  the smallest value in the tree
   while(first->left != nullptr)  {
     // update the root
     first = first->left;
   }
   BSTIterator<Data> iter(first);
   return iter;
  }

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const {
    return typename BST<Data>::iterator(nullptr);
  }
 };


#endif //BST_HPP
