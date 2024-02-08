#include <bits/stdc++.h>
using namespace std;

int N, p[100001];
vector<int> tree[100001];

void dfs(int v, int b) {
	for (int i: tree[v]) if (i != b) {
		p[i] = v;
		dfs(i, v);
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N; int a, b;
	for (int i = 0; i < N - 1; ++i) {
		cin >> a >> b;
		tree[a].push_back(b); tree[b].push_back(a);
	}
	dfs(1, 0);
	for (int i = 2; i <= N; ++i) cout << p[i] << "\n";
}