#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 998244353;

ll N, M;
string S;
ll dp[25 * 3000 + 1];
ll prefix_sum_dp[25 * 3000 + 1];

// dp[i][i]: using i times change for j prefix string

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M;
    cin >> S;
    M = min(M, 25ll * 3000 + 1);
    dp[0] = 1;
    
    for (int i = 0; i < N; ++i) {
        int max_opr = i * 25;
        prefix_sum_dp[0] = dp[0];
        for (int idx = 1; idx <= max_opr; ++idx) {
            prefix_sum_dp[idx] = dp[idx] + prefix_sum_dp[idx - 1];
            prefix_sum_dp[idx] %= MOD;
        }
        for (int idx = 0; idx <= max_opr; ++idx) {
            dp[idx] = prefix_sum_dp[idx];
            if (idx - 26 >= 0) {
                dp[idx] -= prefix_sum_dp[idx - 26];
                dp[idx] += MOD;
                dp[idx] %= MOD;
            }
        }
    }
    ll answer = 0;
    for (int i = 0; i <= M; ++i) {
        answer += dp[i];
        answer %= MOD;
    }
    cout << answer;
}