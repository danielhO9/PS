#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> cache;

bool comp(char a, char b) {
	if (a == b) return true;
	if (a == 'i') {
		if (b == 'i' || b == 'j' || b == 'l') return true;
	}
	if (a == 'v') {
		if (b == 'v' || b == 'w') return true;
	}
	return false;
}

string S, T;

int matchCache(int a, int b) {
	int& ret = cache[a][b];
	if (ret != -1) return ret;
	if (a == 0 || b == 0) {
		ret = a + b;
		return ret;
	}
	bool same = comp(S[a - 1], T[b - 1]);
	ret = min({matchCache(a - 1, b) + 1, matchCache(a, b - 1) + 1, matchCache(a - 1, b - 1) + !same});
	return ret;
}

void solve() {
	int n, m; cin >> n >> m;
	cin >> S >> T;
	cache = vector<vector<int>>(n + 1, vector<int>(m + 1, -1));
	cout << matchCache(n, m);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}