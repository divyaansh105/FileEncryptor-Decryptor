#include "Cryption.hpp"
#include "../processes/Task.hpp"
#include "../filehandling/ReadEnv.cpp"

int executeCryption(const std::string &data)
{
    Task task = Task::fromString(data);
    ReadENV env;
    std::string keyStr = env.getKey();
    int key = std::stoi(keyStr);

    if (task.action == Action::ENCRYPT)
    {
        char currentChar;
        while (task.f_stream.get(currentChar))
        {
            currentChar = (currentChar - key) %256 ; 
            task.f_stream.seekp(-1, std::ios::cur); // Move the cursor back one position
            task.f_stream.put(currentChar);
        }
        task.f_stream.close(); 
    }
    else if (task.action == Action::DECRYPT)
    {
        char currentChar;
        while (task.f_stream.get(currentChar))
        {
            currentChar = (currentChar + key + 256 )  %256 ; 
            task.f_stream.seekp(-1, std::ios::cur); // Move the cursor back one position
            task.f_stream.put(currentChar);
        }
        task.f_stream.close();
    }

    return data.length();
}
