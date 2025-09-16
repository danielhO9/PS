#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 998244353;
ll P;
ll cache[3001], ncache[3001];
ll S[10];
pair<ll, ll> rule[50];

void solve() {
    cin >> P;
    cache[0] = 1;
    for (int i = 0; i < P; ++i) {
        ll N, M; cin >> N >> M;
        for (int j = 0; j < N; ++j) cin >> S[j];
        for (int j = 0; j < M; ++j) {
            cin >> rule[j].first >> rule[j].second;
            --rule[j].first;
            --rule[j].second;
        }
        
        vector<ll> upd;
        for (int mask = 0; mask < (1 << N); ++mask) {
            bool flag = true;
            for (int j = 0; j < M; ++j) if ((mask >> rule[j].second) & 1) {
                if ((mask >> rule[j].first) & 1) continue;
                else {
                    flag = false;
                    break;
                }
            }
            if (!flag) continue;

            ll val = 0;
            for (int j = 0; j < N; ++j) if ((mask >> j) & 1) val += S[j];
            if (val != 0) upd.push_back(val);
        }
        // for (int j: upd) cout << j << ' ';
        // cout << '\n';
        for (int j = 0; j <= 3000; ++j) ncache[j] = cache[j];
        for (ll val: upd) {
            for (int j = 0; j <= 3000; ++j) if (j + val <= 3000) {
                ncache[j + val] += cache[j];
                ncache[j + val] %= MOD;
            }
        }
        swap(ncache, cache);
    }
    ll ans = 0;
    for (ll i = 0; i <= 100 * P; ++i) {
        ans += i * cache[i];
        ans %= MOD;
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}