#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <stdexcept>
#include <format>
#include <tuple>
#include <span>
#include <iterator>
#include <compare>

#if defined _DEBUG
constexpr bool debugBuild{true};
#else
constexpr bool debugBuild{false};
#endif


namespace compileTime
{

template <typename T, size_t ROWS, size_t COLUMNS>
using TwoDArray = std::array< std::array<T,COLUMNS>, ROWS>;

}


namespace runTime
{


template <typename T>
class TwoDArrayIterator 
{
public:
    using iterator_concept  = std::contiguous_iterator_tag;
    using iterator_category = std::random_access_iterator_tag;
    using value_type        = T;
    using reference         = value_type &;
    using row               = std::span<T>;


    TwoDArrayIterator(T  *ptr, size_t  columns) noexcept : ptr{ptr}, columns{columns}
    {}

    TwoDArrayIterator(TwoDArrayIterator const  &    )=default;
 

    std::strong_ordering operator<=>(TwoDArrayIterator const &) const = default;


    TwoDArrayIterator   operator++(int)
    {
        auto original=*this;
        ptr+=columns;
        return original;    
    }

    TwoDArrayIterator   &operator++()
    {
        ptr+=columns;
        return *this;    
    }


    TwoDArrayIterator   &operator+=(int rows)
    {
        ptr+=rows*columns;
        return *this;    
    }

    TwoDArrayIterator   &operator-=(int rows)
    {
        ptr-=rows*columns;
        return *this;    
    }


    TwoDArrayIterator   operator+(int rows) const
    {
        TwoDArrayIterator       result{*this};
        result+=rows;
        return result;    
    }

    TwoDArrayIterator   &operator-(int rows) const
    {
        TwoDArrayIterator       result{*this};
        result-=rows;
        return result;    
    }

    row operator*()
    {
        return {ptr,columns};
    }

private:

    T       *ptr;
    size_t   columns;
};



template <typename T>
class TwoDArrayConstIterator 
{
public:
    using iterator_concept  = std::contiguous_iterator_tag;
    using iterator_category = std::random_access_iterator_tag;
    using value_type        = T;
    using reference         = value_type const&;
    using row               = std::span<T const>;


    TwoDArrayConstIterator(T  *ptr, size_t  columns) noexcept : ptr{ptr}, columns{columns}
    {}

    TwoDArrayConstIterator(TwoDArrayConstIterator const  &    )=default;
 

    std::strong_ordering operator<=>(TwoDArrayConstIterator const &) const = default;


    TwoDArrayConstIterator   operator++(int)
    {
        auto original=*this;
        ptr+=columns;
        return original;    
    }

    TwoDArrayConstIterator   &operator++()
    {
        ptr+=columns;
        return *this;    
    }


    TwoDArrayConstIterator   &operator+=(int rows)
    {
        ptr+=rows*columns;
        return *this;    
    }

    TwoDArrayConstIterator   &operator-=(int rows)
    {
        ptr-=rows*columns;
        return *this;    
    }


    TwoDArrayConstIterator   operator+(int rows) const
    {
        TwoDArrayIterator       result{*this};
        result+=rows;
        return result;    
    }

    TwoDArrayConstIterator   &operator-(int rows) const
    {
        TwoDArrayIterator       result{*this};
        result-=rows;
        return result;    
    }

    row operator*()
    {
        return {ptr,columns};
    }

private:

    T       *ptr;
    size_t   columns;
};




// TODO : reverse iterator


template <typename T>
class TwoDArray
{
public:

    using row           = std::span<T>;
    using constantRow   = std::span<T const>;


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

    T *data()
    {
        return vector.data();
    }

    T const *data() const
    {
        return vector.data();
    }


public: // element access

    T &operator()(size_t row, size_t column)
    {
        debugCheck(row,column);
        return vector[row * columns + column];
    }

    T const &operator()(size_t row, size_t column) const
    {
        debugCheck(row,column);
        return vector[row * columns + column];
    }

    T &at(size_t row, size_t column)
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

    
    auto begin() 
    {
        return TwoDArrayIterator{&vector.front(),columns};
    }

    auto end() 
    {
        return TwoDArrayIterator{&vector.back()+1,columns};
    }


    auto cbegin() 
    {
        return TwoDArrayConstIterator{&vector.front(),columns};
    }

    auto cend() 
    {
        return TwoDArrayConstIterator{&vector.back()+1,columns};
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


}

int main()
{
    {
        compileTime::TwoDArray<int,4,5>      stuff{};
        stuff[1][2]=1;
    }


    runTime::TwoDArray<int>      stuff(5,4);
    stuff(1,2)=1;

    stuff[1][3] = 1;


    stuff.fill(42);

    for(auto const &row : stuff)
    {
        for(auto const &element : row)
        {
            std::cout << element << ' ';
        }

        std::cout << "\n";
    }
}