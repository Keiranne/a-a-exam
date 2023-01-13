#pragma once
#include <iostream>

const int MAX = 100;



template <class TInfo, class KInfo>
class  heap{
public:
	struct NODE {
		TInfo info;
		KInfo key;
		NODE() {}
		NODE(TInfo info, KInfo key) : info(info), key(key) {}
		NODE(const NODE& N) {
			info = N.info;
			key = N.key;
		}
		NODE& operator=(const NODE& N) {
			if (this != &N) {
				info = N.info;
				key = N.key;
			}
			return *this;
		}
		bool operator<(const NODE& N) {
			return key < N.key;
		}
	};
	NODE arr[MAX];
private:
	int size;

	void balance(int i = 0)	{
		int  curr_i = i, i_lson = 2 * curr_i, i_rson = 2 * curr_i + 1;
		while (i_lson < size && (arr[(arr[i_lson] < arr[i_rson] ? i_lson : i_rson)]) < arr[curr_i])
		{
			if (arr[i_lson] < arr[i_rson])
			{
				std::swap(arr[curr_i], arr[i_lson]);
				curr_i = i_lson;
			}
			else
			{
				std::swap(arr[curr_i], arr[i_rson]);
				curr_i = i_rson;
			}
			i_lson = 2 * curr_i;
			i_rson = 2 * curr_i + 1;
		}
	}

	void go_up(int icurr) {
		int i = icurr, iparent = (i) / 2;
		while (iparent >= 0 && arr[i] < arr[iparent] && i != iparent)
		{
			std::swap(arr[i], arr[iparent]);
			i = iparent;
			iparent = (i) / 2;
		}
	}

public:
	heap() {
		size = 0; 
	}

	void clear() {
		size = 0;
	}
	bool empty_h()  const {
		return size == 0;
	}
	bool full_h()  const {
		return size == MAX - 1;
	}
	TInfo first_h()  const {
		return arr[0].info;
	}

	void insert_h(TInfo _info, KInfo _key) {
			int i = size;
			arr[i] = NODE(_info, _key);
			go_up(i);
			++size;
	}

	TInfo* remove_h(){
		TInfo* tmp = nullptr;
		if (!empty_h()) {
			tmp = new TInfo(arr[0].info);
			arr[0] = arr[--size];
			balance();
		}
		return tmp;
	}

	void decrease_key(int i, KInfo new_key) {
		if (arr[i].key > new_key) {
			arr[i].key = new_key;
			go_up(i);
		}
	}

	int get_size() {
		return size;
	}
	
	void view_h(std::ostream& out = std::cout)  const {
		out << '\n';
		for (int i = 0; i < size; ++i)
			out << arr[i].info << ' ';
		out << '\n';
	}

};