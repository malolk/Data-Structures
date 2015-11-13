#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <memory>
#include <initializer_list>
#include <iostream>

template <typename> class LinkedList;
template <typename> class Node;
template <typename T>
Node<T>* findElem(T elem, LinkedList<T> &l);
template <typename T>
Node<T>* findPreElem(T elem, Node<T>* node);
template <typename T>
std::ostream& operator<<(std::ostream &out, LinkedList<T> &l);
template <typename T>
class LinkedList
{
	friend Node<T>* findElem<T>(T elem, LinkedList<T>& l);
	friend Node<T>* findPreElem<T>(T elem, Node<T>* node);
	friend std::ostream& operator<<<T>(std::ostream &out, LinkedList<T> &l);
public:
	LinkedList():head(new class Node<T>()) {};
	LinkedList(std::initializer_list<T> l);
	bool isEmpty();
	bool isLast(Node<T>* p);
	void delElemOnce(T elem);
	void delElemAll(T elem);
	void insertElem(T elem, Node<T>* p);
	void deleteList();
	Node<T>* header() {return head;}
	~LinkedList();
private:
	Node<T> *head = nullptr;	
};


template <typename T>
std::ostream& operator<<(std::ostream &out, LinkedList<T> &l)
{
	if(!l.head) return out;
	auto node = l.head->next;
	while(node)
	{
		out << node->val << (node->next ? " -> " : "\n");
		node = node->next;	
	}		
	return out;
}
template <typename T>
bool LinkedList<T>::isEmpty()
{
	return this->head == nullptr;	
}

template <typename T>
bool LinkedList<T>::isLast(Node<T>* p)
{
	return p->next == nullptr;	
}

template <typename T>
Node<T>* findElem(T elem, LinkedList<T> &l)
{
	if(!l.head) return nullptr;
	auto node = l.head->next;
	while(node && node->val != elem)
		node = node->next; 
	return node;
}
template <typename T>
Node<T>* findPreElem(T elem, Node<T> *firstNode)
{
	if(!firstNode || !firstNode->next)
		return nullptr;
	auto preNode = firstNode;
	while(preNode->next)
	{
		if(preNode->next->val == elem)
			return preNode;
		preNode = preNode->next;
	}
	return nullptr;
}
template <typename T>
Node<T>* delNode(T elem, Node<T> *node)
{
	if(!node || !node->next)
		return nullptr;
	auto preNode = findPreElem(elem, node);
	if(!preNode)
		return nullptr;
	auto tmpNode = preNode->next;
	preNode->next = tmpNode->next;
	delete tmpNode;
	return preNode;
}

template <typename T>
void LinkedList<T>::delElemOnce(T elem)
{
	delNode(elem, head);
}

template <typename T>
void LinkedList<T>::delElemAll(T elem)
{
	if(!head || !head->next)
		return;
	auto preNode = head;
	while(preNode = delNode(elem, preNode));
}

template <typename T>
void LinkedList<T>::insertElem(T elem, Node<T>* p)
{
	if(!p) return;
	auto newNode = new class Node<T>();
	if(newNode == nullptr)
	{
		std::cerr << "insertElem: out of space\n";	
	}
	newNode->val = elem;
	newNode->next = p->next;
	p->next = newNode;
}

template <typename T>
void LinkedList<T>::deleteList()
{
	while(head)
	{
		auto node = head->next;
		delete head;
		head = node;	
	}
}
template <typename T>
LinkedList<T>::~LinkedList()
{
	deleteList();	
}

template <typename T>
LinkedList<T>::LinkedList(std::initializer_list<T> l)
{
	this->head = new class Node<T>();			
	for(auto &it : l)
		insertElem(it, this->head);
}
#endif

