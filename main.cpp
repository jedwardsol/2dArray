#include <iostream>
#include <string>
#include <format>

#include "Fixed2DArray.h"
#include "2DArray.h"
#include "2DArrayIterator.h"



//TODO : test cases




int main()
{
    {
        FixedTwoDArray<int,4,5>      stuff{};
        stuff[1][2]=1;
    }


    TwoDArray<int>      stuff(5,4);
    stuff(1,2)=1;

    stuff[1][3] = 1;


    auto i = stuff.begin();

    stuff.fill(42);

    for(auto const &row : stuff)
    {
        for(auto const &element : row)
        {
            std::cout << element << ' ';
        }

        std::cout << "\n";
    }

    std::vector<int>::iterator a;


    TwoDArray<int>::const_iterator  ci=i;

//  TwoDArray<int>::iterator  ni=ci;



}