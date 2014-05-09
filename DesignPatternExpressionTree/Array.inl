// Name: Xianshi Xie
//Email: xianshi.xie@vanderbilt.edu

#pragma warning(disable: 4172)

// Returns the current size of the array.

template <typename T> INLINE size_t 
Array<T>::size (void) const
{
  return cur_size_;
}

template <typename T> INLINE bool
Array<T>::in_range (size_t index) const
{
  return index < cur_size_;
}

template <typename T> INLINE T &
Array<T>::operator[] (size_t index)
{
  return array_[index];
}

template <typename T> INLINE const T &
Array<T>::operator[] (size_t index) const
{
  return array_[index];
}

// Get an iterator to the begniing of the array
template <typename T> INLINE typename Array<T>::iterator
Array<T>::begin (void)
{
  return Array_Iterator<T>(*this,0);
}

// Get an iterator pointing past the end of the array
template <typename T> INLINE typename Array<T>::iterator
Array<T>::end (void)
{
  return Array_Iterator<T>(*this,cur_size_);
}

// Get an iterator to the begniing of the array
template <typename T> INLINE typename Array<T>::const_iterator
Array<T>::begin (void) const
{
  return Const_Array_Iterator<T>(*this,0);
}

// Get an iterator pointing past the end of the array
template <typename T> INLINE typename Array<T>::const_iterator
Array<T>::end (void) const
{
  return Const_Array_Iterator<T>(*this,cur_size_);
}

template <typename T> INLINE T &
Array_Iterator<T>::operator* (void)
{
  return array_[pos_];
}

template <typename T> INLINE const T &
Array_Iterator<T>::operator* (void) const
{
  return array_[pos_];
}

template <typename T> INLINE Array_Iterator<T> &
Array_Iterator<T>::operator++ (void) 
{
  pos_++;
  return *this;
}

template <typename T> INLINE Array_Iterator<T> 
Array_Iterator<T>::operator++ (int) 
{
  //Doug's comment: Please just say
  //     return Array_Iterator<T> tmp (*this, pos_++);
  //My response: replace my codes with 
  //return Array_Iterator<T>  (array_, pos_++);

  return Array_Iterator<T> (array_, pos_++);
}

template <typename T> INLINE Array_Iterator<T> &
Array_Iterator<T>::operator-- (void)
{
  pos_--;
  return *this;
}

template <typename T> INLINE Array_Iterator<T>
Array_Iterator<T>::operator-- (int) 
{
  //Doug's comment: Please just say
  //     return Array_Iterator<T> tmp (*this, pos_--);
  //My response: replace my codes with 
  //return Array_Iterator<T>  (array_, pos_--);

  return Array_Iterator<T> (array_, pos_--);
}

template <typename T> INLINE bool
Array_Iterator<T>::operator== (const Array_Iterator<T> &rhs) const
{
  return &array_ == &rhs.array_ && pos_ == rhs.pos_;
}

template <typename T> INLINE bool
Array_Iterator<T>::operator!= (const Array_Iterator<T> &rhs) const
{
  return !( *this == rhs );
}

template <typename T> INLINE const T &
Const_Array_Iterator<T>::operator* (void) const
{
  return array_[pos_];
}

template <typename T> INLINE const Const_Array_Iterator<T> &
Const_Array_Iterator<T>::operator++ (void) const
{
  pos_++;
  return *this;
}

template <typename T> INLINE Const_Array_Iterator<T> 
Const_Array_Iterator<T>::operator++ (int) const
{
  //Doug's comment: Please just say
  //     return Const_Array_Iterator<T> tmp (*this, pos_++);
  //My response: replace my codes with 
  //return Const_Array_Iterator<T>  (array_, pos_++);

  return Const_Array_Iterator<T>  (array_, pos_++);
}

template <typename T> INLINE const Const_Array_Iterator<T> &
Const_Array_Iterator<T>::operator-- (void) const
{
  pos_--;
  return *this;
}

template <typename T> INLINE Const_Array_Iterator<T>
Const_Array_Iterator<T>::operator-- (int) const
{
  //Doug's comment: Please just say
  //     return Const_Array_Iterator<T> tmp (*this, pos_--);
  //My response: replace my codes with 
  //return Const_Array_Iterator<T>  (array_, pos_--);
  return Const_Array_Iterator<T>  (array_, pos_--);
}

template <typename T> INLINE bool
Const_Array_Iterator<T>::operator== (const Const_Array_Iterator<T> &rhs) const
{
  return this == &rhs && pos_ == rhs.pos_;
}

template <typename T> INLINE bool
Const_Array_Iterator<T>::operator!= (const Const_Array_Iterator<T> &rhs) const
{
  return !(this == &rhs);
}

