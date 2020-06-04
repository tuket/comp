#pragma once

namespace tkc
{

template <typename T, size_t N>
constexpr size_t size(T(&)[N]) { return N; }

//char* loadStringFromfile(const* fileName);

}