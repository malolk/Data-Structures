#ifndef GRAPHALGO_H_
#define GRAPHALGO_H_

#include "Graph.h"
#include <vector>
#include <algorithm>
#include "../Queue/QueueInArray.h"
#include "../DisjointSet/DisjointSet.h"

namespace GraphAlgo
{

int FindVetexOfInDegreeZero(std::vector<int> &inDegree, int vetexNum)
{
	for(int cnt = 0; cnt < vetexNum; ++cnt)
	{
		if(inDegree[cnt] == 0)
		{
			inDegree[cnt] = -1;
			return cnt;	
		}
	}	
	return -1;
}


class PathLog
{
public:
	int known;
	int distance;	
	int lastPath;
};
class EdgesLog
{
public:
	int u;
	int v;
	int weight;	
};

void InitializeEdgesLog(EdgesLog *pEdge, Graph::Node **lst, int vetexNum, std::vector<EdgesLog *> &pEdgeVec)
{
	Graph::Node *pNode;
	int cnt = 0;
	for(int i = 0; i < vetexNum; ++i)
	{
		pNode = lst[i];
		while(pNode != nullptr)
		{
			pEdge[cnt].u = i;
			pEdge[cnt].v = pNode->orderNum;
			pEdge[cnt].weight = pNode->weight;
			pEdgeVec[cnt] = &pEdge[cnt];
			++cnt;
			pNode = pNode->next;
		}
	}
}

void Kruskal(Graph::Graph &g)
{
	int vetexNum = g.GetVetexNum();
	int edgeNum = g.GetEdgeNum();
	Graph::Node **lst = g.GetAdjLst();
	EdgesLog *pEdge = (EdgesLog *)malloc(edgeNum*sizeof(EdgesLog));
	std::vector<EdgesLog *> pEdgeVec(edgeNum, nullptr);
	std::vector<int> edgePos;
	DisjointSet::DisjointSet setOfVetex(vetexNum);
	if(pEdge == nullptr)
	{
		std::cerr << "Kruskal: malloc error\n";
		exit(-1);	
	}
	InitializeEdgesLog(pEdge, lst, vetexNum, pEdgeVec);
	std::sort(pEdgeVec.begin(), pEdgeVec.end(),
	[](EdgesLog *edgeLeft, EdgesLog *edgeRight){ return edgeLeft->weight < edgeRight->weight; });
	int cnt = 0;
	int edgesInTree = 0;
	while(edgesInTree < vetexNum - 1)
	{
		int u = pEdgeVec[cnt]->u;
		int v = pEdgeVec[cnt]->v;
		if(setOfVetex.FindSetName(u) != setOfVetex.FindSetName(v))
		{	
			setOfVetex.SetUnion(u, v);
			++edgesInTree;
			edgePos.push_back(cnt);
		}
		++cnt;	
	}
	std::cout << "Kruskal finding spanning tree:\n";
	for(const auto &pos : edgePos)
	{
		std::cout << pEdgeVec[pos]->u << ", " 
		<< pEdgeVec[pos]->v << std::endl;	
	}
}
void InitializeNodeLog(PathLog *nodeLog, int startNode, int vetexNum)
{
	for(int i = 0; i < vetexNum; ++i)
	{
		nodeLog[i].known = 0;
		nodeLog[i].lastPath = startNode;
		nodeLog[i].distance = 1 << 30;	
	}
	nodeLog[startNode].distance = 0;	
}

void PrintPath(PathLog *nodeLog, int startNode, int endNode)
{
		if(endNode == startNode)
			return;
		else
		{
			PrintPath(nodeLog, startNode, nodeLog[endNode].lastPath);
			std::cout << "->" << endNode;	
		}		
}

void PrintAllPaths(PathLog *nodeLog, int startNode, int vetexNum)
{
	for(int i = 0; i < vetexNum; ++i)
	{
		std::cout << "node " << startNode << " to " << i << ": ";
		PrintPath(nodeLog, startNode, i);
		std::cout << "\n";
	}	
}

int FindSmallestPoint(PathLog *nodeLog, int vetexNum)
{
	int dist = 1 << 30;
	int retPos;
	for(int i = 0; i < vetexNum; ++i)
	{
		if(!nodeLog[i].known && nodeLog[i].distance != (1 << 30))
		{
			if(nodeLog[i].distance < dist)
			{
				dist = nodeLog[i].distance;
				retPos = i;	
			}
		}	
	}	
	return retPos;
}

void Prim(Graph::Graph &g, int startNode)
{
	int vetexNum = g.GetVetexNum();
	Graph::Node **lst = g.GetAdjLst();
	PathLog *nodeLog = (PathLog *)malloc(vetexNum*sizeof(PathLog));
	if(nodeLog == nullptr)
	{
		std::cerr << "Prim: malloc error\n";
		return;	
	}
	InitializeNodeLog(nodeLog, startNode, vetexNum);

	int knownNum = 0;
	int curPos;
	Graph::Node *pNode;
	while(knownNum < vetexNum)
	{
		curPos = FindSmallestPoint(nodeLog, vetexNum);
		nodeLog[curPos].known = 1;
		pNode = lst[curPos];
		while(pNode != nullptr)
		{
			int orderNum = pNode->orderNum;
			int newLength = pNode->weight;
			if(!nodeLog[orderNum].known)	
			{
				if(nodeLog[orderNum].distance == 1 << 30 || nodeLog[orderNum].distance > newLength)
				{
					nodeLog[orderNum].distance = newLength;
					nodeLog[orderNum].lastPath = curPos;
				}	
			}
			pNode = pNode->next;
		}
		++knownNum;
	}
	PrintAllPaths(nodeLog, startNode, vetexNum);
}
void Dijkstra(Graph::Graph &g, int startNode)
{
	int vetexNum = g.GetVetexNum();
	Graph::Node **lst = g.GetAdjLst();
	PathLog *nodeLog = (PathLog *)malloc(vetexNum*sizeof(PathLog));
	if(nodeLog == nullptr)
	{
		std::cerr << "Dijkstra: malloc error\n";
		return;	
	}
	InitializeNodeLog(nodeLog, startNode, vetexNum);
	
	int knownNum = 0;
	int curPos;
	Graph::Node *pNode;
	while(knownNum < vetexNum)
	{
		curPos = FindSmallestPoint(nodeLog, vetexNum);
		nodeLog[curPos].known = 1;
		pNode = lst[curPos];
		while(pNode != nullptr)
		{
			int orderNum = pNode->orderNum;
			int newLength = nodeLog[curPos].distance + pNode->weight;
			if(!nodeLog[orderNum].known)	
			{
				if(nodeLog[orderNum].distance == 1 << 30 || nodeLog[orderNum].distance > newLength)
				{
					nodeLog[orderNum].distance = newLength;
					nodeLog[orderNum].lastPath = curPos;
				}	
			}
			pNode = pNode->next;
		}
		++knownNum;
	}
	PrintAllPaths(nodeLog, startNode, vetexNum);

}
void BFS(Graph::Graph &g, int startNode)
{
	int vetexNum = g.GetVetexNum();
	Graph::Node **lst = g.GetAdjLst();
	PathLog *nodeLog = (PathLog *)malloc(vetexNum*sizeof(PathLog));
	QueueInArray<int> queuePro(vetexNum);
	if(nodeLog == nullptr)
	{
		std::cerr << "BFS: malloc error\n";
		return;	
	}
	InitializeNodeLog(nodeLog, startNode, vetexNum);
	queuePro.Enqueue(startNode);
	int curNode;
	Graph::Node *pNode;
	while(!queuePro.isEmpty())
	{
		curNode = queuePro.frontElem();
		queuePro.Dequeue();
		pNode = lst[curNode];
		while(pNode != nullptr)
		{
			if(nodeLog[pNode->orderNum].distance == 1 << 30)
			{
				nodeLog[pNode->orderNum].distance = nodeLog[curNode].distance + 1;
				nodeLog[pNode->orderNum].lastPath = curNode;
				queuePro.Enqueue(pNode->orderNum);
			}
			pNode = pNode->next;
		}
	}
	PrintAllPaths(nodeLog, startNode, vetexNum);
}
void InitializeInDegree(std::vector<int> &inDegree, Graph::Node **lst, int vetexNum)
{
	for(int i = 0; i < vetexNum; ++i)
	{
		Graph::Node *pNode = lst[i];
		while(pNode != nullptr)
		{
			inDegree[pNode->orderNum]++;
			pNode = pNode->next;
		}
	}
}

void TopologicalSort(Graph::Graph &g)
{
	int vetexNum = g.GetVetexNum();
	Graph::Node **lst = g.GetAdjLst();
	std::vector<int> orderingNum;
	std::vector<int> inDegree(vetexNum, 0);
	InitializeInDegree(inDegree, lst, vetexNum);
	for(int i = 0; i < vetexNum; ++i)
	{
		int zeroInDegree = 0;
		if((zeroInDegree = FindVetexOfInDegreeZero(inDegree, vetexNum)) == -1)
		{
			std::cerr << "Graph is not acyclic\n";
			return; 	
		}
		orderingNum.push_back(zeroInDegree);
		Graph::Node *pNode = lst[zeroInDegree];
		while(pNode != nullptr)
		{
			inDegree[pNode->orderNum]--;
			pNode = pNode->next;	
		}
	}
	for(const auto &elem : orderingNum)
		std::cout << elem << " ";
	std::cout << std::endl;
}

void TopologicalSortByQueue(Graph::Graph &g)
{
	int vetexNum = g.GetVetexNum();
	Graph::Node **lst = g.GetAdjLst();
	std::vector<int> orderingNum;
	QueueInArray<int> qZeroInDegree(vetexNum);
	std::vector<int> inDegree(vetexNum, 0);
	InitializeInDegree(inDegree, lst, vetexNum);
	for(int i = 0; i < vetexNum; ++i)
		if(inDegree[i] == 0)
			qZeroInDegree.Enqueue(i);

	int counter = 0;
	while(!qZeroInDegree.isEmpty())
	{
		int zeroInDegree = qZeroInDegree.frontElem();
		qZeroInDegree.Dequeue();
		orderingNum.push_back(zeroInDegree);
		Graph::Node *pNode = lst[zeroInDegree];
		while(pNode != nullptr)
		{
			if(--inDegree[pNode->orderNum] == 0)
				qZeroInDegree.Enqueue(pNode->orderNum);
			pNode = pNode->next;	
		}
	}
	if(orderingNum.size() != vetexNum)
	{
		std::cerr << "Graph is not acyclic\n";
		return;	
	}
	for(const auto &elem : orderingNum)
		std::cout << elem << " ";
	std::cout << std::endl;
}
};
#endif    //GRAPHALGO_H_
