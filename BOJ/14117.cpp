#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int m, n;
vector<ll> dp_before, dp_cur;
vector<vector<ll>> sum;

ll C(int i, int j) {
	ll ret = sum[j][j];
	if (i != 0) ret -= sum[i - 1][j] + sum[j][i - 1] - sum[i - 1][i - 1];
	return ret / 2;
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
	int N, K; cin >> N >> K;
	m = K; n = N;
	sum.resize(n);
	for (int i = 0; i < n; ++i) sum[i].resize(n);
	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cin >> sum[i][j];
	for (int i = 0; i < n; ++i) for (int j = 1; j < n; ++j) sum[i][j] += sum[i][j - 1];
	for (int i = 1; i < n; ++i) for (int j = 0; j < n; ++j) sum[i][j] += sum[i - 1][j];
    dp_before.assign(n,0);
    dp_cur.assign(n,0);

    for (int i = 0; i < n; i++)
        dp_before[i] = C(0, i);

    for (int i = 1; i < m; i++) {
        compute(0, n - 1, 0, n - 1);
        dp_before = dp_cur;
    }

    cout << dp_before[n - 1];
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}