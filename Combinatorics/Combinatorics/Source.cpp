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
template <class T>
void swp(T &a, T &b)
{
	T tmp = b;
	b = a;
	a = tmp;
}
void copy(Tinfo * beg, Tinfo * end, Tinfo * dest);

int* get_next_p(int* arr, int size);
int* get_next_c(int* arr, int n, int k);

int TSP(int** adj_matrix, int n) {
	int *hmt_path = new int[n];

	auto get_pweight = [adj_matrix, &hmt_path, n]() {
		int w = adj_matrix[hmt_path[0]][hmt_path[n - 1]];
		for(int i = 0; i < n-1;++i)
			w += adj_matrix[hmt_path[i]][hmt_path[i+1]];
		return w;
	};

	for (int i = 0; i < n; ++i)
		hmt_path[i] = i;
	int min_w = get_pweight(), curr_w = 0;

	while (get_next_p(hmt_path, n))
	{
		curr_w = get_pweight();
		if (curr_w < min_w)
			min_w = curr_w;
	}
	return min_w;
}

void to_subset(Tinfo* arr, int n, bool*B);

void gener_gray(Tinfo* arr, int n);
void gener_squashed(Tinfo* arr, int n);
void JohnsonTrotter(int n, std::ostream& out = std::cout);



int main(){
	//int n, k;
	//std::cin  >> k >> n;
	//std::cout << "\nC = " << Binomial(n, k);

	//int n;
	//std::cin >> n;
	//JohnsonTrotter(n);

	//int n;
	//std::cin >> n;
	//Tinfo * arr = new Tinfo[n];
	//for (int i = 0; i < n; ++i)
	//	std::cin >> arr[i];
	//gener_gray(arr, n);
	//std::cout << '\n';
	//gener_squashed(arr, n);
	//delete[] arr;

	int n = 4;
	int **arr = new int*[n];
	for (int i = 0; i < n; ++i)
		arr[i] = new int[n];
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			std::cin >> arr[i][j];
	std::cout << TSP(arr, n);
	for (int i = 0; i < n; ++i)
		delete[] arr[i];
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

int * get_next_p(int * arr, int size) {//_no_rep in lexicographical order
	int i = size - 1;
	while (i && arr[i] < arr[i - 1])
		--i;
	--i;
	if (i >= 0) {// i == -1 -> no more permutations, arr sorted in descending order 
		int j = size - 1;
		while (j && arr[j] < arr[i])
			--j;
		swp(arr[i], arr[j]);
		++i;
		j = size - 1;
		while (i < j)
		{
			swp(arr[i], arr[j]);
			++i; --j;
		}
	}
	else
	{
		delete[] arr;
		arr = nullptr;
	}
	return arr;
}


int * get_next_c(int * arr, int n, int k) {//_no_rep in lexicographical order
	int i = k - 1;
	while (arr[i] == n - k + 1 + i)
		--i;
	if (i < 0)
	{
		delete[] arr;
		arr = nullptr;
	}
	else {
		++arr[i];
		for (int j = i + 1; j < k; ++j)
			arr[j] = 1 + arr[j - 1];
	}
	return arr;
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



/*
// generate & print all c(k,n) in main:
std::cout << "\n n = ";
int n; std::cin >> n;
std::cout << "\n k = ";
int k; std::cin >> k;
int* arr = new int[n];
std::cout << "\n Array:\n";
for (int i = 0; i < n; ++i)
	std::cin >> arr[i];
int i = 0;
do
{
	std::cout << '\n' << ++i << ": ";
	print(arr, k);
} while (get_next_c(arr, n, k));
*/

/*
// generate & print all p(n) in main:
std::cout << "\n n = ";
int n; std::cin >> n;
int* arr = new int[n];
std::cout << "\n Array:\n";
for (int i = 0; i < n; ++i)
	std::cin >> arr[i];
int i = 0;
do
{
	std::cout << '\n' << ++i << ": ";
	print(arr, n);
}
while (get_next_p(arr, n));
*/
