#include <bits/stdc++.h>
using namespace std;

int X;
int dp[500001];

void init() {
    memset(dp, -1, sizeof(dp));
    dp[0] = 0;
    for (int i = 2; i <= 1000; ++i) {
        for (int j = 500000; j >= i; --j) {
            if (dp[j] == -1 && dp[j - i] != -1) dp[j] = i;
        }
    }
};

int check(int N) {
    int mx = N * (N + 1) / 2;
    int mn = -mx + 2;
    if (X < mn || X > mx) return 0;
    return 1;
}

void solve() {
    cin >> X;
    if (X == 0) {
        cout << "3\n1+2-3\n";
        return;
    }
    int l = 0, r = 1000;
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (check(mid)) r = mid;
        else l = mid;
    }
    int N = r;
    set<int> st;
    while (true) {
        int dif = N * (N + 1) / 2 - X;
        if (dif % 2 == 1 || dif == 2) {
            ++N;
            continue;
        }
        dif >>= 1;
        if (dp[dif] != -1 && dp[dif] <= N) {
            while (dif) {
                st.insert(dp[dif]);
                dif -= dp[dif];
            }
            break;
        }
        ++N;
    }
    cout << N << '\n';
    cout << 1;
    for (int i = 2; i <= N; ++i) {
        if (st.find(i) != st.end()) cout << '-';
        else cout << '+';
        cout << i;
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    init();
    int t; cin >> t;
    while (t--) solve();
}