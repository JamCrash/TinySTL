
#ifndef _TINYSTL_ITERATOR_H
#define _TINYSTL_ITERATOR_H

#include <stddef.h>

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag: public input_iterator_tag{};
struct bidirectional_iterator_tag: public forward_iterator_tag {};
struct random_access_iterator_tag: public bidirectional_iterator_tag {};

template<typename _Tp, typename _Distance> struct input_iterator {
  typedef input_iterator_tag  iterator_category;
  typedef _Tp                 value_type;
  typedef _Distance           difference_type;
  typedef _Tp*                pointer;
  typedef _Tp&                reference;
};

struct output_iterator {
  typedef output_iterator_tag   iterator_category;
  typedef void                  value_type;
  typedef void                  difference_type;  
  typedef void                  pointer;
  typedef void                  reference;
};

template<typename _Tp, typename _Distance> struct forward_iterator {
  typedef forward_iterator_tag  iterator_category;
  typedef _Tp                   value_type;
  typedef _Distance             difference_type;
  typedef _Tp*                  pointer;
  typedef _Tp&                  reference;
};

template<typename _Tp, typename _Distance> struct bidirectional_iterator {
  typedef bidirectional_iterator_tag  iterator_category;
  typedef _Tp                         value_type;
  typedef _Distance                   difference_type;
  typedef _Tp*                        pointer;
  typedef _Tp&                        reference;
};

template<typename _Tp, typename _Distance> struct random_access_iterator {
  typedef random_access_iterator_tag  iterator_category;
  typedef _Tp                         value_type;
  typedef _Distance                   difference_type;
  typedef _Tp*                        pointer;
  typedef _Tp&                        reference;
};

template<typename _Iterator>
struct iterator_traits {
  typedef typename _Iterator::iterator_category iterator_category;
  typedef typename _Iterator::value_type        value_type;
  typedef typename _Iterator::difference_type   difference_type;
  typedef typename _Iterator::pointer           pointer;
  typedef typename _Iterator::reference         reference;
};

template<typename _Tp>
struct iterator_traits<_Tp*> {
  typedef random_access_iterator_tag  iterator_category;
  typedef _Tp                         value_type;
  typedef ptrdiff_t                   difference_type;
  typedef _Tp*                        pointer;
  typedef _Tp&                        reference;
};

template<typename _Tp>
struct iterator_traits<const _Tp*> {
  typedef random_access_iterator_tag  iterator_category;
  typedef _Tp                         value_type;
  typedef ptrdiff_t                   difference_type;
  typedef const _Tp*                        pointer;
  typedef const _Tp&                        reference;
};

template<typename _Iter>
inline typename iterator_traits<_Iter>::iterator_category
iterator_category(const _Iter&)
{
  typedef typename iterator_traits<_Iter>::iterator_category _Category;
  return _Category();
}

template<typename _Iter>
inline typename iterator_traits<_Iter>::value_type*
value_type(const _Iter&)
{
  return static_cast<typename iterator_traits<_Iter>::value_type*>(0);
}

template<typename _Iter>
inline typename iterator_traits<_Iter>::difference_type*
difference_type(const _Iter&)
{
  return static_cast<typename iterator_traits<_Iter>::difference_type*>(0);
}

template<typename _InputIterator, typename _Distance>
inline void __distance(_InputIterator _first, _InputIterator _last, 
                  _Distance& _n, input_iterator_tag)
{
  while(_first != _last) { ++_first; ++_n; }
}



#endif  /* _TINYSTL_ITERATOR_H */
