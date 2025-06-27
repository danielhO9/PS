#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    vector<pair<ll, ll>> v(n);
    for (int i = 0; i < n; ++i) cin >> v[i].first >> v[i].second;
    sort(v.begin(), v.end(), [](const pair<int, int>& a, const pair<int, int> & b) {
       bool sga = a.second > a.first;
       bool sgb = b.second > b.first;
       if (sga == sgb) {
        if (sga == 1) return a.first < b.first;
        else return a.second > b.second;
       }
       return sga > sgb;
    });
    ll ans = 0, rem = 0;
    for (int i = 0; i < n; ++i) {
        if (rem < v[i].first) {
            ans += v[i].first - rem;
            rem = v[i].first;
        }
        rem -= v[i].first;
        rem += v[i].second;
    }
    cout << ans;

}