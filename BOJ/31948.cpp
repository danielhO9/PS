#include <bits/stdc++.h>
using namespace std;

int cache[1501][1501][3];
string S = "";

int matchCache(int l, int r, int t) {
	if (l == r) return false;
	int& ret = cache[l][r][t];
	if (ret != -1) return ret;
	ret = 0;
	if (t == 2) {
		if (matchCache(l, r, 0) == 0 || matchCache(l, r, 1) == 0) {
			ret = 1;
			return ret;
		}
	}
	for (int i = l; i < r; ++i) {
		char base = S[l] == '?' ? '0' + t : S[l];
		char tmp = S[i] == '?' ? '0' + t : S[i];
		if (base == '2' || base != tmp) break;
		if (matchCache(i + 1, r, t) == 0) {
			ret = 1;
			return ret;
		}
	}
	for (int i = r - 1; i > l; --i) {
		char base = S[r - 1] == '?' ? '0' + t : S[r - 1];
		char tmp = S[i] == '?' ? '0' + t : S[i];
		if (base == '2' || base != tmp) break;
		if (matchCache(l, i, t) == 0) {
			ret = 1;
			return ret;
		}
	}
	return ret;
}

void solve() {
	cin >> S;
	int t = 0;
	for (auto i: S) if (i == '?') t = 2;
	memset(cache, -1, sizeof(cache));
	cout << matchCache(0, S.size(), t);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}