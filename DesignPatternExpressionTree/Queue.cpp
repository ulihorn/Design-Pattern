//Name: Xianshi Xie
//Email: xianshi.xie@vanderbilt.edu


#if !defined (_Queue_CPP)
#define _Queue_CPP

#include "Queue.h"

#include <iostream>

// Constructor.
template <typename Q_T>
Queue_Adapter<Q_T>::Queue_Adapter (size_t size)
:queue_(size)
// Initialize here.
{
}

// Destructor.
template <typename T>
Queue<T>::~Queue (void)
{
}

// Copy constructor.
template <typename Q_T>
Queue_Adapter<Q_T>::Queue_Adapter (const Queue_Adapter<Q_T> &rhs)
:queue_(rhs.queue_)
// Initialize here.
{
}

// Assignment operator.
template <typename Q_T> Queue_Adapter<Q_T> &
Queue_Adapter<Q_T>::operator= (const Queue_Adapter<Q_T> &rhs) 
{
  if ( this != &rhs){
    queue_ = rhs.queue_;
  }
  return *this;        

}

// Perform actions needed when queue goes out of scope.
template <typename Q_T>
Queue_Adapter<Q_T>::~Queue_Adapter (void)
{
}

// Compare this queue with <rhs> for equality.  Returns true if the
// size()'s of the two queues are equal and all the elements from 0
// .. size() are equal, else false.
template <typename Q_T> bool 
Queue_Adapter<Q_T>::operator== (const Queue_Adapter<Q_T> &rhs) const
{
  return queue_ == rhs.queue_;
}

// Compare this queue with <rhs> for inequality such that <*this> !=
// <s> is always the complement of the boolean return value of
// <*this> == <s>.
template <typename Q_T> bool 
Queue_Adapter<Q_T>::operator!= (const Queue_Adapter<Q_T> &rhs) const
{
  return !(*this == rhs);
}

// Place a <new_item> at the tail of the queue.  Throws
// the <Overflow> exception if the queue is full.
template <typename Q_T> void
Queue_Adapter<Q_T>::enqueue (const typename Q_T::value_type &new_item)
{
  /* Doug's comments:
  Please don't call is_full() here, but instead call queue.enqueue()
  within a try/catch block, catch the exception that it raises (as we
  discussed in class), and then throw the appropriate Overflow exception
  defined in Queue (also as we discussed in class).
  */
  try{
    return queue_.enqueue(new_item);
  }
  catch (typename Q_T::Overflow &)
  {
    throw typename Queue<typename Q_T::value_type>::Overflow();
  }
}

// Remove and return the front item on the queue.  
// Throws the <Underflow> exception if the queue is empty. 
template <typename Q_T> typename Q_T::value_type
Queue_Adapter<Q_T>::dequeue (void)
{
  /*
  Please don't call is_empty() here, but instead call queue.dequeue()
  within a try/catch block, catch the exception that it raises (as we
  discussed in class), and then throw the appropriate Underflow
  exception defined in Queue (also as we discussed in class).
  */

  try{
    return queue_.dequeue();
  }
  catch (typename Q_T::Underflow &)
  {
    throw typename Queue<typename Q_T::value_type>::Underflow();
  }
}

// Returns the front queue item without removing it. 
// Throws the <Underflow> exception if the queue is empty. 
template <typename Q_T> typename Q_T::value_type
Queue_Adapter<Q_T>::front (void) const
{
  /*
  Please don't call is_empty() here, but instead call queue.front()
  within a try/catch block, catch the exception that it raises (as we
  discussed in class), and then throw the appropriate Underflow
  exception defined in Queue (also as we discussed in class).
  */

  try{
    return queue_.front();
  }
  catch (typename Q_T::Underflow &)
  {
    throw typename Queue<typename Q_T::value_type>::Underflow();
  }
}

// Returns true if the queue is empty, otherwise returns false.
template <typename Q_T> bool
Queue_Adapter<Q_T>::is_empty (void) const 
{
  return queue_.is_empty();
}

// Returns true if the queue is full, otherwise returns false.
template <typename Q_T> bool
Queue_Adapter<Q_T>::is_full (void) const 
{
  return queue_.is_full();
}

// Returns the current size.
template <typename Q_T> size_t 
Queue_Adapter<Q_T>::size (void) const
{
  return queue_.size();
}

#endif /* _Queue_CPP */
