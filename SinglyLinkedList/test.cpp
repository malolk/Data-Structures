#include "LinkedList.h"
#include <iostream>

int main()
{
	LinkedList<int> lst{1, 2, 3, 4, 5};
	lst.insertElem(3, lst.header());
	std::cout << lst;	
//	lst.delElemOnce(3);
	lst.delElemAll(3);
	std::cout << lst;
	lst.deleteList();	
	return 0;	
}
