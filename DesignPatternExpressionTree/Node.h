//Name: Xianshi Xie
//Email: xianshi.xie@vanderbilt.edu
/* -*- C++ -*- */
#ifndef _Node_H
#define _Node_H

//#include "Visitor.h"

template <typename T>
class Tree;

template <typename T>
class Refcounter;

class Visitor;
class Print_Visitor;

/**
* @class Node
* @brief Defines a very simple implementation of a binary tree node.
*/
template <typename T>
class Node
{
  /// Needed for reference counting.
  friend class Tree<T>;
  friend class Refcounter<Node<T> >;

public:
  /// Ctor
  //Node (const T &item, Node *left = 0, Node *right = 0);

  /// Dtor
  virtual ~Node ();

  /// Return the item stored in the node.
  virtual const int item (void) const = 0;

  /// Return the left child.
  virtual Node *left (void) const = 0;

  /// Return the right child.
  virtual Node *right (void) const = 0;


  /// accept visitor
  virtual void accept(Visitor &v) = 0;

protected:
  //ctor
  Node(void);

private:
  /// Reference counter
  int use_;
};

/**
* @class Leaf_Node
* @brief Defines a very simple implementation of a leaf node.
*/
template <typename T>
class Leaf_Node : public Node<T>
{
public:
  /// Ctor
  Leaf_Node(const int item);

  //dtor
  virtual ~Leaf_Node ();

  /// Return the item stored in the node.
  virtual const int item (void) const;

  /// Return the left child.
  virtual Node<T> *left (void) const ;

  /// Return the right child.
  virtual Node<T> *right (void) const ;

  /// accept visitor
  virtual void accept(Visitor &v);

private:
  /// Item stored in the node.
  int item_;

};

/**
* @class Composite_Negate_Node
* @brief Defines a interface of a Composite_Negate_Node.
*/
template <typename T>
class Composite_Negate_Node : public Node<T>
{
public:
  ///Ctor
  Composite_Negate_Node (Node<T> *right);

  /// Dtor
  virtual ~Composite_Negate_Node ();

  /// Return the item stored in the node.
  virtual const int item (void) const;

  /// Return the left child.
  virtual Node<T> *left (void) const;

  /// Return the right child.
  virtual Node<T> *right (void) const;

  /// accept visitor
  virtual void accept(Visitor &v);

private:

  Node<T> * right_;

};


/**
* @class Composite_Binary_Node
* @brief Defines a interface of a Composite_Binary_Node.
*/
template <typename T>
class Composite_Binary_Node : public Node<T>
{
public:
  Composite_Binary_Node (Node<T> *left, Node<T> *right);

  /// Dtor
  virtual ~Composite_Binary_Node () ;

  /// Return the item stored in the node.
  virtual const int item (void) const = 0;

  /// Return the left child.
  virtual Node<T> *left (void) const;

  /// Return the right child.
  virtual Node<T> *right (void) const;

  /// accept visitor
  virtual void accept(Visitor &v) = 0;

protected:

  /// Left child.
  Node<T> *left_;

  /// Right child.
  Node<T> *right_;

};

/**
* @class Composite_Divide_Node
* @brief Defines implementation of a Composite_Divide_Node.
*/
template <typename T>
class Composite_Divide_Node : public Composite_Binary_Node<T>
{
public:

  //Ctor
  Composite_Divide_Node (Node<T> *left = 0, Node<T> *right = 0);

  /// Dtor
  virtual ~Composite_Divide_Node ();

  /// Return the item stored in the node.
  virtual const int item (void) const;

  /// accept visitor
  virtual void accept(Visitor &v);
};

/**
* @class Composite_Subtract_Node
* @brief Defines implementation of a Composite_Subtract_Node.
*/
template <typename T>
class Composite_Subtract_Node : public Composite_Binary_Node<T>
{
public:

  //Ctor
  Composite_Subtract_Node (Node<T> *left = 0, Node<T> *right = 0);

  /// Dtor
  virtual ~Composite_Subtract_Node ();

  /// Return the item stored in the node.
  virtual const int item (void) const;

  /// accept visitor
  virtual void accept(Visitor &v);

};

/**
* @class Composite_Add_Node
* @brief Defines implementation of a Composite_Add_Node.
*/
template <typename T>
class Composite_Add_Node : public Composite_Binary_Node<T>
{
public:

  //Ctor
  Composite_Add_Node (Node<T> *left = 0, Node<T> *right = 0);

  /// Dtor
  virtual ~Composite_Add_Node ();

  /// Return the item stored in the node.
  virtual const int item (void) const;

  /// accept visitor
  virtual void accept(Visitor &v);

};

/**
* @class Composite_Multiply_Node
* @brief Defines implementation of a Composite_Multiply_Node.
*/
template <typename T>
class Composite_Multiply_Node : public Composite_Binary_Node<T>
{
public:

  //Ctor
  Composite_Multiply_Node (Node<T> *left = 0, Node<T> *right = 0);

  /// Dtor
  virtual ~Composite_Multiply_Node ();

  /// Return the item stored in the node.
  virtual const int item (void) const;

  /// accept visitor
  virtual void accept(Visitor &v);

};

#include "Node.cpp"

#endif /* _Node_H */
