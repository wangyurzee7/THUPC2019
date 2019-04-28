#include <stdio.h>
#include <vector>
#include <queue>

bool A(int op, int x) {
	static std::queue<int> q;
	
	if (op == 1) {
		q.push(x);
		return true;
	} else {
		if (q.empty()) return false;
		if (q.front() != x) return false;
		q.pop();
		return true;
	}
}

bool B(int op, int x) {
	static std::vector<int> s;
	
	if (op == 1) {
		s.push_back(x);
		return true;
	} else if (op == 2) {
		if (s.size() == 0) return false;
		if (s.back() != x) return false;
		s.pop_back();
		return true;
	}
}

bool C(int op, int x) {
	static std::priority_queue<int> q;
	
	if (op == 1) {
		q.push(x);
		return true;
	} else {
		if (q.empty()) return false;
		if (q.top() != x) return false;
		q.pop();
		return true;
	}
}

bool D(int op, int x) {
	static std::priority_queue<int, std::vector<int>, std::greater<int> > q;
	
	if (op == 1) {
		q.push(x);
		return true;
	} else {
		if (q.empty()) return false;
		if (q.top() != x) return false;
		q.pop();
		return true;
	}
}

int main() {
	int n;
	scanf("%d", &n);
	bool ans[4] = {true, true, true, true};
	bool (*f[4])(int, int) = {A, B, C, D};
	
	for (int i = 1; i <= n; i++) {
		int op, x;
		scanf("%d%d", &op, &x);
		for (int j = 0; j < 4; j++) {
			ans[j] = ans[j] && f[j](op, x);
		}
	}
	
	for (int i = 0; i < 4; i++) {
		puts(ans[i] ? "Yes" : "No");
	}
}
