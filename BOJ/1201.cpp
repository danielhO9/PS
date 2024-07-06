#include <bits/stdc++.h>
using namespace std;

void solve() {
	int N, M, K; cin >> N >> M >> K;
	vector<int> ans;
	int last = N;
	if (N < M + K - 1 || M * K < N) {
		cout << -1;
		return;
	}
	for (int i = last - M + 1; i <= last; ++i) ans.push_back(i);
	last -= M;
	for (int i = 2; i <= K; ++i) {
		int tmp = min(last - (K - i), M);
		for (int j = last - tmp + 1; j <= last; ++j) ans.push_back(j);
		last -= tmp;
	}
	for (auto i: ans) cout << i << ' ';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}