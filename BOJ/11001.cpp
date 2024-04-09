#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, D;
vector<ll> dp_before, dp_cur;
vector<ll> T, V;

// compute dp_cur[l], ... dp_cur[r] (inclusive)
void compute(int l, int r, int optl, int optr) {
    if (l > r)
        return;

    int mid = (l + r) >> 1;
    pair<ll, int> best = {LLONG_MIN, -1};

    for (int k = max(optl, mid - D); k <= min(mid, optr); k++) {
        best = max(best, {V[k] - k * T[mid] + mid * T[mid], k});
    }

    dp_cur[mid] = best.first;
    int opt = best.second;

    compute(l, mid - 1, optl, opt);
    compute(mid + 1, r, opt, optr);
}

void solve() {
	int N; cin >> N >> D; n = N;
	T.resize(N); V.resize(N);
	for (int i = 0; i < N; ++i) cin >> T[i];
	for (int i = 0; i < N; ++i) cin >> V[i];
    dp_before.assign(n,0);
    dp_cur.assign(n,0);
    compute(0, n - 1, 0, n - 1);
    dp_before = dp_cur;
    cout << *max_element(dp_before.begin(), dp_before.end());
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}