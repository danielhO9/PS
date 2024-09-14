#include <bits/stdc++.h>
using namespace std;

int N;
int G[9][9];
int H[9][9];
int A[9][9];
vector<int> m;
bool used[9];
int ans = INT32_MAX;

void calc() {
	int cnt = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			int a = m[i], b = m[j];
			if (a < b && G[i + 1][j + 1] + H[min(a, b)][max(a, b)] == 1) {
				cnt += A[min(a, b)][max(a, b)];
			}
		}
	}
	ans = min(ans, cnt);
}

void dfs() {
	if (m.size() == N) {
		calc();
		return;
	}
	for (int i = 1; i <= N; ++i) if (!used[i]) {
		used[i] = true;
		m.push_back(i);
		dfs();
		used[i] = false;
		m.pop_back();
	}
}

void solve() {
	cin >> N;
	int M; cin >> M;
	while (M--) {
		int u, v; cin >> u >> v;
		G[u][v] = 1;
		G[v][u] = 1;
	}
	cin >> M;
	while (M--) {
		int u, v; cin >> u >> v;
		H[u][v] = 1;
		H[v][u] = 1;
	}
	for (int i = 1; i <= N - 1; ++i) {
		for (int j = i + 1; j <= N; ++j) {
			cin >> A[i][j];
		}
	}
	for (int i = 1; i <= N; ++i) {
		used[i] = true; m.push_back(i);
		dfs();
		used[i] = false;
		m.pop_back();
	}
	cout << ans;
}


int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}