//Name: Xianshi Xie
//Email: xianshi.xie@vanderbilt.edu

/* -*- C++ -*- */
#ifndef _Queue_H
#define _Queue_H

// This header defines "size_t"
#include <stdlib.h>

#include <stdexcept>

/**
* @class Queue
* @brief Defines a Queue interface for subclasses that have generic
* "first-in/first-out" (FIFO) semantics.
*/
template <class T>
class Queue
{
public:
  /// Trait to use when freeing up memory from LQueue.
  typedef T value_type;

  /// Dtor - make this virtual since we subclass from this interface.
  virtual ~Queue (void) = 0;

  class Underflow {};
  class Overflow {};

  /// Classic Queue operations.

  // Place a <new_item> at the tail of the queue.  Throws
  // the <Overflow> exception if the queue is full, e.g., if memory is
  // exhausted.  
  virtual void enqueue (const T &new_item) = 0;

  // Remove and return the front item on the queue.  
  // Throws the <Underflow> exception if the queue is empty. 
  virtual T dequeue (void) = 0;

  // Returns the front queue item without removing it. 
  // Throws the <Underflow> exception if the queue is empty. 
  virtual T front (void) const = 0;

  // = Check boundary conditions for Queue operations. 

  // Returns 1 if the queue is empty, otherwise returns 0. 
  virtual bool is_empty (void) const = 0;

  // Returns 1 if the queue is full, otherwise returns 0. 
  virtual bool is_full (void) const = 0;

  // Returns the current number of elements in the queue.
  virtual size_t size (void) const = 0;
};

/**
* @class Queue_Adapter
* @brief Defines a parameterized Queue subclass that have generic
* "first-in/first-out" (FIFO) semantics. This uses the adapter
* pattern. This class delegates the method calls to its
* parameterized type.
*/
template <typename Q_T>
class Queue_Adapter : public Queue<typename Q_T::value_type>
{
public:
  /// Default constructor
  Queue_Adapter (size_t size);

  /// Copy ctor
  Queue_Adapter (const Queue_Adapter<Q_T> &rhs);

  /// Dtor
  virtual ~Queue_Adapter (void);

  /// Assignment operator
  Queue_Adapter<Q_T> &operator= (const Queue_Adapter<Q_T> &rhs);

  /// Equality/Inequality operators
  bool operator== (const Queue_Adapter<Q_T> &rhs) const;
  bool operator!= (const Queue_Adapter<Q_T> &rhs) const;

  /// Classic Queue operations.

  /// Place a <new_item> at the tail of the queue.  Throws
  /// the <Overflow> exception if the queue is full, e.g., if memory is
  /// exhausted.  
  virtual void enqueue (const typename Q_T::value_type &new_item);

  /// Remove and return the front item on the queue.  
  /// Throws the <Underflow> exception if the queue is empty. 
  virtual typename Q_T::value_type dequeue (void);

  /// Returns the front queue item without removing it. 
  /// Throws the <Underflow> exception if the queue is empty. 
  virtual typename Q_T::value_type front (void) const;

  /// Returns 1 if the queue is empty, otherwise returns 0. 
  virtual bool is_empty (void) const;

  /// Returns 1 if the queue is full, otherwise returns 0. 
  virtual bool is_full (void) const;

  /// Returns the current number of elements in the queue.
  virtual size_t size (void) const;

private:
  /// You fill in here and *only* here in this header file!
  Q_T queue_;
};

#include "Queue.cpp"

#endif /* _Queue_H */
