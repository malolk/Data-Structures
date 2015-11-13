#ifndef NODE_H
#define NODE_H

template <typename T> 
class Node
{
public:
	Node() = default;
	T val = T();
	Node *next = nullptr;		
};
#endif

