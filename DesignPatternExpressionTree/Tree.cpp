/* -*- C++ -*- */
#if !defined (_Tree_CPP)
#define _Tree_CPP

#include "Tree.h"
#include "Tree_Iterator.h"
#include "Tree_Iterator_Impl.h"
#include "Print_Visitor.h"
#include "Eval_Visitor.h"

// Default ctor
template <typename T>
Tree<T>::Tree ()
{
}

// Ctor take an underlying Node<T>*.
template <typename T>
Tree<T>::Tree (Node<T> *root, bool count)
  : root_ (root,count)
{    
}



// Ctor taking an item to store.
template <typename T>
Tree<T>::Tree (const T &item)
  : root_ (new Node<T> (item))
{
}

// Ctor taking item and two children.
template <typename T>
Tree<T>::Tree (const T &item, Node<T> *left, Node<T> *right)
  : root_ (new Node<T> (item))
{
  root_->left_ = left;
  root_->right_ = right;
}

// Copy ctor
template <typename T>
Tree<T>::Tree (const Tree &t)
  : root_ (t.root_)
{
}

// Assignment operator
template <typename T>
void
Tree<T>::operator= (const Tree &t)
{
  if (this != &t)
    this->root_ = t.root_;
}

// Dtor
template <typename T>
Tree<T>::~Tree ()
{
}



  ////// Below is what I added.

// return the beginning iterator corresponding to the traversal strategy
template <typename T> typename Tree<T>::iterator
Tree<T>::begin (const std::string & strategy_name)
{
  Tree_Iterator_Impl<T> *impl;
  if ( strategy_name == "Level")
    impl = new Level_Order_Tree_Iterator<T>(*this,false);
  else if (strategy_name == "Preorder")
    impl = new Pre_Order_Tree_Iterator<T>(*this,false);
  else if (strategy_name == "Postorder")
    impl = new Post_Order_Tree_Iterator<T>(*this,false);
  else
    throw typename Tree_Iterator_Impl<T>::Unknown();
  return iterator(impl);
}


// return the end iterator corresponding to the traversal strategy
template <typename T>  typename Tree<T>::iterator
Tree<T>::end (const std::string & strategy_name)
{
    Tree_Iterator_Impl<T> *impl;
  if ( strategy_name == "Level")
    impl = new Level_Order_Tree_Iterator<T>(*this,true);
  else if (strategy_name == "Preorder")
    impl = new Pre_Order_Tree_Iterator<T>(*this,true);
  else if (strategy_name == "Postorder")
    impl = new Post_Order_Tree_Iterator<T>(*this,true);
  else
    throw typename Tree_Iterator_Impl<T>::Unknown();
  return iterator(impl);
}


//accept visitor's actions on the root of the tree.
template <typename T> 
void Tree<T>::accept (Visitor &visitor)
{
  /* Doug's comment: This needs to be
  root_->accept (visitor);
  in accordance with the GoF Visitor pattern description.
  My response: write: root_->accept(visitor);
  */

  root_->accept(visitor);
}

//return root pointer
template <typename T> 
Node<T> *
Tree<T>::get_root() const
{
  return root_.get_ptr();
}

  ////// Above is what I added.

// Check if the tree is empty.
template <typename T>
bool
Tree<T>::is_null (void) const
{
  return root_.is_null ();
}

// Return the stored item.
template <typename T>
const T &
Tree<T>::item (void) const
{
  return root_->item ();
}

// Return the left branch.
template <typename T>
Tree<T>
Tree<T>::left (void) const
{
  // wrap the Node* in a tree object and increase reference count by one.
  return Tree<T> (root_->left (), true);
}

// Return the left branch.
template <typename T>
Tree<T>
Tree<T>::right (void) const
{
  // wrap the Node* in a tree object and increase reference count by one.
  return Tree<T> (root_->right (), true);
}


#endif /* _Tree_CPP */
