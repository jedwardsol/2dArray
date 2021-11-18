#include <iostream>
#include <string>
#include <string_view>
#include <format>
using namespace std::literals;


#include "2DArray.h"
#include "2DArrayIterator.h"



//TODO : test cases


void print(auto const &array)
{
    using AT = std::remove_cvref_t<decltype(array)>;
    using VT = AT::value_type;

    std::cout << std::format("{} : {}x{}\n",typeid(VT).name(),array.height(),array.width());

    if(array.empty())
    {
        std::cout << "    empty\n";
    }
    else
    {
        for(auto const &row : array)
        {
            std::cout << "    ";
            for(auto const &element : row)
            {
                std::cout << std::format("{:<8} ",element);
            }
            std::cout << '\n';
        }
    }
        std::cout << '\n';

}




void iterate(auto  &array)
{
    for(auto const &row : array)
    {
        for(auto const &element : row)
        {
            std::cout << std::format("{:<2} ",element);
        }
        std::cout << '\n';
    }
    std::cout << '\n';

    for(auto rit = array.begin(); rit!=array.end(); rit++)
    {
        for(auto cit = (*rit).begin(); cit != (*rit).end(); cit++)
        {
            std::cout << std::format("{:2} ",(*cit));
        }
        std::cout << '\n';
    }
    std::cout << '\n';

    for(auto rit = array.cbegin(); rit!=array.cend(); rit++)
    {
        for(auto cit = (*rit).begin(); cit != (*rit).end(); cit++)
        {
            std::cout << std::format("{:2} ",(*cit));
        }
        std::cout << '\n';
    }
    std::cout << '\n';

    for(auto rit = array.rbegin(); rit!=array.rend(); rit++)
    {
        for(auto cit = (*rit).rbegin(); cit != (*rit).rend(); cit++)
        {
            std::cout << std::format("{:2} ",(*cit));
        }
        std::cout << '\n';
    }
    std::cout << '\n';

    for(auto rit = array.crbegin(); rit!=array.crend(); rit++)
    {
        for(auto cit = (*rit).rbegin(); cit != (*rit).rend(); cit++)
        {
            std::cout << std::format("{:2} ",(*cit));
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}



void citerate(auto const &array)
{

    for(auto const &row : array)
    {
        for(auto const &element : row)
        {
            std::cout << std::format("{:2} ",element);
        }
        std::cout << '\n';
    }
    std::cout << '\n';

    for(auto rit = array.begin(); rit!=array.end(); rit++)
    {
        for(auto cit = (*rit).begin(); cit != (*rit).end(); cit++)
        {
            std::cout << std::format("{:2} ",(*cit));
        }
        std::cout << '\n';
    }
    std::cout << '\n';

    for(auto rit = array.cbegin(); rit!=array.cend(); rit++)
    {
        for(auto cit = (*rit).begin(); cit != (*rit).end(); cit++)
        {
            std::cout << std::format("{:2} ",(*cit));
        }
        std::cout << '\n';
    }
    std::cout << '\n';

    for(auto rit = array.rbegin(); rit!=array.rend(); rit++)
    {
        for(auto cit = (*rit).rbegin(); cit != (*rit).rend(); cit++)
        {
            std::cout << std::format("{:2} ",(*cit));
        }
        std::cout << '\n';
    }
    std::cout << '\n';

    for(auto rit = array.crbegin(); rit!=array.crend(); rit++)
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

    TwoDArray<float>    stuff_e  { std::initializer_list< std::initializer_list<float>>{}};  
    TwoDArray<float>    stuff_ee { {},{},{}};  
    TwoDArray<int>      stuff_i{ {1,2}, {3,4}};
    TwoDArray           stuff_d{ {1.1,2.2}, {3.3,4.4}};
    TwoDArray           stuff_nts{ {"one",  "two",  "three"}, 
                                   {"four", "five", "six"}, 
                                   {"seven","eight","nine"}, };
    
    TwoDArray           stuff_s { {"one"s,  "two"s,  "three"s}, 
                                  {"four"s, "five"s, "six"s}, 
                                  {"seven"s,"eight"s,"nine"s}, };

    TwoDArray           stuff_sv{ {"one"sv,  "two"sv,  "three"sv}, 
                                  {"four"sv, "five"sv, "six"sv}, 
                                  {"seven"sv,"eight"sv,"nine"sv}, };


    print(stuff_e);
    print(stuff_ee);
    print(stuff_i);
    print(stuff_d);
    print(stuff_nts);
    print(stuff_s);
    print(stuff_sv);



}