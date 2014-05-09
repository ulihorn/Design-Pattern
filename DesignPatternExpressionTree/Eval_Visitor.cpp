//Name: Xianshi Xie
//Email: xianshi.xie@vanderbilt.edu

#if !defined (_Eval_Visitor_CPP)
#define _Eval_Visitor_CPP

#include "Eval_Visitor.h"
#include "Visitor.h"
#include "Node.h"
#include "Typedefs.h"
#include <iostream>


//Evaluating action of  Leaf_Node
void Post_Order_Eval_Visitor::visit(const Leaf_Node<char> &node)
{
  eval_.push(node.item());
}

//Evaluating action of  Composite_Add_Node
void Post_Order_Eval_Visitor::visit(const Composite_Add_Node<char> &node)
{
  int top1 = eval_.top();
  eval_.pop();
  int top2 = eval_.top();
  eval_.pop();
  eval_.push(top1+top2);
}

//Evaluating action of  Composite_Subtract_Node
void Post_Order_Eval_Visitor::visit(const Composite_Subtract_Node<char> &node)
{
  int top1 = eval_.top();
  eval_.pop();
  int top2 = eval_.top();
  eval_.pop();
  eval_.push(top2-top1);
}

//Evaluating action of  Composite_Negate_Node
void Post_Order_Eval_Visitor::visit(const Composite_Negate_Node<char> &node)
{
  int top1 = eval_.top();
  eval_.pop();
  eval_.push(-top1);
}

//Evaluating action of  Composite_Multiply_Node
void Post_Order_Eval_Visitor::visit(const Composite_Multiply_Node<char> &node)
{
  int top1 = eval_.top();
  eval_.pop();
  int top2 = eval_.top();
  eval_.pop();
  eval_.push(top1*top2);
}

//Evaluating action of  Composite_Divide_Node
void Post_Order_Eval_Visitor::visit(const Composite_Divide_Node<char> &node)
{
  int top1 = eval_.top();
  eval_.pop();
  int top2 = eval_.top();
  eval_.pop();
  eval_.push(top2/top1);
}

//dtor
Post_Order_Eval_Visitor::~Post_Order_Eval_Visitor()
{
}

// get the evaluation result.
int 
Post_Order_Eval_Visitor::eval_result()
{
  return eval_.top();
}


////Below is Pre_Order_Eval_Visitor

//Doug's Comment: I'm not sure if this is the right logic for pre_order eval.
//My response: The logic should be correct that can be test in the main file.
//             Pre_Order is a little bit different from just reversing 
//             pre_order_iterator and using post_order_eval_visitor.
//             e.g. in post_order_eval_visitor: eval_.push(top2/top1);
//             but in pre_order_eval_visitor: eval_.push(top1/top2);
//             above two are both for Divide_Node
//             Please see my code for details.

//Evaluating action of  Leaf_Node
void Pre_Order_Eval_Visitor::visit(const Leaf_Node<char> &node)
{
  eval_.push(node.item());
}

//Evaluating action of  Composite_Add_Node
void Pre_Order_Eval_Visitor::visit(const Composite_Add_Node<char> &node)
{
  int top1 = eval_.top();
  eval_.pop();
  int top2 = eval_.top();
  eval_.pop();
  eval_.push(top1+top2);
}

//Evaluating action of  Composite_Subtract_Node
void Pre_Order_Eval_Visitor::visit(const Composite_Subtract_Node<char> &node)
{
  int top1 = eval_.top();
  eval_.pop();
  int top2 = eval_.top();
  eval_.pop();
  eval_.push(top1-top2);
}

//Evaluating action of  Composite_Negate_Node
void Pre_Order_Eval_Visitor::visit(const Composite_Negate_Node<char> &node)
{
  int top1 = eval_.top();
  eval_.pop();
  eval_.push(-top1);
}

//Evaluating action of  Composite_Multiply_Node
void Pre_Order_Eval_Visitor::visit(const Composite_Multiply_Node<char> &node)
{
  int top1 = eval_.top();
  eval_.pop();
  int top2 = eval_.top();
  eval_.pop();
  eval_.push(top1*top2);
}

//Evaluating action of  Composite_Divide_Node
void Pre_Order_Eval_Visitor::visit(const Composite_Divide_Node<char> &node)
{
  int top1 = eval_.top();
  eval_.pop();
  int top2 = eval_.top();
  eval_.pop();
  eval_.push(top1/top2);
}

//dtor
Pre_Order_Eval_Visitor::~Pre_Order_Eval_Visitor()
{
}

// get the evaluation result.
int 
Pre_Order_Eval_Visitor::eval_result()
{
  return eval_.top();
}


////Above is Pre_Order_Eval_Visitor


#endif
