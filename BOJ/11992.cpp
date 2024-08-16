#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> dp_before, dp_cur;
ll room[2001];
ll rsum[2001];
ll mulsum[2001];

ll C(int i, int j) {
    ll ret = mulsum[j] - mulsum[i - 1];
    ret -= (rsum[j] - rsum[i - 1]) * i;
    return ret;
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

// https://cp-algorithms.com/dynamic_programming/divide-and-conquer-dp.html
void solve() {
    ll n, k; cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> room[i];
        room[i + n] = room[i];
    }
    for (int i = 1; i <= 2 * n; ++i) {
        rsum[i] = rsum[i - 1] + room[i];
        mulsum[i] = mulsum[i - 1] + i * room[i];
    }
    
    dp_before.assign(2 * n + 1,0);
    dp_cur.assign(2 * n + 1,0);

    ll ans = LLONG_MAX;
    for (int s = 1; s <= n; ++s) {

        for (int i = s; i < s + n; i++)
        dp_before[i] = C(s, i);

        for (int i = 1; i < k; ++i) {
            compute(s, s + n - 1, s, s + n - 1);
            dp_before = dp_cur;

        }
        ans = min(ans, dp_before[s + n - 1]);
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}