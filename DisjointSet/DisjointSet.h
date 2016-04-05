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
		disjointSet = std::vector<int>(num, -1);
    }	
	void SetUnion(int s1, int s2)
	{
		int u = FindSetName(s1);
		int v = FindSetName(s2);
		if(disjointSet[u] < disjointSet[v])
			disjointSet[v] = u;
		else
		{
			if(disjointSet[u] == disjointSet[v])
				disjointSet[v]--;
			disjointSet[u] = v;
		}
	}

	int FindSetName(int s)
	{
		if(disjointSet[s] < 0)
			return s;
		else
			return FindSetName(disjointSet[s]);
	}

private:	
	std::vector<int> disjointSet; 
};	
	
};
#endif

