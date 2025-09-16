#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1000000007;
int k;
string N;
ll cache[100000], tight;

ll slow(ll y, int x = k) {
    ll ret = 0;
    for (ll i = 1; i <= y; ++i) {
        string s = to_string(i);
        string tmp = "";
        for (auto j: s) if (j != x + '0') tmp += j;
        if (tmp.empty()) continue;
        ret += stoll(tmp);
        ret %= MOD;
    }
    return ret;
}

void solve() {
    cin >> k >> N;
    ll tmp = 45 - k;
    for (int i = 0; i < 10; ++i) {
        if (i + '0' == N[0]) break;
        if (i != k) cache[0] += i;
    }
    if (k + '0' != N[0]) tight = N[0] - '0';
    ll cnt = N[0] - '0'; --cnt;
    // cout << cache[0] << ' ' << tight << '\n';

    for (int i = 1; i < N.size(); ++i) {
        cache[i] = (cache[i - 1] * 90) % MOD;
        cache[i] += cnt * tmp; cache[i] %= MOD;
        cache[i] += cache[i - 1]; cache[i] %= MOD;

        for (int j = 0; j < 10; ++j) {
            if (j + '0' == N[i]) break;
            if (j == k) cache[i] += tight;
            else cache[i] += tight * 10 + j;
            cache[i] %= MOD;
        }
        cache[i] += tmp;
        cache[i] %= MOD;

        if (N[i] != k + '0') {
            tight = tight * 10 + N[i] - '0';
            tight %= MOD;
        }
        
        cnt = cnt * 10 + 9; cnt %= MOD;
        cnt += N[i] - '0'; cnt %= MOD;
        // cout << cache[i] << ' ' << tight << '\n';
    }
    int sz = N.size();
    cout << (cache[sz - 1] + tight) % MOD;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}