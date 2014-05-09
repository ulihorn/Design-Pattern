// Name: Xianshi Xie
//Email: xianshi.xie@vanderbilt.edu

/**
* @class AQueue
* @brief Defines a generic "first-in/first-out" (FIFO) 
*  Abstract Data Type (ADT) using an Array
*        that is organized as a "circular queue."
*/

#if !defined (_AQUEUE_C)
#define _AQUEUE_C

#include "AQueue.h"
#include <stdexcept>
#pragma warning(disable: 4996)

// Returns the current size.

template <class T> size_t 
AQueue<T>::size (void) const
{
  return count_;
}

// Constructor.

/* Doug's comment:
Please make sure to order the initialization of data members the same
as in your class definition.

> head_(0),tail_(0),count_(0),

You just need to say

queue_ (size + 1)

here.
*/
/* 
My response: take off head_(0),tail_(0),count_(0), just leave queue_(size+1).
*/
template <class T>
AQueue<T>::AQueue (size_t size):queue_(size+1),head_(0),tail_(0),count_(0)
// Add a "dummy" slot to ease keeping track of full and empty.
{
}

// Copy constructor.

//Doug's comment: Please make sure to order the initialization of data members 
//the same as in your class definition.

//My response: order the initialization of data members the same
//             as in the class definition.

template <class T>
AQueue<T>::AQueue (const AQueue<T> &rhs)
:queue_(rhs.queue_),head_(rhs.head_),tail_(rhs.tail_),count_(rhs.count_)
{
}

// Assignment operator.
template <class T> AQueue<T> &
AQueue<T>::operator= (const AQueue<T> &rhs) 
{
  if (this != &rhs)
  {
    head_ = rhs.head_;
    tail_ = rhs.tail_;
    count_ = rhs.count_;
    queue_ = rhs.queue_;
  }

  return *this;
}

// Perform actions needed when queue goes out of scope.

template <class T>
AQueue<T>::~AQueue (void)
{
  // There's nothing to do here since we didn't dynamically
  // allocate any memory. The queue_ dtor handles that.
}

// Compare this queue with <rhs> for equality.  Returns true if the
// size()'s of the two queues are equal and all the elements from 0
// .. size() are equal, else false.
template <class T> bool 
AQueue<T>::operator== (const AQueue<T> &rhs) const
{
  return size()==rhs.size() &&
    std::equal(begin(),end(),rhs.begin());
}

// Compare this queue with <rhs> for inequality such that <*this> !=
// <s> is always the complement of the boolean return value of
// <*this> == <s>.

template <class T> bool 
AQueue<T>::operator!= (const AQueue<T> &rhs) const
{
  return !(*this == rhs);
}

// Place a <new_item> at the tail of the queue.  Throws
// the <Overflow> exception if the queue is full.

template <class T> void
AQueue<T>::enqueue (const T &new_item)
{
  if (!is_full()){
    queue_[tail_] = new_item;
    count_++;
    tail_ = increment(tail_);
  }
  else
    throw Overflow();
}

// Remove and return the front item on the queue.  
// Throws the <Underflow> exception if the queue is empty. 

template <class T> T 
AQueue<T>::dequeue (void)
{
  if (!is_empty()){

    /*
    You can just say
    T &tmp = queue_[head_];
    which is more efficient.
    */

    //My response: replace T tmp = queue_[head_] 
    //              with T &tmp = queue_[head_];

    T &tmp = queue_[head_];
    head_ = increment(head_);
    count_--;
    return tmp;
  }
  else
    throw Underflow();
}

// Returns the front queue item without removing it. 
// Throws the <Underflow> exception if the queue is empty. 

template <class T> T 
AQueue<T>::front (void) const
{

  if (!is_empty())
    return queue_[head_];
  else
    throw Underflow();

}

// Returns true if the queue is empty, otherwise returns false.

template <class T> bool
AQueue<T>::is_empty (void) const 
{
  return count_ == 0;
}

// Returns true if the queue is full, otherwise returns false.

template <class T> bool
AQueue<T>::is_full (void) const 
{
  return count_ == queue_.size() - 1;
}

// Get an iterator to the begining of the queue
template <typename T> typename AQueue<T>::iterator
AQueue<T>::begin (void)
{
  return iterator(*this,head_);
}

// Get an iterator pointing past the end of the queue
template <typename T> typename AQueue<T>::iterator
AQueue<T>::end (void)
{
  return iterator(*this,tail_);
}

// Get an iterator to the begining of the queue
template <typename T> typename AQueue<T>::const_iterator
AQueue<T>::begin (void) const
{
  return const_iterator(*this,head_);
}

// Get an iterator pointing past the end of the queue
template <typename T> typename AQueue<T>::const_iterator
AQueue<T>::end (void) const
{
  return const_iterator(*this,tail_);
}

// Get an iterator to the end of the queue
template <typename T> typename AQueue<T>::reverse_iterator
AQueue<T>::rbegin (void)
{
  return reverse_iterator(*this,decrement(tail_));

}

// Get an iterator pointing to the beginning of the queue
template <typename T> typename AQueue<T>::reverse_iterator
AQueue<T>::rend (void)
{
  return reverse_iterator(*this,decrement(head_));
}

// Get an iterator to the end of the queue
template <typename T> typename AQueue<T>::const_reverse_iterator
AQueue<T>::rbegin (void) const
{
  return const_reverse_iterator(*this,decrement(tail_));
}

// Get an iterator pointing to the beginning of the queue
template <typename T> typename AQueue<T>::const_reverse_iterator
AQueue<T>::rend (void) const
{
  return const_reverse_iterator(*this,decrement(head_));
}

/// Calculate the appropriate index when incrementing.
template <typename T> size_t
AQueue<T>::increment (size_t index) const
{
  return (index + 1) % queue_.size();
}

/// Calculate the appropriate index when decrementing.
template <typename T> size_t
AQueue<T>::decrement (size_t index) const
{
  return (index + queue_.size() - 1) % queue_.size();
}

template <typename T> INLINE T &
AQueue_Iterator<T>::operator* (void)
{
  return queue_.queue_[pos_];
}

template <typename T> INLINE const T &
AQueue_Iterator<T>::operator* (void) const
{
  return queue_.queue_[pos_];
}

template <typename T> INLINE AQueue_Iterator<T> &
AQueue_Iterator<T>::operator++ (void) 
{
  pos_ = queue_.increment(pos_);
  return *this;
}

// Post-increment.
template <typename T> INLINE AQueue_Iterator<T> 
AQueue_Iterator<T>::operator++ (int) 
{
  AQueue_Iterator<T> tmp = *this;
  pos_ = queue_.increment(pos_);
  return tmp;
}

template <typename T> INLINE AQueue_Iterator<T> &
AQueue_Iterator<T>::operator-- (void)
{
  pos_ = queue_.decrement(pos_);
  return *this;
}

// Post-decrement.
template <typename T> INLINE AQueue_Iterator<T>
AQueue_Iterator<T>::operator-- (int) 
{
  //AQueue_Iterator<T> tmp;
  //pos_ = queue_.decrement(pos_);
  //return tmp;
  AQueue_Iterator<T> tmp = *this;
  pos_ = queue_.decrement(pos_);
  return tmp;
}

template <typename T> INLINE bool
AQueue_Iterator<T>::operator== (const AQueue_Iterator<T> &rhs) const
{
  return &queue_ == &rhs.queue_ && pos_ == rhs.pos_;
}

template <typename T> INLINE bool
AQueue_Iterator<T>::operator!= (const AQueue_Iterator<T> &rhs) const
{
  return !(*this == rhs);
}

template <typename T>
AQueue_Iterator<T>::AQueue_Iterator (AQueue<T> &queue,size_t pos)
:queue_(queue),pos_(pos % queue_.queue_.size())
{
}

template <typename T> INLINE const T &
Const_AQueue_Iterator<T>::operator* (void) const
{
  return queue_.queue_[pos_];
}

template <typename T> INLINE const Const_AQueue_Iterator<T> &
Const_AQueue_Iterator<T>::operator++ (void) const
{
  pos_ = queue_.increment(pos_);
  return *this;
}

template <typename T> INLINE Const_AQueue_Iterator<T>
Const_AQueue_Iterator<T>::operator++ (int) const
{
  Const_AQueue_Iterator<T> tmp=*this;
  pos_ = queue_.increment(pos_);
  return tmp;
}

template <typename T> INLINE const Const_AQueue_Iterator<T> &
Const_AQueue_Iterator<T>::operator-- (void) const
{
  pos_ = queue_.decrement(pos_);
  return *this;
}

// Post-decrement.
template <typename T> INLINE Const_AQueue_Iterator<T>
Const_AQueue_Iterator<T>::operator-- (int) const
{
  Const_AQueue_Iterator<T> tmp=*this;
  pos_ = queue_.decrement(pos_);
  return tmp;
}

template <typename T> INLINE bool
Const_AQueue_Iterator<T>::operator== 
(const Const_AQueue_Iterator<T> &rhs) const
{
  return &queue_ == &rhs.queue_ && pos_ == rhs.pos_;
}

template <typename T> INLINE bool
Const_AQueue_Iterator<T>::operator!= 
(const Const_AQueue_Iterator<T> &rhs) const
{
  return !(*this == rhs);
}

template <typename T>
Const_AQueue_Iterator<T>::Const_AQueue_Iterator 
(const AQueue<T> &queue,size_t pos)
: queue_ (queue),pos_ (pos % queue_.queue_.size())
{
}

template <typename T> INLINE T &
AQueue_Reverse_Iterator<T>::operator* (void)
{
  // Access the underlying element in the array.
  return queue_.queue_[pos_];
}

template <typename T> INLINE const T &
AQueue_Reverse_Iterator<T>::operator* (void) const
{
  return queue_.queue_[pos_];
}

template <typename T> INLINE AQueue_Reverse_Iterator<T> &
AQueue_Reverse_Iterator<T>::operator++ (void) 
{
  pos_ = queue_.decrement(pos_);
  return *this;
}

template <typename T> INLINE AQueue_Reverse_Iterator<T> 
AQueue_Reverse_Iterator<T>::operator++ (int) 
{
  AQueue_Reverse_Iterator<T> tmp = *this;
  pos_ = queue_.decrement(pos_);
  return tmp;
}

template <typename T> INLINE AQueue_Reverse_Iterator<T> &
AQueue_Reverse_Iterator<T>::operator-- (void)
{
  pos_ = queue_.increment(pos_);
  return *this;
}

template <typename T> INLINE AQueue_Reverse_Iterator<T>
AQueue_Reverse_Iterator<T>::operator-- (int) 
{
  AQueue_Reverse_Iterator<T> tmp = *this;
  pos_ = queue_.increment(pos_);
  return tmp;
}

template <typename T> INLINE bool
AQueue_Reverse_Iterator<T>::operator== 
(const AQueue_Reverse_Iterator<T> &rhs) const
{
  return &queue_ == &rhs.queue_ && pos_ == rhs.pos_;
}

template <typename T> INLINE bool
AQueue_Reverse_Iterator<T>::operator!= 
(const AQueue_Reverse_Iterator<T> &rhs) const
{
  return !(*this == rhs);
}

template <typename T>
AQueue_Reverse_Iterator<T>::AQueue_Reverse_Iterator 
(AQueue<T> &queue,size_t pos)
: queue_ (queue),pos_ (pos % queue_.queue_.size())
{
}

template <typename T> INLINE const T &
Const_AQueue_Reverse_Iterator<T>::operator* (void) const
{
  return queue_.queue_[pos_];
}

template <typename T> INLINE const Const_AQueue_Reverse_Iterator<T> &
Const_AQueue_Reverse_Iterator<T>::operator++ (void) const
{
  pos_ = queue_.decrement(pos_);
  return *this;
}

template <typename T> INLINE Const_AQueue_Reverse_Iterator<T>
Const_AQueue_Reverse_Iterator<T>::operator++ (int) const
{
  Const_AQueue_Reverse_Iterator<T> tmp = *this;
  pos_ = queue_.decrement(pos_);
  return tmp;
}

template <typename T> INLINE const Const_AQueue_Reverse_Iterator<T> &
Const_AQueue_Reverse_Iterator<T>::operator-- (void) const
{
  pos_ = queue_.increment(pos_);
  return *this;
}

template <typename T> INLINE Const_AQueue_Reverse_Iterator<T>
Const_AQueue_Reverse_Iterator<T>::operator-- (int) const
{
  Const_AQueue_Reverse_Iterator<T> tmp = *this;
  pos_ = queue_.increment(pos_);
  return tmp;
}

template <typename T> INLINE bool
Const_AQueue_Reverse_Iterator<T>::operator== 
(const Const_AQueue_Reverse_Iterator<T> &rhs) const
{
  return &queue_ == &rhs.queue_ && pos_ == rhs.pos_;
}

template <typename T> INLINE bool
Const_AQueue_Reverse_Iterator<T>::operator!= 
(const Const_AQueue_Reverse_Iterator<T> &rhs) const
{
  return !(*this == rhs);
}

template <typename T>
Const_AQueue_Reverse_Iterator<T>::Const_AQueue_Reverse_Iterator 
(const AQueue<T> &queue, size_t pos)
: queue_ (queue),pos_ (pos % queue_.queue_.size())
{
}

#endif /* _AQUEUE_C */
