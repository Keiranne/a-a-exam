#include "permutation.h"

permutation::~permutation()
{
	delete[] P;
}

std::string permutation::to_str() {
	std::stringstream ss;
	for (int i = 0; i < n; ++i)
		ss << P[i].info + 1 << ' ';
	return ss.str();
}

bool permutation::is_mobile(int i) {//элемент называется мобильным, если стрелка указывает на меньшее число
	int next = i + P[i].dir;
	return next >= 0 && next < n && P[i] > P[next];
}

int permutation::imax() {//возврат -1 означает, что мобильных элементов больше нет, - алгоритм заканчивает работу
	int i_max = -1, i = 0;
	while (i_max == -1 && i < n)
		if (is_mobile(i))
			i_max = i;
		else
			++i;
	while (i < n) {
		if (P[i] > P[i_max] && is_mobile(i))
			i_max = i;
		++i;
	}
	return i_max;
}

void permutation::renovate(int k) {
	for (int i = 0; i < n; ++i) {
		if (P[k] < P[i])
			P[i].re_direct();
	}
}

void permutation::exchange(int& i) {//обмен элемента со следующим в направлении стрелочки
	int inext = i + P[i].dir;
	elem tmp = P[inext];
	P[inext] = P[i];
	P[i] = tmp;
	i = inext;
}
