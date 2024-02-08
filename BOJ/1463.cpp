#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> dp(1000001, 0);
    dp[1] = 0; dp[2] = 1; dp[3] = 1;
    for (int i = 4; i <= 1000000; ++i) {
        vector<int> possible;
        if (i % 2 == 0) possible.push_back(dp[i / 2]);
        if (i % 3 == 0) possible.push_back(dp[i / 3]);
        possible.push_back(dp[i - 1]);
        dp[i] = *min_element(possible.begin(), possible.end()) + 1;
    }
    int N; cin >> N;
    cout << dp[N];
    return 0;
}