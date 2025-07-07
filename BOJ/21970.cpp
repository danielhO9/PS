#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
ll K, c[100000];

void solve() {
    cin >> N >> K;
    for (int i = 0; i < N; ++i) cin >> c[i];
    ll sm = 0; for (int i = 0; i < N; ++i) sm += c[i];
    while (K > 1 && sm % 2 == 0) {
        for (int i = 0; i < N; ++i) c[i] /= 2;
        K /= 2;
        sm = 0;
        for (int i = 0; i < N; ++i) sm += c[i];
    }
    if (K == 1) {
        if (sm % 2) cout << 1;
        else cout << 0;
        return;
    } else cout << 1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}