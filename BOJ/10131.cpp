#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
vector<int> adj[500001];
ll c[500001], a[500001], b[500001];

void dfs(int v, int p) {
	a[v] = 0;
	vector<pair<ll, ll>> arr;
	for (auto u: adj[v]) if (u != p) {
		dfs(u, v);
		a[v] += a[u] + 2;
		arr.push_back({a[u] + 2, b[u] + 1});
	}
	if (v == 1) b[v] = a[v] + c[v];
	else b[v] = c[v];
	sort(arr.begin(), arr.end(), [](const pair<ll, ll>& a, const pair<ll, ll>& b) {
		return max(a.second, a.first + b.second) < max(b.second, a.second + b.first);
	});
	ll sma = 0;
	for (auto& i: arr) {
		b[v] = max(b[v], sma + i.second);
		sma += i.first;
	}
	return;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> c[i];
	for (int i = 0; i < n - 1; ++i) {
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs(1, 0);
	cout << b[1];
}