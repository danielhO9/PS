#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N, M;
const ll PMAX = 75150;
ll a[200], b[200];
bool vis[PMAX];
vector<ll> p;

bool isPrime(ll x) {
    for (auto i: p) {
        if (i >= x) return true;
        if (x % i == 0) return false;
    }
    return true;
}

void solve() {
    cin >> N >> M;
    for (int i = 0; i < N; ++i) cin >> a[i];
    for (int i = 0; i < N; ++i) {
        b[i] = a[i];
        while (!isPrime(--b[i])) {}
    }
    bool flag = false;
    for (int i = 0; i < N; ++i) if (isPrime(a[i])) {
        flag = true;
        break;
    }
    if (flag && N >= 2) {
        cout << "YES\n";
        return;
    }
    ll num = 0;
    for (int i = 0; i < N; ++i) {
        if (a[i] - b[i] <= M) {
            cout << "YES\n";
            return;
        }
        num ^= ((a[i] - b[i]) % (M + 1));
    }
    if (num) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    for (int i = 2; i < PMAX; ++i) vis[i] = true;
    for (ll i = 2; i < PMAX; ++i) if (vis[i]) {
        p.push_back(i);
        for (ll j = i * 2; j < PMAX; j += i) vis[j] = false;
    }
    int t; cin >> t;
    while (t--) solve();
}
