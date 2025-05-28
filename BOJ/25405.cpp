#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N, M, K;
ll L[100000];

pair<ll, ll> f(ll x) {
    pair<ll, ll> ret = make_pair(0, 0);
    for (int i = 0; i < N; ++i) {
        if (L[i] + M <= x) {
            ret.first += M;
            ret.second += M;
        } else if (L[i] >= x + 1) {
            continue;
        } else {
            ret.first += x - L[i];
            ret.second += x + 1 - L[i];
        }
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> L[i];
    cin >> M >> K;
    sort(L, L + N);
    ll l = -1, r = 2e9, mid;
    while (l + 1 < r) {
        mid = (l + r) / 2;
        auto res = f(mid);
        if (res.second < M * K) l = mid;
        else r = mid;
    }
    ll cnt = M * K - f(r).first;
    vector<ll> ans;
    for (int i = 0; i < N; ++i) {
        if (L[i] + M <= r) ans.push_back(L[i] + M);
        else if (L[i] >= r + 1) ans.push_back(L[i]);
    }
    for (int i = 0; i < cnt; ++i) ans.push_back(r + 1);
    while (ans.size() < N) ans.push_back(r);
    sort(ans.begin(), ans.end());
    for (int i = 0; i < N; ++i) cout << ans[i] << ' ';
}