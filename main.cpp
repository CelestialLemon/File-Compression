#include "Huffman.h"
#include "File.h"

enum OperationType {
    ENCODE,
    DECODE
};

enum CompressionAlgorithm {
    HUFFMAN
};

int main(int argc, char** argv)
{
    OperationType operationType = OperationType::ENCODE;
    CompressionAlgorithm compressionAlgorithm = CompressionAlgorithm::HUFFMAN;

    if(std::string(argv[1]) == "encode") operationType = ENCODE;

    if(std::string(argv[1]) == "decode") operationType = DECODE;


    if(std::string(argv[2]) == "huffman") compressionAlgorithm == CompressionAlgorithm::HUFFMAN;

    std::string inputFilepath = std::string(argv[3]);
    std::string outputFilepath = std::string(argv[4]);

    if(fileExists(inputFilepath))
    {
        switch(operationType)
        {
            case OperationType::ENCODE:
                std::cout << "Encoding...\n";
                HuffmanCompression(inputFilepath, outputFilepath);
            break;

            case OperationType::DECODE:
                std::cout << "Decoding...\n";
                HuffmanDecompression(inputFilepath, outputFilepath);
            break;
        }
    }
    else
    {
        std::cout << "ERROR! Invalid filepath";
    }
    
    
}
