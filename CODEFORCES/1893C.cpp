#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	int m; cin >> m;
	int n[m];
	LL l[m], r[m], csum[m];
	for (int i = 0; i < m; ++i) csum[i] = 0;
	vector<LL> a[m], c[m];
	LL nsum = 0, lsum = 0, rsum = 0;
	unordered_map<LL, LL> M[m];
	// 해당 값이 있는 multiset index
	unordered_map<LL, vector<LL>> Portal;
	for (int i = 0; i < m; ++i) {
		cin >> n[i] >> l[i] >> r[i];
		nsum += n[i]; lsum += l[i]; rsum += r[i];
		LL ai, ci;
		for (int j = 0; j < n[i]; ++j) {
			cin >> ai;
			a[i].push_back(ai);
			Portal[ai].push_back(i);
		}
		for (int j = 0; j < n[i]; ++j) {
			cin >> ci;
			c[i].push_back(ci);
			csum[i] += ci;
		}
	}
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n[i]; ++j) {
			M[i][a[i][j]] = c[i][j];
		}
	}
	if (rsum  - lsum > nsum) {
		cout << 0 << '\n';
		return;
	}
	LL ret = LLONG_MAX;
	for (LL i = lsum; i <= rsum; ++i) {
		LL xsize = rsum, must_len = 0;
		for (auto j: Portal[i]) {
			xsize -= r[j];
			LL cnt_not_len = csum[j] - M[j][i];
			if (cnt_not_len < l[j]) {
				xsize += l[j];
				must_len += l[j] - cnt_not_len;
			} else {
				xsize += min(cnt_not_len, r[j]);
			}
		}
		ret = min(ret, must_len + max(0LL, i - xsize));
	}
	cout << ret << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}