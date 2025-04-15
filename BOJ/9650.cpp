#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
ll t[35000], v[35000], cnt[35000];
ll cache[10000][100];
ll pgcd[10000][100];

ll gcd(ll a, ll b) {
    if (a < b) swap(a, b);
    if (b == 0) return a;
    return gcd(b, a % b);
}

void init() {
    for (ll i = 0; i < 10000; ++i) for (ll j = 1; j < 100; ++j) pgcd[i][j] = gcd(i, j);
}

void solve() {
    ll ans = 0;
    for (int i = 0; i < n; ++i) cnt[i] = 1;
    for (int i = 0; i < n; ++i) cin >> t[i] >> v[i];
    multiset<pair<ll, ll>> s; vector<int> arr;
    for (int i = 0; i < n; ++i) arr.push_back(i);
    sort(arr.begin(), arr.end(), [](const int& a, const int& b) {
        if (t[a] * v[a] * v[b] + 100 * v[b] == t[b] * v[a] * v[b] + 100 * v[a]) return t[a] > t[b];
        return t[a] * v[a] * v[b] + 100 * v[b] < t[b] * v[a] * v[b] + 100 * v[a]; 
    });
    for (int i = 0; i < n; ++i) {
        vector<pair<ll, ll>> tmp;
        int cur = arr[i];
        if (i + 1 < n) {
            int nxt = arr[i + 1];
            if (v[nxt] == v[cur] && t[nxt] == t[cur]) {
                cnt[nxt] += cnt[cur];
                continue;
            }
        }
        while (s.begin() != s.end()) {
            if (t[s.begin()->second] >= t[cur] - 100) break;
            s.erase(s.begin());
        }
        auto itr = s.lower_bound(make_pair(t[cur], 0));
        while (itr != s.end()) {
            int prv = itr->second;
            pair<ll, ll> f = make_pair(v[prv] * (t[prv] - t[cur]), v[prv] - v[cur]);
            ll g = pgcd[f.first][f.second];
            assert(g != 0);
            f.first /= g; f.second /= g;
            tmp.push_back(f);
            cache[f.first][f.second] += cnt[prv];
            ++itr;
        }
        s.insert(make_pair(t[cur], cur));
        for (auto& j: tmp) {
            ans = max(ans, cache[j.first][j.second] + cnt[cur]);
            cache[j.first][j.second] = 0;
        }
        ans = max(ans, cnt[cur]);
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    init();
    while (cin >> n) {
        solve();
    }
}