#include "Graph.h"
#include "GraphAlgo.h"

int
main()
{
	Graph::Graph g("topsort.txt");
	//Graph::Graph g("art.txt");
	//Graph::Graph g("undirected.txt");
	//Graph::Graph g("unweighted.txt");
	//Graph::Graph g("acyclic.txt");
	//Graph::Graph g("weighted.txt");
	g.PrintGraph();
	//GraphAlgo::Dijkstra(g, 0);
	//GraphAlgo::BFS(g, 0);
	//GraphAlgo::Prim(g, 0);
	//GraphAlgo::Kruskal(g);
	//GraphAlgo::DFS(g, 0);
	//GraphAlgo::FindArticulation(g, 0);
	GraphAlgo::CriticalPath(g, 0, 9);
	//GraphAlgo::TopologicalSortByQueue(g);
	return 0;
}
