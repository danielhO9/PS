#include <bits/stdc++.h>
using namespace std;

int N, M;
set<int> arr;
vector<int> Q;

void solution(int l) {
	if (Q.size() == M) {
		for (auto i: Q) cout << i << " ";
		cout << "\n";
		return;
	}
	for (int i: arr) {
		if (i >= l) {
			Q.push_back(i);
			solution(i);
			Q.pop_back();
		}
	}
}

int main() {
	cin >> N >> M; int t;
	for (int i = 0; i < N; ++i) {
		cin >> t;
		arr.insert(t);
	}
	for (int i: arr) {
		Q.push_back(i);
		solution(i);
		Q.pop_back();
	}
}