#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include <iostream>
struct Node
{
    char symbol;
    int frequency;
    Node* left;
    Node* right;

    Node();
    Node(char, int);
    Node(char, int, Node*, Node*);
    Node(Node*, Node*);

    bool operator<(Node const&);
};
#endif // NODE_H_INCLUDED
