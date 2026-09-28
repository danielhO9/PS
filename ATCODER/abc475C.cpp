#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, S;
ll L, A[8001], dp[8001][8001], psm[8001];

ll dis(int i, int j) {
    assert(i <= j);
    return psm[j - 1] - psm[i - 1];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> S >> L;
    for (int i = 1; i < N; ++i) cin >> A[i];
    for (int i = 1; i <= N; ++i) psm[i] = psm[i - 1] + A[i];
    for (int i = 1; i <= N; ++i) for (int j = i; j <= N; ++j) {
        dp[i][j] = dis(i, j) + min(dis(min(S, i), max(S, i)), dis(min(S, j), max(S, j)));
    }
    int mx = 1;
    for (int i = 1; i <= N; ++i) for (int j = i; j <= N; ++j) {
        if (dp[i][j] <= L) mx = max(mx, j - i + 1);
    }
    cout << mx;
}