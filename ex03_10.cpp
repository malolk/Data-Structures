#include <iostream>
#include "SinglyLinkedList/LinkedList.h"
#include <string>

LinkedList<unsigned> circleCreate(unsigned N)
{
	LinkedList<unsigned> ret;
	while(N > 0)
	{
		ret.insertElem(N, ret.header());
		--N;	
	}		
	return ret;	
}

void Josephus(LinkedList<unsigned> &lst, unsigned M)
{
	unsigned m = M;
	auto pre = lst.header();
	auto node = pre->next; 
	while(m >= 0)
	{
		if(lst.header()->next->next == nullptr)
			break;
		if(m == 0)
		{
			auto tmp = node;
			std::cout << node->val << " ";
			pre->next = node->next;
			node = node->next;
			delete tmp;
			m = M;
		}		
		else
		{
			pre = node;
			node = node->next;	
			--m;
		}
		if(!node)
		{
			pre = lst.header();
			node = pre->next;	
		}
	}	
}


int main(int argc, char** argv)
{
	unsigned M = stoi(std::string(argv[1]));
	unsigned N = stoi(std::string(argv[2]));
	LinkedList<unsigned> lst = circleCreate(N);
	Josephus(lst, M);

	return 0;
}
