#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
vector<int> adj[1000001];
int lv[1000001];

void dfs(int v, int p) {
	priority_queue<int> pq;
	int mx = -1;
	for (auto u: adj[v]) if (u != p) {
		dfs(u, v);
		pq.push(-lv[u]);
		mx = max(mx, lv[u]);
	}
	bool rem = false;
	while (pq.size() >= 2) {
		int cur = -pq.top(); pq.pop();
		if (cur == -pq.top()) {
			pq.pop();
			pq.push(-cur - 1);
		} else {
			rem = true;
		}
	}
	if (pq.empty()) lv[v] = mx + 1;
	else {
		if (rem) lv[v] = max(mx + 1, -pq.top() + 1);
		else lv[v] = max(mx + 1, -pq.top());
	}
	
}

void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) adj[i].clear();
	for (int i = 2; i <= n; ++i) {
		int p; cin >> p;
		adj[i].push_back(p);
		adj[p].push_back(i);
	}
	dfs(1, 0);
	// for (int i = 1; i <= n; ++i) cout << lv[i] << ' ';
	cout << lv[1] << '\n';
	// cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}