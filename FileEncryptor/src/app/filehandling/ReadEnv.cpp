#include<iostream>
#include<string>
#include<sstream>
#include<fstream>

#include"IO.hpp"


class ReadENV
{
    public :
       std::string getKey()
       {
         std:: string envPath = ".env";
         IO io(envPath);
         std::fstream fileStream = io.getFileStream();  
         std::stringstream buffer;
         buffer << fileStream.rdbuf();
         std::string envContent = buffer.str();
         return envContent;
       }
};

