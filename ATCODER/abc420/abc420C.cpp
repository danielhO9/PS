#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, Q;
ll A[200000], B[200000], mn[200000];

void solve() {
    cin >> N >> Q;
    for (int i = 0; i < N; ++i) cin >> A[i];
    for (int i = 0; i < N; ++i) cin >> B[i];
    ll ans = 0;
    for (int i = 0; i < N; ++i) {
        mn[i] = min(A[i], B[i]);
        ans += mn[i];
    }
    while (Q--) {
        char c; int X; ll V;
        cin >> c >> X >> V; --X;
        ans -= mn[X];
        if (c == 'A') A[X] = V;
        else B[X] = V;
        mn[X] = min(A[X], B[X]);
        ans += mn[X];
        cout << ans << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}