#include <bits/stdc++.h>
using namespace std;

int N, M;
int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, -1, 1};

void solve() {
    cin >> N >> M;
    vector<vector<int>> arr(N, vector<int>(M));
    for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> arr[i][j];

    if (!arr[N - 1][M - 3]) {
        for (int i = 1; i <= 4; ++i) {
            if (i == arr[N - 1][M - 4] || i == arr[N - 1][M - 2]) continue;
            arr[N - 1][M - 3] = i;
            break;
        }
    }
    arr[N - 3][M - 3] = arr[N - 1][M - 3];
    for (int i = 0; i < N; ++i) {
        vector<int> ord;
        if (i == N - 2) {
            ord.push_back(M - 1);
            ord.push_back(M - 2);
            for (int j = 0; j < M - 2; ++j) ord.push_back(j);
        } else {
            for (int j = 0; j < M; ++j) ord.push_back(j);
        }
        for (int j: ord) if (!arr[i][j]) {
            int val = 0;
            for (int k = 0; k < 4; ++k) {
                int ni = i + dy[k], nj = j + dx[k];
                if (0 <= ni && ni < N && 0 <= nj && nj < M && arr[ni][nj]) {
                    val |= (1 << (arr[ni][nj]));
                }
            }
            for (int k = 1; k <= 4; ++k) {
                if (val >> k & 1) continue;
                arr[i][j] = k;
                break;
            }
        }
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) cout << arr[i][j] << ' ';
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}