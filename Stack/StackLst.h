#ifndef STACKLST_H
#define STACKLST_H

#include "Node.h"
#include <initializer_list>
#include <iostream>
template <typename> class StackLst;
template <typename T>
std::ostream& operator<<(std::ostream &out, StackLst<T>& s);
template <typename T>
class StackLst
{
friend std::ostream& operator<<<T>(std::ostream &out, StackLst &s);
public:
	StackLst() : head(new class Node<T>()) {}
	StackLst(std::initializer_list<T> l);
	bool isEmpty();
	void makeEmpty();
	void push(T elem);
	void pop();
	T top();
	T popAndTop();	
	void deleteStack();
	~StackLst()
	{
		deleteStack();	
	}
private:
	Node<T>* head;	
};

template <typename T>
std::ostream& operator<<(std::ostream &out, StackLst<T> &s)
{
	auto tmp = s.head->next;
	while(tmp)
	{
		out << tmp->val << (tmp->next ? "->" : "\n");		
		tmp = tmp->next;
	}
	return out;
}

template <typename T>
void StackLst<T>::push(T elem)
{
	auto newNode = new class Node<T>();
	if(!newNode)
	{
		std::cerr << "push: out of space\n";
		return;  	
	}
	newNode->val = elem;
	newNode->next = head->next;
	head->next = newNode;
}


template <typename T>
bool StackLst<T>::isEmpty()
{
	if(!head)
	{
		std::cerr << "isEmpty: stack has no header.\n";
		return true;	
	}
	return head->next == nullptr;	
}
template <typename T>
void StackLst<T>::pop()
{
	if(isEmpty())
		return;	
	auto tmpNode = head->next;
	head->next = tmpNode->next;
	delete tmpNode;
}
template <typename T>
T StackLst<T>::top()
{
	if(isEmpty())
	{
		std::cerr << "top: Empty Stack\n";
		return T();
	}
	return head->next->val;	
}
template <typename T>
T StackLst<T>::popAndTop()
{
	auto ret = top();
	pop();
	return ret;	
}

template <typename T>
void StackLst<T>::makeEmpty()
{
	while(!isEmpty())
		pop();	
}
template <typename T>
void StackLst<T>::deleteStack()
{
	makeEmpty();
	delete head;
	head = nullptr;	
}

template <typename T>
StackLst<T>::StackLst(std::initializer_list<T> l)
{
	head = new class Node<T>();
	for(auto it : l)
		push(it);	
}

#endif

