#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAX = 998244353;

string S, N;
ll cost[1000][10], sm[1000];

ll cache[1001][10];
ll ncache[1001][10];

void solve() {
    cin >> S >> N;
    int s = S.size(), n = N.size();
    
    if (s < n) {
        cout << -1;
        return;
    }

    for (int i = 0; i < S.size(); ++i) {
        if (i == 0) {
            for (int j = 0; j < 10; ++j) cost[i][j] = MAX;
            cost[i][0] = 1;
            cost[i][S[i] - '0'] = 0;
        } else {
            int x = S[i] - '0';
            for (int j = 0; j < 10; ++j) {
                cost[i][j] = cost[i - 1][j] + (S[i] == '0' ? 0 : 1);
                cost[i][j] = min(cost[i][j], cost[i - 1][(j - x + 10) % 10]);
            }
        }
    }
    // for (int i = 0; i < s; ++i) {
    //     for (int j = 0; j < 10; ++j) cout << cost[i][j] << ' ';
    //     cout << '\n';
    // }

    for (int i = 0; i < s; ++i) for (int j = 0; j < 10; ++j) cache[i][j] = cost[i][j];

    // N[t-1]j -> N[t]j
    for (int t = 0; t < n - 1; ++t) {
        for (int i = 0; i < s; ++i) for (int j = 0; j < 10; ++j) ncache[i][j] = cache[i][j];
        for (int i = 0; i < s; ++i) for (int j = 0; j < 10; ++j) cache[i][j] = MAX;

        for (int j = 0; j < 10; ++j) cache[t + 1][j] = min(cache[t + 1][j], ncache[t][N[t] - '0'] + (S[t + 1] == j + '0' ? 0 : (j == 0 ? 1 : MAX)));

        for (int i = t + 2; i < s; ++i) {
            int x = S[i] - '0';
            for (int j = 0; j < 10; ++j) {
                cache[i][j] = min(cache[i][j], ncache[i - 1][N[t] - '0'] + (S[i] - '0' == j ? 0 : (j == 0 ? 1 : MAX)));
                cache[i][j] = min(cache[i][j], (S[i] == '0' ? 0 : 1) + cache[i - 1][j]);
                cache[i][j] = min(cache[i][j], cache[i - 1][(j - x + 10) % 10]);
            }
        }
    }


    int ans = cache[s - 1][N[n - 1] - '0'];
    if (ans == MAX) cout << -1;
    else cout << ans;

}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}