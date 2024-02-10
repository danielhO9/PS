#include <bits/stdc++.h>
using namespace std;

int find(vector<int>& parents, int x) {
	if (parents[x] == x) return x;
	parents[x] = find(parents, parents[x]);
	return parents[x];
}

void minUnion(vector<int>& parents, int x, int y) {
	x = find(parents, x); y = find(parents, y);
	int minn = min(x, y);
	parents[x] = minn; parents[y] = minn;
}

void maxUnion(vector<int>& parents, int x, int y) {
	x = find(parents, x); y = find(parents, y);
	int maxn = max(x, y);
	parents[x] = maxn; parents[y] = maxn;
}

void solve() {
	int n; cin >> n;
	vector<int> V(n); for (int i = 0; i < n; ++i) cin >> V[i];
	vector<int> minParent(n), maxParent(n);
	for (int i = 0; i < n; ++i) {
		minParent[i] = i;
		maxParent[i] = i;
	}
	priority_queue<pair<int, int>> Q;
	for (int i = 0; i < n - 1; ++i) {
		if (abs(V[i] - V[i + 1]) == 1) Q.push({V[i] + V[i + 1], i});
	}
	while (!Q.empty()) {
		auto now = Q.top(); Q.pop();
		int l = find(minParent, now.second), r = find(minParent, now.second + 1);
		if ((l == r) || (V[l] + V[r] != now.first) || abs(V[l] - V[r]) != 1) continue;
		V[l] = min(V[l], V[r]);
		minUnion(minParent, l, r); maxUnion(maxParent, l, r);
		if (l != 0) {
			int nl = find(minParent, l - 1);
			if (abs(V[nl] - V[l]) == 1) Q.push({V[nl] + V[l], l - 1});
		}
		r = find(maxParent, l);
		if (r != n - 1) {
			if (abs(V[r + 1] - V[l]) == 1) Q.push({V[r + 1] + V[l], r});
		}
	}
	// for (int i = 0; i < n; ++i) {
	// 	cout << find(minParent, i) << ' ';
	// }
	for (int i = 0; i < n; ++i) if (find(minParent, i) != 0) {
		cout << "NO\n"; return;
	}
	int mn = n;
	for (int i = 0; i < n; ++i) mn = min(mn, V[i]);
	if (mn != 0) {
		cout << "NO\n"; return;
	}
	cout << "YES\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}