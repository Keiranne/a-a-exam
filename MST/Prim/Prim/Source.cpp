#include "pr_queue.h"
#include "Graph.h"
#include <fstream>

struct edge {
	int x, y, w;
	edge(int x = 0, int y = -1, int w = INT_MAX): x(x), y(y), w(w) {}
	bool operator<(const edge& e) {
		return (w < e.w );
	}
	edge(const edge& e) {
		x = e.x; 
		y = e.y;
		w = e.w;
	}
	edge& operator=(const edge& e) {
		if (this != &e)
		{
			x = e.x;
			y = e.y;
			w = e.w;
		}
		return *this;
	}
	friend std::ostream& operator<<(std::ostream& out, const edge& e) {
		out << char(e.x + 'a') << '(' << char(e.y + 'a') << ", " << e.w << ')';
		return out;
	}
};


Graph Prim(const Graph& g)
{
	int n = g.get_nV();
	Graph tree(n);
	pr_queue<edge, int> pq;

	for (int i = 1; i < n; ++i)
	{
		int w = g.get_edge(i, 0);
		if (w)
			pq.push(edge(i, 0, w), w);
		else
			pq.push(edge(i), INT_MAX);
	}

	edge tmp; int iw;
	while (!pq.empty())
	{
		pq.view();
		tmp = *pq.pop();
		tree.add_edge(tmp.x, tmp.y, tmp.w);
		int size = pq.h.get_size();
		for (int i = 0; i < size; ++i)
		{
			iw = g.get_edge(tmp.x, pq.h.arr[i].info.x);
			if (iw && (pq.h.arr[i].info.y == -1 || iw < pq.h.arr[i].info.w)) {
				pq.h.arr[i].info.y = tmp.x;
				pq.h.arr[i].info.w = iw;
				pq.h.decrease_key(i, iw);
			}
		}
	}
	return tree;
}





int main()
{
	

	std::ifstream in("input.txt");
	Graph g;
	in >> g;
	std::cout << g;
	Graph MST(Prim(g));
	std::cout << '\n' << MST;

	std::cin.get();
}


/*
	heap<int, int> h;
	h.insert_h(3, 3);
	h.insert_h(2, 2);
	std::cout << "\nview\n";  h.view_h();
	std::cout << "\ndelete: " << *h.remove_h();
	h.insert_h(15, 15);
	h.insert_h(5, 5);
	h.insert_h(4, 4);
	h.insert_h(45, 45);
	std::cout << "\nview\n";  h.view_h();
	std::cout << "\ndelete: " << *h.remove_h() << '\n';
	std::cout << "\nview\n";  h.view_h();
	h.decrease_key(2, -1);
	std::cout << "\nview after decrease\n";  h.view_h();
	//std::cout << h.first_h() << '\n';+
	//h.increase_key(2, 100);
	std::cout << "\nview after increase\n";  h.view_h();
	std::cout << "\ndelete: " << *h.remove_h() << '\n';
	std::cout << "\nview\n";  h.view_h();


	pr_queue<int, int> pq;
	pq.push(2, 2); pq.push(45, 45);
	pq.push(15, 15);
	pq.push(5, 5);
	pq.push(4, 4);
	pq.push(45, 45);
	pq.view();
	std::cout << "\n popped = " << *pq.pop() << '\n';
	pq.view();
	std::cout << "\n popped = " << *pq.pop() << '\n';
	pq.view();
	pq.h.decrease_key(2, 0);
	std::cout << "\n popped = " << *pq.pop() << '\n';
	pq.view();
*/