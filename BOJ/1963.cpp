#include <bits/stdc++.h>
using namespace std;

vector<int> adj[10000];
bool prime[10000];
int dis[10000];

void init() {
	for (int i = 2; i < 10000; ++i) prime[i] = true;
	for (int i = 2; i < 10000; ++i) if (prime[i]) {
		for (int j = i * 2; j < 10000; j += i) prime[j] = false;
	}
	for (int i = 1000; i < 10000; ++i) if (prime[i]) {
		string tmp = to_string(i);
		for (int j = 0; j < 4; ++j) for (char k = '0'; k <= '9'; ++k) {
			if (j == 0 && k == '0') continue;
			string change = tmp; change[j] = k;
			if (tmp != change && prime[stoi(change)]) adj[i].push_back(stoi(change));
		}
	}
}

void solve() {
	int a, b; cin >> a >> b;
	memset(dis, -1, sizeof(dis));
	queue<int> Q; Q.push(a); dis[a] = 0;
	while (!Q.empty()) {
		int v = Q.front(); Q.pop();
		for (auto u: adj[v]) if (dis[u] == -1) {
			dis[u] = dis[v] + 1;
			Q.push(u);
		}
	}
	if (dis[b] == -1) cout << "Impossible\n";
	else cout << dis[b] << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	init();
	int t; cin >> t;
	while (t--) solve();
}