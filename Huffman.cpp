#include "Huffman.h"

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
    std::priority_queue<HuffNode*, std::vector<HuffNode*>, HuffNodeComparator> pq;

    for(const auto& item : freq_counter)
    {
        HuffNode* newNode = new HuffNode(item.first, item.second, nullptr, nullptr);
        pq.push(newNode);
    }

    // delete the data from hashmap to free memory
    freq_counter.clear();

    /*const int pqsize = pq.size();
    for(int i = 0; i < pqsize; i++)
    {
        auto top = pq.top(); pq.pop();
        std::cout << "Key : " << top->key << " freq : " << top->frequency << '\n';
    }*/

    while(pq.size() > 1)
    {
        HuffNode* node1 = pq.top(); pq.pop();
        HuffNode* node2 = pq.top(); pq.pop();

        HuffNode* newNode = new HuffNode(-1, node1->frequency + node2->frequency, node1, node2);

        pq.push(newNode);
    }
    
    return pq.top();
}

bool isLeafNode(HuffNode* node) { 
    if(node->left == nullptr && node->right == nullptr) return true; 
    else return false; 
}

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
