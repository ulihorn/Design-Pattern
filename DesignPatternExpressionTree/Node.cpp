//Name: Xianshi Xie
//Email: xianshi.xie@vanderbilt.edu
/* -*- C++ -*- */
#if !defined (_Node_CPP)
#define _Node_CPP

//#include "Node.h"

#include "Print_Visitor.h"


// Ctor
template <typename T>
Node<T>::Node (void)
:use_ (1)
{    
}

// Dtor
template <typename T>
Node<T>::~Node ()
{
}

//Ctor
template <typename T>
Leaf_Node<T>::Leaf_Node(const int item)
:item_(item)
{
}

/// Return the item stored in the node.
template <typename T> const int
Leaf_Node<T>::item (void) const
{
  return item_;
}

// Return the left child.
template <typename T>
Node<T> *
Leaf_Node<T>::left (void) const
{
  return 0;
}

// Return the right child.
template <typename T>
Node<T> *
Leaf_Node<T>::right (void) const
{
  return 0;
}
/// accept visitor
template <typename T> void
Leaf_Node<T>::accept(Visitor &v)
{
  v.visit(*this);
}

//dtor
template <typename T>
Leaf_Node<T>::~Leaf_Node()
{
}

//ctor
template <typename T>
Composite_Negate_Node<T>::Composite_Negate_Node(Node<T> *right)
:right_(right)
{
}

// Return the item in the node.
template <typename T>
const int
Composite_Negate_Node<T>::item (void) const
{
  return '-';
}

// Return the left child.
template <typename T>
Node<T> *
Composite_Negate_Node<T>::left (void) const
{
  return 0;
}

// Return the right child.
template <typename T>
Node<T> *
Composite_Negate_Node<T>::right (void) const
{
  return right_;
}

////below is what I added.

//accept the visitor
template <typename T>
void
Composite_Negate_Node<T>::accept(Visitor &v)
{
  v.visit(*this);
}

// Dtor
template <typename T>
Composite_Negate_Node<T>::~Composite_Negate_Node ()
{
  // Clean up the subtrees first and then the root recursively
  delete right_;
}

//dtor
template <typename T>
Composite_Binary_Node<T>::~Composite_Binary_Node () 
{
  delete left_;
  delete right_;
}

//ctor
template <typename T>
Composite_Binary_Node<T>::Composite_Binary_Node(Node<T> *left, Node<T> *right)
:left_(left),right_(right)
{
}

// Return the left child.
template <typename T> Node<T> *
Composite_Binary_Node<T>::left() const
{
  return left_;
}

// Return the right child.
template <typename T> Node<T> *
Composite_Binary_Node<T>::right() const
{
  return right_;
}

//ctor
template <typename T>
Composite_Add_Node<T>::Composite_Add_Node(Node<T> *left, Node<T> *right)
:Composite_Binary_Node<T>(left, right)
{
}

// Return the item in the node.
template <typename T>
const int
Composite_Add_Node<T>::item (void) const
{
  return '+';
}


//accept the visitor
template <typename T>
void
Composite_Add_Node<T>::accept(Visitor &v)
{
  v.visit(*this);
}

// Dtor
template <typename T>
Composite_Add_Node<T>::~Composite_Add_Node ()
{
}


//ctor
template <typename T>
Composite_Subtract_Node<T>::Composite_Subtract_Node
(Node<T> *left, Node<T> *right)
:Composite_Binary_Node<T>(left, right)
{
}

// Return the item in the node.
template <typename T>
const int
Composite_Subtract_Node<T>::item (void) const
{
  return '-';
}

//accept the visitor
template <typename T>
void
Composite_Subtract_Node<T>::accept(Visitor &v)
{
  v.visit(*this);
}

// Dtor
template <typename T>
Composite_Subtract_Node<T>::~Composite_Subtract_Node ()
{
}

//ctor
template <typename T>
Composite_Multiply_Node<T>::Composite_Multiply_Node
(Node<T> *left, Node<T> *right)
:Composite_Binary_Node<T>(left, right)
{
}

// Return the item in the node.
template <typename T>
const int
Composite_Multiply_Node<T>::item (void) const
{
  return '*';
}

//accept the visitor
template <typename T>
void
Composite_Multiply_Node<T>::accept(Visitor &v)
{
  v.visit(*this);
}

// Dtor
template <typename T>
Composite_Multiply_Node<T>::~Composite_Multiply_Node ()
{
  //Doug's comment: These delete operations should be 
  //in Composite_Binary_Node's destructor:
}


//Ctor
template <typename T>
Composite_Divide_Node<T>::Composite_Divide_Node(Node<T> *left, Node<T> *right)
:Composite_Binary_Node<T>(left, right)
{
}

// Return the item in the node.
template <typename T>
const int
Composite_Divide_Node<T>::item (void) const
{
  return '/';
}



//accept the visitor
template <typename T>
void
Composite_Divide_Node<T>::accept(Visitor &v)
{
  v.visit(*this);
}

// Dtor
template <typename T>
Composite_Divide_Node<T>::~Composite_Divide_Node ()
{
}

#endif /* _Node_CPP */
