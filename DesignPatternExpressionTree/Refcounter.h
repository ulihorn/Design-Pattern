//Name: Xianshi Xie
//Email: xianshi.xie@vanderbilt.edu

/* -*- C++ -*- */
#ifndef _REFCOUNTER_H_
#define _REFCOUNTER_H_

/**
* @class Refcounter
* @brief This class does reference counting in its constructor and
*        destructor.  The template parameter T must have a member element
*        "int use_"
*/
template <class T>
class Refcounter
{
public:
  /// default Ctor
  Refcounter (void):ptr_(0)
    // You fill in here.
  {
  }

  /// Ctor with refcounting functionality
  /// @param ptr of the object that should be managed
  /// @param own indicates if Refcounter should take ownership
  Refcounter (T* ptr, bool increase_count = false)
    : ptr_ (ptr)
  {
    // by default we assume, the ptr will be created with use_ = 1 and
    // that the Refcounter is taking over ownership, meaning, that is
    // responsible for deletion of the ptr.  If this is not the case,
    // the user can set increase count to true, which results in
    // incrementing the reference count for a passed in object.

    if (increase_count)
      increment ();
  }

  /// copy Ctor
  Refcounter (const Refcounter& rhs)
    // You fill in here.
    :ptr_(rhs.ptr_)
  {
    increment ();
  }

  /// Dtor will delete pointer if refcount becomes 0
  virtual ~Refcounter (void)
  {
    decrement ();
  }

  /// assignment operator
  void operator= (const Refcounter& rhs)
  {
    if (this != &rhs)
    {
      decrement ();

      // You fill in here.
      ptr_ = rhs.ptr_;

      increment ();
    }
  }

  /// dereference operator
  T* operator-> (void) const
  {
    return ptr_;
  }


  ////Below is what I added.

  //return pointer ptr_
  T * get_ptr(void) const
  {
    return ptr_;
  }

  //return the object to which pointer ptr_ points
  T & operator* (void)
  {
    return *ptr_;
  }

  //return the object to which pointer ptr_ points
  const T & operator* (void) const
  {
    return *ptr_;
  }

  //equality checking
  bool operator==(const Refcounter &rhs) const
  {
    return ptr_ == rhs.ptr_;
  }

  //in-equality checking
  bool operator!=(const Refcounter &rhs) const
  {
    return !(ptr_ == rhs.ptr_);
  }



  ////Above is what I added.


  // check if ptr_ is null pointer.
  bool is_null (void) const
  {
    return this->ptr_ == 0;
  }

private:

  /// implementation of the increment operation
  void increment (void)
  {
    if (this->ptr_ != 0)
      this->ptr_->use_ ++;
  }

  /// implementation of the decrement operation
  void decrement (void)
  {
    if (this->ptr_ != 0)
    {
      this->ptr_->use_--;

      // You fill in here.
      if (this->ptr_->use_ == 0) delete this->ptr_;
    }
  }


private:
  /// reference to the refcounted object
  T *ptr_;
};

#endif /* _REFCOUNTER_H_ */
