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
	LinkedList():head(new class Node<T>()) { last = head; };
	LinkedList(std::initializer_list<T> l);
	LinkedList(const LinkedList&);
	LinkedList& operator==(const LinkedList&);
	LinkedList(LinkedList&&) noexcept;
	LinkedList& operator==(LinkedList&&) noexcept;

	bool isEmpty();
	bool isLast(Node<T>* p);
	void delElemOnce(T elem);
	void delElemAll(T elem);
	void insertElem(T elem, Node<T>* p);
	void insertElem(T elem);
	void deleteList();
	void appendNode(Node<T>* n);
	void check_last();
	Node<T>* next(Node<T> *p) { return  ((p&&p->next) ? p->next : nullptr); }
	T val(Node<T> *p) { return p->val; }
	Node<T>* delNode(Node<T> *node);
	Node<T>* first() { return head->next; }
	Node<T>* header() {return head;}
	~LinkedList();
private:
	Node<T>* delNode(T elem, Node<T> *node);
	Node<T> *head = nullptr;
	Node<T> *last = nullptr;	
};

template <typename T>
void LinkedList<T>::check_last()
{
	last = head;
	while(last->next)
		last = last->next;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& rhs)
{
	head = new class Node<T>();
	last = head;
	auto node = rhs.head;
	if(!node->next) 
		return;
	else
		node = node->next; 
	while(node)
	{
		insertElem(node->val);
		node = node->next;
	}
}

template <typename T>
void LinkedList<T>::appendNode(Node<T>* n)
{
	check_last();
	last->next = n;
	//n->next = nullptr;
	last = n;
	last->next = nullptr;	
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList&& rhs) noexcept
{
	head = new class Node<T>();
	last = rhs.last;
	if(!rhs.head) return;
	head->next = rhs.head->next;
	rhs.head->next = nullptr;	
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator==(const LinkedList& rhs)
{
	if(head != rhs.head)
	{
		deleteList();
		head = new class Node<T>();
		last = head;
		auto node = rhs.head;
		if(!node || !node->next)
			return *this;
		node = node->next;
		while(node)
		{
			insertElem(node->val);
			node = node->next;
		}			
	}
	return *this;	
}
template <typename T>
LinkedList<T>& LinkedList<T>::operator==(LinkedList&& rhs) noexcept
{
	if(head != rhs.head)
	{
		deleteList();
		head = new class Node<T>();
		last = rhs.last;
		head->next = rhs.head->next;
		rhs.head->next = nullptr;
	}	
	return *this;
}
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
Node<T>* LinkedList<T>::delNode(T elem, Node<T> *node)
{
	if(!node || !node->next)
		return nullptr;
	auto preNode = findPreElem(elem, node);
	if(!preNode)
		return nullptr;
	auto tmpNode = preNode->next;
	preNode->next = tmpNode->next;
	if(last == tmpNode)
		last = preNode;
	delete tmpNode;
	return preNode;
}
template <typename T>
Node<T>* LinkedList<T>::delNode(Node<T> *node)
{
	if(!node || !node->next)
		return node;
	auto tmp = node->next;	
	node->next = tmp->next;
	if(last == tmp)
		last = node;
	delete tmp;
	return node;
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
	if(p == last)
		last = newNode;
}

template <typename T>
void LinkedList<T>::insertElem(T elem)
{
	insertElem(elem, last);	
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
	last = head;
}
template <typename T>
LinkedList<T>::~LinkedList()
{
	deleteList();	
}

template <typename T>
LinkedList<T>::LinkedList(std::initializer_list<T> l)
{
	head = new class Node<T>();			
	last = head;
	for(auto &it : l)
		insertElem(it);
}
#endif

