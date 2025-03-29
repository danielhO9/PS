#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
    int N; string S, T; cin >> N >> S >> T;
    int ans = 0;
    for (int i = 0; i < N; ++i) if (S[i] != T[i]) ++ans;
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}