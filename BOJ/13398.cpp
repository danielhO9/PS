#include <bits/stdc++.h>
using namespace std;

int cache[100000][2];
int arr[100000];

int matchCache(int i, int t) {
	int& ret = cache[i][t];
	if (ret != -987654321) return ret;
	if (i == 0) {
		ret = arr[i];
		return ret;
	}
	if (t == 0) {
		ret = max(0, matchCache(i - 1, 0)) + arr[i];
	} else {
		ret = max(matchCache(i - 1, 0), matchCache(i - 1, 1) + arr[i]);
	}
	return ret;
}

void solve() {
	int n; cin >> n;
	for (int i = 0; i < n; ++i) cin >> arr[i];
	for (int i = 0; i < n; ++i) for (int j = 0; j < 2; ++j) cache[i][j] = -987654321;
	matchCache(n - 1, 0);
	matchCache(n - 1, 1);
	int ans = arr[0];
	for (int i = 0; i < n; ++i) for (int j = 0; j < 2; ++j) ans = max(ans, cache[i][j]);
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}