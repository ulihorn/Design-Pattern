//Name: Xianshi Xie
//Email: xianshi.xie@vanderbilt.edu
#ifndef _Visitor_H
#define _Visitor_H

#include <stdlib.h>
#include "Typedefs.h"

template <typename T>
class Node;

template <typename T>
class Leaf_Node;

template <typename T>
class Composite_Add_Node;

/**
* @class Visitor
* @brief This is abstract class for the visitor pattern that outlines
*        the interface for the visitors.
*/
class Visitor
{
public:
  //dtor needs to be virtual so that subclass get destroied.
  virtual ~Visitor(void) {};
  //visit method
  virtual void visit(const Leaf_Node<char> &node) = 0;
  virtual void visit(const Composite_Add_Node<char> &node) = 0;
  virtual void visit(const Composite_Negate_Node<char> &node) = 0;
  virtual void visit(const Composite_Subtract_Node<char> &node) = 0;
  virtual void visit(const Composite_Multiply_Node<char> &node) = 0;
  virtual void visit(const Composite_Divide_Node<char> &node) = 0;

};

#endif /*_Visitor_H*/