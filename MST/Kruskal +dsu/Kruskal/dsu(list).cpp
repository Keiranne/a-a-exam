#include "dsu(list).h"

void DSU::make_set(int i)
{
	represents[i] = i;
	subset[i].rank = 1;
	subset[i].tail = subset[i].head = new node(i);
}

void DSU::reparent(int x, int new_prnt) {
	node* p = subset[x].head;
	while (p)
	{
		represents[p->info] = new_prnt;
		p = p->next;
	}
}

void DSU::link(int less, int more)
{
	reparent(less, more);
	subset[more].rank += subset[less].rank;
	subset[more].tail->next = subset[less].head;
	subset[more].tail = subset[less].tail;
	/*subset[less].~listnode();*/
	subset[less].rank = 0;
	subset[less].head = subset[less].tail = nullptr;
}

DSU::~DSU()
{
	delete[] represents;
	delete[] subset;
}

int DSU::Find(int x)
{
	return represents[x];
}

void DSU::Union(int x, int y)
{
	int rX = Find(x), rY = Find(y);
	if (rX != rY)
		subset[rX].rank < subset[rY].rank ? link(rX, rY) : link(rY, rX);
}

void DSU::print()
{
	for (int i = 0; i < size; ++i) {
		std::cout << '\n' << i << ":  ";
		if (subset[i].rank)
		{
			node* p = subset[i].head;
			while (p)
			{
				std::cout << p->info << ' ';
				p = p->next;
			}
		}
	}
	std::cout << '\n';
}

void DSU::print_represents()
{
	for (int i = 0; i < size; ++i)
		std::cout << '\n' << i << " : " << represents[i];
	std::cout << '\n'; 
}
