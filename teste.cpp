#include <iostream>
#include <string>
#include <format>

int main()
{
    std::string w = "World";
    std::cout << std::format("Hello {}!\n", w);

    return 0;
}