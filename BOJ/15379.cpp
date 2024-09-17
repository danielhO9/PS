#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int m, n;
vector<ll> dp_before, dp_cur;
vector<ll> sum;

ll C(int i, int j) {
	return (j - i + 1) * (i ? sum[j] - sum[i - 1] : sum[j]);
}

// min version
// compute dp_cur[l], ... dp_cur[r] (inclusive)
void compute(int l, int r, int optl, int optr) {
    if (l > r)
        return;

    int mid = (l + r) >> 1;
    pair<ll, int> best = {LLONG_MAX, -1};

    for (int k = optl; k <= min(mid, optr); k++) {
        best = min(best, {(k ? dp_before[k - 1] : 0) + C(k, mid), k});
    }

    dp_cur[mid] = best.first;
    int opt = best.second;

    compute(l, mid - 1, optl, opt);
    compute(mid + 1, r, opt, optr);
}

void solve() {
	int L, G; cin >> L >> G;
	sum.resize(L);
	for (int i = 0; i < L; ++i) {
		cin >> sum[i];
		if (i) sum[i] += sum[i - 1];
	}
	m = G; n = L;
    dp_before.assign(n,0);
    dp_cur.assign(n,0);

    for (int i = 0; i < n; i++)
        dp_before[i] = C(0, i);

    for (int i = 1; i < m; i++) {
        compute(0, n - 1, 0, n - 1);
        dp_before = dp_cur;
    }

    cout << dp_before[n - 1] << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}