#include<iostream>
#include "IO.hpp"



IO::IO(const std::string& filePath)
{
    fileStream.open(filePath, std::ios::in | std::ios::out | std::ios::binary);
    if (!fileStream.is_open())
    {
        std::cout << "Error opening file: " << filePath << std::endl;
    }
}

IO::~IO()
{
    if (fileStream.is_open())
    {
        fileStream.close();
    }
}

std::fstream IO::getFileStream()
{
    return std::move(fileStream);
}