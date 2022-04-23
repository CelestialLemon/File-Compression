#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

typedef char byte;
bool fileExists(const std::string& filepath);
std::vector<byte> ReadFileDataRaw(std::string filepath);
void WriteFileDataRaw(std::string filepath, const std::vector<byte>& buffer);



/*
-128 > -127
-1 > 0
0 > -1
1 > 0

-1 > 0
0 > 1
0 > 1
-127 > -128
*/