#pragma once
#include <iostream>

class DSU {
	struct node {
		node* next;
		int info;
		~node() { next = nullptr; }
		node(int info, node*next = nullptr) : info(info), next(next) {}
	};
	struct listnode {
		node * head, *tail;
		int rank;
		~listnode() { head = nullptr; tail = nullptr; }
		listnode() { rank = 0; head = tail = nullptr; }
	};

	listnode* subset;
	int size, *represents;

	void make_set(int i);
	void reparent(int x, int new_prnt);
	void link(int less, int more);
public:
	DSU(int size) :size(size) {
		represents = new int[size];
		subset = new listnode[size];
		for (int i = 0; i < size; ++i)
		{
			make_set(i);
		}
	}
	~DSU();
	int Find(int x);
	void Union(int x, int y);

	void print();
	void print_represents();
};