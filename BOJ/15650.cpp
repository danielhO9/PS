#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<int> Q;

void solution() {
	if (Q.size() == M) {
		for (auto i: Q) cout << i << " ";
		cout << "\n";
		return;
	}
	int l = Q.back();
	if (l > N) return;
	for (int i = l + 1; i <= N; ++i) {
		Q.push_back(i);
		solution();
		Q.pop_back();
	}
}

int main() {
	cin >> N >> M;
	for (int i = 1; i <= N; ++i) {
		Q.push_back(i);
		solution();
		Q.pop_back();
	}
}