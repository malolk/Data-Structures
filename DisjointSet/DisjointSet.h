#ifndef DISJOINTSET_H_
#define DISJOINTSET_H_

#include <vector>

namespace DisjointSet
{

class DisjointSet
{
public:
	DisjointSet(int num)
	{
		disjointSet = (0, num);	
	}
	void SetUnion(int s1, int s2)
	{
		if(disjointSet[s1] < disjointSet[s2])
			disjointSet[s2] = s1;
		else
		{
			if(disjointSet[s1] == disjointSet[s2])
				disjointSet[s2]--;
			disjointSet[s1] = s2;
		}
	}

	int FindSetName(int s)
	{
		if(disjointSet[s] <= 0)
			return disjointSet[s];
		else
			return FindSetName(disjointSet[s]);
	}

private:	
	std::vector<int> disjointSet; 
};	
	
};
#endif

