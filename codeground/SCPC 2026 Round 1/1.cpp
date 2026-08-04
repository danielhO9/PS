#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

ll N, M;

void solve() {
    cin >> N >> M;
    if (N % (M - 1) == 0) cout << (N / (M - 1) - 1) * M + (M - 1) + 1 << '\n';
    else cout << N / (M - 1) * M + (N % (M - 1)) + 1 << '\n';
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