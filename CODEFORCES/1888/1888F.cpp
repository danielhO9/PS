#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

struct query {
	LL l, r, x;
};

void solve() {
	LL n; cin >> n;
	LL a[n]; for (int i = 0; i < n; ++i) cin >> a[i];
	LL dif[n];
	for (int i = 0; i < n; ++i) {
		if (i == 0) dif[i] = a[i];
		else dif[i] = a[i] - a[i - 1];
	}
	vector<query> Q; Q.push_back({1, 1, 0});
	LL q; cin >> q;
	for (int i = 0; i < q; ++i) {
		LL l, r, x; cin >> l >> r >> x;
		--l; --r;
		Q.push_back({l, r, x});
	}
	map<LL, LL> M;
	LL ans = 0;
	for (LL i = 1; i <= q; ++i) {
		LL l = Q[i].l, r = Q[i].r, x = Q[i].x;
		if (x == 0) continue;
		M[l] += x;
		if (r != n - 1) M[r + 1] -= x;
		for (auto [j, k]: M) {
			if (k == 0) continue;
			else if (k < 0) {
				ans = i;
				M.clear();
				break;
			} else {
				break;
			}
		}
	}
	for (LL i = 1; i <= ans; ++i) {
		LL l = Q[i].l, r = Q[i].r, x = Q[i].x;
		dif[l] += x;
		if (r != n - 1) dif[r + 1] -= x;
	}
	LL value = 0;
	for (LL i = 0; i < n; ++i) {
		value += dif[i];
		cout << value << ' ';
	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}

// 2 1 2 5 4
// 2 4 5 8 4
// 2 4 3 6 2
// 3 5 4 6 2