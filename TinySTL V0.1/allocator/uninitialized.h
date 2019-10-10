
#ifndef _TINYSTL_UNINITIALIZED_H
#define _TINYSTL_UNINITIALIZED_H

// copy
template<typename _InputIter, typename _ForwardIter, typename _Tp>
inline _ForwardIter
__uninitialized_copy_aux(_InputIter _first, 
                     _InputIter _last,
                     _ForwardIter _result,
                     __true_type)
{
  return std::copy(_first, _last, _result);
}

template<typename _InputIter, typename _ForwardIter, typename _Tp>
inline _ForwardIter
__uninitialized_copy_aux(_InputIter _first, 
                         _InputIter _last, 
                         _ForwardIter _result,
                         __false_type)
{
  _ForwardIter _cur = _result;
  try
  {
    for(; _first != _last; ++first, ++_cur)
      construct(&*_cur, *_first);
    return _cur;
  }
  catch(...)
  {
    destroy(_result, _cur);
    throw ;
  }
}

template<typename _InputIter, typename _ForwardIter, typename _Tp>
inline _ForwardIter
__uninitialized_copy(_InputIter _first,
                     _InputIter _last,
                     _ForwardIter _result,
                     _Tp*)
{
  using is_POD_type = __type_traits<_Tp>::is_POD_type;
  return __uninitialized_copy_aux(_first, _last, _result, is_POD_type());
}

template<typename _InputIter, typename _ForwardIter>
inline _ForwardIter
uninitialized_copy(_InputIter _first, _InputIter _last, _ForwardIter _result)
{
  return __uninitialized_copy(_first, _last, _result, value_type(_result));
}

// fill
template<typename _ForwardIter, typename _T>
inline void
__uninitialized_fill(_ForwardIter _begin,
                     _ForwardIter _end,
                     const _T& _value,
                     __true_type)
{
  std::fill(_begin, _end, _value);
}

template<typename _ForwardIter, typename _T>
inline void
__uninitialized_fill(_ForwardIter _begin,
                     _ForwardIter _end,
                     const _T& _value,
                     __false_type)
{
  _ForwardIter _cur = _begin;
  try
  {
    for(; _cur != _end; ++_cur)
      construct(&*_cur, _value);
  }
  catch(...)
  {
    destroy(_begin, _cur);
    throw ;
  }
}

template<typename _ForwardIter, typename _T, typename _Tp>
inline void
__uninitialized_fill(_ForwardIter _begin,
                     _ForwardIter _end,
                     const _T& _value,
                     _Tp*)
{
  using is_POD_type = __type_traits<_Tp>::is_POD_type;
  return __uninitialized_fill_aux(_begin, _end, _value, is_POD_type());
}

template<typename _ForwardIter, typename _T>
inline void
uninitialized_fill(_ForwardIter _begin, _ForwardIter _end, const _T& _value)
{
  return __uninitialized_fill(_begin, _end, _value, value_type(_begin));
}

#endif  /* _TINYSTL_UNINITIALIZED_H */
