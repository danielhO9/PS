#include <bits/stdc++.h>
using namespace std;
int N, M, wall[600][600], visited[600][600], ans, dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
deque<pair<int, int>> Q;

bool isPossible(int i, int j) {
    if (0 <= i && i < N && 0 <= j && j < M && !visited[i][j] && wall[i][j] != 1) return true;
    return false;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M; string temp;
    for (int i = 0; i < N; ++i) {
        cin >> temp;
        for (int j = 0; j < M; ++j) {
            if (temp[j] == 'I') {
                Q.push_back({i, j}); visited[i][j] = 1;
            } else if (temp[j] == 'X') wall[i][j] = 1;
            else if (temp[j] == 'P') wall[i][j] = 2;
        }
    }
    while (!Q.empty()) {
        for (int i = 0; i < 4; ++i) {
            if (isPossible(Q.front().first + dx[i], Q.front().second + dy[i])) {
                visited[Q.front().first + dx[i]][Q.front().second + dy[i]] = 1;
                if (wall[Q.front().first + dx[i]][Q.front().second + dy[i]] == 2) ++ans;
                Q.push_back({Q.front().first + dx[i], Q.front().second + dy[i]});
            }
        }
        Q.pop_front();
    }
    if (ans == 0) cout << "TT";
    else cout << ans;
}