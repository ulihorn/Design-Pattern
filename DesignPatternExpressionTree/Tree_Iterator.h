//Name: Xianshi Xie
//Email: xianshi.xie@vanderbilt.edu

#ifndef _TREE_ITERATOR_H
#define _TREE_ITERATOR_H

class Tree_Factory;

#include <stdlib.h>
#include "Node.h"
#include "Tree.h"
#include "Typedefs.h"
#include "Tree_Iterator_Impl.h"
#include "Refcounter.h"

template <typename T>
class Tree_Iterator_Impl;

/**
* @class Tree_Iterator
* @brief Defines a interface and bridge to the tree iterator implementation 
*        that actually traverses the tree.
*/

template <typename T>
class Tree_Iterator
{
  friend class Tree_Iterator_Impl<T>;
public:
  //copty ctor
  Tree_Iterator(const Tree_Iterator<T> &rhs);

  //ctor  the iterator needs to be allocated dynamically and iterator
  /// will take ownership of the memory and clean it up appropriately.
  Tree_Iterator(Tree_Iterator_Impl<T> *);

  //dereference the iterator, return a pointer that points to current NODE.

  /* Doug's comment:I think it's cleaner if you have operator*() return TREE 
  rather than Node<T> *. 
  My response: replace Node<T> * with Tree<T>, which is more general than
  TREE.     */

  Tree<T>  operator* (void);

  //dereference the iterator, return a const pointer
  //that points to current NODE.
  const Tree<T>  operator*(void) const;

  //preincrement, return a reference to the iterator that points next NODE
  Tree_Iterator<T> & operator++(void);

  //postincrement, return a reference to the iterator that points next NODE
  Tree_Iterator<T> operator++(int);

  //check for equality
  bool operator==(const Tree_Iterator<T> &rhs) const;

  //check for inequality
  bool operator!=(const Tree_Iterator<T> &rhs) const;

  //define some traits 
  typedef std::forward_iterator_tag iterator_category;
  typedef T value_type;
  typedef T *pointer;
  typedef T &reference;
  typedef int difference_type;

private:
  /// reference counted Pointer to the iterator impl.
  Refcounter <Tree_Iterator_Impl<T> > iterator_impl_;
};

#include "Tree_Iterator.cpp"

#endif
