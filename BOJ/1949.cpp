#include <bits/stdc++.h>
using namespace std;

int arr[10001];
vector<int> adj[10001];
int cache[10001][2];

int matchCache(int x, int p, int t) {
	int& ret = cache[x][t];
	if (ret != -1) return ret;
	if (t == 1) {
		ret = arr[x];
		for (auto i: adj[x]) if (i != p) ret += matchCache(i, x, 0);
		// cout << x << ' ' << t << ' ' << ret << '\n';
		return ret;
	} else {
		ret = 0;
		for (auto i: adj[x]) if (i != p) {
			ret += max(matchCache(i, x, 0), matchCache(i, x, 1));
		}
		// cout << x << ' ' << t << ' ' << ret << '\n';
		return ret;
	}
}

void solve() {
	int N; cin >> N;
	memset(cache, -1, sizeof(cache));
	for (int i = 1; i <= N; ++i) cin >> arr[i];
	for (int i = 0; i < N - 1; ++i) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b); adj[b].push_back(a);
	}
	cout << max(matchCache(1, 0, 0), matchCache(1, 0, 1));
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}