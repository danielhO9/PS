#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
    int N; cin >> N;
    vector<int> A(N), B(N);
    for (int i = 0; i < N; ++i) cin >> A[i] >> B[i];
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        if (A[i] < B[i]) ++ans;
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}