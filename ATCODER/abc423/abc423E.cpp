#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N, Q;
ll A[300001], S[300001], SS[300001], SSS[300001], xS[300001];

void solve() {
    cin >> N >> Q;
    for (int i = 1; i <= N; ++i) cin >> A[i];
    for (int i = 1; i <= N; ++i) S[i] = S[i - 1] + A[i];
    for (int i = 1; i <= N; ++i) SS[i] = SS[i - 1] + S[i];
    for (int i = 1; i <= N; ++i) SSS[i] = SSS[i - 1] + SS[i];
    for (int i = 1; i <= N; ++i) xS[i] = i * S[i - 1];
    for (int i = 1; i <= N; ++i) xS[i] += xS[i - 1];
    while (Q--) {
        ll L, R; cin >> L >> R;
        ll ans = (R - L + 1) * SS[R]  - (SSS[R - 1] - (L - 2 >= 0 ? SSS[L - 2] : 0))
                 - (R + 1) * (SS[R - 1] - (L - 2 >= 0 ? SS[L - 2] : 0)) + xS[R] - xS[L - 1];
        cout << ans << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}