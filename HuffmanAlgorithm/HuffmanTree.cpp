#include "HuffmanTree.h"

#include <math.h>
#include <fstream>

const int MAX_SIZE = 256;

using namespace std;

HuffmanTree::HuffmanTree()
{
    root = NULL;
}

Node* HuffmanTree::copyTree(Node* otherRoot)
{
    if(!otherRoot)
        return NULL;
    return new Node(otherRoot->symbol, otherRoot->frequency, copyTree(otherRoot->left), copyTree(otherRoot->right));
}

void HuffmanTree::deleteTree(Node* _root)
{
    if(_root != NULL)
    {
        deleteTree(_root->left);
        deleteTree(_root->right);
        delete _root;
        _root = NULL;
    }
    else
        return;
}

HuffmanTree::HuffmanTree(HuffmanTree const &other)
{
    root = copyTree(other.root);
}

HuffmanTree& HuffmanTree::operator=(HuffmanTree const &other)
{
    if(this != &other)
    {
        deleteTree(root);
        root = copyTree(other.root);
    }
    return *this;
}

HuffmanTree::~HuffmanTree()
{
    deleteTree(root);
}

void HuffmanTree::createFrequencyTable(Pair<char, int> *table, string msg)
{
    for(int i = 0; i < MAX_SIZE; i++)
    {
        table[i].second = 0;
    }

    for(int i = 0; i < msg.length(); i++)
    {
        table[msg[i]].first = msg[i];
        table[msg[i]].second += 1;
    }
}

Node* HuffmanTree::createHuffmanTree(Pair<char, int> *frequencyTable)
{
    Vector<Node*> leaves;
    for(int i = 0; i < MAX_SIZE; i++)
    {
        if (frequencyTable[i].second != 0)
        {
            Node* temp = new Node(frequencyTable[i].first, frequencyTable[i].second);
            leaves.insertBack(temp);
        }
    }

    MinHeap<Node*> subTrees(leaves);

    while (subTrees.getSize() > 1)
    {
        Node* f = subTrees.getMin();
        subTrees.deleteMin();

        Node* s = subTrees.getMin();
        subTrees.deleteMin();

        Node* newNode = new Node(f, s);
        subTrees.insertNew(newNode);
    }
    return subTrees.getMin();
}

void HuffmanTree::createCodeTable_help(Node *node, string tempCode, string *codeTable)
{
    if(node->left == NULL && node->right == NULL)
    {
        codeTable[node->symbol] = tempCode;
    }
    else
    {
        if(node->right)
            createCodeTable_help(node->right, tempCode + "1", codeTable);
        if(node->left)
            createCodeTable_help(node->left, tempCode + "0", codeTable);
    }
}

void HuffmanTree::createCodeTable(Pair<char, string> *table)
{
    string codeTable[MAX_SIZE];
    createCodeTable_help(root, "", codeTable);

    for(int i = 0; i < MAX_SIZE; i++)
    {
        if(codeTable[i] != "")
        {
            table[i].first = (char)i;
            table[i].second = codeTable[i];
        }
    }
}

string HuffmanTree::encodeMessage(string msg)
{
    if(msg == "")
    {
        cout << "No message! " << endl;
        return "";
    }
    Pair<char, int> frequencyTable[MAX_SIZE];
    createFrequencyTable(frequencyTable, msg);

    root = createHuffmanTree(frequencyTable);

    Pair<char, string> codeTable[MAX_SIZE];
    createCodeTable(codeTable);

    string encoded = "";
    for (int i = 0; i < msg.length(); i++)
    {
        encoded += codeTable[msg[i]].second;
    }
    return encoded;
}

string HuffmanTree::encodeMessageFromFile(string filename)
{
    ifstream input(filename.c_str(), ios::in);

    if(!input.is_open())
    {
        cout << "Cannot open the file. " << endl;
        return "";
    }

    string fileContent;

    // chetem cqloto sydyrjanie na fajla
    getline(input, fileContent, (char)input.eof());

    input.close();

    // da ne vliza otnovo v encodeMessage
    if(fileContent == "")
    {
        cout << "No message! " << endl;
        return "";
    }

    return encodeMessage(fileContent);
}

// 101011 = 1*2^5 + 0*2^4 + 1*2^3 + 0*2^2 + 1*2^1 + 1*2^0 = 43
int HuffmanTree::myStoi(string code)
{
    int decimal = 0, length, p;
    length = code.length();
    p = length - 1; // stepen

    // chetem chisloto po bitove
    for(int i = 0; i < length; i++)
    {
        // kym tekushtoto desetichno chislo pribawqme chislo polucheno po gornata formula
        decimal += p >= 0 ? (code[i] - '0') * pow(2, p) : 0;
        p--;
    }
    return decimal;
}

void HuffmanTree::from8bitBinariesToDecimals(string encoded)
{
    string tempSub;
    // chetem po 8 bita ot koda, preobrazuvame gi w chislo i go izvejdame
    for (int i = 0; i < encoded.length(); i += 8)
    {
        tempSub = encoded.substr(i, 8);
        cout << myStoi(tempSub) << ' ';
    }
}

double HuffmanTree::ratio(string msg, string code)
{
    return code.length() / (msg.length() * 8.0);
}

string HuffmanTree::decodeMessage(string code)
{
    string decoded = "";
    Node* current = root;

    for(int i = 0; i < code.length(); i++)
    {
        if(current->left != NULL && current->right != NULL)
        {
            if(code[i] == '0')
            {
                if(current->left)
                    current = current->left;
            }
            else
            {
                if(current->right)
                    current = current->right;
            }
        }

        if(current->left == NULL && current->right == NULL)
        {
            decoded += current->symbol;
            current = root;
        }
    }
    return decoded;
}
