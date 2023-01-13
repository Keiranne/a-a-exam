#include <iostream>
#include <functional>
#include <Windows.h>
using Tinfo = int;

void print(const char* mes, const Tinfo* arr, int n, std::ostream& out = std::cout);
void fill_random(Tinfo* arr, int size);
void copy(Tinfo* beg, Tinfo* end, Tinfo* dest);

void SelectionSort(Tinfo* arr, int n, std::function<bool(Tinfo a, Tinfo b)> cmp = [](Tinfo a, Tinfo b) {return a < b; });
void BubbleSort(Tinfo* arr, int n, std::function<bool(Tinfo a, Tinfo b)> cmp = [](Tinfo a, Tinfo b) {return a < b; });
void InsertionSort(Tinfo* arr, int n, std::function<bool(Tinfo a, Tinfo b)> cmp = [](Tinfo a, Tinfo b) {return a < b; });

void Merge(Tinfo *B, int p, Tinfo* C, int q, Tinfo* A, int n);
void MergeSort(Tinfo *A, int n);

int partition(Tinfo* arr, int l, int r, Tinfo p);
int partition(Tinfo* A, int l, int r);
void QuickSort(Tinfo *A, int l, int r);

int BinarySearch(const Tinfo*A, int n, Tinfo key); // iterative
int BinarySearch(const Tinfo*A, int l, int r, Tinfo key); // r

int selection_problem(Tinfo * arr, int n, int k);

int main() {
	int n; std::cout << "n = ";
	std::cin >> n;	Tinfo*arr = new Tinfo[n];
	fill_random(arr, n);
	print("not sorted array:", arr, n);

	int k;
	std::cout << "\n 1 <= k <= " << n << ": ";
	std::cin >> k;
	std::cout << arr[selection_problem(arr, n, k - 1)];

	QuickSort(arr, 0, n - 1);
	print("QuickSort in ascending order:", arr, n);

	BubbleSort(arr, n, [](Tinfo a, Tinfo b) { return a > b; });
	print("BubbleSort in descending order:", arr, n);

	//fill_random(arr, n);
	MergeSort(arr, n);			
	print("MergeSort in ascending order:", arr, n);

	SelectionSort(arr, n, [](Tinfo a, Tinfo b) { return a > b; });
	print("SelectionSort in descending order:", arr, n);

	//fill_random(arr, n);
	InsertionSort(arr, n);
	print("InsertionSort in ascending order:", arr, n);

	std::cout << "\nkey = ";
	std::cin >> k;
	std::cout << "index: " << BinarySearch(arr, n, k) << " vs " << BinarySearch(arr, 0, n - 1, k);

	std::cin.ignore(); std::cin.get();
	delete[] arr;
}



void print(const char* mes, const Tinfo* arr, int n, std::ostream & out){
	out << '\n' << mes << '\n';
	for (int i = 0; i < n; ++i)
		out << arr[i] << ' ';
	out << '\n';
}

void fill_random(Tinfo*arr, int size){
	srand(GetTickCount());
	for (int i = 0; i < size; ++i)
		arr[i] = rand() % 74 - rand() % 97;
}

void copy(Tinfo * beg, Tinfo * end, Tinfo * dest){
	while (beg != end)
		*dest++ = *beg++;
}

void SelectionSort(Tinfo *arr, int n, std::function<bool(Tinfo a, Tinfo b)> cmp){
	int i_extrm;
	for (int i = 0; i < n - 1; ++i)
	{
		i_extrm = i;
		for (int j = i + 1; j < n; ++j)
			if (cmp(arr[j], arr[i_extrm]))
				i_extrm = j;
		std::swap(arr[i], arr[i_extrm]);
	}
}

void BubbleSort(Tinfo *arr, int n, std::function<bool(Tinfo a, Tinfo b)> cmp){
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = 0; j < n - i - 1; ++j)
			if (cmp(arr[1 + j], arr[j]))
				std::swap(arr[1 + j], arr[j]);
	}
}

void Merge(Tinfo * B, int p, Tinfo * C, int q, Tinfo * A, int n){
	int i = 0, j = 0, k = 0;
	while (i < p && j < q)
	{
		if (B[i] < C[j])
			A[k] = B[i++];
		else
			A[k] = C[j++];
		++k;
	}
	if (i < p)
		copy(B + i, B + p, A + k);
	else
		copy(C + j, C + q, A + k);
}

void MergeSort(Tinfo * A, int n){
	if (n > 1)
	{
		int lim = n / 2;
		Tinfo *B = new Tinfo[lim], *C = new Tinfo[n % 2 + lim];
		copy(A, A + lim, B);
		copy(A + lim, A + n, C);
		MergeSort(B, lim);
		MergeSort(C, n % 2 + lim);
		Merge(B, lim, C, n % 2 + lim, A, n);
	}
}

int partition(Tinfo * arr, int l, int r, Tinfo p){ //pivot - p
	int i = l - 1, j = r + 1;
	do
	{
		do ++i;
		while (arr[i] < p && i <= r);
		do --j;
		while (arr[j] > p && j >= l);
		std::swap(arr[i], arr[j]);
	} while (i < j);
	std::swap(arr[i], arr[j]);
	return j;
}

int partition(Tinfo * A, int l, int r){ //pivot - the leftest
	Tinfo p = A[l];
	int i = l, j = r + 1;
	do
	{
		do ++i;
		while (i <= r && A[i] < p);
		do --j;
		while (j >= l && A[j] > p);
		std::swap(A[i], A[j]);
	} while (i <= j);
	std::swap(A[i], A[j]);
	std::swap(A[l], A[j]);
	return j;
}

void QuickSort(Tinfo * A, int l, int r){
	if (l < r)
	{
		int s = partition(A, l, r);
		QuickSort(A, l, s - 1);
		QuickSort(A, s + 1, r);
	}
}

void InsertionSort(Tinfo *arr, int n, std::function<bool(Tinfo a, Tinfo b)> cmp){
	for (int i = 1; i < n; ++i)
	{
		Tinfo tmp = arr[i], j = i - 1;
		while (j >= 0 && cmp(tmp, arr[j]))
		{
			arr[j + 1] = arr[j];
			--j;
		}
		arr[j + 1] = tmp;
	}
}


int BinarySearch(const Tinfo * A, int n, Tinfo key){
	int l = 0, r = n - 1, m = (l + r) / 2;
	while (l <= r && A[m] != key)
	{
		m = (l + r) / 2;
		if (key < A[m])
			r = m - 1;
		else if (key > A[m])
			l = m + 1;
	}
	return A[m] == key ? m : -1;
}

int BinarySearch(const Tinfo * A, int l, int r, const Tinfo key){
	int ires = -1;
	if (l <= r)
	{
		int m = (l + r) / 2;
		if (key == A[m])
			ires = m;
		else if (key > A[m])
			ires = BinarySearch(A, m + 1, r, key);
		else
			ires = BinarySearch(A, l, m - 1, key);
	}
	return ires;
}

int selection_problem(Tinfo * arr, int n, int k){
	int  l = 0, r = n - 1, j;
	do
	{
		j = partition(arr, l, r);
		if (j > k)
			r = j - 1;
		else if (j < k)
			l = j + 1;
	} while (j != k);
	return j;
}
