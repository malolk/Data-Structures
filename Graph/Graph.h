#ifndef GRAPH_H_
#define GRAPH_H_

#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../trivalTools/readTxt.h"


namespace Graph
{


class Node
{
public:
	int orderNum;
	int weight;
	Node *next;	
};

class Graph
{
public:
	Graph() = default;
	Graph(const std::string &path)
	{
		std::string oneLine;
		std::string strBuffer;	
		std::ifstream fileIn(path);
		std::vector<int> record; 
		Node *node;
		std::getline(fileIn, oneLine);
		splitStr2Int(oneLine, record);
		vetexNum = record[0];
		edgeNum = record[1];
		oneLine.clear();
		std::cout << "v :" << vetexNum << "edge: " << edgeNum << std::endl;
		if((g = (Node **)std::malloc(vetexNum*sizeof(Node *))) == nullptr)
			exit(-1);
		for(int i = 0; i < vetexNum; ++i)
			g[i] = nullptr;
		while(std::getline(fileIn, oneLine))
		{
			std::cout << oneLine << std::endl;
			record.clear();
			splitStr2Int(oneLine, record);
			if((node = (Node *)std::malloc(sizeof(Node))) == nullptr)
				exit(-1);
			if(record.empty())
				break;
			node->orderNum = record[1];
			node->weight = record[2];
			if(g[record[0]] == nullptr)
				node->next = nullptr;
			else
				node->next = g[record[0]];
			g[record[0]] = node;
			oneLine.clear();
		}	
	}

	void PrintGraph()
	{
		Node *pNode;
		for(int i = 0; i < vetexNum; ++i)
		{
			pNode = g[i];
			std::cout << "Node " << i << ": ";
			while(pNode != nullptr)
			{
				std::cout << "->" << pNode->orderNum;
				pNode = pNode->next;
			}
			std::cout << std::endl; 
		}		
	}
	Node **GetAdjLst()
	{
		return g;	
	}
	int GetVetexNum()
	{
		return vetexNum;	
	} 
	int GetEdgeNum()
	{
		return edgeNum;	
	} 

	~Graph()
	{
		Node *pNode, *ptmp;
		for(int i = 0; i < vetexNum; ++i)	
		{
			pNode = g[i];
			while(pNode != nullptr)
			{
				ptmp = pNode;
				pNode = pNode->next;
				free(ptmp);	
			}
		}
		if(g != nullptr)
			free(g);
	}
private:
	int vetexNum = 0;
	int edgeNum = 0;		
	Node **g;
};
};
#endif  // GRAPH_H_
