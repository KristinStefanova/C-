#include "Node.h"

Node::Node()
{
    left = NULL;
    right = NULL;
}

Node::Node(char s, int f)
{
    symbol = s;
    frequency = f;
    left = NULL;
    right = NULL;
}

Node::Node(char s, int f, Node *l, Node *r)
{
    symbol = s;
    frequency = f;
    left = l;
    right = r;
}

Node::Node(Node *l, Node *r)
{
    symbol = '~';
    frequency = l->frequency + r->frequency;
    left = l;
    right = r;
}

bool Node::operator<(Node const& other)
{
    return frequency < other.frequency;
}
