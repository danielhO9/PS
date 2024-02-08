#include <bits/stdc++.h>
using namespace std;
int N;
bool graph[100][100], ans[100][100];

void dfs(int i, int j) {
    for (int k = 0; k < N; ++k) {
        if (graph[j][k] == 1 && ans[i][k] == 0) {
            ans[i][k] = 1; dfs(i, k);
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) cin >> graph[i][j];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (graph[i][j] == 1 && ans[i][j] == 0) {
                ans[i][j] = 1; dfs(i, j);
            }
        }
    }
    for (int i = 0; i < N; ++i) { for (int j = 0; j < N; ++j) cout << ans[i][j] << " "; cout << "\n"; }
}