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

    using difference_type   = std::ptrdiff_t;

    using value_type        = T;
    using pointer           = std::conditional_t<isConst, value_type const *,           value_type *>;
    using reference         = std::conditional_t<isConst, value_type const &,           value_type &>;
    using row               = std::conditional_t<isConst, std::span<value_type const>,  std::span<value_type >> ;

// converting constructor iterator -> const_iterator


    TwoDArrayBaseIterator(pointer ptr, size_t  columns) noexcept : ptr{ptr}, columns{columns}
    {}

    TwoDArrayBaseIterator(TwoDArrayBaseIterator const  &    )=default;
 

    [[nodiscard]] std::strong_ordering operator<=>(TwoDArrayBaseIterator const &) const = default;


    TwoDArrayBaseIterator   operator++(int)
    {
        auto original=*this;
        ptr+=columns;
        return original;    
    }

    TwoDArrayBaseIterator   &operator++()
    {
        ptr+=columns;
        return *this;    
    }


    TwoDArrayBaseIterator   &operator+=(int rows)
    {
        ptr+=rows*columns;
        return *this;    
    }

    TwoDArrayBaseIterator   &operator-=(int rows)
    {
        ptr-=rows*columns;
        return *this;    
    }


    [[nodiscard]] TwoDArrayBaseIterator   operator+(int rows) const
    {
        TwoDArrayBaseIterator       result{*this};
        result+=rows;
        return result;    
    }

    [[nodiscard]] TwoDArrayBaseIterator   &operator-(int rows) const
    {
        TwoDArrayBaseIterator       result{*this};
        result-=rows;
        return result;    
    }

    row operator*()
    {
        return {ptr,columns};
    }

private:

    pointer  ptr;
    size_t   columns;
};


template <typename T>
using TwoDArrayIterator = TwoDArrayBaseIterator<T,false>;


template <typename T>
using TwoDArrayConstIterator = TwoDArrayBaseIterator<T,true>;



