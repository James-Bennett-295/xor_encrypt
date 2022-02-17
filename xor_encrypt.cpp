#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using std::cout;
using std::fstream;
using std::ios;
using std::string;

int main(int argc, char *argv[])
{

    // Check args
    if (argc <= 2)
    {
        cout << "Arguments <file> and <key> must be included!\n";
        exit(1);
    };

    // Declare variables
    fstream file;
    string fileContents = "";
    string fileName = argv[1];

    // Read file
    file.open(fileName, ios::in);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            fileContents += line + "\n";
        };
        file.close();
        fileContents.pop_back();
    }
    else
    {
        cout << "Failed to open file for reading!\n";
        exit(1);
    };

    // Encrypt file contents
    const char *key = argv[2];
    const int len = fileContents.length();
    const int keyLen = strlen(key);
    for (int i = 0; i < len; i++)
    {
        fileContents[i] = fileContents[i] ^ key[i % keyLen];
    };

    // Write file
    file.open(fileName, ios::out);
    if (file.is_open())
    {
        file << fileContents;
        file.close();
    }
    else
    {
        cout << "Failed to open file for writing!\n";
        exit(1);
    };
};
