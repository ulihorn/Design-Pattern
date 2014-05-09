/* -*- C++ -*- */
#ifndef _Tree_H
#define _Tree_H

#include "Node.h"
#include "Refcounter.h"
#include "Typedefs.h"
#include <string>

//#include "Tree_Iterator.h"
template <typename T>
class Tree_Iterator;

template <typename T>
class Tree_Iterator_Impl;

template <typename T>
class Level_Order_Tree_Iterator;

template <typename T>
class Pre_Order_Tree_Iterator;

template <typename T>
class Post_Order_Tree_Iterator;


class Visitor;
class Print_Visitor;
class Pre_Order_Eval_Visitor;
class Post_Order_Eval_Visitor;

/**
 * @class Tree
 * @brief Defines a bridge to the node implementation that
 *        actually contains the data items for the tree.
 */
template <typename T>
class Tree
{
  friend class Tree_Iterator<T>;
  friend class Tree_Iterator_Impl<T>;
  friend class Level_Order_Tree_Iterator<T>;  
  friend class Pre_Order_Tree_Iterator<T>;
  friend class Post_Order_Tree_Iterator<T>;
  friend class Visitor;
  friend class Print_Visitor;

public:
  /// Default ctor
  Tree ();

  /// Ctor that takes a Node<T> *.
  Tree (Node<T> *root,bool count=false);

  /// Ctor with an item to contain.
  Tree (const T &item);

  /// Ctor that takes a node and 2 children.
  Tree (const T &item, Node<T> *left, Node<T> *right);

  // Copy ctor
  Tree (const Tree &t);

  /// Assignment operator
  void operator= (const Tree &t);

  /// Dtor
  ~Tree (void);

  // Below is what I added.

  //trait for iterator
  typedef Tree_Iterator<T> iterator;

  // return the beginning iterator corresponding to the traversal strategy
  iterator begin (const std::string & strategy_name);

  // return the end iterator corresponding to the traversal strategy
  iterator end (const std::string & strategy_name);

  //accept visitor's actions on the root of the tree.
  void accept (Visitor &visitor);

  //return root pointer
  Node<T> * get_root() const;

  //Refcounter<Node<T> > get_root(void);


  // Above is is what I added.


  /// Check if tree is null tree.
  bool is_null (void) const;

  /// Return the item in the tree.
  const T &item (void) const;

  /// Return the left child.
  Tree<T> left (void) const;

  /// Return the right child.
  Tree<T> right (void) const;

private:
  /// The underlying pointer to the implementation. These are
  /// reference counted.
  Refcounter <Node<T> > root_;
};

#include "Tree.cpp"

#endif /* _Tree_H */
