#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 998244353;

ll N, Q;
ll a[500000];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> Q;
    for (int i = 0; i < N; ++i) cin >> a[i];
    vector<pair<ll, ll>> arr;
    for (int i = 0; i < N; ++i) arr.push_back(make_pair(a[i], i));
    sort(arr.begin(), arr.end());
    vector<int> ord(N);
    for (int i = 0; i < N; ++i) ord[arr[i].second] = i;
    
    ll ans = 0;
    for (ll i = 0; i < N; ++i) {
        ll tmp = arr[i].first * (arr[i].first - 1) / 2; tmp %= MOD;
        tmp *= (N - i - 1); tmp %= MOD;
        ans += tmp; ans %= MOD;
    }
    // cout << ans << '\n';
    while (Q--) {
        int v, x; cin >> v >> x; --v;
        int idx = ord[v];
        
        if (x == 1) {
            int l = idx, r = N;
            while (l + 1 < r) {
                int m = (l + r) >> 1;
                if (arr[m].first == a[v]) l = m;
                else r = m;
            }

            ans += (a[v] * (N - 1 - l)) % MOD; ans %= MOD;
            ++a[v];
            swap(ord[v], ord[arr[l].second]);
            swap(arr[l], arr[idx]);
            ++arr[l].first;
        } else {
            int l = -1, r = idx;
            while (l + 1 < r) {
                int m = (l + r) >> 1;
                if (arr[m].first == a[v]) r = m;
                else l = m;
            }

            ans -= ((a[v] - 1) * (N - 1 - r)) % MOD; ans += MOD; ans %= MOD;
            --a[v];
            swap(ord[v], ord[arr[r].second]);
            swap(arr[r], arr[idx]);
            --arr[r].first;
        }
        cout << ans << '\n';
    }
}