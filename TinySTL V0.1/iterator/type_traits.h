
#ifndef _TINYSTL_TYPE_TRAITS
#define _TINYSTL_TYPE_TRAITS

struct __true_type {};
struct __false_type {};

template<typename _Tp>
struct __type_traits 
{
  // 参考 SGI
  typedef __true_type this_dummy_must_be_first;
  /* Do not remove this member. It informs a compiler which
  automatically specializes __type_traits that this
  __type_traits template is special. It just makes sure that
  things work if an implementation is using a template
  called __type_traits for something unrelated. */
  
  typedef __false_type has_trivial_default_constructor;
  typedef __false_type has_trivial_constructor;
  typedef __false_type has_trivial_destructor;
  typedef __false_type is_POD_type;
};

template<> struct __type_traits<bool>
{
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_constructor;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

template<> struct __type_traits<char>
{
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_constructor;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

template<> struct __type_traits<unsigned char>
{
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_constructor;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

template<> struct __type_traits<signed char>
{
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_constructor;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

template<> struct __type_traits<short>
{
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_constructor;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

template<> struct __type_traits<unsigned short>
{
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_constructor;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

template<> struct __type_traits<int>
{
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_constructor;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

template<> struct __type_traits<unsigned int>
{
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_constructor;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

template<> struct __type_traits<long>
{
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_constructor;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

template<> struct __type_traits<unsigned long>
{
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_constructor;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

template<> struct __type_traits<long long>
{
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_constructor;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

template<> struct __type_traits<unsigned long long>
{
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_constructor;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

template<> struct __type_traits<float>
{
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_constructor;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

template<> struct __type_traits<double>
{
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_constructor;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

template<> struct __type_traits<long double>
{
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_constructor;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

template<typename _Tp>
struct __type_traits<_Tp*>
{
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_constructor;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

#endif  /* _TINYSTL_TYPE_TRAITS */
