#include <bits/stdc++.h>
using namespace std;
int N, p[100][100]; bool visited[100][100];
int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
int ans, sans;

bool isPossible(int i, int j, int t) {
    if (0 <= i && i < N && 0 <= j && j < N && p[i][j] == t && !visited[i][j]) return true;
    return false;
}

void dfs(int i, int j, int t) {
    for (int k = 0; k < 4; ++k) {
        if (isPossible(i + dx[k], j + dy[k], t)) {
            visited[i + dx[k]][j + dy[k]] = 1;
            dfs(i + dx[k], j + dy[k], t);
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N; string temp;
    for (int i = 0; i < N; ++i) {
        cin >> temp;
        for (int j = 0; j < N; ++j) {
            if (temp[j] == 'R') p[i][j] = 0;
            if (temp[j] == 'G') p[i][j] = 1;
            if (temp[j] == 'B') p[i][j] = 2;
        }
    }
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
        if (!visited[i][j]) {
            ans += 1; visited[i][j] = 1;
            dfs(i, j, p[i][j]);
        }
    }
    cout << ans << " ";
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) if (p[i][j] == 1) p[i][j] = 0;
    memset(visited, 0, sizeof(visited));
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
        if (!visited[i][j]) {
            sans += 1; visited[i][j] = 1;
            dfs(i, j, p[i][j]);
        }
    }
    cout << sans;
}