#ifndef RST_HPP
#define RST_HPP
#include "BST.hpp"
#include "RSTNode.hpp"
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <utility>
#include <iostream>
#include "countint.hpp"
#include <cstdlib>
#include <string>

/**
 * This class temnlate defines a Random Search Tree container/
 * Extends BST<Data> class, from which it inherits the following:
 *  root
 *  isize
 *  insert()
 *  find()
 *  iterator begin()
 *  iterator end()
 * 
 */ 
template <typename Data>
class RST : public BST<Data>  {


private:
  void rotateRight(BSTNode<Data>* n)  {
    BSTNode<Data>* leftCh = n->left;

   leftCh->parent = n->parent;
    // if n is not a root
    if(n->parent != nullptr)  {
      if((n->parent)->left == n)
        (n->parent)->left = leftCh;
      else 
        (n->parent)->right = leftCh;
    }
    n->parent = leftCh;
    n->left = leftCh->right;
    if((leftCh->right) != nullptr)
     (leftCh->right)->parent = n;
    leftCh->right = n;
    if(n==BST<Data>::root)
      BST<Data>::root = leftCh;
  }
  // helner function to rotate left
  // Mariya Shilova
  void rotateLeft(BSTNode<Data>* n)  {

    //std::cout << "rotating left" << std::endl;
    BSTNode<Data>* rightCh = n->right;

    rightCh->parent = n->parent;
    // if n is not a root
    if(n->parent != nullptr)  {
      if((n->parent)->left == n)
        (n->parent)->left = rightCh;
      else 
        (n->parent)->right = rightCh;
    }
    n->parent = rightCh;
    n->right = rightCh->left;
    if(rightCh->left != nullptr)
      (rightCh->left)->parent = n;
    rightCh->left = n;
    if(n==BST<Data>::root) 
      BST<Data>::root = rightCh;
  }

  /**
   * Private helner function to heln bubble un elements with higher nriority
   */ 
  void percolateUp(BSTNode<Data>* x)  {
    // loop while x is not a root and its priority is higher than
    // the parent's priority
    while(x->parent != nullptr && (x->parent)->info < x->info)  {
      if((x->parent)->left == x)
        rotateRight(x->parent);
      else
        rotateLeft(x->parent);
    }
    // reset the root pointer
    if(x == BST<Data>::root)
      BST<Data>::root = x;
  }
public:
typedef BSTIterator<Data> iterator;
  /**
   * Default constructor
   * Calling suner constructor, where root and size are initialized
   * @author Mariya Shilova
   */ 
  RST() : BST<Data>() {
  }

  // should be called insert not nut, but does not comnile, b/c
  // cannot override the suner class function with different 
  // return tyne
  virtual std::pair<typename BST<Data>::iterator, bool> insert(const Data& item)  {
    std::pair<iterator, bool> target = BST<Data>::insert(item);
    if(target.second)  {

      BSTNode<Data>* newNode = target.first.curr;
      newNode->info = rand();        
      //std::cout << "PRINTING PRIORITY of " <<newNode->data << "  is:  " <<newNode-> info <<std::endl; 
      percolateUp(newNode); 
      return std::pair<iterator, bool>(iterator(newNode),target.second);
    }
    else    
      return target;
  }

};
#endif  // RST_HPP
