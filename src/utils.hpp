#pragma once

#include <stdint.h>
#include <assert.h>

namespace tkc
{

typedef int32_t i32;
typedef int64_t i64;
typedef uint32_t u32;
typedef uint64_t u64;

template <typename T, size_t N>
constexpr size_t size(T(&)[N]) { return N; }

template <typename T, typename ST = u32>
class Span
{
    T* _begin, *_end;

public:
    Span() : _begin(nullptr), _end(nullptr) {}
    Span(T* begin, T* end) : _begin(begin), _end(end) {}
    Span(T* begin, ST numElems) : _begin(begin), _end(begin + numElems) {}
    template<int N>
    Span(T (&a)[N]) : _begin(a), _end(a + N) {}

    T* begin() { return _begin; }
    const T* begin()const { return _begin; }
    T* end() { return _end; }
    const T* end()const { return _end; }

    ST size()const { return _end - _begin; }

    T& operator[](ST i) { assert(i < size()); return _begin[i]; }
    const T& operator[](ST i)const { assert(i < size()); return _begin[i]; }
};

}