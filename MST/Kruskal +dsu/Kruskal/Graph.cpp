#include "Graph.h"
Graph::Graph()
{
	n_vertex = n_edges =  0; arr = nullptr;
}

Graph::Graph(int n)
{
	n_vertex = n; n_edges = 0;
	arr = alloc_memory(n_vertex);
}

Graph::Graph(int** a, int nV, int nE)
{
	n_vertex = nV; n_edges = nE;
	arr = alloc_memory(n_vertex);
	copy(a, n_vertex, arr);
}

Graph::~Graph()
{
	free_memory(arr, n_vertex);
}

Graph::Graph(const Graph & g)
{
	n_vertex = g.n_vertex;
	n_edges = g.n_edges;
	arr = alloc_memory(n_vertex);
	copy(g.arr, n_vertex, arr);
}

Graph & Graph::operator=(const Graph & g)
{
	if (this != &g)
	{
		if (n_vertex != g.n_vertex)
		{
			free_memory(arr, n_vertex);
			n_vertex = g.n_vertex;
			n_edges = g.n_edges;
			arr = alloc_memory(n_vertex);
		}
		copy(g.arr, n_vertex, arr);
	}
	return *this;
}

int Graph::get_nV() const
{
	return n_vertex;
}


int Graph::get_nE() const
{
	return n_edges;
}

int ** Graph::get_arr() const
{
	return arr;
}

bool Graph::remove_edge(int i, int j)
{
	bool res = false;
	if (i >= 0 && j >= 0 && i < n_vertex && j < n_vertex && arr[i][j])
	{
		arr[i][j] = arr[j][i] = 0;
		res = true;
		--n_edges;
	}
	return res;
}

bool Graph::add_edge(int i, int j, int value)
{
	bool result = false;
	if (i >= 0 && j >= 0 && i < n_vertex && j < n_vertex && !arr[i][j])
	{
		result = true;
		arr[i][j] = arr[j][i] = value;
		++n_edges;
	}
	return result;
}

void Graph::add_vertex()
{
	int** tmp = alloc_memory(n_vertex);
	copy(arr, n_vertex, tmp);
	free_memory(arr, n_vertex);
	arr = alloc_memory(++n_vertex);
	copy(tmp, n_vertex - 1, arr);
	free_memory(tmp, n_vertex - 1);
}

bool Graph::remove_vertex(int k)
{
	bool res = false;
	if (k < n_vertex && k >= 0)
	{
		int **tmp = alloc_memory(n_vertex);
		copy(arr, n_vertex, tmp);
		free_memory(arr, n_vertex);
		arr = alloc_memory(--n_vertex);

		for (int i = 0; i < n_vertex; ++i)
			for (int j = 0; j < n_vertex; ++j)
			{
				if (i < k)
					arr[i][j] = tmp[i][(j < k ? j : j + 1)];
				else
					arr[i][j] = tmp[i + 1][(j < k ? j : j + 1)];
			}
		free_memory(tmp, n_vertex + 1);
		res = true;
	}
	return res;
}

int Graph::get_edge(int n1, int n2) const
{
	return (n1 >= 0 && n2 >= 0 && n1 < n_vertex && n2 < n_vertex && arr[n1][n2]) ? arr[n1][n2] : -1;
}

std::ostream & operator<<(std::ostream & out, const Graph & g)
{
	for (int i = 0; i < g.n_vertex; ++i)
	{
		for (int j = 0; j < g.n_vertex; ++j)
		{
			out.width(4);
			out << g.arr[i][j] << ' ';
		}
		out << '\n';
	}
	return out;
}

std::istream & operator>>(std::istream & in, Graph & g)
{
	int n_e;
	in >> g.n_vertex >> n_e;
	g.arr = g.alloc_memory(g.n_vertex);
	for (int i = 0; i < n_e; ++i)
	{
		int x, y, value;
		in >> x >> y >> value;
		g.add_edge(x - 1, y - 1, value);
	}
	return in;
}