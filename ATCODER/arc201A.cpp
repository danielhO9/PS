#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N;
ll A[200000], B[200000], C[200000];
// ll mn[200000], mx[200000];

void solve() {
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> A[i] >> B[i] >> C[i];
    ll a = 0, c = 0;
    vector<int> v;
    for (int i = 0; i < N; ++i) {
        if (B[i] >= A[i] + C[i]) {
            a += A[i];
            c += C[i];
        } else v.push_back(i);
    }
    ll b = 0, mn = 0, mx = 0;
    for (auto i: v) {
        b += B[i];
        mn += max(0ll, B[i] - C[i]);
        mx += min(B[i], A[i]);
    }
    ll l = a + mn, r = c + b - mn;
    ll dif = mx - mn;
    if (l >= r) {
        cout << r << '\n';
        return;
    }
    if (l + dif <= r - dif) {
        cout << l + dif << '\n';
        return;
    }
    cout << (l + r) / 2 << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}