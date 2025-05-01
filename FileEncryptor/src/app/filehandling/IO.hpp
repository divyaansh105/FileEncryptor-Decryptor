#pragma once 

#include<fstream>
#include<string>


class IO
{
    public :
        IO(const std::string& fileName);
        ~IO();

        std::fstream getFileStream();

    private :
        std::fstream fileStream;
};