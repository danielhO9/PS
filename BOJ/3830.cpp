#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int N, M;
int parent[100001];
LL dif[100001];

int find(int v) {
	if (parent[v] == v) return v;
	int pv = find(parent[v]);
	dif[v] += dif[parent[v]];
	parent[v] = pv;
	return parent[v];
}

void uni(int a, int b, LL w) {
	int pa = find(a); int pb = find(b);
	if (pa != pb) dif[pb] = dif[a] + w - dif[b];
	parent[pb] = pa;
}

void solve() {
	for (int i = 1; i <= N; ++i) parent[i] = i;
	for (int i = 1; i <= N; ++i) dif[i] = 0LL;
	char c; int a, b; LL w;
	for (int i = 0; i < M; ++i) {
		cin >> c;
		if (c == '!') {
			cin >> a >> b >> w;
			uni(a, b, w);
		} else {
			cin >> a >> b;
			if (find(a) != find(b)) cout << "UNKNOWN" << '\n';
			else cout << dif[b] - dif[a] << '\n';
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	while (cin >> N >> M) solve();
}