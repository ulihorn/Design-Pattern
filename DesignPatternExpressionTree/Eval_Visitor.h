//Name: Xianshi Xie
//Email: xianshi.xie@vanderbilt.edu
#ifndef _Eval_Visitor_H
#define _Eval_Visitor_H

//class Tree_Factory;


#include <stdlib.h>
#include "Typedefs.h"
#include "Visitor.h"


template <typename T>
class Node;



/**
* @class Print_Visitor
* @brief This is sub class for the visitor class and print out the content
*        that the visitor encounters.
*/
class Post_Order_Eval_Visitor : public Visitor
{
public:
  //dtor
  virtual ~Post_Order_Eval_Visitor(void);

  //print out item of Leaf_Node
  virtual void visit(const Leaf_Node<char> &node);

  //print out item of Composite_Add_Node
  virtual void visit(const Composite_Add_Node<char> &node);
  //print out item of Composite_Negate_Node
  virtual void visit(const Composite_Negate_Node<char> &node);
  //print out item of Composite_Subtract_Node
  virtual void visit(const Composite_Subtract_Node<char> &node);
  //print out item of Composite_Multiply_Node
  virtual void visit(const Composite_Multiply_Node<char> &node);
  //print out item of Composite_Divide_Node
  virtual void visit(const Composite_Divide_Node<char> &node);

  int eval_result();

private:
  std::stack<int> eval_;
};

class Pre_Order_Eval_Visitor : public Visitor
{
public:
  //dtor
  virtual ~Pre_Order_Eval_Visitor(void);

  //print out item of Leaf_Node
  virtual void visit(const Leaf_Node<char> &node);

  //print out item of Composite_Add_Node
  virtual void visit(const Composite_Add_Node<char> &node);
  //print out item of Composite_Negate_Node
  virtual void visit(const Composite_Negate_Node<char> &node);
  //print out item of Composite_Subtract_Node
  virtual void visit(const Composite_Subtract_Node<char> &node);
  //print out item of Composite_Multiply_Node
  virtual void visit(const Composite_Multiply_Node<char> &node);
  //print out item of Composite_Divide_Node
  virtual void visit(const Composite_Divide_Node<char> &node);

  int eval_result();

private:
  std::stack<int> eval_;
};

#endif /*_Eval_Visitor_H*/
