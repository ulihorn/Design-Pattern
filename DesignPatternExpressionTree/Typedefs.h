//Name: Xianshi Xie
//Email: xianshi.xie@vanderbilt.edu

/* -*- C++ -*- */
#ifndef _Typedefs_H
#define _Typedefs_H

#include <stdlib.h>
#include <stack>

template <typename T>
class Queue;

template <typename T>
class Queue_Adapter;

template <typename T>
class LQueue;

template <typename T>
class AQueue;

template <typename T>
class Node;

template <typename T>
class Leaf_Node;

template <typename T>
class Composite_Add_Node;

template <typename T>
class Composite_Subtract_Node;

template <typename T>
class Composite_Multiply_Node;

template <typename T>
class Composite_Divide_Node;

template <typename T>
class Composite_Negate_Node;

template <typename T>
class Tree;

typedef Node<char> NODE;
typedef Tree<char> TREE;
typedef Leaf_Node<char> LEAF_NODE;
typedef Composite_Add_Node<char> COMPOSITE_ADD_NODE;
typedef Composite_Subtract_Node<char> COMPOSITE_SUBTRACT_NODE;
typedef Composite_Multiply_Node<char> COMPOSITE_MULTIPLY_NODE;
typedef Composite_Divide_Node<char> COMPOSITE_DIVIDE_NODE;
typedef Composite_Negate_Node<char> COMPOSITE_NEGATE_NODE;

// This part of the solution uses the Adapter pattern.  Note that
// LQUEUE_ADAPTER and AQUEUE_ADAPTER are both children of the Queue
// class.  
typedef Queue_Adapter<LQueue <TREE> > LQUEUE_ADAPTER;
typedef Queue_Adapter<AQueue <TREE> > AQUEUE_ADAPTER;

typedef Queue<TREE> QUEUE;

//typedef std::stack<Node<typename T>* > STACK;

typedef Queue_Adapter<LQueue <TREE> > LQUEUE_ADAPTER_IT;
typedef Queue_Adapter<AQueue <TREE> > AQUEUE_ADAPTER_IT;

typedef Queue<TREE> QUEUE_IT;


#endif /* _Typedefs_H */
