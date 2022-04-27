#include <iostream>
#include <fstream>
#include <climits>
#include <cmath>
#include <string>

void Write()
{
    std::ofstream writeStream("test.txt", std::ios::out | std::ios::binary);
    writeStream << 'c' << "100101" << '\n';

    std::string someString= "The quick brown fox jumps over a lazy dog";
    if(writeStream.is_open())
    {
        writeStream.write(&someString[0], someString.length());
    }
    writeStream.close();
}

void Read()
{
    std::ifstream readStream("test.txt", std::ios::in | std::ios::binary);

    char a; std::string b;
    readStream >> a;
    readStream >> b;

    //char temp; readStream >> temp;

    std::string c(42, ' ');
    if(readStream.is_open())
    {
        readStream.read(&c[0], 42);
    }

    std::cout << "a : " << a << " b : \'" << b << "\'\n";

    std::cout << '\'';
    for(int i = 1; i < 42; i++)
    {
        std::cout << c[i];
    }
    std::cout << '\'';
}

int main(int argc, char** argv)
{
    if(std::string(argv[1]) == "write") Write();
    else if(std::string(argv[1]) == "read") Read();
    return 0;
}