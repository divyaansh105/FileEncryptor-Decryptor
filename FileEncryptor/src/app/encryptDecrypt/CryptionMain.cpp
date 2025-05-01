#include<iostream>

#include "Cryption.hpp"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <data>" << std::endl;
        return 1;
    }

    std::string data = argv[1];
    int result = executeCryption(data);

    std::cout << "Result: " << result << std::endl;

    return 0;
}