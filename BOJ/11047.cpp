#include <bits/stdc++.h>
using namespace std;
int N, K, coin[10];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int N, K; cin >> N >> K;
    for (int i = 0; i < N; ++i) cin >> coin[i];
    int ans = 0;
    for (int i = N - 1; i >= 0; --i) {
        ans += K / coin[i];
        K %= coin[i];
    }
    cout << ans;
    return 0;
}