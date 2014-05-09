//Name: Xianshi Xie
//Email: xianshi.xie@vanderbilt.edu
#if !defined (_Tree_Iterator_Impl_CPP)
#define _Tree_Iterator_Impl_CPP

#include "Options.h"
#include "Node.h"
#include "Typedefs.h"
#include "Tree.h"
#include "Refcounter.h"
#include <stack>
#include <vector>

// Size for the AQueue.
const size_t AQUEUE_SIZE_IT = 80;


// Default ctor - needed for reference counting.
template <typename T>
Tree_Iterator_Impl<T>::Tree_Iterator_Impl ()
: use_ (1)
{
}


// This needs to be virtual so that subclasses are correctly destroyed.
template <typename T>
Tree_Iterator_Impl<T>::~Tree_Iterator_Impl ()
{
}

//dtor
template <typename T>
Level_Order_Tree_Iterator<T>::~Level_Order_Tree_Iterator(void)
{
  // auto_ptr takes care of queue deletion
}

//copty ctor, used for clone() method
template <typename T>
Level_Order_Tree_Iterator<T>::Level_Order_Tree_Iterator
(const Level_Order_Tree_Iterator<T>& rhs)
:tree_(rhs.tree_),
queue_(make_queue_strategy_ (Options::instance()->queue_type()))
{
  for (size_t i=0;i<queue_->size();++i)
  {
    Tree<T> cur = queue_->dequeue();
    queue_->enqueue(cur);
    rhs.queue_->enqueue(cur);
  }   
}

//ctor 
template <typename T>
Level_Order_Tree_Iterator<T>::Level_Order_Tree_Iterator
(Tree<T> &tree,bool is_end)
:tree_(tree),queue_(make_queue_strategy_ (Options::instance()->queue_type()))
{
  if (!is_end)
    queue_->enqueue(tree);
}

//dereference the iterator, return a pointer that points to current NODE
//in level order
template <typename T>
Tree<T>  Level_Order_Tree_Iterator<T>::operator* (void)
{
  return queue_->front();
}

//dereference the iterator, return a const pointer that points 
//to current NODE in level order
template <typename T>
const Tree<T>  Level_Order_Tree_Iterator<T>::operator* (void) const
{
  return queue_->front();
}

//preincrement
template <typename T>
void Level_Order_Tree_Iterator<T>::operator++ (void)
{
  Tree<T> cur = queue_->dequeue();
  if (!cur.left().is_null()) queue_->enqueue(cur.left());
  if (!cur.right().is_null()) queue_->enqueue(cur.right());
}

//get a new copy of Level_Order_Iterator instance itself
//for post increment of iterator
template <typename T>
Tree_Iterator_Impl<T>* 
Level_Order_Tree_Iterator<T>::clone (void)
{
  return new Level_Order_Tree_Iterator<T>(*this);
}

//factory method to build desired type of queue_
template <typename T>
QUEUE_IT *
Level_Order_Tree_Iterator<T>::make_queue_strategy_ 
(const std::string &queue_type)
{
  // You fill in here.

  if (queue_type == "LQueue")
    return  new LQUEUE_ADAPTER_IT(AQUEUE_SIZE_IT);
  else if (queue_type == "AQueue")
    return  new AQUEUE_ADAPTER_IT(AQUEUE_SIZE_IT);
  else
    throw Unknown_Strategy (queue_type);

}



//check for equality
template <typename T>
bool
Level_Order_Tree_Iterator<T>::operator== 
(const Tree_Iterator_Impl<T> &rhs) const
{
  const Level_Order_Tree_Iterator<T> *temp = 
    dynamic_cast<const Level_Order_Tree_Iterator<T> *>(&rhs);
  if (temp)
  {
    // check if the container we are iterating over has the same
    // root node and that the size of the queues are equal. The
    // latter doesn't truly determine equality. However, this is an
    // easy check for determining most inequalities and it allows us
    // to assume the queue at least has a front node (coupled with
    // the is_empty () function later).

    if (tree_.get_root () == temp->tree_.get_root ()
      && queue_->size () == temp->queue_->size ())
    {
      // check for both being is_empty (special condition)
      if (queue_->is_empty () && temp->queue_->is_empty ())
        return true;

      // check the front's node pointer. If the node pointers
      // are equal, then both iterators are pointing to the same
      // position in the tree.

      if (queue_->front ().get_root() == temp->queue_->front ().get_root())
        return true;
    }
  }

  // either we were trying to compare a non-level order iterator or we
  // were comparing two level order iterators that were obviously at
  // different points in the tree (their queue sizes were different)

  return false;
}



//check for inequality
template <typename T>
bool
Level_Order_Tree_Iterator<T>::operator!= 
(const Tree_Iterator_Impl<T> &rhs) const
{
  return !(*this==rhs);
}






//dtor
template <typename T>
Pre_Order_Tree_Iterator<T>::~Pre_Order_Tree_Iterator(void)
{
}

//ctor 
template <typename T>
Pre_Order_Tree_Iterator<T>::Pre_Order_Tree_Iterator(Tree<T> &tree,bool is_end)
:tree_(tree)
{
  if (!is_end)
    stack_.push(tree);
}

//dereference the iterator, return a pointer that points to current NODE
//in Pre order
template <typename T>
Tree<T>  Pre_Order_Tree_Iterator<T>::operator* (void)
{
  return stack_.top();
}

//dereference the iterator, return a const pointer that points 
//to current NODE in Pre order
template <typename T>
const Tree<T>  Pre_Order_Tree_Iterator<T>::operator* (void) const
{
  return stack_.top();
}

//preincrement
template <typename T>
void Pre_Order_Tree_Iterator<T>::operator++ (void)
{
  Tree<T> cur = stack_.top();
  stack_.pop();
  if (!cur.right().is_null()) stack_.push(cur.right());
  if (!cur.left().is_null()) stack_.push(cur.left());
}

//get a new copy of Pre_Order_Iterator instance itself
//for post increment of iterator
template <typename T>
Tree_Iterator_Impl<T>* 
Pre_Order_Tree_Iterator<T>::clone (void)
{
  return new Pre_Order_Tree_Iterator<T>(*this);
}




//check for equality
template <typename T>
bool
Pre_Order_Tree_Iterator<T>::operator== 
(const Tree_Iterator_Impl<T> &rhs) const
{
  const Pre_Order_Tree_Iterator<T> *temp = 
    dynamic_cast<const Pre_Order_Tree_Iterator<T> *>(&rhs);
  if (temp)
  {
    // check if the container we are iterating over has the same
    // root node and that the size of the queues are equal. The
    // latter doesn't truly determine equality. However, this is an
    // easy check for determining most inequalities and it allows us
    // to assume the queue at least has a front node (coupled with
    // the is_empty () function later).

    // Tree<T> &t1 = const_cast <Tree<T> &>(stack_.top ());

    //Tree<T> &t2 = const_cast <Tree<T> &>(temp->stack_.top ());

    if (tree_.get_root () == temp->tree_.get_root ()
      && stack_.size () == temp->stack_.size ())
    {
      // check for both being is_empty (special condition)
      if (stack_.empty () && temp->stack_.empty ())
        return true;

      // check the front's node pointer. If the node pointers
      // are equal, then both iterators are pointing to the same
      // position in the tree.

      if ( stack_.top ().get_root() == temp->stack_.top ().get_root())
        return true;
    }
  }

  // either we were trying to compare a non-Pre order iterator or we
  // were comparing two Pre order iterators that were obviously at
  // different points in the tree (their queue sizes were different)

  return false;
}

//check for inequality
template <typename T>
bool
Pre_Order_Tree_Iterator<T>::operator!= 
(const Tree_Iterator_Impl<T> &rhs) const
{
  return !(*this==rhs);
}


///below is post_order_iterator

//iterator help func
//  to build a stack where all of the tree nodes are pre-stored.
template <typename T>  void 
Post_Order_Tree_Iterator<T>::traverse_help(Tree<T> cur)
{
  if (cur.is_null()) return;  

  if (!cur.left().is_null()) traverse_help(cur.left());  

  if (!cur.right().is_null()) traverse_help(cur.right());

  vector_.push_back(cur);

}

//dtor
template <typename T>
Post_Order_Tree_Iterator<T>::~Post_Order_Tree_Iterator(void)
{
}


//ctor 
template <typename T>
Post_Order_Tree_Iterator<T>::Post_Order_Tree_Iterator
(Tree<T> &tree,bool is_end)
:tree_(tree)
{
  traverse_help(tree);
  if (is_end)
    pos_ = vector_.size();
  else
    pos_ = 0;
}

//dereference the iterator, return a pointer that points to current NODE
//in Pre order
template <typename T>
Tree<T>  Post_Order_Tree_Iterator<T>::operator* (void)
{
  return vector_.operator [](pos_);
}

//dereference the iterator, return a const pointer that points 
//to current NODE in Pre order
template <typename T>
const Tree<T>  Post_Order_Tree_Iterator<T>::operator* (void) const
{
  return vector_.operator [](pos_);
}

//preincrement
template <typename T>
void Post_Order_Tree_Iterator<T>::operator++ (void)
{
  ++pos_;
}




//get a new copy of Pre_Order_Iterator instance itself
//for post increment of iterator
template <typename T>
Tree_Iterator_Impl<T>* 
Post_Order_Tree_Iterator<T>::clone (void)
{
  return new Post_Order_Tree_Iterator<T>(*this);
}

//check for equality
template <typename T>
bool
Post_Order_Tree_Iterator<T>::operator== 
(const Tree_Iterator_Impl<T> &rhs) const
{
  const Post_Order_Tree_Iterator<T> *temp = 
    dynamic_cast<const Post_Order_Tree_Iterator<T> *>(&rhs);

  if (temp)
  {

    if(tree_.get_root() == temp->tree_.get_root() 
      && pos_ == temp->pos_ && vector_.size() && temp->vector_.size())
    {
      for (size_t i=0;i<vector_.size();++i)
      {
        if ( vector_.operator[](i).get_root() != 
          temp->vector_.operator[](i).get_root() )
          return false;
      }
      return true;
    }

    return false;
  }

  return false;


}

//check for inequality
template <typename T>
bool
Post_Order_Tree_Iterator<T>::operator!= 
(const Tree_Iterator_Impl<T> &rhs) const
{
  return !(*this==rhs);
}

#endif /* _Tree_Iterator_Impl_CPP */
