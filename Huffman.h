#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <queue>

typedef struct HuffNode {
    char key;
    unsigned int frequency;
    HuffNode* left;
    HuffNode* right;

    HuffNode(char _key, unsigned int _frequency, HuffNode* _left, HuffNode* _right) 
    : key(_key), frequency(_frequency), left(_left), right(_right) {}

    bool operator<(const HuffNode& rhs) const
    {
        return frequency > rhs.frequency;
    }

} HuffNode;

typedef struct SymbolCodePair {
    char key;
    std::string code;

    SymbolCodePair(char _key, std::string _code)
    : key(_key), code(_code) {}
} SymbolCodePair;

typedef struct HuffNodeComparator {
    bool operator()(HuffNode* lhs, HuffNode* rhs) { return lhs->frequency > rhs->frequency; } 
} HuffNodeComparator;

void PrintInorderTraversal(HuffNode* root);
void PrintDFS(HuffNode* root);
HuffNode* CreateMinHeap(const std::string& message);
bool isLeafNode(HuffNode* node);
void FindSymbolTable(HuffNode* root, std::string prevCode,std::vector<SymbolCodePair>& symbolTable);
std::string EncodeMessage(const std::string& message, const std::vector<SymbolCodePair>& symbolTable);
