#include <bits/stdc++.h>
using namespace std;

int N;
set<int> S;

void solve() {
	cin >> N;
	for (int i = 0; i < N - 1; ++i) {
		int u, v; cin >> u >> v;
		S.insert(u * N + u + v);
		S.insert(v * N + v + u);
	}
	vector<int> V(N);
	for (int i = 0; i < N; ++i) cin >> V[i];
	if (V[0] != 1) {
		cout << 0; return;
	}
	stack<int> Q; Q.push(1);
	for (int i = 1; i < N; ++i) {
		while (!Q.empty() && S.find(V[i] * (N + 1) + Q.top()) == S.end()) Q.pop();
		if (Q.empty()) {
			cout << 0; return;
		}
		Q.push(V[i]);
	}
	cout << 1;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}