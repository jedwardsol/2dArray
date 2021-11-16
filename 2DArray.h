#pragma once

#include <type_traits>
#include <span>

#include <vector>
#include <stdexcept>
#include <tuple>
#include <span>

#include "debug.h"
#include "2DArrayIterator.h"



template <typename T>
class TwoDArray
{
public:

    using row                   = std::span<T>;
    using constantRow           = std::span<T const>;

// TODO : use these consistently
    using value_type            = T;
    using size_type             = std::size_t;
    using difference_type       = std::ptrdiff_t;
    using reference             = value_type &;
    using const_reference       = value_type const&;
    using pointer               = value_type *;
    using const_pointer         = value_type const*;


    using iterator               = TwoDArrayIterator<T>;
    using const_iterator         = TwoDArrayConstIterator<T>;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;




public:
    TwoDArray() = default;

    TwoDArray(size_t rows, size_t columns) : rows{rows}, columns{columns}, vector(rows*columns)
    {}


    TwoDArray(TwoDArray  const&)                      = default;
    TwoDArray(TwoDArray       &&) noexcept            = default;

    TwoDArray &operator=(TwoDArray  const&)           = default;
    TwoDArray &operator=(TwoDArray       &&) noexcept = default;


    // TODO : {} constructors


public:

    auto size() const noexcept
    {
        return std::make_pair(rows,columns);
    }

    auto empty() const noexcept
    {
        return vector.empty();
    }

    auto resize(size_t newRows, size_t newColumns) 
    {
        rows=newRows;        
        columns=newColumns;

        vector.resize(rows*columns);  // TODO : messes up contents if columns changes.
    }


public: // raw access

    pointer data()
    {
        return vector.data();
    }

    const_pointer data() const
    {
        return vector.data();
    }


public: // element access

    reference operator()(size_t row, size_t column)
    {
        debugCheck(row,column);
        return vector[row * columns + column];
    }

    const_reference operator()(size_t row, size_t column) const
    {
        debugCheck(row,column);
        return vector[row * columns + column];
    }

    reference at(size_t row, size_t column)
    {
        check(row,column);

        return vector.at(row * columns + column);
    }

    T const &at(size_t row, size_t column) const
    {
        check(row,column);

        return vector.at(row * columns + column);
    }

    void fill(T const &value)
    {
        for(auto &element : vector)
        {
            element = value;
        }
    }

    T       &front()        = delete;
    T const &front() const  = delete;
    T       &back()         = delete;
    T const &back()  const  = delete;


public: // row access

    row operator[](size_t row)
    {
        debugCheck(row);
        return { &vector[row * columns ], columns};
    }

    constantRow operator[](size_t row) const
    {
        debugCheck(row);
        return { &vector[row * columns ], columns};
    }

    row at(size_t row)
    {
        check(row);

        return { &vector[row * columns ], columns};
    }

    constantRow at(size_t row) const
    {
        check(row);
                         vector.begin();
        return { &vector[row * columns ], columns};
    }



public:     // iterators

    
    [[nodiscard]] auto begin() 
    {
        return iterator{&vector.front(),columns};
    }

    [[nodiscard]] auto end() 
    {
        return iterator{&vector.back()+1,columns};
    }


    [[nodiscard]] auto cbegin() const 
    {
        return const_iterator{&vector.front(),columns};
    }

    [[nodiscard]] auto cend() const
    {
        return const_iterator{&vector.back()+1,columns};
    }

    [[nodiscard]] auto rbegin() 
    {
        return reverse_iterator{end()};
    }

    [[nodiscard]] auto rend() 
    {
        return reverse_iterator{begin()};
    }


    [[nodiscard]] auto crbegin() const
    {
        return const_reverse_iterator{cend()};
    }
         
    [[nodiscard]] auto crend() const
    {
        return const_reverse_iterator{cbegin()};
    }




private:

    void check (size_t row)
    {
        if(row > rows)
        {
            throw std::out_of_range{std::format("Row {} OOB.  rows={}",row,rows)};
        }
    }

    void check (size_t row, size_t column)
    {
        if(row > rows)
        {
            throw std::out_of_range{std::format("Row {} OOB.  rows={}",row,rows)};
        }

        if(column > columns)
        {
            throw std::out_of_range{std::format("Column {} OOB.  columns={}",column,columns)};
        }
    }


    void debugCheck (size_t row)
    {
        if constexpr(debugBuild)
        {
            check(row);
        }
    }

    void debugCheck (size_t row, size_t column)
    {
        if constexpr(debugBuild)
        {
            check(row,column);
        }
    }

private:
    
    size_t              rows   {};
    size_t              columns{};
    std::vector<T>      vector;
};

