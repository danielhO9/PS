#include <bits/stdc++.h>
using namespace std;

int N, M, K;
int S[1000][1000][30];

void solve() {
    cin >> N >> M >> K;
    for (int i = 0; i < M; ++i) for (int j = 0; j < N; ++j) {
        cin >> S[i][j][0];
        --S[i][j][0];
    }
    for (int k = 1; k < 30; ++k) {
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) S[i][j][k] = S[i][S[i][j][k - 1]][k - 1];
        }
    }
    vector<int> cur(N), ncur(N); for (int i = 0; i < N; ++i) cur[i] = i;
    while (K--) {
        int X, Y; cin >> X >> Y; --X;
        for (int i = 0; i < 30; ++i) if ((Y >> i) & 1) {
            for (int j = 0; j < N; ++j) {
                ncur[S[X][j][i]] = cur[j];
            }
            swap(ncur, cur);
        }
    }
    for (int i = 0; i < N; ++i) cout << cur[i] + 1 << ' ';

}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}