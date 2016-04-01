#include "BasicHeaps.h"
#include <string.h>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "../trivalTools/readNums.h"

int main(int argc, char *argv[])
{

	int NUM = atoi(argv[1]);
	int flag = atoi(argv[2]);
	std::vector<int> vec;
	std::vector<int> vecSorted;
	std::ostream_iterator<int> output(std::cout, " ");
	BasicHeaps<int> heap(NUM, flag);

	genRandomNums(vec, NUM);
	std::cout << "input nums:\n";
	std::copy(vec.begin(), vec.end(), output);
	for(auto elem : vec)
		heap.insert(elem);
	while(!heap.isEmpty())
		vecSorted.push_back(heap.delTop());

	std::cout << "\noutput nums:\n";
	std::copy(vecSorted.begin(), vecSorted.end(), output);

	std::cout << std::endl;
	return 0;

}
