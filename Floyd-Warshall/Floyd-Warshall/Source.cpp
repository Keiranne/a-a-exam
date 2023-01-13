#include <iostream>
#include <fstream>

template <class T>
void alloc_memory(T** &arr, int size) {
	arr = new T*[size];
	for (int i = 0; i < size; ++i)
		arr[i] = new T[size];
}
template <class T>
void free_memory(T**& arr, int size) {
	for (int i = 0; i < size; ++i)
		delete[] arr[i];
	delete[] arr;
}
template <class T>
void print_matrix(const char* mess, T** arr, int size, std::ostream& out = std::cout) {
	out << '\n' << mess << '\n';
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
			out << arr[i][j] << ' ';
		out << '\n';
	}
}
template <class T>
void fill_matrix(T** arr, int size, std::istream& in = std::cin) {
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			in >> arr[i][j];
}
template <class T>
void copy_matrix(T** arr, int n, T** brr) {
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			brr[i][j] = arr[i][j];
}

bool** Warshall(int** arr, int n);
int** Floyd(int** gr, int n);

int main() {

	std::ifstream file("input.txt");
	int size; file >> size;
	int** matr_adj; alloc_memory(matr_adj, size);
	fill_matrix(matr_adj, size, file);
	print_matrix("matrix:", matr_adj, size);
	int** shrt_paths = Floyd(matr_adj, size);
	print_matrix("shortest path:", shrt_paths, size);

	bool** trans_cls = Warshall(matr_adj, size);
	print_matrix("transitive closure:", trans_cls, size);


	std::cin.get();
}

bool** Warshall(int** arr, int n){//transitive closure
	bool** res; alloc_memory(res, n);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			res[i][j] = bool(arr[i][j]);

	for (int k = 0; k < n; ++k)
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				res[i][j] |= res[i][k] && res[k][j];
	return res;
}

int** Floyd(int ** gr, int n){//shortest path
	int** res; alloc_memory(res, n);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (!gr[i][j] && i != j)
				res[i][j] = 104803846;
			else
				res[i][j] = gr[i][j];

	for (int k = 0; k < n; ++k)
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				if (res[i][j] > (res[i][k] + res[k][j]))
					res[i][j] = res[i][k] + res[k][j];

	return res;
}