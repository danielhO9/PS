#include <bits/stdc++.h>
using namespace std;

int M, N, H, tomato[100][100][100], ans;
int dx[6] = {1, 0, -1, 0, 0, 0}, dy[6] = {0, 1, 0, -1, 0, 0}, dz[6] = {0, 0, 0, 0, -1, 1};
deque<vector<int>> todo;

bool isPossible(int i, int j, int k) {
    if (0 <= i && i < H && 0 <= j && j < N && 0 <= k && k < M && tomato[i][j][k] == 0) return true;
    return false;
}

void printAnswer() {
    for (int i = 0; i < H; ++i) for (int j = 0; j < N; ++j) for (int k = 0; k < M; ++k) {
        if (tomato[i][j][k] == 0) {
            cout << "-1";
            return;
        }
    }
    cout << ans;
    return;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> M >> N >> H;
    for (int i = 0; i < H; ++i) for (int j = 0; j < N; ++j) for (int k = 0; k < M; ++k) {
        cin >> tomato[i][j][k];
        if (tomato[i][j][k] == 1) todo.push_back({i, j, k, 0});
    }
    while(!todo.empty()) {
        ans = max(ans, todo.front()[3]);
        for (int i = 0; i < 6; ++i) {
            if (isPossible(todo.front()[0] + dx[i], todo.front()[1] + dy[i], todo.front()[2] + dz[i])) {
                tomato[todo.front()[0] + dx[i]][todo.front()[1] + dy[i]][todo.front()[2] + dz[i]] = 1;
                todo.push_back({todo.front()[0] + dx[i], todo.front()[1] + dy[i], todo.front()[2] + dz[i], todo.front()[3] + 1});
            }
        }
        todo.pop_front();
    }
    printAnswer();
    return 0;
}