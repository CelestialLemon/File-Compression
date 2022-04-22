#include "File.h"

std::vector<byte> ReadFileDataRaw(std::string filepath)
{
    std::ifstream readStream(filepath, std::ios::in | std::ios::binary);
    std::vector<byte> buffer = std::vector<byte>(std::istreambuf_iterator<byte>(readStream),std::istreambuf_iterator<byte>());
    readStream.close();
    return buffer;
}

void WriteFileDataRaw(std::string filepath, const std::vector<byte>& buffer)
{
    std::ofstream writeStream(filepath, std::ios::out | std::ios::binary);
    writeStream.write(&buffer[0], buffer.size());
    writeStream.close();
}

bool CompareFiles(std::string filepath1, std::string filepath2)
{
    auto buffer1 = ReadFileDataRaw(filepath1);
    auto buffer2 = ReadFileDataRaw(filepath2);

    if(buffer1.size() != buffer2.size()) return false;

    for(size_t i = 0; i < buffer1.size(); i++)
    {
        if(buffer1[i] != buffer2[i]) return false;
    }
    return true;
}

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