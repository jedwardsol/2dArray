#pragma once

#include <type_traits>
#include <span>

#include <vector>
#include <stdexcept>
#include <tuple>
#include <span>

#include <initializer_list>

#include "debug.h"
#include "2DArrayIterator.h"
#include "thrower.h"

//TODO : noexcept



template <typename T>
class TwoDArray
{
public:

    using value_type            = T;
    using size_type             = std::size_t;
    using difference_type       = std::ptrdiff_t;
    using reference             = value_type &;
    using const_reference       = value_type const&;
    using pointer               = value_type *;
    using const_pointer         = value_type const*;

    using iterator               = TwoDArrayIterator<value_type>;
    using const_iterator         = TwoDArrayConstIterator<value_type>;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    using row                   = std::span<value_type>;
    using constantRow           = std::span<value_type const>;



public:
    TwoDArray() = default;

    TwoDArray(size_type rows, size_type columns) : rows{rows}, columns{columns}, vector(rows*columns)
    {}



    TwoDArray(std::initializer_list<std::initializer_list<T>> contents) : TwoDArray{ contents.size(), 
                                                                                     contents.size() ? contents.begin()->size() : 0}
    {
        for(size_t r{}; auto &row : contents)
        {
            if(row.size() != width())
            {
                throw_runtime_error("row is wrong length"); 
            }

            for(size_t c{}; auto element : row)
            {
                at(r,c)=std::move(element);
                c++;
            }

            r++;                
        }
    }


public:


    TwoDArray(TwoDArray  const&)                      = default;
    TwoDArray(TwoDArray       &&) noexcept            = default;

    TwoDArray &operator=(TwoDArray  const&)           = default;
    TwoDArray &operator=(TwoDArray       &&) noexcept = default;




public:

    auto size() const noexcept
    {
        return std::make_pair(rows,columns);
    }

    auto height() const noexcept
    {
        return rows;
    }

    auto width() const noexcept
    {
        return columns;
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

    // push row,  push column?


public: // raw access

    pointer data() noexcept
    {
        return vector.data();
    }

    const_pointer data() const noexcept
    {
        return vector.data();
    }


public: // element access

    reference operator()(size_t row, size_t column)  noexcept(releaseBuild)
    {
        debugCheck(row,column);
        return vector[row * columns + column];
    }

    const_reference operator()(size_t row, size_t column) const noexcept(releaseBuild)
    {
        debugCheck(row,column);
        return vector[row * columns + column];
    }

    reference at(size_t row, size_t column)
    {
        check(row,column);

        return vector.at(row * columns + column);
    }

    const_reference at(size_t row, size_t column) const
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

    reference       front()        = delete;
    const_reference front() const  = delete;
    reference       back()         = delete;
    const_reference back()  const  = delete;


public: // row access

    row operator[](size_type row)  noexcept(releaseBuild)
    {
        debugCheck(row);
        return { &vector[row * columns ], columns};
    }

    constantRow operator[](size_type row) const  noexcept(releaseBuild)
    {
        debugCheck(row);
        return { &vector[row * columns ], columns};
    }

    row at(size_type row)
    {
        check(row);
        return { &vector[row * columns ], columns};
    }

    constantRow at(size_type row) const
    {
        check(row);
        return { &vector[row * columns ], columns};
    }



public:     // iterators

    
    [[nodiscard]] iterator begin()  noexcept
    {
        return iterator{&vector.front(),columns};
    }

    [[nodiscard]] iterator end()  noexcept
    {
        return iterator{&vector.back()+1,columns};
    }


    [[nodiscard]] const_iterator begin() const noexcept
    {
        return const_iterator{&vector.front(),columns};
    }

    [[nodiscard]] const_iterator end() const  noexcept
    {
        return const_iterator{&vector.back()+1,columns};
    }




    [[nodiscard]] const_iterator cbegin() const  noexcept
    {
        return const_iterator{&vector.front(),columns};
    }

    [[nodiscard]] const_iterator cend() const noexcept
    {
        return const_iterator{&vector.back()+1,columns};
    }

    [[nodiscard]] reverse_iterator rbegin()  noexcept
    {
        return reverse_iterator{end()};
    }

    [[nodiscard]] reverse_iterator rend()  noexcept
    {
        return reverse_iterator{begin()};
    }

    [[nodiscard]] const_reverse_iterator rbegin() const noexcept
    {
        return const_reverse_iterator{end()};
    }

    [[nodiscard]] const_reverse_iterator rend() const noexcept
    {
        return const_reverse_iterator{begin()};
    }




    [[nodiscard]] const_reverse_iterator crbegin() const noexcept
    {
        return const_reverse_iterator{cend()};
    }
         
    [[nodiscard]] const_reverse_iterator crend() const noexcept
    {
        return const_reverse_iterator{cbegin()};
    }


private:

    void check (size_type row)
    {
        if(row > rows)
        {
            throw std::out_of_range{std::format("Row {} OOB.  rows={}",row,rows)};
        }
    }

    void check (size_type row, size_type column)
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


    void debugCheck ([[maybe_unused]] size_type row)  noexcept(releaseBuild)
    {
        if constexpr(debugBuild)
        {
            check(row);
        }
    }

    void debugCheck ([[maybe_unused]]size_type row, [[maybe_unused]] size_type column) noexcept(releaseBuild)
    {
        if constexpr(debugBuild)
        {
            check(row,column);
        }
    }

private:
    
    size_type                   rows   {};
    size_type                   columns{};
    std::vector<value_type>     vector;
};

