
#ifndef _TINYSTL_CONSTRUCT_H
#define _TINYSTL_CONSTRUCT_H

#include <new>

// construct
template<typename _T, typename _Tp>
inline void construct(_T* _ptr, const _Tp& _value)
{
  new ((void*)_ptr) _Tp(value);
}

template<typename _T>
inline void construct(_T* _ptr)
{
  new ((void*)_ptr) _T();
}

// destroy 
/* 直接销毁对象 */
template<typename _T>
inline void destroy(_T* _ptr)
{
  _ptr->~_T();
}

// 迭代器所指对象为__true_type，则什么都不做
template<typename _Iterator>
inline void 
__destroy_aux(_Iterator _first, _Iterator _last, __true_type) {}

template<typename _Iterator>
inline void
__destroy_aux(_Iterator _first, _Iterator _last, __false_type)
{
  while (_first != _last)
  {
    destroy(&*_first);
    _first++;
  }
}

template<typename _Iterator, typename _Tp>
inline void __destroy(_Iterator _first, _Iterator _last, _Tp*)
{
  using _has_trivial_destructor = __type_traits<_Tp>::has_trivial_destructor;
  __destroy_aux(_first, _last, _has_trivial_destructor());
}

/* 范围销毁对象 */
template<typename _Iterator>
inline void destroy(_Iterator _first, _Iterator _last)
{
  __destroy(_first, _last, value_type(_first));
}

#endif  /* _TINYSTL_CONSTRUCT_H */
