#pragma once

#include <iterator>
#include <compare>
#include <type_traits>
#include <span>


template <typename T,bool isConst>
class TwoDArrayBaseIterator 
{
public:
    using iterator_concept  = std::contiguous_iterator_tag;
    using iterator_category = std::random_access_iterator_tag;

    using size_type         = std::size_t;
    using difference_type   = std::ptrdiff_t;

    // internal type

    using internal_pointer  = std::conditional_t<isConst, T             const *,           T *>;



    // exposed type
    using row               = std::conditional_t<isConst, std::span<T const>,           std::span<T >> ;
    using value_type        = row;
    using pointer           = std::conditional_t<isConst, value_type const *,           value_type *>;
    using reference         = std::conditional_t<isConst, value_type const &,           value_type &>;


public:

    TwoDArrayBaseIterator() noexcept : ptr{nullptr}, columns{0}
    {}

    TwoDArrayBaseIterator(internal_pointer ptr, size_type  columns) noexcept : ptr{ptr}, columns{columns}
    {}

    TwoDArrayBaseIterator(TwoDArrayBaseIterator const  &   ) noexcept =default;
    TwoDArrayBaseIterator(TwoDArrayBaseIterator        &&  ) noexcept =default;
 
    TwoDArrayBaseIterator &operator=(TwoDArrayBaseIterator const  &   ) noexcept =default;
    TwoDArrayBaseIterator &operator=(TwoDArrayBaseIterator        &&  ) noexcept =default;


    operator TwoDArrayBaseIterator<T,true>() const noexcept
    {
        return {ptr,columns};
    }


public:

    [[nodiscard]] std::strong_ordering operator<=>(TwoDArrayBaseIterator const &) const noexcept = default;


public:

    TwoDArrayBaseIterator   operator++(int) noexcept
    {
        auto original=*this;
        ptr+=columns;
        return original;    
    }

    TwoDArrayBaseIterator   &operator++() noexcept
    {
        ptr+=columns;
        return *this;    
    }

    TwoDArrayBaseIterator   operator--(int) noexcept
    {
        auto original=*this;
        ptr-=columns;
        return original;    
    }

    TwoDArrayBaseIterator   &operator--() noexcept
    {
        ptr-=columns;
        return *this;    
    }


    TwoDArrayBaseIterator   &operator+=(int rows) noexcept
    {
        ptr+=rows*columns;
        return *this;    
    }

    TwoDArrayBaseIterator   &operator-=(int rows) noexcept
    {
        ptr-=rows*columns;
        return *this;    
    }


public:

    row operator*() const noexcept
    {
        return {ptr,columns};
    }

    row operator[](difference_type rowOffset) const noexcept
    {
        return {ptr + (rowOffset*columns),columns};
    }


    difference_type operator-(TwoDArrayBaseIterator const &other) const noexcept
    {
        return ptr-other.ptr;
    }

private:

    internal_pointer        ptr;
    size_type               columns;
};



template <typename T,bool isConst>
[[nodiscard]] TwoDArrayBaseIterator<T, isConst>   operator+(         TwoDArrayBaseIterator<T, isConst> const &it, 
                                                            typename TwoDArrayBaseIterator<T, isConst>::difference_type rows) noexcept
{
    TwoDArrayBaseIterator<T, isConst>       result{it};
    result+=rows;
    return result;    
}

template <typename T,bool isConst>
[[nodiscard]] TwoDArrayBaseIterator<T, isConst>   operator+(typename TwoDArrayBaseIterator<T, isConst>::difference_type rows,
                                                                     TwoDArrayBaseIterator<T, isConst> const &it) noexcept
{
    TwoDArrayBaseIterator<T, isConst>       result{it};
    result+=rows;
    return result;    
}

template <typename T,bool isConst>
[[nodiscard]] TwoDArrayBaseIterator<T, isConst>   operator-(         TwoDArrayBaseIterator<T, isConst> const &it, 
                                                            typename TwoDArrayBaseIterator<T, isConst>::difference_type rows) noexcept
{
    TwoDArrayBaseIterator<T, isConst>       result{it};
    result-=rows;
    return result;    
}

template <typename T,bool isConst>
[[nodiscard]] TwoDArrayBaseIterator<T, isConst>   operator-(typename TwoDArrayBaseIterator<T, isConst>::difference_type rows,
                                                                     TwoDArrayBaseIterator<T, isConst> const &it ) noexcept
{
    TwoDArrayBaseIterator<T, isConst>       result{it};
    result-=rows;
    return result;    
}



template <typename T>
using TwoDArrayIterator = TwoDArrayBaseIterator<T,false>;

template <typename T>
using TwoDArrayConstIterator = TwoDArrayBaseIterator<T,true>;



static_assert( std::random_access_iterator <TwoDArrayIterator<int>>);
static_assert( std::random_access_iterator <TwoDArrayConstIterator<int>>);
