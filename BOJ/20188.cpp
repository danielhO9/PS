#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL N, ans;
vector<int> graph[300001];
vector<LL> sz(300001);

LL getSz(int v, int p) {
	sz[v] = 1;
	for (auto i: graph[v]) if (i != p) sz[v] += getSz(i, v);
	return sz[v];
}


int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N;
	int a, b;
	for (int i = 0; i < N - 1; ++i) {
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	getSz(1, 0);
	for (int i = 2; i <= N; ++i) {
		ans += N * (N - 1) / 2 - (N - sz[i]) * (N - sz[i] - 1) / 2;
	}
	cout << ans;
}