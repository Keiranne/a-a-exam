#pragma once
#include <iostream>
#include <sstream>
#include <string>

class permutation {
	struct elem {//direction: {-1, 1} - {left, right}
		int info, dir;
		elem(int info = 0, int dir = 0) : info(info), dir(dir) {}
		elem(const elem& e) {
			info = e.info;
			dir = e.dir;
		}
		elem& operator=(const elem& e) {
			if (this != &e) {
				info = e.info;
				dir = e.dir;
			}
			return *this;
		}
		void re_direct() {
			dir *= -1;
		}
		bool operator<(const elem& e) {
			return info < e.info;
		}
		bool operator>(const elem& e) {
			return info > e.info;
		}
	};

	elem* P;
	int n;
public:
	permutation(int n) : n(n) {
		P = new elem[n];//изначально перестановка имеет вид 0,1,2,..,(n-1) и все стрелочки смотрят влево
		for (int i = 1; i < n; ++i)
			P[i] = elem(i, -1);
	}
	~permutation();
	std::string to_str();
	bool is_mobile(int i); 
	int imax();
	void renovate(int k);
	void exchange(int& i);
};