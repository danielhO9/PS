#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N; ll K;
ll c[100], t[100], s[100];

void solve() {
    ll ans = 0;
    cin >> N >> K;
    for (int i = 0; i < N; ++i) cin >> c[i] >> t[i] >> s[i];
    set<pair<ll, ll>> v;
    vector<int> idx(N); for (int i = 0; i < N; ++i) idx[i] = i;
    sort(idx.begin(), idx.end(), [](const int& a, const int& b) {
        return s[a] > s[b];
    });
    for (int i = 0; i < N; ++i) {
        int cur = idx[i];
        ll left = c[cur];
        ll e = t[cur];
        ll start;
        while (left) {
            bool flag = true;
            for (auto j = v.rbegin(); j != v.rend(); ++j) {
                if (j->first <= e && e <= j->second) {
                    e = j->first - 1;
                }
            }
            for (auto j = v.rbegin(); j != v.rend(); ++j) {
                if (j->second < e) {
                    start = j->second + 1;
                    flag = false;
                    break;
                }
            }
            if (e == 0) break;
            if (flag) start = max(1ll, e - left + 1);
            ll pos = e - start + 1;
            pos = min(pos, left);
            if (pos == 0) break;
            left -= pos;
            // cout << pos << ' ';
            ans += pos * s[cur];
            start = e + 1 - pos;
            v.insert(make_pair(start, e));
        }
    }
    cout << ans;
    // for (auto i: v) cout << i.first << ' ' << i.second << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case #" << i << ": ";
        solve();
        cout << '\n';
    }
}