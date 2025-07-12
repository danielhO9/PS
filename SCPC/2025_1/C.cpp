#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007;

string S;
ll arr[100001];

void init() {
    arr[0] = 1;
    for (ll i = 1; i <= 100000; ++i) {
        arr[i] = arr[i - 1] * 3; arr[i] %= MOD;
    }
}

void solve() {
    cin >> S;
    int n = S.size();
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        ll tmp = S[i] - '0';
        if (i == n - 1) ++tmp;
        tmp = min(tmp, 3ll);
        ans += tmp * arr[n - i - 1];
        ans %= MOD;
        if (S[i] > '2') break;
    }
    ans += MOD - 1;
    ans %= MOD;
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    init();
    int t; cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case #" << i << '\n';
        solve();
    }
}