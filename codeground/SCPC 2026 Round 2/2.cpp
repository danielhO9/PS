#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
ll A[200000], B[200000];
ll mn[200000], mx[200000];

void solve() {
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> A[i];
    for (int i = 0; i < N; ++i) cin >> B[i];
    for (int i = 0; i < N; ++i) {
        mn[i] = min(A[i], B[i]);
        mx[i] = max(A[i], B[i]);
    }
    sort(mn, mn + N);
    sort(mx, mx + N);
    ll ans = 0;
    for (ll i = 0; i < N; ++i) {
        ans += mn[i] * (i - N + 1 + i);
        ans += mx[i] * (i - N + 1 + i);
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case #" << i << '\n';
        solve();
        cout.flush();
    }
}