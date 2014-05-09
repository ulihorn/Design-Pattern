// Name: Xianshi Xie
//Email: xianshi.xie@vanderbilt.edu

#ifndef ARRAY_CPP
#define ARRAY_CPP

#include <sys/types.h>
#include "Array.h"
#include "scoped_array.h"

#if !defined (__INLINE__)
#define INLINE 
#include "Array.inl"
#endif /* __INLINE__ */

#include <algorithm>
#include <strstream>
#include <stdexcept>
#include <iostream>
#include <memory.h>
#include <sstream>


#define _SCL_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)


template <typename T> 
Array<T>::Array (size_t size):max_size_(size),cur_size_(size),
is_default_value_(false),default_value_(0),array_(new T[size])
{}

template <typename T> 
Array<T>::Array (size_t size,const T &default_value):max_size_(size),
cur_size_(size),is_default_value_(true),array_(0)
/* Doug's comment:
This code isn't strongly exception safe since memory will be leaked
and array_ will be left in an inconsistent state if an exception is
thrown.

> array_(new T[size])
> {
*/
//My response: replace this with array_(0) and swap array_ with scoped array

{
  //You can simplify this to be
  //       auto_ptr<T> auto_p(new T (default_value));
  //My response: replace auto_ptr<T> auto_p(new T);

  std::auto_ptr<T> auto_p(new T(default_value));

  scoped_array<T> temp_array(new T[size]);
  std::fill(&temp_array[0] , &temp_array[size] , default_value);
  default_value_ = auto_p.release();

  temp_array.swap(array_);
}

// The copy constructor (performs initialization).

template <typename T> 
Array<T>::Array (const Array<T> &s)
:max_size_(s.cur_size_),cur_size_(s.cur_size_),
is_default_value_(s.is_default_value_),array_(0)
{
  scoped_array<T> temp_array(new T[s.cur_size_]);
  std::copy(s.array_ , s.array_+s.cur_size_ , &temp_array[0]);

  std::auto_ptr<T> auto_p(new T);
  if (is_default_value_ ){
    //Doug's comment: Please don't set *auto_p to NULL 
    //since there's not guarantee that NULL
    //is a valid value for type T.
    //My response: replace  *auto_p = NULL with *auto_p = 0;
    //auto_p = 0;
    //else
    *auto_p = *s.default_value_;       
  }
  default_value_ = auto_p.release();

  temp_array.swap(array_);
}

template <typename T> void
Array<T>::resize (size_t new_size)
{
  bool resize_needed((is_default_value_ && new_size>cur_size_) || 
    (!is_default_value_ && new_size>max_size_));
  bool filling_needed (is_default_value_ && new_size>cur_size_);
  if (resize_needed)
  {
    scoped_array<T> temp_array(new T[new_size]);
    std::copy(array_,array_+cur_size_,temp_array.get());
    if ( filling_needed ){
      std::fill(&temp_array[cur_size_],&temp_array[new_size],
        *default_value_);
    }
    max_size_ = new_size ;
    temp_array.swap(array_);
  }      

  cur_size_ = new_size;
}

// Assignment operator (performs assignment). 

template <typename T> void 
Array<T>::operator= (const Array<T> &s)
{
  if (this == &s)  return;
  scoped_array<T> temp_array(new T[s.size()]);
  std::copy(s.array_ , s.array_+s.cur_size_ , &temp_array[0]);

  /*Doug's comment: Don't set max_size_ and cur_size_ until the rest 
  of the code below succeeds or your solution won't be strongly 
  exception safe. 
  >       max_size_ = s.cur_size_ ;
  >       cur_size_ = s.cur_size_;
  >       is_default_value_ = s.is_default_value_;

  >     auto_ptr<T> auto_p(new T);
  >     if (s.default_value_ == NULL)
  >         *auto_p = NULL;
  >     else
  >         *auto_p = *s.default_value_;*/
  //My response: reset max_size_&cur_size_ after *auto_p = *s.default_value_
  std::auto_ptr<T> auto_p(new T);
  if (s.is_default_value_)
    *auto_p = *s.default_value_;

  //Doug's comment: You need to make sure to delete default_value_ 
  //before you reassign to it or you'll leak memory.
  //My response: add the code to delete default_value_;
  delete default_value_;
  default_value_ = auto_p.release();

  temp_array.swap(array_);

  is_default_value_ = s.is_default_value_;
  max_size_ = s.cur_size_ ;
  cur_size_ = s.cur_size_;
}

// Clean up the array (e.g., delete dynamically allocated memory).

template <typename T> 
Array<T>::~Array (void)
{
  delete [] array_;
  delete default_value_;
}

// = Set/get methods.

// Set an item in the array at location index.  

template <typename T> void
Array<T>::set (const T &new_item, size_t index)
{
  if (!in_range(index)){
    resize(index+1);}
  array_[index] = new_item;
}

// Get an item in the array at location index.

template <typename T> void
Array<T>::get (T &item, size_t index)
{
  if ( in_range(index) )
    item = array_[index];
  else{
    std::stringstream s;
    s << (int)index;
    throw std::out_of_range(s.str());
  }
}

// Compare this array with <s> for equality.

template <typename T> bool
Array<T>::operator== (const Array<T> &s) const
{
  return cur_size_ == s.size() &&
    std::equal (s.array_ , s.array_ + s.cur_size_ ,array_);

}

// Compare this array with <s> for inequality.

template <typename T> bool
Array<T>::operator!= (const Array<T> &s) const
{
  return !( *this == s);
}

template <typename T>
Array_Iterator<T>::Array_Iterator (Array<T> &array, size_t pos)
:array_(array),pos_(pos % (array.size()+1))
{		
}

template <typename T>
Const_Array_Iterator<T>::Const_Array_Iterator 
(const Array<T> &array, size_t pos)
:array_(array),pos_(pos % (array.size()+1))
{
}

#endif /* ARRAY_CPP */
