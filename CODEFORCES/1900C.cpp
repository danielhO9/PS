#include <bits/stdc++.h>
using namespace std;

int n, l[300001], r[300001], cache[300001], p[300001], leaf[300001];
string s;

int matchCache(int v) {
	if (v == 1) return 0;
	int& ret = cache[v];
	if (ret != -1) return ret;
	if (l[p[v]] == v) {
		if (s[p[v] - 1] == 'L') ret = matchCache(p[v]);
		else ret = matchCache(p[v]) + 1;
	}
	else if (r[p[v]] == v) {
		if (s[p[v] - 1] == 'R') ret = matchCache(p[v]);
		else ret = matchCache(p[v]) + 1;
	}
	return ret;
}

int solution() {
	cin >> n;
	cin >> s;
	for (int i = 1; i <= n; ++i) {
		cin >> l[i] >> r[i];
		p[l[i]] = i; p[r[i]] = i;
		if (l[i] == 0 && r[i] == 0) leaf[i] = 1;
		else leaf[i] = 0;
	}
	for (int i = 1; i <= n; ++i) cache[i] = -1;
	int ans = n - 1;
	for (int i = 1; i <= n; ++i) if (leaf[i]) ans = min(ans, matchCache(i));
	return ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) cout << solution() << '\n';
}