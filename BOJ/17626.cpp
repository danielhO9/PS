#include <bits/stdc++.h>
using namespace std;
vector<int> dp(50001, 5);

int main() {
    int n; cin >> n;
    for (int i = 1; i <= 50000; ++i) {
        int num = 1;
        while (num * num <= i) {
            if (num * num == i) { dp[i] = 1; break; }
            dp[i] = min(dp[i], 1 + dp[i - num * num]);
            ++num;
        }
    }
    cout << dp[n];
    return 0;
}   