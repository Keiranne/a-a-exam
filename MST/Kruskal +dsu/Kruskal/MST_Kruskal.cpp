#include "dsu(tree).h" //or #include "dsu(list).h"
#include "Graph.h"
#include <algorithm>
#include <fstream>

struct edge {
	int i, j, w;
	edge(int i = 0, int j = 0, int w = 0):	i(i), j(j), w(w) {}
};

edge* list_edges(std::istream &in) {
	int x, y, w, nE;
	in >> nE >> nE; //обусловлено порядком ввода: число_вершин число_ребер
	edge* list = new edge[nE];
	for (int i = 0; i < nE; ++i)
	{
		in >> x >> y >> w;
		list[i] = edge(x - 1, y - 1, w);
	}
	return list;
}
Graph Kruskal(const Graph &g) {
	int nE = g.get_nE(), nV = g.get_nV();
	Graph MST(nV);
	DSU dsu(nV);

	std::ifstream in("input.txt");
	edge* elist = list_edges(in);
	std::sort(elist, elist + nE, [](edge e1, edge e2) {return e1.w < e2.w; });
	in.close();

	int ecount = 1, i = 0;
	while (ecount < nV && i < nE) {
		if (dsu.Find(elist[i].i) != dsu.Find(elist[i].j))
		{ 
			dsu.Union(elist[i].i, elist[i].j);
			MST.add_edge(elist[i].i, elist[i].j, elist[i].w);
			++ecount; 
		} 
		++i; 
	}  
	return MST;
} 

int main() {
	std::ifstream in("input.txt");
	Graph gr;
	in >> gr;

	std::cout << "Graph:\n" << gr << "\nMST:\n" << Kruskal(gr);

	std::cin.get();
	in.close();
}
/*
	DSU dsu(5);
	dsu.print();
	dsu.Union(1, 4);
	dsu.print();
	dsu.Union(2, 3);
	dsu.print();
	dsu.Union(2, 4);
	dsu.print();
	dsu.Find(4);
	dsu.print();*/