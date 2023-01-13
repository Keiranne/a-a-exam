#include "Graph.h"
#include <fstream>
#include <stack>
#include <deque>

void dfs(const Graph& g, bool* is_used, int curr_v){//r
	is_used[curr_v] = true;
	std::cout << char('a' + curr_v) << ' ';	//action
	int n = g.get_nV();
	for (int i = 0; i <n; ++i)
		if (g.get_edge(i, curr_v) && !is_used[i])
			dfs(g, is_used, i);
}

void DFS(const Graph& g) {//r
	int n = g.get_nV();
	bool* used = new bool[n] {};
	for (int i = 0; i < n; ++i)
	{
		if (!used[i])
		{
			dfs(g, used, i);
			std::cout << '\n';
		}
	}
}

void dfsST(Graph& g, bool *used, int n, int v) {//stack
	std::stack<int> s;
	s.push(v);
	used[v] = true;
	std::cout << char('a' + v) << ' ';

	while (!s.empty()) {
		v = s.top();
		bool pushed = false;
		for (int i = 0; i < n && !pushed; ++i)
			if (!used[i] && g.get_edge(i, v)) {
				s.push(i);
				used[i] = true;
				std::cout << char('a' + i) << ' ';
				pushed = true;
			}
		if(!pushed)
			s.pop();
	}
}

void DFSST(Graph& g) {//stack
	int n = g.get_nV();
	bool* used = new bool[n];
	for (int i = 0; i < n; ++i)
		used[i] = false;
	for (int i = 0; i < n; ++i)
	{
		if (!used[i])
		{
			dfsST(g, used, n, i);
			std::cout << '\n';
		}
	}
}

void bfs(const Graph& g, bool* is_used, int v) {
	int n = g.get_nV();

	std::deque<int> q;
	is_used[v] = true;
	q.push_back(v);

	while (!q.empty())
	{
		v = q.front();
		q.pop_front();
		std::cout << char('a' + v) << ' ';
		for (int i = 0; i < n; ++i)
			if (!is_used[i] && g.get_edge(i, v))
			{
				is_used[i] = true;
				q.push_back(i);
			}
	}
}

void BFS(const Graph& g) {
	int n = g.get_nV();
	bool* used = new bool[n] {};
	for (int i = 0; i < n; ++i)
		if (!used[i])
		{
			bfs(g, used, i);
			std::cout << '\n';
		}
}


int main() {

	std::ifstream in("input.txt");
	while(!in.eof())
	{
		Graph gr; 
		in >> gr;
		//std::cout << gr;
		std::cout << "\n-----------------------\n";
		//std::cout << "\nDFS:\n";	DFS(gr);
		std::cout << "\nDFSST:\n";	DFSST(gr);
		std::cout << "\nBFS:\n";	BFS(gr);
	}
	std::cin.get();
	in.close();
}
