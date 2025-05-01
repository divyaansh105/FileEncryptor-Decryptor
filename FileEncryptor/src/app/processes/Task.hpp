#pragma once 

#include <iostream>
#include <sstream>
#include "../filehandling/IO.hpp"


enum class Action
{
  ENCRYPT,
  DECRYPT
};


struct  Task
{
    std::string filePath;
    std::fstream f_stream;
    Action action;

    Task(std::fstream&&  stream , Action act, std::string path){
        f_stream = (std::move(stream));
        action = act; 
        filePath = path;
    }
    
    std::string toString()
    {
        std::ostringstream ss;
        ss<<filePath<<","<<(action == Action::ENCRYPT ? "ENCRYPT" : "DECRYPT");
        return ss.str();
    }

    static Task fromString(const std::string& str)
    {
        std::istringstream ss(str);
        std::string filePath;
        std::string actionStr;

        if(std::getline(ss, filePath, ',') && std::getline(ss, actionStr))
        {
            Action action = (actionStr == "ENCRYPT") ? Action::ENCRYPT : Action::DECRYPT;
            IO io(filePath);
            std::fstream fileStream = std::move(io.getFileStream());
            if(!fileStream.is_open())
            {
                throw std::runtime_error ("Error: Could not open file "  + filePath);
            }
            else
            {
                return Task(std::move(fileStream), action, filePath);

            }
        }
        else
        {
            throw std::runtime_error("Error: Invalid string format");
        }
        
    }
};
