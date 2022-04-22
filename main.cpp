#include "Huffman.h"
#include "File.h"

int main()
{
    auto byteStream = ReadFileDataRaw("./res/clw-bmp.bmp");
    std::string message = "";

    for(byte b : byteStream)
    {
        message += b;
    }

    HuffNode* root = CreateMinHeap(message);

    std::vector<SymbolCodePair> symbolTable;
    FindSymbolTable(root, "", symbolTable);

    for(auto item : symbolTable)
    {
        std::cout << "Symbol : " << item.key << " code " << item.code << "\n";
    }

    std::string encodedMessage = EncodeMessage(message, symbolTable);

    std::cout << "\n\n";
    //std::cout << "Orignial message : " << message << '\n';
    //std::cout << "Encoded message  : " << encodedMessage << '\n';

    std::cout << "\n\n";
    std::cout << "Size of original message " << 8 * message.length() << "bits\n";
    std::cout << "Size of encoded message " << encodedMessage.length() << "bits\n";
}
