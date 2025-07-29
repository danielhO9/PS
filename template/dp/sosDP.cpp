#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> sosDP(vector<ll>& a) {
    int sz = a.size();
    int n = (int)ceil(log2(sz));
    vector<ll> ret(1 << n);
    for (int i = 0; i < n; ++i) {
        for (int x = 0; x < (1 << n); ++x) {
            if (x & (1 << i)) ret[x] += ret[x ^ (1 << i)];
        }
    }
    return ret;
}