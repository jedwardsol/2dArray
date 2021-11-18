#include <iostream>
#include <string>
#include <format>

#include "Fixed2DArray.h"
#include "2DArray.h"
#include "2DArrayIterator.h"



//TODO : test cases


void iterate(auto  &stuff)
{
    for(auto const &row : stuff)
    {
        for(auto const &element : row)
        {
            std::cout << std::format("{:2} ",element);
        }
        std::cout << '\n';
    }
    std::cout << '\n';

    for(auto rit = stuff.begin(); rit!=stuff.end(); rit++)
    {
        for(auto cit = (*rit).begin(); cit != (*rit).end(); cit++)
        {
            std::cout << std::format("{:2} ",(*cit));
        }
        std::cout << '\n';
    }
    std::cout << '\n';

    for(auto rit = stuff.cbegin(); rit!=stuff.cend(); rit++)
    {
        for(auto cit = (*rit).begin(); cit != (*rit).end(); cit++)
        {
            std::cout << std::format("{:2} ",(*cit));
        }
        std::cout << '\n';
    }
    std::cout << '\n';

    for(auto rit = stuff.rbegin(); rit!=stuff.rend(); rit++)
    {
        for(auto cit = (*rit).rbegin(); cit != (*rit).rend(); cit++)
        {
            std::cout << std::format("{:2} ",(*cit));
        }
        std::cout << '\n';
    }
    std::cout << '\n';

    for(auto rit = stuff.crbegin(); rit!=stuff.crend(); rit++)
    {
        for(auto cit = (*rit).rbegin(); cit != (*rit).rend(); cit++)
        {
            std::cout << std::format("{:2} ",(*cit));
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}



void citerate(auto const &stuff)
{

    for(auto const &row : stuff)
    {
        for(auto const &element : row)
        {
            std::cout << std::format("{:2} ",element);
        }
        std::cout << '\n';
    }
    std::cout << '\n';

    for(auto rit = stuff.begin(); rit!=stuff.end(); rit++)
    {
        for(auto cit = (*rit).begin(); cit != (*rit).end(); cit++)
        {
            std::cout << std::format("{:2} ",(*cit));
        }
        std::cout << '\n';
    }
    std::cout << '\n';

    for(auto rit = stuff.cbegin(); rit!=stuff.cend(); rit++)
    {
        for(auto cit = (*rit).begin(); cit != (*rit).end(); cit++)
        {
            std::cout << std::format("{:2} ",(*cit));
        }
        std::cout << '\n';
    }
    std::cout << '\n';

    for(auto rit = stuff.rbegin(); rit!=stuff.rend(); rit++)
    {
        for(auto cit = (*rit).rbegin(); cit != (*rit).rend(); cit++)
        {
            std::cout << std::format("{:2} ",(*cit));
        }
        std::cout << '\n';
    }
    std::cout << '\n';

    for(auto rit = stuff.crbegin(); rit!=stuff.crend(); rit++)
    {
        for(auto cit = (*rit).rbegin(); cit != (*rit).rend(); cit++)
        {
            std::cout << std::format("{:2} ",(*cit));
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void iterate()
{
    TwoDArray<int>      stuff{5,4};

    for(auto row=0u;row< stuff.height();row++)
    {
        for(auto column=0u; column < stuff.width() ; column++)
        {
            stuff[row][column] = static_cast<int>(row*stuff.width()+column);
        }
    }

    iterate(stuff);
    citerate(stuff);


    TwoDArray<int> const     cstuff{stuff};

    iterate(cstuff);
    citerate(cstuff);
}

int main()
{

    iterate();

    TwoDArray<int>      stuff_i{ {1,2}, {3,4}};
    TwoDArray           stuff_d{ {1.1,2.2}, {3.3,4.4}};
    




}