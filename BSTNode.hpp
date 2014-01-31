#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include "countint.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>


/** This class template defines a node type for the BST container.
 *  Note that all members are public. So, the BST implementation should
 *  take care not to expose any BSTNode objects.
 */
template<typename Data>
class BSTNode {

public:

  /** Member variables. */
  BSTNode<Data>* parent;
  BSTNode<Data>* left;
  BSTNode<Data>* right;
  const Data data;  // the const Data in this node
  int info;  // variable used in advanced algorithms 

  /** Constructor.  Initialize a BSTNode with the given Data item,
   *  no parent, and no children.
   */
  BSTNode(const Data & d): data(d) {
    left = right = parent = nullptr;
  }


  /** Return the inorder successor of this BSTNode in a BST,
   *  or nullptr if none.
   *  PRECONDITION: this BSTNode is a node in a BST.
   *  POSTCONDITION:  the BST is unchanged.
   *  RETURNS: the BSTNode that is the inorder successor of this BSTNode,
   *  or nullptr if there is none.
   */ 
  BSTNode<Data>* successor() {

   // temp pointer to the current node
   BSTNode<Data>* temp = this;
   // pointer to the parent of the temp
   BSTNode<Data>* tempPar = temp->parent;
   // traverse only if the current node is not null
   if (temp != nullptr)  {
     
   // CASE 1: there is the right child
     if(temp->right != nullptr)  {
        temp = temp->right; // update current pointer to the right node
        while((temp->left) != nullptr)
          temp = temp->left; // move to the left most node in the tree
        return temp;  // return left most node of the tree or right node
                      // if right node does not have a subtree
     }
     // CASE2: there is no right child
     // do checks if it is the root
     // do checks if it is the left child of its parent
     // do checks if it is the right parent of its parent
     else if(temp->right == nullptr)  {
       // if it is the root return nullptr  
       if(temp->parent == nullptr)  {
         return nullptr;
       }
       // if it is the left child of its parent, there is no right child
       // return the parent
       if (temp == (tempPar->left))  {
         return tempPar;
       }
       // if it is the right child of its parent
       if (temp == (tempPar->right))  {
         // update parent and current pointers until current pointer 
         // becomes the left child of the parent
         // if parent is null, then there is no successor
         while((tempPar->left) != temp) {
           // update the parent and temp
           temp = tempPar;
           tempPar = (tempPar -> parent);
           if(tempPar == nullptr)
             return nullptr;
         } 
         return tempPar;
       }
     }
   }
   return nullptr;
  }

}; 

/** Overload operator<< to insert a BSTNode's fields in an ostream. */
template <typename Data>
std::ostream & operator<<(std::ostream& stm, const BSTNode<Data> & n) {
  stm << '[';
  stm << std::setw(10) << &n;                 // address of the BSTNode
  stm << "; p:" << std::setw(10) << n.parent; // address of its parent
  stm << "; l:" << std::setw(10) << n.left;   // address of its left child
  stm << "; r:" << std::setw(10) << n.right;  // address of its right child
  stm << "; i:" << std::setw(10) << n.info;   // its info field
  stm << "; d:" << n.data;                    // its data field
  stm << ']';
  return stm;
}

#endif // BSTNODE_HPP
