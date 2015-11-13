#include "QueueInArray.h"
#include <iostream>

int main()
{
	QueueInArray<int> q{1, 2, 3, 4, 5, 6};
	std::cout << q;
	q.Enqueue(3);
	std::cout << q;
	q.Dequeue();
	std::cout << q;
	std::cout << q.frontElem() << std::endl;
	q.makeEmpty();
	std::cout << "front: "<< q.curFront() << " rear: " << q.curRear() << std::endl;
	return 0;
}
