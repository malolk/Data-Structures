#include <iostream>
#include "SinglyLinkedList/LinkedList.h"
#include <string>

LinkedList<unsigned> circleCreate(unsigned N)
{
	LinkedList<unsigned> ret;
	unsigned cnt = 1;
	while(cnt <= N)
		ret.insertElem(cnt++);	
	return ret;	
}

void Josephus(LinkedList<unsigned> &lst, unsigned M)
{
	unsigned m = M;
	auto pre = lst.header();
	auto node = lst.next(pre); 
	while(m >= 0)
	{
		if(lst.isLast(lst.first()))
			break;
		if(m == 0)
		{
			std::cout << lst.val(node) << " ";
			pre = lst.delNode(pre);
			node = lst.next(pre);
			m = M;
		}		
		else
		{
			pre = node;
			node = lst.next(pre);
			--m;
		}
		if(!node)
		{
			pre = lst.header();
			node = lst.first();	
		}
	}	
}


int main(int argc, char** argv)
{
	unsigned M = stoi(std::string(argv[1]));
	unsigned N = stoi(std::string(argv[2]));
	LinkedList<unsigned> lst = circleCreate(N);
	std::cout << lst;
	Josephus(lst, M);

	return 0;
}
