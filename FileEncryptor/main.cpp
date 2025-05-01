#include<iostream>
#include <filesystem>

#include "./src/app/processes/ProcessManagement.hpp"
#include "./src/app/processes/Task.hpp"
#include "./src/app/filehandling/IO.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    string targetDirectory ;
    string action ;

    cout << "Enter the  directory path : "<<endl;
    getline(cin, targetDirectory);

    cout << "Enter the action (encrypt/decrypt): "<<endl;
    getline(cin, action);

    try
    {
        if(filesystem::exists(targetDirectory) && filesystem::is_directory(targetDirectory))
        {
            ProcessManagement processManager;
            for(const auto& entry : filesystem::directory_iterator(targetDirectory))
            {
                if (entry.is_regular_file())
                {
                    string filePath = entry.path().string();
                    IO io(filePath);
                    fstream f_stream = move(io.getFileStream());
                    if(f_stream.is_open())
                    { 
                        Action actionType = (action == "encrypt") ? Action::ENCRYPT : Action::DECRYPT;
                        auto task = make_unique<Task>(move(f_stream), actionType, filePath);
                        processManager.addTask(move(task));
                    }
                    else
                    {
                        cerr << "Error: Could not open file " << filePath << endl;
                    }
                }
            } 
            processManager.executeTask();
        }
        else
        {
            throw std::invalid_argument("The provided path is not a valid directory.");
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}