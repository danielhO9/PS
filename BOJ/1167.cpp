#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

vector<pair<int, LL>> tree[100001];
int V, maxV;
LL maxD = LLONG_MIN;

void dfs(int v, LL d, int p) {
	if (maxD < d) {
		maxD = d; maxV = v;
	}
	for (auto [i, j]: tree[v]) if (i != p) dfs(i, d + j, v);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> V; int a, b; LL l;
	for (int i = 0; i < V; ++i) {
		cin >> a;
		while (1) {
			cin >> b;
			if (b == -1) break;
			cin >> l;
			tree[a].push_back({b, l});
		}
	}
	dfs(1, 0, 0); maxD = LLONG_MIN; dfs(maxV, 0, 0);
	cout << maxD;
}