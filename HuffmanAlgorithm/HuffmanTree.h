#ifndef HUFFMANTREE_H_INCLUDED
#define HUFFMANTREE_H_INCLUDED

#include "Node.h"
#include "Pair.h"
#include "Vector.h"
#include "Heap.h"
#include <string>

class HuffmanTree
{
    Node* root;

private:

    void createFrequencyTable(Pair<char, int>* FT, string msg);

    Node* createHuffmanTree(Pair<char, int>* FT);

    void createCodeTable_help(Node*, string, string*);
    void createCodeTable(Pair<char, string>*);

    void deleteTree(Node*);
    Node* copyTree(Node*);

    int myStoi(string code);

public:

    HuffmanTree();
    HuffmanTree(HuffmanTree const&);
    HuffmanTree& operator=(HuffmanTree const&);
    ~HuffmanTree();

    string encodeMessage(string);
    string decodeMessage(string);

    void from8bitBinariesToDecimals(string);
    double ratio(string, string);

    string encodeMessageFromFile(string);
};
#endif // HUFFMANTREE_H_INCLUDED
