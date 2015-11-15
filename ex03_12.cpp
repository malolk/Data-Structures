#include "SinglyLinkedList/LinkedList.h"
#include <iostream>

//! running time O(N), constant extra space.
template <typename T>
void reverseList(LinkedList<T> &lst)
{
	auto head = lst.header();
	if(!head) return;
	auto node = head->next;
	if(!node || !node->next) return;

	auto leftNode = node, rightNode = node;
	leftNode = nullptr;
	while(node)
	{
		rightNode = node->next;
		node->next = leftNode;
		leftNode = node;
		node = rightNode;		
	}
	head->next = leftNode;
}

int main()
{
	LinkedList<unsigned> lst{1, 2, 3, 4, 5, 6, 7, 8, 9};
	std::cout << lst;
	reverseList(lst);
	std::cout << lst;
	return 0;	
}
