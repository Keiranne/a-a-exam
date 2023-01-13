#pragma once
#include "binary_heap.h"


template <class S, class K>
class pr_queue {
public:
	heap<S, K> h;

//public:
	pr_queue() {}
	S top()  const {
		return h.first_h().info;
	}

	S* pop() {
		return h.remove_h();
	}

	bool push(S elem, K key) {
		bool res = !h.full_h();
		if (res)
			h.insert_h(elem, key);
		return res;
	}

	bool empty() const {
		return h.empty_h();
	}

	void view(std::ostream& out = std::cout)  const {
		out << "\npr queue:";
		if (empty())
			out << "is empty\n";
		else
			h.view_h(out);
	}


};