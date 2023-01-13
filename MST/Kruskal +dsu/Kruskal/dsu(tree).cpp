#include "dsu(tree).h"

void DSU::link(int less, int more)
{
	subsets[less].parent = more;
	if (subsets[less].rank == subsets[more].rank)
		++subsets[more].rank;
}

DSU::~DSU(){
	delete[] subsets;
}

int DSU::Find(int i) {//сжатие пути
	if (subsets[i].parent != i)
		subsets[i].parent = Find(subsets[i].parent);
	return subsets[i].parent;
}

void DSU::Union(int x, int y) {//объединение по рангу
	int pX = Find(x), pY = Find(y);
	if (pX != pY)
		subsets[pX].rank < subsets[pY].rank ? link(pX, pY) : link(pY, pX);
}

void DSU::print(){
	std::cout << "\nelem(rank) -> parent\n";
	for (int i = 0; i < n; ++i)
		std::cout << subsets[i].i << '(' << subsets[i].rank << ')'
			<< " -> " << subsets[i].parent << '\n';
	std::cout << '\n';
}
