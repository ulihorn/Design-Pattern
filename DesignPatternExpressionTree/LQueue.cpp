// Name: Xianshi Xie
//Email: xianshi.xie@vanderbilt.edu

#if !defined (_LQUEUE_CPP)
#define _LQUEUE_CPP

#include "LQueue.h"
#include<memory>

#pragma warning(disable: 4355)
#pragma warning(disable: 4996)
// Forward declaration.
template <class T>
//typedef LQueue_Node<T>* NodePtr;
class LQueue_Node
  // = TITLE
  //     Defines an element in the <LQueue>.
{
  friend class LQueue<T>;
  friend class LQueue_Iterator<T>;
  friend class Const_LQueue_Iterator<T>;
  friend class LQueue_Reverse_Iterator<T>;
  friend class Const_LQueue_Reverse_Iterator<T>;

public:
  // = Initialization methods
  LQueue_Node (const T &item,
    LQueue_Node<T> *next = 0,
    LQueue_Node<T> *prev = 0);

  LQueue_Node (LQueue_Node<T> *next,
    LQueue_Node<T> *prev);

  LQueue_Node (void);
  // Default constructor that doesn't initialize <item_>.

  void *operator new (size_t bytes);
  // Allocate a new <LQueue_Node>, trying first from the
  // <free_list_> and if that's empty try from the global <::operator
  // new>.

  void operator delete (void *ptr);
  // Return <ptr> to the <free_list_>.

  static void free_list_allocate (size_t n);
  // Preallocate <n> <LQueue_Nodes> and store them on the
  // <free_list_>.

  static void free_list_release (void);
  // Returns all dynamic memory on the free list to the free store.


private:

  static LQueue_Node<T> *free_list_;
  // Head of the "free list", which is a stack of
  // <LQueue_Nodes> used to speed up allocation.

  T item_;
  // Item in this node.

  LQueue_Node<T> *next_;
  // Pointer to the next node.

  LQueue_Node<T> *prev_;
  // Pointer to the prev node.

};

/* static */
template <class T> LQueue_Node<T> *
LQueue_Node<T>::free_list_ = 0;

// Allocate a new <LQueue_Node>, trying first from the
// <free_list_> and if that's empty try from the global <::operator
// new>.

template <class T> void *
LQueue_Node<T>::operator new (size_t bytes)
{
  // You fill in here.
  if (free_list_ == 0){
    return ::operator new (sizeof(LQueue_Node<T>));
  }
  else{
    LQueue_Node<T>* tmp = free_list_;
    free_list_ = free_list_->next_;        
    return tmp;
  }  
}

// Return <ptr> to the <free_list_>.

template <class T> void
LQueue_Node<T>::operator delete (void *ptr)
{
  // You fill in here.
  //Doug's comment: Make sure to check whether ptr == 0 before proceeding.
  //My response: check whether prt == 0
  if (ptr == 0) return;
  LQueue_Node<T>* tmp = static_cast<LQueue_Node<T>*>(ptr);
  tmp->next_ = free_list_;
  free_list_ = tmp;

}

// Returns all dynamic memory on the free list to the free store.

template <class T> void 
LQueue_Node<T>::free_list_release (void)
{
  // You fill in here.

  while (free_list_ != 0){
    LQueue_Node<T>* tmp = free_list_;
    free_list_ = tmp->next_;
    ::operator delete (tmp);
  }

}

// Preallocate <n> <LQueue_Nodes> and store them on the
// <free_list_>.

template <class T> void 
LQueue_Node<T>::free_list_allocate (size_t n)
{
  // You fill in here.

  for (size_t i=0; i<n; i++){
    LQueue_Node<T> * NewPtr = static_cast< LQueue_Node<T> *>
      (::operator new (sizeof(LQueue_Node<T>)));
    NewPtr->next_ = free_list_;
    free_list_ = NewPtr;
  }

}

template <class T>
LQueue_Node<T>::LQueue_Node 
(const T &item,LQueue_Node<T> *next,LQueue_Node<T> *prev)
: item_ (item),next_ (next),prev_ (prev)
{
}

template <class T>
LQueue_Node<T>::LQueue_Node 
(LQueue_Node<T> *next,LQueue_Node<T> *prev)
: next_ (next),prev_ (prev)
{
}

template <class T>
LQueue_Node<T>::LQueue_Node (void)
// this is helpful to implement the dummy node in a concise way.
: next_ (this),
prev_ (this)
{
}

// Returns the current size.
template <class T> size_t 
LQueue<T>::size (void) const
{
  return count_;
}

// Constructor.

template <class T>
LQueue<T>::LQueue (size_t size_hint)
// Initialize fields here.
: tail_ (0),
count_ (0)
{
  // You fill in here.
  LQueue_Node<T>::free_list_allocate(size_hint);
  tail_ = new LQueue_Node<T>();
}

// Copy constructor.

template <class T>
LQueue<T>::LQueue (const LQueue<T> &rhs)
// Initialize fields here.
: tail_ (0),
count_ (0) // count_ will be set correctly by copy_list
{
  // You fill in here.
  this->copy_list(rhs);
}

// Copy a linked list of nodes
template <class T> void
LQueue<T>::copy_list (const LQueue<T> &rhs)
{
  // You fill in here.
  //Doug's comment: Don't call delete_list() here.
  //My response: remove delete_list()

  /*
  Rather than copying rhs into *this queue I recommend you copy it into
  a temporary queue and then swap the data members (using std::swap()).
  This has the benefit of being strongly exception safe.  Also, you
  should use thr LQueue<T>::iterator associated with rhs rather than
  using the next_ pointer directly.
  */
  //My response:
  LQueue<T> temp(rhs.count_);
  if (!rhs.is_empty())
  {
    for(typename LQueue<T>::const_iterator it=rhs.begin();it!=rhs.end();++it)
    {
      temp.enqueue(*it);
    }
  }
  std::swap(tail_,temp.tail_);
  std::swap(count_,temp.count_);

}

// Delete a linked list of nodes
template <class T> void
LQueue<T>::delete_list ()
{
  // You fill in here.
  //Doug's comment: Please use while (!is_empty()) here.
  //My response: use !is_empty() instead of count_
  while(!is_empty()){
    dequeue_i();
  }
  //Doug's comment: I recommend not deleting tail_ here.
  //My response: remove  delete tail_;
}

// Assignment operator.
template <class T> LQueue<T> &
LQueue<T>::operator= (const LQueue<T> &rhs) 
{
  // You fill in here.
  if (this != &rhs){
    copy_list(rhs);
    //Doug's comment: copy_list() should handle the count_ assignment.
    //My response: remove  count_ = rhs.count_;
  }

  return *this;

}

// Perform actions needed when queue goes out of scope.

template <class T>
LQueue<T>::~LQueue (void)
{
  // You fill in here.
  delete_list();

  //Doug's comment: I recommend calling  delete tail_ here.
  //My response: add delete tail_;
  delete tail_;

}

// Compare this queue with <rhs> for equality.  Returns true if the
// size()'s of the two queues are equal and all the elements from 0
// .. size() are equal, else false.
template <class T> bool 
LQueue<T>::operator== (const LQueue<T> &rhs) const
{
  // You fill in here.
  return count_ == rhs.count_ && std::equal(begin(),end(),rhs.begin());
}

// Compare this queue with <rhs> for inequality such that <*this> !=
// <s> is always the complement of the boolean return value of
// <*this> == <s>.

template <class T> bool 
LQueue<T>::operator!= (const LQueue<T> &rhs) const
{
  return !(*this == rhs);
}

// Place a <new_item> at the tail of the queue.  Throws
// the <Overflow> exception if the queue is full.

template <class T> void
LQueue<T>::enqueue (const T &new_item)
{
  // You fill in here.

  try{
    tail_->item_ = new_item;
    tail_ = tail_->next_ = new LQueue_Node<T>(tail_->next_,tail_);   
    tail_->next_->prev_ = tail_->next_;
    count_++;    
  }
  catch (std::bad_alloc)
  {
    //Doug's comment: This should be fixed with the latest shells.
    //My response: use latest shells, and use Overflow() below.
    throw Overflow();

  }
}

// Remove and return the front item on the queue.  
// Throws the <Underflow> exception if the queue is empty. 

template <class T> T 
LQueue<T>::dequeue (void)
{
  // You fill in here.
  if(!is_empty())
  {
    T tmp = tail_->next_->item_;
    dequeue_i();
    return tmp;
  }
  else
    throw Underflow();
}

template <class T> void
LQueue<T>::dequeue_i (void)
{
  // You fill in here.
  LQueue_Node<T>* del = tail_->next_;
  tail_->next_ = del->next_;
  del->next_->prev_ = tail_;
  delete del;
  count_--;
}

// Returns the front queue item without removing it. 
// Throws the <Underflow> exception if the queue is empty. 

template <class T> T 
LQueue<T>::front (void) const
{
  // You fill in here.
  if (!is_empty())
    return tail_->next_->item_;
  else
    throw Underflow();
}

// Returns true if the queue is empty, otherwise returns false.

template <class T> bool
LQueue<T>::is_empty (void) const 
{
  // You fill in here.
  return count_ == 0;
}

// Returns true if the queue is full, otherwise returns false.

template <class T> bool
LQueue<T>::is_full (void) const 
{
  // there is no upper limit for the queue
  return false;
}

// Get an iterator to the begining of the queue
template <typename T> typename LQueue<T>::iterator
LQueue<T>::begin (void)
{
  // You fill in here.
  return iterator(*this,tail_->next_);
}

// Get an iterator pointing past the end of the queue
template <typename T> typename LQueue<T>::iterator
LQueue<T>::end (void)
{
  // You fill in here.
  return iterator(*this,tail_);
}

// Get an iterator to the begining of the queue
template <typename T> typename LQueue<T>::const_iterator
LQueue<T>::begin (void) const
{
  // You fill in here.
  return const_iterator(*this,tail_->next_);
}

// Get an iterator pointing past the end of the queue
template <typename T> typename LQueue<T>::const_iterator
LQueue<T>::end (void) const
{
  // You fill in here.
  return const_iterator(*this,tail_);
}

// Get an iterator to the end of the queue
template <typename T> typename LQueue<T>::reverse_iterator
LQueue<T>::rbegin (void)
{
  return reverse_iterator(*this,tail_->prev_);
}

// Get an iterator pointing to the beginning of the queue
template <typename T> typename LQueue<T>::reverse_iterator
LQueue<T>::rend (void)
{
  return reverse_iterator(*this,tail_);
}

// Get an iterator to the end of the queue
template <typename T> typename LQueue<T>::const_reverse_iterator
LQueue<T>::rbegin (void) const
{
  return const_reverse_iterator(*this,tail_->prev_);
}

// Get an iterator pointing to the beginning of the queue
template <typename T> typename LQueue<T>::const_reverse_iterator
LQueue<T>::rend (void) const
{
  return const_reverse_iterator(*this,tail_);
}

template <typename T> T &
LQueue_Iterator<T>::operator* (void)
{
  // You fill in here.
  return pos_->item_;
}

template <typename T> const T &
LQueue_Iterator<T>::operator* (void) const
{
  // You fill in here.
  return pos_->item_;
}

template <typename T> LQueue_Iterator<T> &
LQueue_Iterator<T>::operator++ (void) 
{
  // You fill in here.
  pos_ = pos_->next_;
  return *this;
}

// Post-increment.
template <typename T> LQueue_Iterator<T> 
LQueue_Iterator<T>::operator++ (int) 
{
  // You fill in here.
  LQueue_Iterator<T> tmp=*this;
  pos_ = pos_->next_;
  return tmp;

}

template <typename T> LQueue_Iterator<T> &
LQueue_Iterator<T>::operator-- (void) 
{
  // You fill in here.
  pos_ = pos_->prev_;
  return *this;
}

// Post-increment.
template <typename T> LQueue_Iterator<T> 
LQueue_Iterator<T>::operator-- (int) 
{
  // You fill in here.
  LQueue_Iterator<T> tmp=*this;
  pos_ = pos_->prev_;
  return tmp;

}

template <typename T> bool
LQueue_Iterator<T>::operator== (const LQueue_Iterator<T> &rhs) const
{
  // You fill in here.
  return pos_ == rhs.pos_;
}

template <typename T> bool
LQueue_Iterator<T>::operator!= (const LQueue_Iterator<T> &rhs) const
{
  // implement != in terms of ==
  return !(*this == rhs);
}


template <typename T>
LQueue_Iterator<T>::LQueue_Iterator (LQueue<T> &queue,LQueue_Node<T> *pos)
:queue_(queue),pos_(pos)
// You fill in here.
{
}

template <typename T> const T &
Const_LQueue_Iterator<T>::operator* (void) const
{
  // You fill in here.
  return pos_->item_;
}

template <typename T> const Const_LQueue_Iterator<T> &
Const_LQueue_Iterator<T>::operator++ (void) const
{
  // You fill in here.
  pos_ = pos_->next_;
  return *this;
}

template <typename T> Const_LQueue_Iterator<T>
Const_LQueue_Iterator<T>::operator++ (int) const
{
  // You fill in here.
  Const_LQueue_Iterator<T> tmp=*this;
  pos_ = pos_->next_;
  return tmp;

}

template <typename T> const Const_LQueue_Iterator<T> &
Const_LQueue_Iterator<T>::operator-- (void) const
{
  // You fill in here.
  pos_ = pos_->prev_;
  return *this;
}

template <typename T> Const_LQueue_Iterator<T>
Const_LQueue_Iterator<T>::operator-- (int) const
{
  // You fill in here.
  Const_LQueue_Iterator<T> tmp=*this;
  pos_ = pos_->prev_;
  return tmp;
}

template <typename T> bool
Const_LQueue_Iterator<T>::operator== 
(const Const_LQueue_Iterator<T> &rhs) const
{
  // You fill in here.
  return pos_ == rhs.pos_;
}

template <typename T> bool
Const_LQueue_Iterator<T>::operator!= 
(const Const_LQueue_Iterator<T> &rhs) const
{
  return !(*this == rhs);
}



template <typename T>
Const_LQueue_Iterator<T>::Const_LQueue_Iterator 
(const LQueue<T> &queue,LQueue_Node<T> *pos)
:queue_(queue),pos_(pos)
// You fill in here.
{
}


//////Below is the part I added.

template <typename T> T &
LQueue_Reverse_Iterator<T>::operator* (void)
{
  // You fill in here.
  return pos_->item_;
}

template <typename T> const T &
LQueue_Reverse_Iterator<T>::operator* (void) const
{
  // You fill in here.
  return pos_->item_;
}

template <typename T> LQueue_Reverse_Iterator<T> &
LQueue_Reverse_Iterator<T>::operator++ (void) 
{
  // You fill in here.
  pos_ = pos_->prev_;
  return *this;
}

// Post-increment.
template <typename T> LQueue_Reverse_Iterator<T> 
LQueue_Reverse_Iterator<T>::operator++ (int) 
{
  // You fill in here.
  LQueue_Reverse_Iterator<T> tmp=*this;
  pos_ = pos_->prev_;
  return tmp;

}

template <typename T> LQueue_Reverse_Iterator<T> &
LQueue_Reverse_Iterator<T>::operator-- (void) 
{
  // You fill in here.
  pos_ = pos_->next_;
  return *this;
}

// Post-increment.
template <typename T> LQueue_Reverse_Iterator<T> 
LQueue_Reverse_Iterator<T>::operator-- (int) 
{
  // You fill in here.
  LQueue_Reverse_Iterator<T> tmp=*this;
  pos_ = pos_->next_;
  return tmp;

}

template <typename T> bool
LQueue_Reverse_Iterator<T>::operator== 
(const LQueue_Reverse_Iterator<T> &rhs) const
{
  // You fill in here.
  return  pos_ == rhs.pos_;
}

template <typename T> bool
LQueue_Reverse_Iterator<T>::operator!= 
(const LQueue_Reverse_Iterator<T> &rhs) const
{
  // implement != in terms of ==
  return !(*this == rhs);
}


template <typename T>
LQueue_Reverse_Iterator<T>::LQueue_Reverse_Iterator 
(LQueue<T> &queue,LQueue_Node<T>* pos)
:queue_(queue),pos_(pos)
{
}

//below is const_reverse part

template <typename T> const T &
Const_LQueue_Reverse_Iterator<T>::operator* (void) const
{
  // You fill in here.
  return pos_->item_;
}

template <typename T> const Const_LQueue_Reverse_Iterator<T> &
Const_LQueue_Reverse_Iterator<T>::operator++ (void) const
{
  // You fill in here.
  pos_ = pos_->prev_;
  return *this;
}

template <typename T> Const_LQueue_Reverse_Iterator<T>
Const_LQueue_Reverse_Iterator<T>::operator++ (int) const
{
  // You fill in here.
  Const_LQueue_Reverse_Iterator<T> tmp=*this;
  pos_ = pos_->prev_;
  return tmp;
}

template <typename T> const Const_LQueue_Reverse_Iterator<T> &
Const_LQueue_Reverse_Iterator<T>::operator-- (void) const
{
  // You fill in here.
  pos_ = pos_->next_;
  return *this;
}

template <typename T> Const_LQueue_Reverse_Iterator<T>
Const_LQueue_Reverse_Iterator<T>::operator-- (int) const
{
  // You fill in here.
  Const_LQueue_Reverse_Iterator<T> tmp=*this;
  pos_ = pos_->next_;
  return tmp;
}

template <typename T> bool
Const_LQueue_Reverse_Iterator<T>::operator== 
(const Const_LQueue_Reverse_Iterator<T> &rhs) const
{
  // You fill in here.
  return  pos_ == rhs.pos_;
}

template <typename T> bool
Const_LQueue_Reverse_Iterator<T>::operator!= 
(const Const_LQueue_Reverse_Iterator<T> &rhs) const
{
  return !(*this == rhs);
}



template <typename T>
Const_LQueue_Reverse_Iterator<T>::Const_LQueue_Reverse_Iterator 
(const LQueue<T> &queue,LQueue_Node<T>* pos)
:queue_(queue),pos_(pos)
// You fill in here.
{
}



////Above is the part I added.


#endif /* _LQUEUE_CPP */
