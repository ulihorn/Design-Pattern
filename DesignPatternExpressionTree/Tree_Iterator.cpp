//Name: Xianshi Xie
//Email: xianshi.xie@vanderbilt.edu

#if !defined (_Tree_Iterator_CPP)
#define _Tree_Iterator_CPP

#include "Tree_Iterator.h"
#include "Tree_Iterator_Impl.h"
#include "Options.h"


//copty ctor
template <typename T>
Tree_Iterator<T>::Tree_Iterator(const Tree_Iterator<T> &rhs)
:iterator_impl_(rhs.iterator_impl_)
{
}

//ctor  the iterator needs to be allocated dynamically and iterator
/// will take ownership of the memory and clean it up appropriately.
template <typename T>
Tree_Iterator<T>::Tree_Iterator(Tree_Iterator_Impl<T> *impl)
:iterator_impl_(impl)
{
}

//dereference the iterator, return a pointer that points to current NODE.
template <typename T>
Tree<T>  Tree_Iterator<T>::operator* (void)
{
  return *(*iterator_impl_);
}

//dereference the iterator, return a const pointer that points to current NODE
template <typename T>
const Tree<T>  Tree_Iterator<T>::operator*(void) const
{
  return *(*iterator_impl_);
}

//preincrement, return a reference to the iterator that points next NODE
template <typename T>
Tree_Iterator<T> & Tree_Iterator<T>::operator++(void)
{
  ++(*iterator_impl_);
  return *this;
}

//postincrement, return a reference to the iterator that points next NODE
template <typename T>
Tree_Iterator<T> Tree_Iterator<T>::operator++(int)
{
  Tree_Iterator<T> temp (iterator_impl_.get_ptr ()->clone ());
  ++(*iterator_impl_);
  return temp;
}

//check for equality
template <typename T>
bool Tree_Iterator<T>::operator==(const Tree_Iterator<T> &rhs) const
{
  return *iterator_impl_ == *rhs.iterator_impl_;
}

//check for in-equality
template <typename T>
bool Tree_Iterator<T>::operator!=(const Tree_Iterator<T> &rhs) const
{
  return !(*this==rhs);
}


#endif /* _Tree_Iterator_CPP */



