#ifndef TRIVALTOOLS_READNUMS_H_
#define TRIVALTOOLS_READNUMS_H_

#include <iostream>
#include <random>
#include <vector>

namespace{
	using namespace std;

void genRandomNums(vector<int> &vecBuffer, int size)
{
	static default_random_engine e;
	static uniform_int_distribution<int> u(-100, 100);
	for(size_t i = 0; i < size; ++i)
	{
		vecBuffer.push_back(u(e));	
	}		
}

};

#endif		//TRIVALTOOLS_READNUMS_H_
