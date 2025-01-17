#include <bits/stdc++.h>
using namespace std;

int n, m, k;

void solve() {
	cin >> n >> m >> k;
	vector<int> q;
	for (int i = 0; i < m; ++i) {
		int val = 0;
		for (int j = 0; j < k; ++j) {
			int tmp; cin >> tmp; --tmp;
			val += (1 << tmp);
		}
		q.push_back(val);
	}
	int ans = 0;
	for (int i = 0; i < (1 << (2 * n)); ++i) if (__builtin_popcount(i) == n) {
		int cnt = 0;
		for (auto j: q) if ((j & i) == j) ++cnt;
		ans = max(ans, cnt);
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}