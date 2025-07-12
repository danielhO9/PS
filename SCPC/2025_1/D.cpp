#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, R;

void solve() {
    cin >> N >> R;
    vector<ll> bh(N - R), rh(R), bs(N-R-1), rs(R+1);
    for (int i = 0; i < N - R; ++i) cin >> bh[i];
    for (int i = 0; i < R; ++i) cin >> rh[i];
    for (int i = 0; i < N - R - 1; ++i) cin >> bs[i];
    for (int i = 0; i < R + 1; ++i) cin >> rs[i];
    sort(bh.begin(), bh.end());
    sort(rh.begin(), rh.end());
    sort(bs.begin(), bs.end());
    sort(rs.begin(), rs.end());
    
    vector<ll> lb(N - R), rb(N - R);
    for (int i = 0; i < N - R - 1; ++i) {
        lb[i] = abs(bh[i] - bs[i]);
        if (i != 0) lb[i] += lb[i - 1];
    }
    for (int i = N - R - 1; i >= 1; --i) {
        rb[i] = abs(bh[i] - bs[i - 1]);
        if (i != N - R - 1) rb[i] += rb[i + 1];
    }

    vector<ll> lr(R), rr(R);
    for (int i = 0; i < R; ++i) {
        lr[i] = abs(rh[i] - rs[i]);
        if (i != 0) lr[i] += lr[i - 1];
    }
    for (int i = R - 1; i >= 0; --i) {
        rr[i] = abs(rh[i] - rs[i + 1]);
        if (i != R - 1) rr[i] += rr[i + 1];
    }

    ll ans = LLONG_MAX;
    int idx = 0;
    for (int i = 0; i < R + 1; ++i) {
        ll cur = 0;
        if (i != 0) cur += lr[i - 1];
        if (i != R) cur += rr[i];
        while (idx < N - R - 1 && bs[idx] <= rs[i]) ++idx;
        if (idx != 0) cur += lb[idx - 1];
        if (idx != N - R - 1) cur += rb[idx + 1];
        cur += abs(rs[i] - bh[idx]);
        ans = min(ans, cur);
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case #" << i << '\n';
        solve();
    }
}