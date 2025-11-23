#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007;

ll pow(ll a, ll b) {
    if (!b) return 1;
    ll h = pow(a, b >> 1ll);
    h = (h * h) % MOD;
    if (b & 1) return (h * a) % MOD;
    else return h;
}

ll p, q, n;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> p >> q >> n;
    ll val = 1;
    ll x = 1, y = 1, z = 0;
    

    for (int i = 1; i <= n; ++i) {
        if (i == 1) cout << 0 << ' ';
        else if (i == 2) cout << 1 << ' ';
        else {
            vector<pair<ll, ll>> v;
            int cur = 0;
            v.push_back(make_pair(x + 2, x));
            v.push_back(make_pair(y + 2, y));
            v.push_back(make_pair(p, q));
            if (v[0].first * v[1].second < v[1].first * v[0].second) {
                swap(v[0], v[1]);
                cur = 1;
            }
            if (v[0].first * v[2].second < v[2].first * v[0].second) {
                swap(v[0], v[2]);
                cur = 2;
            }
            val *= v[0].first; val %= MOD;
            val *= pow(v[0].second, MOD - 2); val %= MOD;
            if (cur== 0) ++x;
            else if (cur == 1) ++y;
            else ++z;
            cout << val << ' ';
        }
    }
    
}