#include "DisjointSet.h"
#include <iostream>

int
main()
{
	DisjointSet::DisjointSet mset(10);
	mset.SetUnion(0, 2);
	std::cout << mset.FindSetName(0) << std::endl;
	std::cout << mset.FindSetName(2) << std::endl;
	mset.SetUnion(0, 1);
	std::cout << mset.FindSetName(1) << std::endl;

	if(mset.FindSetName(1) == mset.FindSetName(2))
		std::cout << "correct\n";
	return 0;
}
