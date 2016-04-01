#include "LeftistHeaps.h"
#include <string.h>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "../trivalTools/readNums.h"

int main(int argc, char* argv[])
{
	int NUM = atoi(argv[1]);
	std::vector<int> vec, vec2;
	std::vector<int> vecSorted, vecSorted2,vecSorted3;
	std::ostream_iterator<int> output(std::cout, " ");
	LeftistHeaps<int> heap, heap2;

	genRandomNums(vec, NUM);
	std::cout << "input nums: \n";
	std::copy(vec.begin(), vec.end(), output);
	for(auto elem : vec)
		heap.insert(elem);
/*	while(!heap.isEmpty())
		vecSorted.push_back(heap.delTop());

	std::cout << "\noutput nums:\n";
	std::copy(vecSorted.begin(), vecSorted.end(), output);
	std::cout << std::endl;
*/	
	genRandomNums(vec2, NUM);
	std::cout << "input nums: \n";
	std::copy(vec2.begin(), vec2.end(), output);
	for(auto elem : vec2)
		heap2.insert(elem);
/*	while(!heap2.isEmpty())
		vecSorted2.push_back(heap2.delTop());

	std::cout << "\noutput nums:\n";
	std::copy(vecSorted2.begin(), vecSorted2.end(), output);
	std::cout << std::endl;
*/
	heap.merge(heap2);
	while(!heap.isEmpty())
		vecSorted3.push_back(heap.delTop());

	std::cout << "\noutput nums:\n";
	std::copy(vecSorted3.begin(), vecSorted3.end(), output);
	std::cout << std::endl;
 	
	return 0;
}
