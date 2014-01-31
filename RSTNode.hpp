# ifndef RSTNODE_HPP
#define RSTNODE_HPP
#include "BSTNode.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <iomanip>
#include "countint.hpp"

/**
 * This class template defines a node type for the RST container.
 * Extends BSTNode<Data> class, from which it inherits the 
 * following public members: 
 *
 *    BSTNode<Data>* parent
 *    BSTNode<Data>* left
 *    BSTNode<Data>* right
 *    const Data data
 *    int info
 */ 
//declare RST here, so friend declaration below will work
template<typename X> class RST;
template<typename X> class BSTIterator;

template <typename Data>
class RSTNode: public BSTNode<Data>  {

protected:
  // priority variable
  int p;

public :
  
friend class RST<Data>;
friend class BSTIterator<Data>;
  /** 
   * Public constructor
   * calling superclass constructor
   * initializing info, left, right, parent
   */ 
  RSTNode(Data const & d): BSTNode<Data>(d)  {
    this->p = rand();  // generate random priority for the node
  }
};
#endif //RSTNODE_HPP
