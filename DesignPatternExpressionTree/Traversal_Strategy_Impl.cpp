//Name: Xianshi Xie
//Email: xianshi.xie@vanderbilt.edu

#if !defined (_Traversal_Strategy_Impl_CPP)
#define _Traversal_Strategy_Impl_CPP

#include <iostream>
#include<string>

#include "Traversal_Strategy_Impl.h"
#include "Options.h"
#include "Node.h"
#include "Queue.h"
#include "Typedefs.h"

// Size for the AQueue.
const size_t AQUEUE_SIZE = 80;

// Default ctor - needed for reference counting.
Traversal_Strategy_Impl::Traversal_Strategy_Impl ()
  : use_ (1)
{
}

// This needs to be virtual so that subclasses are correctly destroyed.
Traversal_Strategy_Impl::~Traversal_Strategy_Impl ()
{
}

// Ctor
Level_Order_Traversal_Strategy::Level_Order_Traversal_Strategy ()
  // You fill in here.
  :queue_(make_queue_strategy (Options::instance()->queue_type()))
{
}

// Dtor
Level_Order_Traversal_Strategy::~Level_Order_Traversal_Strategy ()
{
  // auto_ptr takes care of queue deletion
}

// Traverse the tree in level order.
void
Level_Order_Traversal_Strategy::traverse (const TREE &root)
{
  // You fill in here.
  queue_->enqueue(root);
  while (!queue_->is_empty())
  {
    TREE cur = queue_->dequeue();
    std::cout << " " << cur.item();
    if (!cur.left().is_null()) queue_->enqueue(cur.left());
    if (!cur.right().is_null()) queue_->enqueue(cur.right());
  }
}

// A Factory method for creating queues.
QUEUE *
Level_Order_Traversal_Strategy::make_queue_strategy 
(const std::string &queue_type)
{
  // You fill in here.
  
  if (queue_type == "LQueue")
    return  new LQUEUE_ADAPTER(AQUEUE_SIZE);
  else if (queue_type == "AQueue")
    return  new AQUEUE_ADAPTER(AQUEUE_SIZE);
  else
    throw Level_Order_Traversal_Strategy::Unknown_Strategy (queue_type);

}

// Traverse the tree in preorder.
void
Pre_Order_Traversal_Strategy::traverse (const TREE &root)
{
  // You fill in here.  
  if (root.is_null()) return;
  std::cout << " " << root.item() ;
  Pre_Order_Traversal_Strategy::traverse(root.left());
  Pre_Order_Traversal_Strategy::traverse(root.right());
}

// Traverse the tree in postorder.
void
Post_Order_Traversal_Strategy::traverse (const TREE &root)
{
  // You fill in here.
  if (root.is_null()) return;
  
  Post_Order_Traversal_Strategy::traverse(root.left());
  Post_Order_Traversal_Strategy::traverse(root.right());
  std::cout << " " << root.item() ;

}

// Traverse the tree in inorder.
void
In_Order_Traversal_Strategy::traverse (const TREE &root)
{
  // You fill in here.
    if (root.is_null()) return;
    In_Order_Traversal_Strategy::traverse(root.left());
    std::cout << " " << root.item() ;
    In_Order_Traversal_Strategy::traverse(root.right());
}

// Traverse the tree in inorder.
void
Null_Traversal_Strategy::traverse (const TREE &)
{
  // no-op
}

#endif /* _Traversal_Strategy_Impl_CPP */
