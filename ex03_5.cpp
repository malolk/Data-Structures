#include "SinglyLinkedList/LinkedList.h"
#include <iostream>

template <typename T>
LinkedList<T> listOr(LinkedList<T> &lst1, LinkedList<T> &lst2)
{
	auto head1 = lst1.header(), head2 = lst2.header();
	if(!head1 || !head2) return LinkedList<T>();
	LinkedList<T> lst3;
	auto node1 = head1->next, node2 = head2->next;
	auto head3 = lst3.header();
	auto cur = head3;
	auto pre1 = head1;
	auto pre2 = head2;
	while(node1 && node2)
	{
		if(node1->val < node2->val)
		{
			cur->next = node1;
			pre1 = node1;
			node1 = node1->next;
			cur = cur->next;
			cur->next = nullptr;	
		}
		else if(node1->val > node2->val)
		{
			cur->next = node2;
			pre2 = node2;
			node2 = node2->next;
			cur = cur->next;
			cur->next = nullptr;	
		}
		else
		{
			cur->next = node1;
			pre1 = node1;
			node1 = node1->next;
			cur = cur->next;
			cur->next = nullptr;	
			pre2 = node2;
			node2 = node2->next;	
		}
	}
	if(node1)
	{
		cur->next = node1;
		pre1->next = nullptr;	
		cur->next->next = nullptr;
	}
	else if(node2)
	{
		cur->next = node2;
		pre2->next = nullptr;	
		cur->next->next = nullptr;	
	}
	return lst3; 
}
int main()
{
	LinkedList<int> lst1{5, 4, 3, 2, 1};	
	LinkedList<int> lst2{7, 5, 0};	
	std::cout << lst1;
	std::cout << lst2;
	LinkedList<int> lst3 = listOr(lst1, lst2);

	std::cout << lst3;

	return 0;
}
