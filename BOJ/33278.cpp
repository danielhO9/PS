#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N, t;
ll x[300000], h[300000];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> t;
    for (int i = 0; i < N; ++i) cin >> x[i] >> h[i];
    vector<pair<ll, ll>> v;
    for (int i = 0; i < N; ++i) v.push_back(make_pair(x[i], h[i]));
    sort(v.begin(), v.end());
    for (int i = 1; i < N; ++i) v[i].first -= v[0].first;
    v[0].first = 0;
    ll mx = 0;
    ll ans = 0;
    for (int i = 0; i < N; ++i) {
        mx = max(mx, v[i].first * t);
        ans += min(mx - v[i].first * t, v[i].second);
        mx = max(mx, v[i].first * t + v[i].second);
    }
    cout << ans;
}