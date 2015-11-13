#include "StackLst.h"
#include <iostream>

int main()
{

	StackLst<int> stk{1, 2, 4, 5, 6, 7, 9};
	std::cout << stk;
	stk.pop();
	std::cout << stk;
	std::cout << stk.top() << "\n";
	std::cout << stk.popAndTop() << std::endl;
	stk.deleteStack();
	stk.top();
	return 0;		
}
