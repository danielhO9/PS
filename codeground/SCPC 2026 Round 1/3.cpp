#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

ll N, A[200001];

void solve() {
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> A[i];
    ll pos = A[0], neg = -A[0];
    ll dp;
    for (int i = 0; i < N; ++i) {
        dp = max(A[i] + neg, pos - A[i]);
        pos = max(pos, dp + A[i + 1]);
        neg = max(neg, dp - A[i + 1]);
    }
    cout << dp << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case #" << i <<  '\n';
        solve();
        cout.flush();
    }
}