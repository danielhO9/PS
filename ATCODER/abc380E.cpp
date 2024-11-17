#include <bits/stdc++.h>
using namespace std;

int N, Q;
const int MAX_N = 500001;
int lpar[MAX_N];
int rpar[MAX_N];
int col[MAX_N];
int sz[MAX_N];
int cnt[MAX_N];

int lfind(int x) {
	if (lpar[x] == x) return x;
	lpar[x] = lfind(lpar[x]);
	return lpar[x];
}

int rfind(int x) {
	if (rpar[x] == x) return x;
	rpar[x] = rfind(rpar[x]);
	return rpar[x];
}

void union_path(int x, int y) {
	int lx = lfind(x), ly = lfind(y);
	if (lx != ly) {
		if (lx > ly) swap(lx, ly);
		lpar[ly] = lx;
		sz[lx] += sz[ly];
	}
	int rx = rfind(x), ry = rfind(y);
	if (rx != ry) {
		if (rx < ry) swap(rx, ry);
		rpar[ry] = rx;
	}
}

void solve() {
	cin >> N >> Q;
	for (int i = 1; i <= N; ++i) {
		lpar[i] = i; rpar[i] = i; sz[i] = 1; col[i] = i;
		cnt[i] = 1;
	}
	while (Q--) {
		int t; cin >> t;
		if (t == 1) {
			int x, c; cin >> x >> c;
			int l = lfind(x);
			if (col[l] == c) continue;
			int r = rfind(x);
			cnt[col[l]] -= sz[l];
			col[l] = c;
			cnt[c] += sz[l];
			if (l != 0) {
				if (col[lfind(l - 1)] == c) union_path(l - 1, l);
			}
			if (r != N) {
				if (col[r + 1] == c) union_path(l, r + 1);
			}
		} else {
			int c; cin >> c;
			cout << cnt[c] << '\n';
		}
	}

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}