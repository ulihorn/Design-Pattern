//Name: Xianshi Xie
//Email: xianshi.xie@vanderbilt.edu

#if !defined (_Tree_Factory_Impl_CPP)
#define _Tree_Factory_Impl_CPP

#include "Tree_Factory_Impl.h"
#include "Traversal_Strategy_Impl.h"

// Tree_Factory_Impl Constructor.
Tree_Factory_Impl::Tree_Factory_Impl ()
  // You fill in here.
  :use_(1)
{
}

// Tree_Factory_Impl Destructor.
Tree_Factory_Impl::~Tree_Factory_Impl ()
{
}

// Constructor.
Binary_Tree_Factory_Impl::Binary_Tree_Factory_Impl ()
{
}

// Destructor
Binary_Tree_Factory_Impl::~Binary_Tree_Factory_Impl (void)
{
}

// Constructor.
Traversal_Strategy
Binary_Tree_Factory_Impl::make_traversal_strategy (const std::string &name)
{
  Traversal_Strategy_Impl* strategy_impl;
  // You fill in here.
  if (name == std::string("Level"))
    strategy_impl = new Level_Order_Traversal_Strategy;
  else if (name == std::string("Preorder"))
    strategy_impl = new Pre_Order_Traversal_Strategy;
  else if (name == std::string("Postorder"))
    strategy_impl = new Post_Order_Traversal_Strategy;
  else if (name == std::string("Inorder"))
    strategy_impl = new In_Order_Traversal_Strategy;

  /*Doug's comment:
  Make sure to handle the case where name != any of the traversal
  strategies (hint, that's what Null_Traversal_Strategy is used for).
  */

  else
    strategy_impl = new Null_Traversal_Strategy;

  return Traversal_Strategy(strategy_impl);

}

// Create the binary tree.
TREE
Binary_Tree_Factory_Impl::make_tree ()
{
  /*
  NODE *t1 = new NODE ('1');
  NODE *t2 = new NODE ('5');
  NODE *t3 = new NODE ('+', t1, t2);
  NODE *t4 = new NODE ('7');
  NODE *t5 = new NODE ('9');
  NODE *t6 = new NODE ('-', t4, t5); 
  TREE tree = TREE ('*', t3, t6);
  */
  NODE *t1 = new LEAF_NODE('2');
  NODE *t2 = new LEAF_NODE('5');
  NODE *t3 = new COMPOSITE_ADD_NODE(t1, t2);
  NODE *t4 = new LEAF_NODE ('7');
  NODE *t5 = new LEAF_NODE ('9');
  NODE *t6 = new COMPOSITE_SUBTRACT_NODE (t4, t5);
  NODE *t7 = new COMPOSITE_MULTIPLY_NODE (t3, t6); 

  TREE tree = TREE(t7);
  return tree;
}

#endif /* _Tree_Factory_Impl_CPP */
