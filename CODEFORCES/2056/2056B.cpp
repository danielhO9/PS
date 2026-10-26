#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
bool graph[1000][1000];

void solve() {
	cin >> n;
	for (int i = 0; i < n; ++i) {
		string s; cin >> s;
		for (int j = 0; j < n; ++j) graph[i][j] = (s[j] == '1');
	}
	vector<int> adj[n];
	vector<int> deg(n, 0);
	for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) {
		if (graph[i][j]) {
			adj[i].push_back(j);
			++deg[j];
		}
		else {
			adj[j].push_back(i);
			++deg[i];
		}
	}
	vector<int> ans;
	queue<int> q;
	for (int i = 0; i < n; ++i) if (deg[i] == 0) q.push(i);
	while (!q.empty()) {
		int cur = q.front(); q.pop();
		ans.push_back(cur + 1);
		for (auto i: adj[cur]) {
			--deg[i];
			if (deg[i] == 0) q.push(i);
		}
	}
	for (auto i: ans) cout << i << ' ';
	cout << '\n';


}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}