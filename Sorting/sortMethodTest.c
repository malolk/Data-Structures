#include "SortMethod.h"
#include <string.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include "../trivalTools/readNums.h"

inline void printVec(const std::vector<int> &vec, const std::string &msg)
{
	std::ostream_iterator<int> output(std::cout, " ");
	std::cout << msg << std::endl;
	std::copy(vec.begin(), vec.end(), output);
	std::cout << std::endl;
}
int
main(int argc, char * argv[])
{
	int  NUM = atoi(argv[1]);
	std::vector<int> input;
	SortingMethod<int> sort;

	genRandomNums(input, NUM);
	printVec(input, "input nums: ");
	//sort.insertionSort(input, NUM);
	//sort.bubbleSort(input, NUM);
	//sort.shellSort(input, NUM);
	//sort.heapSort(input, NUM);
	//sort.mergeSort(input, NUM);
	sort.quickSelect(input, NUM, NUM/2 + 1);
	printVec(input, "output nums: ");
	sort.quickSort(input, NUM);
	printVec(input, "output nums: ");

	return 0;
}
