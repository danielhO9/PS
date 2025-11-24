#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N;
ll a[500000], d[500000];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> a[i] >> d[i];
    vector<pair<ll, ll>> v;
    for (int i = 0; i < N; ++i) v.push_back(make_pair(a[i], d[i]));
    sort(v.begin(), v.end());
    ll ans = 0;
    ll cnt = 0;
    for (int i = 0; i < N; ++i) {
        if (v[i].second == 1) ++cnt;
        else if (v[i].second == 0) ans += 2ll * cnt;
        else ans += cnt;
    }
    cnt = 0;
    for (int i = N - 1; i >= 0; --i) {
        if (v[i].second == -1) ++cnt;
        else if (v[i].second == 0) ans += 2ll * cnt;
    }
    cout << ans;
}