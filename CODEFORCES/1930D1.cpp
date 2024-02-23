#include <bits/stdc++.h>
using namespace std;

int n; string s;
int cache[1000000];

int matchCache(int x) {
	if (x >= n) return 0;
	int& ret = cache[x];
	if (ret != -1) return ret;
	if (s[x] == '1') ret = matchCache(x + 3) + n - x;
	else ret = matchCache(x + 1);
	return ret;
}

void solve() {
	cin >> n; cin >> s;
	for (int i = 0; i < n; ++i) cache[i] = -1;
	int ans = 0;
	for (int i = 0; i < n; ++i) ans += matchCache(i);
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while (t--) solve();
}