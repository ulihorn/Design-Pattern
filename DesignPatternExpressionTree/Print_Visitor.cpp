//Name: Xianshi Xie
//Email: xianshi.xie@vanderbilt.edu

#if !defined (_Visitor_CPP)
#define _Visitor_CPP

#include "Print_Visitor.h"
#include "Visitor.h"
#include "Node.h"
#include "Typedefs.h"
#include <iostream>


//print out item of Leaf_Node
void Print_Visitor::visit(const Leaf_Node<char> &node)
{
  std::cout << node.item() << " ";
}

//print out item of Composite_Add_Node
void Print_Visitor::visit(const Composite_Add_Node<char> &node)
{
  std::cout << "+" << " ";
}

//print out item of Composite_Subtract_Node
void Print_Visitor::visit(const Composite_Subtract_Node<char> &node)
{
  std::cout << "-" << " ";
}

//print out item of Composite_Negate_Node
void Print_Visitor::visit(const Composite_Negate_Node<char> &node)
{
  std::cout << "-" << " ";
}

//print out item of Composite_Multiply_Node
void Print_Visitor::visit(const Composite_Multiply_Node<char> &node)
{
  std::cout << "*" << " ";
}

//print out item of Composite_Divide_Node
void Print_Visitor::visit(const Composite_Divide_Node<char> &node)
{
  std::cout << "/" << " ";
}

//dtor
Print_Visitor::~Print_Visitor()
{
}


#endif
