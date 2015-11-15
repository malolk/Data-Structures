#include "SinglyLinkedList/LinkedList.h"
#include <iostream>
#include <vector>
#include <cstddef>

using listPtr = LinkedList<unsigned>*;
void radix_sort(std::vector<listPtr> &array, listPtr numbers)
{
	std::size_t bucket = array.size();
	auto buf = array;
	//! assumed Bucket be 10 , pass = 3;
	auto pre = numbers->header();
	auto node = pre->next;
	pre->next = nullptr;
	if(!node)
		return;
	while(node)
	{
		auto tmp = node->next;
		array[node->val%bucket]->appendNode(node);	
		node = tmp;
	}
	for(unsigned m = 0; m < 10; ++m)
	{
		auto headArray = array[m]->header();
		auto nd = headArray->next;
		headArray->next = nullptr;
		if(nd == nullptr) continue;
		while(nd != nullptr)
		{
			unsigned index = ((nd->val)/bucket)%bucket;
			LinkedList<unsigned>* l = buf[index];
			auto tmp = nd->next;
			l->appendNode(nd);
			nd = tmp;
		}
	}
	for(unsigned i = 0; i < 10; ++i)
	{
		auto headBuf = buf[i]->header();
		auto nd = headBuf->next;
		headBuf->next = nullptr;
		if(nd == nullptr) continue;
		while(nd)
		{
			auto tmp  = nd->next;
			unsigned index = ((nd->val)/bucket)/bucket;
			LinkedList<unsigned>* l = array[index];
			l->appendNode(nd);
			nd = tmp;
		}
	}	
}


int main()
{
	std::vector<listPtr> array;
	unsigned size = 10;
	while(size-- > 0)
	{
		listPtr p = new LinkedList<unsigned>;
		array.push_back(p);
	}
	LinkedList<unsigned> num{1, 34, 37, 75, 354, 56,234, 756,123, 32, 43, 272, 34, 23};
	std::cout << num;
 	radix_sort(array, &num);
	for(auto it : array)
	{
		std::cout << *it;	
	}

	return 0;
}

