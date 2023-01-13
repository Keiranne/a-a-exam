#include <iostream>
#include "permutation.h"
#include <Windows.h>
using Tinfo = int;

int Binomial(int n, int k);

int power_set(int n);
template <class T>
void print(T* arr, int n, std::ostream & out = std::cout) {
	for (int i = 0; i < n; ++i)
		out << arr[i] << ' ';
}

void copy(Tinfo * beg, Tinfo * end, Tinfo * dest);

void to_subset(Tinfo* arr, int n, bool*B);

void gener_gray(Tinfo* arr, int n);
void gener_squashed(Tinfo* arr, int n);
void JohnsonTrotter(int n, std::ostream& out = std::cout);


int main(){
	//int n, k;
	//std::cin  >> k >> n;
	//std::cout << "\nC = " << Binomial(n, k);

	//JohnsonTrotter(4);
	//std::cout << '\n' << clock() << " ms";

	int n;
	std::cin >> n;
	Tinfo * arr = new Tinfo[n];
	for (int i = 0; i < n; ++i)
		std::cin >> arr[i];

	gener_gray(arr, n);
	std::cout << '\n';
	gener_squashed(arr, n);

	delete[] arr;
	std::cin.get();
	std::cin.get();
}




int Binomial(int n, int k)
{
	int* C = new int[k + 1]{ 1 };
	for (int i = 1; i < n + 1; ++i)
	{
		for (int j = (i < k ? i : k); j > 0; --j)
			C[j] += C[j - 1];
		//	print(C, (i < k+1 ? i : k+1));
	}
	int tmp = C[k];
	delete[] C;
	return tmp;
}

int power_set(int n) {
	int i = 1;
	while (n--)
		i *= 2;
	return i;
}

void copy(Tinfo * beg, Tinfo * end, Tinfo * dest) {
	while (beg != end)
		*dest++ = *beg++;
}

void to_subset(Tinfo * arr, int n, bool * B) {
	for (int i = n - 1; i >= 0; --i)
		if (B[i])
			std::cout << arr[n - i - 1] << ' ';
}

void gener_gray(Tinfo * arr, int n) {
	bool *B = new bool[n] {},
		*N = new bool[n] {};

	auto next = [&B, &N, n]() {
		int i = n;
		do {
			--i;
			B[i] ^= 1;
		} while (!B[i] && i > 0);
		N[i] ^= 1;
	};
	int count = power_set(n);
	for (int i = 0; i < count; ++i)
	{
		std::cout << '\n';
	//	print(B, n);		std::cout << " | ";
	//	print(N, n);		std::cout << " | ";
		to_subset(arr, n, N);
		std::cout << '\n';
		next();
	}

	delete[] B;
	delete[] N;
}

void gener_squashed(Tinfo * arr, int n) {
	bool *B = new bool[n] {};
	auto next = [&B, n]() {
		int i = n;
		do {
			--i;
			B[i] = B[i] ^ 1;
		} while (i > 0 && !B[i]);
	};

	int count = power_set(n);
	for (int i = 0; i < count; ++i)
	{
		std::cout << '\n';
		//print(B, n); 		std::cout << " | "; 
		to_subset(arr, n, B);
		std::cout << '\n';
		next();
	}
	delete[] B;
}

void JohnsonTrotter(int n, std::ostream & out) {
	permutation P(n);
	int k = n - 1, i = 0;
	do
	{
		out << P.to_str() << " -> " << i + 1 << '\n';
		P.exchange(k);
		P.renovate(k);
		k = P.imax();
		++i;
	} while (k >= 0);
	out << P.to_str() << " -> " << i + 1 << '\n';
}

