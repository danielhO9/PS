#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, M;
ll A[501][501];
ll ans[501][501];
ll tmp[501][501];

void solve() {
    cin >> N >> M;
    for (int i = 1; i <= N; ++i) for (int j = 1; j <= M; ++j) cin >> A[i][j];
    for (int i = 1; i <= N; ++i) for (int j = 1; j <= M; ++j) ans[i][j] = A[i][j];
    for (int l = 1; l <= M; ++l) {
        vector<ll> sm(N + 1, 0), cur(N + 1), mx(N + 1), mn(N + 1);
        for (int r = l; r <= M; ++r) {
            for (int i = 1; i <= N; ++i) cur[i] = A[i][r];
            for (int i = 1; i <= N; ++i) cur[i] += cur[i - 1];
            for (int i = 1; i <= N; ++i) sm[i] += cur[i];
            for (int i = N; i >= 1; --i) {
                if (i != N) mx[i] = max(sm[i], mx[i + 1]);
                else mx[i] = sm[i];
            }
            for (int i = 1; i <= N; ++i) mn[i] = min(mn[i - 1], sm[i - 1]);
            for (int i = 1; i <= N; ++i) tmp[i][r] = mx[i] - mn[i];
        }
        for (int i = 1; i <= N; ++i) {
            for (int j = M - 1; j >= l; --j) tmp[i][j] = max(tmp[i][j], tmp[i][j + 1]);
        }
        for (int i = 1; i <= N; ++i) for (int j = l; j <= M; ++j) ans[i][j] = max(ans[i][j], tmp[i][j]);
    }
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) cout << ans[i][j] << ' ';
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}