#include "SinglyLinkedList/LinkedList.h"
#include <iostream>

//! solution to Chapter Ex3.2 
//! Running time O(N)

template <typename T>
void printLots(LinkedList<T> &l1, LinkedList<T> &l2)
{
	auto node1 = l1.header(), node2 = l2.header();
	if(!node1 || !node2 || !node2->next || !node1->next) return;
	std::size_t last = 0;
	node2 = node2->next;
	while(node2)
	{
		auto index = node2->val - last;
		last = node2->val;
		while(index-- > 0)
			node1 = node1->next;
		if(node1)
			std::cout << node1->val << " \n";
		else
			break;
		node2 = node2->next;
	}
}
int main()
{
	LinkedList<int> lst{10, 6, 3, 7, 8, 2, 5, 12};	
	LinkedList<int> lst2{6, 5, 3, 2};
	std::cout << lst; 
	std::cout << lst2;
	printLots(lst, lst2);
	return 0;
}
