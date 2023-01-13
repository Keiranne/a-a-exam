#pragma once
#include <iostream>

class DSU
{
	struct node {
		int i, parent, rank;
		node(int i = 0) : i(i), parent(i) {//~make_set(i)
			rank = 0;
		}
	};

	int n;
	node* subsets;
	void link(int less, int more);
public:
	DSU(int n) : n(n) {
		subsets = new node[n];
		for (int i = 0; i < n; ++i)
			subsets[i] = node(i);
	}
	~DSU();
	int Find(int i);
	void Union(int x, int y);

	void print();
};