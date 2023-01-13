#pragma once
#include <iostream>
#include <iomanip>
class Graph {
	int n_vertex, n_edges, **arr;

	void copy(int** from_a, int n, int**to_a)
	{
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				to_a[i][j] = from_a[i][j];
	}
	void free_memory(int**&a, int n) {
		for (int i = 0; i < n; ++i)
			delete[] a[i];
		delete[] a;
	}
	int** alloc_memory(int n) {
		int** a = new int*[n];
		for (int i = 0; i < n; i++)
			a[i] = new int[n] {};
		return a;
	}

public:
	Graph();
	Graph(int n);
	Graph(int** a, int nV, int nE);
	~Graph();
	Graph(const Graph&g);
	Graph& operator=(const Graph& g);
	int get_nV() const;
	int get_nE() const;
	int** get_arr() const;
	//edge* get_ledge() const;
	bool remove_edge(int i, int j);
	bool add_edge(int i, int j, int value = 1);
	void add_vertex();
	bool remove_vertex(int k);
	int get_edge(int n1, int n2) const;
	friend std::ostream& operator<<(std::ostream& out, const Graph& g);
	friend std::istream& operator>>(std::istream& in, Graph& g);
};
