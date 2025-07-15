#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll prime[2] = {17, 53};
const ll MOD = 998244353;

ll hashing(const vector<ll>& a) {
    ll val[2] = {1ll, 1ll};
    ll curp[2] = {1ll, 1ll};
    for (auto j: a) {
        for (int i = 0; i < 2; ++i) {
            curp[i] *= prime[i]; curp[i] %= MOD;
            val[i] += (j * curp[i]) % MOD;
            val[i] %= MOD;
        }
    }
    return val[0] * val[1];
}