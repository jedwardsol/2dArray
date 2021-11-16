#include <iostream>
#include <string>
#include <format>

#include "Fixed2DArray.h"
#include "2DArray.h"

//TODO : noexcept
//TODO : test cases





#include "2DArrayIterator.h"





int main()
{
    {
        FixedTwoDArray<int,4,5>      stuff{};
        stuff[1][2]=1;
    }


    TwoDArray<int>      stuff(5,4);
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