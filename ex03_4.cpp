#include "SinglyLinkedList/LinkedList.h"
#include <iostream>

//! assume sorted lists are in ascending order
template <typename T>
LinkedList<T> listAnd(LinkedList<T> &lst1, LinkedList<T> &lst2)
{
	auto head1 = lst1.header(), head2 = lst2.header();
	if(!head1 || !head2) return LinkedList<T>();
	LinkedList<T> lst3;
	auto node1 = head1->next, node2 = head2->next;
	auto head3 = lst3.header();
	auto cur = head3;
	auto pre = head1;
	while(node1 && node2)
	{
		if(node1->val > node2->val)
		{
			node2 = node2->next;		
		}	
		else if(node1->val < node2->val)
		{
			pre = node1;
			node1 = node1->next;
		}
		else
		{
			cur->next = node1;
			pre = node1;
			node1 = node1->next;
			cur->next->next = nullptr;
			cur = cur->next;
			node2 = node2->next;	
		}
	}
	return lst3; 
}
int main()
{
	LinkedList<int> lst1{1, 2, 3, 4, 5};	
	LinkedList<int> lst2{1, 4, 7};	
	std::cout << lst1;
	std::cout << lst2;
	LinkedList<int> lst3 = listAnd(lst1, lst2);

	std::cout << lst3;

	return 0;
}
