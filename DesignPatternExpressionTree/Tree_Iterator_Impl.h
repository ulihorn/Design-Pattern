//Name: Xianshi Xie
//Email: xianshi.xie@vanderbilt.edu
#ifndef _TREE_ITERATOR_IMPL_H
#define _TREE_ITERATOR_IMPL_H

#include <stdlib.h>
#include <stdexcept>
#include <stack>
#include <vector>
#include "Refcounter.h"
#include "Queue.h"
#include "LQueue.h"
#include "AQueue.h"
#include "Typedefs.h"

template <typename T>
class Tree;

template <typename T>
class Node;

template <typename T>
class Tree_Iterator;
/**
* @class Tree_Iterator_Impl
* @brief This is abstract class for the iterator pattern that outlines
*        the interface for the tree iteraters.
*/
template<typename T>
class Tree_Iterator_Impl
{
  friend class Tree_Iterator<T>;
  friend class Tree<T>;
  friend class Node<T>;
  friend class Refcounter <Tree_Iterator_Impl<T> >; // allows refcounting
public:

  //ctor
  //Tree_Iterator_Impl(TREE &tree);

  //dtor
  virtual ~Tree_Iterator_Impl(void);

  //dereference the iterator, return a pointer that points to current NODE.
  virtual Tree<T>  operator* (void) = 0;

  //dereference the iterator, return a const pointer that
  //points to current NODE.
  virtual const Tree<T>  operator* (void) const = 0;

  //pre increment, implement by concrete iterator
  virtual void operator++ (void) = 0;

  //check for equality
  virtual bool operator== (const Tree_Iterator_Impl<T> &rhs) const = 0;

  //check for inequality
  virtual bool operator!= (const Tree_Iterator_Impl<T> &rhs) const = 0;

  //used for pre increment and get a copy of the iterator itself
  virtual Tree_Iterator_Impl<T>* clone (void) = 0;

  class Unknown {};

protected:
  /// Default ctor - needed for reference counting
  Tree_Iterator_Impl();

private:
  /// Reference counter
  int use_;


};


/**
* @class Level_Order_Tree_Iterator
* @brief This is concrete subclass iterator for traversing in level order.
*/

template <typename T>
class Level_Order_Tree_Iterator: public Tree_Iterator_Impl<T>
{
public:

  /// Unknown_Strategy class for exceptions when an unknown strategy
  /// name is passed to the make_traversal_strategy method

  class Unknown_Strategy
  {
  public:
    Unknown_Strategy(const std::string &msg)
    {
      msg_ = msg;
    }

    const std::string what(void)
    {
      return msg_;
    }
  private:
    std::string msg_;
  };
  //ctor: used for begin() and end() method of tree
  Level_Order_Tree_Iterator(Tree<T> &tree,bool is_end);

  //copy ctor: used for clone() method
  Level_Order_Tree_Iterator(const Level_Order_Tree_Iterator<T>& rhs);

  //dtor
  virtual ~Level_Order_Tree_Iterator(void);

  //dereference the iterator, return a pointer that points to current NODE
  //in level order
  virtual Tree<T>  operator* (void);
  //dereference the iterator, return a const pointer that
  //points to current NODE in level order.
  virtual const Tree<T>  operator* (void) const;

  //preincrement
  virtual void operator++ (void);

  //check for equality
  virtual bool operator== (const Tree_Iterator_Impl<T> &rhs) const;

  //check for inequality
  virtual bool operator!= (const Tree_Iterator_Impl<T> &rhs) const;

  //get a new copy of Level_Order_Iterator instance itself
  //for post increment of iterator
  virtual Tree_Iterator_Impl<T>* clone (void);

protected:
  Level_Order_Tree_Iterator(void);

private:

  //the tree to which the iterator points
  Tree<T> &tree_;

  /// Factory method to create the appropriate type of queue.
  QUEUE_IT *make_queue_strategy_ (const std::string &queue_type);
  /// Pointer to Queue class used for level traversal.
  std::auto_ptr<QUEUE_IT> queue_;
};



/**
* @class Pre_Order_Tree_Iterator
* @brief This is concrete subclass iterator for traversing in pre order.
*/
template <typename T>
class Pre_Order_Tree_Iterator: public Tree_Iterator_Impl<T>
{
public:

  //ctor: used for begin() and end() method of tree
  Pre_Order_Tree_Iterator(Tree<T> &tree,bool is_end);

  //dtor
  virtual ~Pre_Order_Tree_Iterator(void);

  //dereference the iterator, return a pointer that points to current NODE
  //in level order
  virtual Tree<T>  operator* (void);
  //dereference the iterator, return a const pointer that
  //points to current NODE in level order.
  virtual const Tree<T>  operator* (void) const;

  //preincrement
  virtual void operator++ (void);

  //check for equality
  virtual bool operator== (const Tree_Iterator_Impl<T> &rhs) const;

  //check for inequality
  virtual bool operator!= (const Tree_Iterator_Impl<T> &rhs) const;

  //get a new copy of Level_Order_Iterator instance itself
  //for post increment of iterator
  virtual Tree_Iterator_Impl<T>* clone (void);

protected:
  Pre_Order_Tree_Iterator(void);

private:

  //the tree to which the iterator points
  Tree<T> &tree_;
  // Doug's comment: You don't need to use an auto_ptr<> here 
  // - just use std::stack.
  // My response: replace autoptr with std::stack
  std::stack<Tree<T> > stack_;

};


/**
* @class Post_Order_Tree_Iterator
* @brief This is concrete subclass iterator for traversing in post order.
*/
template <typename T>
class Post_Order_Tree_Iterator: public Tree_Iterator_Impl<T>
{
public:

  //ctor: used for begin() and end() method of tree
  Post_Order_Tree_Iterator(Tree<T> &tree,bool is_end);

  void traverse_help(Tree<T> cur);

  //copy ctor: used for clone() method
  //Post_Order_Tree_Iterator(const Post_Order_Tree_Iterator<T>& rhs);

  //dtor
  virtual ~Post_Order_Tree_Iterator(void);

  //dereference the iterator, return a pointer that points to current NODE
  //in level order
  virtual Tree<T>  operator* (void);
  //dereference the iterator, return a const pointer that
  //points to current NODE in level order.
  virtual const Tree<T>  operator* (void) const;

  //preincrement
  virtual void operator++ (void);

  //check for equality
  virtual bool operator== (const Tree_Iterator_Impl<T> &rhs) const;

  //check for inequality
  virtual bool operator!= (const Tree_Iterator_Impl<T> &rhs) const;

  //get a new copy of Level_Order_Iterator instance itself
  //for post increment of iterator
  virtual Tree_Iterator_Impl<T>* clone (void);

protected:
  Post_Order_Tree_Iterator(void);

private:

  //root of the tree that the iterator points to.
  Tree<T> &tree_;

  //container that stores the tree item
  std::vector<Tree<T> > vector_;
  //position that the current iterator points to.
  size_t pos_;

};


#include "Tree_Iterator_Impl.cpp"


#endif
