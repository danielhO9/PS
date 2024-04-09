#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int MAX_M, MAX_N;
vector<ll> dp_cur;
vector<pair<ll, ll>> pro, con;

ll C(int i, int j) {
	return (con[j].second - pro[i].second) * (con[j].first - pro[i].first);
}

// min version
// compute dp_cur[l], ... dp_cur[r] (inclusive)
void compute(int l, int r, int optl, int optr) {
    if (l > r) return;

    int mid = (l + r) >> 1;
    pair<ll, int> best = {LLONG_MIN, -1};

    for (int k = optl; k <= optr; k++) {
        if (con[k].second > pro[mid].second) best = max(best, {C(mid, k), k});
		else break;
    }

    dp_cur[mid] = best.first;
    int opt = best.second;
	if (opt != -1) compute(l, mid - 1, optl, opt);
    compute(mid + 1, r, max(optl, opt), optr);
}

void solve() {
	int m, n; cin >> m >> n;
	vector<pair<ll, ll>> prod(m), cons(n);
	for (int i = 0; i < m; ++i) cin >> prod[i].first >> prod[i].second;
	for (int i = 0; i < n; ++i) cin >> cons[i].first >> cons[i].second;
	sort(prod.begin(), prod.end());
	sort(cons.begin(), cons.end());
	for (int i = 0; i < m; ++i) {
		if (!pro.empty() && pro.back().second <= prod[i].second) continue;
		pro.push_back(prod[i]);
	}
	for (int i = 0; i < n; ++i) {
		while (!con.empty() && con.back().second <= cons[i].second) con.pop_back();
		con.push_back(cons[i]);
	}
	MAX_N = pro.size();
	MAX_M = con.size();

    dp_cur.assign(MAX_N,0);

    compute(0, MAX_N - 1, 0, MAX_M - 1);
	ll ans = *max_element(dp_cur.begin(), dp_cur.end());
    if (ans >= 0) cout << ans;
	else cout << 0;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}