
#ifndef _TINYSTL_ALLOC_H
#define _TINYSTL_ALLOC_H

#include <stdlib.h>

#include <new>

// __malloc_alloc_template
// 一级配置器
template<int __inst>
class __malloc_alloc_template {

private:
  static void* _oom_malloc(size_t);
  static void* _oom_realloc(void*, size_t);

  static void (* _malloc_alloc_oom_handler)();

public:
  static void* allocate(size_t n)
  {
    void* _result = malloc(n);

    if(_result == 0) 
      _result = _oom_malloc(n);

    return _result;
  }

  static void* deallocate(void* _ptr, size_t /* _n */)
  {
    free(_ptr);
  }

  static void* reallocate(void* _ptr, size_t /* _old_size */, size_t _new_size)
  {
    void* _result = realloc(_ptr, _new_size);

    if(_result == 0) 
      _result = _oom_realloc(_ptr, _new_size);

    return _result;
  }

  static void (* set_malloc_alloc_oom_handler(void (*_f)()))()
  {
    void (*old_handler)() = _malloc_alloc_oom_handler;
    _malloc_alloc_oom_handler = _f;
    return old_handler;
  }
};

template<int __inst>
void (* __malloc_alloc_template<__inst>::_malloc_alloc_oom_handler)() = 0;

template<int __inst>
void*
__malloc_alloc_template<__inst>::_oom_malloc(size_t _n)
{
  void* _result;
  void (* _oom_handler)();

  for(;;) 
  {
    _oom_handler = _malloc_alloc_oom_handler;
    if(_oom_handler == 0) throw std::bad_alloc();
    (*_oom_handler)();
    _result = malloc(_n);
    if(_result) return _result;
  }
}

template<int __inst>
void*
__malloc_alloc_template<__inst>::_oom_realloc(void* _ptr, size_t _n)
{
  void* _result;
  void (* _oom_handler)();

  for(;;)
  {
    _oom_handler = _malloc_alloc_oom_handler;
    if(_oom_handler == 0) throw std::bad_alloc();
    (*_oom_handler)();
    _result = realloc(_ptr, _n);
    if(_result) return _result;
  }
}

typedef __malloc_alloc_template<0> malloc_alloc;  // 第一级配置器

template<typename _Tp, typename _Alloc>
class simple_alloc {

public:
  static _Tp* allocate(size_t _n)
  { return (n==0) ? 0 : _Alloc::allocate(_n * sizeof(_Tp)); }
  static _Tp* allocate(void)
  { return _Alloc::allocate(sizeof(_Tp)); }
  static void deallocate(void* _ptr, size_t _n)
  { if(n!=0) _Alloc::deallocate(_ptr, _n * sizeof(_Tp)); }
  static void deallocate(void* _ptr)
  { _Alloc::deallocate(_ptr); }
};

template<typename _Alloc>
class debug_alloc {

private:
  const size_t __extra = sizeof size_t;

public:
  static void* allocate(size_t _n)
  {
    void* _result = _Alloc(_n + __extra);
    *(size_t*)_result = _n;
    return _result + __extra;
  }

  static void deallocate(void* _ptr, size_t _n)
  {
    void* _real_ptr = _ptr - __extra;
    assert(*(size_t*)_real_ptr == _n);
    _Alloc::deallocate(_real_ptr, _n + __extra);
  }

  static void* reallocate(void* _ptr, size_t _old_size, size_t _new_size)
  {
    void* _real_ptr = _ptr - __extra;
    assert(*(size_t*)_real_ptr == _old_size);
    void* _result = _Alloc::reallocate(_real_ptr, 
                                       _old_size + __extra,
                                       _new_size + __extra);
    *(size_t*)_result = _new_size;
    return _result + __extra;
  }
};

//  __default_alloc_template
//  二级配置器
template<typename __inst>
class __default_alloc_template {

private:
  enum {
    _ALIGN = 8,
    _MAX_BYTES = 128,
    _NFREELISTS = 16
  };

private:
  union _OBJ{
    _OBJ* _free_link_list;
    char _client_data[1];
  };

  static _OBJ* _free_list[];

  // 上舍入至_ALIGN的倍数
  static size_t _round_up(size_t _n)
  {
    return (_n + (_ALIGN - 1)) & (~(_ALIGN - 1));
  }

  // 根据块大小找到合适的下标，从0开始
  static size_t _find_index(size_t _n_bytes)
  {
    assert(_n_bytes != 0);
    return (_n_bytes - 1) / _ALIGN;
  }

  static void* _refill(size_t _n);
  static void* _trunk_alloc(size_t _size, size_t _OBJS);

private:
  // 内存池信息
  static void* _memory_pool_start;
  static void* _memory_pool_end;
  size_t _heap_size;

public:
  static void* allocate(size_t _n)
  {
    if(_n == 0) return (void*)0;
    if(_n > _MAX_BYTES) 
      return malloc_alloc::allocate(_n);
    
    void* _result;
    size_t _idx = _find_index(_n);
    _OBJ* _my_free_link_list = _free_list[_idx];
    
    if(_my_free_link_list == 0)
    {
      _my_free_link_list = _refill(_round_up(_n));
    }

    _free_list[_idx] = _my_free_link_list->_free_link_list;
    _result = _(void*)_my_free_link_list;

    return _result;
  }

  static void deallocate(void* _ptr, size_t _n)
  {
    if(_n > _MAX_BYTES)
      malloc_alloc::deallocate(_ptr, _n);
    
    size_t _idx = _find_index(_n);
    (static_cast<_OBJ*>(_ptr))->_free_link_list = _free_list[_idx];
    _free_list[_idx] = (_OBJ*)_ptr;
  }

};

#endif  /* TINYSTL_ALLOC_H */
