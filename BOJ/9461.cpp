#include <bits/stdc++.h>
using namespace std;
long long dp[101];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    dp[1] = dp[2] = dp[3] = 1;
    dp[4] = dp[5] = 2;
    for (int i = 6; i <= 100; ++i) dp[i] = dp[i - 1] + dp[i - 5];
    int T; cin >> T; int temp;
    for (int i = 0; i < T; ++i) {
        cin >> temp;
        cout << dp[temp] << "\n";
    }
    return 0;
}