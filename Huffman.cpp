#include "Huffman.h"
#include "File.h"
#include <cmath>
/*
    Helper method used to print any huffman tree
    Not used in the actual application
*/
void PrintInorderTraversal(HuffNode* root)
{
    
    if(root == nullptr) return;
    PrintInorderTraversal(root->left);
    PrintInorderTraversal(root->right);

    if(root->key != -1)
    {
        std::cout << "Key : " << root->key << " Freq : " << root->frequency << '\n';
    }
    else
    {
        std::cout << "Key : NULL Freq : " << root->frequency << '\n';
    }

}

/*
    Helper method to print huffman tree in depth first traversel
    Not used in the actual applcation
*/
void PrintDFS(HuffNode* root)
{
    std::queue<HuffNode*> q;
    q.push(root);

    while(!q.empty())
    {
        HuffNode* front = q.front();
        q.pop();

        if(front->key != -1)
            std::cout << "Key : " << front->key << " Freq : " << front->frequency << '\n';
        else
            std::cout << "Key : NULL Freq : " << front->frequency << '\n';

        if(front->left != nullptr) q.push(front->left);
        if(front->right != nullptr) q.push(front->right);
    }
}

/*
    Generate the min heap of huffman tree from given message
*/
HuffNode* CreateMinHeap(const std::string& message)
{
    // count frequncy of occurance of each character in the message
    std::unordered_map<char, int> freq_counter;
    for(const char& c : message)
    {
        if(freq_counter.find(c) != freq_counter.end())
            freq_counter[c]++;
        else
            freq_counter[c] = 1;
    }

    // extract the data in a vector to convert it into heap
    // HuffNodeComparator is a comparsion fuction used to sort the priority queue by frequency of chars
    std::priority_queue<HuffNode*, std::vector<HuffNode*>, HuffNodeComparator> pq;

    // push nodes into priority queue to consturct the min heap
    for(const auto& item : freq_counter)
    {
        HuffNode* newNode = new HuffNode(item.first, item.second, nullptr, nullptr);
        pq.push(newNode);
    }

    // delete the data from hashmap to free memory
    freq_counter.clear();

    // print priority queue
    /*const int pqsize = pq.size();
    for(int i = 0; i < pqsize; i++)
    {
        auto top = pq.top(); pq.pop();
        std::cout << "Key : " << top->key << " freq : " << top->frequency << '\n';
    }*/


    // constructing the min heap
    while(pq.size() > 1)
    {
        HuffNode* node1 = pq.top(); pq.pop();
        HuffNode* node2 = pq.top(); pq.pop();

        HuffNode* newNode = new HuffNode(-1, node1->frequency + node2->frequency, node1, node2);

        pq.push(newNode);
    }
    
    return pq.top();
}

/*
    Helper method to find if a given HuffNode is leaf i.e node beloning to a character
*/
bool isLeafNode(HuffNode* node) { 
    if(node->left == nullptr && node->right == nullptr) return true; 
    else return false; 
}

/*
    consturct symbol table from min-heap
    Takes in vector reference and stores the symbol table in this vector (2nd arguement)
*/
void FindSymbolTable(HuffNode* root, std::string prevCode,std::vector<SymbolCodePair>& symbolTable)
{
    if(root == nullptr) return;
    
    if(isLeafNode(root))
    {
        SymbolCodePair scp(root->key, prevCode);
        symbolTable.push_back(scp);
    }
    else
    {
        FindSymbolTable(root->left, prevCode + "0", symbolTable);
        FindSymbolTable(root->right, prevCode + "1", symbolTable);
    }
}

/*
    Takes a symbol table and message and encodes it
*/
std::string EncodeMessage(const std::string& message, const std::vector<SymbolCodePair>& symbolTable)
{
    std::unordered_map <char, std::string> table;

    for(const SymbolCodePair& scp : symbolTable)
    {
        table[scp.key] = scp.code;
    }

    std::string output = "";
    for(const char& c : message)
    {
        output += table[c];
    }

    return output;
}

int BinaryStringToInt(const std::string& bin)
{
    int res = 0;
    int factor = 1;
    for(const char& c : bin)
    {
        if(c == '1') res += factor;

        factor *= 2;
    }

    return res;
}

/*
    Saves symbol table and encoded message
*/
void SaveHuffmanData(const std::string& filepath, const std::vector<SymbolCodePair>& symbolTable, std::string& encodedMessage)
{
    /*
        1. Create a output stream
        2. Write size of symbol table and symbol table
        3. Write size of encoded message
        4. Byte complete the encoded message by appedning 0s at end
        5. Take one byte(8 chars) at a time from encodedMessage and convert to char and write
    */

    std::cout << "Saving huffman data\n";
    
    /*for(int i = 0; i < encodedMessage.length(); i++)
    {
        if(i % 8 == 0) std::cout << ' ';
        std::cout << encodedMessage[i];
    }*/

    std::ofstream writeStream(filepath, std::ios::out | std::ios::binary);
    
    int sizeOfSymbolTable = symbolTable.size();
    writeStream << sizeOfSymbolTable << '\n';

    for(int i = 0; i < symbolTable.size(); i++)
    {
        writeStream << (int)symbolTable[i].key << '\n' << symbolTable[i].code << '\n';
    }

    int encodedMessageLength = encodedMessage.length();
    writeStream << encodedMessageLength << '\n';

    int charsToAdd = 8 - (encodedMessageLength % 8);
    charsToAdd = charsToAdd == 8 ? 0 : charsToAdd;

    for(int i = 0; i < charsToAdd; i++)
        encodedMessage += '0';

    // convert encoded message to string of bytes

    // find size of buffer needed
    size_t nBytesToWrite = encodedMessage.length() / 8;
    
    // construct buffer and fill random value
    std::string byteData(nBytesToWrite, ' ');

    // index for running through encoded message, bytesConverted to run through buffer
    size_t index = 0, bytesConverted = 0;

    // var to store current byte under proceessing
    std::string currentByteString = "";

    std::cout << "\n\n";
    while(index < encodedMessage.length() && bytesConverted < nBytesToWrite)
    {
        currentByteString += encodedMessage[index];
        if(currentByteString.length() == 8 && bytesConverted < nBytesToWrite)
        {
            // process
            int byteValue = BinaryStringToInt(currentByteString) - 128;
            byteData[bytesConverted] = (char)byteValue;

            currentByteString.clear();
            bytesConverted++;
        }
        index++;
    }

    writeStream.write(&byteData[0], nBytesToWrite);

    /*int index = 0;
    std::string currentByte = "";
    while(index < encodedMessage.size())
    {
        currentByte += encodedMessage[index];
        if(currentByte.length() == 8)
        {
            // process byte
            int byteValue = 0;
            int factor = 1;
            for(char c : currentByte)
            {
                if(c == '1') byteValue += factor;

                factor *= 2;
            }

            // convert from range 0 to 255 to -128 to 127
            byteValue -= 128;
            writeStream << (char)byteValue;
            currentByte.clear();
        }
        index++;
    }*/
    writeStream.close();
}

void HuffmanCompression(const std::string& inputFilepath, const std::string& outputFilepath)
{
    std::vector<byte> byteStream = ReadFileDataRaw(inputFilepath);
    std::string message(byteStream.begin(), byteStream.end());

    HuffNode* root = CreateMinHeap(message);

    std::vector<SymbolCodePair> symbolTable;
    FindSymbolTable(root, "", symbolTable);


    std::string encodedMessage = EncodeMessage(message, symbolTable);

    std::cout << "\n\n";
    //std::cout << "Orignial message : " << message << '\n';
    //std::cout << "Encoded message  : " << encodedMessage << '\n';

    std::cout << "\n\n";
    std::cout << "Size of original message " << 8 * message.length() << " bits\n";
    std::cout << "Size of encoded message " << encodedMessage.length() << " bits\n";

    SaveHuffmanData(outputFilepath, symbolTable, encodedMessage);

}


std::string IntTo8BitBinaryString(int val)
{
    std::string bin = "";
    while(val > 0)
    {
        if(val % 2 == 1) bin += '1';
        else bin += '0';

        val /=2;
    }

    while(bin.length() < 8)
        bin += '0';

    return bin;
}
/*
    Takes in filepath
    Reads symbol table and encoded message from it
    Saves it in the corresponding references
*/
void LoadHuffmanData(const std::string& filepath, std::vector<SymbolCodePair>& symbolTable, int& encodedMessageLength,std::string& encodedMessage)
{
    /*
        1. Create an input stream
        2. Read size of symbol table and symbol table iteself
        3. Read the size of encoded message
        4. Read encoded message char wise, convert to string of byte
        5. Trim the appended part
    */

    std::ifstream readStream(filepath, std::ios::in | std::ios::binary);
    int symbolTableSize = 0;
    readStream >> symbolTableSize;

    for(int i = 0; i < symbolTableSize; i++)
    {
        int key; std::string code;
        readStream >> key >> code;
        SymbolCodePair scp((char)key, code);
        symbolTable.push_back(scp);
    }

    /*for(auto scp : symbolTable)
    {
        std::cout << "key : " << scp.key << " code : " << scp.code << '\n';
    }*/

    readStream >> encodedMessageLength;

    //std::cout << "Encoded message length " << encodedMessageLength << '\n';

    size_t nBytesToRead = (size_t)ceil((float)encodedMessageLength / 8);
    //std::cout << "nBytesToRead " << nBytesToRead << '\n';
    std::string byteData(nBytesToRead + 1, ' ');

    if(readStream.is_open())
    {
        readStream.read(&byteData[0], nBytesToRead + 1);
    }


    for(int i = 1; i < nBytesToRead + 1; i++)
    {
        std::string code = IntTo8BitBinaryString((int)byteData[i] + 128);
        //std::cout << i << ' ' << code << '\n';
        encodedMessage += code;
    }
    /*int index = 0;
    while(index < ceil((float)encodedMessageLength / 8))
    {
        char c;
        readStream >> c;
        int byteValue = c + 128;
        std::string binString = IntTo8BitBinaryString(byteValue);
        encodedMessage += binString;

        index++;
    }

    std::cout << "Loaded huffman data\n";
    std::cout << encodedMessage;*/
   /*while(readStream.peek() != EOF)
   {
        char c;
        readStream >> c;
        int byteValue = c + 128;
        std::string binString = IntTo8BitBinaryString(byteValue);
        encodedMessage += binString;
   }*/
}

void HuffmanDecompression(const std::string& inputFilepath, const std::string& outputFilepath)
{
    std::ofstream writeStream(outputFilepath, std::ios::out | std::ios::binary);

    int encodedMessageLength = 0;
    std::string encodedMessage = "";
    std::vector<SymbolCodePair> symbolTable;

    LoadHuffmanData(inputFilepath, symbolTable, encodedMessageLength, encodedMessage);

    std::unordered_map < std::string, char> symbolTableCache;
    for(const SymbolCodePair& scp : symbolTable)
    {
        symbolTableCache[scp.code] = scp.key;
    }

    symbolTable.clear();
    
    std::string currentBitSequence = "";
    int index = 0;
    while(index < encodedMessageLength)
    {
        currentBitSequence += encodedMessage[index];
        if(symbolTableCache.find(currentBitSequence) != symbolTableCache.end())
        {
            // found
            writeStream << symbolTableCache[currentBitSequence];
            currentBitSequence.clear();
        }
        
        index++;
    }
    writeStream.close();
}
