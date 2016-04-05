#include "Graph.h"
#include "GraphAlgo.h"

int
main()
{
	Graph::Graph g("undirected.txt");
	//Graph::Graph g("unweighted.txt");
	//Graph::Graph g("acyclic.txt");
	//Graph::Graph g("weighted.txt");
	g.PrintGraph();
	//GraphAlgo::Dijkstra(g, 0);
	//GraphAlgo::BFS(g, 0);
	GraphAlgo::Prim(g, 0);
	GraphAlgo::Kruskal(g);
	return 0;
}
